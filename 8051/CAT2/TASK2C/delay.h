#ifndef DELAY_H
#define DELAY_H

/**
 * @brief Calibrated software delay for AT89S52 clocked at 11.0592 MHz.
 * Machine cycle: 12 clock periods = 1.085 us.
 */
void delay_ms(unsigned int ms);
void delay_sec(unsigned char sec);

#endif /* DELAY_H */
