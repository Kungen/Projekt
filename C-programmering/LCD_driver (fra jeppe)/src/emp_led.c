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
#include "emp_led.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

extern void set_emp_leds(INT8U value)
{
	LED_RED_OFF;
	LED_GREEN_OFF;
	LED_YELLOW_OFF;

	switch (value)
	{
	case 0:
		break;
	case 1:
		LED_GREEN_ON;
		break;
	case 2:
		LED_YELLOW_ON;
		break;
	case 3:
		LED_GREEN_ON;
		LED_YELLOW_ON;
		break;
	case 4:
		LED_RED_ON;
		break;
	case 5:
		LED_RED_ON;
		LED_GREEN_ON;
		break;
	case 6:
		LED_RED_ON;
		LED_YELLOW_ON;
		break;
	case 7:
		LED_RED_ON;
		LED_YELLOW_ON;
		LED_GREEN_ON;
		break;
	default:
		LED_RED_OFF;
		LED_GREEN_OFF;
		LED_YELLOW_OFF;
		break;
	}
}

/****************************** End Of Module *******************************/












