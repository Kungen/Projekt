/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: watch.c
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
#include "..\inc\binary.h"
#include "..\inc\glob_def.h"
#include "..\lcd\lcd.h"
#include "..\event\event.h"
#include "watch.h"
#include "..\RTCS\rtcs.h"

/*****************************    Defines    *******************************/

enum WATCH_STATES 				{ STOPPED, RUN, SET_TIME };
enum WATCH_SET_STATES 			{ HOUR, MIN, SEC };
enum WATCH_DISPLAY_STATES		{ DISPLAY_VALUES, DISPLAY_BLANK};

/*****************************   Constants   *******************************/

/*****************************   Varables   *******************************/

BOOLEAN blink_visible = 0;
INT8S	sec = 0;
INT8S min = 0;
INT8S hour = 0;
INT16U SWT = 0;
enum WATCH_STATES watch_state = RUN;
enum WATCH_SET_STATES watch_set_state = SEC;
enum WATCH_DISPLAY_STATES watch_display_state = DISPLAY_VALUES;
/*****************************   Functions   *******************************/


void watch_update_display(enum WATCH_SET_STATES state)
/*****************************************************************************
*   Input    : 	Current state (see SET_STATE enum)
*   Output   : 	-
*   Function : 	This function updates the lcd display accroding to the 
*								actual time and state variable. 
******************************************************************************/
{
	
	switch (state)
	{
		case SEC:
			display_buffer_write_char(10,0, sec / 10 + '0');
			display_buffer_write_char(11,0, sec % 10 + '0');
			break;

		case MIN:
			display_buffer_write_char(7,0, min / 10 + '0');
			display_buffer_write_char(8,0, min % 10 + '0');
			break;

		case HOUR:
			display_buffer_write_char(4,0, hour/ 10 + '0');
			display_buffer_write_char(5,0, hour % 10 + '0');
			break;
	}
}

void watch_run(void)
/*****************************************************************************
*   Input    :	-
*   Output   :	-
*   Function :	This is the clock function. Must be called every second
******************************************************************************/
{
	sec++;
	if( sec >= 60 )
  	{
  		sec = 0;
  		min++;
  		if( min >= 60 )
  		{
  			min = 0;
    		hour++;
    		if( hour >= 24 )
    		{
    			hour = 0;
    		}
		}
  	}
	watch_update_display(SEC);
	if(sec == 0)
	{
		watch_update_display(MIN);
	}
	if(MIN == 0)
	{
		watch_update_display(HOUR);
	}
}
	

void watch_adjust_time(enum EVENTS event)
/*****************************************************************************
*   Input    :	-
*   Output   :	-
*   Function :	-  
******************************************************************************/
{
	INT8S	value_to_add = 0;
	
	if(event == CW)
	{
		value_to_add = +1;
	}
	if(event == CCW)
	{
		value_to_add = -1;
	}

	switch(watch_set_state)
	{
		case SEC:
			sec += value_to_add;
			if (sec > 59)
			{
				sec = 0;
			}
			if (sec < 0)
			{
				sec = 59;
			}
			watch_update_display(SEC);
			break;

		case MIN:
			min += value_to_add;
			if (min > 59)
			{
				min = 0;
			}
			if (min < 0)
			{
				min = 59;
			}
			watch_update_display(MIN);
			break;

		case HOUR:
			hour += value_to_add;
			if (hour > 23)
			{
				hour = 0;
			}
			if (hour < 0)
			{
				hour = 23;
			}
			watch_update_display(HOUR);
			break;
	}
}


void init_watch_task(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
//	display_buffer_write_char(6,0,':');
//	display_buffer_write_char(9,0,':');
	hour = 23;
	min = 59;
	sec = 59;
	_start(WATCH_TASK, MILLI_SEC(0));
}


void watch_task(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	enum EVENTS event =	event_get(DREHIMPULSGEBER_EVENTS);

	switch (watch_state)
	{
		case RUN:
			if (event == SINGLE_PRESS)
			{
				watch_state = SET_TIME;
				watch_set_state = HOUR;
//				watch_display_state = DISPLAY_BLANK;
			}
			else
			{
				SWT++;
				if(SWT == 1000)
				{
					SWT = 0;
					watch_run();
					watch_update_display(HOUR);
					watch_update_display(MIN);
					watch_update_display(SEC);
				}
			}
			break;

		case SET_TIME:
			if ((event == SINGLE_PRESS) && (watch_set_state == SEC))
			{
				watch_state = RUN;
				_start(BLINK_TASK, MILLI_SEC(0));
			}
			else if(event == SINGLE_PRESS)
			{
				watch_set_state++;
			}
			else if((event == CW) || (event == CCW))
			{
				watch_adjust_time(event);
			}
			break;

		case STOPPED:
			break;
	}
	_wait(MILLI_SEC(1));
}

void init_blink_task(void)
{
	_start(BLINK_TASK, MILLI_SEC(0));
}

void blink_task(void)
{
	if(blink_visible == 0)
	{
		display_buffer_write_char(6,0,':');
		display_buffer_write_char(9,0,':');
		blink_visible = 1;
	}
	else
	{
		display_buffer_write_char(6,0,' ');
		display_buffer_write_char(9,0,' ');
		blink_visible = 0;
	}
	if((watch_state == RUN) || (blink_visible == 1))
	{
		_wait(MILLI_SEC(500));
	}
}

/****************************** End Of Module *******************************/

