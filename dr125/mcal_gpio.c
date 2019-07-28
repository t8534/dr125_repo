
#include "mcal_gpio.h"


void MCAL_GPIO_Init()
{
  // Set 3 pins out: 
  // OLED_RST    9 ---- 9    PB1
  // OLED_DC     8 ---- 8    PB0
  // OLED_CS    10 ---- 10   PB2 (SS, PCINT2, OC1B)	
//  DDRB = 0xFF;  // output, 0x00000111 = 0x07

    DDRB |=  (1 << PB0);  // PB0
	DDRB |=  (1 << PB1);  // PB1
	DDRB |=  (1 << PB2);  // PB2
	

	/*
    // set PORTB for output
    DDRB = 0xFF;
    // set PORTD for input
    DDRD &= 0xFB;
    PORTD |= 0x04;
    while (1) {
	    if (PIND & 0x04)
	    PORTB &= ~0x20;
	    else
	    PORTB |= 0x20;
    }
	*/
	
}

