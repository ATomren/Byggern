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
#include "OLED.h"
#include "MENU.h"

 

int main(void)
{
	DDRB &= 0xFC;
	
	uart_init(MYUBRR);
	SRAM_init();
	ADC_init();
	uart_link_printf();
	oled_init();
	
	int oled_current_line = 2;
	oled_reset();
	
	enum CursorState cursor_state = CAN_MOVE;
	
	oled_pos(oled_current_line, 0);
	oled_print_str(">");
	
	
	while (1){	//The actual program, which will run forever
		//SRAM_test();
		
		
		
		volatile uint8_t ch_C = ADC_read(2);
		volatile uint8_t ch_D = ADC_read(3);
		
		
		int left_slider_percentage = ADC_scale_slider(ch_D);
		int right_slider_percentage = ADC_scale_slider(ch_C);
		//enum pos_t joystick_direction = ADC_pos_read(x_percentage, y_percentage);
		
	

		//printf("JoyVert: %d JoyHoriz: %d, SliderLeft: %d, SliderRight: %d \n\r", y_percentage, x_percentage, left_slider_percentage, right_slider_percentage);
		//printf("ButtonLeft: %i, ButtonRight; %i \r\n", buttonA, buttonB);
		//print_direction(joystick_direction);
		//printf("\r\n");
	
	
		MENU_vertical_navigator(&cursor_state, &oled_current_line);
		MENU_print();
		
		
		
		_delay_ms(10);

		

// 		unsigned char received_data = uart_receive();
//  		printf("Received data: %c", received_data);
// 		printf("\n");
		
		//output_testing();

		 
		//uart_send('h');
		
	}
	//uart_receive();
}

