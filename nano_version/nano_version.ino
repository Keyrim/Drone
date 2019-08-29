//Read PPM signal 


void setup()
{
    //      PPM signal setup
    //Interuption
    pinMdode(2, INPUT);


    //Alimentation
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);

    //Serial part
    Serial.begin(115200):
}

void loop()
{
    Serial.prinln(digitalRead(2));
}