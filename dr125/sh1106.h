/**
  ******************************************************************************
  * @file    sh1106.h
  * @author  Waveshare Team
  * @version 
  * @date    21-June-2017
  * @brief   This file includes the OLED driver for SH1106 display moudle
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
  * Display: https://www.waveshare.com/1.3inch-oled-b.htm
  *
  * Resolution: 128x64
  *
  * Interface:
  *
  * PIN      Symbol     Description
  *
  *  1       VCC        Power positive input 3.3-5V
  *  2       GND        Ground
  *  3       NC         NC
  *  4       DIN        Data input
  *  5       CLK        Clock signal input
  *  6       CS         Chip selection, low active
  *  7       D/C        Command signal, low level for command, high level for data
  *  8       RES        Reset signal, low active
  *
  *
  * Hardware config:
  *
  * MODE/INTERFACE      BS0/BS1      DIN      SCK
  *
  * 3-wire SPI          1/0          MOSI     SCLK
  * 4-wire SPI          0/0          MOSI     SCLK
  * I2C                 0/1          SDA      SCL
  *
  *
  *
  */
  
#ifndef _SH1106_H_
#define _SH1106_H_

#include <stdint.h>

//#include <avr/pgmspace.h>


// OLED_RST_PIN - PORT C, pin 0
// OLED_DC_PIN  - PORT C, pin 1
// OLED_CS_PIN  - PORT C, pin 2
// SPI_MOSI     - PORT B, pin 15
// SPI_SCK      - PORT B, pin 14

//todo: rename with prefix
#define VCCSTATE SH1106_SWITCHCAPVCC
#define WIDTH   128
#define HEIGHT   64
#define NUM_PAGE  8

//todo
/*
#define OLED_RST  9 
#define OLED_DC   8
#define OLED_CS  10
#define SPI_MOSI 11     // connect to the DIN pin of OLED 
#define SPI_SCK  13     // connect to the CLK pin of OLED 
*/

//test
//todo
#define OLED_RST  9 
#define OLED_DC   8
#define OLED_CS  10
#define SPI_MOSI 11     /* connect to the DIN pin of OLED */
#define SPI_SCK  13     /* connect to the CLK pin of OLED */

//todo: arek add, but clarify finally
#define LOW       0
#define HIGH      1



//test
void digitalWrite(uint8_t pin, uint8_t state);


void SH1106_begin(void);
void SH1106_display(uint8_t* buffer);
void SH1106_clear(uint8_t* buffer);
void SH1106_pixel(int x, int y, char color, uint8_t* buffer);
void SH1106_bitmap(uint8_t x, uint8_t y, const uint8_t *pBmp, uint8_t chWidth, uint8_t chHeight, uint8_t* buffer);
void SH1106_char1616(uint8_t x,uint8_t y,uint8_t chChar, uint8_t* buffer);
//void SH1106_char1612(uint8_t x,uint8_t y,uint8_t chChar, uint8_t* buffer  //arek test
//void SH1106_char1608(uint8_t x, uint8_t y, uint8_t chChar, uint8_t* buffer);  //arek test
void SH1106_char3216(uint8_t x, uint8_t y, uint8_t chChar, uint8_t* buffer);
void SH1106_string(uint8_t x, uint8_t y, const char *pString, uint8_t Size, uint8_t Mode, uint8_t* buffer);
void SPIWrite(uint8_t *buffer, int bufferLength);
void command(uint8_t cmd);

//arek
void SH1106_char(uint8_t x, uint8_t y, uint8_t acsii, uint8_t size, uint8_t mode, uint8_t* buffer);

//extern const uint8_t Font1612[11][32];
//extern const uint8_t Font3216[11][64];
//extern const uint8_t Signal816[16];
//extern const uint8_t Msg816[16];
//extern const uint8_t Bat816[16];
//extern const uint8_t Bluetooth88[8];
//extern const uint8_t GPRS88[8];
//extern const uint8_t Alarm88[8];
//extern const uint8_t Waveshare12864[1024];


#endif
