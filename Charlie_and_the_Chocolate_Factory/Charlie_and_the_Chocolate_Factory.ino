#include <Wire.h>
#include <I2C_LCD.h>
#include <HuemonelabKit.h>
volatile int used = 0;

I2C_LCD LCD;
uint8_t I2C_LCD_ADDRESS = 0x51; //Device address configuration, the default value is 0x51.
JoyStick joystick(A1, A0);
//For detials of the function useage, please refer to "I2C_LCD User Manual".
//You can download the "I2C_LCD User Manual" from I2C_LCD WIKI page: http://www.seeedstudio.com/wiki/I2C_LCD


void setup(void)
{
  Wire.begin();         //I2C controller initialization.
  Serial.begin(9600);
  joystick.attach(10);
}


void loop(void)
{
  //  LCD.CleanAll(WHITE);    //Clean the screen with black or white.
  //  delay(1000);            //Delay for 1s.

  int button = joystick.isPushed();

  if (button == 1 && used == 0) {
    used = 1;
    tellStory();
  } else if (button == 0 && used == 0) {
    telling(0, 10, "m", "Please press the button to begin.", true, 1000);
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

void tellStory() {
  telling(0, 6, "m", "Hello! Which   genre would youlike to read?", false, 5000);
  telling(0, 8, "s", "Choose by moving the joystick to the..     Fantasy  - Left (<)  Romance  - Up (^)    Poetry   - Right (>) Thriller - Down (v) ", true, 3000);
  telling(0, 8, "s", "Choose by moving the joystick to the..   3 Fantasy  - Left (<)  Romance  - Up (^)    Poetry   - Right (>) Thriller - Down (v) ", true, 1000);
  telling(0, 8, "s", "Choose by moving the joystick to the..   2 Fantasy  - Left (<)  Romance  - Up (^)    Poetry   - Right (>) Thriller - Down (v) ", true, 1000);
  telling(0, 8, "s", "Choose by moving the joystick to the..   1 Fantasy  - Left (<)  Romance  - Up (^)    Poetry   - Right (>) Thriller - Down (v) ", false, 1000);
  int valueX = joystick.read('x'); int valueY = joystick.read('y');

  if (valueX < 200) {
    fantasy();
  } else {
    notReady();
  }

  //afterReading();
}

//void afterReading() {
//  telling(0, 0, "m", "Would you like to check your reading?         <- YES        NO -> ", false, 3000);
  //  telling(0, 0, "m", "Would you like to check your reading?      3  <- YES        NO -> ", false, 1000);
  //  telling(0, 0, "m", "Would you like to check your reading?      2  <- YES        NO -> ", false, 1000);
  //  telling(0, 0, "m", "Would you like to check your reading?      1  <- YES        NO -> ", false, 1000);
  //  int valueXx = joystick.read('x'); int valueYy = joystick.read('y');
  //
  //  if (valueXx < 200) {
  //    quiz();
  //  } else if (valueXx > 800) {
  //    notReady();
  //  }
}

//void quiz() {
//  telling(0, 0, "s", "Who were the workers at the chocolate factory?                    [<] Minions          [^] Simpsons         [>] Oompa Loompas    [v] Willy Wonka     ", false, 3000);
//  telling(0, 0, "s", "Who were the workers at the chocolate factory?                 3  [<] Minions          [^] Simpsons         [>] Oompa Loompas    [v] Willy Wonka     ", false, 1000);
//  telling(0, 0, "s", "Who were the workers at the chocolate factory?                 2  [<] Minions          [^] Simpsons         [>] Oompa Loompas    [v] Willy Wonka     ", false, 1000);
//  telling(0, 0, "s", "Who were the workers at the chocolate factory?                 1  [<] Minions          [^] Simpsons         [>] Oompa Loompas    [v] Willy Wonka     ", false, 1000);
//  int valueX = joystick.read('x'); int valueY = joystick.read('y');
//
//  if (valueX > 800) {
//    telling(0, 24, "m", "Correct! Here is your reward code: s4qv9", false, 5000);
//    used = 0;
//  } else if (valueX < 200) {
//    notReady();
//  }
//
//}

void fantasy() {
  Serial.println("fantasy chosen!");
  displayMessage("s", "Charlie lives in the suburbs with his poor family. Everyday he passes by the biggest chocolate factory in the world, run by Willy Wonka. Charile finds a golden ticket from his Wonka chocolate bar, and he begins his journey by visiting the chocolate factory...");

}

//void notReady() {
//  displayMessage("s", "System not ready yet..");
//}

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

void displayMessage(String size, String message) {
  //LCD.CleanAll(WHITE);
  chooseSize(size);

  int length = message.length();

  Serial.print("I'm displaying this message: ");
  Serial.println(message);

  for (int i = 0; i <= message.length() / 21; i++) {
    int startIndex = i * 105;
    int endIndex = (startIndex + 105 > length - 1) ? (length) : startIndex + 105;
    Serial.print("My start and end index for this page is ");
    Serial.print(startIndex);
    Serial.print(", ");
    Serial.println(endIndex);
    String page = message.substring(startIndex, endIndex);
    Serial.println(page);

    displayOnePage(page);
    delay(5000);
    LCD.CleanAll(WHITE);
  }
}

/* Divides given string into lines (0..5) and prints the appropriate message
   for each line.
*/
void displayOnePage(String pageMessage) {
  int length = pageMessage.length();
  int lastLine = (length / 21 < 5) ? length / 21 + 1 : 5;
  for (int i = 0; i < lastLine; i++) {
    Serial.print("Printing page ");
    Serial.print(i);
    Serial.print(" of ");
    Serial.println(pageMessage);
    LCD.CharGotoXY(0, i * 14);
    int messageEnd = ((i + 1) * 21 < length) ? (i + 1) * 21 : length;
    Serial.print("This is for one page: ");
    Serial.println(pageMessage.substring(i * 21, messageEnd));
    LCD.print(pageMessage.substring(i * 21, messageEnd));
  }
}
