/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: button.c
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
#include "..\inc\glob_def.h"
#include "..\inc\binary.h"
#include "..\rtcs\rtcs.h"
#include "..\event\event.h"
#include "..\queue\queue.h"
#include "..\sw_timer\sw_timer.h"
//#include "..\systick\systick.h"
#include "button.h"
#include "..\lcd\lcd.h"


/*****************************    Defines    *******************************/
#define PC5		5

#define CLEAR_BUTTON_INT_REQUEST 			{SET_BIT_HIGH(GPIO_PORTC_ICR_R, PC5);}
#define ENABLE_BUTTON_INT					{SET_BIT_HIGH(GPIO_PORTC_IM_R, PC5);}
#define DISABLE_BUTTON_INT					{SET_BIT_LOW(GPIO_PORTC_IM_R, PC5);}

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U button_int = 0;

enum button_states button_state = SELECT_MODE;

/*****************************   Functions   *******************************/

void button_gpio_init(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	Push button setup
******************************************************************************/
{
  	INT8U	dummy;
	
		// Enable the GPIO port that is used for the Select button.
	  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;

	  // Do a dummy read to insert a few cycles after enabling the peripheral.
	  dummy = SYSCTL_RCGC2_R;

	  // Set the direction as input (PC5).  
	  SET_BIT_LOW(GPIO_PORTC_DIR_R, PC5);
	  
	  // Enable the GPIO pins for digital function (PF0 and PF1).
	  SET_BIT_HIGH(GPIO_PORTC_DEN_R, PC5);

	  // disbale internal pull-up (PC5.  
	  SET_BIT_HIGH(GPIO_PORTC_PUR_R, PC5);
}

void button_int_setup(void)
{
	// Interrupt on Port PB1

	// Edge trigger
	SET_BIT_LOW(GPIO_PORTC_IS_R, PC5);
	// both edges
//	SET_BIT_HIGH(GPIO_PORTC_IBE_R, PC5);

	// negative 	edge
	SET_BIT_LOW(GPIO_PORTC_IEV_R, PC5);

	// Clear interrupt request
	CLEAR_BUTTON_INT_REQUEST;

	// NVIC setup
	// program NVIC, vector number 17, Interrupt Number = 1
	// Clear pending interrupt
	NVIC_UNPEND0_R |= NVIC_UNPEND0_INT2;
	// Set Priority to 0x10, first clear then set.
	NVIC_PRI0_R &= ~(NVIC_PRI0_INT2_M);
	NVIC_PRI0_R |= (NVIC_PRI0_INT2_M & (0x10<<NVIC_PRI0_INT2_S));
	// enable NVIC interrupt
	NVIC_EN0_R |= NVIC_EN0_INT2;

	// Enable int
	ENABLE_BUTTON_INT;
}

void portc_isr(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	This digi switch ISR function is called every time the user
								turns the	digi switch if the INT is enabled.
******************************************************************************/
{
	button_int++;
	// Clear interrupt request
	CLEAR_BUTTON_INT_REQUEST;
}

void init_button_task(void)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : The function initialise the button task.
******************************************************************************/
{
	button_gpio_init();
	button_int_setup();
	
	_start(BUTTON_TASK,MILLI_SEC(100));
}

enum button_states get_menu_state(void)
{
	return button_state;
}

void button_task(void)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : The button task.
******************************************************************************/
{
	if (button_int > 0)
	{
		DISABLE_BUTTON_INT;
		button_int = 0;
		ENABLE_BUTTON_INT;
		if (button_state == SELECT_MODE)
		{
			button_state = SHOW_DATA_MODE;
		}
		else
		{
			button_state = SELECT_MODE;
		}
	}
	_wait(MILLI_SEC(100));
}

/****************************** End Of Module *******************************/












