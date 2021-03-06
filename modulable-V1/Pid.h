#ifndef Pid_h
#define Pid_h
#include<Arduino.h>

//The frequency of the pid 
#define FREQUENCY 250 


class Pid
{
    
    private:
    //Functions 
        //
    //Variables    
        //ouput of the pid 
        float pid_output ;
        //Coeficients
        float kP = 0, kD = 0, kI = 0 ;


    public:
    //Functions
        Pid();
        //Set our Coeficients
        void set_coef(float p, float i, float d);
        float compute_pid(float error);
    //Variables     
        //Errors      
        float error, previous_error = 0 ; 
        //compensation values
        float p_out, i_out, d_out ;        
        //Max outout
        float max_output  ; 

};


#endif
