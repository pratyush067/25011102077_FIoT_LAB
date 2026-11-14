#include <reg51.h>
#include "delay.h"

sbit TEST_PIN = P1^0;

void main(void) {
    while (1) {
        TEST_PIN = 1;
        delay_ms(100); /* 100 ms pulse width */
        TEST_PIN = 0;
        delay_ms(100);
    }
}
