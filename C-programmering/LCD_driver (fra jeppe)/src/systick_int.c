/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: systick_int.c
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
* 090831  KHA   Module created.
*
*****************************************************************************/


/***************************** Include files *******************************/
#include "inc\lm3s6965.h"
#include "emp_type.h"

/*****************************    Defines    *******************************/

#define FCPU				50000000				// Hertz
#define TIMEOUT				10						// Milliseconds

#define SYSTICK_RELOAD_VALUE (FCPU / 1000) * TIMEOUT

// Missing definemens in lm3s6965.h file
#define NVIC_INT_CTRL_PEND_SYST  	0x04000000  // Pend a systick int
#define NVIC_INT_CTRL_UNPEND_SYST 	0x02000000  // Unpend a systick int

#define SYSTICK_PRIORITY		0x7E

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern INT16S   ticks;


/*****************************   Functions   *******************************/

void init_clk_system()
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function : 	
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
	
	// Step 2
	// Clear PLL lock flag
	SYSCTL_RIS_R = ~(SYSCTL_RIS_PLLLRIS);
	// Set XTAL value, first clear bits then set 
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_XTAL_M); 
	SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_8MHZ;
	// Set OSCSRC, first clear bits then set 
	SYSCTL_RCC_R &= ~(SYSCTL_RCC_OSCSRC_M); 
	SYSCTL_RCC_R |= SYSCTL_RCC_OSCSRC_MAIN;
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

void init_systick(void)
{
	// Systick control and status register, NVIC_ST_CTRL_R
	// Systick reload register, NVIC_ST_RELOAD_R
	// Systick current value register, NVIC_ST_CURRENT_R
	// SYSTICK Calibration Value Register, NVIC_ST_CAL_R

	// Disable systick timer
	NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_ENABLE);
	// Set current systick counter to reload value
	NVIC_ST_CURRENT_R = SYSTICK_RELOAD_VALUE;
	// Set Reload value, Systick reload register 
	NVIC_ST_RELOAD_R = SYSTICK_RELOAD_VALUE;
	// NVIC systick setup, vector number 15
	// Clear pending systick interrupt request
	NVIC_INT_CTRL_R |= NVIC_INT_CTRL_UNPEND_SYST;
	// Set systick priority to 0x10, first clear then set. 
	NVIC_SYS_PRI3_R &= ~(NVIC_SYS_PRI3_TICK_M);
	NVIC_SYS_PRI3_R |= (NVIC_SYS_PRI3_TICK_M & (SYSTICK_PRIORITY<<NVIC_SYS_PRI3_TICK_S));
	// Select systick clock source, Use core clock
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;
	// Enable systick interrupt
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;
	// Enable and start timer
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
}

	void systick_isr(void)
	/*****************************************************************************
	*   Function : See module specification (.h-file).
	*****************************************************************************/
	{
	  // Mark timer tick.
	  ticks++;
	}

