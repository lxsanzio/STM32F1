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
#include "loopback.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

//reconnect:
//  /* Open socket 0 as TCP_SOCKET with port TCP_PORT = 5000 */
//     if((retVal = socket(0, Sn_MR_TCP, TCP_PORT, 0)) == 0) {
//   	  /* Put socket in LISTEN mode. This means we are creating a TCP server */
//   	  if((retVal = listen(0)) == SOCK_OK) {
//   		  /* While socket is in LISTEN mode we wait for a remote connection */
//   		  while((sockStatus = getSn_SR(0)) == SOCK_LISTEN)
//   			  HAL_Delay(100);
//   		  /* OK. Got a remote peer. Let's send a message to it */
//   		  while(1) {
//   			  /* If connection is ESTABLISHED with remote peer */
//   			  if((sockStatus = getSn_SR(0)) == SOCK_ESTABLISHED) {
//   				  uint8_t remoteIP[4];
//   				  uint16_t remotePort;
//   				  /* Retrieving remote peer IP and port number */
//   				  getsockopt(0, SO_DESTIP, remoteIP);
//   				  getsockopt(0,SO_DESTPORT, (uint8_t*)&remotePort);
//   				  sprintf(msg, CONN_ESTABLISHED_MSG, remoteIP[0], remoteIP[1], remoteIP[2], remoteIP[3], remotePort);
//   				  PRINT_STR(msg);
//   				  /* Let's send a welcome message and closing socket */
//   				  if((retVal = send(0, GREETING_MSG, strlen(GREETING_MSG))) == (int16_t)strlen(GREETING_MSG))
//   					  PRINT_STR(SENT_MESSAGE_MSG);
//   				  else { /* Ops: something went wrong during data transfer */
//   					  sprintf(msg, WRONG_RETVAL_MSG, retVal);
//   					  PRINT_STR(msg);
//   				  }
//   				  break;
//   			  }
//   			  else { /* Something went wrong with remote peer, maybe the connection was closed unexpectedly */
//   				  sprintf(msg, WRONG_STATUS_MSG, sockStatus);
//   				  PRINT_STR(msg);
//   				  break;
//   			  }
//   		  }
//
//   	  } else /* Ops: socket not in LISTEN mode. Something went wrong */
//   		  PRINT_STR(LISTEN_ERR_MSG);
//     } else { /* Can't open the socket. This means something is wrong with W5100 configuration: maybe SPI issue? */
//   	  sprintf(msg, WRONG_RETVAL_MSG, retVal);
//   	  PRINT_STR(msg);
//     }
//
//     /* We close the socket and start a connection again */
//     disconnect(0);
//     close(0);
//     goto reconnect;


/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

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
