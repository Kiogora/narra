#ifndef __SYSTEM_PARAMETERS_H_
#define __SYSTEM_PARAMETERS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**@typedef struct system_variables
   @brief Struct containing the different system variables that exist on the system.
*/
typedef struct
{
    char* startup_msg;
#ifdef ALLOW_STARTUP_UPDATE
    char* startup_recovery;
    uint32_t* startup_crc_checksum;
#endif
    char* shutdown_msg;
#ifdef ALLOW_SHUTDOWN_UPDATE
    char* shutdown_recovery;
    uint32_t* shutdown_crc_checksum;
#endif
    char* active_msg;
    //char* active_recovery;
    //uint32_t* active_crc_checksum;
} System_variables;

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_PARAMETERS_H_*/
