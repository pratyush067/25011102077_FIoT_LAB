#include <reg51.h>

sbit LED = P1^0;

volatile unsigned char pwm_tick = 0;
volatile unsigned char duty = 0;

/* Timer 0 ISR: ~500 Hz PWM with 20 steps (100 us slice) */
void timer0_pwm_isr(void) interrupt 1 {
    /* 100 us reload: 65536 - 92 = 65444 (0xFFA4) */
    TH0 = 0xFF;
    TL0 = 0xA4;

    pwm_tick++;
    if (pwm_tick >= 20) {
        pwm_tick = 0;
    }

    if (pwm_tick < duty) {
        LED = 1;
    } else {
        LED = 0;
    }
}

void delay_fade(unsigned int d) {
    unsigned int i, j;
    for (i = 0; i < d; i++)
        for (j = 0; j < 60; j++);
}

void main(void) {
    char dir = 1;
    TMOD &= 0xF0;
    TMOD |= 0x01; /* Mode 1 */
    TH0 = 0xFF;
    TL0 = 0xA4;
    ET0 = 1;
    EA = 1;
    TR0 = 1;

    while (1) {
        if (dir == 1) {
            duty++;
            if (duty >= 20) dir = -1;
        } else {
            duty--;
            if (duty == 0) dir = 1;
        }
        delay_fade(30); /* Fade rate */
    }
}
