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


void setTimer(uint16_t freq)
{

	//ctc mode
	TCCR2 |= (1<<WGM21);
	//fclk/64
	TCCR2 |= (1<<CS22);

	if(freq==1000)OCR2 = 249; //1000Hz
	if(freq==2000)OCR2 = 124; //2000Hz
	if(freq==3000)OCR2 = 82; //3012Hz
	if(freq==4000)OCR2 = 61; //4032Hz
	if(freq==5000)OCR2 = 49; //5000Hz
	if(freq==6000)OCR2 = 40; //6097Hz
	if(freq==7000)OCR2 = 34; //7142Hz
	if(freq==8000)OCR2 = 30; //8064Hz
	if(freq==9000)OCR2 = 26; //9259Hz
	if(freq==10000)OCR2 = 24; //10000Hz

	//interrupt when compared
	TIMSK |= (1<<OCIE2);

	//wymagane poprawki do obliczania pamiÍci!

}


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
