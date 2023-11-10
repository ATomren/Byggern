/*
 * ADC.c
 *
 * Created: 24.10.2023 13:54:44
 *  Author: adriatom
 */ 

#include "ADC.h"


void ADC_init(void){	
	
	ADC->ADC_WPMR = 0x41444300;			//Write-protect OFF
		
	PMC->PMC_PCR = PMC_PCR_EN					// Enable Peripheral clock
				 | PMC_PCR_DIV_PERIPH_DIV_MCK	// clock = MCK
				 | (ID_ADC << PMC_PCR_PID_Pos); // Peripheral ID set to ID 37 (ADC)
	PMC->PMC_PCER1 |= (1 << 5);					// Enable specific peripheral clock for ADC (ID is 37, but 5 for clock 1) (ID=37 minus regsize= 32)
	
	ADC->ADC_CHER = ADC_CHER_CH0;				//Enable channel 0
	
	ADC->ADC_MR = ADC_MR_FREERUN;				//Set mode to freerun so the ADC converts continuously
	
	ADC->ADC_CR = ADC_CR_START;					// Start ADC
				
	// | ADC_CR_SWRST;				// Software-reset of ADC
	//_delay_ms(50);
}

uint16_t ADC_read(void){
	return ADC->ADC_CDR[ADC_channel];
}



