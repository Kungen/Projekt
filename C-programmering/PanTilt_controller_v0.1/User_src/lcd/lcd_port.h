/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: lcd_port.h
*
* PROJECT....: ECP
*
* DESCRIPTION:
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef _LCD_PORT_H
  #define _LCD_PORT_H

/***************************** Include files *******************************/
#include "..\inc\emp_type.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
void lcd_port_setup(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	LCD port setup.
******************************************************************************/	


void lcd_delay_us(INT32U time);
/*****************************************************************************
*   Input    : 	delay in micro sec.
*   Output   : 	-
*   Function :	This function makes a delay.  	
******************************************************************************/


void lcd_write_4bit_mode(INT8U c);
/*****************************************************************************
*   Input    :	c: character. 
*   Output   :	-
*   Function : 	Writes a 8 bit character to the LCD in 4 bit mode
******************************************************************************/

void lcd_write_port(INT8U value);
/*****************************************************************************
*   Input    :	c: character. 
*   Output   :	-
*   Function : 	write a character to the LCD in 4 bit mode
******************************************************************************/


void lcd_rs_low(void);

void lcd_strobe(void);

void lcd_rs_high(void);


/****************************** End Of Module *******************************/
#endif
