/*****************************************************************************
* Odense University College of Enginerring
*
* MODULENAME.: main.c
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
* 110323  JEPE  Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"
#include "inc\lm3s6965.h"
#include "inc\glob_def.h"
#include "inc\application.h"
#include "cpu\cpu.h"
#include "emp_led\emp_led.h"
#include "spi\spi.h"
#include "alive_task\alive_task.h"
#include "keyboard\keyboard.h"
#include "lcd\lcd.h"
#include "adc\adc.h"
#include "print\print.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

// Semaphores
xSemaphoreHandle analog_input_value_mutex;
xSemaphoreHandle lcd_buffer_mutex;
xSemaphoreHandle common_pins_mutex;

// Queues
xQueueHandle keyboard_input_queue;

/*****************************   Functions   *******************************/
void __error__(char *pcFilename, unsigned long ulLine) {
}

static void setupHardware(void)
{

	disable_global_int();
		init_clk_system();
		init_emp_led();
	enable_global_int();

}

/***************************** Main function *******************************/
int main(void)
{
	setupHardware();

	portBASE_TYPE return_value = TRUE;

	// Start all the tasks.

	return_value = xTaskCreate( alive_task, 			( signed portCHAR * ) "alive_task", 		USERTASK_STACK_SIZE, NULL, IDLE_PRIO, NULL );
	if (return_value != TRUE)
	{
		LED_RED_ON();	// Turns red led on if the task creation fails.
		while(1);  		// could not create task.
	}
	return_value = xTaskCreate( spi_task, 				( signed portCHAR * ) "spi_task", 			USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
	if (return_value != TRUE)
	{
		LED_RED_ON();   // Turns red led on if the task creation fails.
		while(1);  		// could not create task.
	}
	return_value = xTaskCreate( lcd_task, 				( signed portCHAR * ) "lcd_task", 			USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
	if (return_value != TRUE)
	{
		LED_RED_ON();   // Turns red led on if the task creation fails.
		while(1);  		// could not create task.
	}
	return_value = xTaskCreate( analog_input_task, 		( signed portCHAR * ) "analog_input_task", 	USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
	if (return_value != TRUE)
	{
		LED_RED_ON();   // Turns red led on if the task creation fails.
		while(1);  		// could not create task.
	}
	return_value = xTaskCreate( keyboard_task, 			( signed portCHAR * ) "keyboard_task", 		USERTASK_STACK_SIZE, NULL, MED_PRIO, NULL );
	if (return_value != TRUE)
	{
		LED_RED_ON();   // Turns red led on if the task creation fails.
		while(1);  		// could not create task.
	}
	return_value = xTaskCreate( print_task, 			( signed portCHAR * ) "print_task", 		USERTASK_STACK_SIZE, NULL, LOW_PRIO, NULL );
	if (return_value != TRUE)
	{
		LED_RED_ON();   // Turns red led on if the task creation fails.
		while(1);  		// could not create task.
	}

	// Creating all the Mutexes

	analog_input_value_mutex = xSemaphoreCreateMutex();
	if (analog_input_value_mutex == NULL)
	{
		LED_YELLOW_ON();	// Turns yellow led on if the mutex creation fails.
		while(1); 			// could not create mutex
	}

	lcd_buffer_mutex = xSemaphoreCreateMutex();
	if (lcd_buffer_mutex == NULL)
	{
		LED_YELLOW_ON();	// Turns yellow led on if the mutex creation fails.
		while(1); 			// could not create mutex
	}

	common_pins_mutex = xSemaphoreCreateMutex();
	if (common_pins_mutex == NULL)
	{
		LED_YELLOW_ON();	// Turns yellow led on if the mutex creation fails.
		while(1); 			// could not create mutex
	}

	// Creating all the Queues
	keyboard_input_queue = xQueueCreate(16, sizeof( INT8U ));
	if (keyboard_input_queue == NULL)
	{
		LED_GREEN_ON();		// Turns green led on if the queue creation fails.
		while(1); 			// could not create queue
	}

	// Start the scheduler.

	vTaskStartScheduler();

	/* 
	 * Will only get here if there was insufficient memory to create the idle task. 
	 */
	return 1;
}
