/*
 * ADC.c
 *
 * Created: 19.09.2023 09:44:19
 *  Author: adriatom
 */ 
#include "ADC.h"
#include "UART.h"

void ADC_init(void){
	//ASSR |= (1<<AS2);
	
	OCR3A = 0x02;
	DDRD |= (1 << PD4);
	TCCR3B |= (1 << WGM32);
	TCCR3A |= (1 << COM3A0);
	TCCR3B |= (1 << CS30);
	
}

uint8_t ADC_read(uint8_t channel){ //has to be volatile
	
	volatile char *p_ADC = (char *) 0x1400; // Start address for the ADC
	p_ADC[0] = 0;
	
	_delay_ms(9*8/FOSC); //Waits for read
	
	uint8_t retreived_value;
	for (int i = 0; i <= channel; i++) {
		retreived_value = p_ADC[0];
		
	}
	//printf("Value of channel %d is %d \n", channel, retreived_value);
	return retreived_value;
	
}


int ADC_scale_X(uint8_t x_axis){
	int max = 255;
	int neutral = 160;
	int width = max - neutral;
	int min = neutral - width;
	
	if((x_axis >= neutral) && (x_axis <= max)){
		return ((x_axis - neutral) * 100) / width;		//Positive direction: 0 to 100%
	}
	else if(x_axis < neutral && x_axis >= min){
		return -(((neutral - x_axis) * 100) / width);	//Negative direction: -100 to 0%
	}
	
	else if(x_axis < min){return -100;}					//Negative direction if below measurement area
	else{return 100;}									//Positive direction if over measurement area
}

int ADC_scale_Y(uint8_t y_axis){
	int max = 255;
	int neutral = 163;
	int width = max - neutral;
	int min = neutral - width;
	
	if((y_axis >= neutral) && (y_axis <= max)){
		return ((y_axis - neutral) * 100) / width;		//Positive direction: 0 to 100%
	}
	else if((y_axis < neutral) && (y_axis >= min)){
		return -(((neutral - y_axis) * 100) / width);	//Negative direction: -100 to 0%
	}
	
	else if(y_axis < min){return -100;}					//Negative direction if below measurement area
	else{return 100;}									//Positive direction if over measurement area
}

int ADC_scale_slider(uint8_t slider){
	float slider_flt = slider;
	return ((slider_flt/255)*100);
}

enum pos_t ADC_pos_read(int x_percentage, int y_percentage){
	if(abs(y_percentage) >= abs(x_percentage)){
		if(y_percentage >= 50){
			return UP;
		}else if (y_percentage <= -50){
			return DOWN;
		}else{
			return NEUTRAL;
		}
	}
	
	else{
		if(x_percentage >= 50){
			return RIGHT;
		}else if (x_percentage <= -50){
			return LEFT;
		}else{
			return NEUTRAL;
		}
	}
};


/*enum pos_t ADC_pos_read_horizontal(int x_percentage){
	if(x_percentage > 50){
		return RIGHT;
		};
	else if(x_percentage < -50){
		return LEFT;
	}else{
		return NEUTRAL;}
	};
	*/

void print_direction(enum pos_t direction){
		switch (direction) {
			case UP:
			printf("Joystick is UP\r\n");
			break;
			case DOWN:
			printf("Joystick is DOWN\r\n");
			break;
			case LEFT:
			printf("Joystick is LEFT\r\n");
			break;
			case RIGHT:
			printf("Joystick is RIGHT\r\n");
			break;
			case NEUTRAL:
			printf("Joystick is NEUTRAL\r\n");
			break;
		}
	}

