/*
 * OLED.h
 *
 * Created: 26.09.2023 09:30:50
 *  Author: larslaun
 */ 


#ifndef OLED_H_
#define OLED_H_
#include <avr/io.h>
#include <avr/pgmspace.h>




void oled_init();
void oled_reset();
void oled_home();
void oled_goto_line(int line);
void oled_goto_column(int column);
void oled_clear_line(int line);void oled_pos(int row, int column);void oled_print(char c);void oled_print_str(char str[]);void oled_print_line(int line);
void oled_write_command(uint8_t write);
void oled_write_data(uint8_t data);




#endif /* OLED_H_ */