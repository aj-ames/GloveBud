#include <Wire.h>
#include <ADXL345.h>


ADXL345 adxl; //variable adxl is an instance of the ADXL345 library

int x,y,z;  
//Constants:

const int flexPin1 = A0; //pin A0 to read analog input
const int flexPin2 = A1;
const int flexPin3 = A2;
const int flexPin4 = A4;
const int flexPin5 = A3;

//Variables:
int F1,F2,F3,F5,F4=0; //save analog value
 
 

void read()
{
  F1 = analogRead(flexPin1);         //Read and save analog value from potentiometer
  Serial.print(F1);                //Print value
  Serial.print("\t");
  delay(100);      //Small delay

  F2 = analogRead(flexPin2);         //Read and save analog value from potentiometer
  Serial.print(F2);               //Print value
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
  Serial.begin(115200);       //Begin Serial communication
  adxl.powerOn();
  //read();

}

void loop(){
  read();
  //while(F1>300 && F2>400 && F3>200 && F4<190 && F5>280)
  //{
  delay(100);
  //read();
  if(F1>300 && F2>400 && F3>180 && F4<190 && F5>280)//activation (relaxed palm)
  {
    delay(100);
  }
  else if(F1<300 && F2<400 && F3<180 && F4<190 && F5<280)//fist
  {
     Serial.print('F');
  }
  else if(F1<300 && F2>400 && F3<180 && F4<190 && F5<280 && x>150)//one holding up+add accelerometer reading
  {
    Serial.print('A');
    //switch LED1 On
  }
  else if(F1<300 && F2>400 && F3<180 && F4<190 && F5<280 && x<150)//one pointing +add accelerometer reading
  {
    Serial.print('C');
  }
  else if(F1<300 && F2>400 && F3>180 && F4<190 && F5<280 && x>150)//two holding up+add accelerometer reading
  {
    
    Serial.print('B');
    //switch LED2 On
  }
  else if(F1<300 && F2>400 && F3>180 && F4<190 && F5<280 && x<150)//two pointing up+add accelerometer reading
  {
    
    Serial.print('D');
    //blink LED2 faster
  }
  else if(F1<300 && F2>400 && F3<180 && F4<190 && F5>280 && x>150)//Metal
  {
    Serial.print('E');
    //switch motor on
  }
  else if(F1>300 && F2<400 && F3<180 && F4<190 && F5<280 && y<10)//thumbs down
  {
    
    Serial.print('G');
    //switch both LED off
  }
  Serial.println();
  delay(500);
  //}
  
  
}



