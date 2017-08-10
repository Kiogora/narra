/* Thread aware FREERTOS-ESP IDF compatible matrix control library */
/* Author: Alois Mbutura*/

#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "displaycontroller.h"
#include "utf8_decoder.h"
#include "renderchaser.h"

/*Private functions*/
/*******************/
static void matrix_init(Matrix* matrixInstanceptr)
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
void matrix_setup(Matrix* matrixInstanceptr, matrix_pin_t _serial_pin, matrix_pin_t _shift_pin, matrix_pin_t _latch_pin, matrix_pin_t _rowclk_pin, matrix_pin_t _rowrst_pin, speedtype_enum _speed)
{
    matrixInstanceptr->unit_per_matrix=4;
    matrixInstanceptr->fontwidth=fontwidth_8;
    matrixInstanceptr->num_rows=numrow_8;
    matrixInstanceptr->num_cols=numcol_8;

/*Speed check*/
    if (IS_SPEED(_speed))
    {
        matrixInstanceptr->speed=_speed;
    }    
    else
    {
        matrixInstanceptr->speed=scroll_speed_5;
    }

/*Matrix control pins*/
    matrixInstanceptr->serial_pin=_serial_pin;
    matrixInstanceptr->shift_pin=_shift_pin;
    matrixInstanceptr->latch_pin=_latch_pin;
    matrixInstanceptr->rowclk_pin=_rowclk_pin;
    matrixInstanceptr->rowrst_pin=_rowrst_pin;

    strcpy(matrixInstanceptr->bytesequence,"C®26     ");
    matrix_init(matrixInstanceptr);

/* Set/reset setup flag*/
    matrixInstanceptr->is_setup=yes;
}
    
/*Matrix display function*/
void display(Matrix* matrixInstanceptr, rendertype _renderx)
{
    size_t utf8_length;
    /*check byte buffer for UTF8 validity*/
    uint8_t invalid = check_valid_UTF8(matrixInstanceptr->bytesequence, &utf8_length);

    if(!invalid)
    {
        uint32_t* utf8string = (uint32_t*)malloc(sizeof(uint32_t)*utf8_length);
        memset(utf8string, 0, sizeof(uint32_t)*utf8_length);

        utf8string_create(utf8string, matrixInstanceptr->bytesequence);
        switch(_renderx)
        {
            case scroll:
                renderchaser(matrixInstanceptr, utf8string, utf8_length);
                break;
        }
        free(utf8string);
    }
    else
    {
        //implement something
    }
}
