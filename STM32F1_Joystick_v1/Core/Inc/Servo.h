/*
 * Servo.h
 *
 *  Created on: 25 abr. 2020
 *      Author: t440
 */

#include "main.h"

#define i  75;
#define j  75;

#ifndef INC_SERVO_H_
#define INC_SERVO_H_


extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;



void movAxisXplus(void);
void movAxisXminus(void);
void movAxisYplus(void);
void movAxisYminus(void);
void movNopX(void);
void movNopY(void);

#endif /* INC_SERVO_H_ */
