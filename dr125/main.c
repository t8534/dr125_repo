/*
 * dr125.c
 *
 * DR125 comp
 *
 * Created: 20.07.2019 22:26:24
 * Author : arek1
 * 
 * Xplained Atmega 328P devboard. 16 MHz clock,
 *
 * Atmega 328P
 * Flash: 32 KB
 * RAM:    2 KB
 * EEPROM: 1 KB
 *
 * Atmega 328P
 * Flash: 16 KB
 * RAM:    1 KB
 * EEPROM: 512 B 
 *
 *
 * Display: https://www.waveshare.com/wiki/1.3inch_OLED_(B)
 *
 * Resolution 128x64
 *
 *
 * Display:                                           Xplained Atmega 328P - 16 MHz
 *
 * OLED_RST    9 ------------------------------------------------- 9    PB1
 * OLED_DC     8 ------------------------------------------------- 8    PB0
 * OLED_CS    10 ------------------------------------------------- 10   PB2 (SS, PCINT2, OC1B)
 * SPI_MOSI   11  -  connect to the DIN pin of OLED - D11 - MOSI - 11   PB3 (MOSI)
 * SPI_SCK    13  -  connect to the CLK pin of OLED - D13 - SCK  - 13   PB5 (SCK) (LED is connected here)
 *
 *
 */ 


// CHANGELOG:
//
// 1.[171230]
// Working OLED, however SPI should be CPOL=0 and CPHA=0, different than show in OLED datasheed
// (CPOL=1, CPHA=1).
//
// Only display bitmap is tested. There is small garbage at the bottom. In arduino it is ok.
// Check.
//


// TODO:
//
// 1.[171231_1107]
// Only display bitmap is tested. There is small garbage at the bottom. In arduino it is ok.
// 
// 2.[190728]
// Move fonts and bitmaps to flash
//
// 3.
// test flashing led PB5 not working if bitmap test compiled
//
// 4.
// After display bitmap, SH1106_clear(oled_buf) not clear display
// 


// NOTES
//
// 1.
// SPI configration
// Arduino default:
// https://arduino.stackexchange.com/questions/16348/how-do-you-use-spi-on-an-arduino
//
// http://www.avrfreaks.net/forum/spi-example-c-code
//
// As I have interfaced a few different SPI devices I can recommend to use an oscilloscope
// to monitor the clock , data and cs lines. You'll have immediate info if the SPI device
// is alive and maybe responding. By the way the most trouble I had with SPI interfaced
// devices was caused by the CS being set/cleared at wrong times for the SPI slave.
//
//
// Arduino default:
// - Mode 0 (the default) - clock is normally low (CPOL = 0) (SPI_POLARITY_HIGH - stm), and the data is sampled
//   on the transition from low to high (leading edge) (CPHA = 0) (SPI_PHASE_1EDGE - stm)
// - Data order: The default is most-significant bit first,
// - Speed: The default setting for SPI is to use the system clock speed divided by four,
//   that is, one SPI clock pulse every 250 ns, assuming a 16 MHz CPU clock.
//   You can change the clock divider by using setClockDivider like this:
//
//   SPI.setClockDivider (SPI_CLOCK_DIV128);
//
//   The fastest rate is "divide by 2" or one SPI clock pulse every 125 ns, assuming
//   a 16 MHz CPU clock. This would therefore take 8 * 125 ns or 1 탎 to transmit one byte.
//
//   However empirical testing shows that it is necessary to have two clock pulses between
//   bytes, so the maximum rate at which bytes can be clocked out is 1.125 탎 each
//   (with a clock divider of 2).
//   To summarize, each byte can be sent at a maximum rate of one per 1.125 탎
//   (with a 16 MHz clock) giving a theoretical maximum transfer rate of 1/1.125 탎,
//   or 888,888 bytes per second (excluding overhead like setting SS low and so on).
//




// It must be first line in the code.
#define F_CPU 16000000UL  // set i the project properties

//#include <avr/io.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
#include <stdint.h>

#include "util/delay.h"

// oled "new" sh1106.h
#include "sh1106.h"
//test
#include "mcal_gpio.h"



#if 0

#define OLED_RST_PIN        GPIO_PIN_0
#define OLED_DC_PIN         GPIO_PIN_1
#define OLED_CS_PIN         GPIO_PIN_2
#define OLED_GPIO_PORT      GPIOC

#define OLED_RST_SET        HAL_GPIO_WritePin(OLED_GPIO_PORT, OLED_RST_PIN, GPIO_PIN_SET)
#define OLED_RST_RESET      HAL_GPIO_WritePin(OLED_GPIO_PORT, OLED_RST_PIN, GPIO_PIN_RESET)
#define OLED_DC_SET         HAL_GPIO_WritePin(OLED_GPIO_PORT, OLED_DC_PIN, GPIO_PIN_SET)
#define OLED_DC_RESET       HAL_GPIO_WritePin(OLED_GPIO_PORT, OLED_DC_PIN, GPIO_PIN_RESET)
#define OLED_CS_SET         HAL_GPIO_WritePin(OLED_GPIO_PORT, OLED_CS_PIN, GPIO_PIN_SET)
#define OLED_CS_RESET       HAL_GPIO_WritePin(OLED_GPIO_PORT, OLED_CS_PIN, GPIO_PIN_RESET)

#endif



// Blinking LED for tests.
#define LCD_LED_CONFIG	DDRB |=  (1 << PB5)
#define LCD_LED_SET		PORTB |= (1 << PB5)
#define LCD_LED_RESET	PORTB &= ~(1 << PB5)



int main(void)
{

	LCD_LED_CONFIG;
		
    // oled "new"
	//todo move to better place
	uint8_t oled_buf[WIDTH * HEIGHT / 8];  // 1024 bytes

    ///////////////////////////////////////////////////////	
	// display an image of bitmap matrix
/*
	SH1106_begin();
	
	SH1106_clear(oled_buf);
	SH1106_bitmap(0, 0, Waveshare12864, 128, 64, oled_buf);
	SH1106_display(oled_buf);
	_delay_ms(2000);
	SH1106_clear(oled_buf);
*/

    ///////////////////////////////////////////////////////
	// Test fonts 32x16 - working, however in place of semicolon is something similar
/*	
	SH1106_begin();
	//SH1106_clear(oled_buf);
	SH1106_char3216(0, 16, '1', oled_buf);
	SH1106_char3216(16, 16, '2', oled_buf);
	SH1106_char3216(32, 16, ':', oled_buf);
	SH1106_char3216(48, 16, '3', oled_buf);
	SH1106_char3216(64, 16, '4', oled_buf);
	SH1106_char3216(80, 16, ':', oled_buf);
	SH1106_char3216(96, 16, '5', oled_buf);
	SH1106_char3216(112, 16, '6', oled_buf);
	SH1106_display(oled_buf);
*/

    ///////////////////////////////////////////////////////
    // Test fonts 16x12 - working, however in place of semicolon is something similar
	// and fuction is SH1106_char1616
/*
    SH1106_begin();
    //SH1106_clear(oled_buf);
    SH1106_char1616(0, 16, '1', oled_buf);
    SH1106_char1616(16, 16, '2', oled_buf);
    SH1106_char1616(32, 16, ':', oled_buf);
    SH1106_char1616(48, 16, '3', oled_buf);
    SH1106_char1616(64, 16, '4', oled_buf);
    SH1106_char1616(80, 16, ':', oled_buf);
    SH1106_char1616(96, 16, '5', oled_buf);
    SH1106_char1616(112, 16, '6', oled_buf);

    SH1106_display(oled_buf);
*/

/*
    ///////////////////////////////////////////////////////
    // Arek function SH1106_char1612() 
	// not working

    SH1106_begin();
    //SH1106_clear(oled_buf);
    SH1106_char1612(0, 16, '1', oled_buf);
    SH1106_char1612(16, 16, '2', oled_buf);
    SH1106_char1612(32, 16, ':', oled_buf);
    SH1106_char1612(48, 16, '3', oled_buf);
    SH1106_char1612(64, 16, '4', oled_buf);
    SH1106_char1612(80, 16, ':', oled_buf);
    SH1106_char1612(96, 16, '5', oled_buf);
    SH1106_char1612(112, 16, '6', oled_buf);

    SH1106_display(oled_buf);
*/


	// GUI
	// Could be ok, for initial tests.
	/*
	SH1106_begin();
	//SH1106_clear(oled_buf);
	// rpm
	SH1106_char3216(0, 0, '1', oled_buf);
	SH1106_char3216(16, 0, '2', oled_buf);
	SH1106_char3216(32, 0, '3', oled_buf);
	SH1106_char3216(48, 0, '4', oled_buf);

	// temperature
	SH1106_char3216(80, 32, '2', oled_buf);
	SH1106_char3216(96, 32, '5', oled_buf);
	SH1106_char3216(112, 32, '6', oled_buf);
	
	// moto hours
    SH1106_char1616(80, 8, '8', oled_buf);  // todo: bug 9 is not displaying correctly, 8 is correct !
    SH1106_char1616(96, 8, '8', oled_buf);
    SH1106_char1616(112, 8, '7', oled_buf);

	// voltage
	SH1106_char1616(0, 40, '1', oled_buf);
	SH1106_char1616(16, 40, '2', oled_buf);
	//SH1106_char1616(32, 40, '.', oled_buf);  // todo: bug, dot is messy
	SH1106_char1616(32, 40, '0', oled_buf);
	SH1106_char1616(48, 40, '4', oled_buf);
	SH1106_char1616(64, 40, '3', oled_buf);

	SH1106_display(oled_buf);
	*/


	// Test 16x8 and string
	//const char *msg = "A";
//	const char *msg1 = "MILEGO DNIA";
//	const char *msg2 = "ASSEMBLERKU";

	// test, 16x4 znaki
/*
	const char *msg1 = " !#$%&()*+,-./01";  // ok
	const char *msg2 = "23456789:;<=>?@A";  // ok
	const char *msg3 = "BCDEFGHIJKLMNOPQ";  // ok
	const char *msg4 = "RSTUVWXYZ[]_abcd";  // do X ok, odn Y smieci
*/

/*
	const char *msg1 = "AAAAAAAAAAAAAAAA";  // 
	const char *msg2 = "AAAAAAAAAAAAAAAA";  // 
	const char *msg3 = "AAAAAAAAAAAAAAAA";  // 
	const char *msg4 = "AAAAAAAAAAAAAAAA";  // 
	*/
	
	//const char *msg5 = "abcdefghijklmnop";
	//const char *msg5 = "abcdefghijklmnop";
	
	SH1106_begin();
	SH1106_clear(oled_buf);
	// SH1106_string(uint8_t x, uint8_t y, const char *pString, uint8_t Size, uint8_t Mode, uint8_t* buffer)

	//SH1106_string(0, 0, msg1, 16, 1, oled_buf);
	//SH1106_string(0, 20, msg2, 16, 1, oled_buf);

	/*
	SH1106_string(0, 0, msg1, 16, 1, oled_buf);
	SH1106_string(0, 16, msg2, 16, 1, oled_buf);
	SH1106_string(0, 32, msg3, 16, 1, oled_buf);
	SH1106_string(0, 48, msg4, 16, 1, oled_buf);
	*/

	//SH1106_string(0, 0, msg4, 16, 1, oled_buf);  // tutaj smieci sa od Z


	//SH1106_string(0, 0, msg5, 16, 1, oled_buf);  // czarny ekran


/*
	SH1106_char(0, 0, ' ', 16, 1, oled_buf);
	SH1106_char(8, 0, '!', 16, 1, oled_buf);
	SH1106_char(16, 0, '#', 16, 1, oled_buf);
	SH1106_char(24, 0, '$', 16, 1, oled_buf);
	SH1106_char(32, 0, '%', 16, 1, oled_buf);
	SH1106_char(40, 0, '&', 16, 1, oled_buf);
	SH1106_char(48, 0, '(', 16, 1, oled_buf);
	SH1106_char(56, 0, ')', 16, 1, oled_buf);
	SH1106_char(64, 0, '*', 16, 1, oled_buf);
	SH1106_char(72, 0, '+', 16, 1, oled_buf);
	SH1106_char(80, 0, ',', 16, 1, oled_buf);
	SH1106_char(88, 0, '-', 16, 1, oled_buf);
	SH1106_char(96, 0, '.', 16, 1, oled_buf);
	SH1106_char(104, 0, '/', 16, 1, oled_buf);
	SH1106_char(112, 0, '0', 16, 1, oled_buf);
	SH1106_char(120, 0, '1', 16, 1, oled_buf);

	SH1106_char(0, 16, '2', 16, 1, oled_buf);
	SH1106_char(8, 16, '3', 16, 1, oled_buf);
	SH1106_char(16, 16, '4', 16, 1, oled_buf);
	SH1106_char(24, 16, '5', 16, 1, oled_buf);
	SH1106_char(32, 16, '6', 16, 1, oled_buf);
	SH1106_char(40, 16, '7', 16, 1, oled_buf);
	SH1106_char(48, 16, '8', 16, 1, oled_buf);
	SH1106_char(56, 16, '9', 16, 1, oled_buf);
	SH1106_char(64, 16, ':', 16, 1, oled_buf);
	SH1106_char(72, 16, ';', 16, 1, oled_buf);
	SH1106_char(80, 16, '<', 16, 1, oled_buf);
	SH1106_char(88, 16, '=', 16, 1, oled_buf);
	SH1106_char(96, 16, '>', 16, 1, oled_buf);
	SH1106_char(104, 16, '?', 16, 1, oled_buf);
	SH1106_char(112, 16, '@', 16, 1, oled_buf);
	SH1106_char(120, 16, 'A', 16, 1, oled_buf);

	SH1106_char(0, 32, 'B', 16, 1, oled_buf);
	SH1106_char(8, 32, 'C', 16, 1, oled_buf);
	SH1106_char(16, 32, 'D', 16, 1, oled_buf);
	SH1106_char(24, 32, 'E', 16, 1, oled_buf);
	SH1106_char(32, 32, 'F', 16, 1, oled_buf);
	SH1106_char(40, 32, 'G', 16, 1, oled_buf);
	SH1106_char(48, 32, 'H', 16, 1, oled_buf);
	SH1106_char(56, 32, 'I', 16, 1, oled_buf);
	SH1106_char(64, 32, 'J', 16, 1, oled_buf);
	SH1106_char(72, 32, 'K', 16, 1, oled_buf);
	SH1106_char(80, 32, 'L', 16, 1, oled_buf);
	SH1106_char(88, 32, 'M', 16, 1, oled_buf);
	SH1106_char(96, 32, 'N', 16, 1, oled_buf);
	SH1106_char(104, 32, 'O', 16, 1, oled_buf);
	SH1106_char(112, 32, 'P', 16, 1, oled_buf);
	SH1106_char(120, 32, 'Q', 16, 1, oled_buf);

	SH1106_char(0, 48, 'R', 16, 1, oled_buf);
	SH1106_char(8, 48, 'S', 16, 1, oled_buf);
	SH1106_char(16, 48, 'T', 16, 1, oled_buf);
	SH1106_char(24, 48, 'U', 16, 1, oled_buf);
	SH1106_char(32, 48, 'V', 16, 1, oled_buf);
	SH1106_char(40, 48, 'W', 16, 1, oled_buf);
	SH1106_char(48, 48, 'X', 16, 1, oled_buf);
	SH1106_char(56, 48, 'Y', 16, 1, oled_buf);
	SH1106_char(64, 48, 'Z', 16, 1, oled_buf);
	SH1106_char(72, 48, '[', 16, 1, oled_buf);
	SH1106_char(80, 48, ']', 16, 1, oled_buf);
	SH1106_char(88, 48, '_', 16, 1, oled_buf);  // blednie odtad
	SH1106_char(96, 48, 'a', 16, 1, oled_buf);
	SH1106_char(104, 48, 'b', 16, 1, oled_buf);
	SH1106_char(112, 48, 'c', 16, 1, oled_buf);
	SH1106_char(120, 48, 'd', 16, 1, oled_buf);
*/


	//const char *msg5 = "XYZ[]_abcd";	// XYZ[ ok, dalej smieci
	//const char *msg5 = "XYZ[]";	// XYZ[ ok, dalej smieci
	//const char *msg5 = "]";  // smiec
	//const char *msg5 = "_";  // smiec
	//const char *msg5 = "a";  // nic sie nie wyswietla
	//const char *msg5 = "p";  // nic sie nie wyswietla
	//SH1106_string(0, 0, msg5, 16, 1, oled_buf);  

	//void SH1106_char(uint8_t x, uint8_t y, uint8_t acsii, uint8_t size, uint8_t mode, uint8_t* buffer)
	// pojedynczo
	//SH1106_char(0, 0, 'X', 16, 1, oled_buf);  // ok
	//SH1106_char(0, 0, ']', 16, 1, oled_buf);  // ok, pojedynczo, byc moze powyzej, w string, funkcja ma buga
	//SH1106_char(0, 0, '_', 16, 1, oled_buf);  // blad, pionowa kreska
	//SH1106_char(0, 0, 'a', 16, 1, oled_buf);  // blad, nic
	SH1106_char(0, 0, 'b', 16, 1, oled_buf);  //  blad, nic



	SH1106_display(oled_buf);




/*
	// Test
	while (1)
	{
		LCD_LED_SET;
		_delay_ms(2000);
		LCD_LED_RESET;
		_delay_ms(2000);
	}
*/	
	
}
