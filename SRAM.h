/*
 * IncFile1.h
 *
 * Created: 12.09.2023 14:02:58
 *  Author: adriatom
 */ 
#define F_CPU 4915200UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#ifndef SRAM_H_
#define SRAM_H_

void SRAM_init(void);
void SRAM_test(void);


#endif /* INCFILE1_H_ */