/**
  ******************************************************************************
  * @file    superled.h
  * @author  LoopEdison
  * @version V1.0
  * @date    12-Dec-2020
  * @brief   superled module
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SUPERLED_H
#define __SUPERLED_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Exported types ------------------------------------------------------------*/
#define SUPERLED_TICK_PERIOD      (1)

typedef enum {
  SUPERLED_OK              = 0X0,
  SUPERLED_ERROR           = 0X1,
}SuperLed_StatusTypeDef;

#define SUPERLED_MSG_LEN          (16)
#define SUPERLED_PRIO_DEFAULT     (0)
#define SUPERLED_COUNTER_DEFAULT  (1)
#define SUPERLED_COUNTER_MAX      ((uint32_t)(-1))
typedef int32_t SLED_MsgDef[SUPERLED_MSG_LEN];
typedef uint32_t SuperLed_IdDef;
typedef struct
{
  SuperLed_IdDef          uId;
  uint32_t                priority;
  uint32_t                counter;
  SLED_MsgDef             message;
}SuperLed_QItemDef;


/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SuperLed_Init(void);
void SuperLed_Task(void const * argument);
SuperLed_StatusTypeDef SuperLed_Display(SuperLed_QItemDef *pLed);
SuperLed_StatusTypeDef SuperLed_Remove(SuperLed_QItemDef *pLed);


#ifdef __cplusplus
}
#endif

#endif /* __SUPERLED_H */

/************************ (C) COPYRIGHT LOOPEDISON *********END OF FILE********/
