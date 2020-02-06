#include "conection.h"
#include "Mpu_filter.h"
#include "timer-it.h"
#include "Pid.h"
#include "states.h"

unsigned int check_esc_order(unsigned int signal){
  signal = max(signal, 1000);
  signal = min(signal, 2000);
  return signal ;
}

//PID settings
#define kP 0
#define kI 0
#define kD 0
#define MAX_PID 200

Mpu_filter mpu ;
Pid roll_pid ;
Pid pitch_pid ;
Timer_it timer ;

//Consignes 
float consigne_roll = 0 ;
float consigne_pitch = 0 ;

//Loop frequency regulation
#define frequence 250
unsigned long loop_timer = 0 ;

//Read PPM signal
#define  NUMBER_OF_CHANEL  11 
byte actual_chanel = 0 ;
unsigned long previous_timer_rising = 0 ;
unsigned int  chanels[NUMBER_OF_CHANEL] ;

//Esc pulses function
unsigned long time_esc = 0 ;
unsigned int esc_pulses[4] = {1000, 1000, 1000, 1000};

//Store our sequences for each states
//sequences are stored on 5 bit of a byte as we just need to know if it is low 0 or high 1 
#define NUMBER_OF_STATES 5
#define sequence1 0b00011000
#define sequence2 0b00011100
#define sequence3 0b00011010
#define sequence4 0b00010000
#define sequence5 0b00011110

byte sequences [NUMBER_OF_STATES] = {sequence1, sequence2, sequence3, sequence4, sequence5}; 
byte sequence_evolution_counter = 0 ;

byte state = STATE_INIT_MPU ;    //We start with the mpu init state 


///////////////////////////////////////////// SETUP¨////////////////////////////////////////////////////////////////////////////


void setup(){
  pinMode(A0, OUTPUT);
  //Initialize the timer
  //We must do it first as it is requiered for the state led 
  timer.init();

  //Set the right output on the pin for the state led
  pinMode(STATE_LED, OUTPUT);

  //Begin Serial Comunication 
  Serial.begin(115200);
  Serial.println("Program begins");

  //Init & calibrate the mpu  
  mpu.set_mpu();

  state = STATE_CALIB_MPU ;
  mpu.calibrate(200); 

  //Set our pids coef
  roll_pid.set_coef(kP, kD, kI);
  pitch_pid.set_coef(kP, kD, kI);
  roll_pid.max_output = MAX_PID ;
  pitch_pid.max_output = MAX_PID ;

  //Set esc pins as output
  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);
  pinMode(PIN_MOTOR_3, OUTPUT);
  pinMode(PIN_MOTOR_4, OUTPUT);
  //same as 
  //DDRB |= 0b00001111 ;

  //PPM IT INIT PART
  attachInterrupt(digitalPinToInterrupt(PIN_PPM_IT), rising, RISING);
  Serial.println("Fin setup");

  state = STATE_MOTOR_DOWN ;

}


IT_FUNCTION{
  //Blink the led according to sequence we want 
  byte led_state = sequences[state] ;
  led_state = led_state >> (5 - sequence_evolution_counter) ;
  //Serial.println(state);
  led_state &= 0b00000001 ;
  sequence_evolution_counter ++ ;
  if(sequence_evolution_counter == 5)
    sequence_evolution_counter = 0 ;
  digitalWrite(STATE_LED, led_state); 

}

void loop(){


  //  ====================== FIN DU SIGNAL DES ESC ===================================
  //  ====================== deux secondes dispo ~ donc lecture mpu et compilation des sorties des moteurs

  //Update MPU
  
  mpu.update(true);

  if(state == STATE_MOTOR_DOWN){
    for(byte m = 0; m < 4; m++)
      esc_pulses[m] = 1000 ; 
  
  }

  else if(state == STATE_FLYING && chanels[CHANEL_THROTTLE] > 1050){
    //Pid calculation 
    unsigned int throttle = chanels[CHANEL_THROTTLE] ;
    float pitch_comp = pitch_pid.compute_pid(consigne_pitch - mpu.Y);
    float roll_comp = roll_pid.compute_pid(consigne_roll - mpu.X);

    esc_pulses[0] = check_esc_order(-pitch_comp + roll_comp + throttle) ;
    esc_pulses[1] = check_esc_order(pitch_comp + roll_comp + throttle);
    esc_pulses[2] = check_esc_order(pitch_comp - roll_comp + throttle) ;
    esc_pulses[3] = check_esc_order(-pitch_comp - roll_comp + throttle) ;


  }
  else{
    for(byte m = 0; m < 4; m++)
      esc_pulses[m] = 1000 ; 
  
  }

  //Pour passer en mode de vol et se maintenir
  //La consigne moteur doit être à zéro 
  //Le switch 1 > 1600  
  if((chanels[CHANEL_SWITCH_1] > 1600)   &&   (chanels[CHANEL_THROTTLE] < 1050 || state == STATE_FLYING))
    state = STATE_FLYING ;
  //Sinon
  else 
    state = STATE_MOTOR_DOWN ;


  //This regulates the rate of the main loop at 250 Hz 
  while(micros()<loop_timer + 1000000/frequence);
  loop_timer = micros();

  //Escs pulses start, notice that we set our outputs high at "loop_timer" moment 
  PORTB |= 0b00001111 ;
  
  
  // Serial.print(mpu.X);
  // Serial.print("\t");
  // Serial.println(mpu.acc_x);

  //Check if it is the time to shut down our esc signal
  while(PORTB != (PORTB & 0b11110000)){
    time_esc = micros() ; 
    for(byte m = 0; m < 4; m++){
      if(time_esc - loop_timer >= esc_pulses[m] ) {        
        PORTB = PORTB & ~(1<<m) ; 
      }
    }
  }

  
}

//This function is called when the pin 2 state changes
void rising()
{
  unsigned int signal_ppm = micros()-previous_timer_rising ;
  if (signal_ppm > 3000) 
  {
    actual_chanel = 0 ;
    previous_timer_rising = micros();
    chanels[actual_chanel] = signal_ppm ;
  }  

  else 
  {
    actual_chanel ++;
    if (actual_chanel == NUMBER_OF_CHANEL) 
      actual_chanel = 0 ;
    chanels[actual_chanel] = signal_ppm ;
    previous_timer_rising = micros();
  }  
  
}








