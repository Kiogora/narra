#ifndef __SYSTEM_PARAMETERS_H_
#define __SYSTEM_PARAMETERS_H_

/**@typedef struct system_variables
   @brief Struct containing the different system variables that exist on the system.
*/
typedef struct
{
    char* startup_msg;
#ifdef ALLOW_STARTUP_UPDATE
#pragma message("STARTUP UPDATE ALLOWED")
    char* startup_recovery;
    uint32_t* startup_crc_checksum;
#endif
    char* shutdown_msg;
#ifdef ALLOW_SHUTDOWN_UPDATE
#pragma message("SHUTDOWN UPDATE ALLOWED")
    char* shutdown_recovery;
    uint32_t* shutdown_crc_checksum;
#endif
    char* active_msg;
#ifndef ALLOW_SIMPLE_ACTIVE_UPDATE
#pragma message("SIMPLE ACTIVE MESSAGE UPDATE DISALLOWED")
    char* active_recovery;
    uint32_t* active_crc_checksum;
#endif
} System_variables;

#endif /*__SYSTEM_PARAMETERS_H_*/
