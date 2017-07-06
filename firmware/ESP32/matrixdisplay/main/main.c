#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "bitsmatrix.h"

#ifdef DEBUG_PROG
#include <stdio.h>
#endif

void app_main(void)
{

    char message[] = "BITCOIN   ";
    uint8_t speed=3;

    gpio_pad_select_gpio(CD4017_RST);
    gpio_set_direction(CD4017_RST, GPIO_MODE_OUTPUT);
    
    gpio_pad_select_gpio(CD4017_CLK);
    gpio_set_direction(CD4017_CLK, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(SH_CLK);
    gpio_set_direction(SH_CLK, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(ST_CLK);
    gpio_set_direction(ST_CLK, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(SER);
    gpio_set_direction(SER, GPIO_MODE_OUTPUT);
    while(1)
    {
        display(message,speed);
    }
}
