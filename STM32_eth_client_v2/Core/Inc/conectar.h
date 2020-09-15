/*
 * conectar.h
 *
 *  Created on: 18 jun. 2020
 *      Author: t440
 */

#ifndef INC_CONECTAR_H_
#define INC_CONECTAR_H_


#include <stdio.h>
#include "main.h"

#include "stm32f1xx_hal.h"
#include "stm32f103xb.h"
#include "wizchip_conf.h"
#include "w5500.h"
#include "socket.h"
#include "errno.h"
//#include "main.h" 		//se agrega para que no solicite info de las macros
/*
 * 		PUERTO COMUNICACION TCP
 */
#define TCP_PORT 5001


void cs_sel();
void cs_desel();
uint8_t spi_rb(void);
void spi_wb(uint8_t b);

void initClient(uint8_t socketNum, uint8_t* bufSize);
void initServer(uint8_t socketNum, uint8_t* bufSize);

int8_t estadoSocket(uint8_t socketNum);
uint8_t estadoWire(void);

//RETARGET, ENVIA Y RECIBE NO SE ESTAN USANDO
uint8_t RetargetInit (uint8_t socketNum, uint8_t* serverIP);

int8_t envia(uint8_t socketNum, char* pbufData, uint8_t len, uint8_t* serverIP);
int8_t recibe(uint8_t socketNum, char* pbufData, uint8_t len, uint8_t* serverIP);



void desconectar(uint8_t socketNum);

#endif /* INC_CONECTAR_H_ */

