/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: cpu.c
*
* PROJECT....: Semesterproject Rob-tek 4.th semester Group 3.
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
#include "..\inc\lm3s6965.h"
#include "..\inc\emp_type.h"
#include "..\inc\glob_def.h"
#include "..\inc\binary.h"
#include "cpu.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
void init_clk_system()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	INT32U dummy;
	// Init clock settings according to datasheet 
	// Set Clock speed to 50 Mhz.
	
	// Step 1
	// Set BYPASS bit
	SYSCTL_RCC_R |= SYSCTL_RCC_BYPASS;
	// Clear USESYS bits
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_USESYSDIV);
	// Enable Main osc.
	SYSCTL_RCC_R |= SYSCTL_RCC_MOSCDIS;
	
	// delay
	for (dummy = 200000; dummy >0; dummy--);

	// Step 2
	// Clear PLL lock flag
	SYSCTL_RIS_R = ~(SYSCTL_RIS_PLLLRIS);
	// Set XTAL value, first clear bits then set 
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_XTAL_M); 
	SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_8MHZ;
	// Set OSCSRC, first clear bits then set 
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_OSCSRC_M); 
	SYSCTL_RCC_R |= SYSCTL_RCC_OSCSRC_MAIN;

	// delay
	for (dummy = 200000; dummy >0; dummy--);

	// Clear PWRDN
		SYSCTL_RCC_R &= ~(SYSCTL_RCC_PWRDN);

	// delay
	for (dummy = 200000; dummy >0; dummy--);
		
	// Step 3
	// Set SYSDIV, first clear bits then set
	// Set to 50 Mhz.
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_SYSDIV_M); 
	SYSCTL_RCC_R |= SYSCTL_RCC_SYSDIV_3;
	// Set USESYS bit
	SYSCTL_RCC_R |= SYSCTL_RCC_USESYSDIV;
	
	// Step 4
	// wait for PLL lock
	while(!(SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS));

	// Step 5
	// Clear BYPASS bit
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_BYPASS);
	
	// delay
	for (dummy = 200000; dummy >0; dummy--);
		
}

void enable_global_int()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	// enable interrupts.
	__asm("cpsie i");
}

void disable_global_int()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  // disable interrupts.
  __asm("cpsid i");
}


/****************************** End Of Module *******************************/












