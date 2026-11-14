#include <reg51.h>

/* Port 0 connected to Common Cathode 7-Segment display via 1k pull-ups */
/* Port 2 connected to 4x4 matrix keypad: P2.0-P2.3 Rows, P2.4-P2.7 Columns */

code unsigned char seg_lut[] = {
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F  /* 9 */
};

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 123; j++);
    }
}

unsigned char keypad_scan(void) {
    unsigned char row, col;
    unsigned char keypad_matrix[4][4] = {
        {1, 2, 3, 10},
        {4, 5, 6, 11},
        {7, 8, 9, 12},
        {14, 0, 15, 13}
    };

    for (row = 0; row < 4; row++) {
        P2 = ~(0x01 << row) | 0xF0; /* Drive one row LOW, keep cols HIGH */
        if ((P2 & 0xF0) != 0xF0) {  /* Check if any column is pulled LOW */
            delay_ms(15);           /* Debounce delay */
            if ((P2 & 0xF0) != 0xF0) {
                for (col = 0; col < 4; col++) {
                    if (!(P2 & (0x10 << col))) {
                        while ((P2 & 0xF0) != 0xF0); /* Wait for release */
                        return keypad_matrix[row][col];
                    }
                }
            }
        }
    }
    return 0xFF; /* No key pressed */
}

void display_digit(unsigned char val) {
    if (val < 10) {
        P0 = seg_lut[val];
    }
}

void main(void) {
    unsigned char key;
    P0 = 0x00; /* Blank display initially */

    while (1) {
        key = keypad_scan();
        if (key != 0xFF && key < 10) {
            display_digit(key);
        }
    }
}
