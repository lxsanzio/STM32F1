/*
 * servo.c
 *
 *  Created on: 19 jul. 2020
 *      Author: t440
 */

#include "servo.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;


//OJO AL TEJO PERRITO, NO VALLA A SER COSA QUE NECESITE ENVIAR TIM_CHANNEL_1 DADO QUE SE
//DEFINIO EN EL MAIN
void initServo(TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim3){
	HAL_TIM_PWM_Start(htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(htim3, TIM_CHANNEL_2);
}

void finishServo(TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim3){
	HAL_TIM_PWM_Stop(htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(htim3, TIM_CHANNEL_2);
}

/*
 * @brief	Movimiento de Servo
 * @param	ht estructura de temporizador tipo PWM. State es el estado si debe sumar,
 * 			mantener o restar una variable de estado que determina si debe girar el
 * 			servo para un lado o hacia el otro. Channel es el canal definido del PWM,
 * 			htim2 definido con channel 1, htim3 definido en channel 2.
 * @note	Tiene incorporado un condiiconal que limita el movimiento del servo. No
 * 			permite que se supere por encima o por debajo de tal limites.
 * @retval	none
 */

void movServ(TIM_HandleTypeDef *ht, int8_t state, uint8_t channel){
	if(channel == 1){
		switch(state){
			case -1:
				if(i <= 25) ht->Instance->CCR1 = i;
				else ht->Instance->CCR1 = i--;
				break;
			case 0:
				ht->Instance->CCR1 = i;
				break;
			case 1:
				if(i >= 125) ht->Instance->CCR1 = i;
				ht->Instance->CCR1 = i++;
				break;
		}
	}
	if(channel == 2){
		switch(state){
			case -1:
				if(j <= 25) ht->Instance->CCR2 = j;
				else ht->Instance->CCR2 = j--;
				break;
			case 0:
				ht->Instance->CCR2 = j;
				break;
			case 1:
				if(j >= 125) ht->Instance->CCR2 = j;
				else ht->Instance->CCR2 = j++;
				break;
		}
	}
}
void movServo(TIM_HandleTypeDef* htim2,TIM_HandleTypeDef* htim3, int8_t stateX, int8_t stateY){
	switch(stateX){
		case -1:
			if(i <= 25) htim2->Instance->CCR1 = i;
			else htim2->Instance->CCR1 = i--;
			break;
		case 0:
			htim2->Instance->CCR1 = i;
			break;
		case 1:
			if(i >= 125) htim2->Instance->CCR1 = i;
			htim2->Instance->CCR1 = i++;
			break;
	}
	switch(stateY){
		case -1:
			if(j <= 25) htim3->Instance->CCR2 = j;
			else htim3->Instance->CCR2 = j--;
			break;
		case 0:
			htim3->Instance->CCR2 = j;
			break;
		case 1:
			if(j >= 125) htim3->Instance->CCR2 = j;
			else htim3->Instance->CCR2 = j++;
			break;
	}
}

//
//  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); 	// Se asocia al eje X
//  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);		// Se asocia al eje Y
//
//
////  htim2.Instance->CCR1 = i;
////  htim3.Instance->CCR2 = j;
//  /* USER CODE END 2 */
//
//  /* Infinite loop */
//  /* USER CODE BEGIN WHILE */
//
//  while (1)
//  {
//    /* USER CODE END WHILE */
//
//	  	 HAL_Delay(100);
//
//	  if ((VR[0]>=2000) && (VR[0]<=3000))				//Representa si el Joystick no se mueve
//	   {
////	    HAL_GPIO_WritePin(xmin_GPIO_Port, xmin_Pin, GPIO_PIN_RESET);
////	    HAL_GPIO_WritePin(xplus_GPIO_Port, xplus_Pin, GPIO_PIN_RESET);
//		  htim2.Instance->CCR1 = i;
////		  movNopX();
//	   }
//
//	   if ((VR[1]>=2000) && (VR[1]<=3000))				//Representa si el joystick no se mueve
//	   {
////	    HAL_GPIO_WritePin(ymin_GPIO_Port, ymin_Pin, GPIO_PIN_RESET);
////	    HAL_GPIO_WritePin(yplus_GPIO_Port, yplus_Pin, GPIO_PIN_RESET);
//		   htim3.Instance->CCR2 = j;
////		   movNopY();
//	   }
//
//	   if ((VR[0]>=4000))								//Representa movimientos que suman en X: htim2
//	   {
////	    HAL_GPIO_WritePin(xmin_GPIO_Port, xmin_Pin, GPIO_PIN_RESET);
////	    HAL_GPIO_WritePin(xplus_GPIO_Port, xplus_Pin, GPIO_PIN_SET);
//		   if(i >= 125) htim2.Instance->CCR1 = i;
//		   else {
//			   i ++;
//			   htim2.Instance->CCR1 = i;
//		   }
//	   }
//
//	   if ((VR[0]<=800))								//Representa movimientos que restan en X: htim2
//	   {
////	    HAL_GPIO_WritePin(xmin_GPIO_Port, xmin_Pin, GPIO_PIN_SET);
////	    HAL_GPIO_WritePin(xplus_GPIO_Port, xplus_Pin, GPIO_PIN_RESET);
//		   if(i <= 25) htim2.Instance->CCR1 = i;
//		   else {
//			   i --;
//			   htim2.Instance->CCR1 = i;
//		   }
//	   }
//
//	   if ((VR[1]>=4000))								//Representa movimientos que suman en Y: htim3
//	   {
////	    HAL_GPIO_WritePin(ymin_GPIO_Port, ymin_Pin, GPIO_PIN_RESET);
////	    HAL_GPIO_WritePin(yplus_GPIO_Port, yplus_Pin, GPIO_PIN_SET);
//		   if(j >= 125) htim3.Instance->CCR2 = j;
//		   else{
//			   j++;
//			   htim3.Instance->CCR2 = j;
//		   }
//	   }
//
//	   if ((VR[1]<=800))								//Representa movimientos que restan en Y:htim3
//	   {
////	    HAL_GPIO_WritePin(ymin_GPIO_Port, ymin_Pin, GPIO_PIN_SET);
////	    HAL_GPIO_WritePin(yplus_GPIO_Port, yplus_Pin, GPIO_PIN_RESET);
//		   if(j<= 25) htim3.Instance->CCR2 = j;
//		   else{
//			   j--;
//			   htim3.Instance->CCR2 = j;
//		   }
//	   }
//
//
