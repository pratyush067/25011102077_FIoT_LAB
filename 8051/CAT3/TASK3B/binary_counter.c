#include <reg51.h>

sbit BUTTON = P3^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 123; j++);
    }
}

void main(void) {
    unsigned char count = 0;
    BUTTON = 1;

    while (1) {
        P1 = (P1 & 0xF0) | (count & 0x0F);
        delay_ms(500);
        count = (count + 1) & 0x0F;

        if (BUTTON == 0) {
            delay_ms(20);
            if (BUTTON == 0) {
                while (BUTTON == 0);
                delay_ms(20);
                /* Advance to next mode */
            }
        }
    }
}
