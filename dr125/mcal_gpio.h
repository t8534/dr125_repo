#ifndef __MCAL_GPIO_H
#define __MCAL_GPIO_H

#include <avr/io.h>
//#include <stdint.h>  // uint8_t, etc.


#define OLED_RST_SET        (PORTB |= 0x02)   // OLED_RST  PB1
#define OLED_RST_RESET      (PORTB &= ~0x02)  // OLED_RST  PB1
#define OLED_DC_SET         (PORTB |= 0x01)   // OLED_DC   PB0
#define OLED_DC_RESET       (PORTB &= ~0x01)  // OLED_DC   PB0
#define OLED_CS_SET         (PORTB |= 0x04)   // OLED_CS   PB2
#define OLED_CS_RESET       (PORTB &= ~0x04)  // OLED_CS   PB2



void MCAL_GPIO_Init(void);
//void MCAL_GPIO_Set(uint8_t pin, uint8_t state);
//void MCAL_GPIO_DeInit(void);


#endif

