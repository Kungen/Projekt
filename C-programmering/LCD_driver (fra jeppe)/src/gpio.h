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

#ifndef _GPIO_H
  #define _GPIO_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/



/*****************************   Functions   *******************************/

void init_gpio(void);
/*****************************************************************************
*   Input    : None
*   Output   : -
*   Function : Initiates leds on the EMP-board
******************************************************************************/

void init_status_led(void);
/*****************************************************************************
*   Input    : None
*   Output   : -
*   Function : Initiates status_led on the Luminary board
******************************************************************************/

void toggle_status_led(void);
/*****************************************************************************
*   Input    : None
*   Output   : -
*   Function : Initiates status_led on the Luminary board
******************************************************************************/

/****************************** End Of Module *******************************/
#endif