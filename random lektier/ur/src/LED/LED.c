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
#include "..\event\event.h"
#include "LED.h"
#include "..\RTCS\rtcs.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U number = 1;

/*****************************   Functions   *******************************/

void init_LED_task(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	Push button setup
******************************************************************************/
{
	INT8U	dummy;

	// Enable the GPIO port that is used for the on-board LED.
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	// Do a dummy read to insert a few cycles after enabling the peripheral.
	dummy = SYSCTL_RCGC2_R;

	GPIO_PORTD_DIR_R = 0x40;
	GPIO_PORTG_DIR_R = 0x03;
	GPIO_PORTD_DEN_R = 0x40;
	GPIO_PORTG_DEN_R = 0x03;

	GPIO_PORTG_DATA_R |= (0x03);
	GPIO_PORTD_DATA_R |= (0x40);
}

void LED_task(void)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : The button state machine.
******************************************************************************/
{
//	number++;
	if(event_get(DREHIMPULSGEBER_EVENTS) == CW)
	{
		number++;
	}
	else if(event_get(DREHIMPULSGEBER_EVENTS) == CCW)
	{
		number--;
	}
	if(number == 0)
	{
		number = 8;
	}
	if(number == 9)
	{
		number = 1;
	}
	if(number > 4)
	{
		GPIO_PORTD_DATA_R &= ~(0x40);
	}
	else
	{
		GPIO_PORTD_DATA_R |= 0x40;
	}

	if(number == 3 || number == 4 || number == 7 || number == 8)
	{
		GPIO_PORTG_DATA_R &= ~(0x01);
	}
	else
	{
		GPIO_PORTG_DATA_R |= 0x01;
	}

	if(number == 2 || number == 4 || number == 6 || number == 8)
	{
		GPIO_PORTG_DATA_R &= ~(0x02);
	}
	else
	{
		GPIO_PORTG_DATA_R |= 0x02;
	}
	_stop(LED_TASK);
}

/****************************** End Of Module *******************************/
