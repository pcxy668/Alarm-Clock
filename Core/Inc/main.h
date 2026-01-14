/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#define BUZZER_EN_Pin GPIO_PIN_1
#define BUZZER_EN_GPIO_Port GPIOA
#define CHRGT_Pin GPIO_PIN_2
#define CHRGT_GPIO_Port GPIOA
#define CHRG_Pin GPIO_PIN_3
#define CHRG_GPIO_Port GPIOA
#define ALARM_SET_Pin GPIO_PIN_6
#define ALARM_SET_GPIO_Port GPIOA
#define ALARM_EN_Pin GPIO_PIN_7
#define ALARM_EN_GPIO_Port GPIOA
#define UP_Pin GPIO_PIN_0
#define UP_GPIO_Port GPIOB
#define DOWN_Pin GPIO_PIN_1
#define DOWN_GPIO_Port GPIOB
#define TIME_SET_Pin GPIO_PIN_2
#define TIME_SET_GPIO_Port GPIOB
#define OLED_ON_Pin GPIO_PIN_10
#define OLED_ON_GPIO_Port GPIOB
#define LIGHT_Pin GPIO_PIN_11
#define LIGHT_GPIO_Port GPIOB
#define TOUCH_Pin GPIO_PIN_14
#define TOUCH_GPIO_Port GPIOB
#define DS18B20_DATA_Pin GPIO_PIN_15
#define DS18B20_DATA_GPIO_Port GPIOB
#define ALARM_5DAY_Pin GPIO_PIN_8
#define ALARM_5DAY_GPIO_Port GPIOA
#define MIC_Pin GPIO_PIN_12
#define MIC_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
