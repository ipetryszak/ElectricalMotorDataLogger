/*
 * measurement.c
 *
 *  Created on: 20 paü 2018
 *      Author: ireneusz
 */

#include <avr/io.h>
#include <avr/delay.h>

#include "../uart/uart.h"
#include "../adc/adc.h"
#include "../timers/timers.h"
#include "../sram/sram.h"
#include "measurement.h"


void startSampling(void)
{

	static uint16_t address = 0b0000000000000000;
	uint8_t MSB,LSB;
	static uint16_t currentSample = 0;
	uint16_t sampl;



	makeSampleChannelA(&MSB,&LSB);

	setAddress(address);
	writeByte(MSB);
	address++;
	setAddress(address);
	writeByte(LSB);
	address++;

	currentSample++;

	if(currentSample>3000)
		{

		stopTimer2(); //stop sampling
		uint16_t add;
		uint16_t data;
		sendUSART('@');
		for(add=0b0000000000000000;add<address;add+=2)
		{
			setAddress(add);
			data = (readByte()<<8);
			setAddress(add+1);
			data |= readByte();
			uart_putint(data,10);
			data = 0;
			sendUSART('-');
			_delay_ms(2);
		}


		while(1);
		sendUSART('!');

		}



}
