/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: leds.c
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
* 050128  KA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "inc\lm3s6965.h"
#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"
#include "..\inc\emp_type.h"
#include "..\inc\glob_def.h"
#include "..\cpu\cpu.h"
#include "..\inc\binary.h"
#include "..\inc\application.h"
#include "adc.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT16U analog_input_value = 0;

/*****************************   Functions   *******************************/

void init_adc(void)
{
	INT32U dummy;
	//init ADC
	// Enable the ADC.
	SYSCTL_RCGC0_R |= SYSCTL_RCGC0_ADC | SYSCTL_RCGC0_ADCSPD1M;
				  
	// Do a dummy read to insert a few cycles after enabling the peripheral.
	dummy = SYSCTL_RCGC0_R;
				  
	ADC_SSPRI_R = ADC_SSPRI_SS3_1ST | ADC_SSPRI_SS2_2ND | ADC_SSPRI_SS1_3RD |  ADC_SSPRI_SS0_4TH;

	//disable sequence
	ADC_ACTSS_R = 0;

	//controller control event, mode : controller
	ADC_EMUX_R = ADC_EMUX_EM3_PROCESSOR;

	//input multiplexer input, sequancer 3 select, ADC 1 enable.
	ADC_SSMUX3_R = 0x01;

	//ADC sample sequence control 3
	ADC_SSCTL3_R =  ADC_SSCTL3_END0 ;

	//enable sequencer 3
	ADC_ACTSS_R = ADC_ACTSS_ASEN3;

	// Start conversion
	ADC_PSSI_R = 0x08;
}


void init_analog_input_task(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
	init_adc();
}

INT16U get_analog_input_value(void)
{
	INT16U return_value = 0;
	xSemaphoreTake( analog_input_value_mutex, portMAX_DELAY );
	return_value = analog_input_value;
	xSemaphoreGive( analog_input_value_mutex);
	
	return return_value;
}


void set_analog_input_value(INT16U value)
{
	xSemaphoreTake( analog_input_value_mutex, portMAX_DELAY );
	analog_input_value = value;
	xSemaphoreGive( analog_input_value_mutex);
}


void analog_input_task(void *pvParameters)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
	INT16S adc_result=0;
	
	init_analog_input_task();
	

	while(1)
	{
		// Get ADC result
		adc_result = ADC_SSFIFO3_R;
		
		adc_result -= 20;
		if (adc_result < 0)
		{
			adc_result = 0;
		}
		else
		if (adc_result > 1000)
		{
			adc_result = 1000;
		}

		set_analog_input_value(adc_result);
				
	  //enable sequencer 3, Start ADC
	  ADC_ACTSS_R = ADC_ACTSS_ASEN3;
	
	  // Start conversion
	  ADC_PSSI_R = 0x08;
	 
	  vTaskDelay(MILLI_SEC(50)); // Wait 50 milli sec.
	}
}

/****************************** End Of Module *******************************/




