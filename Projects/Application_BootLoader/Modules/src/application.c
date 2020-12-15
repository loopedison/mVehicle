/**
  ******************************************************************************
  * @file    application.c
  * @author  LoopEdison
  * @version V1.0
  * @date    12-Dec-2020
  * @brief   Application for BootLoader
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "bsp.h"
/* Includes ------------------------------------------------------------------*/
#include "cpu_id.h"
#include "xxtea.h"
#include "crc16.h"
/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "flash_if.h"
#include "ymodem.h"

/* Private typedef -----------------------------------------------------------*/
/* app Function */
typedef void (*pFunction)(void);

#pragma pack(4)
typedef struct
{
  uint32_t SysRunLevel[1];
  uint32_t SysCpuId[3];
  uint32_t SysEncryptKey[4];
  uint32_t SysBootVer[1];
  uint32_t SysReserved[55];
}BootLoader_FlashInfoTypeDef;
#pragma pack()

#pragma pack(4)
typedef struct
{
  uint32_t SysUpgradeFlag[1];
  uint32_t SysReserved[63];
}BootLoader_RamInfoTypeDef;
#pragma pack()

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ------------------ Information on Flash ---------------------------------- */
#define BOOTLOADER_FLASH_INFO_ADDR          (0x08002f00)
static const BootLoader_FlashInfoTypeDef BootLoaderFlashInfo __attribute__((at(BOOTLOADER_FLASH_INFO_ADDR))) = 
{
  .SysRunLevel[0]                   = 0xffffffff,
  .SysCpuId[0 ... 2]                = 0xffffffff,
  .SysEncryptKey[0 ... 3]           = 0xffffffff,
  .SysBootVer[0]                    = 0xffffffff,
  .SysReserved[0 ... 54]            = 0xffffffff,
};

/* Sys Run Level */
#define SYS_RUN_LEVEL_KEYWORD         (0XCDEF89AB)
#define SYS_RUN_LEVEL_ADDR            (BOOTLOADER_FLASH_INFO_ADDR + 0x00000000)

/* Cpu ID */
#define SYS_CPU_ID_KEYWORD            (0XA5A5A5A5)
#define SYS_CPU_ID_ADDR               (BOOTLOADER_FLASH_INFO_ADDR + 0x00000004)

/* Encrypt KEY */
#define SYS_ENCRYPT_KEYWORD           ("WWW.JISHIVR.CN")
#define SYS_ENCRYPT_KEY_0             (0XE9F78F0B)
#define SYS_ENCRYPT_KEY_1             (0X43F215FD)
#define SYS_ENCRYPT_KEY_2             (0X77E68673)
#define SYS_ENCRYPT_KEY_3             (0XD86C3B82)
#define SYS_ENCRYPT_KEY_ADDR          (BOOTLOADER_FLASH_INFO_ADDR + 0x00000010)

/* Boot Ver */
#define SYS_BOOT_VERSION              (0XAA000100)
#define SYS_BOOT_VER_ADDR             (BOOTLOADER_FLASH_INFO_ADDR + 0x00000020)


/* ------------------ Information on Ram ------------------------------------ */
#define BOOTLOADER_RAM_INFO_ADDR      (0x20000f00)
static BootLoader_RamInfoTypeDef BootLoaderRamInfo __attribute__((at(BOOTLOADER_RAM_INFO_ADDR))) ={0};

/* Upgrade Flag */
#define SYS_UPGRADE_FLAG_KEYWORD      (0XCDEF89AB)
#define SYS_UPGRADE_FLAG_ADDR         (BOOTLOADER_RAM_INFO_ADDR + 0x00000000)


/* ------------------- Access To Flash & RAM Storage ------------------------ */
volatile BootLoader_FlashInfoTypeDef *pFlashInfo = (BootLoader_FlashInfoTypeDef*)&BootLoaderFlashInfo;
volatile BootLoader_RamInfoTypeDef   *pRamInfo   = (BootLoader_RamInfoTypeDef*)&BootLoaderRamInfo;


/* ------------------ Information for Boot File ----------------------------- */
/* Boot File Info */
#define ENCRYPT_ARRAY_SIZE            (0x8)
#define BOOT_FILE_HEAD_SIZE           (0x8) /* Must size 8*uint32 */
typedef struct
{
  uint32_t bootVer;
  uint32_t xDataSize;
  uint32_t reserved[6];
}BootLoader_AppFileInfoType;

/* Private function prototypes -----------------------------------------------*/
void BootLoader_Menu(void);
uint32_t BootLoader_Menu_Download(void);
uint32_t BootLoader_Menu_Upload(void);
uint32_t BootLoader_Menu_Upgrade(uint32_t xAddrDest, uint32_t xAddrSrc, uint32_t xDataSize);
/* Private functions ---------------------------------------------------------*/

//==============================================================================
/**
  * @brief  Application_Main
  * @param  None
  * @retval None
  */
void Application_Main(void)
{
  /* Get CPU ID */
  uint32_t sysCpuId[3] = {0};
  CPU_getId(sysCpuId);
  
  /* Initialise BSP SYSLED UART1 */
  BSP_Init();
  BSP_UART1_Init();
  BSP_SYSKEY_Init();
  BSP_SYSLED_Init();
  
/*---- Debug Flash Led Start ---*/
BSP_SYSLED_TurnOn();    HAL_Delay(25);
BSP_SYSLED_TurnOff();   HAL_Delay(25);
/*------------------------------*/
  
  /* Get Run Level */
  if(pFlashInfo->SysRunLevel[0] == 0xffffffff)
  {
    /* The First Time, Reload */
    /* Run Flag, CpuID, EncryptKey, BootVer */
    HAL_FLASH_Unlock();
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (SYS_RUN_LEVEL_ADDR), (SYS_RUN_LEVEL_KEYWORD));
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (SYS_CPU_ID_ADDR + 0*sizeof(uint32_t)), (sysCpuId[0]^SYS_CPU_ID_KEYWORD));
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (SYS_CPU_ID_ADDR + 1*sizeof(uint32_t)), (sysCpuId[1]^SYS_CPU_ID_KEYWORD));
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (SYS_CPU_ID_ADDR + 2*sizeof(uint32_t)), (sysCpuId[2]^SYS_CPU_ID_KEYWORD));
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (SYS_ENCRYPT_KEY_ADDR + 0*sizeof(uint32_t)), (SYS_ENCRYPT_KEY_0));
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (SYS_ENCRYPT_KEY_ADDR + 1*sizeof(uint32_t)), (SYS_ENCRYPT_KEY_1));
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (SYS_ENCRYPT_KEY_ADDR + 2*sizeof(uint32_t)), (SYS_ENCRYPT_KEY_2));
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (SYS_ENCRYPT_KEY_ADDR + 3*sizeof(uint32_t)), (SYS_ENCRYPT_KEY_3));
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (SYS_BOOT_VER_ADDR), (SYS_BOOT_VERSION));
    HAL_FLASH_Lock();
    
    /* Generate system reset */
    HAL_Delay(1);
    NVIC_SystemReset();
  }
  else if(pFlashInfo->SysRunLevel[0] == SYS_RUN_LEVEL_KEYWORD)
  {
    /* check cpu id */
    uint32_t *pCpuID = (uint32_t *)pFlashInfo->SysCpuId;
    for(uint32_t i=0; i<3; i++)
    {
      if((sysCpuId[i]^SYS_CPU_ID_KEYWORD) != *(pCpuID+i))
      {
/*---- Debug Flash Led Error ---*/
BSP_SYSLED_TurnOn();    HAL_Delay(1000);
BSP_SYSLED_TurnOff();   HAL_Delay(25);
while(true);
/*------------------------------*/
      }
    }
    
    /* Normal Running */
    BootLoader_Menu();
  }
  
/*----- Debug Flash Led Stop ---*/
BSP_SYSLED_TurnOn();    HAL_Delay(2000);
BSP_SYSLED_TurnOff();   HAL_Delay(25);
/*------------------------------*/
  
  while(true);
  
}

//==============================================================================
/**
  * @brief  Display the Main Menu on HyperTerminal
  * @param  None
  * @retval None
  */
void BootLoader_Menu(void)
{
/*----- Debug Flash Led --------*/
BSP_SYSLED_TurnOn();    HAL_Delay(25);
BSP_SYSLED_TurnOff();   HAL_Delay(25);
/*------------------------------*/
  
  /* Show Debug Information */
  Serial_PutString((uint8_t *)"\r\n");
  Serial_PutString((uint8_t *)"Application will start in 3 seconds.\r\n");
  
  /* check inputKey and uart */
  uint8_t inputKey=0;
  HAL_UART_Receive(&huart1, &inputKey, 1, 3000);
  /* Checkout if Key or Msg */
  if((inputKey == 'C')||(BSP_SYSKEY_Read() == true))
  {
    pRamInfo->SysUpgradeFlag[0] = SYS_UPGRADE_FLAG_KEYWORD;
  }
  
  /* Enter Upgrade Mode If Valid */
  if(pRamInfo->SysUpgradeFlag[0] == SYS_UPGRADE_FLAG_KEYWORD)
  {
    /* Initialise Flash */
    FLASH_If_Init();
    
    /* Show help Information */
    Serial_PutString((uint8_t *)"\r\n");
    Serial_PutString((uint8_t *)"======================================\r\n");
    Serial_PutString((uint8_t *)"=    (C) COPYRIGHT LoopEdison        =\r\n");
    Serial_PutString((uint8_t *)"=    Welcome Bootloader Programming  =\r\n");
    Serial_PutString((uint8_t *)"======================================\r\n");
    Serial_PutString((uint8_t *)"\r\n");
    
    while (1)
    {
      /* Show menu list */
      Serial_PutString((uint8_t *)"============= Main Menu ==============\r\n");
      Serial_PutString((uint8_t *)"=>Board Information -------------- 0 =\r\n");
      Serial_PutString((uint8_t *)"=>Download image to Flash -------- 1 =\r\n");
      Serial_PutString((uint8_t *)"=>Execute application ------------ 2 =\r\n");
      Serial_PutString((uint8_t *)"=>Exit and Reboot ---------------- 3 =\r\n");
      Serial_PutString((uint8_t *)"======================================\r\n");
      Serial_PutString((uint8_t *)">> ");
      
      /* Handle user inputKey From uart and Echo back */
      inputKey = 0;
      __HAL_UART_FLUSH_DRREGISTER(&huart1);
      HAL_UART_Receive(&huart1, &inputKey, 1, RX_TIMEOUT);
      Serial_PutByte(inputKey);
      Serial_PutString((uint8_t *)"\r\n");
      
      if(inputKey == '0')
      {
        Serial_PutString((uint8_t *)"Board Info V0.1.0\r\n");
        
      }
      else if(inputKey == '1')
      {
        Serial_PutString((uint8_t *)"Enter Download Mode\r\n");
        BootLoader_Menu_Download();
      }
      else if(inputKey == '2')
      {
        Serial_PutString((uint8_t *)"Execute application...\r\n");
        break;
      }
      else if(inputKey == '3')
      {
        Serial_PutString((uint8_t *)"Exit and Reboot ...\r\n");
        NVIC_SystemReset();
      }
      else if(inputKey == '!')
      {
        /* Clean the input path */
        __HAL_UART_FLUSH_DRREGISTER(&huart1);
        /* Receive inputKey */
        inputKey = 0;
        HAL_UART_Receive(&huart1, &inputKey, 1, 1000);
        if(inputKey == '$')
        {
          Serial_PutString((uint8_t *)"Enter Upload Mode\r\n");
          /* Upload user application from the Flash */
          BootLoader_Menu_Upload();
        }
      }
      else
      {
        Serial_PutString((uint8_t *)"Invalid Input !\r\n");
      }
    }
  }
  
  /* Test application code at APPLICATION_ADDRESS */
  if(((*(__IO uint32_t*)APPLICATION_ADDRESS) & 0x2FFE0000 ) == 0x20000000)
  {
    /* application address */
    pFunction JumpToApplication;
    uint32_t JumpAddress;
    /* Jump to user application */
    JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);
    JumpToApplication = (pFunction) JumpAddress;
    /* Initialize user application's Stack Pointer */
    __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
    JumpToApplication();
  }
  
  /* Show Debug Information */
  Serial_PutString((uint8_t *)"Application Load Failed!\r\n");
  
}


//==============================================================================
/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval Status
  */
uint32_t BootLoader_Menu_Download(void)
{
  uint32_t status = 0;
  
  uint8_t aFileName[FILE_NAME_LENGTH];
  uint8_t number[11] = {0};
  uint32_t size = 0;
  COM_StatusTypeDef result;
  
  Serial_PutString((uint8_t *)"Waiting for the file to be sent ... (press 'a' to abort)\n\r");
  result = Ymodem_Receive((uint8_t*)APPLICATION_ADDRESS, aFileName, &size);
  
  if (result == COM_OK)
  {
    Serial_PutString((uint8_t *)"Download Successfully!\r\n");
    Serial_PutString((uint8_t *)"Name: ");
    Serial_PutString(aFileName);
    Int2Str(number, size);
    Serial_PutString((uint8_t *)"\r\n");
    Serial_PutString((uint8_t *)"Size: ");
    Serial_PutString(number);
    Serial_PutString((uint8_t *)" Bytes\r\n");
    
/*------- Decrypt Flash --------*/
    Serial_PutString((uint8_t *)"Prepare Application...");
    /* Decrypt Code From Download */
    BootLoader_AppFileInfoType fileInfo;
    memcpy(&fileInfo, (uint32_t *)(APPLICATION_ADDRESS), sizeof(uint32_t)*BOOT_FILE_HEAD_SIZE);
    btea((uint32_t *)&fileInfo, (-1)*(BOOT_FILE_HEAD_SIZE), (const uint32_t *)(pFlashInfo->SysEncryptKey));
    if(fileInfo.bootVer == pFlashInfo->SysBootVer[0])
    {
      uint32_t xAddrDest = APPLICATION_ADDRESS;
      uint32_t xAddrSrc  = APPLICATION_ADDRESS + sizeof(uint32_t)*BOOT_FILE_HEAD_SIZE;
      uint32_t xDataSize = sizeof(uint32_t)*fileInfo.xDataSize;
      BootLoader_Menu_Upgrade(xAddrDest, xAddrSrc, xDataSize);
    }
    Serial_PutString((uint8_t *)"OK\r\n");
/*------------------------------*/
    
    status = 0;
  }
  else if (result == COM_LIMIT)
  {
    Serial_PutString((uint8_t *)"Error: Image size limit!\r\n");
    status = 1;
  }
  else if (result == COM_DATA)
  {
    Serial_PutString((uint8_t *)"Error: Verification failed!\r\n");
    status = 1;
  }
  else if (result == COM_ABORT)
  {
    Serial_PutString((uint8_t *)"Error: Aborted by user.\r\n");
    status = 1;
  }
  else
  {
    Serial_PutString((uint8_t *)"Error: Failed to receive the file!\r\n");
    status = 1;
  }
  
  return (status);
}

//==============================================================================
/**
  * @brief  Upload a file via serial port.
  * @param  None
  * @retval Status
  */
uint32_t BootLoader_Menu_Upload(void)
{
  uint32_t status = 0;
  
  uint8_t tVal = 0;
  Serial_PutString((uint8_t *)"\n\n\rSelect Receive File\n\r");
  HAL_UART_Receive(&huart1, &tVal, 1, RX_TIMEOUT);
  if(tVal == CRC16Y)
  {
    /* Transmit the flash image through ymodem protocol */
    tVal = Ymodem_Transmit((uint8_t*)APPLICATION_ADDRESS, (const uint8_t*)"UploadedFlashImage.bin", APPLICATION_FLASH_SIZE);
    
    if (tVal != 0)
    {
      Serial_PutString((uint8_t *)"\n\rError Occurred while Transmitting File\n\r");
      status = 1;
    }
    else
    {
      Serial_PutString((uint8_t *)"\n\rFile uploaded successfully \n\r");
      status = 0;
    }
  }
  
  return (status);
}

//==============================================================================
/**
  * @brief  Upgrade Firmware
  * @param  None
  * @retval Status
  */
uint32_t BootLoader_Menu_Upgrade(uint32_t xAddrDest, uint32_t xAddrSrc, uint32_t xDataSize)
{
  /* Check Param */  
  if((xAddrDest%sizeof(uint32_t) != 0)||(xAddrSrc%sizeof(uint32_t) != 0)||(xDataSize%sizeof(uint32_t) != 0))
  {
    return (1);
  }
  
  uint32_t status = 0;
  
  /* Unlock Flash Begin */
  HAL_FLASH_Unlock();
  
  /* Decrypt Firmware And Program */
  uint32_t pBuf[FLASH_PAGE_SIZE/sizeof(uint32_t)];
  uint32_t xMsg[ENCRYPT_ARRAY_SIZE];
  uint32_t iDataLen = 0;
  uint32_t iDataBlock = 0;
  while((status == 0)&&(iDataLen < xDataSize))
  {
    /* datasize to program */
    if(iDataLen + FLASH_PAGE_SIZE < xDataSize)  { iDataBlock = FLASH_PAGE_SIZE; }
    else                                        { iDataBlock = xDataSize - iDataLen; }
    
    /* Copy to RAM */
    memcpy(pBuf, (void*)(xAddrSrc + iDataLen), iDataBlock);
    
    /* Erase Select Flash */
    uint32_t SectorError;
    FLASH_EraseInitTypeDef EraseInitStruct;
    EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
    EraseInitStruct.PageAddress = xAddrDest + iDataLen;
    EraseInitStruct.NbPages = 1;
    if(HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK)
    {
      status = 1;
      break;
    }
    
    /* Decrypt, and Program to Flash */
    for(uint32_t i=0; ((status == 0)&&(i<(iDataBlock/sizeof(uint32_t)/ENCRYPT_ARRAY_SIZE))); i++)
    {
      memcpy(xMsg, (void *)(pBuf+(i*ENCRYPT_ARRAY_SIZE)), sizeof(uint32_t)*ENCRYPT_ARRAY_SIZE);
      btea(xMsg, (-1*ENCRYPT_ARRAY_SIZE), (const uint32_t *)(pFlashInfo->SysEncryptKey));
      for(uint32_t j=0; ((status == 0)&&(j<(ENCRYPT_ARRAY_SIZE))); j++)
      {
        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, (xAddrDest + iDataLen + sizeof(uint32_t)*(i*ENCRYPT_ARRAY_SIZE+j)), xMsg[j]) != HAL_OK)
        {
          status = 1;
          break;
        }
      }
    }
    
    /* For Next */
    iDataLen += iDataBlock;
  }
  
  /* Lock Flash End */
  HAL_FLASH_Lock();
  
  return (status);
}

//==============================================================================
//==============================================================================
#ifdef USE_FULL_ASSERT
/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  while(1)
  {}
}
#endif /* USE_FULL_ASSERT */

#ifdef USE_USER_ASSERT
void AssertFail(char *file, int line)
{
  while(1)
  {}
}
#endif /* USE_USER_ASSERT */


/************************ (C) COPYRIGHT LOOPEDISON *********END OF FILE********/
