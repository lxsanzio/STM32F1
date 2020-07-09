/*
 * conectar.c
 *
 *  Created on: 18 jun. 2020
 *      Author: t440
 */


#include "conectar.h"

extern SPI_HandleTypeDef hspi1;

/*
 * @brief   Conjunto de funciones 4 funciones utilizadas para la comunicacion SPI
 * 			de modulo w5500.
 * @note	Se llama a la variable hspi1 de donde fue definida (main.c)
 */

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

/*
 * @brief	Inicializador del Cliente
 * @param	socketNum: entero sin signo que identifica el socket del modulo
 * 			bufSize: array de entero. Se determina la cantidad de memoria al stack.
 * 					 el modulo w5500 tiene stack, que de hasta 16Kb de memoria maximo
 * 					 de asignación total entre la suma de los socket.
 * @note	-El modulo W5500 puede manejar hasta 8 socket en simultaneo.
 * 			-El bufer asignado a cada socket va de 0 a 16 Kb, sin embargo, la suma
 * 			total de los sockets debe ser menor o igual a 16Kb.
 * 			El modulo w5500 tiene stack, que de hasta 16Kb de memoria maximo
 * 			de asignación total entre la suma de los socket.
 */

void initClient(uint8_t socketNum, uint8_t bufSize){
	uint8_t phyLink = 0;
	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);
	wizchip_init(&bufSize, &bufSize);
	wiz_NetInfo netInfo = { .mac		= {0x00, 0x08, 0xdc, 0xab, 0xef}, //Mac Addres
							.ip 		= {192, 168, 2, 191},
							.sn			= {255, 255, 255, 0},
							.gw			= {192, 168, 2, 1} };
	 do {
	    ctlwizchip(CW_GET_PHYLINK, (void*) &phyLink);
	    HAL_Delay(10);
	  } while(phyLink == PHY_LINK_OFF);

	wizchip_setnetinfo(&netInfo);
//	wizchip_getnetinfo(&netInfo);		No hace falta que esté

}
/*
 * @brief	Inicializador del Server
 * @param	socketNum: entero sin signo que identifica el socket del modulo
 * 			bufSize: array de entero. Se determina la cantidad de memoria al stack.
 * 					 el modulo w5500 tiene stack, que de hasta 16Kb de memoria maximo
 * 					 de asignación total entre la suma de los socket.
 * @note	-El modulo W5500 puede manejar hasta 8 socket en simultaneo.
 * 			-El bufer asignado a cada socket va de 0 a 16 Kb, sin embargo, la suma
 * 			total de los sockets debe ser menor o igual a 16Kb.
 * 			El modulo w5500 tiene stack, que de hasta 16Kb de memoria maximo
 * 			de asignación total entre la suma de los socket.
 */

void initServer(uint8_t socketNum, uint8_t bufSize){
	uint8_t phyLink = 0;
	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);
	wizchip_init(&bufSize, &bufSize);
	wiz_NetInfo netInfo = { .mac		= {0x00, 0x08, 0xdc, 0xab, 0xff}, //Mac Addres
							.ip 		= {192, 168, 2, 192},
							.sn			= {255, 255, 255, 0},
							.gw			= {192, 168, 2, 1} };
	do{
		ctlwizchip(CW_GET_PHYLINK, (void*) &phyLink);
	    HAL_Delay(10);
	} while(phyLink == PHY_LINK_OFF);

	wizchip_setnetinfo(&netInfo);
//	wizchip_getnetinfo(&netInfo);
}

uint8_t estadoSocket(uint8_t socketNum){
	uint16_t len;
	len = getSn_RX_RSR(socketNum);
	if (len > 0) 	return 1;
	else 	return 1;
}

int8_t envia(uint8_t socketNum, char* pbufData, uint8_t *lenData){
	uint16_t len;
	uint32_t sentlen;

	len = getSn_RX_RSR(socketNum);
	if(estadoScket(socketNum)) return (-1);
	// recibir(socketNum); significa que hay algo por recibir pero debe controlarse
	// una jerarquia mas arriba, o desde el main o interrupcion
	else{
		if(getSn_SR(socketNum) == SOCK_ESTABLISHED){
			len = (uin16_t *)(&lenData);
			while(1){
				sentlen = send (socketNum, (void*)pbufData, len);
				if ((uint16_t *)sentlen == len)
					return 0; //modificar el 0 Se envio todo significaría
				else if ((sentlen > 0) && (sentlen < &lenData)){  //En caso de que haya quedado algo por enviar
						&lendata -= sentlen;
						pbufData += (len - pbufData);
						//HACE FALTA SEGUIR ENVIANDO DATOS, CORRER
				}
				else if (sentlen < 0)  //Menor a cero Error
					return EIO;

				}
			}
		else if(getSn_SR(socketNum) != SOCKET_CONNECT)

		}
	}

//int8_t _write(int fd, char* ptr, int len, uint8_t socketNum){
//  uint8_t sentlen = 0;
//  uint8_t buflen = len;
//
//  if(getSn_SR(socketNum) == SOCK_ESTABLISHED) {
//	if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
//	  while(1) {
//		sentlen = send(gSock, (void*) ptr, buflen);
//		if (sentlen == buflen)
//		  return len;
//		else if (sentlen > 0 && sentlen < buflen) {
//		  buflen -= sentlen;
//		  ptr += (len - buflen);
//		}
//		else if (sentlen < 0)
//		  return EIO;
//	  }
//	}
//  } else if(getSn_SR(gSock) != SOCK_LISTEN) {
//	/* Remote peer close the connection? */
//	close(gSock);
//	RetargetInit(gSock);
//  }
//
//  errno = EBADF;
//  return -1;
//
//
//}
//
//int8_t _read(int fd, char* ptr, int len, uint8_t socketNum) {
//  if(getSn_SR(socketNum) == SOCK_ESTABLISHED) {
//    if (fd == STDIN_FILENO) {
//      while(1) {
//        len = recv(gSock, (void*) ptr, len);
//        if (len > 0)
//          return len;
//        else
//          return EIO;
//      }
//    }
//  } else if(getSn_SR(gSock) != SOCK_LISTEN) {
//    /* Remote peer close the connection? */
//    close(gSock);
//    RetargetInit(gSock);
//  }
//
//  errno = EBADF;
//  return -1;
//}


/*
 * @brief	Recargador de Inicio
 * @param	socketNum: entero sin signo que identifica el socket del modulo
 * 			serverIP: array de entero. La direccion IP del server en caso.
 * 					 el modulo w5500 tiene stack, que de hasta 16Kb de memoria maximo
 * 					 de asignación total entre la suma de los socket.
 * 					 SI ES CLIENTE, IGUALAR PREVIAMENTE A CERO "serverIP = 0" O EN EL MOMENTO
 * 					 DE HACER LA LLAMADA A LA FUNCION PASAR PARAMETRO 0
 * 		 	serverIP: array entero sin signo que se pasa por referencia en funcion connect().
 * @retval	0: No se pudo establecer comunicacion. Cliente con servidor o servidor en modo listen.
 * 			1: Se estableció la coneccion entre cliente y servidor.
 * 			2: No se pudo establecer el socket.
 * @note	Esta funcion se llama para reorientar o actualizar los modos en los modulos W5500.
 * 			- Inicia socket, si devuelve el mismo valor de socket, se inicio exitoso
 * 			- Necesita el modulo un tiempo
 * 			- Si es cliente y se debe conectar a un servidor. Si se conecta devuelve SOCK_ESTABLISHED.
 * 			- En caso de ser servidor debe incializar el socket y luego quedar en modo 'listen'
 */

uint8_t RetargetInit (uint8_t socketNum, uint8_t serverIP){
	/*
	 * ESTABLECIMIENTO Y CONFIGURACION DE SOCKET EN MODO TCP, BUSCANDO CONECTAR CON SERVIDOR
	 * O ESCUCHA CLIENTE SI ES SERVIDOR
	 */
	if(socket(socketNum, Sn_MR_TCP, TCP_PORT, SF_TCP_NODELAY) == socketNum){
		HAL_Delay(800);
		if(serverIP != 0){
			if(connect(socketNum,&serverIP,TCP_PORT == SOCK_OK);
				return 1 ;
			return 0;
		}
		else{
			if(listen(socketNum) == SOCK_OK)
				return 1;
		}
		return 0;
		}
	return 2;
}

/*

getSn_RX_RSR
Received data size register(R)

Sn_RX_RSR indicates the data size received and saved in Socket n RX Buffer.
Sn_RX_RSR does not exceed the Sn_RXBUF_SIZE and is calculated as the difference between
ï¿½Socket n RX Write Pointer (Sn_RX_WR)and ï¿½Socket n RX Read Pointer (Sn_RX_RD)
*/

/*
 * @brief	Inicializador del servidor
 * @param	socketNum: entero sin signo que identifica el socket del modulo
 * 					   el modulo W5500 puede manejar hasta 8 socket en simultaneo
 * 			bufSize: array de entero. Se determina la cantidad de memoria al stack.
 * 					 el modulo w5500 tiene stack, que de hasta 16Kb de memoria maximo
 * 					 de asignación total entre la suma de los socket.
 * @note	-El bufer asignado a cada socket va de 0 a 16 Kb, sin embargo, la suma
 * 			total de los sockets debe ser menor o igual a 16Kb.
 * 			El modulo w5500 tiene stack, que de hasta 16Kb de memoria maximo
 * 			de asignación total entre la suma de los socket.
 */


  /*
   * Documentación del modulo W5500
   * http://wizwiki.net/wiki/doku.php/products:w5500:application:tcp_function
   */


void desconectar(uint8_t socketNum){
  disconnect(socketNum);
  close(socketNum);

}

