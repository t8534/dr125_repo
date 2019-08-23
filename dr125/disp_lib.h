/*
 * sh1106_lib.h
 *
 * Created: 03.08.2019 21:54:54
 *  Author: arek1
 */ 


#ifndef DISP_LIB_H_
#define DISP_LIB_H_

#include "f1206.h"
#include "f1608.h"
#include "f3216.h"


void DISP_drawString(uint16_t x, uint16_t y, const char *pString, DISP_FontsId_t fnt, DISP_FontMode_t fntMode);
void DISP_bitmap(uint8_t x, uint8_t y, const uint8_t *pBmp, uint8_t chWidth, uint8_t chHeight, uint8_t* buffer);


#endif /* DISP_LIB_H_ */