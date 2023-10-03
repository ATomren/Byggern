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
#include "CAN_com.h"
#include "CAN_CTRL.h"
#include "SPI_com.h"

 

int main(void)
{
	DDRB &= 0xFC;
	
	uart_init(MYUBRR);
	SRAM_init();
	ADC_init();
	uart_link_printf();
	oled_init();
	
	CAN_CTRL_init();
		
	int oled_current_line = 2;
	oled_reset();
	
	enum CursorState cursor_state = CAN_MOVE;
	
	oled_pos(oled_current_line, 0);
	oled_print_str(">");
	
	while (1){	//The actual program, which will run forever
		/*
		volatile uint8_t ch_C = ADC_read(2);
		volatile uint8_t ch_D = ADC_read(3);
		
		int left_slider_percentage = ADC_scale_slider(ch_D);
		int right_slider_percentage = ADC_scale_slider(ch_C);

		//printf("JoyVert: %d JoyHoriz: %d, SliderLeft: %d, SliderRight: %d \n\r", y_percentage, x_percentage, left_slider_percentage, right_slider_percentage);
		//printf("ButtonLeft: %i, ButtonRight; %i \r\n", buttonA, buttonB);
		//print_direction(joystick_direction);
		//printf("\r\n");
	
		MENU_vertical_navigator(&cursor_state, &oled_current_line);
		MENU_print();
		*/
		
		SPI_read();

		//_delay_ms(10);
		_delay_ms(1000);

		//CAN_CTRL_write(MCP_CANCTRL, 0x0F);
		//_delay_ms(10);
		uint8_t canStat = CAN_CTRL_read(MCP_CANSTAT);
		printf("CANSTAT: %x \n\r", canStat);
		_delay_ms(1000);
		
		CAN_CTRL_bit_modify(MCP_CANCTRL, 0b11100000, MODE_LOOPBACK);
		canStat = CAN_CTRL_read(MCP_CANSTAT);
		printf("CANSTAT: %x \n\r", canStat);
		

		
		
/*
		if (regValue == 0x0F) {
			printf("JIPPPPIIII \n\r");
			} else {
			printf("FAAAAAAAAAEEEEEEEEN \n\r");
		}*/
_delay_ms(1000);
	}
}

