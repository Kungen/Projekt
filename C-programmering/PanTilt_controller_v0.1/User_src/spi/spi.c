/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: spi.c
*
* PROJECT....: See module specification file (.h-file).
*
* DESCRIPTION:
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 110323  JEPE  Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/

#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"
#include "..\inc\lm3s6965.h"
#include "..\inc\emp_type.h"
#include "..\inc\glob_def.h"
#include "..\inc\binary.h"
#include "..\adc\adc.h"
#include "spi.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
INT8S test = 0;
/*****************************   Functions   *******************************/

void init_spi_pin(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
    INT8S dummy;

    // Enable GPIO port A.
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;

    // Do a dummy read to insert a few cycles after enabling the peripheral.
    dummy = SYSCTL_RCGC2_R;

    // Set the direction as output (PA2, 3 and 5).
    GPIO_PORTA_DIR_R |= 0x04 | 0x08 | 0x20;

    // Set the direction as input  (PA4)
    GPIO_PORTA_DIR_R &= ~(0x10);

	// Enables PA2-5 for alternative operation.
    GPIO_PORTA_AFSEL_R |= 0x04 | 0x08 | 0x10 | 0x20;

    // Enable the GPIO pins for digital function (PA2-5).
    GPIO_PORTA_DEN_R |= 0x04 | 0x08 | 0x10 | 0x20;
}

void init_spi(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	//Inits the pins used for SPI
	init_spi_pin();

	// Init SPI.
    INT8S dummy;

    // Enable the SSI.
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_SSI0;

    // Do a dummy read to insert a few cycles after enabling the peripheral.
    dummy = SYSCTL_RCGC1_R;

	// 1. Ensures that the SSE bit in the SSICR1 register is disabled before making any configuration changes.
    SSI0_CR1_R &= ~(SSI_CR1_SSE);

    // 2. Set the SSI to master mode
    SSI0_CR1_R = 0x00000000;

    // 3. Setting up the SSI clock to 1 MHz ( FSSIClk = FSysClk / (CPSDVSR * (1 + SCR)) )
    SSI0_CPSR_R = 10;
    SSI0_CR0_R |= 0x0400;

    // 4. Setting up the SSI for Freescale SPI mode (SPH = 1 and SPO = 0) and 16 bit data
	SSI0_CR0_R |= SSI_CR0_SPH;
	SSI0_CR0_R &= ~(SSI_CR0_SPO);
	SSI0_CR0_R |= SSI_CR0_DSS_16;

	// 5. Enabling the SSI
	SSI0_CR1_R |= SSI_CR1_SSE;
}

void spi_task(void *pvParameters)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	init_spi();

	vTaskDelay(MILLI_SEC(10));

	INT16U data;
	INT16U dummy;

	while( 1 )
	{
		dummy = 0x00FF & ( get_analog_input_value() / 10 );
		data = (dummy << 8);
		data += dummy & 0x00FF;
		SSI0_DR_R = data;

		vTaskDelay(MILLI_SEC(100));
	}

}


/****************************** End Of Module *******************************/












