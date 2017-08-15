
/*Standard C libs*/
#include <stdint.h>
#include <string.h>

/*ESP-IDF libs*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*project libs*/
#include "narra_parameters.h"
#include "system_loader.h"
#include "system_controller.h"
#include "utf8_decoder.h"
#include "scroller.h"

/*Private functions*/
/*******************/
static void system_init(Matrix* matrixInstanceptr)
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
}


/*Public functions*/
/******************/

/*setup matrix*/
void system_setup(Matrix* matrixInstanceptr, System_variables* system_variables, matrix_pin_t _serial_pin, matrix_pin_t _shift_pin, matrix_pin_t _latch_pin, matrix_pin_t _rowclk_pin, matrix_pin_t _rowrst_pin, speedtype_enum _speed)
{
    system_loader(system_variables);

    matrixInstanceptr->unit_per_matrix=0x08;
    matrixInstanceptr->fontwidth=0x08;
    matrixInstanceptr->num_rows=0x08;
    matrixInstanceptr->num_cols=0x08;

/*Matrix control pins*/
    matrixInstanceptr->serial_pin=_serial_pin;
    matrixInstanceptr->shift_pin=_shift_pin;
    matrixInstanceptr->latch_pin=_latch_pin;
    matrixInstanceptr->rowclk_pin=_rowclk_pin;
    matrixInstanceptr->rowrst_pin=_rowrst_pin;
    
    matrixInstanceptr->speed=_speed;

    matrixInstanceptr->system_state=startup;
    matrixInstanceptr->current_message=NULL;
    system_init(matrixInstanceptr);
    
    system_display(matrixInstanceptr, system_variables, scroll);

    system_activate(matrixInstanceptr);
}

void system_activate(Matrix* matrixInstanceptr)
{
    matrixInstanceptr->system_state=active;
}

void system_deactivate(Matrix* matrixInstanceptr, System_variables* system_variables)
{
    matrixInstanceptr->system_state=shutdown;
    system_display(matrixInstanceptr, system_variables, scroll);
}
    
/*Matrix display function*/
void system_display(Matrix* matrixInstanceptr, System_variables* system_variables, rendertype _renderx)
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
        size_t utf8_length;
        char* narra_spacer="     ";
        char* unprocessed_string=(char*)malloc(strlen(matrixInstanceptr->current_message)+strlen(narra_spacer)+1);
        strcpy(unprocessed_string, matrixInstanceptr->current_message);
        strcat(unprocessed_string, narra_spacer);
        /*check byte buffer for UTF8 validity*/
        uint8_t invalid = check_count_valid_UTF8(unprocessed_string, &utf8_length);
        if(!invalid)
        {
            uint32_t* utf8string = (uint32_t*)malloc(sizeof(uint32_t)*utf8_length);
            memset(utf8string, 0, sizeof(uint32_t)*utf8_length);

            utf8string_create(utf8string, unprocessed_string);
            switch(_renderx)
            {
                case scroll:
                    renderchaser(matrixInstanceptr, utf8string, utf8_length);
                    break;
            }
            free(utf8string);
            free(unprocessed_string);
        }
        else
        {
            //implement something
        }
    }
}

//TODO-Add check if the active CRC = realtime calculated CRC. If not display recovery.
/*
        if(crcFast(test_buffer, strlen(test_buffer)) == crcFast(new_startup_msg, strlen(new_startup_msg)))
        {
            //cleanup code
            return ESP_OK;
        }
        else
        {
            nvs_set_str(system_updater, "active_msg", new_active_msg);
            return CRC_ERROR;
            //return crc error update failed
        }

*/
