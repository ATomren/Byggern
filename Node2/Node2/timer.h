/*
 * timer.h
 *
 * Created: 24.10.2023 08:39:18
 *  Author: adriatom
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

#include "sam.h"

static void SysTick_init(int us);
void _delay_us(uint16_t us);
void _delay_ms(uint16_t ms);

#endif /* TIMER_H_ */