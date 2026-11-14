#include <reg51.h>

sbit BUTTON = P3^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 123; j++);
    }
}

void main(void) {
    BUTTON = 1;

    while (1) {
        P1 = (P1 & 0xF0) | 0x0F; /* All ON */
        delay_ms(250);

        P1 = (P1 & 0xF0) | 0x00; /* All OFF */
        delay_ms(250);

        if (BUTTON == 0) {
            delay_ms(20);
            if (BUTTON == 0) {
                while (BUTTON == 0);
                delay_ms(20);
                /* Return to Mode 1 */
            }
        }
    }
}
