#include <mcs51/at89x52.h>

void timerDelay(void);

// note: long press will force a double increment
void main(void) {
    int count = 0x00;
    P1 = 0x00;
    while (1) {
    	// when the button corresponding to port P2
    	// is pressed, increment the count and display
    	// it on port P1
        if (!P2_0) {
            while (!P2_0);
            count = count + 0x01;
            timerDelay();
            P1 = count;
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