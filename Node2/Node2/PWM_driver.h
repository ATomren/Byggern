/*
 * PWM.h
 *
 * Created: 24.10.2023 08:42:17
 *  Author: adriatom
 */ 


#ifndef PWM_driver_H_
#define PWM_driver_H_

#include "sam.h"

#define DC_Value_Min 80
#define DC_Value_Max 165

/*
#define volatile uint32_t PWM_CMR0*(0x40094200)	 // PWM Channel Mode Register (0)
#define volatile uint32_t PWM_CPRD0*(0x4009420C) // PWM Channel Period Register
#define volatile uint32_t PWM_CDTY0*(0x40094204) // PWM Channel Duty Cycle Register 0
*/

#define CPRD 1641 // Period = 20ms = 1680000/84000000
#define ch 5

void PWM_init(void);
void PWM_duty_cycle_update(int CDTYUPD);
void PWM_DC_from_joystick(uint8_t x_percentage);



#endif /* PWM_driver_H_ */