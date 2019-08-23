/*
 * f3216.h
 *
 *      Author: LiberdaA
 */

#ifndef F3216_H_
#define F3216_H_


#include <stdint.h>
#include "font.h"
#include "disp_lib.h"


extern Font_t Font3216;

void DISP_DrawCharFont3216(uint16_t x, uint16_t y, uint8_t acsii, DISP_FontMode_t fntMode);


#endif /* F3216_H_ */
