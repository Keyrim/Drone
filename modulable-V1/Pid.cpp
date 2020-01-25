#include "Pid.h"

Pid::Pid(){
    
}

//Set the coef for the pid
void Pid::set_coef(float p, float i, float d){
    //The proportional error isssss the proportional error gg all 
    kP = p;
    //We take care of the FREQUENCY cuz it ibviously impact our integration  
    kI = i / FREQUENCY;
    //We take care of the FREQUENCY cuz it ibviously impact our derivate 
    kD = d * FREQUENCY;
}

//Take the system error as an input and output it as an 
float Pid::compute_pid(float error){
    p_out = kP * error ;
    i_out += kI * error ;
    d_out = (error - previous_error) * kD ;
    pid_output = p_out + i_out + d_out ;
    pid_output = min(max_output, pid_output);
    pid_output = max(-max_output, pid_output);
    previous_error = error;
    return pid_output;
}