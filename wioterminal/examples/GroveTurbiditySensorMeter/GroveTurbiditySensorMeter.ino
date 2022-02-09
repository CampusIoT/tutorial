
// #define ENABLE_ANALOG 1

#ifdef ENABLE_ANALOG

void setup() {
 
  Serial.begin(9600); //Baud rate: 9600
}
 
void loop() {
  int sensorValue = analogRead(A0);// read the input on analog pin 0:
  float voltage = sensorValue * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.println(voltage); // print out the value you read:
  delay(500);
}



int ledPin = 3;               

int sensor_in = 1;                 // Turbidity sensor on Digital Pin 2

 

void setup(){

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);      // Set ledPin as output mode

  pinMode(sensor_in, INPUT);       //Set Turbidity sensor pin to input mode

}

#else

int ledPin = 3;               
int sensor_in = 2;                 // Turbidity sensor on Digital Pin 2
 
void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);      // Set ledPin as output mode
  pinMode(sensor_in, INPUT);       //Set Turbidity sensor pin to input mode
}
 
void loop(){
   int sensorValue = digitalRead(sensor_in);
   Serial.println(sensorValue);
   if(sensorValue==HIGH){       //Read sensor signal 
        digitalWrite(ledPin, HIGH);   // if sensor is LOW, then turn on
     }else{
        digitalWrite(ledPin, LOW);    // if sensor is HIGH, then turn off the led
     }
    delay(500);
}

#endif
