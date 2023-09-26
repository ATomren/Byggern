/*
 * OLED.c
 *
 * Created: 26.09.2023 09:31:04
 *  Author: larslaun
 */ 

#include "OLED.h"
#include "fonts.h"

#define COMMAND_ADDRESS 0x1000
#define DATA_ADDRESS 0x1200


volatile char* oled_command = COMMAND_ADDRESS;
volatile char* oled_data = DATA_ADDRESS;

void oled_init(){
	oled_write_command(0xae); // display off
	oled_write_command(0xa1); //segment remap
	oled_write_command(0xda); //common pads hardware: alternative
	oled_write_command(0x12);
	oled_write_command(0xc8); //common output scan direction:com63~com0
	oled_write_command(0xa8); //multiplex ration mode:63
	oled_write_command(0x3f);
	oled_write_command(0xd5); //display divide ratio/osc. freq. mode
	oled_write_command(0x80);
	oled_write_command(0x81); //contrast control
	oled_write_command(0x50);
	oled_write_command(0xd9); //set pre-charge period
	oled_write_command(0x21);
	oled_write_command(0x20); //Set Memory Addressing Mode
	oled_write_command(0x02); //Setter til page addressering
	oled_write_command(0xdb); //VCOM deselect level mode
	oled_write_command(0x30);
	oled_write_command(0xad); //master configuration
	oled_write_command(0x00);
	oled_write_command(0xa4); //out follows RAM content
	oled_write_command(0xa6); //set normal display
	oled_write_command(0xaf); // display on
	
	//oled_write_command(0xb0); //set page start to page 0
	
}

void oled_write_command(uint8_t command){
	oled_command[0] = command;
}

void oled_write_data(uint8_t data){
	oled_data[0] = data;
}

void oled_reset(){
	oled_pos(0,0);
	for (int line = 0; line<8; line++){
		oled_clear_line(line); 
	}
	oled_pos(0,0);
}

void oled_home(){
	oled_pos(0,0);
}


void oled_goto_line(int line){
	if (line<8 && line>=0){
		int line_com = 0xB0 + line;
		oled_write_command(line_com);
	}
}


void oled_goto_column(int column){
	oled_write_command(0x00 + (column%16));
	oled_write_command(0x10 + (column/16));	
}
void oled_pos(int row, int column){	oled_goto_line(row);	oled_goto_column(column);}void oled_clear_line(int line){	oled_pos(line, 0);	for (int i = 0; i<128; i++){		oled_write_data(0x0);	}}void oled_print(char c){	for (int col = 0; col<8; col++){		uint8_t byte = pgm_read_byte(&(font8[c-32][col]));		oled_write_data(byte);	}}void oled_print_str(char str[]){	int cnt = 0;	for (cnt = 0; str[cnt] != '\0'; cnt++);		for (int c = 0; c < cnt; c++){		oled_print(str[c]);	}}void oled_print_line(int line){	oled_pos(line, 0);	for (int i = 0; i<128; i++){		oled_write_data(0xFF);	}}