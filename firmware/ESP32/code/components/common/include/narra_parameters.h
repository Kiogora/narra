#ifndef __SYSTEM_PARAMETERS_H_
#define __SYSTEM_PARAMETERS_H_

#include "narra_types.h"
#include "narra_defines.h"

/**
    @typedef struct system_variables
    @brief Struct containing the different system variables that exist on the system.
**/
typedef struct
{
    char* startup_msg;
#ifdef ALLOW_COMPLEX_STARTUP_MSG_UPDATE
#pragma message("COMPLEX STARTUP MESSAGE UPDATE ALLOWED")
    char* startup_recovery;
    uint32_t* startup_crc_checksum;
#else
#pragma message("SIMPLE STARTUP MESSAGE UPDATE ALLOWED")
#endif
    char* shutdown_msg;
#ifdef ALLOW_COMPLEX_SHUTDOWN_MSG_UPDATE
#pragma message("COMPLEX SHUTDOWN MESSAGE UPDATE ALLOWED")
    char* shutdown_recovery;
    uint32_t* shutdown_crc_checksum;
#else
#pragma message("SIMPLE SHUTDOWN MESSAGE UPDATE ALLOWED")
#endif
    char* active_msg;
#ifdef ALLOW_COMPLEX_ACTIVE_MSG_UPDATE
#pragma message("COMPLEX ACTIVE MESSAGE UPDATE ALLOWED")
    char* active_recovery;
    uint32_t* active_crc_checksum;
#else
#pragma message("SIMPLE ACTIVE MESSAGE UPDATE ALLOWED")
#endif
    narra_pin_t param_serial_pin;
    narra_pin_t param_shift_pin;
    narra_pin_t param_latch_pin;
    narra_pin_t param_rowclk_pin;
    narra_pin_t param_rowrst_pin;
} System_variables;

#endif /*__SYSTEM_PARAMETERS_H_*/
