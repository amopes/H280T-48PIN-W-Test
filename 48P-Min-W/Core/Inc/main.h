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
#include "stm32f4xx_hal.h"

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
#define DI3_T9CH1_Pin GPIO_PIN_5
#define DI3_T9CH1_GPIO_Port GPIOE
#define DI2_T9CH2_Pin GPIO_PIN_6
#define DI2_T9CH2_GPIO_Port GPIOE
#define LED0_PE7_Pin GPIO_PIN_7
#define LED0_PE7_GPIO_Port GPIOE
#define LED1_PE8_Pin GPIO_PIN_8
#define LED1_PE8_GPIO_Port GPIOE
#define LED2_PE10_Pin GPIO_PIN_10
#define LED2_PE10_GPIO_Port GPIOE
#define DI1_PD10_Pin GPIO_PIN_10
#define DI1_PD10_GPIO_Port GPIOD
#define DI0_PD11_Pin GPIO_PIN_11
#define DI0_PD11_GPIO_Port GPIOD
#define DI4_PD3_Pin GPIO_PIN_3
#define DI4_PD3_GPIO_Port GPIOD
#define DI5_PD4_Pin GPIO_PIN_4
#define DI5_PD4_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
