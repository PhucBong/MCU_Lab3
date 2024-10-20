/*
 * input_processing.c
 *
 *  Created on: Oct 13, 2024
 *      Author: truon
 */


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

void fsm_automatic_run(){
	if(timer_flag[2] == 1){
		ledScanning();
		setTimer(2, 10);
	}
	ledDispMode();
}


