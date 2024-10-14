/*
 * input_processing.c
 *
 *  Created on: Oct 13, 2024
 *      Author: truon
 */

#include "main.h"
#include "input_reading.h"
#include "global.h"
#include "led_display.h"
#include "timer.h"



enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND};
enum ButtonState buttonState = BUTTON_RELEASED;

void fsm_for_input_processing(void){
	switch (buttonState) {
		case BUTTON_RELEASED:
			if(is_button_pressed(0)){
				buttonState = BUTTON_PRESSED;
				//INCREASE VALUE OF PORT A BY ONE UNIT
			}
			break;
		case BUTTON_PRESSED:
			if(!is_button_pressed(0)){
				buttonState = BUTTON_RELEASED;
			}
			else{
				if(is_button_pressed_1s(0)){
					buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND;

				}
			}
			break;

		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if(!is_button_pressed(0)){
				buttonState = BUTTON_RELEASED;
			}
			//todo
			break;
		default:
			break;
	}
}

enum ledColor {GREEN, AMBER, RED};
enum ledColor cur_color1 = RED;
enum ledColor cur_color2 = GREEN;

int sw_led = 0;
int c_1s = 100;
int counter1 = 5, counter2 = 3;
void fsm_automatic_run(){
	switch (status) {
		case INIT:
			initColor1();
			initColor2();

			setTimer(1,3000);
			status = AUTO_RED_GREEN;
			cur_color1 = RED;
			cur_color2 = GREEN;
			break;
		case AUTO_RED_GREEN:
			setRed1();
			setGreen2();

			if(timer_flag[1] == 1){
				status = AUTO_RED_AMBER;
				setTimer(1,2000);
				cur_color1 = RED;
				cur_color2 = AMBER;
			}
			break;
		case AUTO_RED_AMBER:
			setRed1();
			setAmber2();

			if(timer_flag[1] == 1){
				status = AUTO_GREEN_RED;
				setTimer(1, 3000);
				cur_color1 = GREEN;
				cur_color2 = RED;
			}
			break;
		case AUTO_GREEN_RED:
			setGreen1();
			setRed2();

			if(timer_flag[1] == 1){
				status = AUTO_AMBER_RED;
				setTimer(1, 2000);
				cur_color1 = AMBER;
				cur_color2 = RED;
			}
			break;
		case AUTO_AMBER_RED:
			setAmber1();
			setRed2();

			if(timer_flag[1] == 1){
				status = AUTO_RED_GREEN;
				setTimer(1, 3000);
				cur_color1 = RED;
				cur_color2 = GREEN;
			}

			break;
		default:
			break;
	}

	if(c_1s <= 0){

		if(counter1 <= 0){
			switch (cur_color1) {
				case RED:
					counter1 = 5;
					break;
				case AMBER:
					counter1 = 2;
					break;
				case GREEN:
					counter1 = 3;
					break;
				default:
					break;
			}
		}
		if(counter2 <= 0){
			switch (cur_color2) {
				case RED:
					counter2 = 5;
					break;
				case AMBER:
					counter2 = 2;
					break;
				case GREEN:
					counter2 = 3;
					break;
				default:
					break;
			}
		}
		counter1--;
		counter2--;
		c_1s = 100;
	}

	switch (sw_led) {
		case 0:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
			display7SEG(counter1 / 10);

			if(timer_flag[2] == 1){
				sw_led = 1;
				setTimer(2, 200);
			}
			break;
		case 1:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
			display7SEG(counter1 % 10);

			if(timer_flag[2] == 1){
				sw_led = 2;
				setTimer(2, 200);
			}
			break;
		case 2:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
			display7SEG(counter2 / 10);

			if(timer_flag[2] == 1){
				sw_led = 3;
				setTimer(2, 200);
			}
			break;
		case 3:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
			display7SEG(counter2 % 10);

			if(timer_flag[2] == 1){
				sw_led = 0;
				setTimer(2, 200);
			}
			break;
		default:
			break;
	}
	c_1s--;
}
