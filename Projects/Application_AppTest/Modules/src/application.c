/**
  ******************************************************************************
  * @file    application.c
  * @author  LoopEdison
  * @version V1.0
  * @date    15-Dec-2020
  * @brief   BootLoader
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
#include "m_superled.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//==============================================================================
/* led: default running */
/* Double flash */
const SuperLed_QItemDef cLedDefaultRun = 
{
  .counter = SUPERLED_COUNTER_MAX,
  .priority = SUPERLED_PRIO_DEFAULT,
  .message[0] = 50,
  .message[1] = -50,
  .message[2] = 50,
  .message[3] = -1850,
  .message[4] = 0,
};
/* led: error */
/* Quick flash */
const SuperLed_QItemDef cLedErrorRun = 
{
  .counter = SUPERLED_COUNTER_MAX,
  .priority = SUPERLED_PRIO_DEFAULT,
  .message[0] = 50,
  .message[1] = -50,
  .message[2] = 0,
};

static SuperLed_QItemDef sLedSys;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//==============================================================================
/**
  * @brief  Application_Main
  * @param  None
  * @retval None
  */
void Application_Main(void)
{
  //=======================================
  /* Initialise BSP */
  BSP_Init();
  //=======================================
  /* Init modules */
  SuperLed_Init();
  
  //=======================================
  /* LED: DefaultRun */
  memcpy(&sLedSys, &cLedDefaultRun, sizeof(SuperLed_QItemDef));
  SuperLed_Display(&sLedSys);
  
  while(true)
  {
    //=======================================
    //Led flash Task
    SuperLed_Task(NULL);
  }
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
