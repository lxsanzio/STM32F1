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

//static enum {sAdvance, sStop, sBack} sServoX, sServoY;		//variable enumerada para estado de movimiento de servo
													// avanza, no se mueve o retrocede

void initJoystick(ADC_HandleTypeDef *, uint16_t []);
void finJoystick(ADC_HandleTypeDef *);
//void stateJoystick(uint16_t R[]);
uint8_t stateJoysticks(uint16_t R);
void stateButton(uint8_t);				//INTENSION DE CONTROLAR LUZ DEL PIN_C13


#endif /* INC_JOYSTICK_H_ */
