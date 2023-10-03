/*
 * CAN_CTRL.c
 *
 * Created: 03.10.2023 08:15:09
 *  Author: adriatom
 */ 

// CAN Control is the header for the MCP2515 CAN Controller

#include "CAN_CTRL.h"

uint8_t CAN_CTRL_init(void){
		
	SPI_MasterInit();	//Initialize SPI
	CAN_CTRL_reset();	//Send reset-command
	
	_delay_ms(50);
	
	// Self-test
	uint8_t value = CAN_CTRL_read(MCP_CANSTAT);
	_delay_ms(50);
	
	if ((value & MODE_MASK) != MODE_CONFIG){
		printf("MCP2515 is NOT in configuration mode after reset! : %x \n\r", value);
		return 1;	//Init error/incomplete
	}
	
	// MORE INITIALIZATION
	printf("MCP2515 initialized correctly! : %x \n\r", value);
	return 0;	//Init complete	
}


uint8_t CAN_CTRL_read(uint8_t address){
	uint8_t result;
	
	PORTB &= ~(1<<PB4); //Select CAN-controller
	
	SPI_write(MCP_READ);	// Send read instruction: MCP_READ = 0b11
	SPI_write(address);		// Send address
	result = SPI_read();	// Read result
	
	PORTB |= (1<<PB4);
	
	return result;
}

void CAN_CTRL_write(uint8_t address, uint8_t data){
	
	PORTB &= ~(1 << PB4); // Select CAN-controller			
	
	SPI_write(MCP_WRITE);  // Send write instruction: MCP_WRITE = 0b02
	SPI_write(address);     // Send address
	SPI_write(data);        // Send data
	
	PORTB |= (1 << PB4);
}

void CAN_CTRL_RTS(void){
	PORTB &= ~(1 << PB4); // Select CAN-controller
	
	uint8_t value_RTS__TX0 = 0x81;
	SPI_write(value_RTS__TX0); // Send RTS instruction with the desired RTS bits
	
	PORTB |= (1 << PB4);
}

uint8_t CAN_CTRL_read_status(void){
	uint8_t result;
	
	PORTB &= ~(1 << PB4);		// Select CAN-controller
	
	SPI_write(MCP_READ_STATUS); // Send read status instruction
	result = SPI_read();        // Read result
	
	PORTB |= (1 << PB4);
	
	return result;
}

void CAN_CTRL_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	PORTB &= ~(1 << PB4);		// Select CAN-controller
	
	SPI_write(MCP_BITMOD); // Send bit modify instruction
	SPI_write(address);        // Send address
	SPI_write(mask);           // Send mask
	SPI_write(data);           // Send data
	
	PORTB |= (1 << PB4);
}

void CAN_CTRL_reset(void) {
	PORTB &= ~(1 << PB4); // Select CAN-controller
	
	SPI_write(MCP_RESET); // Send reset-instruksjon
	
	PORTB |= (1 << PB4);
	
	// Etter en reset, MCP2515 trenger litt tid for å initialisere seg.
	//_delay_ms(10);
}
