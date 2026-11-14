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

unsigned char keypad_scan(void) {
    unsigned char r, c;
    unsigned char map[4][4] = {
        {1, 2, 3, 10},
        {4, 5, 6, 11},
        {7, 8, 9, 12},
        {14, 0, 15, 13}
    };
    for (r = 0; r < 4; r++) {
        P1 = ~(0x01 << r) | 0xF0;
        if ((P1 & 0xF0) != 0xF0) {
            delay_ms(15);
            if ((P1 & 0xF0) != 0xF0) {
                for (c = 0; c < 4; c++) {
                    if (!(P1 & (0x10 << c))) {
                        while ((P1 & 0xF0) != 0xF0);
                        return map[r][c];
                    }
                }
            }
        }
    }
    return 0xFF;
}

void main(void) {
    unsigned char cur_row = 0;
    unsigned char cur_col = 0;
    unsigned char k;

    lcd_init();
    lcd_goto(cur_row, cur_col);
    lcd_data('*');

    while (1) {
        k = keypad_scan();
        if (k != 0xFF) {
            /* Erase old position */
            lcd_goto(cur_row, cur_col);
            lcd_data(' ');

            /* Process movement */
            if (k == 2) { /* UP */
                cur_row = 0;
            } else if (k == 8) { /* DOWN */
                cur_row = 1;
            } else if (k == 4) { /* LEFT */
                if (cur_col > 0) cur_col--;
            } else if (k == 6) { /* RIGHT */
                if (cur_col < 15) cur_col++;
            }

            /* Draw at new position */
            lcd_goto(cur_row, cur_col);
            lcd_data('*');
        }
    }
}
