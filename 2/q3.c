#include <mcs51/at89x52.h>

void delay(int, int);
void process(int);
int mask(int);

void main(void) {
	int num = 0x0000;
	while(1) {
		if(!P2_0 || !P2_1 || !P2_2 || !P2_3) {
			num = num % 1000;
			num = num * 10 + ((1-P2_3)*8 + (1-P2_2)*4 + (1-P2_1)*2 + (1-P2_0)*1);
            while(!P2_0 || !P2_1 || !P2_2 || !P2_3);
		}
        process(num);
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

void process(int count) {
	P1 = mask(-1);
	P3 = 0b1110;
	P1 = mask(count);
	delay(0x00, 0xEE);
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
   	switch(digit%10) {
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
