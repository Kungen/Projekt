/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef _EMP_LCD_H
  #define _EMP_LCD_H

/***************************** Include files *******************************/

#include "inc\lm3s6965.h"

/*****************************    Defines    *******************************/

#define LCD_RS_OFF GPIO_PORTA_DATA_R &= ~(0x80)
#define LCD_RS_ON GPIO_PORTA_DATA_R |= 0x80

#define LCD_E_OFF GPIO_PORTB_DATA_R &= ~(0x40)
#define LCD_E_ON GPIO_PORTB_DATA_R |= 0x40

#define LCD_RW_OFF GPIO_PORTA_DATA_R &= ~(0x40)
#define LCD_RW_ON GPIO_PORTA_DATA_R |= 0x40


/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void init_lcd(void);

void lcd_print_string(const char *text, char address);

void lcd_byte(char byte);

void lcd_nibble(char nibble);

void lcd_clear(void);

void lcd_print_char(char byte, char address);

void lcd_print_integer(INT32U number, char address);

/****************************** End Of Module *******************************/
#endif
