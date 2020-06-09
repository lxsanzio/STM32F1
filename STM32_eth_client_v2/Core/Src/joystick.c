/*
 * Joystick.c
 *
 *  Created on: 8 jun. 2020
 *      Author: t440
 */

#include "joystick.h"




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
