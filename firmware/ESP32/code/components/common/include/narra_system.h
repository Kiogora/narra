#ifndef __NARRA_SYSTEM_H_
#define __NARRA_SYSTEM_H_

/***********************************************************************************/
/*Defines*/
/***********************************************************************************/

/**@def High
   @brief Macro that defines the macro low as 1
*/
#define HIGH 1

/**@def low
   @brief Macro that defines macro low as 0.
*/
#define LOW 0

/**@def IS_SPEED(SPEED)
   @brief Checks that the speed is a valid speed.
*/
#define IS_SPEED(SPEED) \
  (((SPEED) == system_speed_1)        || \
   ((SPEED) == system_speed_2)        || \
   ((SPEED) == system_speed_3)        || \
   ((SPEED) == system_speed_4)        || \
   ((SPEED) == system_speed_5)        || \
   ((SPEED) == system_speed_6)        || \
   ((SPEED) == system_speed_7)        || \
   ((SPEED) == system_speed_8)        || \
   ((SPEED) == system_speed_9)        || \
   ((SPEED) == system_speed_10)       || \
   ((SPEED) == system_speed_11)       || \
   ((SPEED) == system_speed_12)       || \
   ((SPEED) == system_speed_13)       || \
   ((SPEED) == system_speed_14)       || \
   ((SPEED) == system_speed_15)       || \
   ((SPEED) == system_speed_16)       || \
   ((SPEED) == system_speed_17)       || \
   ((SPEED) == system_speed_18)       || \
   ((SPEED) == system_speed_19)       || \
   ((SPEED) == system_speed_20))

/**@def implemented UTF-8 codepoint limits
   @brief codepoint range limits of implemented codepoints.
*/
#define codepoint_base_0x20  0x20U
#define codepoint_limit_0x7E  0x7EU
#define codepoint_base_0xA1  0xA1U
#define codepoint_limit_0xAE  0xAEU

/**@def IS_UTF8_CODEPOINT_IMPLEMENTED(UTF8_CODEPOINT)
   @brief Checks that the codepoint implemented.
*/
#define IS_UTF8_CODEPOINT_IMPLEMENTED(UTF8_CODEPOINT) \
((((UTF8_CODEPOINT) >= codepoint_base_0x20) && ((UTF8_CODEPOINT) <= codepoint_limit_0x7E)) || \
(((UTF8_CODEPOINT) >= codepoint_base_0xA1) && ((UTF8_CODEPOINT) <= codepoint_limit_0xAE)))

/***********************************************************************************/
/*Typedefs*/
/***********************************************************************************/

/**@typedef matrix_pin_t
   @brief Define the type of the set of control pins - bytes in this case.
*/
typedef uint8_t matrix_pin_t;

/**@typedef speed_t
   @brief Define the speed of the message.
*/
typedef uint8_t speed_t;

/**@typedef xristics_t
   @brief Declare the type of the set of row/col width - bytes in this case.
*/
typedef uint8_t xristics_t;

/**@typedef font_t 
   @brief Declare the type of the font width - bytes in this case.
*/
typedef uint8_t font_t;

/**@typedef speedtype_enum
   @brief matrix scroll speeds
*/

typedef enum
{
    system_speed_1  = (speed_t)0x20,
    system_speed_2  = (speed_t)0x19,
    system_speed_3  = (speed_t)0x18,
    system_speed_4  = (speed_t)0x17,
    system_speed_5  = (speed_t)0x16,
    system_speed_6  = (speed_t)0x15,
    system_speed_7  = (speed_t)0x14,
    system_speed_8  = (speed_t)0x13,
    system_speed_9  = (speed_t)0x12,
    system_speed_10 = (speed_t)0x11,
    system_speed_11 = (speed_t)0x10,
    system_speed_12 = (speed_t)0x09,
    system_speed_13 = (speed_t)0x08,
    system_speed_14 = (speed_t)0x07,
    system_speed_15 = (speed_t)0x06,
    system_speed_16 = (speed_t)0x05,
    system_speed_17 = (speed_t)0x04,
    system_speed_18 = (speed_t)0x03,
    system_speed_19 = (speed_t)0x02,
    system_speed_20 = (speed_t)0x01
}speedtype_enum;

typedef enum
{
    scroll = (xristics_t)0x01
}rendertype;

typedef enum
{
    startup = (xristics_t)0x03,
    active = (xristics_t)0x02,
    shutdown = (xristics_t)0x01,
}matrix_state;

/**@typedef struct Matrix
   @brief Allows several matrix to be setup and allocated memory. Each accessed individually by a common API.
*/
typedef struct
{

    char* current_message;
    matrix_pin_t serial_pin;
    matrix_pin_t shift_pin;
    matrix_pin_t latch_pin;
    matrix_pin_t rowclk_pin;
    matrix_pin_t rowrst_pin;
    xristics_t   num_rows;
    xristics_t   num_cols;
    xristics_t   unit_per_matrix;
    font_t       fontwidth;
    speed_t      speed;
    matrix_state  system_state;
 
} Matrix;

#endif /*__NARRA_SYSTEM_H_*/
