/*
 * f1206.h
 *
 *      Author: LiberdaA
 */

#ifndef F1206_H_
#define F1206_H_


#include <stdint.h>
#include "font.h"
#include "disp_lib.h"


extern Font_t Font1206;

void DISP_DrawCharFont1206(uint16_t x, uint16_t y, uint8_t acsii, DISP_FontMode_t fntMode);


#endif /* F1206_H_ */
