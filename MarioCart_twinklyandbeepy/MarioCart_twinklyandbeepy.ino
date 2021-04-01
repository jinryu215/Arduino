#include <HuemonelabKit.h>

Buzzer beep(12);
RGBLed twinkle(9,10,11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  double tempo[54] = {8,8,8,8,8,8, 4,4,4,4,4, 8,4,8,4,8/3, 4,4,8,4, 6,6,6,4,8,8, 8,4,8,4,8/3, 8,4,8,4,8/3, 4,4,8,4, 6,6,6,4,8,8, 8,4,8,8,8,8,8,8};
  char notes[54] = {'e','e','R','e','R','c','e', 'g','R','G','R', 'c','R','G','R','E', 'A','B','S','A', 'G','e','g','a','f','g', 'R','e','c','d','B', 'c','R','G','R','E', 'A','B','S','A', 'G','e','g','a','f','g', 'R','e','c','d','c','B','R','c'};
  
  for(int a=0; a<54; a++){
    if(notes[a]!='R'){
      if(a%3==0){
       twinkle.setColor(255,0,0);
      }else if((a%3)==1){
        twinkle.setColor(0,255,0);
      }else{
        twinkle.setColor(0,0,255);
      }
    }
    
    double t = 60000*4/180/tempo[a];
    beep.note(notes[a],t);
  }

  exit(0);
}
