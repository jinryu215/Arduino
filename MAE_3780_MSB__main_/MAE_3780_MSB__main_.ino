#include <HuemonelabKit.h>
volatile int operating = 0;
volatile int smiling = 0;

Buzzer buzzer(13);
TouchSensor touch(2);
Stepper stepper(8, 9, 10, 11);
ServoMotor servo;
RGBLed rgb(3, 5, 6);

int main(void) {
  //Serial.begin(9600);
  stepper.setSpeed(10);
  stepper.setDir(1);
  servo.attach(7);

  while (1) {
    int value = touch.read();
    //Serial.println(value);

    if (value == 1) {           //Touched
      if (operating == 0) {   //Not been studying
        rgb.setColor(255, 255, 0);
        //    buzzer.play(random(1, 6));
        buzzer.play(2);
        rgb.setColor(0, 0, 0);
        
        servo.write(180);
        delay(500);
        servo.write(90);
        delay(500);
        servo.write(180);

        operating = 1;
        smiling = 1;
      } else {                //been studying
        buzzer.play(3);
        servo.write(180);
        rgb.setColor(0, 0, 0);
        operating = 0;
        delay(5000);
      }
    } else {                  //Untouched
      if (operating == 1) {   //been studying
        if (smiling == 1) {
          for (int i = 1; i <= 90; i++) {
            int color = 255 / 90 * i;
            stepper.step(2048 / 90);
            rgb.setColor(color, color, color);
            servo.write(180 - i);
          }
          smiling = 0;
        } else {
        }
      } else {
        rgb.setColor(50, 50, 0);
        servo.write(180);
      }
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
