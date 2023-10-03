/*
 * SPI_com.c
 *
 * Created: 03.10.2023 08:13:26
 *  Author: adriatom
 */ 

#include "SPI_com.h"


void SPI_MasterInit(void)
{
	/* Set SS, MOSI and SCK output, all others input */
	DDRB = (1<<PB5)|(1<<PB7)|(1<<PB4);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	//|(1<<SPIE)
}

void SPI_write(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}

uint8_t SPI_read(void){
	//send a dummy byte from master, to push slave-data to master
	SPI_write('*');
	
	return SPDR;
}