/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: lcd_port.c
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
#include "inc\lm3s6965.h"
#include "..\inc\emp_type.h"
#include "..\inc\binary.h"
#include "..\cpu\cpu.h"
#include "lcd_port.h"

/*****************************    Defines    *******************************/


#define LCD_RS			7			// PA7
#define	LCD_RW			6			// PA6
#define LCD_E			6			// PB6
#define LCD_PORT_MASK	0x3C

#define DELAY_US(x)		(x*(FCPU/1000000))/3

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
/* Definemens for GPIO ports */ 

void lcd_rs_low(void)
{
	SET_BIT_LOW(GPIO_PORTA_DATA_R,LCD_RS);
}

void lcd_rs_high(void)
{
	SET_BIT_HIGH(GPIO_PORTA_DATA_R,LCD_RS);
}

void lcd_strobe(void)
{
	// Timings constrains for LCD_E pin
	// LCD_E pin, Tcycle, min = 550nS, Tw, min = 220ns 
	SET_BIT_HIGH(GPIO_PORTB_DATA_R,LCD_E);
	// 50 Mhz, Tw, min 220ns => 11 nops
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	SET_BIT_LOW(GPIO_PORTB_DATA_R,LCD_E);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
}

void lcd_write_port(INT8U value)
{
	GPIO_PORTB_DATA_R = ((value & 0x0F)<< 2) | (GPIO_PORTB_DATA_R & ~(LCD_PORT_MASK));
}

void lcd_write_4bit_mode(INT8U c)
/*****************************************************************************
*   Input    :	c: character. 
*   Output   :	-
*   Function : 	write a character to the LCD in 4 bit mode
******************************************************************************/
{
	 
	GPIO_PORTB_DATA_R = ((c & 0xF0)>> 2) | (GPIO_PORTB_DATA_R & ~(LCD_PORT_MASK));
	lcd_strobe();
	GPIO_PORTB_DATA_R = ((c & 0x0F)<< 2) | (GPIO_PORTB_DATA_R & ~(LCD_PORT_MASK));
	lcd_strobe();
}



void lcd_port_setup(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	LCD port setup.
******************************************************************************/	
{
		INT8S dummy;
	  
		// LCD_RS PA7 
		// LCD_RW PA6
		// LCD_E  PB6 // Strobe
		// LCD_D4..D7 // PB2 .. PB5
		
		// Enable the GPIO port that is used for LCD_RW.
	  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
	  // Do a dummy read to insert a few cycles after enabling the peripheral.
	  dummy = SYSCTL_RCGC2_R;
	  // Set the direction as output.  
	  SET_BIT_HIGH(GPIO_PORTA_DIR_R, LCD_RW);
	  // Enable the GPIO pins for digital function.
	  SET_BIT_HIGH(GPIO_PORTA_DEN_R, LCD_RW);
	  // Set pin low
	  SET_BIT_LOW(GPIO_PORTA_DATA_R, LCD_RW);
	  
	  // Enable the GPIO port that is used for LCD_RS.
	  // Set the direction as output.  
	  SET_BIT_HIGH(GPIO_PORTA_DIR_R, LCD_RS);
	  // Enable the GPIO pins for digital function.
	  SET_BIT_HIGH(GPIO_PORTA_DEN_R, LCD_RS);
	  // Set pin high
	  SET_BIT_HIGH(GPIO_PORTA_DATA_R, LCD_RS);
	  
	  // Enable the GPIO port that is used for LCD_E (Strobe).
 	  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
 	  // Do a dummy read to insert a few cycles after enabling the peripheral.
 	  dummy = SYSCTL_RCGC2_R;
	  
	  // Set the direction as output.  
	  SET_BIT_HIGH(GPIO_PORTB_DIR_R, LCD_E);
	  // Enable the GPIO pins for digital function.
	  SET_BIT_HIGH(GPIO_PORTB_DEN_R, LCD_E);
	  // Set pin low
	  SET_BIT_LOW(GPIO_PORTB_DATA_R, LCD_E);
	  	  
	  // Set the direction as output for LCD_D4 .. LCD_D7  
	  GPIO_PORTB_DIR_R &=  ~(LCD_PORT_MASK);
	  GPIO_PORTB_DIR_R |= LCD_PORT_MASK;
	  // Enable digital function for LCD_E and LCD_D4 .. LCD_D7
	  GPIO_PORTB_DEN_R &=  ~(LCD_PORT_MASK);
	  GPIO_PORTB_DEN_R |= LCD_PORT_MASK;
}


void inline lcd_delay_us(INT32U time)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function :	This function makes a delay.  	
******************************************************************************/
{
	
	time = DELAY_US(time); // Scale vaule.
	
	asm("           mov r3, %0 \n\t"    	// load time value
	    "tloop:		sub r3, #1 \n\t"		// decrement loop counter
	    "           cmp r3, #0 \n\t"		// check if reached zero
	    "           bne tloop  \n\t"		// jump to loop label if not done
	                :
	                :"r" (time)
	                ); 
	          					
}

/****************************** End Of Module *******************************/












