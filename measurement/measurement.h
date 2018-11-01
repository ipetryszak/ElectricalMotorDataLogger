/*
 * measurement.h
 *
 *  Created on: 20 paü 2018
 *      Author: ireneusz
 */

#ifndef MEASUREMENT_MEASUREMENT_H_
#define MEASUREMENT_MEASUREMENT_H_

struct settings
{
	uint8_t channel;
	uint8_t samplingTime;
	uint16_t frequency;
};

struct samples
{
	uint8_t MSB;
	uint8_t LSB;
	uint8_t array[32];
};

struct settings newSettings;
struct samples currentSamples;

uint16_t amountOfSamples;

void startSampling(void);
void setSamplingFreq(char freq);
void setSamplingTime(char time);
void setSamplingChannel(char channel);
void setSamplingStart(char setStart);
uint8_t isEnoughMemory(uint16_t amountOfSamples);
uint8_t isSet(void);


#endif /* MEASUREMENT_MEASUREMENT_H_ */
