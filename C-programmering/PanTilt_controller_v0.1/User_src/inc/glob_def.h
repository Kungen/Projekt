/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: glob_def.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Definements of variable types.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef _GLOB_DEF_H
  #define _GLOB_DEF_H

/***************************** Include files *******************************/

#include "..\FreeRTOSConfig.h"

/*****************************    Defines    *******************************/

#define FALSE			0
#define TRUE  			!FALSE
#define NULL			((void *)0)

#define MILLI_SEC(x)	x / ( 1000 / ( ( INT16U ) configTICK_RATE_HZ) )

// Task defines
#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define IDLE_PRIO	0
#define LOW_PRIO	1
#define	MED_PRIO	2
#define	HIGH_PRIO 	3

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

/****************************** End Of Module *******************************/
#endif
