
#include "mcal_gpio.h"


void MCAL_GPIO_Init()
{
  // Set 3 pins out: 
  // OLED_RST    9 ---- 9    PB1
  // OLED_DC     8 ---- 8    PB0
  // OLED_CS    10 ---- 10   PB2 (SS, PCINT2, OC1B)	
  DDRB = 0xFF;  // output, 0x00000111 = 0x07

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


#if 0
  /* -1- Enable GPIOA Clock (to be able to program the configuration registers) */
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Pin = (OLED_RST_PIN);
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Output push-pull
  GPIO_InitStruct.Pull = GPIO_NOPULL;         //No pull up/down because this is not led.
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH  ;
  HAL_GPIO_Init(OLED_GPIO_PORT, &GPIO_InitStruct); 
  GPIO_InitStruct.Pin = (OLED_DC_PIN);
  HAL_GPIO_Init(OLED_GPIO_PORT, &GPIO_InitStruct); 
  GPIO_InitStruct.Pin = (OLED_CS_PIN);
  HAL_GPIO_Init(OLED_GPIO_PORT, &GPIO_InitStruct); 
#endif
	
}

