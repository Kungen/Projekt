/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: lcd.h
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

#ifndef _LCD_H
  #define _LCD_H

/***************************** Include files *******************************/
#include "..\inc\emp_type.h"
/*****************************    Defines    *******************************/

/* LCD character size */
#define COL_SIZE				16
#define ROW_SIZE				2

/* LCD Function definemens */
//#define	CLEAR_DISPLAY		0x01
//#define BLINK_ON				0x0D
//#define DISPLAY_ON			0x0C

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void display_init(void);
/*****************************************************************************
*   Input    : 	None
*   Output   : 	None
*   Function : 	This function init. the LCD-Display.
******************************************************************************/

BOOLEAN display_buffer_write_char(INT8U col_p, INT8U row_p, INT8U ch);
/*****************************************************************************
*   Input    : 	col_p: column position
* 							row_p: row position
* 							ch: character
*   Output   : 	Always returns TRUE
*   Function : 	This function puts a character in the display buffer according 
* 							to colum and row position.
*****************************************************************************/

BOOLEAN display_buffer_write_string(INT8U col_p, INT8U row_p, INT8U *str);
/*****************************************************************************
*   Input    : 	col_p: column position
* 							row_p: row position
* 							str: string
*   Output   : 	Always returns TRUE
*   Function : 	This function write a string in the display buffer according 
* 							to colum and row position.
******************************************************************************/

void lcd_task(void *pvParameters);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	The display task, must be called every 10 ms.
*   						Displays the characters in buffer one by one every time 
* 							this task is called.	
******************************************************************************/
/****************************** End Of Module *******************************/
#endif
