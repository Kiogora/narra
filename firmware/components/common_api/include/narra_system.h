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
