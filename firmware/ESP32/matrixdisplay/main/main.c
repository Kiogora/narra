#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "bitsmatrix.h"

void app_main(void)
{
    Matrix matrix;

    /*num_rows x num_cols matrix*/
    matrix.num_rows=8;
    matrix.num_cols=8;

    /*Number of num_rows x num_cols matrix, per manufacturable unit*/ 
    matrix.unit_per_matrix=4;

    /*Font choice width*/
    matrix.fontwidth=8;

    /*Matrix control pins*/
    matrix.serial_pin=GPIO_NUM_25;
    matrix.shift_pin=GPIO_NUM_26;
    matrix.latch_pin=GPIO_NUM_27;
    matrix.rowclk_pin=GPIO_NUM_12;
    matrix.rowrst_pin=GPIO_NUM_14;

    strcpy(matrix.message,"BITSOKO   ");
    matrix.speed=8;

    matrix_init(&matrix);
    
    while(TRUE)
    {
        display(&matrix);
    }
}
