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
#define KEY_2_Pin GPIO_PIN_2
#define KEY_2_GPIO_Port GPIOE
#define KEY_3_Pin GPIO_PIN_3
#define KEY_3_GPIO_Port GPIOE
#define KEY_4_Pin GPIO_PIN_4
#define KEY_4_GPIO_Port GPIOE
#define LED_1_Pin GPIO_PIN_5
#define LED_1_GPIO_Port GPIOE
#define OLED_SCL_Pin GPIO_PIN_0
#define OLED_SCL_GPIO_Port GPIOC
#define OLED_SDA_Pin GPIO_PIN_1
#define OLED_SDA_GPIO_Port GPIOC
#define A_A_Pin GPIO_PIN_9
#define A_A_GPIO_Port GPIOE
#define A_B_Pin GPIO_PIN_11
#define A_B_GPIO_Port GPIOE
#define PWM_A_Pin GPIO_PIN_13
#define PWM_A_GPIO_Port GPIOE
#define PWM_B_Pin GPIO_PIN_14
#define PWM_B_GPIO_Port GPIOE
#define SERVO_PWM_Pin GPIO_PIN_10
#define SERVO_PWM_GPIO_Port GPIOB
#define STANDBY_PWM_50HZ_Pin GPIO_PIN_11
#define STANDBY_PWM_50HZ_GPIO_Port GPIOB
#define RELAY_4_Pin GPIO_PIN_12
#define RELAY_4_GPIO_Port GPIOB
#define RELAY_3_Pin GPIO_PIN_13
#define RELAY_3_GPIO_Port GPIOB
#define RELAY_1_Pin GPIO_PIN_14
#define RELAY_1_GPIO_Port GPIOB
#define RELAY_2_Pin GPIO_PIN_15
#define RELAY_2_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_10
#define BEEP_GPIO_Port GPIOD
#define AIN2_Pin GPIO_PIN_11
#define AIN2_GPIO_Port GPIOD
#define AIN1_Pin GPIO_PIN_12
#define AIN1_GPIO_Port GPIOD
#define STBY_Pin GPIO_PIN_13
#define STBY_GPIO_Port GPIOD
#define BIN1_Pin GPIO_PIN_14
#define BIN1_GPIO_Port GPIOD
#define BIN2_Pin GPIO_PIN_15
#define BIN2_GPIO_Port GPIOD
#define SCL_6050_Pin GPIO_PIN_7
#define SCL_6050_GPIO_Port GPIOC
#define SDA_6050_Pin GPIO_PIN_8
#define SDA_6050_GPIO_Port GPIOC
#define GRAY_DAT_Pin GPIO_PIN_9
#define GRAY_DAT_GPIO_Port GPIOC
#define GRAY_CLK_Pin GPIO_PIN_8
#define GRAY_CLK_GPIO_Port GPIOA
#define B_A_Pin GPIO_PIN_15
#define B_A_GPIO_Port GPIOA
#define GRAY_8_Pin GPIO_PIN_10
#define GRAY_8_GPIO_Port GPIOC
#define GRAY_7_Pin GPIO_PIN_11
#define GRAY_7_GPIO_Port GPIOC
#define GRAY_6_Pin GPIO_PIN_12
#define GRAY_6_GPIO_Port GPIOC
#define GRAY_5_Pin GPIO_PIN_0
#define GRAY_5_GPIO_Port GPIOD
#define GRAY_4_Pin GPIO_PIN_1
#define GRAY_4_GPIO_Port GPIOD
#define GRAY_3_Pin GPIO_PIN_2
#define GRAY_3_GPIO_Port GPIOD
#define GRAY_2_Pin GPIO_PIN_3
#define GRAY_2_GPIO_Port GPIOD
#define GRAY_1_Pin GPIO_PIN_4
#define GRAY_1_GPIO_Port GPIOD
#define B_B_Pin GPIO_PIN_3
#define B_B_GPIO_Port GPIOB
#define LED_0_Pin GPIO_PIN_5
#define LED_0_GPIO_Port GPIOB
#define KEY_0_Pin GPIO_PIN_0
#define KEY_0_GPIO_Port GPIOE
#define KEY_1_Pin GPIO_PIN_1
#define KEY_1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
