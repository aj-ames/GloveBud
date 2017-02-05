#include <Wire.h>
#include <ADXL345.h>

ADXL345 adxl; //variable adxl is an instance of the ADXL345 library

int x,y,z;  

//Constants:
const int flexPin1 = A0; //pin A0 to read analog input
const int flexPin2 = A1;
const int flexPin3 = A2;
const int flexPin4 = A3;
const int flexPin5 = A6;

//Variables F1,F2,F3,F5,F4; //save analog value
int F1,F2,F3,F4,F5;

void read()
{
  F1 = analogRead(flexPin1);         //Read and save analog value from potentiometer'
  Serial.print(F1);                //Print value
  Serial.print("\t");
  delay(100);      //Small delay

  F2 = analogRead(flexPin2);         //Read and save analog value from potentiometer
  Serial.print(F2);               //Print 
  Serial.print("\t");
  delay(100);                          //Small delay

  F3 = analogRead(flexPin3);         //Read and save analog value from potentiometer
  Serial.print(F3);               //Print value
  Serial.print("\t");
  delay(100);                          //Small delay

  F4 = analogRead(flexPin4);         //Read and save analog value from potentiometer
  Serial.print(F4);               //Print value
  Serial.print("\t");
  delay(100);                          //Small delay

  F5 = analogRead(flexPin5);         //Read and save analog value from potentiometer
  Serial.print(F5);               //Print value
  Serial.print("\t");
  delay(100);                          //Small delay
  
  adxl.readAccel(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z

   // print out values:
 
  Serial.print("x: "); Serial.println(x);    // raw data without offset
  Serial.print(" y: "); Serial.println(y);     // raw data without offset
  Serial.print(" z: "); Serial.println(z);     // raw data without offset
  Serial.println(); 
}

void setup(){
  Serial.begin(9600);       //Begin Serial communication
  adxl.powerOn();
}

void loop()
{
  read();
  if(F1>150)
    Serial.print('H');
  else
    Serial.print('L');

    delay(100);

    if(F2>200)
    Serial.print('H');
  else
    Serial.print('L');

    delay(100);

    if(F3>100)
    Serial.print('H');
  else
    Serial.print('L');

    delay(100);

    if(F4>100)
    Serial.print('H');
  else
    Serial.print('L');

    delay(100);

    if(F5>140)
    Serial.print('H');
  else
    Serial.print('L');

     delay(100);

    if(x>0)
    Serial.print('P');
  else
    Serial.print('N');

     delay(100);

    if(y>0)
    Serial.print('P');
  else
    Serial.print('N');

     delay(100);

    if(z>0)
    Serial.print('P');
  else
    Serial.print('N');
}



