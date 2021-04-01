#include <Wire.h>
#include <I2C_LCD.h>
#include <HuemonelabKit.h>

volatile int used = 0;

I2C_LCD LCD;
uint8_t I2C_LCD_ADDRESS = 0x51; //Device address configuration, the default value is 0x51.
JoyStick joystick(A1, A0);

void setup() {
  Wire.begin();         //I2C controller initialization.
  Serial.begin(9600);
  joystick.attach(10);
}

void loop() {
  //  int button = joystick.isPushed();
  //  Serial.println("button is ");
  //  Serial.print(button);
  //  Serial.print(" used is ");
  //  Serial.print(used);

  delay(5000);
  int button = 1;
  
  if (button == 1 && used == 0) {
    used = 1;
    LCD.CleanAll(WHITE);
    tellStory();
  } else if (button == 0 && used == 0) {
    telling(0, 6, "m", "Please press   the button to  begin.", true, 1000);
  }
}

void tellStory() {
  telling(0, 6, "m", "Hello! Which   genre would youlike to read?", false, 1000);
  telling(0, 8, "s", "Choose by moving the joystick to the..     Fantasy  - Yellow    Mistery  - Red       Action   - Green     Poetry   - Blue     ", true, 1000);
  telling(0, 8, "s", "Choose by moving the joystick to the..   3 Fantasy  - Yellow    Mistery  - Red       Action   - Green     Poetry   - Blue     ", true, 1000);
  telling(0, 8, "s", "Choose by moving the joystick to the..   2 Fantasy  - Yellow    Mistery  - Red       Action   - Green     Poetry   - Blue     ", true, 1000);
  telling(0, 8, "s", "Choose by moving the joystick to the..   1 Fantasy  - Yellow    Mistery  - Red       Action   - Green     Poetry   - Blue     ", false, 1000);
  //int valueX = joystick.read('x'); int valueY = joystick.read('y');
  int valueX = 1000;
  
  if (valueX > 800) {
    fantasy();
  } else {
    //notReady();
  }
  used = 0;
}

void fantasy() {
  displayMessage("s", "Charlie lives in the suburbs with his poor family. Everyday he passes by the biggest chocolate factory in the world, run by Willy Wonka. One day, he won a golden ticket to the factory, and ...");
  //displayMessage("s", "Charlie lives in the suburbs with his poor family. Everyday he passes by the biggest chocolate factory in the world, run by Willy Wonka. ------1---------2------------3-----------4---------5");
}


void displayMessage(String size, String message) {
  //LCD.CleanAll(WHITE);
  chooseSize(size);

  int length = message.length();

  Serial.print("I'm displaying this message: ");
  Serial.println(message);
  //
  //  String page = message.substring(0, 105);
  Serial.print("message length is ");
  Serial.print(message.length());
  Serial.print(" and it has #pages: ");
  Serial.println(message.length() / 105);
  for (int i = 0; i <= message.length() / 105; i++) {
    int startIndex = i * 105;
    int endIndex = (startIndex + 105 > length - 1) ? (length) : startIndex + 105;
    Serial.print("My start and end index for this page is ");
    Serial.print(startIndex);
    Serial.print(", ");
    Serial.println(endIndex);
    String page = message.substring(startIndex, endIndex);
    Serial.println("This page goes off like..");
    Serial.println(page);

    displayOnePage(page);
    delay(5000);
    LCD.CleanAll(WHITE);
  }
}

void displayOnePage(String pageMessage) {
  int length = pageMessage.length();
  Serial.println(length);
  int lastLine = (length / 21 < 5) ? length / 21 + 1 : 5;
  for (int i = 0; i < lastLine; i++) {
    Serial.print("Printing line ");
    Serial.print(i);
    Serial.print(": ");
    LCD.CharGotoXY(0, i * 14);
    int messageEnd = ((i + 1) * 21 < length) ? (i + 1) * 21 : length;
    Serial.println(pageMessage.substring(i * 21, messageEnd));
    LCD.print(pageMessage.substring(i * 21, messageEnd));
  }
}

void telling(int x, int y, String size, String inst, boolean keep, int time) {
  chooseSize(size);

  LCD.CharGotoXY(x, y);
  LCD.print(inst);
  delay(time);
  if (!keep) {
    LCD.CleanAll(WHITE);
  }
}

void chooseSize(String size) {
  //8*16 font size��auto new line��black character on white back ground.
  if (size == "s") {
    LCD.FontModeConf(Font_6x8, FM_ANL_AAA, BLACK_BAC);
  } else if (size == "m") {
    LCD.FontModeConf(Font_8x16_2, FM_ANL_AAA, BLACK_BAC);
  } else if (size == "l") {
    LCD.FontModeConf(Font_12x24, FM_ANL_AAA, BLACK_BAC);
  }
}
