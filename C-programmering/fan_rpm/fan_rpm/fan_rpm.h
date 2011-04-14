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

#ifndef _FAN_RPM_H
  #define _FAN_RPM_H

/***************************** Include files *******************************/
#include "..\inc\emp_type.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/


void init_fan_rpm(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	Setup of the digi switch INT.	
******************************************************************************/


void enable_fan_rpm_int(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	This function enables the digi switch INT.	
******************************************************************************/


void disable_fan_rpm_int(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	This function disables the digi switch INT.
******************************************************************************/


INT16U get_fan_rpm(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	Return the counter value since last call
*   Function : 	Every time the digi switch is turned an internal counter is 
								updated. When this functin is called the currnet counter value
								is return and	then cleared.
******************************************************************************/

void portd_isr(void);

void fan_rpm_task(void);

/****************************** End Of Module *******************************/
#endif
