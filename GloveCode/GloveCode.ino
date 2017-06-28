#include<ESP8266WiFi.h>
#include<PubSubClient.h>

WiFiClient espClient;
PubSubClient myClient(espClient);

const char* mqtt_server = "192.168.43.95";
const char* ssid = "Astr1x";
const char* pass = "astr1x2096";
String clientID = "ESP8266Glove";
const int port = 1883;

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include<Adafruit_NeoPixel.h>


#define s0 15
#define s1 14
#define s2 13
#define mul A0
int flex1, flex2, flex3, flex4, flex5;
double x,y,z;

boolean f1=false,f2=false,f3=false,f4=false,f5=false;
boolean cmdExecuted = false;
boolean cmdInput = false;
boolean cmdCancel = false;
String cmd;

long startTime;

String msg;
char message[100];


/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

#define rgb 12
String hex;

String hexa[16]={"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"};
int convertor[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(10, rgb, NEO_GRB+NEO_KHZ800);
uint32_t red = pixels.Color(255,0,0);
uint32_t green = pixels.Color(0,255,0);
uint32_t blue = pixels.Color(0,0,255);
uint32_t white = pixels.Color(255,255,255);
uint32_t purple = pixels.Color(139,0,139);
uint32_t black = pixels.Color(0,0,0);


void redShow() {
  for(int i=0;i<10;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, red); // Moderately bright green color.
  }
  pixels.show();
}

void greenShow() {
  for(int i=0;i<10;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, green); // Moderately bright green color.
    pixels.show();
  }
}

void blueShow() {
  for(int i=0;i<10;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, blue); // Moderately bright green color.
    pixels.show();
  }
}


void whiteShow() {
  for(int i=0;i<10;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, white); // Moderately bright green color.
    pixels.show();
  }
}

void purpleShow() {
  for(int i=0;i<10;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, purple); // Moderately bright green color.
    pixels.show();
  }
}

void blackShow() {
  for(int i=0;i<10;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, black); // Moderately bright green color.
    pixels.show();
  }
}

void rawValues() {
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

  x = event.acceleration.x;
  y = event.acceleration.y;
  z = event.acceleration.z;
 
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(10);

  if(flex1 > 540)
    f1 = false;
  else if(flex1 < 500)
    f1 = true;

  if(flex2 > 520)
    f2 = false;
  else if(flex2 < 430)
    f2 = true;
    
  if(flex3 > 540)
    f3 = false;
  else if(flex3 < 470)
    f3 = true;
    
  if(flex4 > 540)
    f4 = false;
  else if(flex4 < 470)
    f4 = true;
}

void gestures() {
  if(f1 == true && f2 == false && f3 == true && f4 == true && x > 0.0) {
    //Turn on Light 1
    myClient.publish("Glove","RL1O:");
    Serial.println("RL10:");
    greenShow();
    delay(2000);
    cmdExecuted = true;
    blueShow();
    return;
  }
  else if(f1 == true && f2 == false && f3 == true && f4 == true && x < 0.0 && y < 0.0) {
    //Turn off Light 1
    myClient.publish("Glove","RL1F:");
    Serial.println("Light 1 OFF");
    greenShow();
    delay(2000);
    cmdExecuted = true;
    blueShow();
    return;
  }
  else if(f1 == true && f2 == false && f3 == false && f4 == true && x > 0.0) {
    //Turn on Light 2
    myClient.publish("Glove","RL2O:");
    Serial.println("Light 2 ON");
    greenShow();
    delay(2000);
    cmdExecuted = true;
    blueShow();
    return;
  }
  else if(f1 == true && f2 == false && f3 == false && f4 == true && x < 0.0 && y < 0.0) {
    //Turn off Light 2
    myClient.publish("Glove","RL2F:");
    Serial.println("Light 2 OFF");
    greenShow();
    delay(2000);
    cmdExecuted = true;
    blueShow();
    return;
  }
  else if(f1 == false && f2 == false && f3 == false && f4 == true && x > 0.0) {
    //Turn on Fan
    myClient.publish("Glove","FT:");
    Serial.println("Fan ON");
    greenShow();
    delay(2000);
    cmdExecuted = true;
    blueShow();
    return;
  }
  else if(f1 == false && f2 == false && f3 == false && f4 == true && x < 0.0 && y < 0.0) {
    //Turn off Fan
    myClient.publish("Glove","FF:");
    Serial.println("Fan OFF");
    greenShow();
    delay(2000);
    cmdExecuted = true;
    blueShow();
    return;
  }
  else if(f1 == false && f2 == true && f3 == true && f4 == true && x > 0.0) {
    //Turn Disco ON
    myClient.publish("Glove","DT:");
    Serial.println("Disco ON");
    greenShow();
    delay(2000);
    cmdExecuted = true;
    blueShow();
    return;
  }
  else if(f1 == false && f2 == true && f3 == true && f4 == true && x < 0.0) {
    //Turn Disco OFF
    myClient.publish("Glove","DF:");
    Serial.println("Disco OFF");
    greenShow();
    delay(2000);
    cmdExecuted = true;
    blueShow();
    return;
  }
  else if(z > 13.0) {
    //Turn Everything OFF
    myClient.publish("Glove","X:");
    Serial.println("TURNED OFF");
    whiteShow();
    delay(2000);
    cmdExecuted = true;
    blueShow();
    return;
  }
  else
    cmdCancel = true;
}


void setup() {
  Serial.begin(115200);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(mul, INPUT);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  delay(100);
  pixels.begin();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  myClient.setServer(mqtt_server,port);

  blueShow();
  
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
}


void reconnect() {
  if(myClient.connect(clientID.c_str())) {
    Serial.println("Connected");
    Serial.println(Serial.read());
  }
  else {
    Serial.println("Failed Reconnection");
    Serial.println(myClient.state());
  }
}

void loop() {
  while(!myClient.connected()) {
    Serial.println("Attempting MQTT Connection");
    if(!myClient.connected()) 
      reconnect();
  }
  myClient.loop();
  rawValues();
  if(f1 == true && f2 == true && f3 == true && f4 == true && x < 0.0 && y < 0.0 && myClient.connected()) {
    purpleShow();
    cmdInput= true;
    startTime = millis();
    while(millis() - startTime < 5000 && cmdExecuted!=true) {
      rawValues();
      gestures();
    }
    if(cmdCancel == true && cmdExecuted == false) {
      cmdCancel = false;
      for(int i = 0; i < 5; i++) {
        redShow();
        delay(200);
        blackShow();
        delay(100);
      }
      blueShow();
    }
    cmdExecuted = false;
  }
}
