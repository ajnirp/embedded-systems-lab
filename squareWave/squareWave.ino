/* Program to generate a square wave
   that toggles between 1-4 V
   of frequency 100 Hz
   
   When given as input to the open-loop system in
   Fig 1.1, the output is a triangular wave
   with freq 100 Hz
*/

int pwm = 5;
int ms = 0;
boolean high = true;
float k = 0.2;

void setup() {
  pinMode(pwm, OUTPUT);
  init_tccr();
  init_ocr();
  
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

/* Set timer compare value to 1250
   so that ISR is called once every 5 msec
*/
void init_ocr() {
  OCR1A = 1250;
}

void loop() {
  int plant_output = analogRead(A5);
  int plant_input = analogRead(A0);
  int err = -plant_output + plant_input;
  err = err * k;
  err = map(err, 0, 1023, 0, 255);
  analogWrite(6, err);
}

/* Interrupt service routine */
ISR(TIMER1_COMPA_vect) {
  high = !high;
  if (high) analogWrite(pwm,205);
  else analogWrite(pwm, 51);
}
