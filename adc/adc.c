/*
 * adc.c
 *
 *  Created on: 15 paü 2018
 *      Author: ireneusz
 */
#include <avr/io.h>
#include "adc.h"
#include "../spi/spi.h"

void initADC(void)
{
	DDRB |= CS_ADC_PIN;
	CS_ADC_HIGH;
}

void makeSampleChannelA(uint8_t *msb, uint8_t *lsb) {
	CS_ADC_LOW;
	sendSPI(0b00001100);
	*msb = 0b00001111&sendSPI(0);
	*lsb = sendSPI(0);
	CS_ADC_HIGH;
}
void makeSampleChannelB(uint8_t *msb, uint8_t *lsb) {
	CS_ADC_LOW;
	sendSPI(0b00001100);
	*msb = 0b00001111&sendSPI(0b10000000);
	*lsb = sendSPI(0);
	CS_ADC_HIGH;
}
