/**
  ******************************************************************************
  * @file    schedule.c
  * @author  LoopEdison
  * @version V1.0
  * @date    18-Dec-2020
  * @brief   schedule module
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"
#include "config.h"

/* Includes ------------------------------------------------------------------*/
#include "m_schedule.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SCHEDULE_TICK         (1)   //ms
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Schedule_Init(void);
void Schedule_Task(void const * argument);
/* Private functions ---------------------------------------------------------*/

//==============================================================================
/**
  * @brief  Schedule Init
  * @param  None 
  * @retval None 
  */
void Schedule_Init(void)
{
  /* initial all the drivers and modules */
  /* Default settings */
}

//==============================================================================
/**
  * @brief  Schedule Task
  * @param  argument 
  * @retval None 
  */
void Schedule_Task(void const * argument)
{
  static uint32_t tickNew=0, tickLst=0;
  tickNew = HAL_GetTick();
  if(tickNew - tickLst >= SCHEDULE_TICK)
  {
    /* Update tick */
    tickLst = tickNew;
    /* ----------- */
  }
}

//==============================================================================
/**
  * @brief  Schedule TICK callback.
  * @param  None
  * @retval None
  */
void Schedule_TICKCallBack(void)
{
}


/************************ (C) COPYRIGHT LOOPEDISON *********END OF FILE********/
