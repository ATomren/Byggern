/*
 * SPI_com.h
 *
 * Created: 03.10.2023 08:13:52
 *  Author: adriatom
 */ 


#ifndef SPI_COM_H_
#define SPI_COM_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

void SPI_MasterInit(void);
void SPI_write(char cData);
uint8_t SPI_read(void);

#endif /* SPI_COM_H_ */