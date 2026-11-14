#include <reg51.h>

sbit LED = P1^0;
volatile unsigned int ms_count = 0;

void timer0_isr(void) interrupt 1 {
    /* Reload for 1 ms tick: 65536 - 922 = 64614 (0xFC66) */
    TH0 = 0xFC;
    TL0 = 0x66;

    ms_count++;
    if (ms_count >= 1000) {
        LED = ~LED; /* Toggle LED state */
        ms_count = 0;
    }
}

void main(void) {
    TMOD &= 0xF0;
    TMOD |= 0x01; /* Timer 0 in 16-bit Mode 1 */

    TH0 = 0xFC;
    TL0 = 0x66;

    ET0 = 1; /* Enable Timer 0 interrupt */
    EA = 1;  /* Enable global interrupts */
    TR0 = 1; /* Start Timer 0 */

    while (1) {
        /* Background CPU tasks executed without timing jitter */
    }
}
