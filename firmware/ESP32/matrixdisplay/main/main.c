#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "displaycontroller.h"


void app_main(void)
{
    /*Define Matrix instance*/
    Matrix matrix;
    /*Obtain address and set pointer at Matrix instance data-structure*/ 
    Matrix* matrixptr = &matrix;
    /*Setup and initialise Matrix instance data-structure*/
    /*Lower scroll speed values indicate lower scroll speeds and vice versa, check enumeration for details*/
    matrix_setup(matrixptr, GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27, GPIO_NUM_12, GPIO_NUM_14, scroll_speed_15);

    while(TRUE)
    {
        /*Check if matrix instance is setup and display only if*/
        if (matrix.is_setup){ display(matrixptr, scroll); }
    }
}

