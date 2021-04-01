/* 
///////////////////////////Problem 5///////////////////////////

volatile int GreenLED=0;

ISR(INT0_vect){  // external interrupt 0 is triggered
  PORTD |= 0b01000000; // turn Green LED on
  GreenLED=1;
  
}

int main(void){
  // setup code that only runs once
  DDRD = 0b11000000; // set red and green LED pins as outputs, other pins as inputs
  
  EICRA = 0b00000001; // trigger external interrupt 0 on any logical change 
  EIMSK = 0b00000001; // enable external interrupt 0
  
  sei(); // enable interrupts globally
  
  while(1){
    // code that loops forever
    
    if(PIND & 0b00000100){ // if PD2 is '1'
      PORTD &= 0b01111111; // turn Red LED off
    } else {
      PORTD |= 0b10000000; // turn Red LED on
      _delay_ms(50);
    }
    
    if(GreenLED && (PIND & 0b00000100)){ // Green LED 'on' && PD2 '1'
      PORTD &= 0b10111111; // turn Green LED off
      GreenLED=0;
    } else {
      _delay_ms(50);
    }
  }
  
}

*/


/*
///////////////////////////Problem 6///////////////////////////
volatile int GreenLED=0;

ISR(PCINT2_vect){
  PORTD |= 0b01000000; // turn Green LED on
  GreenLED=1;
  }
 
 int main(void){
  // setup code that only runs once
  DDRD = 0b11000000; // set red and green LED pins as outputs, other pins as inputs
  
  PCICR = 0b00000100; // pin change interrupt enable 2 
  PCMSK2 = 0b00000100; // enable pin change interrupt (PCINT18)
  sei();      // enable interrupts globally
  
  // code that loops forever
  while(1){
    if(PIND & 0b00000100){ // if PD2 is '1'
      PORTD &= 0b01111111; // turn Red LED off
    } else {
      PORTD |= 0b10000000; // turn Red LED on
      _delay_ms(50);
    }
    
    if(GreenLED && (PIND & 0b00000100)){ // Green LED 'on' && PD2 '1'
      PORTD &= 0b10111111; // turn Green LED off
      GreenLED=0;
    } else {
      _delay_ms(50);
    }
  } 
}
*/
