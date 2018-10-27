/*
 * uart.c
 *
 *  Created on: 25 paü 2018
 *      Author: ireneusz
 */
#include<avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"


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
