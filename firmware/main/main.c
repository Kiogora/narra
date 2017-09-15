
/*ESP-IDF libs*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*Project libs*/
#include "narra_parameters.h"
 
#include "ble.h"
#include "system_loader.h"
#include "system_controller.h"
#include "system_updater.h"

typedef struct
{
    Matrix* matrixinstanceptr;
    System_variables* system_variables;
} Ble_task_parameters;

/*The below structures declared outside stack. Ensures validity between task frames and context switches*/
Matrix matrix=
{
    .current_message=NULL,
};

System_variables system_variables =
{
    .startup_msg=NULL,
    .shutdown_msg=NULL,
    .active_msg=NULL,
};
/*Now define the structure*/
Ble_task_parameters ble_task_parameters=
{
    .matrix_instance_ptr=&matrix,
    .system_variables_ptr=&system_variables;
};

void init_pin_interface(Matrix* matrixInstanceptr)
{
    matrixInstanceptr->serial_pin=GPIO_NUM_25;
    matrixInstanceptr->shift_pin=GPIO_NUM_26;
    matrixInstanceptr->latch_pin=GPIO_NUM_27;
    matrixInstanceptr->rowclk_pin=GPIO_NUM_12;
    matrixInstanceptr->rowrst_pin=GPIO_NUM_14;
}

void displayTask(void *pvParameters)
{
    init_pin_interface(&matrix);

/*    char* new_text="***WELCOME TO HEAVEN***";
    system_update_startup(new_text);
presentation_t
    char* active_text="***VIVO-ENERGY©µ***";    
    system_update_active(active_text);
*/
    if(matrix_init(&matrix, &system_variables, narra_speed_15) == ESP_OK)
    {
        /*Call xTaskCreate for the BLE task here*/
        /*pass pointer to a structure of pointers to other structures-crazy*/
        xTaskCreate(bleTask, "BleTask", 4096, (void*)&ble_task_parameters, 1, NULL);
        for(;;)
        {
            matrix_display(&matrix, &system_variables, scroll);
        }    
    }
    else
    {
        //implement pin and speed initialisation error exception handling here
    }
}

void bleTask(void *pvParameters)
{
    esp_err_t ret;
    /* Initialise NVS*/
    ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    /*TODO: cast the pvparameters, passed pointer to a valid type */

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if (ret)
    {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable controller failed\n", __func__);
        return;
    }

    ret = esp_bt_controller_enable(ESP_BT_MODE_BTDM);
    if (ret)
    {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable controller failed\n", __func__);
        return;
    }

    ESP_LOGI(GATTS_TABLE_TAG, "%s init bluetooth\n", __func__);
    ret = esp_bluedroid_init();
    if (ret)
    {
        ESP_LOGE(GATTS_TABLE_TAG, "%s init bluetooth failed\n", __func__);
        return;
    }
    ret = esp_bluedroid_enable();
    if (ret) 
    {
        ESP_LOGE(GATTS_TABLE_TAG, "%s enable bluetooth failed\n", __func__);
        return;
    }
    string ="What the fuck are you saying bitch!!!!";
    esp_ble_gatts_register_callback(gatts_event_handler);
    esp_ble_gap_register_callback(gap_event_handler);
    esp_ble_gatts_app_register(SYSTEM_APP_ID);
    esp_ble_gatts_app_register(USAGE_APP_ID);

    for(;;)
    {
        ;
    }
}

void app_main(void)
{
    xTaskCreate(displayTask, "DisplayTask", 1024, NULL, 1, NULL );
}
//TODO: Move speed from system initialisation at start and implement in parameters in func write_speed/update_speed .

