#include "delay.h"

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 123; j++) {
            /* 11.0592 MHz calibration waste loop */
        }
    }
}

void delay_sec(unsigned char sec) {
    unsigned char s;
    for (s = 0; s < sec; s++) {
        delay_ms(1000);
    }
}
