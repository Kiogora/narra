#ifndef __SYSTEM_UPDATER_H_
#define __SYSTEM_UPDATER_H_

#ifdef __cplusplus
extern "C" {
#endif


#define ALLOW_STARTUP_MSG_UPDATE
#define ALLOW_SHUTDOWN_MSG_UPDATE

#define DEBUG_UPDATER

#define UPDATER_ERRORCODES_BASE 0x300
#define UTF8_ERROR (UPDATER_ERRORCODES_BASE + 0x01)
#define WRITE_ERROR (UPDATER_ERRORCODES_BASE + 0x02)

//#define NARRA_CRC16
/*Choose one of the following CRC options to change the CRC nature in crc.h*/
#if defined (NARRA_CRC32)
#define CRC32
#elif defined (NARRA_CRC16)
#define CRC16
#elif defined (NARRA_CRC_CCITT)
#define CRC_CCITT
#endif

//system-updater error codes

#ifdef ALLOW_STARTUP_MSG_UPDATE
int32_t system_update_startup(char* new_startup_msg);
#endif
int32_t system_update_active(char* new_active_msg);
#ifdef ALLOW_SHUTDOWN_MSG_UPDATE
int32_t system_update_shutdown(char* new_shutdown_msg);
#endif


#ifdef __cplusplus
}
#endif /*__SYSTEM_UPDATER_H_*/

#endif /*__SYSTEM_UPDATER_H_*/
