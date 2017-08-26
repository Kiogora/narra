#ifndef __SYSTEM_CONTROLLER_H_
#define __SYSTEM_CONTROLLER_H_

#include "narra_system.h"
#include "narra_parameters.h"
#include "narra_types.h"

/***********************************************************************************/
/*Public function prototypes go here*/
/***********************************************************************************/

esp_err_t matrix_init(Matrix* matrixInstanceptr, System_variables* system_variables, narra_speed_enum _speed);

void matrix_display(Matrix* matrixInstanceptr, System_variables* system_variables, narra_rendertype_enum _renderx);

void matrix_activate(Matrix* matrixInstanceptr);

void matrix_deactivate(Matrix* matrixInstanceptr, System_variables* system_variables);

void matrix_reboot(void);

#endif /*__SYSTEM_CONTROLLER_H_*/

