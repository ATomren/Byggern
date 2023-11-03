/*
 * ADC.c
 *
 * Created: 24.10.2023 13:54:44
 *  Author: adriatom
 */ 

#include "ADC.h"


void ADC_init(void){	
	
	//ADC->ADC_WPMR = 0x41444301;
	
	ADC->ADC_MR = ADC_MR_FREERUN;
	ADC->ADC_CHER = ADC_CHER_CH0;
	PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_ADC << PMC_PCR_PID_Pos);
	PMC->PMC_PCER1 |= 1 << (ID_ADC - 32);
	ADC->ADC_CR = ADC_CR_START;
	//ADC->ADC_CR = 0b10;

	// ADC_COR??!! enable single ended mode
}

uint16_t ADC_read(void){
	return ADC->ADC_CDR[ADC_channel];
}



