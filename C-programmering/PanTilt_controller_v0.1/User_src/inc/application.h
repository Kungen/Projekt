/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: main.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 100405  KHA    Module created.
*
*****************************************************************************/

#ifndef _APPLICATION_H
  #define _APPLICATION_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

// Mutexes
extern xSemaphoreHandle analog_input_value_mutex;
extern xSemaphoreHandle lcd_buffer_mutex;
extern xSemaphoreHandle common_pins_mutex;

// Queues
extern xQueueHandle keyboard_input_queue;

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

/****************************** End Of Module *******************************/
#endif

