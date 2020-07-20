/*
 * servo.h
 *
 *  Created on: 19 jul. 2020
 *      Author: t440
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32f1xx_hal.h"

uint16_t i = 75;
uint16_t j = 75;

void initServo(TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim3);
void finishServo(TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim3);

void movServ(TIM_HandleTypeDef *ht, int8_t state, uint8_t channel);

#endif /* INC_SERVO_H_ */
