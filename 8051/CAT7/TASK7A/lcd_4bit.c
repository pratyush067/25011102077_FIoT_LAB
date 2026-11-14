#include <reg51.h>
#include "lcd_4bit.h"

sbit RS = P2^0;
sbit EN = P2^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 123; j++);
    }
}

static void lcd_pulse(void) {
    EN = 1;
    delay_ms(1);
    EN = 0;
    delay_ms(1);
}

static void lcd_send_nibble(unsigned char n) {
    P2 = (P2 & 0x0F) | (n & 0xF0);
    lcd_pulse();
}

void lcd_cmd(unsigned char cmd) {
    RS = 0;
    lcd_send_nibble(cmd & 0xF0);
    lcd_send_nibble((cmd << 4) & 0xF0);
    delay_ms(2);
}

void lcd_data(unsigned char d) {
    RS = 1;
    lcd_send_nibble(d & 0xF0);
    lcd_send_nibble((d << 4) & 0xF0);
    delay_ms(1);
}

void lcd_init(void) {
    delay_ms(20);
    RS = 0;
    lcd_send_nibble(0x20); /* Select 4-bit mode */
    lcd_cmd(0x28);         /* 4-bit, 2 lines, 5x8 font */
    lcd_cmd(0x0C);         /* Display ON, cursor OFF */
    lcd_cmd(0x06);         /* Increment cursor */
    lcd_cmd(0x01);         /* Clear display */
    delay_ms(5);
}

void lcd_puts(char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

void main(void) {
    lcd_init();
    lcd_cmd(0x80); /* Row 1 */
    lcd_puts("IoT Lab 8051");
    lcd_cmd(0xC0); /* Row 2 */
    lcd_puts("LCD Driver OK");

    while (1);
}
