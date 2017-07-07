#ifndef __bitsmatrix_h_
#define __bitsmatrix_h_

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************************/
/*Defines*/
/***********************************************************************************/

/**@def FLIP_MATRIX
   @brief Compilation directive to control display flipping. Uncomment to enable.
*/
//#define FLIP_MATRIX

/**@def True
   @brief Macro that defines the width of the font in bits.
*/
#define TRUE 1
#define HIGH 1

/**@def True
   @brief Macro that defines the width of the font in bits.
*/

#define FALSE 0
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

/**@def IS_FONT(FONT)
   @brief Checks that the font width is valid.
*/
#define IS_FONTWIDTH(FONT) ((FONT) == fontwidth_8)

/**@def IS_NUMROWS(ROWS)
   @brief Checks that the row number is valid.
*/
#define IS_NUMROWS(ROWS) ((ROWS) == numrow_8)

/**@def IS_NUMCOLS(ROWS)
   @brief Checks that the column number is valid.
*/
#define IS_NUMCOLS(COLS) ((COLS) == numcol_8)
/***********************************************************************************/
/*Typedefs*/
/***********************************************************************************/

/**@typedef matrix_pin_t
   @brief Define the type of the set of control pins - bytes in this case.
*/
typedef uint8_t matrix_pin_t;

/**@typedef messageTypedef
   @brief Define the type of the message.
*/
typedef char messageTypedef;

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

/**@typedef fontwidth_enum
   @brief matrix font width from a font header.
*/  
typedef enum
{
    fontwidth_8  = (font_t)0x08
}fontwidth_enum;

/**@typedef numrow_enum
   @brief Number of rows per single LED matrix sub-unit. 
*/ 
typedef enum
{
    numrow_8  = (xristics_t)0x08
}numrow_enum;

/**@typedef numcol_enum
   @brief Number of columns per single LED matrix sub-unit. 
*/ 
typedef enum
{
    numcol_8  = (xristics_t)0x08
}numcol_enum;

typedef enum
{
    yes  = (xristics_t)0x01
}is_setup;

/**@typedef matrix_type_TypeDef
   @brief Matrix type in use.
*/


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
    /*units_per_matrix implicitely defined during setup procedure*/
    xristics_t   unit_per_matrix;
    xristics_t   is_setup;
    font_t       fontwidth;
    speed_t      speed;
    messageTypedef message[11];
} Matrix;

/***********************************************************************************/
/*Public function prototypes go here*/
/***********************************************************************************/

/**@fn display
   @brief display message at a given speed
   @param[in] message
   @param[in] speed
   @return Status of the call
   @retval void
*/
void display(Matrix* matrixInstance);

/**@fn matrix_setup
   @brief display message at a given speed
   @param[in] Matrix* matrixInstance,
   @param[in] serial_pin
   @param[in] latch_pin
   @param[in] rowclk_pin
   @param[in] rowrst_pin
   @param[in] speed
   @param[in] fontwidth
   @param[in] numrows
   @param[in] numcols
   @return Status of the call
   @retval void
*/
/*TODO-Implement error checking on pins based on API given by espressif.*/
void matrix_setup(Matrix* matrixInstance, matrix_pin_t _serial_pin, matrix_pin_t _shift_pin, matrix_pin_t _latch_pin,
                  matrix_pin_t _rowclk_pin, matrix_pin_t _rowrst_pin, speedtype_enum _speed, font_t _fontwidth,
                  xristics_t _numrows, xristics_t _numcols);
#ifdef __cplusplus
}
#endif

#endif /*__BITSMATRIX_H_*/

