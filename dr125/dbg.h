/*
 * dbg.h
 *
 * Debug utilities, prepared for xplained 16 MHz Atmega 328P devboard.
 *
 *  Author: arek
 *
 */ 


#ifndef DBG_H_
#define DBG_H_

// Example usage of toggle pins, tune it to particular devboard.
/*
// Debug pins C0, C1, C2, C3, C4, C5
#define DBG_PINS_INIT    \
do { \
	DDRC = 0b00000111; \
	PORTC = 0b00000000; \
} while (0)

#define DBG_PIN0_TOGGLE  PORTC ^=0b00000001
#define DBG_PIN1_TOGGLE  PORTC ^=0b00000010
#define DBG_PIN2_TOGGLE  PORTC ^=0b00000100
#define DBG_PIN3_TOGGLE  PORTC ^=0b00001000
#define DBG_PIN4_TOGGLE  PORTC ^=0b00010000
#define DBG_PIN5_TOGGLE  PORTC ^=0b00100000
*/

// Blinking LED for tests.
// This is internal "user" led on xplained devboard.
#define LCD_LED_CONFIG	DDRB |=  (1 << PB5)
#define LCD_LED_SET		PORTB |= (1 << PB5)
#define LCD_LED_RESET	PORTB &= ~(1 << PB5)


// UART

// This is message buffer, set the length to max possible message you would like to send.
#define DBG_DEC_MSG_BUFF_LEN    10UL
uint8_t DBG_DecMsgBuff[DBG_DEC_MSG_BUFF_LEN];

void DBG_UartInit();
void DBG_UartPrintStr(const char *str);
void DBG_UartPrintDec(uint8_t* str, uint8_t len, uint32_t val);
void DBG_UartPrintCRLF();


#endif /* DBG_H_ */