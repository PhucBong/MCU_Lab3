/*
 * software_timer.c
 *
 *  Created on: Oct 13, 2024
 *      Author: truon
 */

#include "software_time.h"

int TIMER_CYCLE = 10;
int timer_flag[10] = {0};
int timer_counter[10] = {0};

void setTimer(int num, int duration){
	timer_flag[num] = 0;
	timer_counter[num] = duration;
}
void timerRun(){
	for(int i = 0; i < 9; i++){
		if(timer_counter[i] > 0){
			timer_counter[i]--;
			if(timer_counter[i] <= 0){
				timer_flag[i] = 1;
			}
		}
	}
}
