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




int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS;	//Disables watchdog-timer
	configure_uart();
	
	can_init_def_tx_rx_mb(CAN_BR_values);
	
	//PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK;
	//PMC->PMC_PCER0 = PMC_PCER0_PID11;
	
	PIOA->PIO_PER = (1 << 19)|(1 << 20);
	PIOA->PIO_OER = (1 << 19)|(1 << 20);
	
	PIOA->PIO_SODR = (1 << 19)|(1 << 20);
	
    /* Replace with your application code */
	CAN_MESSAGE test_msg;
	//test_msg.id = 22;
	//test_msg.data_length = 8;
	//test_msg.data[8];

	
	while (1) {
	
	can_receive(&test_msg, 0);
	if (test_msg.id == '$'){ //lesing av posisjon over CAN
		printf("Message Data0: %x\r\n", test_msg.data[0]);
	}else{
		printf("Funkar inte");
		}
	/*
	printf("Message ID: %c\r\n", test_msg.id);
	printf("Message Data Length: %c\r\n", test_msg.data_length);
	
	printf("Message Data1: %x\r\n", test_msg.data[1]);
	printf("Message Data2: %x\r\n", test_msg.data[2]);
	printf("Message Data3: %x\r\n", test_msg.data[3]);
	printf("Message Data4: %x\r\n", test_msg.data[4]);
	printf("Message Data5: %x\r\n", test_msg.data[5]);
	printf("Message Data6: %x\r\n", test_msg.data[6]);
	printf("Message Data7: %x\r\n", test_msg.data[7]);*/
	
	printf("------------------%c\r\n", ' ');
		
		
		//_delay_ms(1000);

    }
}