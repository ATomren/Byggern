#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void uart_init(unsigned int ubrr);
void uart_send(unsigned char data);
unsigned char uart_receive(void);
void uart_link_printf(void);


#endif //UART_H