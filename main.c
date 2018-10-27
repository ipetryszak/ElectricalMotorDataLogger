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
	uint8_t data,l=0;
	uint16_t zapis = 0;

	initLatch1();
	initLatch2();

	setAddress(0b00000000);

	initSRAMControl();


	for(zapis = 0b0000000000000000; zapis<=0b0100000000000000;zapis++,l++)
	{

		setAddress(zapis);
		writeByte(l);

	}



	zapis = 0b0000000000000000;

	while(1)
	{
		zapis++;
		if(zapis==0b0100000000000000)
			{
			sendUSART('!');
			while(1);
			}

		setAddress(zapis);
		data = readByte();
		uart_putint(data,10);
		sendUSART('-');
		_delay_ms(1);

	}
}
