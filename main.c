/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#define A LL_GPIO_PIN_0
#define B LL_GPIO_PIN_1
#define C LL_GPIO_PIN_2
#define D LL_GPIO_PIN_3
#define E LL_GPIO_PIN_4
#define F LL_GPIO_PIN_5
#define G LL_GPIO_PIN_6
#define DP LL_GPIO_PIN_7

#define P1 LL_GPIO_PIN_8
#define P2 LL_GPIO_PIN_9
#define P3 LL_GPIO_PIN_10
#define P4 LL_GPIO_PIN_11

int a = 0;
int pushes = 0;
int push_flag = 0;
int count = 0;
int c = 0;
int b = 0;
int d = 1;
uint32_t digit[10] = {
		A|B|C|D|E|F,   //0
		B|C,		   //1
		A|B|G|E|D,     //2
		A|B|C|D|G,     //3
		B|C|F|G,       //4
		A|F|G|C|D,     //5
		A|F|G|C|D|E,   //6
		A|B|C,         //7
		A|B|C|D|E|F|G, //8
		A|B|C|D|F|G    //9
};

uint32_t dplace [4] = {
		P2|P3|P4,
		P3|P4|P1,
		P2|P4|P1,
		P3|P2|P1,
};
//Отображение цифр
void numer (int n) {
	uint32_t port_B = 0;
	int n1, n2, n3, n4;
	n1 = n%10;
	n2 = ((n-n1)%100)/10;
	n3 = ((n-n1-n2)%1000)/100;
	n4 = (n-n1-n2-n3)/1000;
	int dig [4] = {n4, n3, n2, n1};

	for (int i = 3; i>=0;--i) {
//First variant (более медленный вариант, равномерная яркость)
//		if (i == 0 && dig[0] != 0) {
//				LL_GPIO_SetOutputPin(GPIOB, digit[dig[0]]|dplace[0]);
//				}
//		if (i == 1 && (dig[1]!= 0 | dig[0]!= 0)) {
//				LL_GPIO_SetOutputPin(GPIOB, digit[dig[1]]|dplace[1]);
//				}
//		if (i == 2 && (dig[2]!= 0 | dig[1]!= 0)) {
//				LL_GPIO_SetOutputPin(GPIOB, digit[dig[2]]|dplace[2]);
//				}
//		if (i == 3) {
//				LL_GPIO_SetOutputPin(GPIOB, digit[dig[3]]|dplace[3]);
//				}
//		HAL_Delay(1);
//		LL_GPIO_WriteOutputPort(GPIOB, 0);
// Second variant (сразу весь порт, быстро, но яркость неравномерная)
		if (i == 0 && dig[0] != 0) {
			port_B = digit[dig[0]]|dplace[0];
				}
		if (i == 1 && (dig[1]!= 0 | dig[0]!= 0)) {
			port_B = digit[dig[1]]|dplace[1];
				}
		if (i == 2 && (dig[2]!= 0 | dig[1]!= 0)) {
			port_B = digit[dig[2]]|dplace[2];
				}
		if (i == 3) {
			port_B = digit[dig[3]]|dplace[3];
				}
		LL_GPIO_WriteOutputPort(GPIOB, port_B);
		HAL_Delay(1); //больше времени на засветку, чтобы цифры успевали загораться)
    }
}

int button () {
	uint32_t b_flag1 = 0; //флаг нажатой кнопки
	uint32_t b_clk = 0;
	int loong = 0; //длинное нажатие
	for (int i=0; i<1000; ++i){


	while (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0)) {
		b_flag1 = 1;
		b_clk = 0;
		++loong; //считаем цикл для определения длинного нажатия
		if (loong > 100){
				return 3;  //длинное нажатие
			}
		HAL_Delay(10);
	}

	if (b_flag1) { //антидребезг
	    b_clk++;
	    HAL_Delay(10);
	}

	if (b_clk >= 5) { //досчитали цикл антидребезга
		HAL_Delay (50); //мин. разрыв между нажатиями
	    for (int k = 0; k<100000; ++k){
	    if(LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0)) { //ждем второе нажатие
		return 2; //двойное нажатие
	}
	}
		return 1;//короткое нажатие

	}
	}
return 0; //нет нажатия
}

//int gLed_State = 0;
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void Digit (int d) {

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {

	 a = button();
	 if (a != 0) {
	 		push_flag = a;
	 	}

//Счетчик нажатий
//	if (a == 1) {
//		++pushes;
//	}
//	numer(pushes);
//Автосчетчик
	 if(a == 3) {  //если длинное нажатие
		 numer(0); //показываем, что обнулилось
		 HAL_Delay(1000); //время, чтобы отпустить кнопку (иначе засчитается еще и короткое нажатие)
	 }
	 if (a == 2) { //пришло двойное нажатие
		 HAL_Delay(500);  //выжидаем прекращение нажима (иначе засчитается еще и короткое нажатие
	 }
	 if(a==1) { //пришло короткое нажатие, ставим флаг 1 или 2 для старта и остановки соответственно
		 if (c <=1) {
			 c++;
		 }
		 else {
			 c--;
		 }
	 }
	 if(a==2) { //пришло двойное нажатие, ставим флаг 1 или 2 для прямого и обратного хода
	 		 if (d == 1) {
	 			 d++;
	 		 }
	 		 else {
	 			 d--;
	 		 }
	 	 }

	if (d == 1 && c == 1 && count < 9999) {
		count++;
	}
	if (d == 2 && c == 1 && count > 0) {
		count--;
	}
	if (push_flag == 3) {
		count = 0;
	}

	 numer(count);







    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

  /**/
  LL_GPIO_ResetOutputPin(A_GPIO_Port, A_Pin);

  /**/
  LL_GPIO_ResetOutputPin(B_GPIO_Port, B_Pin);

  /**/
  LL_GPIO_ResetOutputPin(C_GPIO_Port, C_Pin);

  /**/
  LL_GPIO_ResetOutputPin(P3_GPIO_Port, P3_Pin);

  /**/
  LL_GPIO_ResetOutputPin(P4_GPIO_Port, P4_Pin);

  /**/
  LL_GPIO_ResetOutputPin(bLed_GPIO_Port, bLed_Pin);

  /**/
  LL_GPIO_ResetOutputPin(gLed_GPIO_Port, gLed_Pin);

  /**/
  LL_GPIO_ResetOutputPin(D_GPIO_Port, D_Pin);

  /**/
  LL_GPIO_ResetOutputPin(E_GPIO_Port, E_Pin);

  /**/
  LL_GPIO_ResetOutputPin(F_GPIO_Port, F_Pin);

  /**/
  LL_GPIO_ResetOutputPin(G_GPIO_Port, G_Pin);

  /**/
  LL_GPIO_ResetOutputPin(DP_GPIO_Port, DP_Pin);

  /**/
  LL_GPIO_ResetOutputPin(P1_GPIO_Port, P1_Pin);

  /**/
  LL_GPIO_ResetOutputPin(P2_GPIO_Port, P2_Pin);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE0);

  /**/
  LL_GPIO_SetPinPull(bButton_GPIO_Port, bButton_Pin, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinMode(bButton_GPIO_Port, bButton_Pin, LL_GPIO_MODE_INPUT);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_0;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  GPIO_InitStruct.Pin = A_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(A_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = B_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(B_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = C_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(C_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = P3_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(P3_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = P4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(P4_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = bLed_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(bLed_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = gLed_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(gLed_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = D_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(D_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = E_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(E_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = F_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(F_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = G_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(G_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = DP_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(DP_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = P1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(P1_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = P2_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(P2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
