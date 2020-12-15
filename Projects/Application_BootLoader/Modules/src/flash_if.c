/**
  ******************************************************************************
  * @file    flash_if.c 
  * @author  LoopEdison
  * @version V1.0
  * @date    21-May-2018
  * @brief   This file provides all the memory related operation functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "config.h"
#include "bsp.h"
/* Includes ------------------------------------------------------------------*/
#include "flash_if.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Unlocks Flash for write access
  * @param  None
  * @retval None
  */
void FLASH_If_Init(void)
{
  /* Unlock the Program memory */
  HAL_FLASH_Unlock();
  /* Clear all FLASH flags */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
  /* Unlock the Program memory */
  HAL_FLASH_Lock();
}

/**
  * @brief  This function does an erase flash area
  * @param  [beginAddr] <= {area} < [endAddr]
  * @retval FLASHIF_OK : user flash area successfully erased
  *         FLASHIF_ERASEKO : error occurred
  */
uint32_t FLASH_If_Erase(uint32_t beginAddr, uint32_t endAddr)
{
  HAL_StatusTypeDef status = HAL_OK;
  FLASH_EraseInitTypeDef pEraseInit;
  uint32_t PageError = 0;
  uint32_t NbrOfPages = 0;
  
  /* Unlock the Flash to enable the flash control register access *************/ 
  HAL_FLASH_Unlock();
  
  /* Get the sector where start the user flash area */
  if((endAddr-beginAddr)%FLASH_PAGE_SIZE != 0)
  {
    NbrOfPages = 1 + (endAddr-beginAddr)/FLASH_PAGE_SIZE;
  }
  else
  {
    NbrOfPages = (endAddr-beginAddr)/FLASH_PAGE_SIZE;
  }
  
  pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
  pEraseInit.PageAddress = beginAddr;
  pEraseInit.Banks = FLASH_BANK_1;
  pEraseInit.NbPages = NbrOfPages;
  status = HAL_FLASHEx_Erase(&pEraseInit, &PageError);
  
  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();
  
  if (status != HAL_OK)
  {
    /* Error occurred while page erase */
    return FLASHIF_ERASEKO;
  }
  
  return FLASHIF_OK;
}

/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  destination: start address for target location
  * @param  p_source: pointer on buffer with data to write
  * @param  length: length of data buffer (unit is 32-bit word)
  * @retval uint32_t 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
uint32_t FLASH_If_Write(uint32_t destination, uint32_t *p_source, uint32_t length)
{
  uint32_t i = 0;
  
  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();
  
  for (i = 0; (i < length) && (destination <= (APPLICATION_ADDRESS_END-4)); i++)
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, destination, *(uint32_t*)(p_source+i)) == HAL_OK)      
    {
     /* Check the written value */
      if (*(uint32_t*)destination != *(uint32_t*)(p_source+i))
      {
        /* Flash content doesn't match SRAM content */
        return(FLASHIF_WRITINGCTRL_ERROR);
      }
      /* Increment FLASH destination address */
      destination += 4;
    }
    else
    {
      /* Error occurred while writing data in Flash memory */
      return (FLASHIF_WRITING_ERROR);
    }
  }
  
  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();
  
  return (FLASHIF_OK);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
