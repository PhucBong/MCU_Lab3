/*
 * global.h
 *
 *  Created on: Oct 13, 2024
 *      Author: truon
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define INIT 			0
#define AUTO_RED_GREEN 	1
#define AUTO_RED_AMBER 	2
#define AUTO_GREEN_RED 	3
#define AUTO_AMBER_RED 	4

#define RED_INIT 		30
#define AMBER_INIT		5
#define GREEN_INIT 		25

void initLedTime();
extern int mode;
extern int redValue, amberValue, greenValue;
extern int redNew, amberNew, greenNew;


#endif /* INC_GLOBAL_H_ */
