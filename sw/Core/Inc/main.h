/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define RCC_OSC32_OUT_Pin GPIO_PIN_15
#define RCC_OSC32_OUT_GPIO_Port GPIOC
#define COLLUMN_1_Pin GPIO_PIN_0
#define COLLUMN_1_GPIO_Port GPIOC
#define COLLUMN_2_Pin GPIO_PIN_1
#define COLLUMN_2_GPIO_Port GPIOC
#define COLLUMN_3_Pin GPIO_PIN_2
#define COLLUMN_3_GPIO_Port GPIOC
#define COLLUMN_4_Pin GPIO_PIN_3
#define COLLUMN_4_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define COLLUMN_5_Pin GPIO_PIN_4
#define COLLUMN_5_GPIO_Port GPIOC
#define COLLUMN_6_Pin GPIO_PIN_5
#define COLLUMN_6_GPIO_Port GPIOC
#define ROW_1_Pin GPIO_PIN_6
#define ROW_1_GPIO_Port GPIOC
#define ROW_2_Pin GPIO_PIN_7
#define ROW_2_GPIO_Port GPIOC
#define ROW_3_Pin GPIO_PIN_8
#define ROW_3_GPIO_Port GPIOC
#define ROW_4_Pin GPIO_PIN_9
#define ROW_4_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define ROW_5_Pin GPIO_PIN_10
#define ROW_5_GPIO_Port GPIOC
#define ROW_6_Pin GPIO_PIN_11
#define ROW_6_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define MATRIX_SIZE 6
#define ONE_NUM_ELEMENT_ID 0
#define ONE_STATUS_ELEMENT_ID 1
#define END_ID 0xff

typedef uint8_t matrix_size_t;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
