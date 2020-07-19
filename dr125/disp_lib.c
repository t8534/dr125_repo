/*
 * sh1106_lib.c
 *
 * Created: 03.08.2019 21:55:14
 *  Author: arek1
 */ 


#include "f1206.h"
#include "f1608.h"
#include "f3216.h"
#include "f1612.h"
#include "disp_lib.h"
#include "sh1106_drv.h"


static Font_t *fontManager[DISP_FONT_MAX_NUMBER] = {&Font1608, &Font1206, &Font1612, &Font3216};


void DISP_drawString(uint16_t x, uint16_t y, const char *pString, DISP_FontsId_t fnt, DISP_FontMode_t fntMode)
{
	uint8_t height = fontManager[fnt]->height;
	uint8_t width = fontManager[fnt]->width;
	uint8_t spacing = fontManager[fnt]->spacing;
	drawCharFont_t drawCharFont = fontManager[fnt]->drawCharFont;


	if (y > (DISP_HEIGHT - height))
		return;

	while (*pString != '\0')
	{
		drawCharFont(x, y, *pString, fntMode);

		x += width + spacing;  // spacing makes space between letters

		if (x > (DISP_WIDTH - width))
			return;

		pString++;
	}
	
}


void DISP_bitmap(uint8_t x, uint8_t y, const uint8_t *pBmp, uint8_t chWidth, uint8_t chHeight, uint8_t* buffer)
{
	uint8_t i,j,byteWidth = (chWidth + 7)/8;
	for(j = 0;j < chHeight;j++){
		for(i = 0;i <chWidth;i ++){
			if( *(pBmp +j*byteWidth+i/8) & (128 >> (i & 7)) )  //todo: check is dereference ok
			{
				SH1106_setPixel(x+i,y+j,1);
			}
		}
	}
}


// https://www.edaboard.com/showthread.php?238680-Decimal-to-ASCII-conversion-progam-in-C
// Buffer lenght should be 1 longer then expected digit, to put '\0'
void DISP_decToStr(uint8_t* str, uint8_t len, uint32_t val)
{
	uint8_t i;

	for (i = 1; i <= len; i++)
	{
		str[len-i] = (uint8_t) ((val % 10UL) + '0');
		val/=10;
		
		//if (val == 0)  // to avoid zero
		//	break;
	}

	str[i-1] = '\0';
		
}
