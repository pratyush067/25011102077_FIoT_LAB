#include <reg51.h>

code unsigned char seg_lut[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 123; j++);
    }
}

unsigned char keypad_scan(void) {
    unsigned char row, col;
    unsigned char map[4][4] = {
        {1, 2, 3, 10},
        {4, 5, 6, 11},
        {7, 8, 9, 12},
        {14, 0, 15, 13}
    };
    for (row = 0; row < 4; row++) {
        P2 = ~(0x01 << row) | 0xF0;
        if ((P2 & 0xF0) != 0xF0) {
            delay_ms(15);
            if ((P2 & 0xF0) != 0xF0) {
                for (col = 0; col < 4; col++) {
                    if (!(P2 & (0x10 << col))) {
                        while ((P2 & 0xF0) != 0xF0);
                        return map[row][col];
                    }
                }
            }
        }
    }
    return 0xFF;
}

void display_digit(unsigned char val) {
    if (val < 10) P0 = seg_lut[val];
    else P0 = 0x00;
}

void running_led(void) {
    unsigned char pat = 0x01, i;
    for (i = 0; i < 4; i++) {
        P1 = (P1 & 0xF0) | pat;
        delay_ms(150);
        pat <<= 1;
        if (keypad_scan() != 0xFF) return;
    }
}

void binary_counter(void) {
    unsigned char i;
    for (i = 0; i < 16; i++) {
        P1 = (P1 & 0xF0) | i;
        delay_ms(200);
        if (keypad_scan() != 0xFF) return;
    }
}

void alternate_led(void) {
    P1 = (P1 & 0xF0) | 0x0A;
    delay_ms(200);
    P1 = (P1 & 0xF0) | 0x05;
    delay_ms(200);
}

void blink_all(void) {
    P1 = (P1 & 0xF0) | 0x0F;
    delay_ms(200);
    P1 = (P1 & 0xF0) | 0x00;
    delay_ms(200);
}

void led_control(unsigned char key) {
    switch (key) {
        case 1: P1 = (P1 & 0xF0) | 0x01; break;
        case 2: P1 = (P1 & 0xF0) | 0x02; break;
        case 3: P1 = (P1 & 0xF0) | 0x04; break;
        case 4: P1 = (P1 & 0xF0) | 0x08; break;
        case 5: running_led(); break;
        case 6: alternate_led(); break;
        case 7: binary_counter(); break;
        case 8: blink_all(); break;
        case 9: P1 = (P1 & 0xF0) | 0x00; break;
        case 0: P1 = (P1 & 0xF0) | 0x00; P0 = 0x00; break;
    }
}

void main(void) {
    unsigned char current_key = 0;
    P0 = 0x00;
    P1 = 0x00;

    while (1) {
        unsigned char k = keypad_scan();
        if (k != 0xFF && k < 10) {
            current_key = k;
            display_digit(current_key);
        }
        led_control(current_key);
    }
}
