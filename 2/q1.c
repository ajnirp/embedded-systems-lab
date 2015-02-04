#include <mcs51/at89x52.h>

void delay(int, int);

void main(void) {
    int count = 0x00;
    P1 = 0x00;
    while (1) {
        // when the button corresponding to port P2 is pressed,
        // increment the count and update it on port P1
        if (!P2_0) {
            while (!P2_0);
            count = count + 0x01;
            // debouncing (for about 56 ms, using Timer 0)
            delay(0x00, 0x35);
            P1 = count;
        }
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