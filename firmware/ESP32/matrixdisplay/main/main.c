#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "bitsmatrix.h"

void app_main(void)
{
    /*Define Matrix struct instance*/
    Matrix matrix;
    matrix_setup(&matrix, GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27, 
                 GPIO_NUM_12, GPIO_NUM_14,scroll_speed_13, 
                 fontwidth_8, numrow_8, numcol_8);

    while(TRUE)
    {
        if (matrix.is_setup)
        {
            display(&matrix);
        }
    }
}

