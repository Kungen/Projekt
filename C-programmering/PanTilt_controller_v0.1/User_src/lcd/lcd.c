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

#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"
#include "..\inc\emp_type.h"
#include "..\inc\binary.h"
#include "..\inc\glob_def.h"
#include "..\inc\application.h"
#include "lcd_port.h"
#include "lcd.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

typedef struct  
{
	INT8U	display_char;
	INT8U	display_dirty_bit;
} LCD_BUFFER ;

LCD_BUFFER	display_buffer[COL_SIZE][ROW_SIZE];
 
INT8S col_pointer = 0;
INT8S row_pointer = 0;

INT8S last_col_pointer = -1;

/*****************************   Functions   *******************************/

BOOLEAN display_buffer_write_char(INT8U col_p, INT8U row_p, INT8U ch)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{

	BOOLEAN return_value = TRUE;
	
	xSemaphoreTake(lcd_buffer_mutex, portMAX_DELAY );
	if (!(ch == display_buffer[col_p][row_p].display_char ))
	{
		display_buffer[col_p][row_p].display_char = ch;
		display_buffer[col_p][row_p].display_dirty_bit = TRUE;
	}
	xSemaphoreGive(lcd_buffer_mutex);
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
		xSemaphoreTake(lcd_buffer_mutex, portMAX_DELAY );
		if (!(*str == display_buffer[col_p][row_p].display_char))
		{
			display_buffer[col_p][row_p].display_char = *str;
			display_buffer[col_p][row_p].display_dirty_bit = TRUE;
		}
		xSemaphoreGive(lcd_buffer_mutex);
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
	xSemaphoreTake(lcd_buffer_mutex, portMAX_DELAY );
	for (row=0; row < ROW_SIZE; row++)
	{
		for (col=0; col < COL_SIZE; col++)
		{
			display_buffer[col][row].display_char = ' ';
			display_buffer[col][row].display_dirty_bit = FALSE;
		}
	}
	xSemaphoreGive(lcd_buffer_mutex);
}

void display_init(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	lcd_port_setup();
	lcd_init_display();
}


void lcd_task(void *pvParameters)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	INT8U	display_updated = FALSE;
	
	display_init();
	vTaskDelay(MILLI_SEC(10)); // Wait 10 milli sec.
	
	while(1)
	{
		display_updated = FALSE;
		do
		{
			if (col_pointer >= COL_SIZE)
			{
				// next line
				col_pointer = 0;
				row_pointer++;
				last_col_pointer = -1;

				if (row_pointer >= ROW_SIZE)
				{
					// Goto start of display.
					col_pointer = 0;
					row_pointer = 0;
					display_updated = TRUE;
				}
			}	
			xSemaphoreTake(lcd_buffer_mutex, portMAX_DELAY );
			if (display_buffer[col_pointer][row_pointer].display_dirty_bit == TRUE)
			{
				xSemaphoreTake(common_pins_mutex, portMAX_DELAY );
				if (!(col_pointer == last_col_pointer))
				{
					display_buffer_goto_xy(col_pointer, row_pointer);
					lcd_delay_us(40);
					lcd_rs_high();			// write character
				}
				lcd_write_4bit_mode(display_buffer[col_pointer][row_pointer].display_char);
				xSemaphoreGive(common_pins_mutex);
				display_buffer[col_pointer][row_pointer].display_dirty_bit = FALSE;
				last_col_pointer = col_pointer + 1;
				display_updated = TRUE;
			}
			xSemaphoreGive(lcd_buffer_mutex);
			col_pointer++;
		}
		while (!display_updated);
		
		vTaskDelay(MILLI_SEC(5)); // Wait 5 milli sec.
	}
}
/****************************** End Of Module *******************************/












