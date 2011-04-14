/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: digi_switch.h
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

#ifndef _DIGI_SWITCH_H
  #define _DIGI_SWITCH_H

/***************************** Include files *******************************/
#include "..\inc\emp_type.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/


void init_digi_switch(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	Setup of the digi switch INT.	
******************************************************************************/


void enable_digi_switch(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	This function enables the digi switch INT.	
******************************************************************************/


void disable_digi_switch(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	This function disables the digi switch INT.
******************************************************************************/


INT8S get_digi_switch_counter(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	Return the counter value since last call
*   Function : 	Every time the digi switch is turned an internal counter is 
								updated. When this functin is called the currnet counter value
								is return and	then cleared.
******************************************************************************/

void portb_isr(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	This digi switch ISR function is called every time the user 
								turns the	digi switch if the INT is enabled.
******************************************************************************/


/****************************** End Of Module *******************************/
#endif
