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
 *
 */ 


// It must be first line in the code.
#define F_CPU 16000000UL  // set i the project properties

#include <avr/io.h>

#include "util/delay.h"


// Blinking LED for tests.
#define LCD_LED_CONFIG	DDRB |=  (1 << PB5)
#define LCD_LED_SET		PORTB |= (1 << PB5)
#define LCD_LED_RESET	PORTB &= ~(1 << PB5)


int main(void)
{

	LCD_LED_CONFIG;

	while (1)
	{
		LCD_LED_SET;
		_delay_ms(2000);
		LCD_LED_RESET;
		_delay_ms(2000);
	}
}



