/*
 * input_processing.h
 *
 *  Created on: Oct 13, 2024
 *      Author: truon
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

extern int cnt;
extern int counter1[3];
extern int counter2[3];
extern int sw_led;
enum Color {RED, GREEN, AMBER}; // 0 RED, 1 GREEN, 2 AMBER

void fsm_for_input_processing(void);
void fsm_automatic_run(void);

#endif /* INC_INPUT_PROCESSING_H_ */
