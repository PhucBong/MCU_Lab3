/*
 * software_time.h
 *
 *  Created on: Oct 13, 2024
 *      Author: truon
 */

#ifndef INC_SOFTWARE_TIME_H_
#define INC_SOFTWARE_TIME_H_

extern int timer_flag[10];

void setTimer(int num, int duration);
void timerRun();

#endif /* INC_SOFTWARE_TIME_H_ */
