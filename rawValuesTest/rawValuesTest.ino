int flex1, flex2, flex3, flex4, flex5;
#define s0 15
#define s1 14
#define s2 13
#define mul A0

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {
  Serial.begin(115200);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(mul, INPUT);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  delay(100);
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop() {
  digitalWrite(s0,LOW);
  digitalWrite(s1,LOW);
  digitalWrite(s2,LOW);
  delay(10);
  flex1=analogRead(mul);
  delay(10);
  

  digitalWrite(s0,LOW);
  digitalWrite(s1,LOW);
  digitalWrite(s2,HIGH);
  delay(10);
  flex2=analogRead(mul);
  delay(10);

  digitalWrite(s0,LOW);
  digitalWrite(s1,HIGH);
  digitalWrite(s2,LOW);
  delay(10);
  flex3=analogRead(mul);
  delay(10);

  digitalWrite(s0,HIGH);
  digitalWrite(s1,HIGH);
  digitalWrite(s2,LOW);
  delay(10);
  flex4=analogRead(mul);
  delay(10);
  Serial.print("Flex1: "); Serial.print(flex1); Serial.print("  ");
  Serial.print("Flex2: "); Serial.print(flex2); Serial.print("  ");
  Serial.print("Flex3: "); Serial.print(flex3); Serial.print("  ");
  Serial.print("Flex4: "); Serial.print(flex4); Serial.print("  ");
  Serial.println(" ");
  delay(10);
  
  sensors_event_t event; 
  accel.getEvent(&event);
 
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(10);

  if(event.acceleration.z > 14) {
    Serial.println("Woohhooooo");
    delay(10);
    }
  
}
