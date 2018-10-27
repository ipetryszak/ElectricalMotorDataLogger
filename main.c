/*
 * main.c
 *
 *  Created on: 27 paü 2018
 *      Author: ireneusz
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "sram/sram.h"
#include "uart/uart.h"
#include "spi/spi.h"
#include "adc/adc.h"
#include "timers/timers.h"


int main()
{
	sei();
	initUSART(MYUBRR);
	initSPI();
	initADC();
	initLatch1();
	initLatch2();
	initSRAMControl();

	_delay_ms(10000);
	initTimer2();



	while(1);
}
