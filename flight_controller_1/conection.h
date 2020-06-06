#ifndef conection_h
#define conection_h

//Define MOTOR LAYOUT
//  1  avant    2
//  3           4 
#define PIN_MOTOR_1 8
#define PIN_MOTOR_2 9
#define PIN_MOTOR_3 10
#define PIN_MOTOR_4 11

//Moteurs branchés tous les trois sur le port B, avec le moteur 1 sur le premier bit du 
// port B et le moteur 4 sur le 4eme pour une gestion plus simple de l'écriture sur les ports

//Rc receiver input , do not change this plz, may not work then
#define PIN_PPM_IT 2

//Potentiometer input conection 
#define PIN_PT_1 1
#define PIN_PT_2 2
#define PIN_PT_3 3

//Chanels conf
#define CHANEL_PITCH 1
#define CHANEL_ROLL 2
#define CHANEL_THROTTLE 3
#define CHANEL_YAW 4
#define CHANEL_SWITCH_1 5   //Switch 1 à deux position pour le control global des moteurs 
#define CHANEL_SWITCH_2 6   //Switch 2 à trois position
#define CHANEL_SWITCH_3 7   //Switch 3 à trois position 
#define CHANEL_SWITCH_4 8   //Switch 4 à deux position 

//LEDS d'état
#define STATE_LED 3
#define STATE_BAT_LED 4

#define ANALOG_KP A7
#define ANALOG_KD A6 



#endif
