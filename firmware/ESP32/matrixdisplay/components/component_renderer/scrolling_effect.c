
/*Standard C libs*/
#include <stdint.h>
#include <stddef.h>

/*ESP-IDF libs*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*project libs*/
#include "glyphmap.h"
#include "system_controller.h"
#include "utf8_decoder.h"
#include "scrolling_effect.h"

static void shift_and_latch(Matrix* matrixInstanceptr, uint32_t row_data)
{
    /* The effect of clockskew should be accounted for,to ensure the clock pulse has effectively propagated*/ 
    uint32_t Mask = 0x80000000;
    uint32_t flag=0;
    for (unsigned int pos=0; pos<(sizeof(Mask)*8); pos++)
    {
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
        Mask>>=1;
    }
    /*Quick temporay toggle to a high state on GPIO connected to latch_pin bus*/
    /*latch data on rising edge*/
    gpio_set_level(matrixInstanceptr->latch_pin, HIGH);
    gpio_set_level(matrixInstanceptr->latch_pin, LOW);
}

void scrolling_effect(Matrix* matrixInstanceptr, uint32_t* _utf8string, size_t _utf8_length)
{
    uint32_t buffer[8]={0,0,0,0,0,0,0,0};
    uint32_t  temp=0;
    uint8_t shift_step=1;
    size_t index=0;
    for (uint32_t k=0; k<_utf8_length; k++)
    {
        for (unsigned int scroll=0; scroll<(matrixInstanceptr->fontwidth/shift_step); scroll++)
        {
            for (unsigned int row=0; row<matrixInstanceptr->num_rows; row++)
            {
                index = _utf8string[k];
                /*Obtain the codepoint's glyph*/
                if(IS_UTF8_CODEPOINT_IMPLEMENTED(index))
                {
                    if (index >= codepoint_base_0x20 && index <= codepoint_limit_0x7E)
                    {
                        temp = utf8_0020_007E[index-codepoint_base_0x20][row];
                    }
                    else if (index >= codepoint_base_0xA1 && index <= codepoint_limit_0xAE)
                    {
                        temp = utf8_00A1_00AE[index-codepoint_base_0xA1][row];    
                    }
                }
                else
                {
                    temp = unimplemented[row];
                }
                /*Fill Display buffer based on it's shift amount.*/
buffer[row] = (buffer[row] << shift_step)|(temp >> ((matrixInstanceptr->fontwidth-shift_step)-(scroll*shift_step)));
            }
            for(unsigned int l=0; l<matrixInstanceptr->speed;l++)
            {             
                for (unsigned int i=0; i<matrixInstanceptr->num_rows; i++)
                {
                    if(i==7)
                    {
                        shift_and_latch(matrixInstanceptr, buffer[0]);
                    }
                    else
                    {
                        shift_and_latch(matrixInstanceptr, buffer[i+1]);
                    }                  
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

