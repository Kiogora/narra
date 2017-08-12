#ifndef __SYSTEM_LOADER_H_
#define __SYSTEM_LOADER_H_

#ifdef __cplusplus
extern "C" {
#endif


#define DEBUG

/**@def system loader error codes
   @brief Different loader error codes.
*/
#define LOADER_ERRORCODES_BASE 0x200
#define NVS_INIT_ERROR (LOADER_ERRORCODES_BASE + 0x01)
#define STARTUP_MSG_ERROR (LOADER_ERRORCODES_BASE + 0x02)
#define ACTIVE_MSG_ERROR (LOADER_ERRORCODES_BASE + 0x03)
#define SHUTDOWN_MSG_ERROR (LOADER_ERRORCODES_BASE + 0x04)

/**@typedef struct system_messages
   @brief Different system messages that can exist on the system.
*/
typedef struct
{
    char* startup_msg;
    char* shutdown_msg;
    char* active_msg;
    char* recovery_msg;
} System_variables;
  
/*load system variables on boot*/
int32_t system_loader(System_variables* instanceptr);


#ifdef __cplusplus
}
#endif

#endif /*__TEXT_UTILS_H_*/
