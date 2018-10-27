/*
 * spi.c
 *
 *  Created on: 15 paü 2018
 *      Author: ireneusz
 */
#include <avr/io.h>
#include "spi.h"

//--- init SPI -----------------------------------------------------------------
void initSPI(void) {
	DDRB |= (1 << PB5) | (1 << PB3) | (1 << PB2); //mosi sck cs as output

	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPI2X); //ENABLE SPI, MASTER MODE, double speed CLK=/2

}

//-- send SPI ------------------------------------------------------------------
uint8_t sendSPI(uint8_t bajt) {
	SPDR = bajt;
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}
