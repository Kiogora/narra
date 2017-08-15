
/*ESP-IDF libs*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*Project libs*/
#include "narra_parameters.h"
#include "system_loader.h"
#include "system_controller.h"
#include "system_updater.h"


void app_main(void)
{
    Matrix matrix;    
    System_variables system_variables;

    char* new_text="***WELCOME TO HEAVEN***";
    system_update_startup(new_text);

    char* active_text="***ACTIVE***";    
    system_update_active(active_text);

    char* shutdown_text="***GOODBYE***";    
    system_update_shutdown(shutdown_text);
    int i=0;

    system_setup(&matrix, &system_variables, GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27, GPIO_NUM_12, GPIO_NUM_14, system_speed_15);

    while(1)
    {
        i++;
        system_display(&matrix, &system_variables, scroll);

        if(i==5)
        {
            system_deactivate(&matrix, &system_variables); 
        }       
    }
}

