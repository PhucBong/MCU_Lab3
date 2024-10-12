/*
 * fsm_automatic.c
 *
 *  Created on: Oct 13, 2024
 *      Author: truon
 */

#include "fsm_automatic.h"

void fsm_automatic_run(){
	switch (status) {
		case INIT:
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, SET);
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, SET);

			status = AUTO_RED;
			setTimer(1, 5000);
			break;
		case AUTO_RED:
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, RESET);
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, SET);
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, SET);

			if(timer_flag[1] == 1){
				status = AUTO_GREEN;
				setTimer(1, 3000);
			}
			break;
		case AUTO_GREEN:
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, RESET);
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, SET);

			if(timer_flag[1] == 1){
				status = AUTO_YELLOW;
				setTimer(1, 2000);
			}
			break;
		case AUTO_YELLOW:
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, SET);
			HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, RESET);

			if(timer_flag[1] == 1){
				status = AUTO_RED;
				setTimer(1, 5000);
			}
			break;
		default:
			break;
	}
}
