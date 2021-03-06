 #include "conection.h"
#include "Mpu_filter.h"
#include "timer-it.h"
#include "Pid.h"
#include "states.h"

unsigned int check_esc_order(unsigned int signal) {
  signal = max(signal, 1000);
  signal = min(signal, 2000);
  return signal ;
}
//Max angle consigne
#define ANGLE_MAX_CONSIGNE 60
#define ROTATION_MAX_YAW 400

//PID settings
//Pour le pid sur le yaw je bosse sur la vitesse angulaire et non l'angle 
//Pid actuels : manque peut être très léger de kd mais assez clean comme ça 
#define kP_roll 2.94
#define kP_pitch 2.94
#define kP_yaw 4

#define kI_roll 0
#define kI_pitch 0
#define kI_yaw 0
    
#define kD_roll 0.27
#define kD_pitch 0.27 
#define kD_yaw 0

#define MAX_PID 200

Mpu_filter mpu ;
Pid roll_pid ;
Pid pitch_pid ;
Pid yaw_pid ;
Timer_it timer ;

//Consignes
float consigne_roll = 0 ;
float consigne_pitch = 0 ;
float consigne_yaw = 0 ;

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
#define NUMBER_OF_STATES 6
#define sequence1 0b00011000
#define sequence2 0b00011100
#define sequence3 0b00011010
#define sequence4 0b00010000
#define sequence5 0b00011110
#define sequence6 0b00000000

byte sequences [NUMBER_OF_STATES] = {sequence1, sequence2, sequence3, sequence4, sequence5, sequence6};
byte sequence_evolution_counter = 0 ;

byte state = STATE_INIT_MPU ;    //We start with the mpu init state
byte state_bat = STATE_BAT_LOW ;

float v_bat = 12 ;
// Le jeton de parole détermine quelle info on envoit de manière à ne pas envoyer toutes les info tous le temps
// Actuelement on a 25 jetons au plus donc chaque info est envoyé à 250Hz / 25 = 10 Hz
// 1  Batt
// 2 mpu.X
// 3 mpu.Y 
// 4 moteur 1
// 5        2
// 5        3
// 6        4
// . . .
// 25       .
#define MAX_JETON_PAROLE 10
byte jeton_parole = 0 ;

///////////////////////////////////////////// SETUP¨////////////////////////////////////////////////////////////////////////////


void setup() {
  
  //Initialize the timer
  //We must do it first as it is requiered for the state led
  timer.init();

  //Set the right output on the pin for states led
  pinMode(STATE_LED, OUTPUT);
  pinMode(STATE_BAT_LED, OUTPUT);

  //Begin Serial Comunication
  Serial.begin(115200);
  Serial.println("Program begins");

  //Init & calibrate the mpu
  mpu.set_mpu();
  delay(100);
  state = STATE_CALIB_MPU ;
  mpu.calibrate(200);

  //Set our pids coef
  roll_pid.set_coef(kP_roll, kI_roll, kD_roll);
  pitch_pid.set_coef(kP_pitch, kI_pitch, kD_pitch);
  yaw_pid.set_coef(kP_yaw, kI_yaw, kD_yaw);
  
  roll_pid.max_output = MAX_PID ;
  pitch_pid.max_output = MAX_PID ;
  yaw_pid.max_output = MAX_PID ;

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
  byte led_bat = sequences[state_bat];
  led_state = led_state >> (5 - sequence_evolution_counter) ;
  led_bat = led_bat >> (5 - sequence_evolution_counter);
  led_state &= 0b00000001 ;
  led_bat &= 0b00000001 ;
  sequence_evolution_counter ++ ;
  if (sequence_evolution_counter == 5)
    sequence_evolution_counter = 0 ;
  digitalWrite(STATE_LED, led_state);
  digitalWrite(STATE_BAT_LED, !led_bat);

}

void loop() {


  //  ====================== FIN DU SIGNAL DES ESC ===================================
  //  ====================== deux secondes dispo ~ donc lecture mpu et compilation des sorties des moteurs

  //Read v_bat
  v_bat = analogRead(A0);
  v_bat = (v_bat * 5) / 1023 ;  //Passage bit vers volt
  v_bat *= 2.744 ;              //Compense le pont diviseur de tension
  if(v_bat > 12)
    state_bat = STATE_BAT_HIGH ;
  else if(v_bat > 11)
    state_bat = STATE_BAT_MIDLLE_HIGH ;
  else if(v_bat > 10 )
    state_bat = STATE_BAT_MIDLLE_LOW ;
  else 
    state_bat = STATE_BAT_LOW ;

  //update_coefs();
  //Update MPU  
  mpu.update(true); 
  
  //consigne are given in degrees
  //YAW
  consigne_yaw = map(chanels[CHANEL_YAW], 1050, 1950, -ROTATION_MAX_YAW, ROTATION_MAX_YAW)  ;
  //PITCH
  consigne_pitch = map(chanels[CHANEL_PITCH], 1050, 1950, -ANGLE_MAX_CONSIGNE, ANGLE_MAX_CONSIGNE)  ;
  //ROLL
  consigne_roll = map(chanels[CHANEL_ROLL], 1050, 1950, -ANGLE_MAX_CONSIGNE, ANGLE_MAX_CONSIGNE) ; 
  if (state == STATE_MOTOR_DOWN) {
    for (byte m = 0; m < 4; m++)
      esc_pulses[m] = 1000 ;

  }
  //state == STATE_FLYING  && chanels[CHANEL_THROTTLE] > 1050
  else if (state == STATE_FLYING  && chanels[CHANEL_THROTTLE] > 1100) {
    //Pid calculation
    unsigned int throttle = chanels[CHANEL_THROTTLE] ;
    float pitch_comp = pitch_pid.compute_pid(consigne_pitch - mpu.Y);
    float roll_comp = roll_pid.compute_pid(consigne_roll - mpu.X);
    float yaw_comp = yaw_pid.compute_pid(consigne_yaw - mpu.gy_z);
    esc_pulses[0] = check_esc_order(-pitch_comp - roll_comp + yaw_comp + throttle) ;
    esc_pulses[1] = check_esc_order(pitch_comp - roll_comp - yaw_comp + throttle);
    esc_pulses[2] = check_esc_order(-pitch_comp + roll_comp - yaw_comp + throttle) ;
    esc_pulses[3] = check_esc_order(pitch_comp + roll_comp + yaw_comp + throttle) ;


  }
  else {
    for (byte m = 0; m < 4; m++)
      esc_pulses[m] = 1000 ;

  }

  //Pour passer en mode de vol et se maintenir
  //La consigne moteur doit être à zéro
  //Le switch 1 > 1600
  if ((chanels[CHANEL_SWITCH_1] > 1600)   &&   (chanels[CHANEL_THROTTLE] < 1100 || state == STATE_FLYING))
    state = STATE_FLYING ;
  //Sinon
  else
    state = STATE_MOTOR_DOWN ;

  //This regulates the rate of the main loop at 250 Hz
  while (micros() < loop_timer + 1000000 / frequence);
  loop_timer = micros();
  //            ----------------------------------------------------- début signal ESC ------------------------------------------------
  PORTB |= 0b00001111 ; //Escs pulses start, notice that we set our outputs high at "loop_timer" moment
  //On a une ms et PAS PLUS pour envoyer les info que l'on veut sur la liason radio
  
  String message = "" ;
  char separation = ' ';
  switch(jeton_parole){
    case 0 :
      Serial.print((String)v_bat + separation);
      break;
    case 1 :
      Serial.print((String)mpu.X + separation);
      break ;
    case 2 :
      Serial.print((String)mpu.Y + separation);
      break ;
    case 3 :
      Serial.print((String)analogRead(A7) + separation);
      break ;
    case 4 :
      Serial.print((String)analogRead(A6) + separation);
      break ;
    case 5 :
      Serial.print((String)analogRead(A5) + separation);
      break ;
    case 6 :
      Serial.print((String)chanels[4] + separation);
      break ;
    case 7 :
      Serial.print((String)state);
      break ;
    case MAX_JETON_PAROLE - 1 :
      Serial.println();
    default :
      break ;
  }

  //Update jeton parole value
  jeton_parole ++ ;
  if(jeton_parole >= MAX_JETON_PAROLE)
    if(chanels[CHANEL_SWITCH_4 ] < 1500 )
      jeton_parole = 0 ;
    else 
      jeton_parole = MAX_JETON_PAROLE ;

      
  //Check if it is the time to shut down our esc signal ----------------------------------------------------------------------
  while (PORTB != (PORTB & 0b11110000)) {
    time_esc = micros() ;
    for (byte m = 0; m < 4; m++) {
      if (time_esc - loop_timer >= esc_pulses[m] ) {
        PORTB = PORTB & ~(1 << m) ;
      }
    }
  }
}

//This function is called when the pin 2 state changes
void rising()
{
  unsigned int signal_ppm = micros() - previous_timer_rising ;
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

void update_coefs(void){
  float kp = (float)map(analogRead(ANALOG_KP), 0, 1023, 6000, 0) / 1000.0;
  float kd = (float)map(analogRead(ANALOG_KD), 0, 1023, 2000, 0) / 1000.0;
  Serial.println(kp);
  Serial.println(kd);
  roll_pid.set_coef(kp, 0, kd);
  pitch_pid.set_coef(kp, 0, kd);
}
