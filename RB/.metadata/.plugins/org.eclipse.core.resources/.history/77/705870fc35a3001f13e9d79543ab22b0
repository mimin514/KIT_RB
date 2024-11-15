/*
 * led_display.c
 *
 *  Created on: Sep 30, 2024
 *      Author: User
 */
#include "input_reading.h"
#include "main.h"
#include "input_processing.h"
#include "led_display.h"
#include "i2c-lcd.h"
int count=0,cnt=0;

// function blink led
void led_red_blink(){
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)== HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)){
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
	}
	else {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
	}
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)== HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)){
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
		}
		else {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);
		}

}
void led_green_blink(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
}
void led_yellow_blink(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);


	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);
}


// 1: D3 - D4
void on_red1_led(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);

}
void on_yellow1_led(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);

}
void on_green1_led(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
}
 // 2: D9 - D10
void on_red2_led(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);

}
void on_yellow2_led(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1);

}
void on_green2_led(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
}
void off_led1(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
}
void off_led2(){
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0);
}
void modify_red_duration()
{

	led_red_blink();
}
void modify_yellow_duration()
{


	led_yellow_blink();
}
void modify_green_duration()
{

	led_green_blink();
}





int digit_index=0;
const uint16_t digit_pins_1[] = {EN1_Pin, EN3_Pin};
const uint16_t digit_pins_2[] = { EN2_Pin, EN4_Pin};

uint8_t digit1, digit2,digit3,digit4 ;
int mode=1;



void updatemode(int modee){
	mode=modee;
}

int num11,num22;

int cntred = 5, 	cntye = 3, 	cntgr = 5;
int cntred2 = 5, 	cntye2 = 3, cntgr2 = 5;

int red_duration = 5;
int yellow_duration = 3;
int green_duration = 5;

int new_red_duration = 0;
int new_yellow_duration = 0;
int new_green_duration = 0;

void timeledlight(){
	//display2number(num11, num22);
	lcd_goto_XY(1, 0);
	lcd_send_string("hehe");

}
void normalstate(){
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_5 |GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7 , GPIO_PIN_RESET);

	if (cntred >= 0) {
		num11=cntred--;

		on_red2_led();
	}
	else if (cntgr >= 0)  	{

		on_green2_led();

		num11=cntgr--;
	}
	else if (cntye >= 0) 	{
		num11=cntye--;

		on_yellow2_led();
	}

	if (cntgr2 >= 0)  	{
		num22=cntgr2--;

		on_green1_led();

	}
	else if (cntye2 >= 0) 	{
		num22=cntye2--;

		on_yellow1_led();
	}
	else if (cntred2 >= 0) 	{
		num22=cntred2--;

		on_red1_led();
	}

	if (cntred2 < 0 && cntgr2 < 0 && cntye2 < 0) {
		cntred2 = red_duration;
		cntgr2 = green_duration ;
		cntye2 = yellow_duration;
	}

	if (cntred < 0 && cntgr < 0 && cntye < 0) {
		cntred = red_duration;
		cntgr = green_duration ;
		cntye = yellow_duration;
	}
}

void update_numbers(int duration) {
    num11 = duration;
    num22 = duration;
}
void increment_duration(int *new_duration) {
    *new_duration += 1;
    if (*new_duration > 10) {
        *new_duration = 1;
    }
    num11 = *new_duration;
    num22 = *new_duration;
}

void save_duration(int *new_duration, int *active_duration) {
    if (*new_duration > 0) {
        *active_duration = *new_duration;
        *new_duration = 0;
        update_numbers(*active_duration);
    }
}
// Button 2
void but2_red(){ increment_duration(&new_red_duration);}
void but2_ye() { increment_duration(&new_yellow_duration);}
void but2_gr() { increment_duration(&new_green_duration);}

// Button 3
void but3_red(){save_duration(&new_red_duration,  	&red_duration);}
void but3_ye() {save_duration(&new_yellow_duration, &yellow_duration);}
void but3_gr() {save_duration(&new_green_duration, 	&green_duration);}



