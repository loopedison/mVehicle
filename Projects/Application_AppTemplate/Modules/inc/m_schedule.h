/**
  ******************************************************************************
  * @file    schedule.h
  * @author  LoopEdison
  * @version V1.0
  * @date    18-Dec-2020
  * @brief   schedule module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SCHEDULE_H
#define __SCHEDULE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Schedule_Init(void);
void Schedule_Task(void const * argument);
void Schedule_TICKCallBack(void);


#ifdef __cplusplus
}
#endif

#endif /* __SCHEDULE_H */

/************************ (C) COPYRIGHT LOOPEDISON *********END OF FILE********/
