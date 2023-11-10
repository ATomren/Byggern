/*
 * motor.c
 *
 * Created: 03.11.2023 14:35:36
 *  Author: adriatom
 */ 

#include "motor.h"


void MOTOR_init(void){
	PMC->PMC_PCER0 |= PMC_PCER0_PID13;	// Peripheral Clock Enable 0, PIOC
	
	PIOD->PIO_PER |= EN|NOT_RST|NOT_OE|SEL|DIR;	//Enable perpiherals
	
	PIOD->PIO_OER |= EN|NOT_RST|NOT_OE|SEL|DIR;	//Set as outputs
	
	PIOD->PIO_SODR = EN|NOT_OE;	//NOT_OE for å ikke sample i utgangspunkt?
	
	//Kalibrering, kjør motor til en side
	PIOD->PIO_SODR = DIR;
	DAC_Control_Motor_Speed(2500);
	_delay_ms(2000);
	DAC_Control_Motor_Speed(0);
	
	
	PIOD->PIO_CODR = NOT_RST; //Reset enkoder
	_delay_ms(50);
	PIOD->PIO_SODR = NOT_RST; //Reset enkoder
	
	PIOC->PIO_ODR |= 0x1FE;	//PIN 1 til 8, pins for å lese fra enkoder
	printf("motor init complete \n\r");
}



uint16_t MOTOR_read_encoder(void){
	
	// 1: Set !OE low, to sample and hold the encoder value
	PIOD->PIO_CODR = NOT_OE;

	// 2: Set SEL low to output high byte
	PIOD->PIO_CODR = SEL;
	
	// 3: Wait approx. 20 microseconds for output to settle
	
	_delay_us(20);
	
	// 4: Read MJ2 to get high byte
	uint8_t encoder_high_byte = (PIOC->PIO_PDSR >> 1);
	
	// 5: Set SEL high to output low byte
	PIOD->PIO_SODR = SEL;
	
	// 6: Wait approx. 20 microseconds

	_delay_us(20);
	
	// 7: Read MJ2 to get low byte
	uint8_t encoder_low_byte = (PIOC->PIO_PDSR >> 1);

	// 8: Set !OE to hi
	PIOD->PIO_SODR = NOT_OE;
	
	return (uint16_t)(encoder_high_byte << 8 | encoder_low_byte); //Sette sammen high og low byte til uint16
	
	//printf("WORD: %u \t HIGH: %u \t LOW: %u \r\n", encoder_value, encoder_high_byte, encoder_low_byte);
}


