//25 Juin 2019
//First version of the complementary filter

//Library to use the MPU 6050 using I2C
#include<Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
float X=0, Y=0;
unsigned long last_time_mpu = 0;
float delta_t_mpu = 0;

//That function get the values from the MPU and apllies a complementary filter to get better values more usable
void angle()
{
  //Initialazing varaibles  
  float AcX,AcY,AcZ,GyX,GyY,GyZ,AcTotal, Tmp;
  float AcXangle , AcYangle;
  //Staring the comunication with the MPU
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x3B);                                                    //Send the requested starting register
  Wire.endTransmission();                                              //End the transmission
  Wire.requestFrom(0x68,14);                                           //Request 14 bytes from the MPU-6050
  while(Wire.available() < 14);                                        //Wait until all the bytes are received
  //Stocking the values
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  //Computing values from acc to guess the angles 
  AcTotal = sqrt(AcX*AcX + AcZ*AcZ + AcY*AcY);
  AcXangle = asin(AcX/AcTotal) * 57.296 ;
  AcYangle = asin(AcY/AcTotal) * -57.296 ;
  //Possibility to adjust raw values in case of a static error
  //AcXangle += 10.5;
  //AcYangle +=  0.75;
  //Here we have our complementary filter
  //First we add the gyro values
  //We know that the value 131 means 1 degree per seconds (sensitive factor)
  GyX /= 131 ;
  GyY /= 131 ;
  GyZ /= 131 ;
  
  delta_t_mpu= (millis() - last_time_mpu)  ;
  X += GyX * delta_t_mpu /1000;
  Y += GyY * delta_t_mpu /1000;
  
  last_time_mpu = millis() ;

  X = X *0.998 + AcXangle * 0.002;
  Y = Y *0.998 + AcYangle * 0.002;

  Serial.print(X);
  Serial.print("    ");
  Serial.print(AcXangle);
  Serial.print("    ");
  Serial.println(GyX * delta_t_mpu /1000);

  
 
 
}

void setup(){
  //Set up the MPU
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);     
  Wire.endTransmission(true);
  Serial.begin(9600);

  //Configure the Gyro
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0);
  Wire.endTransmission();
  last_time_mpu = millis();  
  
}


void loop(){
  angle();
  
}
