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
//Column control function.
static void shift_and_latch(Matrix* matrixInstance, uint32_t row_data)
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
            gpio_set_level(matrixInstance->serial_pin, LOW);
        }
        else
        {
            /*If queried bit is set, output a high state '1' on GPIO connected to serial_pin line*/         
            gpio_set_level(matrixInstance->serial_pin, HIGH);
        }
        /*Quick temporay toggle to a high state on GPIO connected to serial_pin bus*/
        /*Shift data on rising edge*/
        gpio_set_level(matrixInstance->shift_pin, HIGH);
        gpio_set_level(matrixInstance->shift_pin, LOW);
#ifdef FLIP_MATRIX
        Mask<<=1;
#else
        Mask>>=1;
#endif
    }
    /*Quick temporay toggle to a high state on GPIO connected to latch_pin bus*/
    /*latch data on rising edge*/
    gpio_set_level(matrixInstance->latch_pin, HIGH);
    gpio_set_level(matrixInstance->latch_pin, LOW);
}

/*Public functions*/
/******************/

void matrix_init(Matrix* matrixInstance)
{
    gpio_pad_select_gpio(matrixInstance->serial_pin);
    gpio_pad_select_gpio(matrixInstance->shift_pin);
    gpio_pad_select_gpio(matrixInstance->latch_pin);
    gpio_pad_select_gpio(matrixInstance->rowclk_pin);
    gpio_pad_select_gpio(matrixInstance->rowrst_pin);
    gpio_set_direction(matrixInstance->serial_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(matrixInstance->shift_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(matrixInstance->latch_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(matrixInstance->rowclk_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(matrixInstance->rowrst_pin, GPIO_MODE_OUTPUT); 
}

//Row representation and row control function.
void display(Matrix* matrixInstance)
{
    uint32_t buffer[NUMROWS]={0,0,0,0,0,0,0,0};
    uint32_t  temp;
    uint8_t shift_step=1;
    uint16_t string_length;
    char index;

    /*Obtain message length*/
    string_length = strlen(matrixInstance->message);
    for (unsigned int k=0; k<string_length; k++)
    {
        for (unsigned int scroll=0; scroll<(matrixInstance->fontwidth/shift_step); scroll++)
        {
            for (unsigned int row=0; row<matrixInstance->num_rows; row++)
            {
                /*Obtain current letter from the message*/
                index = matrixInstance->message[k];
                /*Obtain the letter's dot matrix representation in CharData matrix.*/
                temp = CharData[index-32][row];
                /*Fill Display buffer based on it's shift amount.*/
#ifdef FLIP_MATRIX
                buffer[row] = (buffer[row] << shift_step)|(temp << (scroll*shift_step));
#else
                buffer[row] = (buffer[row] << shift_step)|(temp >> ((matrixInstance->fontwidth-shift_step)-(scroll*shift_step)));
#endif
            }
            for(unsigned int l=0; l<matrixInstance->speed;l++)
            {
                for (unsigned int i=0; i<matrixInstance->num_rows; i++)
                {
#ifdef FLIP_MATRIX
                    if(i==7)
                    {
                        shift_and_latch(matrixInstance, buffer[7]);
                    }
                    else
                    {
                        shift_and_latch(matrixInstance, buffer[i+1]);
                    }
#else
                    if(i==7)
                    {
                        shift_and_latch(matrixInstance, buffer[0]);
                    }
                    else
                    {
                        shift_and_latch(matrixInstance, buffer[i+1]);
                    }
#endif                   
                    gpio_set_level(matrixInstance->rowclk_pin, HIGH);
                    gpio_set_level(matrixInstance->rowclk_pin, LOW);
                    vTaskDelay(1 / portTICK_PERIOD_MS);
                }
                /*pulse the decade counter reset line before it reaches the 9th count*/
                gpio_set_level(matrixInstance->rowrst_pin, HIGH);
                gpio_set_level(matrixInstance->rowrst_pin, LOW);
            }
        }
    }
}
