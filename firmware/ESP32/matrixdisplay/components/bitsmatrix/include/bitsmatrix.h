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

typedef uint8_t font_t ;

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
    messageTypedef message[11];
} Matrix;

/***********************************************************************************/
/*Public function prototypes go here*/
/***********************************************************************************/

/**@fn matrix_setup
   @brief setup the matrix control pins
   @param[in] serial_pin
   @param[in] shift_pin
   @param[in] latch_pin
   @param[in] rowclk_pin
   @param[in] rowrst_pin
   @return Status of the call
   @retval void
*/
void matrix_init(Matrix* matrixInstance);

/**@fn display
   @brief display message at a given speed
   @param[in] message
   @param[in] speed
   @return Status of the call
   @retval void
*/
void display(Matrix* matrixInstance);

#ifdef __cplusplus
}
#endif

#endif /*__BITSMATRIX_H_*/

