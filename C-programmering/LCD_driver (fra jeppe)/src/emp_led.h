/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: emp.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef _EMP_LED_H
  #define _EMP_LED_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

#define LED_RED_ON 			GPIO_PORTD_DATA_R &= ~(0x40)
#define LED_GREEN_ON 		GPIO_PORTG_DATA_R &= ~(0x02)
#define LED_YELLOW_ON 		GPIO_PORTG_DATA_R &= ~(0x01)

#define LED_RED_OFF 		GPIO_PORTD_DATA_R |= 0x40
#define LED_GREEN_OFF 		GPIO_PORTG_DATA_R |= 0x02
#define LED_YELLOW_OFF 		GPIO_PORTG_DATA_R |= 0x01

#define LED_RED_TOGGLE 		GPIO_PORTD_DATA_R ^= 0x40
#define LED_GREEN_TOGGLE	GPIO_PORTG_DATA_R ^= 0x02
#define LED_YELLOW_TOGGLE 	GPIO_PORTG_DATA_R ^= 0x01

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void set_emp_leds(INT8U value);
/*****************************************************************************
*   Input    : 0-7
*   Output   : 0-7 on the EMP boards leds
*   Function :
******************************************************************************/

/****************************** End Of Module *******************************/
#endif
