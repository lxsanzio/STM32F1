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


/*
 * @brief	Determina estado de joystick.
 * @param	R: Entero sin signo de 16b que lo arbitra el ADC
 * @note	Al invocarse el método se elige el array a verificar si el que corresponde a X o Y.
 * @retval	0: Retrocede
 * 			1:  No se mueve
 * 			2:	Adelanta
 */

uint8_t stateJoysticks(uint16_t R){
	if (R <= 500)	return 0;
	if ((R >= 1600) && (R <= 2300))	return 1;
	if (R >= 3000) return 2;
}




void stateButton(uint8_t btn)
{

}

