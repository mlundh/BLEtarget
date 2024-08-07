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
#include "stm32wbxx_hal.h"
#include "app_conf.h"
#include "app_entry.h"
#include "app_common.h"

#include "stm32wbxx_ll_tim.h"
#include "stm32wbxx_ll_bus.h"
#include "stm32wbxx_ll_cortex.h"
#include "stm32wbxx_ll_rcc.h"
#include "stm32wbxx_ll_system.h"
#include "stm32wbxx_ll_utils.h"
#include "stm32wbxx_ll_pwr.h"
#include "stm32wbxx_ll_gpio.h"
#include "stm32wbxx_ll_dma.h"

#include "stm32wbxx_ll_exti.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define LOG

#ifdef DEBUG
#define LOG_DBG_LENGTH_MAX (80)
#define LOG_DBG_ENTRY(format, ...) {  \
    char message[LOG_DBG_LENGTH_MAX] = {0};\
    snprintf((char*)message, LOG_DBG_LENGTH_MAX, "DBG "format"\r\n" , ##__VA_ARGS__);\
    uint32_t buffSize = strlen(message)+1;\
    CDC_Transmit_FS((uint8_t*)message, buffSize);\
    }
#else
#define LOG_DBG_ENTRY(evHandler, format, ...)
#endif

#ifdef LOG
#define LOG_LENGTH_MAX (80)
#define LOG_ENTRY(format, ...) {  \
    char message[LOG_LENGTH_MAX] = {0};\
    snprintf((char*)message, LOG_LENGTH_MAX, "LOG "format"\r\n" , ##__VA_ARGS__);\
    uint32_t buffSize = strlen(message)+1;\
    CDC_Transmit_FS((uint8_t*)message, buffSize);\
    }
#else
#define LOG_DBG_ENTRY(evHandler, format, ...)
#endif

#define ERROR_LENGTH_MAX (80)
#define ERROR_ENTRY(format, ...) {  \
    char message[ERROR_LENGTH_MAX] = {0};\
    snprintf((char*)message, ERROR_LENGTH_MAX, "ERROR "format"\r\n" , ##__VA_ARGS__);\
    uint32_t buffSize = strlen(message)+1;\
    CDC_Transmit_FS((uint8_t*)message, buffSize);\
    }
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CH_B_Pin GPIO_PIN_14
#define CH_B_GPIO_Port GPIOC
#define CH_B_EXTI_IRQn EXTI15_10_IRQn
#define CH_C_Pin GPIO_PIN_15
#define CH_C_GPIO_Port GPIOC
#define CH_C_EXTI_IRQn EXTI15_10_IRQn
#define BOOT_Pin GPIO_PIN_3
#define BOOT_GPIO_Port GPIOH
#define CH_1_Pin GPIO_PIN_0
#define CH_1_GPIO_Port GPIOA
#define CH_1_EXTI_IRQn EXTI0_IRQn
#define CH_2_Pin GPIO_PIN_1
#define CH_2_GPIO_Port GPIOA
#define CH_2_EXTI_IRQn EXTI1_IRQn
#define CH_3_Pin GPIO_PIN_2
#define CH_3_GPIO_Port GPIOA
#define CH_3_EXTI_IRQn EXTI2_IRQn
#define CH_4_Pin GPIO_PIN_3
#define CH_4_GPIO_Port GPIOA
#define CH_4_EXTI_IRQn EXTI3_IRQn
#define CH_5_Pin GPIO_PIN_4
#define CH_5_GPIO_Port GPIOA
#define CH_5_EXTI_IRQn EXTI4_IRQn
#define CH_6_Pin GPIO_PIN_5
#define CH_6_GPIO_Port GPIOA
#define CH_6_EXTI_IRQn EXTI9_5_IRQn
#define CH_7_Pin GPIO_PIN_6
#define CH_7_GPIO_Port GPIOA
#define CH_7_EXTI_IRQn EXTI9_5_IRQn
#define CH_8_Pin GPIO_PIN_7
#define CH_8_GPIO_Port GPIOA
#define CH_8_EXTI_IRQn EXTI9_5_IRQn
#define LED_Pin GPIO_PIN_10
#define LED_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
