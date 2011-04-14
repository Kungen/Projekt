/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: button.h
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

#ifndef _BUTTON_H
  #define _BUTTON_H

/***************************** Include files *******************************/
#include "..\inc\emp_type.h"
#include "..\sw_timer\sw_timer.h"

/*****************************    Defines    *******************************/

enum button_states
{
  SELECT_MODE, SHOW_DATA_MODE
};

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void button_task(void);

void button_init(void);

void portc_isr(void);

/****************************** End Of Module *******************************/
#endif
