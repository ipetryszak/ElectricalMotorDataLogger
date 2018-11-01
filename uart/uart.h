/*
 * uart.h
 *
 *  Created on: 25 paü 2018
 *      Author: ireneusz
 */

#ifndef UART_UART_H_
#define UART_UART_H_


#define FOSC 16000000// Clock Speed
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1

void initUSART(unsigned int ubrr);
void sendUSART(unsigned char data);
void uart_puts(char *s);
void uart_putint(int value, int radix);


#endif /* UART_UART_H_ */
