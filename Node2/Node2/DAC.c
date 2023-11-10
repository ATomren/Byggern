/*
 * DAC.c
 *
 * Created: 03.11.2023 09:22:03
 *  Author: adriatom
 */ 

#include "DAC.h"

void DAC_Init(void){
	DACC->DACC_WPMR = 0x44414300; //Write protect
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;
	PIOB->PIO_PDR |= PIO_PDR_P16;	// Disable Register
	PIOB->PIO_ABSR &= ~(1 << 16);	// Peripheral Select A
	//PMC->PMC_PCR = PMC_PCR_EN;
	
	DACC->DACC_MR |= (1 << 16);		//Mode Register, USER_SEL= Ch1
				
	DACC->DACC_CHER |= (1 << 1);	//Channel enable register
}


void DAC_Control_Motor_Speed(uint16_t input){
	DACC->DACC_CDR = input;	//Conversion Data Register, Data to convert	
}

void DAC_Joystick_To_Motor_Speed(uint8_t js_percentage, uint16_t* current_speed){
	uint8_t speed_delta = 100;
	if((js_percentage >= 75) && (*current_speed < 3995)){
		DACC->DACC_CDR = *current_speed + speed_delta;
		*current_speed = *current_speed + speed_delta;
	}
	else if ((js_percentage <= 25) && (*current_speed >= 1600)){
		DACC->DACC_CDR = *current_speed - speed_delta;
		*current_speed = *current_speed - speed_delta;
	}
}