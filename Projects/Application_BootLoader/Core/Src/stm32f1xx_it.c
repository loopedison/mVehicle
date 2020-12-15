/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @author  LoopEdison
  * @version V1.0
  * @date    12-Dec-2020
  * @brief   Interrupt Handler
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"
#include "bsp.h"

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

//==============================================================================
/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  while (1)
  {
  }
}

//==============================================================================
/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  while (1)
  {
  }
}

//==============================================================================
/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  while (1)
  {
  }
}

//==============================================================================
/**
* @brief This function handles Prefetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  while (1)
  {
  }
}

//==============================================================================
/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

//==============================================================================
/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
}

//==============================================================================
/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
}

//==============================================================================
/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
}

//==============================================================================
/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/


//==============================================================================
//==============================================================================

/************************ (C) COPYRIGHT LOOPEDISON *********END OF FILE********/
