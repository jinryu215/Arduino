int main(void){
  // setup code that only runs once
  DDRD = 0b00001000; // set pin 3 as output
  PORTD = 0b00001000; // set pin 3 high, other pins low
  while(1){
    // code that loops forever
    
  }
}
