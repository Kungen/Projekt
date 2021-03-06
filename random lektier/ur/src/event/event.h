/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: event.h
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

#ifndef _EVENT_H
  #define _EVENT_H

/***************************** Include files *******************************/
#include "..\inc\emp_type.h"
/*****************************    Defines    *******************************/

#define MAX_EVENTS	1

enum 	EVENT_TYPES 
{ 
	DREHIMPULSGEBER_EVENTS = 0
};


enum EVENTS
{
  NO_EVENT = 0,
  
  // Button events    
  SINGLE_PRESS,
  CW,
  CCW
};


/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void event_init(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	-
******************************************************************************/

void event_set(enum EVENT_TYPES type, enum EVENTS event );
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	-
******************************************************************************/

enum EVENTS event_get(enum EVENT_TYPES type);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	-
******************************************************************************/

/****************************** End Of Module *******************************/
#endif
