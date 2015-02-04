#include <mcs51/at89x52.h>

void delay(int, int);
void process(int);
int mask(int);

void main(void) {
    while(1) {
        P2_0 = 1; P2_1 = 0; P2_2 = 0; P2_3 = 0;
        delay(0x00, 0x35);
        if(P2_4 == 0) {
            process(3);
            P2_0 = 0;
            while(P2_4 == 0);
        } else if(P2_5 == 0) {
            process(2);
            P2_0 = 0;
            while(P2_5 == 0);
        } else if(P2_6 == 0) {
            process(1);
            P2_0 = 0;
            while(P2_6 == 0);
        } else if(P2_7 == 0) {
            process(0);
            P2_0 = 0;
            while(P2_7 == 0);
        } else process(-1);

        P2_0 = 0; P2_1 = 1; P2_2 = 0; P2_3 = 0;
        delay(0x00, 0x35);
        if(P2_4 == 0) {
            process(7);
            P2_1 = 0;
            while(P2_4 == 0);
        } else if(P2_5 == 0) {
            process(6);
            P2_1 = 0;
            while(P2_5 == 0);
        } else if(P2_6 == 0) {
            process(5);
            P2_1 = 0;
            while(P2_6 == 0);
        } else if(P2_7 == 0) {
            process(4);
            P2_1 = 0;
            while(P2_7 == 0);
        } else process(-1);

        P2_0 = 0; P2_1 = 0; P2_2 = 1; P2_3 = 0;
        delay(0x00, 0x35);
        if(P2_4 == 0) {
            process(11);
            P2_2 = 0;
            while(P2_4 == 0);
        } else if(P2_5 == 0) {
            process(10);
            P2_2 = 0;
            while(P2_5 == 0);
        } else if(P2_6 == 0) {
            process(9);
            P2_2 = 0;
            while(P2_6 == 0);
        } else if(P2_7 == 0) {
            process(8);
            P2_2 = 0;
            while(P2_7 == 0);
        } else process(-1);

        P2_0 = 0; P2_1 = 0; P2_2 = 0; P2_3 = 1;
        delay(0x00, 0x35);
        if(P2_4 == 0) {
            process(15);
            P2_3 = 0;
            while(P2_4 == 0);
        } else if(P2_5 == 0) {
            process(14);
            P2_3 = 0;
            while(P2_5 == 0);
        } else if(P2_6 == 0) {
            process(13);
            P2_3 = 0;
            while(P2_6 == 0);
        } else if(P2_7 == 0) {
            process(12);
            P2_3 = 0;
            while(P2_7 == 0);
        } else process(-1);
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

void process(int num) {
    static int p = 0, q = 0, r = 0, s = 0;
    if (num != -1) {
        s = r; r = q;
        q = p; p = num;
    }
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
