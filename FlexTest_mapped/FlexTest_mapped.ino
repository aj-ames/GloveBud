//Constants:
const int flexPin1 = A0; //pin A0 to read analog input
const int flexPin2 = A1; //pin A1 to read analog input
const int flexPin3 = A2; //pin A0 to read analog input
const int flexPin4 = A3; //pin A0 to read analog input
const int flexPin5 = A4; //pin A0 to read analog input

//Variables:
int F1,F2,F3,F4,F5; //save analog value


void setup(){
  
  pinMode(ledPin, OUTPUT);  //Set pin 3 as 'output'
  Serial.begin(9600);       //Begin serial communication
  }

void loop(){
  Serial.println();
  
  F1 = analogRead(flexPin1);         //Read and save analog value from potentiometer
  Serial.print(F1);                //Print value
  Serial.print("\t");
  F1 = map(F1, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
  Serial.print(F1); //mapped value
  delay(100);      //Small delay

  F2 = analogRead(flexPin2);         //Read and save analog value from potentiometer
  Serial.print(F2);                //Print value
  Serial.print("\t");
  F2 = map(F2, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
  Serial.print(F2); //mapped value
  delay(100);      //Small delay

  F3 = analogRead(flexPin3);         //Read and save analog value from potentiometer
  Serial.print(F3);                //Print value
  Serial.print("\t");
  F3 = map(F3, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
  Serial.print(F3); //mapped value
  delay(100);      //Small delay

  F4 = analogRead(flexPin4);         //Read and save analog value from potentiometer
  Serial.print(F4);                //Print value
  Serial.print("\t");
  F4 = map(F4, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
  Serial.print(F4); //mapped value
  delay(100);      //Small delay

  F5 = analogRead(flexPin5);         //Read and save analog value from potentiometer
  Serial.print(F5);                //Print value
  Serial.print("\t");
  F5 = map(F5, 700, 900, 0, 255);//Map value 0-1023 to 0-255 (PWM)
  Serial.print(F1); //mapped value
  delay(100);      //Small delay
}
