#include <reg51.h>

sbit PULSE_OUT = P1^1;

unsigned char current_mode = 2; /* Default 1 kHz */

/* Preload lookup table for half-periods: 100Hz, 500Hz, 1kHz, 2kHz, 5kHz */
code unsigned int reload_table[] = {
    0xEE00, /* 100 Hz */
    0xFC66, /* 500 Hz */
    0xFE33, /* 1 kHz  */
    0xFF1A, /* 2 kHz  */
    0xFFA4  /* 5 kHz  */
};

void timer0_isr(void) interrupt 1 {
    unsigned int r = reload_table[current_mode];
    TH0 = (r >> 8) & 0xFF;
    TL0 = r & 0xFF;
    PULSE_OUT = ~PULSE_OUT;
}

void main(void) {
    TMOD &= 0xF0;
    TMOD |= 0x01; /* Mode 1 16-bit timer */

    TH0 = 0xFE;
    TL0 = 0x33;

    ET0 = 1;
    EA = 1;
    TR0 = 1;

    while (1) {
        /* Background control or mode switching */
    }
}
