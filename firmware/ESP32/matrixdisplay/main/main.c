
/*ESP-IDF libs*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*Project libs*/
#include "system_loader.h"
#include "system_controller.h"

void app_main(void)
{
    Matrix matrix;    
    System_variables system_variables;

    system_setup(&matrix, &system_variables, GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27, GPIO_NUM_12, GPIO_NUM_14, system_speed_15);

    while(1)
    {
        system_display(&matrix, &system_variables, scroll);
    }
}

