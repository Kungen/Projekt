/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp_led.c
*
* PROJECT....: Semesterproject Rob-tek 4.th semester Group 3.
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 110215  JEPE  Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/

#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"
#include "..\inc\lm3s6965.h"
#include "..\inc\emp_type.h"
#include "..\inc\glob_def.h"
#include "emp_led.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/


void init_emp_led(void)
{
	INT8S dummy;
	  // Enable the GPIO port that is used for the on-board LED.
	  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOG;
	  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;

	  // Do a dummy read to insert a few cycles after enabling the peripheral.
	  dummy = SYSCTL_RCGC2_R;

	  // Set the direction as output (PF0).
	  GPIO_PORTG_DIR_R = 0x01 | 0x02;
	  GPIO_PORTD_DIR_R = 0x40;

	  // Enable the GPIO pins for digital function (PF0 and PF1).
	  GPIO_PORTG_DEN_R = 0x01 | 0x02;
	  GPIO_PORTD_DEN_R = 0x40;

	  // Turn LEDs off (active low)
	  LED_GREEN_OFF();
	  LED_RED_OFF();
	  LED_YELLOW_OFF();
}

void set_emp_leds(INT8U value)
{
	LED_RED_OFF();
	LED_GREEN_OFF();
	LED_YELLOW_OFF();

	switch (value)
	{
	case 0:
		break;
	case 1:
		LED_GREEN_ON();
		break;
	case 2:
		LED_YELLOW_ON();
		break;
	case 3:
		LED_GREEN_ON();
		LED_YELLOW_ON();
		break;
	case 4:
		LED_RED_ON();
		break;
	case 5:
		LED_RED_ON();
		LED_GREEN_ON();
		break;
	case 6:
		LED_RED_ON();
		LED_YELLOW_ON();
		break;
	case 7:
		LED_RED_ON();
		LED_YELLOW_ON();
		LED_GREEN_ON();
		break;
	default:
		LED_RED_OFF();
		LED_GREEN_OFF();
		LED_YELLOW_OFF();
		break;
	}
}

/****************************** End Of Module *******************************/












