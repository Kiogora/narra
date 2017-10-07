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
#ifndef __SYSTEM_CONTROLLER_H_
#define __SYSTEM_CONTROLLER_H_

#include "narra_system.h"
#include "narra_parameters.h"
#include "narra_types.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

/***********************************************************************************/
/*Public function prototypes go here*/
/***********************************************************************************/

esp_err_t matrix_init(Matrix* matrixInstanceptr, System_variables* system_variables, narra_speed_enum _speed);

void matrix_display(Matrix* matrixInstanceptr, System_variables* system_variables, narra_rendertype_enum _renderx);

void matrix_activate(Matrix* matrixInstanceptr);

void matrix_deactivate(Matrix* matrixInstanceptr, System_variables* system_variables);

void set_controller_event_group(EventGroupHandle_t event_group);


#endif /*__SYSTEM_CONTROLLER_H_*/

