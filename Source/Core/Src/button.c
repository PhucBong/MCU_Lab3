/*
 * button.c
 *
 *  Created on: Oct 13, 2024
 *      Author: truon
 */

#include "button.h"

int button1_flag = 0;

int keyReg0 = NORMAL_STATE;
int keyReg1 = NORMAL_STATE;
int keyReg2 = NORMAL_STATE;

int keyReg3 = NORMAL_STATE;
int timerForKeyPress = 200;

int isButton1Pressed(){
	if(button1_flag == 1){
		button1_flag = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(){
	button1_flag = 1;
}

void getKeyInput(){
	keyReg0 = keyReg1;
	keyReg1 = keyReg2;
	keyReg2 = HAL_GPIO_ReadPin(Button1_GPIO_Port, Button1_Pin);
	if((keyReg0 == keyReg1) && (keyReg1 == keyReg2)){
		if(keyReg3 != keyReg2){
			keyReg3 = keyReg2;
			if(keyReg2 == PRESSED_STATE){
				subKeyProcess();
				timerForKeyPress = 200;
			}
		}
		else{ // dang nhan de
			timerForKeyPress--;
			if(timerForKeyPress == 0){
				keyReg3 = NORMAL_STATE;
			}
		}
	}
}
