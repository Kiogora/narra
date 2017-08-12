#ifndef __DISPLAY_CONTROLLER_H_
#define __DISPLAY_CONTROLLER_H_

#ifdef __cplusplus
extern "C" {
#endif

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
  (((SPEED) == scroll_speed_1)        || \
   ((SPEED) == scroll_speed_2)        || \
   ((SPEED) == scroll_speed_3)        || \
   ((SPEED) == scroll_speed_4)        || \
   ((SPEED) == scroll_speed_5)        || \
   ((SPEED) == scroll_speed_6)        || \
   ((SPEED) == scroll_speed_7)        || \
   ((SPEED) == scroll_speed_8)        || \
   ((SPEED) == scroll_speed_9)        || \
   ((SPEED) == scroll_speed_10)       || \
   ((SPEED) == scroll_speed_11)       || \
   ((SPEED) == scroll_speed_12)       || \
   ((SPEED) == scroll_speed_13)       || \
   ((SPEED) == scroll_speed_14)       || \
   ((SPEED) == scroll_speed_15)       || \
   ((SPEED) == scroll_speed_16)       || \
   ((SPEED) == scroll_speed_17)       || \
   ((SPEED) == scroll_speed_18)       || \
   ((SPEED) == scroll_speed_19)       || \
   ((SPEED) == scroll_speed_20))

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
    scroll_speed_1  = (speed_t)0x20,
    scroll_speed_2  = (speed_t)0x19,
    scroll_speed_3  = (speed_t)0x18,
    scroll_speed_4  = (speed_t)0x17,
    scroll_speed_5  = (speed_t)0x16,
    scroll_speed_6  = (speed_t)0x15,
    scroll_speed_7  = (speed_t)0x14,
    scroll_speed_8  = (speed_t)0x13,
    scroll_speed_9  = (speed_t)0x12,
    scroll_speed_10 = (speed_t)0x11,
    scroll_speed_11 = (speed_t)0x10,
    scroll_speed_12 = (speed_t)0x09,
    scroll_speed_13 = (speed_t)0x08,
    scroll_speed_14 = (speed_t)0x07,
    scroll_speed_15 = (speed_t)0x06,
    scroll_speed_16 = (speed_t)0x05,
    scroll_speed_17 = (speed_t)0x04,
    scroll_speed_18 = (speed_t)0x03,
    scroll_speed_19 = (speed_t)0x02,
    scroll_speed_20 = (speed_t)0x01
}speedtype_enum;


typedef enum
{
    yes  = (xristics_t)0x01
}is_setup;

typedef enum
{
    scroll = (xristics_t)0x01
}rendertype;

typedef enum
{
    startup = (xristics_t)0x01,
    active = (xristics_t)0x02,
    shutdown = (xristics_t)0x03,
    error = (xristics_t)0x04
}matrix_message_state;

/**@typedef struct Matrix
   @brief Allows several matrix to be setup and allocated memory. Each accessed individually by a common API.
*/
typedef struct
{
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

    matrix_message_state  message_state;

    char* current_message;

    xristics_t  is_setup; 

} Matrix;

/***********************************************************************************/
/*Public function prototypes go here*/
/***********************************************************************************/

void display(Matrix* matrixInstanceptr, rendertype _renderx);

/*TODO-Implement error checking on pins based on API given by espressif.*/

void matrix_setup(Matrix* matrixInstanceptr, matrix_pin_t _serial_pin, matrix_pin_t _shift_pin, matrix_pin_t _latch_pin, matrix_pin_t _rowclk_pin, matrix_pin_t _rowrst_pin, speedtype_enum _speed);

#ifdef __cplusplus
}
#endif

#endif /*__CONTROLLER_H_*/

