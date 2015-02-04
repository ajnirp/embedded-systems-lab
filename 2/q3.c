#include <mcs51/at89x52.h>

void delay(int, int);
void process(int);
int mask(int);

// Top-left Switch = #12
// i.e. R1, C1

// R1, R2, R3, R4
// P2_3, P2_2, P2_1, P2_0

// C1, C2, C3, C4
// P2_4, P2_5, P2_6, P2_7

void main(void) {
    while(1) {
        // check for presses in the 4th column
        P2_7 = 0; P2_6 = 1; P2_5 = 1; P2_4 = 1;
        // check if the button lies in the 1st row
        if(P2_3 == 0) {
            while(P2_3 == 0) // debouncing as reqd.
            	process(0); // avoid blanking out the displays
            P2_7 = 1;
            process(1); // append the corresponding number
        } else if(P2_2 == 0) { // repeat for subsequent rows
            while(P2_2 == 0)
            	process(0);
            P2_7 = 1;
            process(2);
        } else if(P2_1 == 0) {
            while(P2_1 == 0)
            	process(0);
            P2_7 = 1;
            process(3);
        } else if(P2_0 == 0) {
            while(P2_0 == 0)
            	process(0);
            P2_7 = 1;
            process(4);
        } else process(0);

        // repeat for other columns
        P2_7 = 1; P2_6 = 0; P2_5 = 1; P2_4 = 1;
        if(P2_3 == 0) {
            while(P2_3 == 0)
            	process(0);
            P2_6 = 1;
            process(5);
        } else if(P2_2 == 0) {
            while(P2_2 == 0)
            	process(0);
            P2_6 = 1;
            process(6);
        } else if(P2_1 == 0) {
            while(P2_1 == 0)
            	process(0);
            P2_6 = 1;
            process(7);
        } else if(P2_0 == 0) {
            while(P2_0 == 0)
            	process(0);
            P2_6 = 1;
            process(8);
        } else process(0);

        P2_7 = 1; P2_6 = 1; P2_5 = 0; P2_4 = 1;
        if(P2_3 == 0) {
            while(P2_3 == 0)
            	process(0);
            P2_5 = 1;
            process(9);
        } else if(P2_2 == 0) {
            while(P2_2 == 0)
            	process(0);
            P2_5 = 1;
            process(10);
        } else if(P2_1 == 0) {
            while(P2_1 == 0)
            	process(0);
            P2_5 = 1;
            process(11);
        } else if(P2_0 == 0) {
            while(P2_0 == 0)
            	process(0);
            P2_5 = 1;
            process(12);
        } else process(0);

        P2_7 = 1; P2_6 = 1; P2_5 = 1; P2_4 = 0;
        if(P2_3 == 0) {
            while(P2_3 == 0)
            	process(0);
            P2_4 = 1;
            process(13);
        } else if(P2_2 == 0) {
            while(P2_2 == 0)
            	process(0);
            P2_4 = 1;
            process(14);
        } else if(P2_1 == 0) {
            while(P2_1 == 0)
            	process(0);
            P2_4 = 1;
            process(15);
        } else if(P2_0 == 0) {
            while(P2_0 == 0)
            	process(0);
            P2_4 = 1;
            process(16);
        } else process(0);
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

// values on displays (left-right)
static int p = 0, q = 0, r = 0, s = 0;

void process(int num) {
    // cycle the display only when
    // a switch is pressed (num > 0)
    num = num - 1;
    if (num != -1) {
        s = r; r = q;
        q = p; p = num;
    }
    // else merely refresh displays
    P1 = mask(-1);
    P3 = 0b1110;
    P1 = mask(p);
    delay(0x00, 0xEE);
    P1 = mask(-1);
    P3 = 0b1101;
    P1 = mask(q);
    delay(0x00, 0xEE);
    P1 = mask(-1);
    P3 = 0b1011;
    P1 = mask(r);
    delay(0x00, 0xEE);
    P1 = mask(-1);
    P3 = 0b0111;
    P1 = mask(s);
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
            return 0b10010000;
            break;
        case 10:
            return 0b10001000;
            break;
        case 11:
            return 0b10000011;
            break;
        case 12:
            return 0b10100111;
            break;
        case 13:
            return 0b10100001;
            break;
        case 14:
            return 0b10000110;
            break;
        case 15:
            return 0b10001110;
            break;
        default:
            return 0b11111111;
    }
}
