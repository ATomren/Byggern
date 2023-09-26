/*
 * GccApplication1.c
 *
 * Created: 29.08.2023 09:08:00
 * Author : adriatom
 */ 

#include <avr/io.h>
#define F_CPU 4915200UL
#include <stdio.h>
#include <util/delay.h>

#include "UART.h"

int main(void)
{
//      while (1) 
//      {
//  		PORTB |= (1 << PB0);
//  		_delay_ms(500);
//  		PORTB &= (0 << PB0);
//  		_delay_ms(500);
//      }

	uart_init(MYUBRR);

}

