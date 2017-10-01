/*Standard C libs*/
#include <stdint.h>
#include <string.h>

/*ESP-IDF libs*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"

/*project libs*/
#include "narra_types.h"
#include "narra_parameters.h"
#include "narra_system.h"
#include "narra_defines.h"

#include "system_controller.h"
#include "system_loader.h"
#include "scrolling_effect.h"
#include "utf8_decoder.h"

static const char* TAG = "CONTROLLER_API";

/*Task synchronisation event group*/
EventGroupHandle_t xControllerEventGroup = NULL;

/*Private functions*/
/*******************/
/* You can change this function's contents depending on the embedded platform*/
static esp_err_t init_pin_interface(Matrix* matrixInstanceptr)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION [%s]", __func__);
    gpio_pad_select_gpio(matrixInstanceptr->serial_pin);
    gpio_pad_select_gpio(matrixInstanceptr->shift_pin);
    gpio_pad_select_gpio(matrixInstanceptr->latch_pin);
    gpio_pad_select_gpio(matrixInstanceptr->rowclk_pin);
    gpio_pad_select_gpio(matrixInstanceptr->rowrst_pin);
    gpio_set_direction(matrixInstanceptr->serial_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(matrixInstanceptr->shift_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(matrixInstanceptr->latch_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(matrixInstanceptr->rowclk_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(matrixInstanceptr->rowrst_pin, GPIO_MODE_OUTPUT);

    return ESP_OK;
}

static char* add_txt_spacer(Matrix* matrixInstanceptr, char* spacer)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION [%s]", __func__);
    if(spacer != NULL && matrixInstanceptr->current_message != NULL)
    {
/*
        Pointer OK!
*/
        char* spaced_string=(char*)malloc(strlen(matrixInstanceptr->current_message)+strlen(spacer)+1);

        strcpy(spaced_string, matrixInstanceptr->current_message);

        strcat(spaced_string, spacer);

        return spaced_string;
    }
    else
    {
/*        
        NULL pointer dereferencing exception!
*/
        return matrixInstanceptr->current_message;
    }
}

static void show(Matrix* matrixInstanceptr, System_variables* system_variables, narra_rendertype_enum _renderx)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION [%s]", __func__);
    char* unprocessed_string = add_txt_spacer(matrixInstanceptr, "    ");

    if(unprocessed_string != NULL)
    {
        /*check byte buffer for UTF8 validity*/
        size_t utf8_length;
        uint8_t invalid = check_count_valid_UTF8(unprocessed_string, &utf8_length);

        if(!invalid)
        {
            uint32_t* utf8string = (uint32_t*)malloc(sizeof(uint32_t)*utf8_length);
            memset(utf8string, 0, sizeof(uint32_t)*utf8_length);

            utf8string_create(utf8string, unprocessed_string);
            switch(_renderx)
            {
                case scroll:
                    scrolling_effect(matrixInstanceptr, utf8string, utf8_length);
                    break;
            }
            free(utf8string);
        }
        else
        {
            /*implement invalid UTF8 exception handling or invalid char pointer here.*/
            /*This may not actually be an error as for shutdown state the current message after scroll us NULL!*/
        }
    }
}


/*Public functions*/
/******************/

/*setup matrix*/
esp_err_t matrix_init(Matrix* matrixInstanceptr, System_variables* system_variables, narra_speed_enum _speed)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION [%s]", __func__);
    int32_t loader_return_code = system_loader(system_variables);

    if (loader_return_code == NVS_INIT_ERROR)
    {
        /*Non-recoverable loader error*/
        return ESP_FAIL;
    }
    else
    {

        if(IS_SPEED_VALID(_speed))
        {
            matrixInstanceptr->speed=_speed;
        }
        else
        {
            ESP_LOGE(TAG,"Invalid system speed passed to init function");
            return ESP_FAIL;
        }

        matrixInstanceptr->unit_per_matrix=0x08;
        matrixInstanceptr->fontwidth=0x08;
        matrixInstanceptr->num_rows=0x08;
        matrixInstanceptr->num_cols=0x08;
        
        matrixInstanceptr->system_state=startup;
        matrixInstanceptr->current_message=NULL;

        esp_err_t err = init_pin_interface(matrixInstanceptr);

        if(err == ESP_OK)
        {    
            matrix_display(matrixInstanceptr, system_variables, scroll);
            matrix_activate(matrixInstanceptr);
        }

        return err;
    }
}

void matrix_activate(Matrix* matrixInstanceptr)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION [%s]", __func__);

    if(matrixInstanceptr->system_state == shutdown)
    {
        matrixInstanceptr->system_state=startup;
    }
}

void matrix_deactivate(Matrix* matrixInstanceptr, System_variables* system_variables)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION [%s]", __func__);

    if(matrixInstanceptr->system_state == active)
    {
        matrixInstanceptr->system_state=shutdown;
    }
}

void set_controller_event_group(EventGroupHandle_t event_group)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION [%s]", __func__);
    if(event_group != NULL)
    {
        xControllerEventGroup=event_group;
        ESP_LOGI(TAG, "SET CONTROLLER EVENT GROUP");
    }
    else
    {
        ESP_LOGE(TAG, "UNABLE TO SET CONTROLLER EVENT GROUP! CHECK HEAP MEMORY");
    }
}
    
/*Matrix display function*/
void matrix_display(Matrix* matrixInstanceptr, System_variables* system_variables, narra_rendertype_enum _renderx)
{
    ESP_LOGD(TAG, "ENTERED FUNCTION [%s]", __func__);
    EventBits_t delete_display = STOP_DISPLAY;

    switch(matrixInstanceptr->system_state)
    {
        case(startup):
            matrixInstanceptr->current_message=system_variables->startup_msg;
            show(matrixInstanceptr, system_variables, scroll);
            matrixInstanceptr->system_state=active;
            break;
        case(active):
            matrixInstanceptr->current_message=system_variables->active_msg;
            show(matrixInstanceptr, system_variables, _renderx);
            break;
        case(shutdown):
            matrixInstanceptr->current_message=system_variables->shutdown_msg;
            show(matrixInstanceptr, system_variables, scroll);
            matrixInstanceptr->current_message=NULL;
            xEventGroupSetBits(xControllerEventGroup, delete_display);
            break;
    }
}

//TODO-Add check if the active CRC = realtime calculated CRC. If not display recovery.
