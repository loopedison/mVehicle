/**
  ******************************************************************************
  * @file    flash_if.h 
  * @author  LoopEdison
  * @version V1.0
  * @date    21-May-2018
  * @brief   This file provides all the headers of the flash_if functions.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_H__
#define __FLASH_IF_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Error code */
enum 
{
  FLASHIF_OK = 0,
  FLASHIF_ERASEKO,
  FLASHIF_WRITINGCTRL_ERROR,
  FLASHIF_WRITING_ERROR,
  FLASHIF_PROTECTION_ERRROR
};

/* protection type */  
enum{
  FLASHIF_PROTECTION_NONE         = 0,
  FLASHIF_PROTECTION_PCROPENABLED = 0x1,
  FLASHIF_PROTECTION_WRPENABLED   = 0x2,
  FLASHIF_PROTECTION_RDPENABLED   = 0x4,
};

/* protection update */
enum {
	FLASHIF_WRP_ENABLE,
	FLASHIF_WRP_DISABLE
};

/* Define the address from where user application will be loaded.
   Note: this area is reserved for the IAP code                  */
#define APPLICATION_ADDRESS         ((uint32_t)0x08004000)
#define APPLICATION_ADDRESS_END     ((uint32_t)0x08010000)
#define APPLICATION_FLASH_SIZE      (APPLICATION_ADDRESS_END - APPLICATION_ADDRESS)
#define APPLICATION_FLASH_PAGES     (APPLICATION_FLASH_SIZE/FLASH_PAGE_SIZE)
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void     FLASH_If_Init(void);
uint32_t FLASH_If_Erase(uint32_t beginAddr, uint32_t endAddr);
uint32_t FLASH_If_Write(uint32_t destination, uint32_t *p_source, uint32_t length);

#endif  /* __FLASH_IF_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
