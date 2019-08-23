/*
 * f1612.h
 *
 *      Author: LiberdaA
 */

#ifndef F1612_H_
#define F1612_H_


#include <stdint.h>
#include "font.h"
#include "disp_lib.h"


extern Font_t Font1612;

void DISP_DrawCharFont1612(uint16_t x, uint16_t y, uint8_t acsii, DISP_FontMode_t fntMode);


#endif /* F1612_H_ */
