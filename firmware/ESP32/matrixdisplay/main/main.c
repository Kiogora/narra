#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "bitsmatrix.h"

void matrix_setup();

void app_main(void)
{
    /*Define Matrix struct instance*/
    Matrix matrix;
    matrix_setup(&matrix);

    while(TRUE)
    {
        display(&matrix);
    }
}

void matrix_setup(Matrix* matrixInstance)
{
    
/*num_rows x num_cols matrix*/
    matrixInstance->num_rows=8;
    matrixInstance->num_cols=8;
    /*Number of num_rows x num_cols matrix, per manufacturable unit*/ 
    matrixInstance->unit_per_matrix=4;
    
/*Font choice width*/
    matrixInstance->fontwidth=8;

    /*Matrix control pins*/
    matrixInstance->serial_pin=GPIO_NUM_25;
    matrixInstance->shift_pin=GPIO_NUM_26;
    matrixInstance->latch_pin=GPIO_NUM_27;
    matrixInstance->rowclk_pin=GPIO_NUM_12;
    matrixInstance->rowrst_pin=GPIO_NUM_14;

    strcpy(matrixInstance->message,"BITSOKO   ");
    matrixInstance->speed=8;

    matrix_init(matrixInstance);
}
