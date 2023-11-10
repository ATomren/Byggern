/*
 * game.c
 *
 * Created: 24.10.2023 19:16:06
 *  Author: adriatom
 */ 

#include "game.h"


void Game_Score_Keeper(int* game_score, int* score_flag){
	//printf("VAUE: %u\r\n", ADC_read());
	if(*score_flag == 0){
		if(ADC_read() < GOAL_TRESHOLD){
			*game_score -= 1;
			*score_flag = 1;
		}
	}
	if(ADC_read()>GOAL_TRESHOLD + 500){
		*score_flag = 0;
	}
}

