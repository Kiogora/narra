#ifndef __SYSTEM_UPDATER_H_
#define __SYSTEM_UPDATER_H_

#include "narra_types.h"
#include "narra_defines.h"

#if defined ALLOW_SIMPLE_STARTUP_MSG_UPDATE || defined ALLOW_COMPLEX_STARTUP_MSG_UPDATE
int32_t system_update_startup(char* new_startup_msg);
#endif
#if defined ALLOW_SIMPLE_ACTIVE_MSG_UPDATE || defined ALLOW_COMPLEX_ACTIVE_MSG_UPDATE
int32_t system_update_active(char* new_active_msg);
#endif
#if defined ALLOW_SIMPLE_SHUTDOWN_MSG_UPDATE || defined ALLOW_COMPLEX_SHUTDOWN_MSG_UPDATE
int32_t system_update_shutdown(char* new_shutdown_msg);
#endif

#endif /*__SYSTEM_UPDATER_H_*/

//TODO: Section the update function internals above to change based on the above preprocessor macros. Maybe edit the bootloader?
