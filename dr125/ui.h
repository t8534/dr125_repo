/*
 * ui.h
 *
 *      Author: LiberdaA
 */

#ifndef UI_H_
#define UI_H_


#include "f1206.h"
#include "f1608.h"
#include "f3216.h"

#include "disp_lib.h"
#include "sh1106_drv.h"


void UI_init();
void UI_deInit();

void UI_updateRPM(uint16_t rpm);
void UI_updateTempereature(uint16_t temperature);
void UI_updateMth(uint16_t mth);
void UI_updateVolt(float volt);


#endif /* UI_H_ */
