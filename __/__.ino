#include <HuemonelabKit.h>
volatile int operating = 0;
volatile int smiling = 0;
volatile int speed = 0;

Buzzer buzzer(13);
TouchSensor touch(2);
ServoMotor servoA;
ServoMotor servoFace;
RGBLed rgb(3, 5, 6);

void setup() {
  //Serial.begin(9600);
  servoA.attach(7);
}

void loop() {
  int value = touch.read();
  //Serial.println(value);

  if (value == 1) {           //Touched
    if (operating == 0) {   //Not been studying
      //    buzzer.play(random(1, 6));
      buzzer.play(2);

      servoA.write(180);
      delay(500);
      servoA.write(100);
      delay(500);
      servoA.write(180);

      operating = 1;
      smiling = 1;
    } else {                //been studying
      buzzer.play(3);
      servoA.write(180);
      rgb.setColor(0, 0, 0);
      operating = 0;
      delay(10000);
    }
  } else {                  //Untouched
    if (operating == 1) {   //been studying
      if (smiling == 1) {
        for (int i = 1; i <= 80; i++) {
          int color = 3 * i; //(255/80)
          rgb.setColor(color, color, color);
          servoA.write(180 - i);
          servoFace.write(320-4*i);
        }
        smiling = 0;
      } else{
      }
    } else {
      
      rgb.setColor(0, 0, 0);
      servoA.write(180);


    }
  }

  //  if (operating == 1) {
  //    for (int i = 1; i <= 255; i++) {
  //      int color = 255 / 255 * i;
  //      stepper.step(2048 / 255);
  //      rgb.setColor(color, color, color);
  //    }
  //    operating = 0;
  //  }

  //  if (value == 1 && operating == )
}
