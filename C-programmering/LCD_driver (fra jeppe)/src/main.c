/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: main.c
*
* PROJECT....: ECP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 110208  Jepe  Module created.
*
*****************************************************************************/


/***************************** Include files *******************************/
#include "inc\lm3s6965.h"
#include "emp_type.h"
#include "emp_led.h"
#include "gpio.h"
#include "global_int.h"
#include "systick_int.h"
#include "emp_lcd.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

volatile INT16S ticks = 0;
INT8U testing = 0;

/*****************************   Functions   *******************************/


int main(void)
/*****************************************************************************
*   Input    : NONE
*   Output   : Returns 0
*   Function : LED follows SWITCH
******************************************************************************/
{
  INT8S alive_timer = 50;

  disable_global_int();
    init_gpio();
	init_clk_system();
	init_systick();
	init_lcd();
  enable_global_int();
  LED_YELLOW_OFF;

   // Loop forever.
  while(1)
  {
	  while( !ticks );

	  // The following will be executed every 10mS
	  ticks--;
	  if( ! --alive_timer )
	  {
		testing++;
		if (testing == 16)
		{
			testing = 40;
		}
		if (testing == 56)
		{
			testing = 0;
		}
		lcd_clear();
		lcd_print_string("hej",testing);
		alive_timer =	150;
	    toggle_status_led();
	    LED_GREEN_TOGGLE;
	    LED_RED_TOGGLE;
	    LED_YELLOW_TOGGLE;
	  }

  }
  return( 0 );
  }

/****************************** End Of Module *******************************/


