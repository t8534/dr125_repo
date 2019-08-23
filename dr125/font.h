/*
 * font.h
 *
 *      Author: LiberdaA
 */

#ifndef FONT_H_
#define FONT_H_

#include <stdint.h>


typedef enum DISP_FONTS_TYPE
{
	DISP_FONT1608,
	DISP_FONT1206,
	DISP_FONT1612,
	DISP_FONT3216,
	DISP_FONT_MAX_NUMBER
} DISP_FontsId_t;


typedef enum DISP_FONT_MODE
{
	DISP_FONT_POSITIVE,
	DISP_FONT_NEGATIVE,
} DISP_FontMode_t;


typedef void (*drawCharFont_t)(uint16_t, uint16_t, uint8_t, DISP_FontMode_t);


typedef struct FONT
{
	DISP_FontsId_t id;
	uint8_t height;
	uint8_t width;
	uint8_t spacing;    // letter spacing
	drawCharFont_t drawCharFont;
} Font_t;


#endif /* FONT_H_ */
