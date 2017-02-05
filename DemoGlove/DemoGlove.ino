int incomingByte;
int i;
int led1=10;
int led2=11;
int motor=12;

void setup() {
  // initialize Serial communication:
  Serial.begin(115200);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(motor,OUTPUT);
}

void loop() {
  // see if there's incoming Serial data:
  if (Serial.available()) {
    // read the oldest byte in the Serial1 buffer:
    incomingByte = Serial.read();
    if (incomingByte == 'A') {
       digitalWrite(led1,HIGH);
       delay(50);
    }
    if (incomingByte == 'B') {
      digitalWrite(led2,HIGH);
    delay(50);
    }
    if (incomingByte == 'C') {
      for(i=0;i<5;i++)
    {
    digitalWrite(led1,HIGH);
    delay(200);
    digitalWrite(led1,LOW);
    delay(200);
    }
    //Blink LED1
    }
    if (incomingByte == 'D') {
      for(i=0;i<5;i++)
      {
      digitalWrite(led2,HIGH);
    delay(200);
    digitalWrite(led2,LOW);
    delay(200);
    }
    }
    if (incomingByte == 'E') {
      digitalWrite(motor, HIGH);
    }
    if (incomingByte == 'F') {
      digitalWrite(motor, LOW);
      delay(50);
    }
    if (incomingByte == 'G') {
     digitalWrite(led1,LOW);
    delay(50);
    digitalWrite(led2,LOW);
    delay(50);
    }
}
}

