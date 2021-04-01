int main(void){
  // setup code that only runs once
  DDRD = 0b00001000; // set pin 3 as output
  DDRB = 0b00001000; // set pin 11 as output
  
  while(1){
    // code that loops forever
    PORTD = 0b00001000; // set pin 3 high
    _delay_ms(1000);    // wait 1 second
    PORTD = 0b00000000; // set pin 3 low
    _delay_ms(1000);    // wait 1 second
    PORTB = 0b00001000; // set pin 11 high
    _delay_ms(1000);    // wait 1 second
    PORTB = 0b00000000; // set pin 11 low
    _delay_ms(1000);    // wait 1 second
    }
    
}
