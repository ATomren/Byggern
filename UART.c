#include "UART.h"

void uart_init(unsigned int ubrr){
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;
	
	UCSRB = (1<<RXEN) | (1<<TXEN);
	
	UCSRC = (1<<URSEL) | (1<<USBS) | (3<<UCSZ0); //
	
}

void uart_send(unsigned char data){
	while(!(UCSRA & (1<<UDRE))); 
		
	UDR = data;
}

unsigned char uart_receive(){
	while(!(UCSRA & (1<<RXC)));
	
	return UDR;
}