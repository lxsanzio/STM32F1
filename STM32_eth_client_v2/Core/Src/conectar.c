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
 * 		 	serverIP: array entero sin signo que se pasa por referencia en funcion connect().
 * @note	-El modulo W5500 puede manejar hasta 8 socket en simultaneo.
 * 			-El bufer asignado a cada socket va de 0 a 16 Kb, sin embargo, la suma
 * 			total de los sockets debe ser menor o igual a 16Kb.
 * 			El modulo w5500 tiene stack, que de hasta 16Kb de memoria maximo
 * 			de asignación total entre la suma de los socket.
 */

void initClient(uint8_t socketNum, uint8_t bufSize){
	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);
	wizchip_init(bufSize, bufSize);
	wiz_NetInfo netInfo = { .mac		= {0x00, 0x08, 0xdc, 0xab, 0xef}, //Mac Addres
							.ip 		= {192, 168, 2, 191},
							.sn			= {255, 255, 255, 0},
							.gw			= {192, 168, 2, 1} };
	wizchip_setnetinfo(&netInfo);
	wizchip_getnetinfo(&netInfo);

}

void initServer(uint8_t socketNum, uint8_t bufSize){
	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);
	wizchip_init(bufSize, bufSize);
	wiz_NetInfo netInfo = { .mac		= {0x00, 0x08, 0xdc, 0xab, 0xff}, //Mac Addres
							.ip 		= {192, 168, 2, 192},
							.sn			= {255, 255, 255, 0},
							.gw			= {192, 168, 2, 1} };
	wizchip_setnetinfo(&netInfo);
	wizchip_getnetinfo(&netInfo);
}

int8_t _write(int fd, char* ptr, int len, uint8_t socketNum){
  uint8_t sentlen = 0;
  uint8_t buflen = len;

  if(getSn_SR(socketNum) == SOCK_ESTABLISHED) {
	if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
	  while(1) {
		sentlen = send(gSock, (void*) ptr, buflen);
		if (sentlen == buflen)
		  return len;
		else if (sentlen > 0 && sentlen < buflen) {
		  buflen -= sentlen;
		  ptr += (len - buflen);
		}
		else if (sentlen < 0)
		  return EIO;
	  }
	}
  } else if(getSn_SR(gSock) != SOCK_LISTEN) {
	/* Remote peer close the connection? */
	close(gSock);
	RetargetInit(gSock);
  }

  errno = EBADF;
  return -1;


}

uint8_t RetargetInit (uint8_t socketNum, uint8_t serverIP){
	/*
	 * ESTABLECIMIENTO Y CONFIGURACION DE SOCKET EN MODO TCP, BUSCANDO CONECTAR CON SERVIDOR
	 * O ESCUCHA CLIENTE SI ES SERVIDOR
	 */
	if(socket(socketNum, Sn_MR_TCP, TCP_PORT, SF_TCP_NODELAY) == socketNum){
		HAL_Delay(800);
		if(serverIP == 0){
			connect(0,&serverIP,TCP_PORT);
			if(getSn_SR(socketNum) == SOCK_ESTABLISHED)
				return 1;
			return 0;
		}
		else{
			if(listen(socketNum) == SOCK_OK)
				return 1;
		}
		return 0;
		}
}

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

