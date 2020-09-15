/*
 * servo.c
 *
 *  Created on: 19 jul. 2020
 *      Author: t440
 */

#include "servo.h"


uint8_t serv[2] = {75,75};
uint8_t x = 5;


void initServo(TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim3){
	HAL_TIM_PWM_Start(htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(htim3, TIM_CHANNEL_2);
	htim2->Instance->CCR1 = serv[0];
	htim3->Instance->CCR2 = serv[1];
}

void finishServo(TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim3){
	HAL_TIM_PWM_Stop(htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(htim3, TIM_CHANNEL_2);
}

/*
 * @brief	Movimiento de Servo
 * @param	ht puntero a estructura de temporizador tipo PWM. State es el estado si
 * 			debe sumar,	mantener o restar una variable de estado que determina si debe
 * 			girar el servo para un lado o hacia el otro. Channel es el canal
 * 			definido del PWM, htim2 definido con channel 1, htim3 definido en channel 2.
 * @note	Tiene incorporado un condiiconal que limita el movimiento del servo. No
 * 			permite que se supere por encima o por debajo de tal limites.
 * @retval	none
 */

void movServo(TIM_HandleTypeDef *ht, uint8_t state, uint8_t channel){
	if(channel == 1){
		switch(state){
			case 0:
				if(serv[0] <= 25) ht->Instance->CCR1 = serv[0];
				else ht->Instance->CCR1 = serv[0] -= x;
				break;
			case 1:
				ht->Instance->CCR1 = serv[0];
				break;
			case 2:
				if(serv[0] >= 125) ht->Instance->CCR1 = serv[0];
				ht->Instance->CCR1 = serv[0] += x;
				break;
		}
	}
	if(channel == 2){
		switch(state){
			case -0:
				if(serv[1] <= 25) ht->Instance->CCR2 = serv[1];
				else ht->Instance->CCR2 = serv[1] -= x;
				break;
			case 1:
				ht->Instance->CCR2 = serv[1];
				break;
			case 2:
				if(serv[1] >= 125) ht->Instance->CCR2 = serv[1];
				else ht->Instance->CCR2 = serv[1] += x;
				break;
		}
	}
}


