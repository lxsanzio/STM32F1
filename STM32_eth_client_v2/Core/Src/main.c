/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

void SwitchLED (){
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

void prendeLED(void);
void apagaLED(void);

void translate (char *msg, uint8_t *rcv);
void parpadea (void);
void sirenaLoca(void);

void toggleFlag(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint16_t VR[2];
uint8_t socketNum = 0;


uint8_t _sirena;
enum _estadoPa{sINIT, sFINISH, sWORK, sERROR, sCLOSE} estadoP;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{/* USER CODE BEGIN 1 */
	/*
	 * VARIABLES PARA DEFINICION DE CONEXION TCP
	 */
	uint8_t bufSize[] = {2, 0, 0, 0, 0, 0, 0, 0};
	uint8_t serverIP[4] = {192, 168, 2, 192};
	char bufmsg[60];

//	uint8_t recv;				//VARIABLE QUE SE USÓ UNA VEZ PARA LO QUE SE RECIBE DEL SERVIDOR
//	uint16_t count = 0;
	/*
	 * VARIABLES QUE INTERACTUAN EN LO QUE SE VA A ENVIAR
	 * */
	int8_t _stateJoyX;
	int8_t _stateJoyY;

	uint8_t snd[3];

	/*
	 * VARIABLES QUE SE USARÍAN PARA LA CAPA INTERACTIVA DEL MODULO
	 */
//	int8_t stateTx;
//	int8_t stateRx;
//	int8_t stateSocket;
//	uint8_t stateRetarget;

	//VARIABLES DE ESTADO DE FUNCIONAMIENTO PROGRAMA
	bool estadoPi = false;


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
//  initClient(socketNum, bufSize);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  PRINT_HEADER();
  /*
   * Inicializo modulo cliente
   */
  initClient(socketNum, bufSize);
  apagaLED();
  _sirena = 0;			//LLEVARLO A OTRO LADO
  estadoP = sCLOSE;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  	  switch(estadoP){
			  case sINIT:
				  if(estadoPi == false){
					  initJoystick(&hadc1,VR);
					  prendeLED();
					  estadoPi = true;
					  estadoP = sWORK;
				  }
				  else estadoP += 1;
				  break;

			  case sFINISH:
				  finJoystick(&hadc1);
				  apagaLED();
				  estadoPi = false;
				  estadoP = sCLOSE;
				  break;


			  case sWORK:
	  //EMPIEZA 2DO SWITCH FUNCIONAMIENTO
				  __NOP();
				  if(estadoWire() == 1)	estadoP = sERROR;
				  switch(getSn_SR(socketNum)){
				  	  case SOCK_INIT:
				  		  HAL_Delay(50);
				  		  connect(socketNum, serverIP,TCP_PORT);
				  		  break;
				  	  case SOCK_ESTABLISHED:
				  		  HAL_Delay(50);
				  	  	  _stateJoyX = stateJoysticks(VR[0]);
						  _stateJoyY = stateJoysticks(VR[1]);
						  snd[0] = _stateJoyX;
						  snd[1] = _stateJoyY;
						  snd[2] = _sirena;
						  sprintf(bufmsg,"%d,%d,%d",snd[0],snd[1],snd[2]);
						  //mostrar lo que se va a enviar.
						  PRINT_STR(bufmsg);
						  send(socketNum,(uint8_t*)bufmsg,strlen(bufmsg));
						  /*
						   * Probar enviando el array entero y debuguear el servidor.
						   * note: En su momento el compilador arrojó un warning por
						   * incompatibilidad de tipo o falta de casteo. El problema
						   * es que entiendo que la funcion sprintf asigna en bufmsg
						   * valores quedando una variable "cont char .." y no un "char"
						   * comun y sivestre. Es para pensar!!
						   */

						  break;
				  	  case SOCK_CLOSE_WAIT:
				  		  HAL_Delay(50);
				  		  close(socketNum);
				  		  break;
				  	  case SOCK_CLOSED:
				  		  HAL_Delay(50);
				  		  socket(socketNum,Sn_MR_TCP,TCP_PORT,SF_TCP_NODELAY);

				  		  break;
				  }
				  break;
				  //TERMINA 2DO SWITCH DE FUNCIONAMIENTO

			  case sERROR:
				  parpadea();
				  if(estadoWire() == 0) estadoP = sWORK;
				  break;



			  case sCLOSE:
				  __NOP();
				  break;


	  	  }

	  }


    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */



}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel 
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/*
 * @brief	Funcion Callback llamada de interrupción externa. El condicional sirve
 * 			determina quien realiza la llamada. El GPIO_PIN_12 boton start/fin.
 * 			Inicia o termina proceso. El GPIO_PIN_13 es el boton que inicia sirena
 * 			en el modulo conectado por eth, osea el servidor.
 * @note	Nombro proceso a funcion que:
 * 				- Modifica Flag
 * 				- Comienza o termina muestreo ADC
 * 				- Comienza o termina transmición de datos
 * 				- Enciende o apaga Led GPIO_PIN_13
 * @param 	GPIO_Pin: Valor de PIN que llama a la interrupción
 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	/*
	 * EN LA LLAMADA A LA INTERRUPCION SE TIENE QUE PONER POCO CODIGO
	 */

	if(GPIO_Pin == GPIO_PIN_12){			//A COMPLETAR CON FUNCION, RECORDAR FLAG QUE CONDICIONA PIN_13

		toggleFlag();



	}
	//AL PRECIONAR EL BOTON DE SIRENA SE SETEA EN ACTIVO LA VARIABLE
	if(GPIO_Pin == GPIO_PIN_15){
		if(estadoP == sWORK){
			sirenaLoca();
		}
	}
}


void toggleFlag(void){
	estadoP = sINIT;
}


void prendeLED(void){
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

void apagaLED(void){
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

void translate (char *bufmsg, uint8_t *rcv){

	if(*bufmsg == 48) *rcv = 0;				// Es lo toma entero a la comparacion.
	if(*bufmsg == 49) *rcv = 1;

	/*	CODIGOS ASCII
	 * 48 = 0
	 * 49 = 1
	 */
}

void parpadea (void){
	uint8_t i =0;
	while(i < 5){
		apagaLED();
		HAL_Delay(50);
		prendeLED();
		HAL_Delay(50);
		i++;
	}
}

void sirenaLoca(void){
	switch(_sirena){
	case 0:
		_sirena = 1;
		break;
	case 1:
		_sirena = 0;
		break;
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
