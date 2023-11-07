/*
 * Node2.c
 *
 * Created: 10.10.2023 14:02:24
 * Author : adriatom
 */ 

#include "sam.h"
#include "can_controller.h"
#include "uart.h"
#include <stdio.h>
#include "printf_stdarg.h"
#include "ADC.h"
#include "PWM_driver.h"
#include "DAC.h"
#include "motor.h"
#include "Utilities.h"
#include "POS_CTRL.h"
#include <stdlib.h>



int main(void)
{
    /* Initialize the SAM system */
	SystemInit();
	// Inits
    
	WDT->WDT_MR = WDT_MR_WDDIS;	//Disables watchdog-timer
	configure_uart();
	can_init_def_tx_rx_mb(CAN_BR_values);
	ADC_init();
	PWM_init();
	DAC_Init();
	MOTOR_init();
	Utilities_init();
	POS_CTRL_timer_interrupt_init();
	
	//Global variables
	uint16_t motor_speed = 1500; //1500 -> 4095
		
	CAN_MESSAGE msg;
	
	//int game_lives = 10;
	//int score_flags = 0;
	
	while (1) {
		// Might need to disable INTERRUPT	
		can_receive(&msg, 0);
		// Might need to enable INTERRUPT

		PWM_DC_from_joystick(msg.data[0]);
		//printf("Joystick_X: %u \t Joystick Y: %u \t Slider: %u \t Button A: %u \t Button B: %u \r\n", msg.data[0], msg.data[4], msg.data[1], msg.data[2], msg.data[3]);
		//DAC_Control_Motor_Speed(1500);
		//DAC_Joystick_To_Motor_Speed(msg.data[4], &motor_speed);
		MOTOR_read_encoder();
		Utilities_activate_solenoide(&msg);
	
		//printf("counter value: %u \t RC-value: &u \r\n", TC0->TC_CHANNEL[0].TC_CV, TC_RC_value);
		
		// 		for(int i = 0; i < 1000000000; ++i){	
		// 		}
		//Game_Score_Keeper(&game_lives, &score_flags);
		//printf("Game Lives: %d \r\n", game_lives);	
    }
}


void TC0_Handler(void){
	// I/O lines på side 858 TCLK0=PB26=Peripheral B
	//printf("INTERRUPT HAS BEEN CALLED!!!!! %c \r\n", ' ');
	// Read the status register to clear the interrupt flag
	uint32_t status;
	status = TC0->TC_CHANNEL[TC_ch].TC_SR;
	
	// Init static variables
	static uint16_t integral_value = 0;
	
	
	// Code for what the interrupt-handler should do. Compute DAC-value by the PI-controller
	CAN_MESSAGE msg;
	can_receive(&msg, 0);
	
	uint16_t setpoint = msg.data[1] * 14;	// Right Slider-value
	uint16_t process_value = MOTOR_read_encoder();
	int error = setpoint - process_value;
	uint16_t abs_error = abs(setpoint - process_value) ;
	
	if (error != 0){
	integral_value = integral_value + (Ki * abs_error * T);
	}
	else if (error == 0){
		integral_value = 0;
	}
	printf("ProcessValue: %u \r\n", process_value);
	printf("Error: %u \t IntegralValue: %u \r\n", error, integral_value);
	
	// Update the direction of the servo, depending on the error-sign
	if (error >= 0){
		PIOD->PIO_CODR = DIR;	// DIR = 1
		}else{
		PIOD->PIO_SODR = DIR;	// DIR = 0
	}
	
	uint16_t motor_speed_PI = (uint16_t)((Kp * error) + integral_value);
	if (motor_speed_PI >= 4095){
		motor_speed_PI = 4095;
	}
	printf("MOTOR-SPEED: %u \r\n", motor_speed_PI);
	//DAC_Control_Motor_Speed(motor_speed_PI);	// Update motor-speed with	
}

