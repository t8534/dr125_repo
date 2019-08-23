/*
 * f1608_test.h
 *
 */

#ifndef F1608_H_
#define F1608_H_


#include <stdint.h>
#include "font.h"
#include "disp_lib.h"


extern Font_t Font1608;

void DISP_DrawCharFont1608(uint16_t x, uint16_t y, uint8_t acsii, DISP_FontMode_t fntMode);


#endif /* F1608_H_ */
