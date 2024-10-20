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
#include "input_processing.h"



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


int counter1[3];
int counter2[3];

enum Color cur_color1 = RED;
enum Color cur_color2 = GREEN;

int cnt = 0;
int sw_led = 0;

void fsm_automatic_run(){
	if(timer_flag[1] == 1){
		switch (status) {
			case INIT:
				initColor1();
				initColor2();

				cnt = 3;
				status = AUTO_RED_GREEN;
				cur_color1 = RED;
				cur_color2 = GREEN;

				break;
			case AUTO_RED_GREEN:
				setRed1();
				setGreen2();

				cnt--;
				counter1[cur_color1]--;
				counter2[cur_color2]--;

				if(counter1[RED] < 0) counter1[RED] = 5;
				if(counter1[GREEN] < 0) counter1[GREEN] = 3;
				if(counter1[AMBER] < 0) counter1[AMBER] = 2;

				if(counter2[RED] < 0) counter2[RED] = 5;
				if(counter2[GREEN] < 0) counter2[GREEN] = 3;
				if(counter2[AMBER] < 0) counter2[AMBER] = 2;
				if(cnt <= 0){
					cnt = 2;
					status = AUTO_RED_AMBER;
					cur_color1 = RED;
					cur_color2 = AMBER;
				}
				break;
			case AUTO_RED_AMBER:
				setRed1();
				setAmber2();

				cnt--;
				counter1[cur_color1]--;
				counter2[cur_color2]--;

				if(counter1[RED] < 0) counter1[RED] = 5;
				if(counter1[GREEN] < 0) counter1[GREEN] = 3;
				if(counter1[AMBER] < 0) counter1[AMBER] = 2;

				if(counter2[RED] < 0) counter2[RED] = 5;
				if(counter2[GREEN] < 0) counter2[GREEN] = 3;
				if(counter2[AMBER] < 0) counter2[AMBER] = 2;
				if(cnt <= 0){
					cnt = 3;
					status = AUTO_GREEN_RED;
					cur_color1 = GREEN;
					cur_color2 = RED;
				}
				break;
			case AUTO_GREEN_RED:
				setGreen1();
				setRed2();

				cnt--;
				counter1[cur_color1]--;
				counter2[cur_color2]--;

				if(counter1[RED] < 0) counter1[RED] = 5;
				if(counter1[GREEN] < 0) counter1[GREEN] = 3;
				if(counter1[AMBER] < 0) counter1[AMBER] = 2;

				if(counter2[RED] < 0) counter2[RED] = 5;
				if(counter2[GREEN] < 0) counter2[GREEN] = 3;
				if(counter2[AMBER] < 0) counter2[AMBER] = 2;
				if(cnt <= 0){
					status = AUTO_AMBER_RED;
					cnt = 2;
					cur_color1 = AMBER;
					cur_color2 = RED;
				}
				break;
			case AUTO_AMBER_RED:
				setAmber1();
				setRed2();

				cnt--;
				counter1[cur_color1]--;
				counter2[cur_color2]--;

				if(counter1[RED] < 0) counter1[RED] = 5;
				if(counter1[GREEN] < 0) counter1[GREEN] = 3;
				if(counter1[AMBER] < 0) counter1[AMBER] = 2;

				if(counter2[RED] < 0) counter2[RED] = 5;
				if(counter2[GREEN] < 0) counter2[GREEN] = 3;
				if(counter2[AMBER] < 0) counter2[AMBER] = 2;
				if(cnt <= 0){
					status = AUTO_RED_GREEN;
					cnt = 3;
					cur_color1 = RED;
					cur_color2 = GREEN;
				}

				break;
			default:
				break;
		}
		setTimer(1, 1000);
	}


	switch (sw_led) {
		case 0:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
			display7SEG(counter1[cur_color1] / 10);

			if(timer_flag[2] == 1){
				sw_led = 1;
				setTimer(2, 100);
			}
			break;
		case 1:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
			display7SEG(counter1[cur_color1] % 10);

			if(timer_flag[2] == 1){
				sw_led = 2;
				setTimer(2, 100);
			}
			break;
		case 2:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
			display7SEG(counter2[cur_color2] / 10);

			if(timer_flag[2] == 1){
				sw_led = 3;
				setTimer(2, 100);
			}
			break;
		case 3:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
			display7SEG(counter2[cur_color2] % 10);

			if(timer_flag[2] == 1){
				sw_led = 0;
				setTimer(2, 100);
			}
			break;
		default:
			break;
	}

//	if(timer_flag[3] == 1){
//		counter1[cur_color1]--;
//		counter2[cur_color2]--;
//
//		if(counter1[RED] <= 0) counter1[RED] = 6;
//		if(counter1[GREEN] <= 0) counter1[GREEN] = 4;
//		if(counter1[AMBER] <= 0) counter1[AMBER] = 3;
//
//		if(counter2[RED] <= 0) counter2[RED] = 6;
//		if(counter2[GREEN] <= 0) counter2[GREEN] = 4;
//		if(counter2[AMBER] <= 0) counter2[AMBER] = 3;
//
//		setTimer(3, 1000);
//	}

}
