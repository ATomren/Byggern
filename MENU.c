/*
 * MENU.c
 *
 * Created: 26.09.2023 15:21:23
 *  Author: adriatom
 */ 

#include "MENU.h"


void MENU_vertical_navigator(enum CursorState* cursor_state, int* current_line){
	enum pos_t currentJoystickState = ADC_pos_read(ADC_scale_X(ADC_read(1)), ADC_scale_Y(ADC_read(0))); //returns enum joystick position
	if (*cursor_state == CAN_MOVE){
		switch(currentJoystickState){
			case UP:
				if(*current_line >2){
					oled_clear_line(*current_line);
					*current_line=*current_line-1;
					oled_pos(*current_line, 0);
					*cursor_state = HAS_MOVED;
					oled_print('>');
				}break;
			case DOWN:
				if(*current_line <7){
					oled_clear_line(*current_line);
					*current_line = *current_line+1;
					oled_pos(*current_line,0);
					*cursor_state = HAS_MOVED;
					oled_print('>');
					
				}break;
		}
	}else if(currentJoystickState == NEUTRAL){
		*cursor_state = CAN_MOVE;
	}
}

void MENU_print(void){
// 	oled_pos(0, 40);
// 	oled_print_str(menu->title);
// 	switch(menu->currentLine){
// 		case 3:
// 			oled_clear_line(menu->currentLine);
// 			oled_pos(menu->currentLine, 9);
// 			oled_print_str(menu->line3);
// 			oled_pos(menu->currentLine, 0);
// 			oled_print_str()
// 			break;
// 		case 4:
// 			oled_pos(menu->currentLine, 3);
// 			oled_print_str(menu->line3);
// 	}
//	for (int i = 0; i < 8; i++){
//		oled_pos(i, 9);
//		oled_print_str(lineStrings[i]);
//	}
	oled_pos(0,40);
	oled_print_str("PING PONG");
	
	oled_pos(2,10);
	oled_print_str("New Game");
	
	oled_pos(3,10);
	oled_print_str("Load Game");
	
	oled_pos(4,10);
	oled_print_str("Settings");
	
	oled_pos(5,10);
	oled_print_str("Scoreboard");
	
	oled_pos(6,10);
	oled_print_str("Quit Game");
	
// 	for løkke
// 		clear linje
// 		if line = current line: print pil
// 		print tekste for current pil
// 		
	
	
}


void menu_click(){
	if(PB2 er lav){
		print(current line)
	}
}