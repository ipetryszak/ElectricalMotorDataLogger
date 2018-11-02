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
	static uint8_t toggle = 0;

	if(chosenChannel == 1) makeSampleChannelA(&MSB,&LSB);
	if(chosenChannel == 2) makeSampleChannelB(&MSB,&LSB);
	if(chosenChannel == 3 && toggle==0){ makeSampleChannelA(&MSB,&LSB); toggle = 1;}
	else if(chosenChannel==3 && toggle==1){ makeSampleChannelB(&MSB,&LSB); toggle = 0;}
	else {}

	setAddress(address);
	writeByte(MSB);
	address++;
	setAddress(address);
	writeByte(LSB);
	address++;

	currentSample++;

	if(currentSample>amountOfSamples)
	{

		stopTimer(); //stop sampling
		uint16_t add;
		uint16_t data;

		for(add=0b0000000000000000;add<address;add+=2)
		{
			setAddress(add);
			data = (readByte()<<8);
			setAddress(add+1);
			data |= readByte();
			uart_putint(data,10);
			data = 0;
			sendUSART(',');
		}
		sendUSART('!');
		address = 0b0000000000000000;
		currentSample = 0;

	}
}


void setSamplingChannel(char channel)
{
	//1 - ch1, 2 - ch2, 3 - ch12
	if(channel=='1')newSettings.channel = 1;
	if(channel=='2')newSettings.channel = 2;
	if(channel=='3')newSettings.channel = 3;

}

void setSamplingFreq(char freq)
{
	//in hz
	if(freq=='0')newSettings.frequency = 1000;
	if(freq=='1')newSettings.frequency = 2000;
	if(freq=='2')newSettings.frequency = 3000;
	if(freq=='3')newSettings.frequency = 4000;
	if(freq=='4')newSettings.frequency = 5000;
	if(freq=='5')newSettings.frequency = 6000;
	if(freq=='6')newSettings.frequency = 7000;
	if(freq=='7')newSettings.frequency = 8000;
	if(freq=='8')newSettings.frequency = 9000;
	if(freq=='9')newSettings.frequency = 10000;
}
void setSamplingTime(char time)
{
	//in seconds
	if(time=='0')newSettings.samplingTime = 1;
	if(time=='1')newSettings.samplingTime = 2;
	if(time=='2')newSettings.samplingTime = 3;
	if(time=='3')newSettings.samplingTime = 4;
	if(time=='4')newSettings.samplingTime = 5;
	if(time=='5')newSettings.samplingTime = 6;
	if(time=='6')newSettings.samplingTime = 7;
	if(time=='7')newSettings.samplingTime = 8;
	if(time=='8')newSettings.samplingTime = 9;
	if(time=='9')newSettings.samplingTime = 10;
}
void setSamplingDefaultSettings(void)
{
	setSamplingChannel('1');
	setSamplingFreq('0');
	setSamplingTime('0');
}
uint8_t isSet(void)
{
	if((newSettings.channel != 0) && (newSettings.frequency != 0) && (newSettings.samplingTime != 0)) return 1;
	else return 0;
}
uint8_t isEnoughMemory(uint16_t amountOfSamples)
{
	if(amountOfSamples<=MEMORY_SIZE_BYTES_FOR_SAMPLES) return 1;
	else return 0;
}
void setSamplingStart(char setStart)
{
	if(isSet())
	{
		amountOfSamples = 0;
		chosenChannel = newSettings.channel;
		if(chosenChannel==3)speed2x =1;
		else speed2x = 0;

		if(chosenChannel==3)time2xOrNot = newSettings.samplingTime + newSettings.samplingTime;
		else time2xOrNot = newSettings.samplingTime;

		uint8_t iterator;
		for(iterator=0;iterator<time2xOrNot;iterator++) amountOfSamples+=newSettings.frequency;

		if(isEnoughMemory(amountOfSamples))
		{
			setAndStartTimer(newSettings.frequency,speed2x);
		}

	}

}

