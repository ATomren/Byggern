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
#include "ADC.h"

 

int main(void)
{
	DDRB &= 0xFC;
	
	uart_init(MYUBRR);
	SRAM_init();
	ADC_init();
	uart_link_printf();
	
	
	while (1){	//The actual program, which will run forever
		//SRAM_test();
		
		volatile uint8_t ch_A = ADC_read(0);
		volatile uint8_t ch_B = ADC_read(1);
		volatile uint8_t ch_C = ADC_read(2);
		volatile uint8_t ch_D = ADC_read(3);
		
		int x_percentage = ADC_scale_X(ch_B);		//
		int y_percentage = ADC_scale_Y(ch_A);
		int left_slider_percentage = ADC_scale_slider(ch_D);
		int right_slider_percentage = ADC_scale_slider(ch_C);
		enum pos_t joystick_direction = ADC_pos_read(x_percentage, y_percentage);
		
		int buttonA = (PINB & (1 << PB0)) >> PB0;
		int buttonB = (PINB & (1 << PB1)) >> PB1;

		printf("JoyVert: %d JoyHoriz: %d, SliderLeft: %d, SliderRight: %d \n\r", y_percentage, x_percentage, left_slider_percentage, right_slider_percentage);
		print_direction(joystick_direction);
		//printf("ButtonLeft: %i, ButtonRight; %i \r\n", buttonA, buttonB);

		_delay_ms(500);



// 		unsigned char received_data = uart_receive();
//  		printf("Received data: %c", received_data);
// 		printf("\n");
		
		//output_testing();

		 
		//uart_send('h');
		
	}
	//uart_receive();
}

