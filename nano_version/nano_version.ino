//Conection :
//MPU Sda : A4
//MPU Scl : A5
//PPM input : D2
//Motor 1 PWM : D9
//Motor 2 PWM : D10
//Motor 3 PWM : D11
//Motor 4 PWM : D12


#include <Wire.h>
#include <Servo.h>
const int MPU=0x68;  // I2C address of the MPU-6050

//Read PPM signal
const byte number_of_chanel = 11 ;
byte actual_chanel = 0 ;
unsigned long previous_timer_rising = 0 ;
unsigned int  chanels[number_of_chanel] ;

//Constante compensation (PID coefs)
const float kp_roll = 1.4, kp_pitch = 1.4, kp_yaw = 0 ;
const float kd_roll = 0.0, kd_pitch = 0.0 ;
const float ki_roll = 0.0, ki_pitch = 0.0 ;
int compensation_max = 200;

//Error variables
float roll_error, pitch_error, yaw_error ;
float roll_previous_error = 0, pitch_previous_error=0;
float roll_compens, pitch_compens, yaw_compens;

//Rc orders 
const int inclination_max = 45 ; //(degrees)
const int max_rotation_rate = 100 ; //(degrees per second for the yax axis control)
float roll_order = 0, pitch_order = 0, yaw_order ;



//Check for the compensation and motor orders
float check_compensation(float comp)
{
  if(comp < -compensation_max)return -compensation_max ;
  else if(comp > compensation_max)return compensation_max ;
  else return comp ;
}
int check_motor_order(int order)
{
  if(order < 1000)return 1000 ;
  else if(order > 2000)return 2000 ;
  else return order ;
}

//Motor Instanciation
Servo moteur1 ;
Servo moteur2 ;
Servo moteur3 ;
Servo moteur4 ;
unsigned int global_power = 1000;


//timer things
unsigned long loop_timer ; 
unsigned long start_timer_esc ;
const int frequence = 250; //Frequence of the loop in hz
//raw data
float AcX, AcY, AcZ, GyX=0, GyY=0, GyZ=0;
float X=0, Y=0;

//Global , we know in witch mode the drone is flying 
//0, motors off 
//1, mode manuel
byte global = 0 ;

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
    Wire.requestFrom(MPU, 6);

    while(Wire.available()< 6);
    GyX = (Wire.read()<<8|Wire.read())/65.5;
    GyY = (Wire.read()<<8|Wire.read())/65.5;  
    GyZ = (Wire.read()<<8|Wire.read())/65.5;  

}



void setup()
{
  //Motor assignement
  moteur1.attach(9);
  moteur2.attach(10);
  moteur3.attach(11);
  moteur4.attach(12);
  
  // Wake up the mpu 
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();

  //Set up the accelerometer
  //1g = 8192
  //+- 4g
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
  
  //      PPM signal setup
  attachInterrupt(digitalPinToInterrupt(2), rising, RISING);

  //Serial part
  Serial.begin(115200);

  //Start the timer for the PPM Signal
  previous_timer_rising = micros();
}

void loop()
{
    //Here we determine in wich fly mode we are using signals from the rc transmiter
    if(chanels[8]<1500)global = 0 ;
    else if(chanels[8]>1500)global = 1 ;

    if(global==0)
    {
      //Flying mode where motors are set to 0
        moteur1.writeMicroseconds(1000);
        moteur2.writeMicroseconds(1000);
        moteur3.writeMicroseconds(1000);
        moteur4.writeMicroseconds(1000);
    }
    else if(global == 1)
    {
        //Standard flying mode 
        read_mpu();
        //Compute our raw values
        float total_vector = sqrt(AcX*AcX + AcY*AcY + AcZ*AcZ);    
        AcX = -asin(AcX/total_vector)*57.32; 
        AcY = asin(AcY/total_vector)*57.32;
        
        //Complementary filter
        X += GyX / frequence ; 
        X = X * 0.996 + AcY * 0.004 ;
        Y += GyY / frequence ;
        Y = Y * 0.996 + AcX * 0.004;

        //Rc setpoint calculation
        global_power = chanels[3];
        roll_order = map(chanels[1], 1000, 2000, -inclination_max, inclination_max);
        pitch_order = map(chanels[2], 1000, 2000, -inclination_max, inclination_max);
        yaw_order = map(chanels[4], 1000, 2000, -max_rotation_rate,  max_rotation_rate);

        //error calculation
        roll_error = roll_order - X ;
        pitch_error = pitch_order + Y ;
        yaw_error = yaw_order - GyZ ;
        //Proportional
        roll_compens = roll_error * kp_roll ;
        pitch_compens = pitch_error * kp_pitch ;
        yaw_compens = yaw_compens * kp_yaw ;
        //Derivate (we compute the derivate and then we add it to our compensation)
        roll_compens += (roll_error-roll_previous_error)*kd_roll;
        pitch_compens += (pitch_error - pitch_previous_error)*kd_pitch;
        
        //Update "previous" values
        roll_previous_error = roll_error ;
        pitch_previous_error = pitch_error;    
        
        //Motors are told what to do
        moteur1.writeMicroseconds(check_motor_order(global_power + roll_compens + pitch_compens ));
        moteur2.writeMicroseconds(check_motor_order(global_power - roll_compens + pitch_compens ));
        moteur3.writeMicroseconds(check_motor_order(global_power - roll_compens - pitch_compens ));
        moteur4.writeMicroseconds(check_motor_order(global_power + roll_compens - pitch_compens ));
    }
    else
    {
        moteur1.writeMicroseconds(1000);
        moteur2.writeMicroseconds(1000);
        moteur3.writeMicroseconds(1000);
        moteur4.writeMicroseconds(1000);
    }

    

    //We regulate our frequence here
    //Need a constant frequence to compute the gyroscope angle
    while(micros()<loop_timer + 1000000/frequence);
    loop_timer = micros();
  
}


//This function is called when the pin 2 state changes
void rising()
{
  unsigned int signal_ppm = micros()-previous_timer_rising ;
  if (signal_ppm > 3000) 
  {
    actual_chanel = 0 ;
    previous_timer_rising = micros();
    chanels[actual_chanel] = signal_ppm ;
  }  

  else 
  {
    actual_chanel ++;
    if (actual_chanel == number_of_chanel) actual_chanel = 0 ;
    chanels[actual_chanel] = signal_ppm ;
    previous_timer_rising = micros();
  }  
  
}