//Serial part
long value;
long id ;
String data = "";
bool read_serial()
{
    while (Serial.available())
    {
        char chr = Serial.read();
        if(chr == '\n')
        {
            value = data.toInt();
            id = value & 15;
            value -= id ;
            value = value >> 4 ;
            data = "";
            return true ;
        }
        else 
        {
            data += chr ;
            return false ;
        }
    }
    
}

void write_serial(long sId, long sValue)
{
    sValue = sValue <<4 ;
    sValue += sId ;
    Serial.pritn(sValue):
    Serial.print("\n");
}

//Loop regualtion part
int frequence = 250 ; //(Hz)
unsigned long previoous_loop_timer =0 ;

//Motor part
#include<Servo.h>
#define pin_moteur 7
Servo moteur;
int global_power = 1100 ; 

//MPU6050 part
#include<Wire.h>
const int MPU=0x68;  // I2C address of the MPU-6050
#define moyenne_iteration 3
//raw data
float AcX, AcY, AcZ, GyX=0, GyY=0, GyZ=0;
float X=0, Y=0;

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



//Partie gestion global
bool affichage_X = true;
bool moyenne = false ;
bool affichage_period_loop = false ;





void setup()
{
    //Phase d'Initalisation de la liaison série ainsi que des moteurs
    moteur.attach(pin_moteur);
    Serial.begin(9600);
    Serial.println("-Debut du programme-");
    Serial.print("-Initalisation moteur ");$
    Servo.writeMicroseconds(1000);
    for(int i =0; i <30; i++)Serial.print(".");
    Serial.println(".");
    Serial.println("Les moteus sont prets-");
    //Initalisation du MPU
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
    Serial.println("-Mpu initialisé-");



}
void loop()
{
    //Si des données sont present dans le tampon
    if(Serial.available)
    {
        //Si des données sont utilisables
        if(read_serial())
        {
            if(id == 0)
            {
                //Gestion des boolean globales
                if     (value == 0)affichage_X = true ;
                else if(value == 1)affichage_X = false ;
                else if(value == 2)moyenne = true ;
                else if(value == 3)moyenne = false ;
                else if(value == 4)affichage_period_loop = true ;
                else if(value == 5)affichage_period_loop = false ;

            }
            //Permet de controller lapuissance du des moteurs, les faires tourner ou non
            else if(id == 1)global_power = value ;

        }
    }
    //On afficher ou pas la periode de la derniere boucle
    if(affichage_period_loop)write_serial(1, micros()-previoous_loop_timer);

    //On garde une periode constante sur la lecture du MPU
    while(micros()<previoous_loop_timer + (1000000/frequence);

    previoous_loop_timer = micros();
    if(moyenne)
    {
        AcX = 0;
        AcY = 0;
        AcZ = 0 ;
        for(int i = 0; i < moyenne_iteration, i++)
        {
            Wire.beginTransmission(MPU);
            Wire.write(0x3B);       //Send the starting register (accelerometer)
            Wire.endTransmission();
            Wire.requestFrom(MPU, 6);
            while (Wire.available()< 6);
            AcX += Wire.read()<<8|Wire.read();
            AcY += Wire.read()<<8|Wire.read();
            AcZ += Wire.read()<<8|Wire.read();           
        }
        //Get the true raws values in g according to our setting
        AcZ /= 8192;
        AcX /= 8192;
        AcY /= 8192;
        //On oublie pas de faire la moyenne sinon ca serait pas de chance^^
        AcZ /= moyenne_iteration;
        AcX /= moyenne_iteration;
        AcY /= moyenne_iteration;
    }
    else 
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
    }
    float total_vector = sqrt(AcX*AcX + AcY*AcY + AcZ*AcZ);    
    X = asin(AcY/total_vector)*57.32;


    if (affichage_X)write_serial(0, (long)((90+X)*1000));


    


}