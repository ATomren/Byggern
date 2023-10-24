/*
 * ADC.h
 *
 * Created: 24.10.2023 13:55:01
 *  Author: adriatom
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "sam.h"
#include <stdint.h>
#define ADC_channel 0


void ADC_init(void);

uint16_t ADC_read(void);

#endif 