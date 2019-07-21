

#include "mcal_spi.h"


/* Buffer used for transmission */
//#define MCAL_SPI_TX_BUFF_LEN  20
//uint8_t aTxBuffer[MCAL_SPI_TX_BUFF_LEN];

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

void MCAL_SPI_Init()
{

  //todo: in stm SS is not used, in Arduino ? is SS (PB2) defined as GPIO or SPI SS ?
  //      This is D10 - OLED_CS. In sh1106.cpp this is used as GPIO
  //
  // Set MOSI, SCK and SS output, all others input. SS must be set output even if not used.
  // If SS is configured as an input and is driven low while MSTR is set,
  // MSTR will be cleared, and SPIF in SPSR will become set.
  DDRB = ((1<<DDB3)|(1<<DDB5)|(1<<DDB2));

  // SPIE = 0 - disable irq, default
  // SPE = 1 - enable SPI
  // DORD = 0 - MSB first, default
  // MSTR = 1 - Master
  // CPOL = 0 - This is 1 = SCK High when idle. Low in Active state. 0 - SCK Low when idle. Default is 0.
  // CPHA = 0 - if CPOL = 1, CPHA = 1 - sample on the rising edge which is second. Default is 0.
  // SPR0 = 0  // The system clock is 8 MHz, OLED clock = 4 MHz. The divider is 4 if SPI2X = 0, this is 2 MHz
  // SPR1 = 0  // If something goes wrong, set SPI2X = 1, than divider = 4, so we have 4 MHz clock. 
  // SPI enable, Master, f/16
  //SPCR = ((1<<SPE)|(1<<MSTR)|(1<<CPOL)|(1<<CPHA));  // Not working
  SPCR = ((1<<SPE)|(1<<MSTR));  // working: SPI Mode 0 (CPOL = 0, CPHA = 0)
		
}


void MCAL_SPI_Tx(uint8_t *pData, uint16_t size)
{
	// Only output, we do not receive.
  uint8_t *buff = pData;
  	
  while(size)
  {
    SPDR = *buff;
    while(!(SPSR & (1<<SPIF)));
	size--;
    buff++;      
  }
	
}


void MCAL_SPI_DeInit()
{
	
	
}

//#endif
