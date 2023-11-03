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


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS;	//Disables watchdog-timer
	configure_uart();
	
	can_init_def_tx_rx_mb(CAN_BR_values);
	ADC_init();
	PWM_init();
	DAC_Init();
	MOTOR_init();
	
	PIOA->PIO_PER = (1 << 19)|(1 << 20);
	PIOA->PIO_OER = (1 << 19)|(1 << 20);
	PIOA->PIO_SODR = (1 << 19)|(1 << 20);
	
    /* Replace with your application code */
	CAN_MESSAGE msg;
	
	//int game_lives = 10;
	//int score_flags = 0;
	

	while (1) {
	
		can_receive(&msg, 0);

		PWM_DC_from_joystick(msg.data[0]);
		printf("Slider: %u \r\n", msg.data[1]);
		printf("Button A: %u	\t Button B: %u \r\n", msg.data[2], msg.data[3]);
	
		DAC_Control_Motor_Speed(500);
		MOTOR_read_encoder();
		printf("------------------------------------%c\r\n", ' ');
	
		//Game_Score_Keeper(&game_lives, &score_flags);
		//printf("Game Lives: %d \r\n", game_lives);
	
		//_delay_ms(1000);
		//printf("ADC VALUE: %u\r\n", ADC_read());
	

    }
}