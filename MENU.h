/*
 * MENU.h
 *
 * Created: 26.09.2023 15:21:10
 *  Author: adriatom
 */ 


#ifndef MENU_H_
#define MENU_H_

#include "OLED.h"
#include "ADC.h"

enum CursorState {
	CAN_MOVE,
	HAS_MOVED
};

//char lineStrings[8][128] = {"EPIC PING PONG GAME - Lars", "Start New Game", "Load Game", "Settings", "Scoreboard", "Change Skin", "RageQuit" };

// struct Menu{
// 	char title[] = "EPIC PING PONG GAME - Lars"
// 	char line1[] = "";
// 	char line2[] = "Start New Game";
// 	char line3[] = "Load Game";
// 	char line4[] = "Settings";
// 	char line5[] = "Scoreboard";
// 	char line6[] = "Change Skin";
// 	char line7[] = "RageQuit";
// 	int currentLine;
// 	enum CursorState;
// 	};

void MENU_init(void);

void MENU_vertical_navigator(enum CursorState* cursor_state, int* current_line);
void MENU_print(void);

void menu_click();



#endif /* MENU_H_ */