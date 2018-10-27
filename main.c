/*
 * main.c
 *
 *  Created on: 27 paü 2018
 *      Author: ireneusz
 */

#include <avr/io.h>
#include <avr/delay.h>
#include "sram/sram.h"
#include "uart/uart.h"


int main()
{
	initUSART(MYUBRR);
	uint8_t data,zapis = 0;

	initLatch1();
	setAddress(0b00000000);

	initSRAMControl();

	uint8_t l = 0;
	for(zapis = 0b01000000; zapis<0b11000000;zapis++,l++)
	{
		setAddress(zapis);
		writeByte(l);
	}

	zapis = 0b01000000;

	while(1)
	{
		zapis++;
		if(zapis>0b11000000)
			{
			sendUSART('!');
			zapis = 0b01000000;
			}

		setAddress(zapis);
		data = readByte();
		uart_putint(data,10);
		sendUSART('-');
		_delay_ms(1000);

	}
}
