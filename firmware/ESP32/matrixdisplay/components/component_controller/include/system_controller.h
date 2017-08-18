#ifndef __DISPLAY_CONTROLLER_H_
#define __DISPLAY_CONTROLLER_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "narra_system.h"
#include "narra_parameters.h"

/***********************************************************************************/
/*Public function prototypes go here*/
/***********************************************************************************/

/*TODO-Implement error checking on pins based on API given by espressif.*/

void system_setup(Matrix* matrixInstanceptr, System_variables* system_variables, matrix_pin_t _serial_pin, matrix_pin_t _shift_pin, matrix_pin_t _latch_pin, matrix_pin_t _rowclk_pin, matrix_pin_t _rowrst_pin, speedtype_enum _speed);


void system_display(Matrix* matrixInstanceptr, System_variables* system_variables, rendertype _renderx);

void system_activate(Matrix* matrixInstanceptr);

void system_deactivate(Matrix* matrixInstanceptr, System_variables* system_variables);

void system_reboot(void);
#ifdef __cplusplus
}
#endif

#endif /*__CONTROLLER_H_*/

