/*
 * ui.c
 *
 *      Author: LiberdaA
 */

// TODO:
// 1.
// Many independent screens support
//

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


static uint16_t rpm;
static uint16_t temperature;
static uint16_t mth;
static float volt;


void UI_init()
{
	rpm = 0;
	temperature = 0;
	mth = 0;
	volt = 0.0;



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


void UI_updateRPM(uint16_t _rpm)
{
	if (_rpm > 9999)
		return;
		
}


void UI_updateTempereature(uint16_t _temperature)
{
	if (_temperature > 999)
		return;

}


void UI_updateMth(uint16_t _mth)
{
	if (_mth > 9999)
	return;
}




void UI_updateVolt(float _volt)
{

}

