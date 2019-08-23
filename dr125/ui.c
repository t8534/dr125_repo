/*
 * ui.c
 *
 *      Author: LiberdaA
 */

#include "util/delay.h"

#include "f1206.h"
#include "f1608.h"
#include "f3216.h"

#include "disp_lib.h"
#include "sh1106_drv.h"

#include "ui.h"



static const char *rpm_default = "9999";
static const char *temperat_default = "999";
static const char *volt_default = "99.99";
static const char *mth_default = "9999";	
	

void UI_init()
{

	SH1106_init();
	SH1106_clearScreen();

	// Set default values
    // UI - ok ready.
	DISP_drawString(2, 8, rpm_default, DISP_FONT1612, DISP_FONT_POSITIVE);
	DISP_drawString(18, 40, temperat_default, DISP_FONT1612, DISP_FONT_POSITIVE);
	DISP_drawString(82, 8, volt_default, DISP_FONT1608, DISP_FONT_POSITIVE);
	DISP_drawString(90, 40, mth_default, DISP_FONT1608, DISP_FONT_POSITIVE);
	
	SH1106_updateScreen();

	_delay_ms(4000);  // 4s

	SH1106_clearScreen();
}


void UI_deInit()
{
	//DISP_deInit();
}


void UI_updateRPM(uint16_t rpm)
{

}


void UI_updateTempereature(uint16_t temperature)
{

}


void UI_updateMth(uint16_t mth)
{

}


void UI_updateVolt(uint8_t volt)
{

}

