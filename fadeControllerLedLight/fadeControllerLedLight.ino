// These constants won't change.  They're used to give names
// to the pins used:
int potPin = A0;          // set input pin for the POT
int fadepotPin = A1;      // set input pin for the fadePOT
int ledPin = 3;           // set output pin for the LED

int sensorValue = 0;      // value read from the POT
int outputValue = 0;      // value output to the LED
int delayValue = 0;       // value output to the delay amount
int fadepotValue = 0;     // value read from the fadePOT
int fadeoutputValue = 0;  // value output to the fade amount


void setup() {
// initialize serial communitcations at 9600 bps:
     Serial.begin(9600);   
// declare the ledPin as an OUTPUT:
     pinMode(ledPin, OUTPUT);
// declare the potPin as an INPUT:
     pinMode(potPin, INPUT);
// declare the fadepotPin as an INPUT:     
     pinMode(fadepotPin, INPUT);
}

void loop() {
// read the analog in value:
    sensorValue = analogRead(potPin);
    fadepotValue = analogRead(fadepotPin);
  
// maps it to the range wanted:
    outputValue = map(sensorValue, 0, 1023, 1, 100);
    delayValue = map(sensorValue, 0, 1023, 80, 5);
    fadeoutputValue = map(fadepotValue, 0, 1023, 0, 255);
 
// print the results to the serial monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue); 
  Serial.print("\t delay = ");
  Serial.println(delayValue);
  Serial.print("\t fade = ");
  Serial.println(fadeoutputValue);   
 
// if sensor value reads below 1 set led as low:
  if (sensorValue < 1) {
  digitalWrite(ledPin, LOW);
  }
  
// if sensorvalue reads below 40 set led as high:  
  else if (sensorValue < 40) {
  digitalWrite(ledPin, HIGH);
  }
  
// if sensorvalue reads above 40 start fading:  
  else if (sensorValue > 40)
  {
// fade in from fadeoutputValue to max in increments of 5 points:
  for (int fadeValue = fadeoutputValue; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // sets the delay according to delay value of pot
    delay(delayValue);
  }

  // fade out from max to fadeoutputValue in increments of 5 points:
  for (int fadeValue = 255; fadeValue >= fadeoutputValue; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // sets the delay according to delay value of pot
    delay(delayValue);
  }
 } 
}
