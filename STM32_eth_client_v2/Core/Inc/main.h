/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "wizchip_conf.h"
#include "w5500.h"
#include "socket.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "joystick.h"
#include "conectar.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern UART_HandleTypeDef huart1;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/*
 *
#define SEPARATOR            "=============================================\r\n"
#define WELCOME_MSG  		 "Welcome to STM32Nucleo Ethernet configuration\r\n"
#define NETWORK_MSG  		 "Network configuration:\r\n"
#define IP_MSG 		 		 "  IP ADDRESS:  %d.%d.%d.%d\r\n"
#define NETMASK_MSG	         "  NETMASK:     %d.%d.%d.%d\r\n"
#define GW_MSG 		 		 "  GATEWAY:     %d.%d.%d.%d\r\n"
#define MAC_MSG		 		 "  MAC ADDRESS: %x:%x:%x:%x:%x:%x\r\n"
#define GREETING_MSG 		 "Well done guys! Welcome to the IoT world. Bye!\r\n"
#define CONN_ESTABLISHED_MSG "Connection established with remote IP: %d.%d.%d.%d:%d\r\n"
#define SENT_MESSAGE_MSG	 "Sent a message. Let's close the socket!\r\n"
#define WRONG_RETVAL_MSG	 "Something went wrong; return value: %d\r\n"
#define WRONG_STATUS_MSG	 "Something went wrong; STATUS: %d\r\n"
#define CONNECT_ERR_MSG		 "CONNECT Error!\r\n"


 */
#define SEPARATOR            "=============================================\r\n"
#define WELCOME_MSG  		 "Bienvenido a STM32Nucleo Ethernet Configuracion\r\n"
#define NETWORK_MSG  		 "Network configuration:\r\n"
#define IP_MSG 		 		 "  IP ADDRESS:  %d.%d.%d.%d\r\n"
#define NETMASK_MSG	         "  NETMASK:     %d.%d.%d.%d\r\n"
#define GW_MSG 		 		 "  GATEWAY:     %d.%d.%d.%d\r\n"
#define MAC_MSG		 		 "  MAC ADDRESS: %x:%x:%x:%x:%x:%x\r\n"
#define GREETING_MSG 		 "Well done guys! Welcome to the IoT world. Bye!\r\n"	//no hace falta
#define CONN_ESTABLISHED_MSG "Connection established with remote IP: %d.%d.%d.%d:%d\r\n"
#define SENT_MESSAGE_MSG	 "Se envio el msj.\r\n"
#define WRONG_RETVAL_MSG	 "Something went wrong; return value: \r\n"  //%d se borro
#define WRONG_STATUS_MSG	 "Something went wrong; STATUS: %d\r\n"
#define WRONG_SENTVAL_MSG	 "Something went wrong; return value: %d\r\n"
#define CONNECT_ERR_MSG		 "CONNECT Error!\r\n"



#define TCP_PORT 5001

#define PRINT_STR(msg) do  {										\
  HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);		\
} while(0)

#define PRINT_HEADER() do  {													\
  HAL_UART_Transmit(&huart1, (uint8_t*)SEPARATOR, strlen(SEPARATOR), 100);		\
  HAL_UART_Transmit(&huart1, (uint8_t*)WELCOME_MSG, strlen(WELCOME_MSG), 100);	\
  HAL_UART_Transmit(&huart1, (uint8_t*)SEPARATOR, strlen(SEPARATOR), 100);		\
} while(0)

#define PRINT_NETINFO(netInfo) do { 																					\
  HAL_UART_Transmit(&huart1, (uint8_t*)NETWORK_MSG, strlen(NETWORK_MSG), 100);											\
  sprintf(msg, MAC_MSG, netInfo.mac[0], netInfo.mac[1], netInfo.mac[2], netInfo.mac[3], netInfo.mac[4], netInfo.mac[5]);\
  HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);															\
  sprintf(msg, IP_MSG, netInfo.ip[0], netInfo.ip[1], netInfo.ip[2], netInfo.ip[3]);										\
  HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);															\
  sprintf(msg, NETMASK_MSG, netInfo.sn[0], netInfo.sn[1], netInfo.sn[2], netInfo.sn[3]);								\
  HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);															\
  sprintf(msg, GW_MSG, netInfo.gw[0], netInfo.gw[1], netInfo.gw[2], netInfo.gw[3]);										\
  HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);															\
} while(0)

#define PRINT_FAIL() do  {																		\
	HAL_UART_Transmit(&huart1, (uint8_t*)WRONG_RETVAL_MSG,(uint16_t)strlen(WRONG_RETVAL_MSG),100);\
} while(0)
//	sprintf(msg,)
	//COMO TRAER LOS FLAGS DE LO QUE NO FUNCIONA: AL ENVIAR, AL RECIBIR O AL NO PODER
	//ESTABLECER LA COMUNICACION
//#define PRINT_FAIL_CONNECT

#define PRINT_OK()	do	{																\
	HAL_UART_Transmit(&huart1, (uint8_t*)GREETING_MSG, (uint16_t)strlen(GREETING_MSG),100);	\
} while (0)

char msg[60];





/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
