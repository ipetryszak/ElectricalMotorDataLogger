/*
 * sram.c
 *
 *  Created on: 27 paü 2018
 *      Author: ireneusz
 */

#include <avr/io.h>
#include<avr/delay.h>
#include "sram.h"

void initSRAMControl(void)
{
	SRAM_CONTROL_DDR |= SRAM_WE | SRAM_OE | SRAM_CE;
	SRAM_CONTROL_PORT |=SRAM_WE | SRAM_OE;
	SRAM_CE_LOW;
}

void initLatch1(void)
{
	DDRB |= (1<<PB0);
	PORTB &=~(1<<PB0);
}

void dataPortOutput(void)
{
	DDRC = 0b11111111;
	DDRD |= 0b01100000;
}
void dataPortInput(void)
{
	DDRC = 0b11000000;
	DDRD &= ~((1<<PD5) | (1<<PD6));
}


void setAddress(uint8_t byte)
{
	dataPortOutput();
	PORTC = 0b11000000;
	PORTD &= ~((1<<PD5) | (1<<PD6));
	PORTC |= (0b00111111&byte);
	byte = byte&0b11000000;
	PORTD |= byte>>1;
	PORTB |=(1<<PB0);
	PORTB &=~(1<<PB0);
	PORTC = 0b11000000;
	PORTD &= ~((1<<PD5) | (1<<PD6));
}

void writeByte(uint8_t byte)
{
	dataPortOutput();
	PORTC = 0b11000000;
	PORTD &= ~((1<<PD5) | (1<<PD6));
	PORTC |= (0b00111111&byte);
	byte = byte&0b11000000;
	PORTD |= byte>>1;
	SRAM_WE_LOW;
	SRAM_WE_HIGH;
	PORTC = 0b11000000;
	PORTD &= ~((1<<PD5) | (1<<PD6));
}

uint8_t readByte(void)
{
	uint8_t byte;
	dataPortInput();
	SRAM_OE_LOW;
    _delay_us(1);
	byte = PINC;
	byte |= ((PIND&0b01100000)<<1);
	SRAM_OE_HIGH;
	return byte;
}

