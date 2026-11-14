#include <reg51.h>

sbit BUTTON = P3^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 123; j++);
    }
}

void main(void) {
    unsigned char pattern = 0x01;
    BUTTON = 1; /* Configure P3.2 as input */

    while (1) {
        /* Update lower 4 bits of Port 1 while preserving upper 4 bits */
        P1 = (P1 & 0xF0) | (pattern & 0x0F);
        delay_ms(250);

        pattern <<= 1;
        if (pattern > 0x08) {
            pattern = 0x01;
        }

        /* Check for button press event with debouncing */
        if (BUTTON == 0) {
            delay_ms(20); /* Debounce filter */
            if (BUTTON == 0) {
                while (BUTTON == 0); /* Wait for button release */
                delay_ms(20);
                /* Advance mode */
            }
        }
    }
}
