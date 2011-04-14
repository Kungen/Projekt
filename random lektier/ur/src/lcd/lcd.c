/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: lcd.c
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

/***************************** Include files *******************************/

#include "..\inc\emp_type.h"
#include "..\inc\binary.h"
#include "..\inc\glob_def.h"
#include "lcd_port.h"
#include "lcd.h"
#include "..\RTCS\rtcs.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U	display_buffer[COL_SIZE][ROW_SIZE];
INT8U col_pointer = 0;
INT8U row_pointer = 0;

/*****************************   Functions   *******************************/

BOOLEAN display_buffer_write_char(INT8U col_p, INT8U row_p, INT8U ch)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{

	BOOLEAN return_value = TRUE;
	
	display_buffer[col_p][row_p] = ch;
		
	return return_value;
}

BOOLEAN display_buffer_write_string(INT8U col_p, INT8U row_p, INT8U *str)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	BOOLEAN return_value = TRUE;
	
	while( *str )
	{
		display_buffer[col_p][row_p] = *str;
		col_p++;
		str++;
	}

	return return_value; 
}


BOOLEAN lcd_function(INT8U function)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	BOOLEAN	return_value = TRUE;  

		lcd_rs_low();				// write control bytes
		lcd_write_4bit_mode(function);

	return return_value;
}


BOOLEAN display_buffer_goto_xy(INT8U col_p, INT8U row_p)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U pos;
	INT8U	return_value = FALSE;

	if ((col_p < COL_SIZE) && (row_p < ROW_SIZE))
	{
		pos = row_p*0x40 + col_p;
 		pos |= 0x80;
		return_value = lcd_function(pos);
  	}
	return return_value;
}

void lcd_init_display(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	Initialise the LCD - put into 4 bit mode
******************************************************************************/
{
	INT8U col;
	INT8U row;
	
	lcd_delay_us(15000);
	lcd_rs_low();						// write control bytes
	lcd_write_port(0x03);  	// attention!
  lcd_strobe();
	lcd_delay_us(5000);
	lcd_strobe();
	lcd_delay_us(100);
	lcd_strobe();
	lcd_delay_us(5000);
	lcd_write_port(0x2);			// set 4 bit mode
	lcd_strobe();
	lcd_delay_us(40);
	lcd_write_4bit_mode(0x28);	// 4 bit mode, 1/16 duty, 5x8 font
	lcd_delay_us(40);
	lcd_write_4bit_mode(0x08);	// display off
	lcd_delay_us(40);
	lcd_write_4bit_mode(0x0C);	// display on, blink curson on
	lcd_delay_us(40);
	lcd_write_4bit_mode(0x06);	// entry mode
	lcd_delay_us(40);
	lcd_write_4bit_mode(0x01);	// Home
	lcd_delay_us(40);

	// clear display
	for (row=0; row < ROW_SIZE; row++)
	{
		for (col=0; col < COL_SIZE; col++)
		{
			display_buffer[col][row] = ' ';
		}
	}
	
}

void init_lcd_task(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	lcd_port_setup();
	lcd_init_display();
	_start(LCD_TASK, MILLI_SEC(0));
}


void lcd_task(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{

	if (col_pointer >= COL_SIZE)
	{
		// next line
		col_pointer = 0;
		row_pointer++;

		if (row_pointer >= ROW_SIZE)
		{
			// Goto start of display.
			col_pointer = 0;
			row_pointer = 0;
			display_buffer_goto_xy(col_pointer, row_pointer);
		}
		else
		{
			display_buffer_goto_xy(col_pointer,row_pointer);
		}
	}
	else
	{
		// Can't write characters to display in same tick period as control commands
		lcd_rs_high();			// write characters	
		lcd_write_4bit_mode(display_buffer[col_pointer][row_pointer]);
		col_pointer++;
	}
	_wait(MILLI_SEC(2));
}

/****************************** End Of Module *******************************/












