/*
 * uart.c
 *
 *  Created on: 25 paü 2018
 *      Author: ireneusz
 */
#include<avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "../measurement/measurement.h"


//------------------------------------------------------------------------------
//-- init USART ----------------------------------------------------------------
void initUSART(unsigned int ubrr) {
	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) ubrr;
	/* Enable receiver and transmitter and enable interrupt when received */
	UCSRB = (1 << TXEN) | (1<<RXEN) | (1<<RXCIE);
	/* Set frame format: 8data, 1stop bit */
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//-- send USART ----------------------------------------------------------------
void sendUSART(unsigned char data) {
	/* Wait for empty transmit buffer */
	while (!( UCSRA & (1 << UDRE)));
	/* Put data into buffer, sends the data */
	UDR = data;
}
//------------------------------------------------------------------------------
void uart_puts(char *s) {
	register char c;
	while ((c = *s++))
		sendUSART(c);
}

void uart_putint(int value, int radix) {
	char string[17];			// bufor na wynik funkcji itoa
	itoa(value, string, radix);		// konwersja value na ASCII
	uart_puts(string);
}


ISR(USART_RXC_vect)
{
	//get received data from uart register
	char character = UDR;

	/*  char array to hold commands - commands specifics
	 *  first letter					second letter
	 *  C - channel					1 - CH1, 2 - CH2, 3 - CH12
	 *  F - sampling frequency		1..10 kHz
	 *  T - sampling time			1..10 s
	 *  S - start sampling			1 - start promptly, 2 - start on rising edge
	 *
	 *  commands are ended with char '!'
	 */
	static char command[2];

	//iterator for tab
	static uint8_t i=0;

	if(character!='!')command[i++]=character;
	else
	{
		i = 0;

		switch(command[0])
		{
			case 'C': //channel
			{
				if(command[1]>='1'&&command[1]<='3')
					{
						setSamplingChannel(command[1]);
					}
				break;
			}
			case 'F': //freq samp
			{
				if(command[1]>='0'&&command[1]<='9')
					{
						setSamplingFreq(command[1]);
					}

				break;
			}
			case 'T': //time
			{
				if(command[1]>='0'&&command[1]<='9')
					{
						setSamplingTime(command[1]);
					}

				break;
			}
			case 'S': //start sampling
			{
				if(command[1]>='1'&&command[1]<='2')
				{
					setSamplingStart(command[1]);
				}

				break;
			}
		}
	}
}

