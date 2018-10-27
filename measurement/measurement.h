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
	uint8_t period;
	uint16_t amountOfSamples;
};

struct samples
{
	uint8_t MSB;
	uint8_t LSB;
	uint8_t array[32];
};

struct settings newSettings;
struct samples currentSamples;

void setSettings(uint8_t,uint8_t);
void startSampling(void);


#endif /* MEASUREMENT_MEASUREMENT_H_ */
