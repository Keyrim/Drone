#include "conection.h"
#include "Mpu_filter.h"
#include "Pid.h"

//PID settings
#define kP 1
#define kI 0
#define kD 0
#define MAX_PID 200

Mpu_filter mpu ;
Pid roll_pid ;
Pid pitch_pid ;

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





void setup(){
  //Begin Serial Comunication 
  Serial.begin(115200);
  Serial.println("Program begins");

  //Init & calibrate the mpu  
  //mpu.set_mpu();
  //mpu.calibrate(100);

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

}

void loop(){

  
  if(chanels[CHANEL_SWITCH_1] > 1500)   //The switch defines is we can start the motors
  {

  }


  //This regulates the rate of the main loop at 250 Hz

  while(micros()<loop_timer + 1000000/frequence);
  loop_timer = micros();

  //Escs pulses start, notice that we set our outputs high at "loop_timer" moment 
  PORTB |= 0b00001111 ;
  for(byte m = 0; m < 4; m++){
    esc_pulses[m] = chanels[CHANEL_THROTTLE] ; 
  }
  //Update MPU
  //mpu.update(true);


  //Check if it is the time to shut down our esc signal
  byte compteur_moteur_up = 4 ;
  while(PORTB != (PORTB & 0b11110000)){
    time_esc = micros() ; 
    for(byte m = 0; m < 4; m++){
      if(time_esc - loop_timer >= esc_pulses[m] ) {        
        PORTB &= ~(1<<m) ;
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
    if (actual_chanel == NUMBER_OF_CHANEL) actual_chanel = 0 ;
    chanels[actual_chanel] = signal_ppm ;
    previous_timer_rising = micros();
  }  
  
}








