#include <HuemonelabKit.h>

JoyStick joystick(A1, A0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  joystick.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valueX = joystick.read('x');
  int valueY = joystick.read('y');
  int button = joystick.isPushed();

  Serial.print("x축 :");
  Serial.println(valueX);
  Serial.print("y축 :");
  Serial.println(valueY);
  Serial.print("버튼 :");
  Serial.println(button);
  delay(1000);
}
