#include <reg51.h>

sbit RS = P2^0;
sbit EN = P2^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 123; j++);
}

static void lcd_pulse(void) {
    EN = 1; delay_ms(1); EN = 0; delay_ms(1);
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
    lcd_send_nibble(0x20);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    delay_ms(5);
}

void lcd_goto(unsigned char row, unsigned char col) {
    if (row == 0) lcd_cmd(0x80 + (col & 0x0F));
    else lcd_cmd(0xC0 + (col & 0x0F));
}

void lcd_puts(char *s) {
    while (*s) lcd_data(*s++);
}

void lcd_print_number(unsigned int val) {
    char buf[6];
    int i = 0;
    if (val == 0) { lcd_data('0'); return; }
    while (val > 0) {
        buf[i++] = (val % 10) + '0';
        val /= 10;
    }
    while (i > 0) {
        lcd_data(buf[--i]);
    }
}

void main(void) {
    unsigned int count = 0;
    lcd_init();

    lcd_goto(0, 0);
    lcd_puts("Count Value:");

    while (1) {
        lcd_goto(1, 0);
        lcd_puts("Val: ");
        lcd_print_number(count);
        lcd_puts("     "); /* Clear trailing characters */
        count++;
        delay_ms(500);
    }
}
