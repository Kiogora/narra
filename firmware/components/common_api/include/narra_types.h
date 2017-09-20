#ifndef __NARRA_TYPES_H_
#define __NARRA_TYPES_H_

/***********************************************************************************/
/*Typedefs*/
/***********************************************************************************/

/**@typedef narra_pin_t
   @brief Define the type of the set of control pins - bytes in this case.
*/
typedef uint8_t narra_pin_t;

/**@typedef narra_speed_t
   @brief Define the speed of the message.
*/
typedef uint8_t narra_speed_t;

/**@typedef narra_xristics_t
   @brief Declare the type of the set of row/col width - bytes in this case.
*/
typedef uint8_t narra_xristics_t;

/**@typedef narra_font_t 
   @brief Declare the type of the font width - bytes in this case.
*/
typedef uint8_t narra_font_t;

/**@typedef narra_speedtype_enum
   @brief matrix scroll speeds
*/

typedef enum
{
    narra_speed_1  = (narra_speed_t)0x20,
    narra_speed_2  = (narra_speed_t)0x19,
    narra_speed_3  = (narra_speed_t)0x18,
    narra_speed_4  = (narra_speed_t)0x17,
    narra_speed_5  = (narra_speed_t)0x16,
    narra_speed_6  = (narra_speed_t)0x15,
    narra_speed_7  = (narra_speed_t)0x14,
    narra_speed_8  = (narra_speed_t)0x13,
    narra_speed_9  = (narra_speed_t)0x12,
    narra_speed_10 = (narra_speed_t)0x11,
    narra_speed_11 = (narra_speed_t)0x10,
    narra_speed_12 = (narra_speed_t)0x09,
    narra_speed_13 = (narra_speed_t)0x08,
    narra_speed_14 = (narra_speed_t)0x07,
    narra_speed_15 = (narra_speed_t)0x06,
    narra_speed_16 = (narra_speed_t)0x05,
    narra_speed_17 = (narra_speed_t)0x04,
    narra_speed_18 = (narra_speed_t)0x03,
    narra_speed_19 = (narra_speed_t)0x02,
    narra_speed_20 = (narra_speed_t)0x01
}narra_speed_enum;

/**@typedef narra_rendertype_enum
   @brief Means to render message
*/
typedef enum
{
    scroll = (narra_xristics_t)0x00
}narra_rendertype_enum;

/**@typedef narra_state
   @brief Operational states of the matrix
*/
typedef enum
{
    active = (narra_xristics_t)0x02,
    startup = (narra_xristics_t)0x01,
    shutdown = (narra_xristics_t)0x00,
}narra_state_enum;

#endif /*__NARRA_TYPES_H_*/
