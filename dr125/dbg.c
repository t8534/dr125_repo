/*
 * dbg.c
 *
 *  Author: arek
 *
 *
 * TODO:
 * 1.
 * Predefined string messages in a flash.
 *
 *
 */ 

#include <avr/io.h>
#include "dbg.h"


static void PutChar(const char *s);


void DBG_UartInit()
{
	// configure ports double mode
	UCSR0A = 0x00;

	// configure the ports speed 9600
	UBRR0H = 0x00;
	UBRR0L = 103;  // 9600 bps at 16 MHz clock

	// asynchronous, 8N1 mode
	UCSR0C |= 0x06;
	
	// rx/tx enable
	//UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);  // enable tx only

		
}


void DBG_UartPrintStr(const char *msg)
{
  const char *str = msg;

  while (*str)
  {
	  PutChar(str);
	  str++;
  }	
	
}


void DBG_UartPrintDec(uint8_t* str, uint8_t len, uint32_t val)
{
	uint8_t i;

	for (i = 1; i <= len; i++)
	{
		str[len-i] = (uint8_t) ((val % 10UL) + '0');
		val/=10;
	}

	str[i-1] = '\0';
	
	DBG_UartPrintStr((const char *)str);
}


void DBG_UartPrintCRLF()
{
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = 0xD;  // CR - carriage return 

		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = 0xA;  // LF - line feed
}


static void PutChar(const char *s)
{
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = *s;	
}


