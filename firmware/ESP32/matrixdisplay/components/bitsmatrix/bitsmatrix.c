/* Thread aware FREERTOS-ESP IDF compatible library */
/* Author: Alois Mbutura*/

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "bitsmatrix.h"
#include "bitsfont.h"

#ifdef DEBUG_PROG
/*Stdio header file- stdout retargetted to serial*/
#include <stdio.h>
#endif

static void shift_and_latch(uint8_t row_data)
{
    /*Bitbangs the data on the shit registers by controlling the data and shift and latch clocks*/
    /* The effect of clockskew should be accounted for,to ensure the clock pulse has effectively propagated*/ 
    /*local variable initialisation*/
    //printf("\t\t\t\t\t\tEntryshiftnlatch\n");
    //printf("row_data: %#08x\n", row_data);
    row_data=(uint8_t)row_data;
    printf("size of row to latch:%d\n",sizeof(row_data));
    uint8_t Mask = 0x80;
    uint8_t current_bit=0;
    for (unsigned int pos=0; pos<(sizeof(Mask)*8U); pos++)
    {
        /*Query bit status at position given by the bitmask*/
        /*https://en.wikipedia.org/wiki/Mask_(computing)*/
        current_bit = row_data & Mask;
        //printf("size of mask:%d\n",sizeof(Mask));
        if(current_bit==0)
        {
            /*If queried bit is reset, output a low state '0' on GPIO connected to SER line*/         

#ifdef USE_ESPIDF
            //printf("Bit: 0\n");
            gpio_set_level(SER, 0);
#else
            /*Auxillary platorm code here*/
            /*col_data = 0U;*/
#endif
        }
        else
        {
            /*If queried bit is set, output a high state '1' on GPIO connected to SER line*/         
#ifdef USE_ESPIDF
            //printf("Bit: 1\n");
            gpio_set_level(SER, 1);
#else
            /*Auxillary platorm code goes here*/
            /*col_data = 1U;*/
#endif
        }
        /*Quick temporay toggle to a high state on GPIO connected to SH_Clk bus*/
        /*Shift data on rising edge*/
#ifdef USE_ESPIDF
        gpio_set_level(SH_CLK, 1);
        //printf("GPIO SHCLK status: %d\n", gpio_get_level(SH_CLK));
        gpio_set_level(SH_CLK, 0);
        //printf("GPIO SHCLK status: %d\n", gpio_get_level(SH_CLK));
#else
        /*Auxillary platorm code goes here*/
        /*col_srclk = 1U;*/
        /*col_srlck = 0U;*/
#endif
        /*left shift bitmask by 1 bit position.*/
        Mask >>= 1;
    }
    /*Quick temporay toggle to a high state on GPIO connected to ST_Clk bus*/
    /*latch data on rising edge*/
#ifdef USE_ESPIDF
    gpio_set_level(ST_CLK, 1);
    gpio_set_level(ST_CLK, 0);
#else
    /*Auxillary platorm code goes here*/
    /*col_rck = 1U;*/
    /*col_rck = 0U;*/
#endif
}


void display(char message[], uint8_t speed)
{
    uint8_t buffer[NUMROWS]={0,0,0,0,0,0,0,0};
    uint8_t  temp;
    uint8_t shift_step=1;
    uint16_t string_length; //String length should not pass 32768.
    char index;

    /*Obtain message length*/
    string_length = strlen(message);
    //printf("Stringlength is %u\n",string_length);
    for (unsigned int k=0; k<string_length; k++)
    {
        //printf("letter:%u \n",k);
        for (unsigned int scroll=0; scroll<(CHAR_WIDTH/shift_step); scroll++)
        {
            //printf("\tscroll:%u \n",scroll);
            for (unsigned int row=0; row<NUMROWS; row++)
            {
                //printf("\t\trow:%u \n",row);
                /*Obtain current letter from the message*/
                index = message[k];
                /*Obtain the letter's dot matrix representation in CharData matrix.*/
                temp = CharData[index-32][row];
                /*Fill Display buffer based on it's shift amount.*/
                //printf("chardata %d",CharData[index-32U][row]);
                //buffer row=original 32 bits row OR temp>>(Numrows-shifstep)--scroll*shift_step
                //printf("letter:%u \n",k);
                //printf("original buffer: %#08x\n", buffer[row]);
                //printf("original buffer: %#08x\n", buffer[row]);
                buffer[row] = (buffer[row] << shift_step)|(temp >> ((CHAR_WIDTH-shift_step)-scroll*shift_step));
                //printf("updated buffer: %#08x\n", buffer[row]);
            }
            for(unsigned int l=0; l<speed;l++)
            {
                //printf("\t\t\tl:%u \n",l);
                for (unsigned int i=0; i<NUMROWS; i++)
                {
                  //printf("\t\t\t\ti:%u \n",i);
                    
                    if(i==7)
                    {
                        //printf("size of buffer:%d\n",sizeof(buffer[0]));
                        shift_and_latch(buffer[0]);
                    }
                    else
                    {
                        //printf("size of buffer:%d\n",sizeof(buffer[i+1]));
                        shift_and_latch(buffer[i+1]);
                    }
#ifdef USE_ESPIDF
                    //printf("\t\t\t\tCD4017CLK");
                    gpio_set_level(CD4017_CLK, 1);
                    gpio_set_level(CD4017_CLK, 0);
                    //printf("\t\t\t\tCD4017CLK");
                    vTaskDelay(1 / portTICK_PERIOD_MS);
#else
                    /*Auxillary platorm code goes here*/
                    /*CD4017_Clk = 1U;:*/
                    /*CD4017_Clk = 0U;*/
                    /*Delay_ms(1);*/
#endif
                }
                /*pulse the decade counter reset line before it reaches the 9th count*/
#ifdef USE_ESPIDF
                //printf("\t\t\t\tCD4017RST");
                gpio_set_level(CD4017_RST, 1U);
                gpio_set_level(CD4017_RST, 0U);
                //printf("\t\t\t\tCD4017RST");
#else
                /*Auxillary platorm code goes here*/
                /*CD4017_Rst = 1;*/
                /*CD4017_Rst = 0;*/
#endif
            }
        }
    }
}

