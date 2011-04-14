/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: button.c
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
#include "inc\lm3s6965.h"
#include "..\inc\emp_type.h"
#include "..\inc\glob_def.h"
#include "..\inc\binary.h"
#include "..\event\event.h"
#include "Drehimpulsgeber.h"
#include "..\RTCS\rtcs.h"

/*****************************    Defines    *******************************/

// Button State machine states.
// ----------------------------
enum button_states
{
  IDLE, FIRST_PUSH, A_and_B_0, A_and_B_1 //,button_state = IDLE;
};

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

enum button_states button_state = IDLE;

/*****************************   Functions   *******************************/


void init_drehimpulsgeber_task(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	Push button setup
******************************************************************************/
{
	INT8U	dummy;

	// Enable the GPIO port that is used for the Select button.
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;

	// Do a dummy read to insert a few cycles after enabling the peripheral.
	dummy = SYSCTL_RCGC2_R;

	// Set the direction as input (PB1, PC4 and PC5).
	GPIO_PORTB_DIR_R &= ~(0x02);
	GPIO_PORTC_DIR_R &= ~(0x30);

	// Enable the GPIO pins for digital function (PB1, PC4 and PC5).
	GPIO_PORTB_DEN_R |= 0x02;
	GPIO_PORTC_DEN_R |= 0x30;

	// Enable internal pull-up (PB1, PC4 and PC5).
	GPIO_PORTB_PUR_R |= 0x02;
	GPIO_PORTC_PUR_R |= 0x30;

	// Start tasks
	_start(DREHIMPULSGEBER_TASK, MILLI_SEC(0));
}

enum EVENTS drehimpulsgeber_state_machine(void)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : The button state machine.
******************************************************************************/
{
  enum EVENTS event = NO_EVENT;

  switch( button_state )
  {
    case IDLE:
	  	if(!(GPIO_PORTC_DATA_R & 0x20))									// if button pushed
		{
	  		button_state = FIRST_PUSH;
		}
	  	else if((GPIO_PORTC_DATA_R & (0x10)) && (GPIO_PORTB_DATA_R & (0x02)))
	  	{
	  		button_state = A_and_B_1;
	  	}
	  	else if(!(GPIO_PORTC_DATA_R & (0x10)) && !(GPIO_PORTB_DATA_R & (0x02)))
	  	{
	  		button_state = A_and_B_0;
	  	}
		break;

    case FIRST_PUSH:
    	if((GPIO_PORTC_DATA_R & 0x20)) 	// if timeout
		{
//		    button_state = FIRST_RELEASE;
		    event = SINGLE_PRESS;
		    button_state = IDLE;
		}
		break;

//    case FIRST_RELEASE:
//		button_state = IDLE;
//		break;

    case A_and_B_0:
    	if(!(GPIO_PORTC_DATA_R & 0x20))									// if button pushed
    	{
    		button_state = FIRST_PUSH;
    	}
    	else if(GPIO_PORTB_DATA_R & (0x02))
    	{
    		button_state = IDLE;
    		event = CCW;
    	}
    	else if(GPIO_PORTC_DATA_R & (0x10))
    	{
    		button_state = IDLE;
    		event = CW;
    	}
    	break;

    case A_and_B_1:
    	if(!(GPIO_PORTC_DATA_R & 0x20))									// if button pushed
    	{
    		button_state = FIRST_PUSH;
    	}
    	else if(!(GPIO_PORTB_DATA_R & (0x02)))
       	{
       		button_state = IDLE;
       		event = CCW;
       	}
       	else if(!(GPIO_PORTC_DATA_R & (0x10)))
       	{
       	    button_state = IDLE;
       	    event = CW;
       	}
       	break;
  }
  return event;
}

void drehimpulsgeber_task(void)
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : The button task.
******************************************************************************/
{
	enum EVENTS event;

	event = drehimpulsgeber_state_machine();

	event_set(DREHIMPULSGEBER_EVENTS, event);

	if(event == CW || event == CCW)
	{
		_start(LED_TASK, MILLI_SEC(0));
	}
	_wait(MILLI_SEC(1));
}

/****************************** End Of Module *******************************/












