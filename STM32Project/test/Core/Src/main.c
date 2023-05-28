/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
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
int a = 2;
char data;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/*
舵机控制函数：
返回值：无		参数：float类型的占空比值x%
注：
	7占空比的时候大概在中间位置，舵机使用的是 TIM_1的Channel_1 -> PE9
*/
void ServoControl(float duty_cycle)
{
	int pwm = 0;
	
	if(duty_cycle < 2.5)	//限制舵机PWM范围为20%-12.5%占空比，超出按照极限值算
	{
		duty_cycle = 2.5;
	}
	else if(duty_cycle > 12.5)
	{
		duty_cycle = 12.5;
	}

	pwm = (duty_cycle /100) * 20000.0;		//换算为pwm数值，计数值为20000
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
}

/*
电机控制函数：
返回值：无		参数：int类型的左右电机选择	0->左电机 1->右电机
									int类型的前进后退或停止选择	0->前进	1->后退 2->停止
									float类型的占空比值x%
注：
	左电机pwmA口 -> TIM_1的Channel_2 -> PE11
	右电机pwmB口 -> TIM_1的Channel_3 -> PE13
	AIN1 -> PF0		10
	AIN2 -> PF1
	BIN1 -> PF2		10
	BIN2 -> PF3
	STBY -> PF4
*/
void MotorControl(int left_or_right, int direction, float duty_cycle)
{
	int pwm = 0;
	
	if(duty_cycle < 0)	//限制舵机PWM范围为0%-100%占空比，超出按照极限值算
	{
		duty_cycle = 0;
	}
	else if(duty_cycle > 100)
	{
		duty_cycle = 100;
	}
	pwm = (duty_cycle /100) * 20000.0;		//换算为pwm数值，计数值为20000
	
	
	if(left_or_right == 0)	//控制左 或者 右电机 0->左电机 1->右电机
	{
		if(direction == 0)//控制电机前进后退或停止	0->前进	1->后退 2->停止
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
		}
		else if(direction == 1)
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
		}
		else if(direction == 2)
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_RESET);
		}
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm);
		
		}
	else
	{
		if(direction == 0)//控制电机前进后退或停止	0->前进	1->后退 2->停止
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
		}
		else if(direction == 1)
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
		}
		else if(direction == 2)
		{
			HAL_GPIO_WritePin(STBY_GPIO_Port, STBY_Pin, GPIO_PIN_RESET);
		}

		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm);
	}
	
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*
重定向printf和scanf函数，需引用<stdio.h>并且在设置中勾选USE MicroLib
*/
int fputc(int ch, FILE *f)
{
	uint8_t temp[1] = {ch};
	HAL_UART_Transmit(&huart1, temp, 1, 0xffff);
	return ch;
}

/*
int fgetc(FILE * f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1,&ch, 1, 0xffff);
  return ch;
}
*/

//重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
//int fgetc(FILE *f)
//{
//		/* 等待串口输入数据 */
//		while (USART_GetFlagStatus(&huart1, USART_FLAG_RXNE) == RESET);
//		//DEBUG_USARTx改成你想用的USART端口
//		return (int)USART_ReceiveData(&huart1);
//		//DEBUG_USARTx改成你想用的USART端口
//}

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
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); //开启TIM1 CHANNEL_1的PWM	舵机
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); //开启TIM1 CHANNEL_2的PWM	左电机
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3); //开启TIM1 CHANNEL_3的PWM		右电机
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//		data = getchar();
//		printf("data is %c\n", data);
		
		/*
		进库
		*/
		HAL_Delay(1000);
		ServoControl(100);
		HAL_Delay(3000);
		MotorControl(0, 1, 100);
		MotorControl(1, 1, 100);
		
		HAL_Delay(500);
		
		MotorControl(0, 2, 0);
		MotorControl(1, 2, 0);
		HAL_Delay(1000);
		ServoControl(7);
		
		HAL_Delay(1000);
		
		MotorControl(0, 1, 100);
		MotorControl(1, 1, 100);
		
		HAL_Delay(150);
		
		MotorControl(0, 2, 0);
		MotorControl(1, 2, 0);
		
		
		/*
		
		出库1
		
		*/
		HAL_Delay(2000);
		
		MotorControl(0, 0, 100);
		MotorControl(1, 0, 100);
		HAL_Delay(110);
		MotorControl(0, 2, 0);
		MotorControl(1, 2, 0);
		HAL_Delay(1000);
		
		ServoControl(100);
		HAL_Delay(1000);
		MotorControl(0, 0, 100);
		MotorControl(1, 0, 100);
		HAL_Delay(500);
		
		MotorControl(0, 2, 0);
		MotorControl(1, 2, 0);
		HAL_Delay(1000);
		ServoControl(7);
		
					
		//停车
		MotorControl(0,2,0);
		MotorControl(1,2,0);
		HAL_Delay(1000);
		ServoControl(7);
		HAL_Delay(1000);

		
		break;
		
		
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
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

  /** Initializes the CPU, AHB and APB buses clocks
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
