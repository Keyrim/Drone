#ifndef Mpu_filter_h
#define Mpu_filter_h

#include <Arduino.h>
#include <Wire.h>
#include <Math.h>



//#define MPU_I2C 0x68
#define FREQUENCE 250 
#define ALPHA 0.001



class Mpu_filter
{
    private:
        //Nothing private, we are a bit comunist here 

        

    public:
        //Init function
        Mpu_filter();
        void set_mpu();
        void update(bool complementary);
        void calibrate(int iteration);
        
        int adress = 0x68 ;

        //Values with complementary filter
        float X = 0,Y = 0, Z = 0;
        //Raw gy values
        float gy_x, gy_y, gy_z;
        //Raw acc values
        float acc_x, acc_y, acc_z ;
        
        //Calibration acc values
        float acc_x_cal = 0, acc_y_cal = 0 ;
        float gy_x_cal = 0, gy_y_cal = 0, gy_z_cal = 0 ;
};

#endif
