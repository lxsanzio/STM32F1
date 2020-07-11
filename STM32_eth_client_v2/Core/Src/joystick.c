/*
 * Joystick.c
 *
 *  Created on: 8 jun. 2020
 *      Author: t440
 */

#include "joystick.h"

/**
 * @brief	Función inicio de Joystick.
 * @param	hadc1: puntero a tipo de dato estructura ADC
 * 			VR[]: arreglo en donde se almacena lo que es recogido por el ADC
 * 				  tiene dos canales de conversion.
 * @note	Inicia el ADC por DMA.
 * @retval	None
 *
 */

void initJoystick(ADC_HandleTypeDef* hadc1, uint16_t VR[]){
	HAL_ADC_Start_DMA(hadc1,(uint32_t *)VR,2);
}

/**
 * @brief	Funcion finaliza Joystick
 * @param	hadc1: puntero a tipo de dato estructura ADC
 * @note	Finaliza ADC por DMA
 * @retval	None
 *
 */

void finJoystick(ADC_HandleTypeDef *hadc1){
	HAL_ADC_Stop_DMA(hadc1);
}


/**
 * @brief   Estado del Joystick que determina si el movimiento es incremental,
 * 			decremental o se mantiene quieto.
 * @note	El argumento es pasado por referencia es un vector que se actualiza
 * 			conforme se refrescan los valores del ADC
 * @retval	None
 *
 */
void stateJoystick(uint16_t R[]){
	if ((R[0]>=2000) && (R[0]<=3000))				//Representa si el Joystick no se mueve
	{
		if(sServoX != 1) sServoX = sStop;
	}
	if ((R[1]>=2000) && (R[1]<=3000))				//Representa si el joystick no se mueve
	{
		if(sServoY != 1) sServoY = sStop;
	}

	if ((R[0]>=4000))								//Representa movimientos en X: incrementando (htim2, guiño a PWM servidor)
	{
		if(sServoX != 0) sServoX = sAdvance;
	}
	if ((R[0]<=800))								//Representa movimientos en X: decrementando (htim2, guiño a PWM servidor)
	{
		if(sServoX != 2) sServoX = sBack;
	}
	if ((R[1]>=4000))								//Representa movimientos en Y: incrementando (htim3, guiño a PWM servidor)
	{
		if(sServoY != 0) sServoY = sAdvance;
	}
	if ((R[1]<=800))								//Representa movimientos en Y: decrementando (htim3, guiño a PWM servidor)
	{
		if(sServoY != 2) sServoY = sBack;
	}
}		//POSIBILIDAD DE RETORNAR UN VALOR ENTERO DEL 0 AL 6 CON LA CANTIDAD DE ESTADOS
		//( 3 POR CADA PAR X,Y). O BIEN, VER ALGUN VALOR POR REFERENCIA





void stateButton(uint8_t btn)
{

}

//void stateJoystick(uint16_t *R)
//{
//
//		  if ((R[0]>=2000) && (R[0]<=3000))				//Representa si el Joystick no se mueve
//		   {
//	////		  htim2.Instance->CCR1 = i;						//Esta sentencia es para PWM salida a servo
//	///*
//	// * 		Previo a usar tipo de dato enumerado
//	// */
//	//
//	////		  if ( vX != "m1") vX = "m1";
//		   }
//	//
//		   if ((R[1]>=2000) && (R[1]<=3000))				//Representa si el joystick no se mueve
//		   {
//	////		   htim3.Instance->CCR2 = j;					//Esta sentencia es para PWM salida a servo
//	//
//	//
//	////		   vY = "m1";		//m1 indica no movimiento
//		   }
//	//
//		   if ((R[0]>=4000))								//Representa movimientos que suman en X: htim2
//		   {
//	////		   if(i >= 125) htim2.Instance->CCR1 = i;
//	////		   else {
//	////			   i ++;
//	////			   htim2.Instance->CCR1 = i; 					//Esta sentencia es para PWM salida a servo
////			   }
//	//
//	//
//	////		   vX = "m2"; 		//m2 indica movimiento para un lado
//		   }
//	//
//		   if ((R[0]<=800))								//Representa movimientos que restan en X: htim2
//		   {
//	////		   if(i <= 25) htim2.Instance->CCR1 = i;
//	////		   else {
//	////			   i --;
//	////			   htim2.Instance->CCR1 = i;					//Esta sentencia es para PWM salida a servo
//	////		   }
//	//
//	//
//	////		   vX = "m0";		//m0 indica movimiento para otro lado
//		   }
//	//
//		   if ((R[1]>=4000))								//Representa movimientos que suman en Y: htim3
//		   {
//	////		   if(j >= 125) htim3.Instance->CCR2 = j;
//	////		   else{
//	////			   j++;
//	////			   htim3.Instance->CCR2 = j;
//	////		   }
//	//
//	//
//	////		   vY = "m2";		//m1 indica movimiento para un lado
//	//
//		   }
//
//		   if ((R[1]<=800))								//Representa movimientos que restan en Y:htim3
//		   {
//	////		   if(j<= 25) htim3.Instance->CCR2 = j;
//	////		   else{
//	////			   j--;
//	////			   htim3.Instance->CCR2 = j;
//	////		   }
//	//
//	//
//	////		   vY = "m0";		//el valor m0 indica movimiento para un lado
//		   }
//
//
//
//}
