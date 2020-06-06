#ifndef timer_it_h
#define timer_it_h
#include <Arduino.h>
#define IT_FUNCTION ISR(TIMER1_COMPA_vect)


//Atm it is a simple 5hz timer 

class Timer_it {
    public:
    //public functions
    Timer_it();
    void init();
    //public variables

    private:
    //private functions

    //private variables

};

#endif 