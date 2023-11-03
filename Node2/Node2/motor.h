/*
 * motor.h
 *
 * Created: 03.11.2023 14:35:52
 *  Author: adriatom
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdio.h>
#include "sam.h"
#include "timer.h"

#define NOT_OE PIO_PD0
#define NOT_RST PIO_PD1
#define SEL PIO_PD2
#define EN PIO_PD9
#define DIR PIO_PD10
#define DO0 PIO_PC1
#define DO1 PIO_PC2
#define DO2 PIO_PC3
#define DO3 PIO_PC4
#define DO4 PIO_PC5
#define DO5 PIO_PC6
#define DO6 PIO_PC7
#define DO7 PIO_PC8



void MOTOR_init(void);

void MOTOR_read_encoder(void);






#endif /* MOTOR_H_ */