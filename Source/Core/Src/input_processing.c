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

void fsm_automatic_run(){
	switch (status) {
		case INIT:
			initColor1();
			initColor2();

			setTimer(1,3000);
			status = AUTO_RED_GREEN;
			break;
		case AUTO_RED_GREEN:
			setRed1();
			setGreen2();

			if(timer_flag[1] == 1){
				status = AUTO_RED_AMBER;
				setTimer(1,2000);
			}
			break;
		case AUTO_RED_AMBER:
			setRed1();
			setAmber2();

			if(timer_flag[1] == 1){
				status = AUTO_GREEN_RED;
				setTimer(1, 3000);
			}
			break;
		case AUTO_GREEN_RED:
			setGreen1();
			setRed2();

			if(timer_flag[1] == 1){
				status = AUTO_AMBER_RED;
				setTimer(1, 2000);
			}
			break;
		case AUTO_AMBER_RED:
			setAmber1();
			setRed2();

			if(timer_flag[1] == 1){
				status = AUTO_RED_GREEN;
				setTimer(1, 3000);
			}

			break;
		default:
			break;
	}
}
