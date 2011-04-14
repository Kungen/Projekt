/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: digi_switch.c
*
* PROJECT....: EMP
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
#include "..\rtcs\rtcs.h"
#include "digi_switch.h"

/*****************************    Defines    *******************************/

#define PB1		1
#define PC4		4

#define CLEAR_DIGI_SWITCH_INT_REQUEST {SET_BIT_HIGH(GPIO_PORTB_ICR_R, PB1);}
#define ENABLE_DIGI_SWITCH_INT				{SET_BIT_HIGH(GPIO_PORTB_IM_R, PB1);}
#define DISABLE_DIGI_SWITCH_INT				{SET_BIT_LOW(GPIO_PORTB_IM_R, PB1);}

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8S	digi_switch_counter;

/*****************************   Functions   *******************************/

void enable_digi_switch(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	digi_switch_counter = 0;	

	// clear pending int.
	CLEAR_DIGI_SWITCH_INT_REQUEST;

	// Enable int.
	ENABLE_DIGI_SWITCH_INT;
}


void disable_digi_switch(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	DISABLE_DIGI_SWITCH_INT;
}


INT8S get_digi_switch_counter(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	INT8U	return_value = 0;
	
	DISABLE_DIGI_SWITCH_INT;
	return_value = digi_switch_counter;
	digi_switch_counter = 0;
	ENABLE_DIGI_SWITCH_INT;
	
	return return_value;
}


void digi_switch_port_setup(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	Digi switch setup.
******************************************************************************/

{
	INT8U	dummy;

	// PC4, DIGI A, PB1, DIGI B
	
	// Enable the GPIO port that is used for the digi switch.
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
  
  // Do a dummy read to insert a few cycles after enabling the peripheral.
  dummy = SYSCTL_RCGC2_R;

  // Set the direction as input  
  SET_BIT_LOW(GPIO_PORTC_DIR_R, PC4);
  SET_BIT_LOW(GPIO_PORTB_DIR_R, PB1);
  
  // Enable the GPIO pins for digital function (PF0 and PF1).
  SET_BIT_HIGH(GPIO_PORTC_DEN_R, PC4);
  SET_BIT_HIGH(GPIO_PORTB_DEN_R, PB1);
  
  // Disable open drain
  SET_BIT_LOW(GPIO_PORTC_ODR_R, PC4);
  SET_BIT_LOW(GPIO_PORTB_ODR_R, PB1);
    
  // Disable alternative function
  SET_BIT_LOW(GPIO_PORTC_AFSEL_R,PC4);
  SET_BIT_LOW(GPIO_PORTB_AFSEL_R,PB1);
  
  // Disable internal pull-up   
  SET_BIT_LOW(GPIO_PORTC_PUR_R, PC4);
  SET_BIT_LOW(GPIO_PORTB_PUR_R, PB1);
}

void digi_switch_int_setup(void)
{
	// Interrupt on Port PB1
	
	// Edge trigger
	SET_BIT_LOW(GPIO_PORTB_IS_R, PB1);
	// both edges
	SET_BIT_HIGH(GPIO_PORTB_IBE_R, PB1);
  	
	// negative 	edge
	// SET_BIT_LOW(GPIO_PORTB_IEV_R, PB1);

	// Clear interrupt request
	CLEAR_DIGI_SWITCH_INT_REQUEST;
	
	// NVIC setup
	// program NVIC, vector number 17, Interrupt Number = 1
	// Clear pending interrupt
	NVIC_UNPEND0_R |= NVIC_UNPEND0_INT1;
	// Set Priority to 0x10, first clear then set. 
	NVIC_PRI0_R &= ~(NVIC_PRI0_INT1_M);
	NVIC_PRI0_R |= (NVIC_PRI0_INT1_M & (0x10<<NVIC_PRI0_INT1_S));
	// enable NVIC interrupt
	NVIC_EN0_R |= NVIC_EN0_INT1;
	
	// Enable int
	ENABLE_DIGI_SWITCH_INT;
}


void portb_isr(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	This digi switch ISR function is called every time the user 
								turns the	digi switch if the INT is enabled.
******************************************************************************/
{
	if (TEST_BIT_HIGH(GPIO_PORTB_MIS_R, PB1))
	{
		if (TEST_BIT_HIGH(GPIO_PORTB_DATA_R,PB1) == (TEST_BIT_HIGH(GPIO_PORTC_DATA_R,PC4)>>3))
		{
			// CW
			digi_switch_counter++;
		}
		else
		{
			// CCW
			digi_switch_counter--;
		}
	}
	// Clear interrupt request
	CLEAR_DIGI_SWITCH_INT_REQUEST;
}


void init_digi_switch(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	digi_switch_port_setup();
	digi_switch_int_setup();
	disable_digi_switch();
}


/***************************** End Of Module *******************************/












