//25 Juin 2019
//First version of the complementary filter

//Library to use the MPU 6050 using I2C
#include<Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
float X=0, Y=0;
unsigned long last_time_mpu = 0;
float delta_t_mpu = 0;
float data;
float dmax= 0 ;

//That function get the values from the MPU and apllies a complementary filter to get better values more usable
void angle()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3F);
  Wire.endTransmission();
  Wire.requestFrom(MPU, 2);
  data = Wire.read() <<8|Wire.read();
  data /= 16384 ;
  if (data  >= dmax) dmax = data;
  Serial.println(dmax);
}

void setup(){
  //Set up the MPU
  Wire.begin();

  //Configure the ACC
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);     
  Wire.endTransmission(true);
  Serial.begin(250000);

  //Configure the Gyro
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0);
  Wire.endTransmission();

  
  
}


void loop(){

  
  angle();
  delay(50);
  
}
