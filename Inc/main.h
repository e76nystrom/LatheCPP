/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#define Dbg8_Pin GPIO_PIN_2
#define Dbg8_GPIO_Port GPIOE
#define Logic1_Pin GPIO_PIN_3
#define Logic1_GPIO_Port GPIOE
#define ExtInt_Pin GPIO_PIN_4
#define ExtInt_GPIO_Port GPIOE
#define ExtInt_EXTI_IRQn EXTI4_IRQn
#define JogA1_Pin GPIO_PIN_5
#define JogA1_GPIO_Port GPIOE
#define JogA1_EXTI_IRQn EXTI9_5_IRQn
#define JogB2_Pin GPIO_PIN_6
#define JogB2_GPIO_Port GPIOE
#define JogB2_EXTI_IRQn EXTI9_5_IRQn
#define XFlag_Pin GPIO_PIN_13
#define XFlag_GPIO_Port GPIOC
#define ZFlag_Pin GPIO_PIN_15
#define ZFlag_GPIO_Port GPIOC
#define Dbg5_Pin GPIO_PIN_2
#define Dbg5_GPIO_Port GPIOC
#define Dbg0_Pin GPIO_PIN_0
#define Dbg0_GPIO_Port GPIOA
#define Step2a_Pin GPIO_PIN_1
#define Step2a_GPIO_Port GPIOA
#define Encoder_Pin GPIO_PIN_2
#define Encoder_GPIO_Port GPIOA
#define Dbg2_Pin GPIO_PIN_3
#define Dbg2_GPIO_Port GPIOA
#define Dbg1_Pin GPIO_PIN_4
#define Dbg1_GPIO_Port GPIOA
#define Index_Pin GPIO_PIN_0
#define Index_GPIO_Port GPIOB
#define Index_EXTI_IRQn EXTI0_IRQn
#define Dbg4_Pin GPIO_PIN_1
#define Dbg4_GPIO_Port GPIOB
#define JogA2_Pin GPIO_PIN_8
#define JogA2_GPIO_Port GPIOE
#define JogA2_EXTI_IRQn EXTI9_5_IRQn
#define Pin15_Pin GPIO_PIN_9
#define Pin15_GPIO_Port GPIOE
#define Dbg9_Pin GPIO_PIN_10
#define Dbg9_GPIO_Port GPIOE
#define Pin13_Pin GPIO_PIN_11
#define Pin13_GPIO_Port GPIOE
#define Dir2_Pin GPIO_PIN_12
#define Dir2_GPIO_Port GPIOE
#define XB_Pin GPIO_PIN_13
#define XB_GPIO_Port GPIOE
#define XB_EXTI_IRQn EXTI15_10_IRQn
#define Step2b_Pin GPIO_PIN_14
#define Step2b_GPIO_Port GPIOE
#define XA_Pin GPIO_PIN_15
#define XA_GPIO_Port GPIOE
#define XA_EXTI_IRQn EXTI15_10_IRQn
#define Step1_Pin GPIO_PIN_10
#define Step1_GPIO_Port GPIOB
#define Dir1_Pin GPIO_PIN_12
#define Dir1_GPIO_Port GPIOB
#define Pin16_Pin GPIO_PIN_14
#define Pin16_GPIO_Port GPIOB
#define Pin12_Pin GPIO_PIN_15
#define Pin12_GPIO_Port GPIOB
#define Dir3_Pin GPIO_PIN_8
#define Dir3_GPIO_Port GPIOD
#define Pin11_Pin GPIO_PIN_9
#define Pin11_GPIO_Port GPIOD
#define Dir4_Pin GPIO_PIN_10
#define Dir4_GPIO_Port GPIOD
#define Pin10_Pin GPIO_PIN_11
#define Pin10_GPIO_Port GPIOD
#define ZA_Pin GPIO_PIN_12
#define ZA_GPIO_Port GPIOD
#define ZA_EXTI_IRQn EXTI15_10_IRQn
#define Step4_Pin GPIO_PIN_13
#define Step4_GPIO_Port GPIOD
#define ZB_Pin GPIO_PIN_14
#define ZB_GPIO_Port GPIOD
#define ZB_EXTI_IRQn EXTI15_10_IRQn
#define Index1_Pin GPIO_PIN_15
#define Index1_GPIO_Port GPIOD
#define RemTx_Pin GPIO_PIN_6
#define RemTx_GPIO_Port GPIOC
#define RemRx_Pin GPIO_PIN_7
#define RemRx_GPIO_Port GPIOC
#define Dir5_Pin GPIO_PIN_8
#define Dir5_GPIO_Port GPIOC
#define Step5_Pin GPIO_PIN_9
#define Step5_GPIO_Port GPIOC
#define Pin17_Pin GPIO_PIN_8
#define Pin17_GPIO_Port GPIOA
#define Dbg3_Pin GPIO_PIN_15
#define Dbg3_GPIO_Port GPIOA
#define SPI_SCK_Pin GPIO_PIN_10
#define SPI_SCK_GPIO_Port GPIOC
#define SPI_MISO_Pin GPIO_PIN_11
#define SPI_MISO_GPIO_Port GPIOC
#define DbgTx_Pin GPIO_PIN_12
#define DbgTx_GPIO_Port GPIOC
#define Pin14_Pin GPIO_PIN_1
#define Pin14_GPIO_Port GPIOD
#define DbgRx_Pin GPIO_PIN_2
#define DbgRx_GPIO_Port GPIOD
#define Pin1_Pin GPIO_PIN_3
#define Pin1_GPIO_Port GPIOD
#define SPI_SEL_Pin GPIO_PIN_6
#define SPI_SEL_GPIO_Port GPIOD
#define JogB1_Pin GPIO_PIN_7
#define JogB1_GPIO_Port GPIOD
#define JogB1_EXTI_IRQn EXTI9_5_IRQn
#define Step3_Pin GPIO_PIN_4
#define Step3_GPIO_Port GPIOB
#define SPI_MOSI_Pin GPIO_PIN_5
#define SPI_MOSI_GPIO_Port GPIOB
#define I2C_SCL_Pin GPIO_PIN_6
#define I2C_SCL_GPIO_Port GPIOB
#define Dbg10_Pin GPIO_PIN_7
#define Dbg10_GPIO_Port GPIOB
#define Dbg11_Pin GPIO_PIN_8
#define Dbg11_GPIO_Port GPIOB
#define I2C_SDA_Pin GPIO_PIN_9
#define I2C_SDA_GPIO_Port GPIOB
#define Dbg6_Pin GPIO_PIN_0
#define Dbg6_GPIO_Port GPIOE
#define Dbg7_Pin GPIO_PIN_1
#define Dbg7_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
