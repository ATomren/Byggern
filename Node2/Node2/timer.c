/*
 * timer.c
 *
 * Created: 24.10.2023 08:39:28
 *  Author: adriatom
 */ 


#include "timer.h"


volatile uint32_t down_counter = 0;

static void SysTick_init(int us) {
	
	SysTick->LOAD = (us*84) - 1;    //Reload-value is N-1, where N is 84*input in microseconds

	SysTick->VAL = 0;		// Sets counter-value to 0

	SysTick->CTRL = 0b111;	// Sets Control to: Clock=MCK, Tickint = countdown to zero asserts SystTick exception-request (interrupt), and enables counter
	
	NVIC_SetPriority(SysTick_IRQn, 1);	// set the priorty of the interrupt to 1 (less than the TC0-handler)
}

void _delay_ms(uint16_t ms) {
	SysTick_init(1000);	//Initialize Systick init function with 1000 microseconds (1 millisecond)
	down_counter = ms;
	
	while(down_counter != 0){
		};
}

void _delay_us(uint16_t us) {
	SysTick_init(1);	//Initialize Systick init function with 1 microseconds
	down_counter = us;
	
	while(down_counter != 0){
		};
}



void SysTick_Handler(void) {
	if(down_counter!=0) {
		down_counter = down_counter - 1; //Decrements the downcounter to update the delay_functions
	}
	else {
		SysTick->CTRL = 0;	//Resets Control-register and disables counter
	}
}




/*
volatile float microseconds = 0;

void SysTick_Handler(void){
		microseconds++;
}

void _delay_us(int us){
	int init_time = microseconds;
	while((microseconds - init_time) > us){	
	}
}


void _delay_ms(float ms){
	float init_time = microseconds;
	while(((microseconds) - init_time) > ms){
	}
}*/