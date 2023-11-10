/*
 * PWM.c
 *
 * Created: 24.10.2023 08:42:28
 *  Author: adriatom
 */ 

#include "PWM_driver.h"


void PWM_init(void){
	PWM->PWM_WPCR = 0x50574D00;				// Assures no write protection for PWM.
	PWM->PWM_ENA = PWM_ENA_CHID5;		// Enable PWM channel 5.
	
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;	// Peripheral Clock Enable, 1
	PIOC->PIO_PDR |= PIO_PDR_P19;		// Disable Register, to use peripheral
	PIOC->PIO_ABSR |= PIO_ABSR_P19;		// Peripheral Select, B
	
	PMC->PMC_PCR = PMC_PCR_EN;	
	// PWM Clock Register
	PWM->PWM_CLK |= PWM_CLK_DIVA(1);	// No dividing	
	PWM->PWM_CLK |= PWM_CLK_PREA(0);	// CLK = MCK
	
	PWM->PWM_CH_NUM[CH].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_1024 | PWM_CMR_CPOL; // Divide MCK by 1024,  CPOL starts high level
	PWM->PWM_CH_NUM[CH].PWM_CPRD = CPRD; // sets period to 20ms

	
	PWM_duty_cycle_update(122); //start servo in the middle
}

void PWM_duty_cycle_update(int CDTYUPD){ //Set CDTYUPD as duty cycle and assures values in safe interval
	if (CDTYUPD < (DC_Value_Min)){
		PWM->PWM_CH_NUM[CH].PWM_CDTY = DC_Value_Min;
	}else if(CDTYUPD > DC_Value_Max){
		PWM->PWM_CH_NUM[CH].PWM_CDTY = DC_Value_Max;
	}else{
		PWM->PWM_CH_NUM[CH].PWM_CDTY = CDTYUPD;
	}
}

void PWM_DC_from_joystick(uint8_t x_percentage){ //connect joystick to pwm 
	
	int CDTYUPD = (DC_Value_Min + ((x_percentage)*(DC_Value_Max-DC_Value_Min))/100);
	//printf("CDTYUPD: %u \t X-perc: %u \r\n", CDTYUPD, x_percentage);
	uint8_t scaled_CDTYUPD = 245 - CDTYUPD; //mirror direction
	if ((scaled_CDTYUPD > 132) || (scaled_CDTYUPD<112)){  //Set deadzone for servo
	PWM_duty_cycle_update(scaled_CDTYUPD);
	} else{
		PWM_duty_cycle_update(122);
	}
}