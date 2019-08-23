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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "util/delay.h"

#include "disp_lib.h"
//test
#include "mcal_gpio.h"

#include "ui.h"




// Blinking LED for tests.
#define LCD_LED_CONFIG	DDRB |=  (1 << PB5)
#define LCD_LED_SET		PORTB |= (1 << PB5)
#define LCD_LED_RESET	PORTB &= ~(1 << PB5)


int main(void)
{

	LCD_LED_CONFIG;
	
	
	uint16_t rpm = 0;
	uint16_t temperature = 0;
	uint16_t mth = 0;
	uint8_t volt = 0;


	UI_init();

	UI_updateRPM(rpm);
	UI_updateTempereature(temperature);
	UI_updateMth(mth);
	UI_updateVolt(volt);


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
