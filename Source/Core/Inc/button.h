/*
 * button.h
 *
 *  Created on: Oct 13, 2024
 *      Author: truon
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

extern int button1_flag;

int isButton1Pressed();
void getKeyInput();
void subKeyProcess();

#endif /* INC_BUTTON_H_ */
