/*
 * DAC.h
 *
 * Created: 03.11.2023 09:21:53
 *  Author: adriatom
 */ 


#ifndef DAC_H_
#define DAC_H_

#include "sam.h"
#include <stdio.h>

//#define  DACC_P_ID = 38

void DAC_Init(void);
void DAC_Control_Motor_Speed(uint16_t input);
void DAC_Joystick_To_Motor_Speed(uint8_t js_percentage, uint16_t* current_speed);





#endif /* DAC_H_ */