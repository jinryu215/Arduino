/* MAE 3780 HW 7
   Jin Ryu (jfr224)
*/

///////////////////////////Problem 3///////////////////////////
/*
  int main(void){
  DDRD = 0b11000000; // bits 7,6 in port D are outputs, bits 5-0 are inputs

  while(1){
    //light up the two LEDs
    PORTD = 0b11000000; //setting bits 7,6 in port D to 1

    _delay_ms(1000);

    //turn off the two LEDs
    PORTD = 0b00000000; //setting bits 7,6 in port D to 0

    _delay_ms(1000);
  }
  }
*/



///////////////////////////Problem 4///////////////////////////
/*
  int main(void){
  DDRD = 0b11000000; // bits 7,6 in port D are outputs, bits 5-0 are inputs

  while(1){
    //light up the Red LED
    PORTD = 0b10000000; //setting bits 7,6 in port D to 1

    _delay_ms(500);

    //light up the Green LED
    PORTD = 0b01000000; //setting bits 7,6 in port D to 0

    _delay_ms(500);
  }
  }
*/



///////////////////////////Problem 5///////////////////////////
/*
  ISR(INT0_vect){  // external interrupt 0 is triggered
  if (PIND & 0b00000100){ //if PD2 is '1'
    PORTD &= 0b10111111; // turn Green LED off
  } else {
    PORTD |= 0b01000000; // turn Green LED on
  }
  }

  int main(void){
  // setup code that only runs once
  DDRD = 0b11000000; // set red and green LED pins as outputs, other pins as inputs
  EICRA = 0b00000001; // trigger external interrupt 0 on any logical change
  EIMSK = 0b00000001; // enable external interrupt 0
  sei(); // enable interrupts globally

  while(1){
    if(PIND & 0b00000100){ // if PD2 is '1'
      PORTD &= 0b01111111; // turn Red LED off
    } else {
      PORTD |= 0b10000000; // turn Red LED on
    }
  }

  }
*/



///////////////////////////Problem 6///////////////////////////
/*
  ISR(PCINT2_vect) {
  if (PIND & 0b00000100) {
    PORTD &= 0b10111111; // turn Green LED off
  } else {
    PORTD |= 0b01000000; // turn Green LED on
  }
  }

  int main(void) {
  // setup code that only runs once
  DDRD = 0b11000000; // set red and green LED pins as outputs, other pins as inputs

  PCICR = 0b00000100; // pin change interrupt enable 2
  PCMSK2 = 0b00000100; // enable pin change interrupt (PCINT18)
  sei();      // enable interrupts globally

  // code that loops forever
  while (1) {
    if (PIND & 0b00000100) { // if PD2 is '1'
      PORTD &= 0b01111111; // turn Red LED off
    } else {
      PORTD |= 0b10000000; // turn Red LED on
    }
  }
  }
*/



///////////////////////////Problem 7///////////////////////////
/*
  int main(void) {
  // setup code that only runs once
  Serial.begin(9600); // initialize serial

  // set TIMER1 to normal mode w/ prescaler of 1024
  TCCR1A = 0x00; //fill in
  TCCR1B = 0b00000101; //fill in

  while (1) {
    // code that loops forever
    Serial.println(TCNT1); //fill in
  }
  }
*/



//////////////////////////Problem 8////////////////////////////
/*
  volatile int period; // declare period as a volatile variable

  ISR(PCINT2_vect) { // interrupt service routine for pin change interrupt request 2
  if (PIND & 0b00000100) { // button released
    period = TCNT1 * .064;
    Serial.print("Button was pressed for ");
    Serial.print(period);
    Serial.print("ms (=");
    Serial.print(period / 1000);
    Serial.println("s).");
  } else { // button pressed
    TCNT1 = 0x00;
  }
  }

  int main(void) {
  // setup code that only runs once
  Serial.begin(9600); // initialize serial

  PCICR = 0b00000100; // enable pin change interrupt
  PCMSK2 = 0b00000100; // enable
  sei(); // enable interrupts globally

  TCCR1A = 0x00; // set timer 1 to normal mode
  TCCR1B = 0b00000101; // and set prescaler to 1024

  Serial.begin(9600); // initialize serial

  while (1) {
    // code that loops forever
  }

  }
*/



///////////////////////////Problem 9///////////////////////////

// control servo position using PWM from timer 1
int main(void)
{
  DDRB = 0b00000010; // set pin 9 as output
  // set timer control registers to set up PWM with desired frequency and pulse width.
  // Use timer mode 8 (phase and frequency correct PWM).
  TCCR1A = 0b10000000; // mode 8
  TCCR1B = 0b00010010; // mode 8, precalor 8
  ICR1 = 20000; //in microseconds
  OCR1A = 900;


  while (1) {
    // write code to make the servo oscillate between its two extremes by changing the
    // duty cycle from 900us to 2100us and back repeatedly.
    // Hint: look at the LED fading code from problem 7 on HW3.
    while (OCR1A <= 2100) {
      OCR1A++;
    }
    while (OCR1A > 900) {
      OCR1A--;
    }
  }
}
