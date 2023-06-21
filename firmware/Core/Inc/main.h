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
#define ADC_Pin GPIO_PIN_0
#define ADC_GPIO_Port GPIOA
#define BTN_ACTIVATE_Pin GPIO_PIN_0
#define BTN_ACTIVATE_GPIO_Port GPIOB
#define BTN_ACTIVATE_EXTI_IRQn EXTI0_IRQn
#define BTN_DEACTIVATE_Pin GPIO_PIN_1
#define BTN_DEACTIVATE_GPIO_Port GPIOB
#define BTN_DEACTIVATE_EXTI_IRQn EXTI1_IRQn
#define LED_ERR_Pin GPIO_PIN_12
#define LED_ERR_GPIO_Port GPIOB
#define LED_DEACT_Pin GPIO_PIN_13
#define LED_DEACT_GPIO_Port GPIOB
#define LED_ACT_Pin GPIO_PIN_14
#define LED_ACT_GPIO_Port GPIOB
#define RELAY_Pin GPIO_PIN_3
#define RELAY_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
