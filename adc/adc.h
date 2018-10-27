/*
 * adc.h
 *
 *  Created on: 15 paü 2018
 *      Author: ireneusz
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_


#define CS_ADC_PIN (1<<PB2);
#define CS_ADC_HIGH PORTB |= CS_ADC_PIN;
#define CS_ADC_LOW PORTB &= ~CS_ADC_PIN;

void initADC(void);
void makeSampleChannelA(uint8_t *msb, uint8_t *lsb);
void makeSampleChannelB(uint8_t *msb, uint8_t *lsb);

#endif /* ADC_ADC_H_ */
