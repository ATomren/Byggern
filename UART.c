#include "UART.h"

void uart_init(unsigned int ubrr){
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00); //
	
}

void uart_send(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0))){
		//printf("Shit aint working");
	} 
		
	UDR0 = data;
}

unsigned char uart_receive(void){
	while(!(UCSR0A & (1<<RXC0))){
		//printf("Shit ain't working");
	}
	
	return UDR0;
}

void uart_link_printf(void){
 	fdevopen(&uart_send, &uart_receive);
}