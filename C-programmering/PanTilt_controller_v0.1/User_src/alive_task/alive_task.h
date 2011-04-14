/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp_led.h
*
* PROJECT....: Semesterproject Rob-tek 4.th semester Group 3.
*
* DESCRIPTION: GPIO init of the status diode on the luminary kit and alive_task (toggles diode every 500ms).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 110323  JEPE  Module created.
*
*****************************************************************************/

#ifndef _ALIVE_TASK_H
  #define _ALIVE_TASK_H

/***************************** Include files *******************************/
#include "..\inc\emp_type.h"
/*****************************    Defines    *******************************/

#define LED_STATUS_ON() 	GPIO_PORTF_DATA_R &= ~(0x01)
#define LED_STATUS_OFF() 	GPIO_PORTF_DATA_R |= 0x01
#define LED_STATUS_TOGGLE()	GPIO_PORTF_DATA_R ^= 0x01

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void alive_task(void *pvParameters);
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : Toggles the status LED every 500 ms
******************************************************************************/

void init_alive_task(void);
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : Sets up GPIO for the status LED on the luminary board
******************************************************************************/

/****************************** End Of Module *******************************/
#endif
