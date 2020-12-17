/**
  ******************************************************************************
  * @file    bsp_syskey.h
  * @author  LoopEdison
  * @version V1.0
  * @date    12-Dec-2020
  * @brief   Function for syskey
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"

#ifdef BSP_SYSKEY_MODULE_ENABLED

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
  * @brief  Initial syskey
  * @param  none: 
  * @retval BSP_OK    : normal
  */
BSP_StatusTypeDef BSP_SYSKEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* GPIO Ports Clock Enable */
  BSP_SYSKEY_GPIO_CLK_ENABLE();
  /*Configure GPIO pins */
  GPIO_InitStruct.Pin = BSP_SYSKEY_GPIO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BSP_SYSKEY_GPIO_PORT, &GPIO_InitStruct);
  
  HAL_GPIO_WritePin(BSP_SYSKEY_GPIO_PORT, BSP_SYSKEY_GPIO_PIN, GPIO_PIN_SET);
  
  return (BSP_OK);
}

//==============================================================================
/**
  * @brief  sys key state
  * @param  None: 
  * @retval 
  */
bool BSP_SYSKEY_Read(void)
{
  return (HAL_GPIO_ReadPin(BSP_SYSKEY_GPIO_PORT, BSP_SYSKEY_GPIO_PIN) == GPIO_PIN_RESET);
}

#endif /* BSP_SYSKEY_MODULE_ENABLED */

/************************ (C) COPYRIGHT LOOPEDISON *********END OF FILE********/
