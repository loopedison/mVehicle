/**
  ******************************************************************************
  * @file    bsp_syskey.h
  * @author  LoopEdison
  * @version V1.0
  * @date    12-Dec-2020
  * @brief   Function for syskey
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_SYSKEY_H
#define __BSP_SYSKEY_H

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
BSP_StatusTypeDef BSP_SYSKEY_Init(void);
bool              BSP_SYSKEY_Read(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_SYSKEY_H */

/************************ (C) COPYRIGHT LOOPEDISON *********END OF FILE********/
