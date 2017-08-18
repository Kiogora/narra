#include "stddef.h"
#include "esp_system.h"
#include "system_updater.h"
#include "utf8_decoder.h"
#include "nvs.h"
#include "narra_nvs.h"
#ifdef DEBUG_UPDATER
#include "stdio.h"
#endif

#ifdef ALLOW_STARTUP_MSG_UPDATE
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
#ifdef DEBUG_UPDATER
            printf("Write startup success\n");
#endif
            return ESP_OK;
        }

        else
        {
#ifdef DEBUG_UPDATER
            printf("Write error code %d!\n",err);
#endif
            return WRITE_ERROR;
        }
    }
    else
    {
#ifdef DEBUG_UPDATER
        printf("UTF-8 error!\n");
#endif
        //return invalid UTF-8 error update failed
        return UTF8_ERROR;
    }
}
#endif

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
#ifdef DEBUG_UPDATER
            printf("Write active success\n");
#endif
            return ESP_OK;
        }
        else
        {
#ifdef DEBUG_UPDATER
            printf("Write error code %d!\n",err);
#endif
            return WRITE_ERROR;
        }
    }
    else
    {
#ifdef DEBUG_UPDATER
        printf("UTF-8 error!\n");
#endif
        //return invalid UTF-8 error update failed
        return UTF8_ERROR;
    }
}

#ifdef ALLOW_SHUTDOWN_MSG_UPDATE
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
#ifdef DEBUG_UPDATER
            printf("Write shutdown success\n");
#endif
            return ESP_OK;
        }
        else
        {
#ifdef DEBUG_UPDATER
            printf("Write error code %d!\n",err);
#endif
            return WRITE_ERROR;
        }
    }
    else
    {
#ifdef DEBUG_UPDATER
        printf("UTF-8 error!\n");
#endif
        //return invalid UTF-8 error update failed
        return UTF8_ERROR;
    }
}
#endif
