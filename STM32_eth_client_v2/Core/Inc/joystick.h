/*
 * joystick.h
 *
 *  Created on: 8 jun. 2020
 *      Author: t440
 */



#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

#include <stdio.h>
#include "stm32f1xx_hal.h"


void initJoystick(ADC_HandleTypeDef *, uint16_t []);
void finJoystick(ADC_HandleTypeDef *);
uint8_t stateJoysticks(uint16_t R);
void stateButton(uint8_t);				//INTENSION DE CONTROLAR LUZ DEL PIN_C13


#endif /* INC_JOYSTICK_H_ */
