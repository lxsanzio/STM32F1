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

void initClient(uint8_t socketNum, uint8_t* bufSize){
	uint8_t phyLink = 0;
	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);
	wizchip_init(bufSize, bufSize);
	wiz_NetInfo netInfo = { .mac		= {0x00, 0x11, 0x08, 0xdc, 0xab, 0xef}, //Mac Addres
							.ip 		= {192, 168, 2, 191},
							.sn			= {255, 255, 255, 0},
							.gw			= {192, 168, 2, 1} };
	 do {
	    ctlwizchip(CW_GET_PHYLINK, (void*) &phyLink);
	    HAL_Delay(10);
	  } while(phyLink == PHY_LINK_OFF);

	wizchip_setnetinfo(&netInfo);
	wizchip_getnetinfo(&netInfo);
	PRINT_NETINFO(netInfo);				//VISUALIZA POR USART LOS PARAMETROS DE RED
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

void initServer(uint8_t socketNum, uint8_t* bufSize){
	uint8_t phyLink = 0;
	reg_wizchip_cs_cbfunc(cs_sel, cs_desel);
	reg_wizchip_spi_cbfunc(spi_rb, spi_wb);
	wizchip_init(bufSize, bufSize);
	wiz_NetInfo netInfo = { .mac		= {0x00, 0x11, 0x08, 0xdc, 0xab, 0xff}, //Mac Addres
							.ip 		= {192, 168, 2, 192},
							.sn			= {255, 255, 255, 0},
							.gw			= {192, 168, 2, 1} };
	do{
		ctlwizchip(CW_GET_PHYLINK, (void*) &phyLink);
	    HAL_Delay(10);
	} while(phyLink == PHY_LINK_OFF);

	wizchip_setnetinfo(&netInfo);
	wizchip_getnetinfo(&netInfo);
	PRINT_NETINFO(netInfo);				//VISUALIZA POR USART LOS PARAMETROS DE RED
}


/*	@brief	Estado del socket
 * 	@param	socketNum: entero sin signo que identifica el socket del modulo.
 * 	@note	Esta funcion testea el stack RX del modulo.
 * 	@retval	0: No hay datos que recibir
 * 			1: Hay datos el stack RX
 */
uint8_t estadoSocket(uint8_t socketNum){
	uint16_t len;
	len = getSn_RX_RSR(socketNum);
	if (len > 0) 	return 1;
	else 	return 0;
}

/*	@brief	Estado del cable
 * 	@note	Función que determina la conexion del cable eth, en caso de que esté conectado
 * 			enviará datos, de lo contrario pasa a estado close.
 * 	@retval 	0: El cable se encuentra conectado y debe enviar y recibir datos.
 * 				1: El cable eth se desconectó
 */


uint8_t estadoWire(void){
	uint8_t phyLink = 0;
	ctlwizchip(CW_GET_PHYLINK, (void*) &phyLink);
	HAL_Delay(10);
	if(phyLink == PHY_LINK_OFF){
		return 1;
	}
	return 0;
}

/*
 * @brief	Enviar datos
 * @oaram	socketNum: entero sin signo que identifica el socket del modulo.
 * 			pbufData: Puntero al dato a enviar.
 * 			len: tamaño de lo que se envia.
 * 			serverIP: Array entero sin signo que se pasa por referencia en funcion connect(),
 * 			en caso de llamar retargetInit y el que este enviando info es el cliente. Si es server
 * 			se pasa paramatro '0'.
 * @retval -1: Bad File Number 'val = 9'
 * 			0: Se envio el paquete completo.
 * 			EIO: Hubo un error de I/O valor 'errno = 5'
 *
 */

int8_t envia(uint8_t socketNum, char* pbufData, uint8_t len, uint8_t* serverIP){
	uint16_t buflen;
	uint32_t sentlen;
	if(getSn_SR(socketNum) == SOCK_ESTABLISHED){
		buflen = (uint16_t)len;
		while(1){
			sentlen = send(socketNum, (void*) pbufData, buflen);
			if ((uint16_t )sentlen == buflen)
				return 0;
			else if ((sentlen > 0) && (sentlen < buflen)){  //En caso de que haya quedado algo por enviar
					buflen -= sentlen;
					pbufData += (len - buflen);				//CORRE de lugar el array

			}
			else if (sentlen < 0)  //Menor a cero Error FALTAL
				return EIO;		//EIO = 5 en 'errno.h' I/O Error
			}
		}
	else if(getSn_SR(socketNum) != SOCK_ESTABLISHED){
			close(socketNum);
			RetargetInit(socketNum, serverIP);
	}
	errno = EBADF;
	return -1; // Hubo algún error
}

/*
 * @brief	Recibe datos
 * @oaram	socketNum: entero sin signo que identifica el socket del modulo.
 * 			pbufData: Puntero al dato a enviar.
 * 			len: tamaño de lo que se envia.
 * 			serverIP: Array entero sin signo que se pasa por referencia en funcion connect(),
 * 			en caso de llamar retargetInit y el que este enviando info es el cliente. Si es server
 * 			se pasa paramatro '0'.
 * @retval  -1: Salio mal algo al intentar recibir.
 * 			EIO: Error de I/O. val. '5'
 * 			0: si se envio correctamente.
 */
int8_t recibe(uint8_t socketNum, char* pbufData, uint8_t len, uint8_t* serverIP){
	if(getSn_SR(socketNum) == SOCK_ESTABLISHED){
		while(1){
			len = recv(socketNum, (void*)pbufData,len);
			if(len > 0)
				return 0;
			else
				return EIO;
		}
	}
	else{
		close(socketNum);
		HAL_Delay(100);
		RetargetInit(socketNum, serverIP);
	}
	errno = EBADF;
	return -1;
}

/*
 * @brief	Recargador de Inicio
 * @param	socketNum: entero sin signo que identifica el socket del modulo
 * 			serverIP: array de entero. La direccion IP del server en caso.
 * 					 el modulo w5500 tiene stack, que de hasta 16Kb de memoria maximo
 * 					 de asignación total entre la suma de los socket.
 * 					 SI ES CLIENTE, IGUALAR PREVIAMENTE A CERO "serverIP = 0" O EN EL MOMENTO
 * 					 DE HACER LA LLAMADA A LA FUNCION PASAR PARAMETRO 0
 * 		 	serverIP: array entero sin signo que se pasa por referencia en funcion connect().
 * @retval	0: No se pudo establecer comunicacion con Cliente.
 * 			1: Se estableció la coneccion entre cliente y servidor.
 * 			2: No se pudo establecer el socket.
 * 			3: No se pudo establecer comunicacion con servidor
 * @note	Esta funcion se llama para reorientar o actualizar los modos en los modulos W5500.
 * 			- Inicia socket, si devuelve el mismo valor de socket, se inicio exitoso
 * 			- Necesita el modulo un tiempo
 * 			- Si es cliente y se debe conectar a un servidor. Si se conecta devuelve SOCK_ESTABLISHED.
 * 			- En caso de ser servidor debe incializar el socket y luego quedar en modo 'listen'
 */

uint8_t RetargetInit (uint8_t socketNum, uint8_t* serverIP){
	uint16_t server_port = 5001;
	uint8_t statusSocket;


	statusSocket = getSn_SR(socketNum);
//	while((getSn_SR(socketNum) != SOCK_LISTEN) || (getSn_SR(socketNum) != SOCK_ESTABLISHED)){
	while((statusSocket != 20)){// || (statusSocket != 23)){

	if(socket(socketNum, Sn_MR_TCP, server_port, SF_TCP_NODELAY) == socketNum){
		HAL_Delay(800);
		if(*serverIP != 0){
			if(connect(socketNum,serverIP,server_port) == SOCK_OK)
		return 1 ;
			return 0;
		}
		else{
			if(listen(socketNum) == SOCK_OK)
				return 1;
		}
		return 3;
	}
	return 2;
	}
	return 1;
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

