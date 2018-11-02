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

/*
 * TIMER2
 */
void setAndStartTimer(uint16_t freq,uint8_t doubleSpeed)
{

	//ctc mode
	TCCR2 |= (1<<WGM21);

	if(doubleSpeed==0)
	{
		if(((freq>=1000)&(freq<=5000))|((freq==8000) | (freq==10000)))
			{
				TCCR2 &= ~((1<<CS20) | (1<<CS21));
				TCCR2 |= (1<<CS22);
			}
		if((freq==6000) | (freq==7000))
			{
				TCCR2 &= ~(1<<CS22);
				TCCR2 |= (1<<CS20) | (1<<CS21);
			}
		if(freq==9000)
			{
			TCCR2 &= ~((1<<CS22) | (1<<CS20));
			TCCR2 |= (1<<CS21);
			}
		if(freq==1000)OCR2 = 249; //1000Hz
		if(freq==2000)OCR2 = 124; //2000Hz
		if(freq==3000)OCR2 = 82; //3012Hz
		if(freq==4000)OCR2 = 61; //4032Hz
		if(freq==5000)OCR2 = 49; //5000Hz
		if(freq==6000)OCR2 = 82; //6024Hz
		if(freq==7000)OCR2 = 32; //7042Hz
		if(freq==8000)OCR2 = 30; //8064Hz
		if(freq==9000)OCR2 = 221; //9009Hz
		if(freq==10000)OCR2 = 24; //10000Hz
	}
	else if(doubleSpeed==1)
	{
		if(((freq>=1000)&(freq<=2000))|((freq==4000) | (freq==5000)))
			{
				TCCR2 &= ~((1<<CS20) | (1<<CS21));
				TCCR2 |= (1<<CS22);
			}
		if((freq==3000))
			{
				TCCR2 &= ~(1<<CS22);
				TCCR2 |= (1<<CS20) | (1<<CS21);
			}
		if(freq==1000)OCR2 = 124; //1000Hz
		if(freq==2000)OCR2 = 61; //4032Hz
		if(freq==3000)OCR2 = 82; //6024Hz
		if(freq==4000)OCR2 = 30; //8064Hz
		if(freq==5000)OCR2 = 24; //10000Hz
	}
	else{}
	//interrupt when compared
	TIMSK |= (1<<OCIE2);
}


void stopTimer(void)
{
	//clear all prescaling bits
	TCCR2 &= ~((1<<CS22) | (1<<CS21) | (1<<CS20));
}



ISR(TIMER2_COMP_vect)
{
	startSampling();
}
