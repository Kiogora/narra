
/*ESP-IDF libs*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*Project libs*/
#include "narra_parameters.h"
 
#include "system_loader.h"
#include "system_controller.h"
#include "system_updater.h"

void init_pin_interface(Matrix* matrixInstanceptr)
{

    matrixInstanceptr->serial_pin=GPIO_NUM_25;
    matrixInstanceptr->shift_pin=GPIO_NUM_26;
    matrixInstanceptr->latch_pin=GPIO_NUM_27;
    matrixInstanceptr->rowclk_pin=GPIO_NUM_12;
    matrixInstanceptr->rowrst_pin=GPIO_NUM_14;
}

void app_main(void)
{
    Matrix matrix;    
    System_variables system_variables;

    init_pin_interface(&matrix);

    char* new_text="***WELCOME TO HEAVEN***";
    system_update_startup(new_text);

    char* active_text="***VIVO-ENERGY©µ***";    
    system_update_active(active_text);

    if(matrix_init(&matrix, &system_variables, narra_speed_15) == ESP_OK)
    {
        while(1)
        {
            matrix_display(&matrix, &system_variables, scroll);    
        }
    }
    else
    {
        //implement pin and speed initialisation error exception handling here
    }
}
//TODO: Move speed from system initialisation at start and implement in parameters in func write_speed/update_speed .

