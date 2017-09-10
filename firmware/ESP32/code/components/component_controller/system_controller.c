
/*Standard C libs*/
#include <stdint.h>
#include <string.h>

/*ESP-IDF libs*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
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

static const char* TAG = "Component_controller";

/*Private functions*/
/*******************/
/* You can change this function's contents depending on the embedded platform*/
static esp_err_t init_pin_interface(Matrix* matrixInstanceptr)
{
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
        NULL pointer dereferencing error!
*/
        return matrixInstanceptr->current_message;
    }
}


/*Public functions*/
/******************/

/*setup matrix*/
esp_err_t matrix_init(Matrix* matrixInstanceptr, System_variables* system_variables, narra_speed_enum _speed)
{
    system_loader(system_variables);

    /*Send event group to bluetooth task to start*/

    matrixInstanceptr->unit_per_matrix=0x08;
    matrixInstanceptr->fontwidth=0x08;
    matrixInstanceptr->num_rows=0x08;
    matrixInstanceptr->num_cols=0x08;
    if(IS_SPEED_VALID(_speed))
    {
        matrixInstanceptr->speed=_speed;
    }
    else
    {
        ESP_LOGE(TAG,"Invalid system speed passed to init function");
        return ESP_FAIL;
    }
    
    matrixInstanceptr->system_state=startup;
    matrixInstanceptr->current_message=NULL;

    esp_err_t err=init_pin_interface(matrixInstanceptr);

    if(err==ESP_OK)
    {    
        matrix_display(matrixInstanceptr, system_variables, scroll);
        matrix_activate(matrixInstanceptr);
    }

    return err;
}

void matrix_activate(Matrix* matrixInstanceptr)
{
    matrixInstanceptr->system_state=active;
}

void matrix_deactivate(Matrix* matrixInstanceptr, System_variables* system_variables)
{
    matrixInstanceptr->system_state=shutdown;
    matrix_display(matrixInstanceptr, system_variables, scroll);
}

void matrix_reboot(void)
{
    esp_restart();
}
    
/*Matrix display function*/
void matrix_display(Matrix* matrixInstanceptr, System_variables* system_variables, narra_rendertype_enum _renderx)
{
    if (matrixInstanceptr->system_state== startup || matrixInstanceptr->system_state== active)
    {
        switch(matrixInstanceptr->system_state)
        {
            case(startup):
                matrixInstanceptr->current_message=system_variables->startup_msg;
                break;                
            case(active):
                matrixInstanceptr->current_message=system_variables->active_msg;
                break;
            case(shutdown):
                matrixInstanceptr->current_message=system_variables->shutdown_msg;
                break;
        }
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
                free(unprocessed_string);
            }
            else
            {
                //implement invalid UTF8 exception handling here.
            }
        }
    }
}

//TODO-Add check if the active CRC = realtime calculated CRC. If not display recovery.
