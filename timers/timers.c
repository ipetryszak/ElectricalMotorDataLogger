/*
 * timers.c
 *
 *  Created on: 17 paü 2018
 *      Author: ireneusz
 */
#include<avr/io.h>
#include<avr/interrupt.h>
#include "timers.h"
#include "../uart/uart.h"
#include "../adc/adc.h"
#include "../measurement/measurement.h"


void initTimer2(void)
{
	/*
	 * timer2
	 * 16MHz/64/99 - 1 = 2500 Hz
	 * 31 = 1s = 2ks
	 */
	//ctc mode
	TCCR2 |= (1<<WGM21);
	//fclk/64
	TCCR2 |= (1<<CS22);
	//interrupt when compared
	TIMSK |= (1<<OCIE2);
	//extra divider //99
	OCR2 = 82; //3000Hz
}

void stopTimer2(void)
{
	//clear fclk/64
	TCCR2 &= ~(1<<CS22);
}

ISR(TIMER2_COMP_vect)
{
	startSampling();
}
