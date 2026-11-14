#include <reg51.h>

void uart_init(void) {
    TMOD &= 0x0F;
    TMOD |= 0x20; /* Timer 1 Mode 2 (8-bit auto-reload) */
    TH1 = 0xFD;   /* 9600 Baud @ 11.0592 MHz */
    SCON = 0x50;  /* 8-bit UART, Receive Enabled */
    TR1 = 1;      /* Start Timer 1 */
    TI = 1;       /* Prime transmit flag */
}

void uart_send_char(char c) {
    while (TI == 0);
    TI = 0;
    SBUF = c;
}

void uart_send_string(char *str) {
    while (*str) {
        uart_send_char(*str++);
    }
}

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 123; j++);
    }
}

void main(void) {
    uart_init();

    while (1) {
        uart_send_string("Hello from 8051\r\n");
        delay_ms(1000);
    }
}
