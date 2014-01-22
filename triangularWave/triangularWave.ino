/* Program to generate a triangular wave
   of frequency 100 Hz */

int pwm = 5;
int ms = 0;
//boolean up = true;
boolean low = true;
//boolean on = true;

// lut[i] ~= analog value for i volts
int lut[6];

void setup() {
  pinMode(pwm, OUTPUT);
  
  init_tccr();
  init_ocr();
  init_lut();
  
  interrupts(); // Enable interrupts
}

void init_tccr() {
  /* Set waveform generation mode to CTC i.e.
       WGM13 == 0
       WGM12 == 1
       WGM11 == 0
       WGM10 == 0
     and set prescaling to 64 i.e.
       CS12 == 0
       CS11 == 1
       CS10 == 1
  */
  TCCR1A &= 0xfc; // set WGM11 and WGM10 to 0
  TCCR1B &= 0xeb; // set WGM13 and CS12 to 0
  TCCR1B |= 0x0b; // set WGM12, CS11 and CS10 to 1
  
  /* Set prescalar for timer 0 to 1 */
  TCCR0B &= 0xf8;
  TCCR0B |= 0x01;
  
  /* Enable comparison */
  TIMSK1 = 0x02;
}

/* Set timer compare value to 250 */
void init_ocr() {
  OCR1A = 250;
}

/* Initialize the lookup table */
void init_lut() {
  lut[0] = 0;
  lut[1] = 51;
  lut[2] = 102;
  lut[3] = 154;
  lut[4] = 205;
  lut[5] = 255;
}

void loop() {}

/* Interrupt service routine */
ISR(TIMER1_COMPA_vect) {
//  
//  ms += 1;
//  
//  // change direction if need be
//  if (ms == 5) up = false;
//  else if (ms == 10) {
//    up = true;
//    ms = 0;
//  }
//  
//  // write the analog value
//  if (up) analogWrite(pwm, lut[ms]);
//  else analogWrite(pwm, lut[10-ms]);
  if (low) {
    
  }
}
