#include <xc.h>
#define EN RE0
#define RS RE1
#define RW RE2
#define LCD PORTD

#define LCD_8BIT 


void delay(int ms);
void lcd_enable();
void lcd_command(char a);
void lcd_data(char a);
void lcd_string(char *a);
void lcd_numbers(int a); //for numbers
void lcd_position(int row,int column);
void lcd_displayon_cursoron();
void lcd_displayon_cursoroff();
void lcd_displayoff_cursoron();
void lcd_displayoff_cursoroff();
void lcd_clear();
void lcd_initialize();

