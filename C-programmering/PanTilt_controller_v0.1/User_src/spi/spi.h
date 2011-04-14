/*****************************************************************************
* Odense University College of Enginerring
*
* MODULENAME.: spi.h
*
* PROJECT....: Semesterproject Rob-tek 4.th semester Group 3.
*
* DESCRIPTION: This module is responsibly for the SPI communication between the Luminary kit and the Xilinx FPGA motorcontroller
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 110323  JEPE  Module created.
*
*****************************************************************************/

#ifndef _SPI_H
  #define _SPI_H

/***************************** Include files *******************************/
#include "..\inc\emp_type.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void init_spi(void);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function :	initializes spi communication in Freescale SPI mode (16 bit strings)
*****************************************************************************/

void spi_task(void *pvParameters);
/*****************************************************************************
*   Input    : 	-
*   Output   : 	-
*   Function :	Testing the SPI.
*****************************************************************************/

/****************************** End Of Module *******************************/
#endif
