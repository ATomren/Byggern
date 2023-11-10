/*
 * POS_CTRL.h
 *
 * Created: 03.11.2023 12:47:35
 *  Author: adriatom
 */ 


#ifndef POS_CTRL_H_
#define POS_CTRL_H_

#include "sam.h"
#include "motor.h"
#include "can_controller.h"
#include <stdio.h>

//Global variables for timer
#define TC_ch 0 
#define MCK 84000000
#define TC0_frequency 6
#define TC_RC_value MCK/(2*TC0_frequency)



// Global variables for PI-Controller
#define Kp 2
#define Ki 1.5
#define T 1.0/TC0_frequency

// Functions
void POS_CTRL_timer_interrupt_init(void);
//void TC0_Handler(void);

#endif /* POS_CTRL_H_ */