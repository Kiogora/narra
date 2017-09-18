#ifndef __NARRA_SYSTEM_H_
#define __NARRA_SYSTEM_H_

#include "narra_types.h"

/**
    @typedef struct Matrix
    @brief Allows several matrix to be setup and allocated memory. Each accessed individually by a common API.
**/
typedef struct
{

    char* current_message;
    narra_pin_t serial_pin;
    narra_pin_t shift_pin;
    narra_pin_t latch_pin;
    narra_pin_t rowclk_pin;
    narra_pin_t rowrst_pin;
    narra_xristics_t   num_rows;
    narra_xristics_t   num_cols;
    narra_xristics_t   unit_per_matrix;
    narra_font_t       fontwidth;
    narra_speed_enum   speed;
    narra_state_enum   system_state;
 
} Matrix;

#endif /*__NARRA_SYSTEM_H_*/
