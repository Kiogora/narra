#include <stddef.h>
#include <stdint.h>
#include "esp_partition.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "narra_parameters.h"
#include <string.h>
#include "nvs.h"
#include "narra_nvs.h"
#include "system_loader.h"
#ifdef DEBUG_LOADER
#include "stdio.h"
#endif


//static void string_load(System_variables* instanceptr, char* key);

static esp_err_t narra_load_startup_msg(System_variables* instanceptr)
{
    nvs_handle system_loader;
    esp_err_t err = nvs_open("system", NVS_READONLY, &system_loader);
#ifdef DEBUG_LOADER
    if(err == ESP_ERR_NVS_NOT_FOUND)
    {
        printf("The system namespace was not found in read only mode\n");
    }
    else if(err == ESP_OK)
    {
        printf("The system namespace was found in read only mode\n");
    }
#endif
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
        instanceptr->startup_msg = malloc(string_size);
        err = nvs_get_str(system_loader, "startup_msg", instanceptr->startup_msg, &string_size);
#ifdef DEBUG_LOADER
        printf("Startup message is %s\n", instanceptr->startup_msg);
#endif
    }
    else
    {
        instanceptr->startup_msg = malloc(strlen("ERROR!")+1);
        strcpy(instanceptr->startup_msg,"ERROR!");
#ifdef DEBUG_LOADER
        printf("Startup message is %s\n", instanceptr->startup_msg);
#endif
    }
    nvs_close(system_loader);
    return err;   
}

static esp_err_t narra_load_shutdown_msg(System_variables* instanceptr)
{
    nvs_handle system_loader;
    esp_err_t err = nvs_open("system", NVS_READONLY, &system_loader);
#ifdef DEBUG_LOADER
    if(err == ESP_ERR_NVS_NOT_FOUND)
    {
        printf("The system namespace was not found in read only mode\n");
    }
    else if(err == ESP_OK)
    {
        printf("The system namespace was found in read only mode\n");
    }
#endif
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
        instanceptr->shutdown_msg = malloc(string_size);
        err = nvs_get_str(system_loader, "shutdown_msg", instanceptr->shutdown_msg, &string_size);
#ifdef DEBUG_LOADER
        printf("Shutdown message is %s\n", instanceptr->shutdown_msg);
#endif
    }
    else
    {
        instanceptr->shutdown_msg = malloc(strlen("ERROR!")+1);
        strcpy(instanceptr->shutdown_msg,"ERROR!");
#ifdef DEBUG_LOADER
        printf("Shutdown message is %s\n", instanceptr->shutdown_msg);
#endif
    }
    nvs_close(system_loader);
    return err; 
}

static esp_err_t narra_load_active_msg(System_variables* instanceptr)
{
    nvs_handle system_loader;
    esp_err_t err = nvs_open("system", NVS_READONLY, &system_loader);
#ifdef DEBUG_LOADER
    if(err == ESP_ERR_NVS_NOT_FOUND)
    {
        printf("The system namespace was not found in read only mode\n");
    }
    else if(err == ESP_OK)
    {
        printf("The system namespace was found in read only mode\n");
    }
#endif
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
        instanceptr->active_msg = malloc(string_size);
        err = nvs_get_str(system_loader, "active_msg", instanceptr->active_msg, &string_size);
#ifdef DEBUG_LOADER
        printf("Active message is %s\n", instanceptr->active_msg);
#endif
    }
    else
    {
        instanceptr->active_msg = malloc(strlen("ERROR!")+1);
        strcpy(instanceptr->active_msg,"ERROR!");
#ifdef DEBUG_LOADER
        printf("Active message is %s\n", instanceptr->active_msg);
#endif
    }
    nvs_close(system_loader);
    return err; 
}

int32_t system_loader(System_variables* instanceptr)
{

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
