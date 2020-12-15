/**
  ******************************************************************************
  * @file    bsp_sysled.h
  * @author  LoopEdison
  * @version V1.0
  * @date    12-Dec-2020
  * @brief   Function for sysled
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_SYSLED_H
#define __BSP_SYSLED_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "bsp_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
BSP_StatusTypeDef BSP_SYSLED_Init(void);
BSP_StatusTypeDef BSP_SYSLED_TurnOff(void);
BSP_StatusTypeDef BSP_SYSLED_TurnOn(void);
BSP_StatusTypeDef BSP_SYSLED_Toggle(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_SYSLED_H */

/************************ (C) COPYRIGHT LOOPEDISON *********END OF FILE********/
