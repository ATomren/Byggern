/*
 * Utilities.c
 *
 * Created: 07.11.2023 15:33:54
 *  Author: adriatom
 */ 

#include "Utilities.h"

void Utilities_init(void){
	//LEDs
	PIOA->PIO_PER = (1 << 19)|(1 << 20);
	PIOA->PIO_OER = (1 << 19)|(1 << 20);
	PIOA->PIO_SODR = (1 << 19)|(1 << 20);
	
	//Button
	PIOC->PIO_PER = (1 << 17);
	PIOC->PIO_OER = (1 << 17);
	PIOC->PIO_SODR = (1 << 17);
}

void Utilities_activate_solenoide(uint8_t button){
	if (button == 1){
		PIOC->PIO_CODR = (1 << 17);
	}else{
		PIOC->PIO_SODR = (1 << 17);
	}
}