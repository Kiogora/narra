#ifndef __bitsmatrix_h_
#define __bitsmatrix_h_

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_PROG
#define USE_ESPIDF

#define NUMROWS 8U
#define CHAR_WIDTH 8U

#define SER GPIO_NUM_25
#define SH_CLK GPIO_NUM_26
#define ST_CLK GPIO_NUM_27
#define CD4017_CLK GPIO_NUM_12
#define CD4017_RST GPIO_NUM_14 

/*Function prototypes go here*/
void display(char message[], uint8_t speed);

#ifdef __cplusplus
}
#endif

#endif /*__BITSMATRIX_H_*/

