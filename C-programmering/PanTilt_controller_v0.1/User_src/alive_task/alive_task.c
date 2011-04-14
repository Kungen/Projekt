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
#include "..\inc\binary.h"
#include "..\inc\glob_def.h"
#include "alive_task.h"

/*****************************    Defines    *******************************/

#define PF0		0

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void init_alive_task(void)
	  {
	  	// Init status led port.
	    INT8S dummy;
	    // Enable the GPIO port that is used for the on-board LED.
	    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;

	    // Do a dummy read to insert a few cycles after enabling the peripheral.
	    dummy = SYSCTL_RCGC2_R;

	    // Set the direction as output (PF0).
	    SET_BIT_HIGH(GPIO_PORTF_DIR_R, PF0);

	  	// Enable the GPIO pins for digital function (PF0 and PF1).
	    SET_BIT_HIGH(GPIO_PORTF_DEN_R, PF0);

	  	// Set pin high
	  	SET_BIT_HIGH(GPIO_PORTF_DATA_R, PF0);

	  	// Turn status led off
	  	LED_STATUS_OFF();
}

void alive_task(void *pvParameters)
{
	init_alive_task();
	vTaskDelay(MILLI_SEC(10));

	while( 1 )
	{
	  	// Toggles status LED every 500 ms.
	  	LED_STATUS_TOGGLE();

		vTaskDelay(MILLI_SEC(500));
	}
}

/****************************** End Of Module *******************************/












