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
* 0902012  KHA   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "inc\lm3s6965.h"
#include "inc\emp_type.h"
#include "cpu\cpu.h"
#include "rtcs\rtcs.h"
#include "LED\LED.h"
#include "event\event.h"
#include "Drehimpulsgeber\Drehimpulsgeber.h"
#include "watch\watch.h"
#include "lcd\lcd.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void init_alive_task(void)
{
	// Init status led port.
  INT8S dummy;
  // Enable the GPIO port that is used for the on-board LED.
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;

  // Do a dummy read to insert a few cycles after enabling the peripheral.
  dummy = SYSCTL_RCGC2_R;

  // Set the direction as output (PF0).  
  GPIO_PORTF_DIR_R |= 0x01;
  //SET_BIT_HIGH(GPIO_PORTF_DIR_R, PF0);
	  
	// Enable the GPIO pins for digital function (PF0 and PF1).
	GPIO_PORTF_DEN_R |= 0x01;
  //SET_BIT_HIGH(GPIO_PORTF_DEN_R, PF0);
  
	// Set pin high
  GPIO_PORTF_DATA_R |= 0x01;
	//SET_BIT_HIGH(GPIO_PORTF_DATA_R, PF0);

  // Start task
  _start(ALIVE_TASK, MILLI_SEC(1000));
}

void alive_task(void)
{
	// Toggles status LED every 1 sec.
	GPIO_PORTF_DATA_R ^= 0x01;
	
	// Wait 1 sec.
	_wait(MILLI_SEC(100));
}



int main(void)
/*****************************************************************************
*   Input    : NONE
*   Output   : Returns 0
*   Function : Init hardware and then loop forever
******************************************************************************/
{	
  	
	disable_global_int();
	clk_system_init();
	systick_init();
	enable_global_int();
		
	start_rtcs_scheduler();		// Call scheduler
  
  while(1);
  
  return( 0 );
}

/****************************** End Of Module *******************************/
