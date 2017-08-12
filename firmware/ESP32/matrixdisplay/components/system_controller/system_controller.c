
/*Standard C libs*/
#include <stdint.h>
#include <string.h>

/*ESP-IDF libs*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*project libs*/
#include "system_loader.h"
#include "system_controller.h"
#include "utf8_decoder.h"
#include "scroll_renderer.h"

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

    matrixInstanceptr->message_state=startup;
    matrixInstanceptr->current_message=NULL;
    system_init(matrixInstanceptr);
/* Set/reset setup flag*/
    matrixInstanceptr->enable_state=enabled;
}
    
/*Matrix display function*/
void system_display(Matrix* matrixInstanceptr, rendertype _renderx)
{
    size_t utf8_length;
    char* narra_spacer="     ";
    char* unprocessed_string=(char*)malloc(strlen(matrixInstanceptr->current_message)+strlen(narra_spacer)+1);
    strcpy(unprocessed_string,matrixInstanceptr->current_message);
    strcat(unprocessed_string, narra_spacer);
    /*check byte buffer for UTF8 validity*/
    uint8_t invalid = check_valid_UTF8(unprocessed_string, &utf8_length);
    if(!invalid)
    {
        uint32_t* utf8string = (uint32_t*)malloc(sizeof(uint32_t)*utf8_length);
        memset(utf8string, 0, sizeof(uint32_t)*utf8_length);

        utf8string_create(utf8string,unprocessed_string);
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
