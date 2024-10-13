/*
 * timer.h
 *
 *  Created on: Oct 13, 2024
 *      Author: truon
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

extern int timer_flag[10];

void setTimer(int num, int duration);
void timerRun(void);
void HAL_TIM_PeriodElapsedCallBack(TIM_HandleTypeDef *htim);


#endif /* INC_TIMER_H_ */
