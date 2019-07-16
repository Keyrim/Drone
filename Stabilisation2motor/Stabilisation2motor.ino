//This file is used to aply a filter to the raw data from the mpu 6050
//DataSheet of the mpu 
//https://store.invensense.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf
//Datasheet registre MPU 
//https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
//This code is made to stabilize something with one motor using the x axe of the mpu6050 
#include <Wire.h>
#include <Servo.h>
const int MPU=0x68;  // I2C address of the MPU-6050
const int frequence = 250; //Frequence of the loop in hz
const float max_total_vector = 1.2 ;
unsigned long loop_timer ; 
unsigned long start_timer_esc ;
//raw data
float AcX, AcY, AcZ, GyX=0, GyY=0, GyZ=0;
float X=0, Y=0;
//Pin ESC
#define ESC1 5
#define ESC2 7
Servo right_esc ;
Servo left_esc ;
//Signal ESC 
unsigned int signal_esc1 = 1000, signal_esc2 = 1000 ;

//regulations thngs
float consigne = 0 ;
const float kP = 1, kD = 1 , kI = 0.00;
float error, last_error = 0 ;
float p, i, d;
int global_power = 1100 ; 


void read_mpu()
{
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);       //Send the starting register (accelerometer)
    Wire.endTransmission();
    Wire.requestFrom(MPU, 6);
    while (Wire.available()< 6);
    AcX = Wire.read()<<8|Wire.read();
    AcY = Wire.read()<<8|Wire.read();
    AcZ = Wire.read()<<8|Wire.read();

    //Get the true raws values in g according to our setting
    AcZ /= 8192;
    AcX /= 8192;
    AcY /= 8192;
    
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission();
    Wire.requestFrom(MPU, 4);
    while(Wire.available()< 4);
    GyX = (Wire.read()<<8|Wire.read())/65.5;
    GyY = (Wire.read()<<8|Wire.read())/65.5;    

}

void setup()
{
    //Initialize the pin for the ESC
    left_esc.attach(ESC1);
    right_esc.attach(ESC2);

    // Wake up the mpu 
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission();

    //Set up the accelerometer
    //1g = 8192
    //+- 2g
    Wire.beginTransmission(MPU);
    Wire.write(0x1C);
    Wire.write(0x08);
    Wire.endTransmission();

    //Set up the gyroscope
    //1deg/s = 65.5 
    //+- 500
    Wire.beginTransmission(MPU);
    Wire.write(0x1B);
    Wire.write(0X08);
    Wire.endTransmission();    

    Serial.begin(115200);
    loop_timer = micros();
    
    left_esc.writeMicroseconds(1000);
    right_esc.writeMicroseconds(1000);
    delay(4000);
    
}

void loop()
{
    read_mpu();
    //Compute our raw values
    float total_vector = sqrt(AcX*AcX + AcY*AcY + AcZ*AcZ);    
    AcX = asin(AcX/total_vector)*57.32;
    AcY = asin(AcY/total_vector)*57.32;
    //Complementary filter now
    X += GyX / frequence ;
    if(total_vector<max_total_vector)X = X * 0.98 + AcY * 0.02 ;

    error = consigne - X ;
    p = error * kP ;
    d = (error - last_error) * kD ;
    i += error * kI ;
    signal_esc1 = p + i + d + global_power ;
    signal_esc2 = - p - i - d + global_power ;
    last_error = error ;
    left_esc.writeMicroseconds(signal_esc1);
    right_esc.writeMicroseconds(signal_esc2);

    //We regulate our frequence here
    while(micros()<loop_timer + 1000*(1/frequence));
    loop_timer = micros();
    Serial.println(X);

    

}