/* Thread aware FREERTOS-ESP IDF compatible matrix control library */
/* Author: Alois Mbutura*/

#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "bitsmatrix.h"
#include "bitsfont.h"

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

//Column control function.
static void shift_and_latch(Matrix* matrixInstanceptr, uint32_t row_data)
{
    /*Bitbangs the data on the shit registers by controlling the data and shift and latch clocks*/
    /* The effect of clockskew should be accounted for,to ensure the clock pulse has effectively propagated*/ 
#ifdef FLIP_MATRIX
    uint32_t Mask = 0x000000001;
#else
    uint32_t Mask = 0x80000000;
#endif

    uint32_t flag=0;
    for (unsigned int pos=0; pos<(sizeof(Mask)*8); pos++)
    {
        /*Query bit status at position given by the bitmask*/
        /*https://en.wikipedia.org/wiki/Mask_(computing)*/
        flag = row_data & Mask;
        if((flag & Mask) != Mask)
        {
            /*If queried bit is reset, output a low state '0' on GPIO connected to serial_pin line*/         
            gpio_set_level(matrixInstanceptr->serial_pin, LOW);
        }
        else
        {
            /*If queried bit is set, output a high state '1' on GPIO connected to serial_pin line*/         
            gpio_set_level(matrixInstanceptr->serial_pin, HIGH);
        }
        /*Quick temporay toggle to a high state on GPIO connected to serial_pin bus*/
        /*Shift data on rising edge*/
        gpio_set_level(matrixInstanceptr->shift_pin, HIGH);
        gpio_set_level(matrixInstanceptr->shift_pin, LOW);
#ifdef FLIP_MATRIX
        Mask<<=1;
#else
        Mask>>=1;
#endif
    }
    /*Quick temporay toggle to a high state on GPIO connected to latch_pin bus*/
    /*latch data on rising edge*/
    gpio_set_level(matrixInstanceptr->latch_pin, HIGH);
    gpio_set_level(matrixInstanceptr->latch_pin, LOW);
}

/*Public functions*/
/******************/

//setup matrix
void matrix_setup(Matrix* matrixInstanceptr, matrix_pin_t _serial_pin, matrix_pin_t _shift_pin, matrix_pin_t _latch_pin,
                  matrix_pin_t _rowclk_pin, matrix_pin_t _rowrst_pin, speedtype_enum _speed)
{
/*Hardcoded characteristics*/ 
/*******************************************************************************/
    matrixInstanceptr->unit_per_matrix=4;
    matrixInstanceptr->fontwidth=fontwidth_8;
    matrixInstanceptr->num_rows=numrow_8;
    matrixInstanceptr->num_cols=numcol_8;

/*Preliminary sanity check(s)*/
/*******************************************************************************/
/*Speed check*/
    if (IS_SPEED(_speed))
    {
        matrixInstanceptr->speed=_speed;
    }    
    else
    {
        matrixInstanceptr->speed=scroll_speed_5;
    }

/*******************************************************************************/
/*Matrix control pins*/
    matrixInstanceptr->serial_pin=_serial_pin;
    matrixInstanceptr->shift_pin=_shift_pin;
    matrixInstanceptr->latch_pin=_latch_pin;
    matrixInstanceptr->rowclk_pin=_rowclk_pin;
    matrixInstanceptr->rowrst_pin=_rowrst_pin;


    strcpy(matrixInstanceptr->message,"BITSOKO    ");

    matrix_init(matrixInstanceptr);

/* Set/reset setup flag*/
    matrixInstanceptr->is_setup=yes;
}

//Row representation and row control function.
void display(Matrix* matrixInstanceptr)
{
    uint32_t buffer[numrow_8]={0,0,0,0,0,0,0,0};
    uint32_t  temp;
    uint8_t shift_step=1;
    uint16_t string_length;
    char index;

    /*Obtain message length*/
    string_length = strlen(matrixInstanceptr->message);
    for (unsigned int k=0; k<string_length; k++)
    {
        for (unsigned int scroll=0; scroll<(matrixInstanceptr->fontwidth/shift_step); scroll++)
        {
            for (unsigned int row=0; row<matrixInstanceptr->num_rows; row++)
            {
                /*Obtain current letter from the message*/
                index = matrixInstanceptr->message[k];
                /*Obtain the letter's dot matrix representation in CharData matrix.*/
                temp = CharData[index-32][row];
                /*Fill Display buffer based on it's shift amount.*/
#ifdef FLIP_MATRIX
                buffer[row] = (buffer[row] << shift_step)|(temp << (scroll*shift_step));
#else
                buffer[row] = (buffer[row] << shift_step)|(temp >> ((matrixInstanceptr->fontwidth-shift_step)-(scroll*shift_step)));
#endif
            }
            for(unsigned int l=0; l<matrixInstanceptr->speed;l++)
            {
                for (unsigned int i=0; i<matrixInstanceptr->num_rows; i++)
                {
#ifdef FLIP_MATRIX
                    if(i==7)
                    {
                        shift_and_latch(matrixInstanceptr, buffer[7]);
                    }
                    else
                    {
                        shift_and_latch(matrixInstanceptr, buffer[i+1]);
                    }
#else
                    if(i==7)
                    {
                        shift_and_latch(matrixInstanceptr, buffer[0]);
                    }
                    else
                    {
                        shift_and_latch(matrixInstanceptr, buffer[i+1]);
                    }
#endif                   
                    gpio_set_level(matrixInstanceptr->rowclk_pin, HIGH);
                    gpio_set_level(matrixInstanceptr->rowclk_pin, LOW);
                    vTaskDelay(1 / portTICK_PERIOD_MS);
                }
                /*pulse the decade counter reset line before it reaches the 9th count*/
                gpio_set_level(matrixInstanceptr->rowrst_pin, HIGH);
                gpio_set_level(matrixInstanceptr->rowrst_pin, LOW);
            }
        }
    }
}
