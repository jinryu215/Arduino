// fade an LED with PWM

int main(void)
{
  DDRD = 0b00001000; // set pin 3 as output
  TCCR2A = 0b00100001; // set up PWM, datasheet p205
  TCCR2B = 0b00000001; // set up PWM and prescaler, datasheet p206
  while(1){
    while(OCR2B<255){
      OCR2B++;  // increment output compare register
      _delay_ms(10);
    }
    while(OCR2B>0){
      OCR2B--; // decrement output compare register
      _delay_ms(10);
    }
  }
}
