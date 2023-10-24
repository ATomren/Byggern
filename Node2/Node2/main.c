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



int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS;	//Disables watchdog-timer
	configure_uart();
	
	can_init_def_tx_rx_mb(CAN_BR_values);
	ADC_init();
	PWM_init();
	
	//PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK;
	//PMC->PMC_PCER0 = PMC_PCER0_PID11;
	
	PIOA->PIO_PER = (1 << 19)|(1 << 20);
	PIOA->PIO_OER = (1 << 19)|(1 << 20);
	
	PIOA->PIO_SODR = (1 << 19)|(1 << 20);
	
    /* Replace with your application code */
	CAN_MESSAGE test_msg;
	
	
	int game_lives = 10;
	int score_flags = 0;
	
	
	
	
	while (1) {
	
	can_receive(&test_msg, 0);
	if (test_msg.id == '$'){ //lesing av posisjon over CAN
		//printf("Message Data0: %x\r\n", test_msg.data[0]);
	}else{
		printf("Funkar inte %c\r\n",' ');
		}

	PWM_DC_from_joystick(test_msg.data[0]);
	
	Game_Score_Keeper(&game_lives, &score_flags);
	printf("Game Lives: %d \r\n", game_lives);
	
	
	
	printf("ADC VALUE: %u\r\n", ADC_read());
	
	printf("------------------%c\r\n", ' ');
		
		
		//_delay_ms(1000);

    }
}