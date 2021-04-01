#include <HuemonelabKit.h>
volatile int operating = 0;
volatile int smiling = 0;

Buzzer buzzer(13);
TouchSensor touch(2);
ServoMotor servoA;
ServoMotor servoFace;
RGBLed rgb(3, 5, 6);

void setup() {
  //Serial.begin(9600);
  servoA.attach(7);
  servoFace.attach(8);
}

void loop() {
  int value = touch.read();
  //Serial.println(value);



  if (value == 1) {           //Touched
    if (operating == 0) {   //Not been studying -- "Turn on" (Red)
      rgb.setColor(255, 255, 0);
      //    buzzer.play(random(1, 6));
      buzzer.play(2);
      
      servoA.write(100);
      for (int i = 1; i <= 80; i++) {
        servoA.write(100 + i);
        delay(10);
      }
      for (int i = 1; i <= 80; i++) {
        servoA.write(180 - i);
        delay(10);
      }

      operating = 1;
      smiling = 1;


    } else {                //been studying -- "Turn off"
      buzzer.play(3);
     
      for (int i = 1; i <= 80; i++) {
        servoA.write(180 - i);
        delay(10);
      }
      rgb.setColor(0, 0, 0);
      operating = 0;
      for (int i = 0; i <= 320; i++) {    //Face 320->0
        servoFace.write(i);
        delay(10);
      }
      delay(5000);
    }


  } else {                  //Untouched
    if (operating == 1) {   //been studying -- "Studying" (Blue)
      if (smiling == 1) {
        for (int i = 1; i <= 80; i++) {
          int color = 3* i;               //= 255 / 80 * i
          servoFace.write(320-(i-1)*4);   //Face 0->320
          rgb.setColor(color, color, color);
          servoA.write(100 + i);
          delay(100);
        }
        smiling = 0;
      }


    } else {                                 // -- "Idle" (Green)
      rgb.setColor(50, 50, 0);
      servoA.write(100);
      servoFace.write(320);
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
