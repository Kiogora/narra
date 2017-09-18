
/*Standard C libs*/
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/*ESP-IDF libs*/
#include "esp_partition.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

/*project libs*/
#include "narra_parameters.h"
#include "narra_nvs.h"

#include "system_loader.h"

static const char* TAG = "LOADER_API";


//static void string_load(System_variables* instanceptr, char* key);

static esp_err_t narra_load_startup_msg(System_variables* instanceptr)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION: %s", __func__);
    nvs_handle system_loader;
    esp_err_t err = nvs_open("system", NVS_READONLY, &system_loader);
    if(err == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE(TAG, "The system namespace was not found in read only mode");
    }
    else if(err == ESP_OK)
    {
        ESP_LOGI(TAG, "The system namespace was found in read only mode");
    }
    size_t string_size;
    err = nvs_get_str(system_loader, "startup_msg", NULL, &string_size);
    if (err != ESP_OK)
    {
        nvs_close(system_loader);
        nvs_open("system", NVS_READWRITE, &system_loader);
        char* test_message = "Test_startup_message";
        nvs_set_str(system_loader, "startup_msg", test_message);
        nvs_close(system_loader);
        nvs_open("system", NVS_READONLY, &system_loader);
    }
    err = nvs_get_str(system_loader, "startup_msg", NULL, &string_size);

    if(err == ESP_OK)
    {
        if(instanceptr->startup_msg == NULL)
        {
            /*This code branch is executed on boot*/
            instanceptr->startup_msg = malloc(string_size);
            err = nvs_get_str(system_loader, "startup_msg", instanceptr->startup_msg, &string_size);
            ESP_LOGI(TAG, "Initial startup message is %s", instanceptr->startup_msg);
        }
        else
        {
            /*This is after the startup message has been allocated, probably after a write during runtime*/
            free(instanceptr->startup_msg);
            instanceptr->startup_msg = NULL;
            instanceptr->startup_msg = malloc(string_size);
            err = nvs_get_str(system_loader, "startup_msg", instanceptr->startup_msg, &string_size);
            ESP_LOGI(TAG, "Current startup message is %s", instanceptr->startup_msg);          
        }
    }
    else
    {
        if(instanceptr->startup_msg == NULL)
        {
            instanceptr->startup_msg = malloc(strlen("STARTUP MESSAGE LOAD ERROR!")+1);
            strcpy(instanceptr->startup_msg,"STARTUP MESSAGE LOAD ERROR!");
            ESP_LOGE(TAG, "Initial startup message is %s", instanceptr->startup_msg);
        }
        else
        {
            free(instanceptr->startup_msg);
            instanceptr->startup_msg = NULL;
            instanceptr->startup_msg = malloc(strlen("STARTUP MESSAGE LOAD ERROR!")+1);
            strcpy(instanceptr->startup_msg,"STARTUP MESSAGE LOAD ERROR!");
            ESP_LOGE(TAG, "Current startup message is %s", instanceptr->startup_msg);    
        }
    }
    nvs_close(system_loader);
    return err;   
}

static esp_err_t narra_load_shutdown_msg(System_variables* instanceptr)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION: %s", __func__);
    nvs_handle system_loader;
    esp_err_t err = nvs_open("system", NVS_READONLY, &system_loader);
    if(err == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE(TAG, "The system namespace was not found in read only mode");
    }
    else if(err == ESP_OK)
    {
        ESP_LOGI(TAG, "The system namespace was found in read only mode");
    }
    size_t string_size;
    err = nvs_get_str(system_loader, "shutdown_msg", NULL, &string_size);
    if (err != ESP_OK)
    {
        nvs_close(system_loader);
        nvs_open("system", NVS_READWRITE, &system_loader);
        char* test_message = "Test_shutdown_message";
        nvs_set_str(system_loader, "shutdown_msg", test_message);
        nvs_close(system_loader);
        nvs_open("system", NVS_READONLY, &system_loader);
    }
    err = nvs_get_str(system_loader, "shutdown_msg", NULL, &string_size);

    if(err == ESP_OK)
    {
        if(instanceptr->shutdown_msg == NULL)
        {
            instanceptr->shutdown_msg = malloc(string_size);
            err = nvs_get_str(system_loader, "shutdown_msg", instanceptr->shutdown_msg, &string_size);
            ESP_LOGI(TAG, "Initial shutdown message is %s", instanceptr->shutdown_msg);
        }
        else
        {
            free(instanceptr->shutdown_msg);
            instanceptr->shutdown_msg = NULL;
            instanceptr->shutdown_msg = malloc(string_size);
            err = nvs_get_str(system_loader, "shutdown_msg", instanceptr->shutdown_msg, &string_size);
            ESP_LOGI(TAG, "Current shutdown message is %s", instanceptr->shutdown_msg);
        }
    }
    else
    {
        if(instanceptr->shutdown_msg == NULL)
        {
            instanceptr->shutdown_msg = malloc(strlen("SHUTDOWN MESSAGE LOAD ERROR!")+1);
            strcpy(instanceptr->shutdown_msg,"SHUTDOWN MESSAGE LOAD ERROR!");
            ESP_LOGE(TAG, "Initial shutdown message is %s", instanceptr->shutdown_msg);
        }
        else
        {
            free(instanceptr->shutdown_msg);
            instanceptr->shutdown_msg = NULL;
            instanceptr->shutdown_msg = malloc(strlen("SHUTDOWN MESSAGE LOAD ERROR!")+1);
            strcpy(instanceptr->shutdown_msg,"SHUTDOWN MESSAGE LOAD ERROR!");
            ESP_LOGE(TAG, "Current shutdown message is %s", instanceptr->shutdown_msg);
        }
    }
    nvs_close(system_loader);
    return err; 
}

static esp_err_t narra_load_active_msg(System_variables* instanceptr)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION: %s", __func__);
    nvs_handle system_loader;
    esp_err_t err = nvs_open("system", NVS_READONLY, &system_loader);
    if(err == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE(TAG, "The system namespace was not found in read only mode");
    }
    else if(err == ESP_OK)
    {
        ESP_LOGI(TAG, "The system namespace was found in read only mode");
    }
    size_t string_size;
    err = nvs_get_str(system_loader, "active_msg", NULL, &string_size);
    if (err != ESP_OK)
    {
        nvs_close(system_loader);
        nvs_open("system", NVS_READWRITE, &system_loader);
        char* test_message = "Test_active_message";
        nvs_set_str(system_loader, "active_msg", test_message);
        nvs_close(system_loader);
        nvs_open("system", NVS_READONLY, &system_loader);
    }
    err = nvs_get_str(system_loader, "active_msg", NULL, &string_size);

    if(err == ESP_OK)
    {
        if(instanceptr->active_msg == NULL)
        {
            instanceptr->active_msg = malloc(string_size);
            err = nvs_get_str(system_loader, "active_msg", instanceptr->active_msg, &string_size);
            ESP_LOGI(TAG, "Initial active message is %s\n", instanceptr->active_msg);
        }
        else
        {
            free(instanceptr->active_msg);
            instanceptr->active_msg = NULL;
            instanceptr->active_msg = malloc(string_size);
            err = nvs_get_str(system_loader, "active_msg", instanceptr->active_msg, &string_size);
            ESP_LOGI(TAG, "Current active message is %s\n", instanceptr->active_msg);
        }
    }
    else
    {
        if(instanceptr->shutdown_msg == NULL)
        {
            instanceptr->active_msg = malloc(strlen("RUNTIME MESSAGE LOAD ERROR!")+1);
            strcpy(instanceptr->active_msg,"RUNTIME MESSAGE LOAD ERROR!");
            ESP_LOGE(TAG, "Initial active message is %s\n", instanceptr->active_msg);
        }
        else
        {
            free(instanceptr->active_msg);
            instanceptr->active_msg = NULL; 
            instanceptr->active_msg = malloc(strlen("RUNTIME MESSAGE LOAD ERROR!")+1);
            strcpy(instanceptr->active_msg,"RUNTIME MESSAGE LOAD ERROR!");
            ESP_LOGE(TAG, "Current active message is %s\n", instanceptr->active_msg);
        }
    }
    nvs_close(system_loader);
    return err; 
}

int32_t system_loader(System_variables* instanceptr)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION: %s", __func__);
    if (narra_nvs_init() != ESP_OK)
    {
        return NVS_INIT_ERROR;
    }

    if (narra_load_startup_msg(instanceptr) != ESP_OK)
    {
        return STARTUP_MSG_ERROR;
    }

    if (narra_load_shutdown_msg(instanceptr) != ESP_OK)
    {
        return SHUTDOWN_MSG_ERROR;
    }

    if (narra_load_active_msg(instanceptr) != ESP_OK)
    {
        return ACTIVE_MSG_ERROR;
    }
    return ESP_OK;
}
