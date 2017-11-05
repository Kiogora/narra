/*Author: alois mbutura<aloismbutura@gmail.com>

 Copyright 2017 Bitsoko services LTD

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
/*Standard C libs*/
#include <stdint.h>
#include <stddef.h>

/*ESP-IDF libs*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

/*project libs*/
#include "glyphmap.h"
#include "narra_system.h"
#include "narra_defines.h"
#include "utf8_decoder.h"
#include "scrolling_effect.h"

static const char* TAG = "RENDERER_API";

static void shift_and_latch(Matrix* matrixInstanceptr, uint64_t row_data)
{
/*    ESP_LOGD(TAG, "ENTERED FUNCTION [%s]", __func__);*/
    /* The effect of clockskew should be accounted for,to ensure the clock pulse has effectively propagated*/ 
    uint64_t Mask = 0x8000000000000000;
    uint64_t flag=0;
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
/*    ESP_LOGD(TAG, "ENTERED FUNCTION [%s]", __func__);*/
    uint64_t buffer[8]={0,0,0,0,0,0,0,0};
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
                    else if(i >= 0 && i < 7)
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

