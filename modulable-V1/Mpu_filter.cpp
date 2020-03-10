#include "Mpu_filter.h"

Mpu_filter::Mpu_filter(){
    //Init function
}

void Mpu_filter::set_mpu(){
    // Wake up the mpu 
    Wire.begin();
    TWBR = 12;                                                                //Set the I2C clock speed to 400kHz.  
    Wire.beginTransmission(adress);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission();

    //Set up the accelerometer
    //1g = 8192
    //+- 4g     
    Wire.beginTransmission(adress);
    Wire.write(0x1C);
    Wire.write(0x08);
    Wire.endTransmission();

    //Set up the gyroscope
    //1deg/s = 65.5 
    //+- 500
    Wire.beginTransmission(adress);
    Wire.write(0x1B);
    Wire.write(0X08);
    Wire.endTransmission();
}

void Mpu_filter::update(bool complementary){
    
    Wire.beginTransmission(adress);
    Wire.write(0x3B);       //Send the starting register (accelerometer)
    Wire.endTransmission();
    Wire.requestFrom(adress, 6);
    while (Wire.available()< 6);
    acc_x = Wire.read()<<8|Wire.read();
    acc_y = Wire.read()<<8|Wire.read();
    acc_z = Wire.read()<<8|Wire.read();

    //Get the true raws values in g according to our setting
    acc_x /= 8192;
    acc_y /= 8192;
    acc_z /= 8192;


    
    Wire.beginTransmission(adress);
    Wire.write(0x43);
    Wire.endTransmission();
    Wire.requestFrom(adress, 6);

    while(Wire.available()< 6);
    gy_x = (Wire.read()<<8|Wire.read())/65.5;
    gy_y = (Wire.read()<<8|Wire.read())/65.5;  
    gy_z = (Wire.read()<<8|Wire.read())/65.5;  

    Z += (gy_z - gy_z_cal)/ FREQUENCE ;
    
    

    float total_vector = sqrt(acc_x*acc_x + acc_y*acc_y + acc_z*acc_z);     
    acc_x = -asin(acc_x/total_vector)*57.32; 
    acc_y = asin(acc_y/total_vector)*57.32; 
    
    
    if(complementary){   
        //Complementary filter
        Y += (gy_x - gy_x_cal) / FREQUENCE ;
        Y = Y * (1 - ALPHA) + (-acc_y_cal + acc_y) * ALPHA; 
        

        X += (gy_y - gy_y_cal)/ FREQUENCE ;
        X = X * (1 - ALPHA) + (-acc_x_cal + acc_x) * ALPHA;   
    }
    
    

}

void Mpu_filter::calibrate(int iteration){
    double x_sum = 0;
    double y_sum = 0;
    double gx_sum = 0;
    double gy_sum = 0;
    double gz_sum = 0;
    for(int i = 0; i < iteration; i++){
        update(false);
        x_sum += acc_x ;
        y_sum += acc_y ;
        gx_sum += gy_x ;
        gy_sum += gy_y ;
        gz_sum += gy_z ;
        delay(10);
    }
    acc_x_cal = x_sum / iteration ;
    acc_y_cal = y_sum / iteration ;
    gy_x_cal = gx_sum / iteration ;
    gy_y_cal = gy_sum / iteration ;
}
