#include <mcs51/at89x52.h>

void delay(int);
void process(int);
int mask(int);

void main(void) {
	int count = 0x00;
	while(1) {
		if(!P2_0) {
			while(!P2_0);
			count = count + 0x01;
			delay(0x35);
			process(count);
		}
	}
}

void delay(int l) {
	TMOD = 0x01;
	TL0 = 0x00;
	TH0 = l;
	TR0 = 1;
	while (TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}

void process(int count) {
	int tens = count / 10;
	int units = count % 10;
	P3 = 0b1110;
	P1 = mask(units);
	delay(0x1F4);
	P3 = 0b1101;
	P1 = mask(tens);
}

int mask(int digit) {
	switch(digit) {
		case 0:
			return 0b11111100;
			break;
		case 1:
			return 0b01100000;
			break;
		case 2:
			return 0b11011010;
			break;
		case 3:
			return 0b11110011;
			break;
		case 4:
			return 0b01100110;
			break;
		case 5:
			return 0b10110110;
			break;
		case 6:
			return 0b10111110;
			break;
		case 7:
			return 0b11100000;
			break;
		case 8:
			return 0b11111110;
			break;
		case 9:
			return 0b11100110;
			break;
	}
}