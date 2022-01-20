/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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

#include "bme680.h"
#include "bsec_integration.h"
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
int8_t i2cWrite(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);
int8_t i2cRead(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);
void bsec_output(int64_t timestamp, float iaq, uint8_t iaq_accuracy, float temp, float raw_temp, float raw_pressure, float humidity, float raw_humidity, float raw_gas,
                 float static_iaq, uint8_t static_iaq_accuracy, float co2_equivalent, uint8_t co2_accuracy, float breath_voc_equivalent,
                 uint8_t breath_voc_accuracy, float comp_gas_value, uint8_t comp_gas_accuracy,float gas_percentage, uint8_t gas_percentage_accuracy);
int64_t get_timestamp_us (void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BME680_LED_Pin GPIO_PIN_5
#define BME680_LED_GPIO_Port GPIOD
#define RTC_LED_Pin GPIO_PIN_3
#define RTC_LED_GPIO_Port GPIOK
#define RENDER_TIME_Pin GPIO_PIN_4
#define RENDER_TIME_GPIO_Port GPIOD
#define VSYNC_FREQ_Pin GPIO_PIN_6
#define VSYNC_FREQ_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
