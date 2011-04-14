/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp_led.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 110215  JEPE009 Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/

#include "inc\lm3s6965.h"
#include "emp_type.h"
#include "emp_lcd.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
static inline void delay_nop(void)
{
    __asm("nop\n\tnop");
}

void delay_ms(INT32U ms)
{
	INT32U i;
	for (i = 0; i < (50000 * ms); i++){};
}

void delay_us(INT32U us)
{
	INT32U i;
	for (i = 0; i < (50 * us); i++){};
}

void lcd_nibble(char nibble)
{
	nibble = nibble & 0xf0;
	GPIO_PORTB_DATA_R = (GPIO_PORTB_DATA_R & 0xC3) | ((nibble >> 2) & 0x3C);
	LCD_E_ON;
	delay_nop();
	LCD_E_OFF;
	delay_nop();
}

void lcd_byte(char byte)
{
	lcd_nibble(byte);
	delay_us(3);
	byte = (byte & 0x0f) | ((byte << 4) & 0xf0);
	lcd_nibble(byte);
	delay_us(3);
}

void lcd_clear(void)
{
	lcd_byte(0x01);				//clear display
	delay_ms(2);
	lcd_byte(0x0C);				//display on
}

void lcd_print_char(char byte, char address)
{
	lcd_byte(address | 0x80);
	LCD_RS_ON;
	lcd_byte(byte);
	LCD_RS_OFF;
	lcd_byte(0x80);
}

void lcd_print_string(const char *text, char address)
{								/* Prints out strings from ROM to LCD. To Print a char array prefix variable with (char *) */
	lcd_byte(0x28);				//set cond: 4-bit, 2-line mode, 1 display line, 5-7 char font
	lcd_byte(address | 0x80);	//move cursor to location
	lcd_byte(0x0C);				//display on
	LCD_RS_ON;
	while( *text){
		lcd_byte(*text);		//print out the char
		*text++;				//keep going until \0
		}
	LCD_RS_OFF;
	lcd_byte(0x80);				//move cursor back to address 0
}

void lcd_print_integer(INT32U number, char address)
{
	if (number > 100000)
	{
		lcd_print_char(((number / 100000) + 48),address);
		lcd_print_char((((number / 10000) % 10) + 48),(address + 1));
		lcd_print_char((((number / 1000) % 10) + 48),(address + 2));
		lcd_print_char((((number / 100) % 10) + 48),(address + 3));
		lcd_print_char((((number / 10) % 10) + 48),(address + 4));
		lcd_print_char((((number) % 10) + 48),(address + 5));
	}
}

void init_lcd(void)
{
	LCD_RS_OFF;
	LCD_RW_OFF;
	LCD_E_OFF;
	delay_ms(15);
	lcd_nibble(0x30);
	delay_ms(5);
	lcd_nibble(0x30);
	delay_ms(2);
	lcd_nibble(0x20);
	delay_ms(2);
	lcd_byte(0x01);
	delay_ms(2);
	lcd_byte(0x28);
	lcd_byte(0x08);
	lcd_byte(0x06);
	lcd_byte(0x01);
	delay_ms(2);
	lcd_byte(0x0C);
}

/****************************** End Of Module *******************************/












