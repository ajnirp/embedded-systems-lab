#include <mcs51/at89x52.h>

void delay(int, int);
void process(int);
int mask(int);

void main(void) {
	int count = 0x00;
	while(1) {
        // when the button corresponding to port P2 is pressed,
        // increment the count and show it on the 7-segment display
		if(!P2_0) {
			while(!P2_0);
			count = count + 0x01;
            // limit it to 4 digits (note: for counting
            // only upto 99, take remainder with 100)
            count = count % 10000;
            // no delay is explicitly inserted here as the
            // display/refresh function uses up 20 ms anyway
		}
        process(count);
	}
}

void delay(int n1, int n2) {
	TMOD = 0x01;
	TL0 = n1;
	TH0 = n2;
	TR0 = 1;
	while (TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}

// P1 - CN2, P3 - CN1
void process(int count) {
    // note: refresh the display first (no ghosting)
    P1 = mask(-1);
	P3 = 0b1110;
	P1 = mask(count);
    // keep a 5 ms delay to avoid garbled output
	delay(0x00, 0xEE);
    // repeat for the displays corresponding to higher places
    P1 = mask(-1);
	P3 = 0b1101;
	P1 = mask(count/10);
	delay(0x00, 0xEE);
    P1 = mask(-1);
	P3 = 0b1011;
	P1 = mask(count/100);
	delay(0x00, 0xEE);
    P1 = mask(-1);
	P3 = 0b0111;
	P1 = mask(count/1000);
	delay(0x00, 0xEE);
}

int mask(int digit) {
   	switch(digit) {
		case 0:
			return 0b11000000;
			break;
		case 1:
			return 0b11111001;
			break;
		case 2:
			return 0b10100100;
			break;
		case 3:
			return 0b10110000;
			break;
		case 4:
			return 0b10011001;
			break;
		case 5:
			return 0b10010010;
			break;
		case 6:
			return 0b10000010;
			break;
		case 7:
			return 0b11111000;
			break;
		case 8:
			return 0b10000000;
			break;
		case 9:
			return 0b10011000;
			break;
		default:
		    return 0b11111111;
	}
}