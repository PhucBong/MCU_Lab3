/*
 * timer.c
 *
 *  Created on: Oct 13, 2024
 *      Author: truon
 */

#include "main.h"
#include "input_reading.h"

const int TIMER_CYCLE = 10;
int timer_flag[10] = {0};
int timer_counter[10] = {0};

void setTimer(int num, int duration){
	timer_flag[num] = 0;
	timer_counter[num] = duration / TIMER_CYCLE;
}

void timerRun(void){
//	for(int i = 0; i < 10; i++){
//		if (timer_counter[i] > 0){
//			timer_counter[i]--;
//			if(timer_counter[i] <= 0){
//				timer_flag[i] = 1;
//			}
//		}
//	}
	if (timer_counter[1] > 0){
		timer_counter[1]--;
		if(timer_counter[1] <= 0){
			timer_flag[1] = 1;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		button_reading();

	}
	timerRun();
}
