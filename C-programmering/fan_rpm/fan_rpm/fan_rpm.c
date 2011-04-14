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
#include "fan_rpm.h"

/*****************************    Defines    *******************************/

#define PD7		7

#define CLEAR_FAN_INT_REQUEST 		{SET_BIT_HIGH(GPIO_PORTD_ICR_R, PD7);}
#define ENABLE_FAN_INT				{SET_BIT_HIGH(GPIO_PORTD_IM_R, PD7);}
#define DISABLE_FAN_INT				{SET_BIT_LOW(GPIO_PORTD_IM_R, PD7);}

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U	fan_int_counter;
INT16U	fan_rpm;

/*****************************   Functions   *******************************/

void enable_fan_rpm_int(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	fan_int_counter = 0;

	// clear pending int.
	CLEAR_FAN_INT_REQUEST;

	// Enable int.
	ENABLE_FAN_INT;
}


void disable_fan_rpm_int(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	DISABLE_FAN_INT;
}


INT16U get_fan_int_counter(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	INT16U	return_value = 0;
	
	DISABLE_FAN_INT;
	return_value = fan_int_counter;
	fan_int_counter = 0;
	ENABLE_FAN_INT;
	
	return return_value;
}

INT16U get_fan_rpm(void)
{
	return fan_rpm;
}

void fan_port_setup(void)
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	fan GPIO setup.
******************************************************************************/

{
	INT8U	dummy;

	// PC4, DIGI A, PB1, DIGI B
	
	// Enable the GPIO port that is used for the digi switch.
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
  
  // Do a dummy read to insert a few cycles after enabling the peripheral.
  dummy = SYSCTL_RCGC2_R;

  // Set the direction as input  
  SET_BIT_LOW(GPIO_PORTD_DIR_R, PD7);
  
  // Enable the GPIO pins for digital function (PF0 and PF1).
  SET_BIT_HIGH(GPIO_PORTD_DEN_R, PD7);
  
  // Disable open drain
  SET_BIT_LOW(GPIO_PORTD_ODR_R, PD7);
    
  // Disable alternative function
  SET_BIT_LOW(GPIO_PORTD_AFSEL_R,PD7);
  
  // Disable internal pull-up   
  SET_BIT_LOW(GPIO_PORTD_PUR_R, PD7);
}

void fan_int_setup(void)
{
	// Interrupt on Port PB1

	// Edge trigger
	SET_BIT_LOW(GPIO_PORTD_IS_R, PD7);
	// both edges
	SET_BIT_HIGH(GPIO_PORTD_IBE_R, PD7);

	// negative 	edge
	// SET_BIT_LOW(GPIO_PORTB_IEV_R, PB1);

	// Clear interrupt request
	SET_BIT_HIGH(GPIO_PORTD_ICR_R, PD7);

	// NVIC setup
	// program NVIC, vector number 17, Interrupt Number = 1
	// Clear pending interrupt
	NVIC_UNPEND0_R |= NVIC_UNPEND0_INT3;
	// Set Priority to 0x10, first clear then set.
	NVIC_PRI0_R &= ~(NVIC_PRI0_INT3_M);
	NVIC_PRI0_R |= (NVIC_PRI0_INT3_M & (0x10<<NVIC_PRI0_INT3_S));
	// enable NVIC interrupt
	NVIC_EN0_R |= NVIC_EN0_INT3;

	// Enable int
	ENABLE_FAN_INT;
}

void portd_isr(void)
{
	fan_int_counter++;
	GPIO_PORTF_DATA_R ^= 0x01;
	CLEAR_FAN_INT_REQUEST;
}


void init_fan_rpm(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	fan_port_setup();
	fan_int_setup();
	disable_fan_rpm_int();
	_start(FAN_RPM_TASK, MILLI_SEC(0));
}

void fan_rpm_task(void)
{
	fan_rpm = get_fan_int_counter() * 10 * 60 / 4;
	_wait(MILLI_SEC(100));
}

/***************************** End Of Module *******************************/












