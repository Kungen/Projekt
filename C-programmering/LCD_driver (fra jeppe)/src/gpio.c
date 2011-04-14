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

extern void init_gpio()
{
	INT8S dummy;
	  // Enable the GPIO port that is used for the on-board LED.
	  SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;
	  SYSCTL_RCGC2_R += SYSCTL_RCGC2_GPIOG;
	  SYSCTL_RCGC2_R += SYSCTL_RCGC2_GPIOD;
	  SYSCTL_RCGC2_R += SYSCTL_RCGC2_GPIOA;
	  SYSCTL_RCGC2_R += SYSCTL_RCGC2_GPIOB;

	  // Do a dummy read to insert a few cycles after enabling the peripheral.
	  dummy = SYSCTL_RCGC2_R;

	  // Set the direction as output (PF0).
	  GPIO_PORTG_DIR_R = 0x01 | 0x02;
	  GPIO_PORTD_DIR_R = 0x40;
	  GPIO_PORTF_DIR_R = 0x01;
	  GPIO_PORTA_DIR_R = 0x40 | 0x80;
	  GPIO_PORTB_DIR_R = 0x04 | 0x08 | 0x10 | 0x20 | 0x40;

	  // Enable the GPIO pins for digital function (PF0 and PF1).
	  GPIO_PORTF_DEN_R = 0x01 | 0x02;
	  GPIO_PORTG_DEN_R = 0x01 | 0x02;
	  GPIO_PORTD_DEN_R = 0x40;
	  GPIO_PORTA_DEN_R = 0x40 | 0x80;
	  GPIO_PORTB_DEN_R = 0x04 | 0x08 | 0x10 | 0x20 | 0x40;

	  // Enable internal pull-up (PF1).
	  GPIO_PORTF_PUR_R = 0x02;

	  GPIO_PORTA_DATA_R &= ~(0xFF);
	  GPIO_PORTB_DATA_R &= ~(0xFF);
	  GPIO_PORTD_DATA_R &= ~(0xFF);
	  GPIO_PORTG_DATA_R &= ~(0xFF);
	  GPIO_PORTF_DATA_R &= ~(0xFF);

}

void toggle_status_led(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : Toggles status led on the luminary board
*****************************************************************************/
{
    GPIO_PORTF_DATA_R ^= 0x01;
}

/****************************** End Of Module *******************************/












