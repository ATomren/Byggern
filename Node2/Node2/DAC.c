/*
 * DAC.c
 *
 * Created: 03.11.2023 09:22:03
 *  Author: adriatom
 */ 

#include "DAC.h"

void DAC_Init(void){
	DACC->DACC_WPMR = 0x44414300;
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;
	PIOB->PIO_PDR |= PIO_PDR_P16;	// Disable Register
	PIOB->PIO_ABSR &= ~(1 << 16);	// Peripheral Select A
	//PMC->PMC_PCR = PMC_PCR_EN;
	
	DACC->DACC_MR |= (1 << 16);		//Mode Register, USER_SEL= Ch1
				
	DACC->DACC_CHER |= (1 << 1);	//Channel enable register
	
	// Trenger vi interrupt register?
				
	
}


void DAC_Control_Motor_Speed(uint16_t input){
	DACC->DACC_CDR = input;	//Conversion Data Register, Data to convert
}