/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define B_A_Pin GPIO_PIN_0
#define B_A_GPIO_Port GPIOA
#define B_B_Pin GPIO_PIN_1
#define B_B_GPIO_Port GPIOA
#define TIRG_1_Pin GPIO_PIN_4
#define TIRG_1_GPIO_Port GPIOA
#define TIRG_2_Pin GPIO_PIN_5
#define TIRG_2_GPIO_Port GPIOA
#define ECHO_1_Pin GPIO_PIN_6
#define ECHO_1_GPIO_Port GPIOA
#define ECHO_2_Pin GPIO_PIN_7
#define ECHO_2_GPIO_Port GPIOA
#define OLED_SCL_Pin GPIO_PIN_0
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_1
#define OLED_SDA_GPIO_Port GPIOB
#define ServoPwm_Pin GPIO_PIN_10
#define ServoPwm_GPIO_Port GPIOB
#define PWM_Pin GPIO_PIN_11
#define PWM_GPIO_Port GPIOB
#define BIN2_Pin GPIO_PIN_12
#define BIN2_GPIO_Port GPIOB
#define BIN1_Pin GPIO_PIN_13
#define BIN1_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_14
#define AIN2_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_15
#define AIN1_GPIO_Port GPIOB
#define A_A_Pin GPIO_PIN_8
#define A_A_GPIO_Port GPIOA
#define A_B_Pin GPIO_PIN_9
#define A_B_GPIO_Port GPIOA
#define PWMA_Pin GPIO_PIN_10
#define PWMA_GPIO_Port GPIOA
#define PWMB_Pin GPIO_PIN_11
#define PWMB_GPIO_Port GPIOA
#define STBY_Pin GPIO_PIN_12
#define STBY_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_15
#define BUZZER_GPIO_Port GPIOA
#define GRAY_1_Pin GPIO_PIN_3
#define GRAY_1_GPIO_Port GPIOB
#define GRAY_2_Pin GPIO_PIN_4
#define GRAY_2_GPIO_Port GPIOB
#define GRAY_3_Pin GPIO_PIN_5
#define GRAY_3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
