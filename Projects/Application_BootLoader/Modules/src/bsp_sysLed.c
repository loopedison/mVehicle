/**
  ******************************************************************************
  * @file    bsp_sysled.c
  * @author  LoopEdison
  * @version V1.0
  * @date    12-Dec-2020
  * @brief   Function for sysled
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

#ifdef BSP_SYSLED_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* External function prototypes -----------------------------------------------*/
/* Export variables ----------------------------------------------------------*/
/* Export function prototypes ------------------------------------------------*/

//==============================================================================
/**
  * @brief  Initial sysled
  * @param  none: 
  * @retval BSP_OK    : normal
  */
BSP_StatusTypeDef BSP_SYSLED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* GPIO Ports Clock Enable */
  BSP_SYSLED_GPIO_CLK_ENABLE();
  /*Configure GPIO pins */
  GPIO_InitStruct.Pin = BSP_SYSLED_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BSP_SYSLED_GPIO_PORT, &GPIO_InitStruct);
  
  HAL_GPIO_WritePin(BSP_SYSLED_GPIO_PORT, BSP_SYSLED_GPIO_PIN, GPIO_PIN_SET);
  
  return (BSP_OK);
}

//==============================================================================
/**
  * @brief  Turn OFF sysled
  * @param  None: 
  * @retval BSP_OK    : normal
  */
BSP_StatusTypeDef BSP_SYSLED_TurnOff(void)
{
  HAL_GPIO_WritePin(BSP_SYSLED_GPIO_PORT, BSP_SYSLED_GPIO_PIN, GPIO_PIN_SET);
  return (BSP_OK);
}

//==============================================================================
/**
  * @brief  Turn ON sysled
  * @param  None: 
  * @retval BSP_OK    : normal
  */
BSP_StatusTypeDef BSP_SYSLED_TurnOn(void)
{
  HAL_GPIO_WritePin(BSP_SYSLED_GPIO_PORT, BSP_SYSLED_GPIO_PIN, GPIO_PIN_RESET);
  return (BSP_OK);
}

//==============================================================================
/**
  * @brief  Toggle sysled
  * @param  None: 
  * @retval BSP_OK    : normal
  */
BSP_StatusTypeDef BSP_SYSLED_Toggle(void)
{
  HAL_GPIO_TogglePin(BSP_SYSLED_GPIO_PORT, BSP_SYSLED_GPIO_PIN);
  return (BSP_OK);
}


#endif /* BSP_SYSLED_MODULE_ENABLED */

/************************ (C) COPYRIGHT LOOPEDISON *********END OF FILE********/
