/**
  ******************************************************************************
  * @file    sh1106.c 
  * @author  Waveshare Team
  * @version 
  * @date    21-June-2017
  * @brief   This file includes the OLED driver for SH1106 display module
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  *
  * Modified and cleared from bugs by Arek
  *
  */

//
// Following datasheet OLED 1.3" from Waveshare, SPI settings:
// The clock is Idle High, and Active - Low = CPOL = 1
// The sample is on the rising edge, which is the second edge = CPHA = 1
// SPI Mode = 3, if CPOL = 1 and CPHA = 1
// Clock cycle 250ns = 4 MHz.
//
//
// TODO:
// 1.
// Change int to uint
//


#include <stdio.h>
#include <util/delay.h>
#include "sh1106_drv.h"
#include "mcal_spi.h"
#include "mcal_gpio.h"



static uint8_t disp_buffer[DISP_WIDTH * DISP_HEIGHT / 8];


void digitalWrite(uint8_t pin, uint8_t state)
{
	switch(pin)
	{
		case OLED_RST:
			(state == HIGH) ? OLED_RST_SET : OLED_RST_RESET;
			break;

		case OLED_DC:
			(state == HIGH) ? OLED_DC_SET : OLED_DC_RESET;
			break;

		case OLED_CS:
			(state == HIGH) ? OLED_CS_SET : OLED_CS_RESET;
			break;
		
		default:
			break;
	}
}


void SPIWrite(uint8_t *buffer, int bufferLength) {
  MCAL_SPI_Tx(buffer, (uint16_t)bufferLength);
}


void command(uint8_t cmd){
    digitalWrite(OLED_DC, LOW);  // Command mode
    SPIWrite(&cmd, 1);
}


void SH1106_init()
{
    MCAL_SPI_Init(); //todo: what about deinit ?	
    //HAL_Delay(10);
	_delay_ms(10);
    MCAL_GPIO_Init(); //todo: what about deinit ?	
    //HAL_Delay(10);
	_delay_ms(10);
	
	  //arek add, set CS high to init interface
    digitalWrite(OLED_CS, HIGH);  // LOW - data can be send, HIGH - interface init
    //HAL_Delay(100);  // arek: add because stm is quicker than atmega
	_delay_ms(100);
	
	
    digitalWrite(OLED_CS, LOW);  // LOW - data can be send, HIGH - interface init
    //HAL_Delay(10);  // arek: add because stm is quicker than atmega
    _delay_ms(10);
	digitalWrite(OLED_RST, HIGH);
    //delay(10);
    //HAL_Delay(10);
	_delay_ms(10);
    digitalWrite(OLED_RST, LOW);  // Reset active - initialization
    //delay(10);
    //HAL_Delay(10);
	_delay_ms(10);
    digitalWrite(OLED_RST, HIGH);
    
    command(0xAE);//--turn off oled panel
    command(0x02);//---set low column address
    command(0x10);//---set high column address
    command(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    command(0x81);//--set contrast control register
    command(0xA0);//--Set SEG/Column Mapping     
    command(0xC0);//Set COM/Row Scan Direction   
    command(0xA6);//--set normal display
    command(0xA8);//--set multiplex ratio(1 to 64)
    command(0x3F);//--1/64 duty
    command(0xD3);//-set display offset    Shift Mapping RAM Counter (0x00~0x3F)
    command(0x00);//-not offset
    command(0xd5);//--set display clock divide ratio/oscillator frequency
    command(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
    command(0xD9);//--set pre-charge period
    command(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    command(0xDA);//--set com pins hardware configuration
    command(0x12);
    command(0xDB);//--set vcomh
    command(0x40);//Set VCOM Deselect Level
    command(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
    command(0x02);//
    command(0xA4);// Disable Entire Display On (0xa4/0xa5)
    command(0xA6);// Disable Inverse Display On (0xa6/a7) 
    command(0xAF);//--turn on oled panel
}


void SH1106_clearScreen()
{
    int i;
    for(i = 0; i < DISP_WIDTH * DISP_HEIGHT / 8; i++)
    {
        disp_buffer[i] = 0;
    }
	SH1106_updateScreen();
}


void SH1106_setPixel(int x, int y, char color)
{
    if(x > DISP_WIDTH || y > DISP_HEIGHT)return ;
    if(color)
        disp_buffer[x+(y/8)*DISP_WIDTH] |= 1<<(y%8);
    else
        disp_buffer[x+(y/8)*DISP_WIDTH] &= ~(1<<(y%8));
}


void SH1106_updateScreen()
{
    uint8_t page;
    uint8_t *pBuf = disp_buffer;
    
    for (page = 0; page < 8; page++) {  
        /* set page address */
        command(0xB0 + page);
        /* set low column address */
        command(0x02); 
        /* set high column address */
        command(0x10); 
        /* write data */
        digitalWrite(OLED_DC, HIGH);  // Display mode
        SPIWrite(pBuf, DISP_WIDTH); 
        pBuf += DISP_WIDTH;
    }
}
