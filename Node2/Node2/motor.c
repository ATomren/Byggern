/*
 * motor.c
 *
 * Created: 03.11.2023 14:35:36
 *  Author: adriatom
 */ 

#include "motor.h"


void MOTOR_init(void){
	PIOD->PIO_PER |= EN|NOT_RST|NOT_OE|SEL|DIR;
	
	PIOD->PIO_OER |= EN|NOT_RST|NOT_OE|SEL|DIR;
	
	PIOD->PIO_CODR = NOT_RST;
	PIOD->PIO_SODR = EN|NOT_OE;	//NOT_OE for å ikke sample i utgangspunkt?
	
	//Kjør til en side for å kalibrere?
	
	_delay_ms(50);
	
	PIOD->PIO_SODR = NOT_RST;
	
	PIOC->PIO_ODR |= 0x1FE;	//PIN 1 til 8
}



void MOTOR_read_encoder(void){
	
	// 1: Set !OE low, to sample and hold the encoder value
	PIOD->PIO_CODR = NOT_OE;

	// 2: Set SEL low to output high byte
	PIOD->PIO_CODR = SEL;
	
	// 3: Wait approx. 20 microseconds for output to settle
	
	_delay_us(20);
	
	// 4: Read MJ2 to get high byte
	uint8_t encoder_high_byte = (PIOC->PIO_PDSR >> 1);
	printf("ENCODA High BYTE: %x \r\n", encoder_high_byte);
	
	// 5: Set SEL high to output low byte
	PIOD->PIO_SODR = SEL;
	
	// 6: Wait approx. 20 microseconds
	_delay_us(20);
	
	// 7: Read MJ2 to get low byte
	uint8_t encoder_low_byte = (PIOC->PIO_PDSR >> 1);
	printf("ENCODA low BYTE: %x \r\n", encoder_low_byte);
	// 8: Set !OE to hi
	PIOD->PIO_SODR = NOT_OE;
}


// uint8_t extract_encoder_val(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7) {
// 	return (b7 << 7) | (b6 << 6) | (b5 << 5) | (b4 << 4) |(b3 << 3) | (b2 << 2) | (b1 << 1) | b0;
// }


