/* Thread aware FREERTOS-ESP IDF compatible matrix control library */
/* Author: Alois Mbutura*/

#include <stdint.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "displaycontroller.h"
#include "utf8.h"
#include "glyphmap.h"
#include <stdio.h>

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
void matrix_setup(Matrix* matrixInstanceptr, matrix_pin_t _serial_pin, matrix_pin_t _shift_pin, matrix_pin_t _latch_pin, matrix_pin_t _rowclk_pin, matrix_pin_t _rowrst_pin, speedtype_enum _speed)
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


    strcpy(matrixInstanceptr->message,"C©K52     ");

    matrix_init(matrixInstanceptr);

/* Set/reset setup flag*/
    matrixInstanceptr->is_setup=yes;
}
    
static int check_codepoints(char* string, size_t* count)
{
    uint32_t codepoint;
    uint32_t state = 0;

    for (*count = 0; *string; ++string)
    {
        if (!decode(&state, &codepoint, *string)){ *count += 1; printf("U+%08X\n", codepoint);}
    }
    return state != UTF8_ACCEPT;
}

static void utf8string_create(char* string, uint32_t* codepointbuffer)
{
    uint32_t codepoint;
    uint32_t state = 0;
    for (int k = 0; *string; ++string)
    {
        if (!decode(&state, &codepoint, *string))
        {
//TODO: Add check, memory referenced doesn't go past array bounds.
             *(codepointbuffer + (sizeof(uint32_t) * k) )  = codepoint;
//            printf("Write offset in bytes:%d", (sizeof(uint32_t) * k));
//            printf("Written location:%p\n",codepointbuffer + k);
//            printf("k:%d\n", k);
            k++;
        }
    }
}


//Row representation and row control function.
void display(Matrix* matrixInstanceptr)
{
    uint32_t buffer[numrow_8]={0,0,0,0,0,0,0,0};
    uint32_t  temp;
    uint8_t shift_step=1;
    size_t string_length;
    size_t index;
//    printf("Entered display function\n");
    /*check byte buffer for UTF8 validity*/
    uint8_t invalid = check_codepoints(matrixInstanceptr->message, &string_length);

    if(!invalid)
    {
        /*Buffer to store the utf8string of size based on codepoints found in byte buffer*/
        /*formed and freed dynamically, locally at the function level*/
        /*Avoids memory fragmentation at the global level--memory leaks?*/
        uint32_t* utf8string = (uint32_t*)malloc(sizeof(uint32_t)*string_length);
        memset(utf8string, 0, sizeof(uint32_t)*string_length);
        /*create a utf8string from the byte buffer*/
        utf8string_create(matrixInstanceptr->message, utf8string);
//        printf("stringlength: %d\n", string_length);
        for (uint32_t k=0; k<string_length; k++)
        {
//            printf("character:%d\n",k);
//            printf("value:U+%08X\n",utf8string[k*sizeof(uint32_t)]);
            for (unsigned int scroll=0; scroll<(matrixInstanceptr->fontwidth/shift_step); scroll++)
            {
                for (unsigned int row=0; row<matrixInstanceptr->num_rows; row++)
                {
                    index = utf8string[k*sizeof(uint32_t)];
                    /*Obtain the codepoint's glyph*/
                    if(IS_UTF8_CODEPOINT_IMPLEMENTED(index))
                    {
//                        if(index >= CODEPOINT_BASE_0X20 && index <= CODEPOINT_LIMIT_0X7E)
//                        {
//                        printf("Code implemented");
                        temp = utf8_0020_007E[index-CODEPOINT_BASE_0X20][row];
//                        }
                    }
                    else
                    {
//                        printf("Code NOT implemented");
                        temp = unimplemented[row];
                    }
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
    free(utf8string);
    }
    else
    {
        //implement something
    }
}
