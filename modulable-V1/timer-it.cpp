#include "timer-it.h"

Timer_it::Timer_it(){

}

void Timer_it::init(){
    //Prescaler set at 8 
    //f_comparaison = (16 000 000 / (prescaler * f_cible))
    delay(100);
    //Setup interuptions 
    cli();//stop interrupts
    //set timer1 interrupt at 1Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    //It frequency is set to 5 hz  
    OCR1A =  3124;// = ( 16 000 000 / (prescaler * fre cible)) - 1
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    //  CS11 bits for 8 prescaler
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);        
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A); 
    sei();//allow interrupts
}