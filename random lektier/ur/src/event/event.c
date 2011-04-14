/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: event.c
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

/***************************** Include files *******************************/

#include "..\inc\emp_type.h"
#include "..\inc\binary.h"
#include "..\inc\glob_def.h"
#include "event.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U events[MAX_EVENTS];

/*****************************   Functions   *******************************/


void event_init(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	INT8U	i;
	for( i= 0; i < MAX_EVENTS; i++ )
	{
		if( events[i] )
		{
			events[i] = 0;	
		}
	}	
}


void event_set(enum EVENT_TYPES type, enum EVENTS event )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	events[type] = event;
}


enum EVENTS event_get(enum EVENT_TYPES type)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	return events[type];
}


/****************************** End Of Module *******************************/












