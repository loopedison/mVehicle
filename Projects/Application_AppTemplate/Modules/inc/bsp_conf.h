/**
  ******************************************************************************
  * @file    bsp_conf.h
  * @author  LoopEdison
  * @version V1.0
  * @date    12-Dec-2020
  * @brief   Config for BSP
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_CONF_H
#define __BSP_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define USE_BSP_ASSERT    (1)

/* Exported functions ------------------------------------------------------- */
#define BSP_UART1_MODULE_ENABLED
#define BSP_SYSLED_MODULE_ENABLED
#define BSP_SYSKEY_MODULE_ENABLED

/* Module Configure --------------------------------------------------------- */
#ifdef BSP_UART1_MODULE_ENABLED
  #include "bsp_uart1.h"
  #define BSP_UART1_USING_INT           (1)
  #define BSP_UART1_USING_DMA           (1)
  #define BSP_UART1_DEFAULT_BAUDRATE    (115200)
  #define BSP_UART1_DEFAULT_PRIO        (6)
  #define BSP_UART1_DMA_RX_PRIO         (6)
  #define BSP_UART1_DMA_TX_PRIO         (6)
#endif /* BSP_UART1_MODULE_ENABLED */

#ifdef BSP_SYSLED_MODULE_ENABLED
  #include "bsp_sysLed.h"
  #define BSP_SYSLED_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOC_CLK_ENABLE()
  #define BSP_SYSLED_GPIO_PORT          (GPIOC)
  #define BSP_SYSLED_GPIO_PIN           (GPIO_PIN_13)
#endif /* BSP_SYSLED_MODULE_ENABLED */

#ifdef BSP_SYSKEY_MODULE_ENABLED
  #include "bsp_syskey.h"
  #define BSP_SYSKEY_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
  #define BSP_SYSKEY_GPIO_PORT          (GPIOA)
  #define BSP_SYSKEY_GPIO_PIN           (GPIO_PIN_0)
#endif /* BSP_SYSKEY_MODULE_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* __BSP_CONF_H */

/************************ (C) COPYRIGHT LOOPEDISON *********END OF FILE********/
