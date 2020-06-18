/*
 * cliente.c
 *
 *  Created on: Jun 16, 2020
 *      Author: t440
 */

#include "cliente.h"

extern SPI_HandleTypeDef hspi1;

void cs_sel() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //CS LOW
}

void cs_desel() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); //CS HIGH
}

uint8_t spi_rb(void) {
	uint8_t rbuf;
	HAL_SPI_Receive(&hspi1, &rbuf, 1, 0xFFFFFFFF);
	return rbuf;
}

void spi_wb(uint8_t b) {
	HAL_SPI_Transmit(&hspi1, &b, 1, 0xFFFFFFFF);
}


void initClient(uint8_t socketNum, uint8_t bufSize, uint8_t serverIP){
	uint8_t sockStatus;
	uint8_t retVal;
	uint8_t rcvBuf[60];
	uint16_t rcvLen;
	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);
	wizchip_init(bufSize, bufSize);
	wiz_NetInfo netInfo = { .mac		= {0x00, 0x08, 0xdc, 0xab, 0xef}, //Mac Addres
							.ip 		= {192, 168, 2, 191},
							.sn			= {255, 255, 255, 0},
							.gw			= {192, 168, 2, 1} };
	wizchip_setnetinfo(&netInfo);
	wizchip_getnetinfo(&netInfo);
	if((retVal = socket(socketNum, Sn_MR_TCP, TCP_PORT, SF_TCP_NODELAY)) == 0){
			HAL_Delay(800);
		  		  /*Busco conectarme*/
			sockStatus = getSn_SR(0);
			HAL_Delay(800);

			while(sockStatus != SOCK_OK) sockStatus = connect(0,&serverIP,TCP_PORT);
			if(sockStatus == SOCK_OK){
				sockStatus = getSn_SR(0);
				while(1){
					if((sockStatus = getSn_SR(0)) == SOCK_ESTABLISHED){ // Sn_SR  SE queda aca!! LPM
						uint8_t remoteIP[4];
						uint16_t remotePort;
						getsockopt(0, SO_DESTIP, remoteIP);
						getsockopt(0, SO_DESTPORT, (uint8_t*)&remotePort);
	//IMPRIMIR POR UART QUIEN SE CONECTO

	//					sprintf(msg, CONN_ESTABLISHED_MSG, remoteIP[0], remoteIP[1], remoteIP[2], remoteIP[3], remotePort);
	//					PRINT_STR(msg);
						retVal = recv(0, rcvBuf, sizeof(rcvBuf));
	//					PRINT_STR(rcvBuf);
						break;
					}
					else { /* Something went wrong with remote peer, maybe the connection was closed unexpectedly */
	//					sprintf(msg, WRONG_STATUS_MSG, sockStatus);
	//					PRINT_STR(msg);
						break;
					}
			  }

			  }
			else {/* Ops: socket not in LISTEN mode. Something went wrong */
	//			  PRINT_STR(CONNECT_ERR_MSG);
			retVal = recv(0, rcvBuf, sizeof(rcvBuf));
			  }

		 }
		 else { /* Can't open the socket. This means something is wrong with W5100 configuration: maybe SPI issue? */
	//		 sprintf(msg, WRONG_RETVAL_MSG, retVal);
	//		 PRINT_STR(msg);
		  }

}

void initServer(uint8_t socketNum, uint8_t bufSize){
	uint8_t sockStatus;
	uint8_t retVal;
	uint8_t rcvBuf[60];
	uint16_t rcvLen;
	uint8_t i = 0;
	/*
	 * COMIENZA PROCESO DE INICIALIZACION DE MODULO W5500
	 */
	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);
	wizchip_init(bufSize, bufSize);
	wiz_NetInfo netInfo = { .mac		= {0x00, 0x08, 0xdc, 0xab, 0xff}, //Mac Addres
							.ip 		= {192, 168, 2, 192},
							.sn			= {255, 255, 255, 0},
							.gw			= {192, 168, 2, 1} };
	wizchip_setnetinfo(&netInfo);
	wizchip_getnetinfo(&netInfo);

	/*
	 * FINALIZA PROCESO DE INCIALIZAICON DE MODULO W5500
	 */

	/*
	 * ESTABLECIMIENTO Y CONFIGURACION DE SOCKET EN MODO TCP, QUEDANDO EN MODO ESCUCHA
	 */

  if((retVal = socket(socketNum, Sn_MR_TCP, TCP_PORT, SF_TCP_NODELAY)) == socketNum) {
	  /* Put socket in LISTEN mode. This means we are creating a TCP server */
	  if((retVal = listen(socketNum)) == SOCK_OK) {
		  /* While socket is in LISTEN mode we wait for a remote connection */
		  while((sockStatus = getSn_SR(socketNum)) == SOCK_LISTEN)
			  HAL_Delay(800);
		  /* OK. Got a remote peer. Let's send a message to it */
		  while(1) {
			  /* If connection is ESTABLISHED with remote peer */
			  if((sockStatus = getSn_SR(socketNum)) == SOCK_ESTABLISHED) {
				  uint8_t remoteIP[4];
				  uint16_t remotePort;
				  /* Retrieving remote peer IP and port number */
				  getsockopt(0, SO_DESTIP, remoteIP);
				  getsockopt(0,SO_DESTPORT, (uint8_t*)&remotePort);
//				  sprintf(msg, CONN_ESTABLISHED_MSG, remoteIP[0], remoteIP[1], remoteIP[2], remoteIP[3], remotePort);
//				  PRINT_STR(msg);
				  break;
			  }
			  else { /* Something went wrong with remote peer, maybe the connection was closed unexpectedly */
//				  sprintf(msg, WRONG_STATUS_MSG, sockStatus);
//				  PRINT_STR(msg);
				  //SI NO SE PUDO ESTABLECER CONECCION SE DEBE INFORMAR ERROR
				  i++;
				  if(i > 500){
					  //SI ESTE CONTADOR SUPERA
					  break;
				  }
			  }
		  }

	  } else /* Ops: socket not in LISTEN mode. Something went wrong */
		  PRINT_STR(LISTEN_ERR_MSG);
	 } else { /* Can't open the socket. This means something is wrong with W5100 configuration: maybe SPI issue? */
	  sprintf(msg, WRONG_RETVAL_MSG, retVal);
	  PRINT_STR(msg);
	 }


}
void desconectar(uint8_t socketNum){
  disconnect(socketNum);
  close(socketNum);

}
