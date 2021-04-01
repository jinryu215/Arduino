//Code to make a servo motor run when the light sensor is covered (dark) and 
//stop when the light sensor is not covered (exposed to light)

// Setup:
// - attach light sensor to pin A0 on your shield
// - attach servo motor to pin D5 on your shield

#include <Servo.h>
#include "Ultrasonic.h"
 
Ultrasonic ultrasonic(7);
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
//const int thresholdvalue=10; //The threshold for which the LED should turn on. 
int thresholdvalue=10; //The threshold for which the LED should turn on. 
int servolocation=0;
int mode=0; //mode 0 - not in use, mode 1 - in use

void setup() {
  Serial.begin(9600); //Start the Serial connection (helps you debug your code)
  myservo.attach(5); // Servo attached to Pin D5; if you move the servo to another pin change this number
}

void loop() {
  int distance = ultrasonic.MeasureInCentimeters(); //Read how much light is entering the light sensor
  Serial.println(distance);
  if(distance < thresholdvalue && mode==0) { //If the amount of light is LESS than 400, run the motor
    for (pos = 0; pos <= 90; pos += 1) { 
      myservo.write(pos);              
      delay(15);                       
    }
    servolocation=90;
    mode=1;
  } else if (distance > thresholdvalue && mode==1){
    for (pos = 90; pos >= 0; pos -= 1) { 
      myservo.write(pos);              
      delay(15);
    }
    servolocation=0;
    mode=0;
  } else if (distance > thresholdvalue && mode==0){
    myservo.write(servolocation); 
  } else { //If the amount of light is MORE than 400, stop the motor
    myservo.write(servolocation); 
  }

// Debugging stuff
  //  Serial.println("the analog read data is ");
  //  Serial.println(sensorValue);
  //  delay(500);
}
