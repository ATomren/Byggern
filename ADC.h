/*
 * ADC.h
 *
 * Created: 19.09.2023 09:43:50
 *  Author: adriatom
 */ 

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART.h"

enum pos_t {UP, DOWN, NEUTRAL, LEFT, RIGHT};

void ADC_init(void);
uint8_t ADC_read(uint8_t channel); //has to be volatile
int ADC_scale_X(uint8_t x_axis);
int ADC_scale_Y(uint8_t y_axis);
int ADC_scale_slider(uint8_t slider);

enum pos_t ADC_pos_read(int x_percentage, int y_percentage);

void print_direction(enum pos_t);



#endif /* ADC_H_ */