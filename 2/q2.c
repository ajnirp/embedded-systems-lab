#include <mcs51/at89x52.h>

void timerDelay(void);
void mask(void);

void main(void) {
    int count = 0x00;
    P1 = 0x00;
    P3 = 0b1110;
    while (1) {
        if (!P2_0) {
            while (!P2_0);
            count = count + 0x01;
            timerDelay();
            
        }
    }
}

void timerDelay(void) {
	TMOD = 0x01;
	TL0 = 0x00;
	TH0 = 0x35;
	TR0 = 1;
	while (TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}

void process(int count) {
	int tens = count / 10;
	int units = count % 10;

	mask(units);
	mask(tens);
}

int mask(int digit) {
	switch(digit) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	}
}