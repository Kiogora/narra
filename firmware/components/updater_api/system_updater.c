/*Standard C libs*/
#include <stddef.h>

/*ESP-IDF libs*/
#include "nvs.h"
#include "esp_system.h"
#include "esp_log.h"

/*project libs*/
#include "narra_defines.h"
#include "narra_system.h" /*Contains the matrix description struct*/
#include "narra_nvs.h"
#include "narra_parameters.h"

#include "system_updater.h"
#include "system_controller.h"/*Sets the matrix description struct, enable state member*/
#include "utf8_decoder.h"

static const char* TAG = "Component_updater";

#if defined ALLOW_SIMPLE_STARTUP_MSG_UPDATE || defined ALLOW_COMPLEX_STARTUP_MSG_UPDATE
int32_t system_update_startup(char* new_startup_msg)
{
    narra_nvs_init();
    nvs_handle system_updater;
    nvs_open("system", NVS_READWRITE, &system_updater);
    /*Test if the string is a valid UTF-8 string before commiting to write the nvs*/
    uint8_t invalid = simple_check_UTF8(new_startup_msg);
    if(!invalid)
    {
        esp_err_t err = nvs_set_str(system_updater, "startup_msg", new_startup_msg);
        /*Write to the active section of the nvs with the new message*/
        if(err == ESP_OK)
        {
            ESP_LOGI(TAG, "Write startup success");
            return ESP_OK;
        }

        else
        {
            ESP_LOGE(TAG, "Write error code %d!", err);
            return WRITE_ERROR;
        }
    }
    else
    {
        ESP_LOGE(TAG, "UTF-8 error!");
        //return invalid UTF-8 error update failed
        return UTF8_ERROR;
    }
}
#endif

#if defined ALLOW_SIMPLE_ACTIVE_MSG_UPDATE || defined ALLOW_COMPLEX_ACTIVE_MSG_UPDATE
int32_t system_update_active(char* new_active_msg)
{
    narra_nvs_init();
    nvs_handle system_updater;
    nvs_open("system", NVS_READWRITE, &system_updater);
    /*Test if the string is a valid UTF-8 string before commiting to write the nvs*/
    uint8_t invalid = simple_check_UTF8(new_active_msg);
    if(!invalid)
    {
        /*Write to the active section of the nvs with the new message*/
        esp_err_t err = nvs_set_str(system_updater, "active_msg", new_active_msg);
        if(err == ESP_OK)
        {
            ESP_LOGI(TAG, "Write active success");
            return ESP_OK;
        }
        else
        {
            ESP_LOGE(TAG, "Write error code %d!", err);
            return WRITE_ERROR;
        }
    }
    else
    {
        ESP_LOGE(TAG, "UTF-8 error!");
        //return invalid UTF-8 error update failed
        return UTF8_ERROR;
    }
}
#endif

#if defined ALLOW_SIMPLE_SHUTDOWN_MSG_UPDATE || defined ALLOW_COMPLEX_SHUTDOWN_MSG_UPDATE
int32_t system_update_shutdown(char* new_shutdown_msg)
{
    narra_nvs_init();
    nvs_handle system_updater;
    nvs_open("system", NVS_READWRITE, &system_updater);
    /*Test if the string is a valid UTF-8 string before commiting to write the nvs*/
    uint8_t invalid = simple_check_UTF8(new_shutdown_msg);
    if(!invalid)
    {
        esp_err_t err = nvs_set_str(system_updater, "shutdown_msg", new_shutdown_msg);
        /*Write to the active section of the nvs with the new message*/
        if (err == ESP_OK)
        {
            ESP_LOGI(TAG, "Write active success");          
            return ESP_OK;
        }
        else
        {
            ESP_LOGE(TAG, "Write error code %d!", err);
            return WRITE_ERROR;
        }
    }
    else
    {
        ESP_LOGE(TAG, "UTF-8 error!");
        //return invalid UTF-8 error update failed
        return UTF8_ERROR;
    }
}
#endif
