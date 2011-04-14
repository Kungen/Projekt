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

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void enable_global_int()
{
	// enable interrupts.
	__asm("cpsie i");
}

void disable_global_int()
{
  // disable interrupts.
  __asm("cpsid i");
}

/****************************** End Of Module *******************************/












