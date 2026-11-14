#ifndef LCD_4BIT_H
#define LCD_4BIT_H

void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char d);
void lcd_puts(char *str);
void delay_ms(unsigned int ms);

#endif

