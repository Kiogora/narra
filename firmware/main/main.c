/*ESP-IDF libs*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "bt.h"
#include "bta_api.h"
#include "esp_task_wdt.h"

#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_main.h"
#include "esp_gattc_api.h"

/*Project libs*/
#include "ble.h"
#include "narra_parameters.h"
#include "system_loader.h"
#include "system_controller.h"
#include "system_updater.h"
#include "narra_defines.h"

static const char* BLE_TASK_TAG = "BLE_TASK";
static const char* APP_MAIN_TAG = "APP_MAIN";
static const char* DISPLAY_TASK_TAG = "DISPLAY_TASK";
static const char* LOADER_TASK_TAG = "LOADER_TASK";
static const char* STATE_TASK_TAG = "STATE_TASK";

/*Task alias/handle*/
TaskHandle_t xBleTaskHandle = NULL;
TaskHandle_t xDisplayTaskHandle = NULL;
TaskHandle_t xLoaderTaskHandle = NULL;
TaskHandle_t xStateTaskHandle = NULL;

/*Task synchronisation event group*/
EventGroupHandle_t xEventGroup = NULL;

typedef struct
{
    Matrix* matrix_instance_ptr;
    System_variables* system_variables_ptr;
} Generic_task_parameters;

/*The below structures declared outside stack.*/
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

/*Now define the structure with references of the memory set aside for the above structures*/
Generic_task_parameters generic_task_parameters=
{
    .matrix_instance_ptr=&matrix,
    .system_variables_ptr=&system_variables
};

void init_pin_interface(Matrix* matrixInstanceptr)
{
    matrixInstanceptr->serial_pin=GPIO_NUM_25;
    matrixInstanceptr->shift_pin=GPIO_NUM_26;
    matrixInstanceptr->latch_pin=GPIO_NUM_27;
    matrixInstanceptr->rowclk_pin=GPIO_NUM_14;
    matrixInstanceptr->rowrst_pin=GPIO_NUM_12;
}

void BleTask(void *pvParameters)
{
    ESP_LOGD(BLE_TASK_TAG, "ENTERED TASK");
    esp_err_t nvs_state, bt_init_fail;

    /* Initialise NVS*/
    nvs_state = nvs_flash_init();

    if (nvs_state == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvs_state = nvs_flash_init();
    }
    ESP_ERROR_CHECK(nvs_state);

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();

    bt_init_fail = esp_bt_controller_init(&bt_cfg);
    if (bt_init_fail)
    {
        ESP_LOGE(BLE_TASK_TAG, "FUNCTION:[%s] BLUETOOTH CONTROLLER INIT FAILED\n", __func__);
        vTaskDelete(xBleTaskHandle);
    }

    bt_init_fail = esp_bt_controller_enable(ESP_BT_MODE_BTDM);
    if (bt_init_fail)
    {
        ESP_LOGE(BLE_TASK_TAG, "FUNCTION:[%s] BLUETOOTH CONTROLLER ENABLE FAILED\n", __func__);
        vTaskDelete(xBleTaskHandle);
    }

    ESP_LOGI(BLE_TASK_TAG, "FUNCTION:[%s] INITIALISED BLUETOOTH CONTROLLER\n", __func__);

    bt_init_fail = esp_bluedroid_init();
    if (bt_init_fail)
    {
        ESP_LOGE(BLE_TASK_TAG, "FUNCTION:[%s] BLUEDROID STACK INIT FAILED\n", __func__);
        vTaskDelete(xBleTaskHandle);
    }

    bt_init_fail = esp_bluedroid_enable();
    if (bt_init_fail) 
    {
        ESP_LOGE(BLE_TASK_TAG, "FUNCTION:[%s] BLUEDROID STACK ENABLE FAILED\n", __func__);
        vTaskDelete(xBleTaskHandle);
    }

    Generic_task_parameters* ble_param = (Generic_task_parameters*)pvParameters;    

    esp_attr_value_t* usage_state_attr = get_usage_state_attribute();
    esp_attr_value_t* usage_runtime_string_attr = get_usage_runtime_string_attribute();
    esp_attr_value_t* usage_startup_string_attr = get_usage_startup_string_attribute();
    esp_attr_value_t* usage_shutdown_string_attr = get_usage_shutdown_string_attribute();

    usage_state_attr->attr_value = (uint8_t*) &(ble_param->matrix_instance_ptr->system_state);
    usage_runtime_string_attr->attr_value = (uint8_t*) ble_param->system_variables_ptr->active_msg;
    usage_startup_string_attr->attr_value = (uint8_t*) ble_param->system_variables_ptr->startup_msg;
    usage_shutdown_string_attr->attr_value = (uint8_t*) ble_param->system_variables_ptr->shutdown_msg;

    esp_ble_gatts_register_callback(gatts_event_handler);
    esp_ble_gap_register_callback(gap_event_handler);
    esp_ble_gatts_app_register(SYSTEM_APP_ID);
    esp_ble_gatts_app_register(USAGE_APP_ID);

    for(;;) ;
}

void DisplayTask(void *pvParameters)
{
    ESP_LOGD(DISPLAY_TASK_TAG, "ENTERED TASK");
    init_pin_interface(&matrix);

    if(matrix_init(&matrix, &system_variables, narra_speed_16) == ESP_OK)
    {
        /*Call xTaskCreate for the BLE task here*/
        /*pass pointer to a structure of pointers to other structures-crazy*/
        if(xBleTaskHandle == NULL)
        {
            xTaskCreate(BleTask, "BleTask", 4096, (void*)&generic_task_parameters, 1, &xBleTaskHandle);

            if(xBleTaskHandle != NULL)
            {
                ESP_LOGI(DISPLAY_TASK_TAG, "BLE TASK CREATED OR EXISTS!");
            }
            else
            {
                ESP_LOGE(DISPLAY_TASK_TAG, "FUNCTION:[%s] BLE TASK CREATION FAILED! CHECK AVAILABLE HEAP MEMORY",
                                            __func__);
            }
        }

        for(;;)
        {
            matrix_display(&matrix, &system_variables, scroll);
        }    
    }
    else
    {
        ; //implement matrix initialisation exception handling here
    }
    vTaskDelete(xDisplayTaskHandle);
}

void LoaderTask(void *pvParameters)
{
    ESP_LOGD(LOADER_TASK_TAG, "ENTERED TASK");

    System_variables* LoaderSysVars = (System_variables*)pvParameters;

    EventBits_t xEventGroupValue;
    EventBits_t xBitstoWaitFor = STRING_UPDATE_BIT;

    for(;;)
    {
        xEventGroupValue = xEventGroupWaitBits(xEventGroup, xBitstoWaitFor, pdTRUE, pdFALSE, portMAX_DELAY); 

        if(xEventGroupValue & xBitstoWaitFor)
        {
            system_loader(LoaderSysVars);
        }
    }
        
}

void StateTask(void *pvParameters)
{
    ESP_LOGD(STATE_TASK_TAG, "ENTERED TASK");

    Generic_task_parameters* state_param = (Generic_task_parameters*)pvParameters;

    EventBits_t xEventGroupValue;

    EventBits_t xBitstoWaitFor = (ACTIVATE_BIT | DEACTIVATE_BIT | STOP_DISPLAY);

    for(;;)
    {
        /*Since the state bits can only be set one at a go, dont wait for all bits of interest*/
        xEventGroupValue = xEventGroupWaitBits(xEventGroup, xBitstoWaitFor, pdTRUE, pdFALSE, portMAX_DELAY); 

        if( ( xEventGroupValue & ACTIVATE_BIT ) != 0 )
        {
            /*Call activate function*/ 
            ESP_LOGI(STATE_TASK_TAG, "ATTEMPTING MATRIX CONTROLLER HARD ACTIVATION");
            if(xDisplayTaskHandle == NULL)
            {
                ESP_LOGI(STATE_TASK_TAG, "DISPLAY TASK NON-EXISTENT OR HANDLE UNALLOCATED, ATTEMPTING CREATION!");

                xTaskCreate(DisplayTask, "DisplayTask", 8192, NULL, 1, &xDisplayTaskHandle);

                if(xDisplayTaskHandle != NULL)
                {
                    ESP_LOGI(STATE_TASK_TAG, "DISPLAY TASK CREATED OR EXISTS");
                }
                else
                {
                    ESP_LOGE(STATE_TASK_TAG, "FUNCTION:[%s] DISPLAY TASK CREATION FAILED! CHECK HEAP MEMORY!",
                                             __func__);
                } 
            }
            else
            {
                ESP_LOGE(STATE_TASK_TAG, "FUNCTION:[%s] DISPLAY TASK EXISTS OR HANDLE ALLOCATED!", __func__);    
            }

        }
        else if( ( xEventGroupValue & DEACTIVATE_BIT ) != 0 )
        {
            ESP_LOGI(STATE_TASK_TAG, "ATTEMPTING MATRIX CONTROLLER SOFT DEACTIVATION");
            /*Call deactivate function*/
            if(state_param->matrix_instance_ptr->system_state == active)
            {
                matrix_deactivate(state_param->matrix_instance_ptr, state_param->system_variables_ptr);
                ESP_LOGI(STATE_TASK_TAG, "SOFT DEACTIVATED MATRIX CONTROLLER");
            }
            else
            {
                ESP_LOGI(STATE_TASK_TAG, "MATRIX CONTROLLER ALREADY SOFT DEACTIVATED, SILENTLY IGNORING REQUEST");
            }      
        }
        else if( ( xEventGroupValue & STOP_DISPLAY ) != 0 )
        {
            /*Delete the display task so as not to consume CPU time when not needed*/
            if(xDisplayTaskHandle != NULL)
            {
                vTaskDelete(xDisplayTaskHandle);
                xDisplayTaskHandle=NULL;
                ESP_LOGI(STATE_TASK_TAG, "HARD DEACTIVATION! DELETED DISPLAY TASK!")
            }
            else
            {
                ESP_LOGE(STATE_TASK_TAG, "UNABLE TO HARD DEACTIVATE DUE TO ALREADY NON-EXISTENT DISPLAY TASK!")
            }
        }
    }
        
}

void app_main(void)
{
    xEventGroup = xEventGroupCreate();
    
    set_controller_event_group(xEventGroup);
    set_ble_event_group(xEventGroup);

    xTaskCreate(DisplayTask, "DisplayTask", 8192, NULL, 1, &xDisplayTaskHandle);
    xTaskCreate(LoaderTask, "LoaderTask", 4096, (void*)&system_variables, 1, &xLoaderTaskHandle);
    xTaskCreate(StateTask, "StateTask", 4096, (void*)&generic_task_parameters, 1, &xStateTaskHandle);

    if(xDisplayTaskHandle != NULL)
    {
        ESP_LOGI(APP_MAIN_TAG, "DisplayTask and LoaderTask created");
    }
    else
    {
        ESP_LOGE(APP_MAIN_TAG, "function:\"%s\" DisplayTask and/or LoaderTask CREATION FAILED! CHECK HEAP MEMORY",
                               __func__);
    }
}
//TODO: Move speed from system initialisation at start and implement in parameters in func write_speed/update_speed .
