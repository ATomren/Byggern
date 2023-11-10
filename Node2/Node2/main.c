/*
 * Node2.c
 *
 * Created: 10.10.2023 14:02:24
 * Author : adriatom
 */ 

#include "sam.h"
#include "can_controller.h"
#include "uart.h"
#include "printf_stdarg.h"
#include "ADC.h"
#include "PWM_driver.h"
#include "DAC.h"
#include "motor.h"
#include "Utilities.h"
#include "POS_CTRL.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>


//Global variables
volatile CAN_MESSAGE msg;
volatile uint16_t motor_speed_PI;

int main(void){
    /* Initialize the SAM system */
	SystemInit();
		
	//Disables watchdog-timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Other Inits
	configure_uart();
	can_init_def_tx_rx_mb(CAN_BR_values);
	ADC_init();
	PWM_init();
	DAC_Init();
	MOTOR_init();
	Utilities_init();
	POS_CTRL_timer_interrupt_init();
	
	int game_lives = 10;
	int score_flags = 0;
	
	while (1) {
		// Receive control-signals from Node 1
		can_receive(&msg, 0);
		
		// Test-prints
			//printf("Left button: %u , Right button: %u \r\n", msg.data[2], msg.data[3]);
			//printf("Joystick_X: %u \t Joystick Y: %u \t Slider: %u \t Button A: %u \t Button B: %u \r\n", msg.data[0], msg.data[4], msg.data[1], msg.data[2], msg.data[3]);
		
		PWM_DC_from_joystick(msg.data[0]);		// Control Servo with joystick
		
		Utilities_activate_solenoide(msg.data[2]);	// Activate solenoide
		
		DAC_Control_Motor_Speed(motor_speed_PI);	// Update motor-speed
		
		// Run Game-logic and print status
		Game_Score_Keeper(&game_lives, &score_flags);	
		printf("Game Lives: %d \r\n", game_lives);	
    }
}

void TC0_Handler(void){

	// Read the status register to clear the interrupt flag
	uint32_t status;
	status = TC0->TC_CHANNEL[TC_ch].TC_SR;
	
	// Init static variables
	static uint16_t integral_value = 0;
	
	// Compute values
	uint16_t setpoint = msg.data[1] * 14;					// Right Slider-value	// 14 to scale setpoint to encoder-interval
	uint16_t process_value = MOTOR_read_encoder();			// Process-value is read from Encoder
	if(process_value > 50000){
		process_value = 0;
	}
	
	//int error = setpoint - process_value;					// Error
	
	uint16_t abs_error = abs(setpoint - process_value) ;	// Absolute value of error
	
	uint16_t proportional_value = Kp * abs_error;
	
 	if (abs_error > 50){
 		 integral_value = integral_value + (Ki * abs_error * T);
		 motor_speed_PI = (uint16_t)((proportional_value) + integral_value);
		 if (motor_speed_PI >= 4095){
			 motor_speed_PI = 4095;	 
		 }else if (motor_speed_PI < 1300){
			 motor_speed_PI = 1300;
		}	
		
		// Update the direction of the servo, depending on the error-sign
		if (setpoint > process_value){
			PIOD->PIO_CODR = DIR;	// DIR = 1
		}else{
			PIOD->PIO_SODR = DIR;	// DIR = 0
		}
		
	// If motor within deadzone, reset integral_value and set low (no) motorspeed
	}else{
		integral_value = 0;	
		motor_speed_PI = 1000;
	}
	
	//printf("ENCODER: %u \t SETPOINT: %u \t Abs-Error: %u \t INTEGRAL: %u \t\t MOTOR-SPEED: %u \r\n", process_value, setpoint, abs_error, integral_value, motor_speed_PI);
}

