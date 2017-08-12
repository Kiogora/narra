
/*ESP-IDF libs*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*Project libs*/
#include "system_controller.h"
#include "system_loader.h"

void app_main(void)
{
    System_variables system_variables;
    Matrix matrix;
    
    matrix_setup(&matrix, GPIO_NUM_25, GPIO_NUM_26, GPIO_NUM_27, GPIO_NUM_12, GPIO_NUM_14, scroll_speed_15);
    system_loader(&system_variables);

    matrix.current_message=system_variables.startup_msg;
    display(&matrix, scroll);

    matrix.current_message=system_variables.active_msg;
    while(1)
    {
        /*Check if matrix instance is setup and display only if*/
        if (matrix.is_setup){ display(&matrix, scroll); }
    }
}

