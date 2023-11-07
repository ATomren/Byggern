/*
 * POS_CTRL.c
 *
 * Created: 03.11.2023 12:47:48
 *  Author: adriatom
 */ 

#include "POS_CTRL.h"



/************************************************************************/
/* l I/O signals TIOA0, TIOA1 or TIOA2          for chaining by programming the TC
Block Mode Register (TC_BMR)                                                            */
/************************************************************************/


void POS_CTRL_timer_interrupt_init(){
	
	// Enable clock for TC0
	PMC->PMC_PCER0 |= PMC_PCER0_PID27;		// Peripheral Clock Enable 0, ID 27
	PMC->PMC_PCR = (PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_TC0 << PMC_PCR_PID_Pos));

	// Write Protection Off
	//TC0->TC_WPMR = 0x54494D00;
	
	// Disable clock to configure it before it starts
	TC0->TC_CHANNEL[TC_ch].TC_CCR = TC_CCR_CLKDIS;	// Disable clock for TC0 to configure it

	// TC Channel Mode Register
	//TC0->TC_CHANNEL[TC_ch].TC_CMR = (TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_WAVSEL_UP_RC | TC_CMR_WAVE | TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET); //Prescaler MCK/2, Waveform and automatic trigger on RC Compare
	TC0->TC_CHANNEL[TC_ch].TC_CMR = (TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_WAVSEL_UP_RC | TC_CMR_WAVE); //Prescaler MCK/2, Waveform and automatic trigger on RC Compare
	//TC0->TC_CHANNEL[TC_ch].TC_CMR = (TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_CPCTRG);
	
	// TC Register Compare ("time-step")
	TC0->TC_CHANNEL[TC_ch].TC_RC = TC_RC_value; // RC is the register used for Register Compare. When the timer reaches this value, it generates an interrupt and resets the counter
	
	// Enable Interrupt for RC
	TC0->TC_CHANNEL[TC_ch].TC_IER = TC_IER_CPCS;
	
	// Enable NVIC interrupt
	NVIC_EnableIRQ(ID_TC0);
	
	// Enable the counter clock. Reset the counter and start the clock
	TC0->TC_CHANNEL[TC_ch].TC_CCR = (TC_CCR_CLKEN | TC_CCR_SWTRG);	
	

	NVIC_SetPriority(TC0_IRQn, 2);
	
	printf("Interrupt Init completed, %c", ' ');
}


