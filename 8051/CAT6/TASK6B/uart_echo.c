#include <reg51.h>

void uart_init(void) {
    TMOD &= 0x0F;
    TMOD |= 0x20; /* Timer 1 Mode 2 */
    TH1 = 0xFD;   /* 9600 Baud */
    SCON = 0x50;  /* 8-bit UART, REN = 1 */
    TR1 = 1;
    TI = 1;
}

char uart_read_char(void) {
    while (RI == 0);
    RI = 0;
    return SBUF;
}

void uart_send_char(char c) {
    while (TI == 0);
    TI = 0;
    SBUF = c;
}

void main(void) {
    char ch;
    uart_init();

    while (1) {
        ch = uart_read_char();
        uart_send_char(ch); /* Immediate echo */
    }
}
