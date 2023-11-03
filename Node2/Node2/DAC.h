/*
 * DAC.h
 *
 * Created: 03.11.2023 09:21:53
 *  Author: adriatom
 */ 


#ifndef DAC_H_
#define DAC_H_

#include "sam.h"

//#define  DACC_P_ID = 38

void DAC_Init(void);
void DAC_Control_Motor_Speed(uint16_t input);




#endif /* DAC_H_ */