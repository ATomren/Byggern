/*
 * GccApplication1.c
 *
 * Created: 29.08.2023 09:08:00
 * Author : adriatom
 */ 

#include <avr/io.h>

#include <stdio.h>
#include "UART.h"
#include "SRAM.h"

 

int main(void)
{
	uart_init(MYUBRR);
	SRAM_initialize();
	uart_link_printf();
	
	
	while (1){	//The actual program, which will run forever
		SRAM_test();
		
		
		

// 		unsigned char received_data = uart_receive();
//  		printf("Received data: %c", received_data);
// 		printf("\n");
		
		//output_testing();

		 
		//uart_send('h');
		
	}
	//uart_receive();
}

