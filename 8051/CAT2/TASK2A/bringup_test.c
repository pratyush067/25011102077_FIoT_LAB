#include <reg51.h>

/* AT89S52 Minimum System Bring-Up Test Program
 * Toggles Port 1 to verify crystal oscillation and core execution.
 */

void delay_test(void) {
    unsigned int i, j;
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 120; j++);
    }
}

void main(void) {
    while (1) {
        P1 = 0xFF; /* Drive all Port 1 pins HIGH */
        delay_test();
        P1 = 0x00; /* Drive all Port 1 pins LOW */
        delay_test();
    }
}
