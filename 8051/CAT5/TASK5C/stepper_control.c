#include <reg51.h>

code unsigned char step_sequence[4] = {
    0x08, /* 1000 */
    0x04, /* 0100 */
    0x02, /* 0010 */
    0x01  /* 0001 */
};

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 123; j++);
    }
}

void main(void) {
    unsigned char step = 0;

    while (1) {
        /* Step motor with 50 ms medium speed interval */
        P2 = (P2 & 0xF0) | step_sequence[step];
        delay_ms(50);

        step++;
        if (step >= 4) {
            step = 0;
        }
    }
}
