#ifndef __NARRA_DEFINES_H_
#define __NARRA_DEFINES_H_ 

/**********************************************/
/*Updater defines                             */
/**********************************************/

/**********************************/
/*Active message update defines   */
/**********************************/
/*Update type macro precedence*/
/*Complex update procedures have higher precedence to simple update procedures*/
#if defined (ALLOW_SIMPLE_ACTIVE_MSG_UPDATE) && defined (ALLOW_COMPLEX_ACTIVE_MSG_UPDATE)
    #undef ALLOW_SIMPLE_ACTIVE_MSG_UPDATE
#endif

/**
   @def ALLOW_SIMPLE_ACTIVE_MSG_UPDATE
   @brief active message update type definition
**/
#define ALLOW_SIMPLE_ACTIVE_MSG_UPDATE

/**
   @def ALLOW_COMPLEX_ACTIVE_MSG_UPDATE
   @brief active message update type definition
**/
//#define ALLOW_COMPLEX_ACTIVE_MSG_UPDATE

/**********************************/
/*Startup message update defines  */
/**********************************/
/*Update type macro precedence*/
/*Complex update procedures have higher precedence to simple update procedures*/
#if defined (ALLOW_SIMPLE_STARTUP_MSG_UPDATE) && defined (ALLOW_COMPLEX_STARTUP_MSG_UPDATE)
    #undef ALLOW_SIMPLE_STARTUP_MSG_UPDATE
#endif

/**
    @def ALLOW_SIMPLE_STARTUP_MSG_UPDATE
    @brief simple startup message update type definition
**/
#define ALLOW_SIMPLE_STARTUP_MSG_UPDATE

/**
    @def ALLOW_COMPLEX_STARTUP_MSG_UPDATE
    @brief complex startup message update type definition
**/
//#define ALLOW_COMPLEX_STARTUP_MSG_UPDATE

/***********************************/
/*Shutdown message update defines  */
/***********************************/
/*Update type macro precedence*/
/*Complex update procedures have higher precedence to simple update procedures*/
#if defined (ALLOW_SIMPLE_SHUTDOWN_MSG_UPDATE) && defined (ALLOW_COMPLEX_SHUTDOWN_MSG_UPDATE)
    #undef ALLOW_SIMPLE_SHUTDOWN_MSG_UPDATE
#endif

/**
    @def ALLOW_SIMPLE_SHUTDOWN_MSG_UPDATE
    @brief simple shutdown message update type definition
*/
#define ALLOW_SIMPLE_SHUTDOWN_MSG_UPDATE

/**
    @def ALLOW_COMPLEX_SHUTDOWN_MSG_UPDATE
    @brief complex shutdown message update type definition
*/
//#define ALLOW_COMPLEX_SHUTDOWN_MSG_UPDATE

/***********************************/
/*Uodater error code defines       */
/***********************************/
/**
    @def updater error codes
    @brief Implemented updater error codes.
**/
#define UPDATER_ERRORCODES_BASE 0x300
#define UTF8_ERROR (UPDATER_ERRORCODES_BASE + 0x01)
#define WRITE_ERROR (UPDATER_ERRORCODES_BASE + 0x02)

/**********************************************/
/*Loader defines                              */
/**********************************************/
/**
    @def system loader error codes
    @brief Different loader error codes.
**/
#define LOADER_ERRORCODES_BASE 0x200
#define NVS_INIT_ERROR (LOADER_ERRORCODES_BASE + 0x01)
#define STARTUP_MSG_ERROR (LOADER_ERRORCODES_BASE + 0x02)
#define ACTIVE_MSG_ERROR (LOADER_ERRORCODES_BASE + 0x03)
#define SHUTDOWN_MSG_ERROR (LOADER_ERRORCODES_BASE + 0x04)

/**********************************************/
/*UTF-8 implementation defines                */
/**********************************************/
/**
    @def Implemented UTF-8 codepoint ranges
    @brief Implemented UTF-8 codepoint ranges
**/
#define codepoint_base_0x20  0x20U
#define codepoint_limit_0x7E  0x7EU
#define codepoint_base_0xA1  0xA1U
#define codepoint_limit_0xAE  0xAEU

/**
    @def IS_UTF8_CODEPOINT_IMPLEMENTED(UTF8_CODEPOINT)
    @brief Checks that the codepoint implemented.
**/
#define IS_UTF8_CODEPOINT_IMPLEMENTED(UTF8_CODEPOINT) \
((((UTF8_CODEPOINT) >= codepoint_base_0x20) && ((UTF8_CODEPOINT) <= codepoint_limit_0x7E)) || \
(((UTF8_CODEPOINT) >= codepoint_base_0xA1) && ((UTF8_CODEPOINT) <= codepoint_limit_0xAE)))

/**********************************************/
/*GPIO state defines                          */
/**********************************************/
/**
    @def HIGH
    @brief Macro that defines the macro HIGH as 1
**/
#define HIGH 1

/**
    @def LOW
    @brief Macro that defines macro LOW as 0.
**/
#define LOW 0

/**********************************************/
/*Speed validity checker defines              */
/**********************************************/
/**@def IS_SPEED(SPEED)
   @brief Checks that the speed is a valid speed.
*/
#define IS_SPEED_VALID(SPEED) \
  (((SPEED) == narra_speed_1)        || \
   ((SPEED) == narra_speed_2)        || \
   ((SPEED) == narra_speed_3)        || \
   ((SPEED) == narra_speed_4)        || \
   ((SPEED) == narra_speed_5)        || \
   ((SPEED) == narra_speed_6)        || \
   ((SPEED) == narra_speed_7)        || \
   ((SPEED) == narra_speed_8)        || \
   ((SPEED) == narra_speed_9)        || \
   ((SPEED) == narra_speed_10)       || \
   ((SPEED) == narra_speed_11)       || \
   ((SPEED) == narra_speed_12)       || \
   ((SPEED) == narra_speed_13)       || \
   ((SPEED) == narra_speed_14)       || \
   ((SPEED) == narra_speed_15)       || \
   ((SPEED) == narra_speed_16)       || \
   ((SPEED) == narra_speed_17)       || \
   ((SPEED) == narra_speed_18)       || \
   ((SPEED) == narra_speed_19)       || \
   ((SPEED) == narra_speed_20))

#endif
