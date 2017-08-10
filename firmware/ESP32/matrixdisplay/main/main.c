#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "displaycontroller.h"
//#include "crc.h"
#include <stdio.h>

void app_main(void)
{
    /*Define Matrix instance*/
    Matrix matrix;
    /*Obtain address and set pointer at Matrix instance data-structure*/ 
    Matrix* matrixptr = &matrix;
    /*Setup and initialise Matrix instance data-structure*/
    /*Lower scroll speed values indicate lower scroll speeds and vice versa, check enumeration for details*/
    matrix_setup(matrixptr, GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27, GPIO_NUM_12, GPIO_NUM_14, scroll_speed_15);
/*
    char  test[] = "123456789";


	printf("The check value for the %s standard is 0x%X\n", CRC_NAME, CHECK_VALUE);
	

	printf("The crcSlow() of \"123456789\" is 0x%X\n", crcSlow(test, strlen(test)));
	

	crcInit();

	printf("The crcFast() of \"123456789\" is 0x%X\n", crcFast(test, strlen(test)));
*/

    while(1)
    {
        /*Check if matrix instance is setup and display only if*/
        if (matrix.is_setup){ display(matrixptr, scroll); }
    }
}

