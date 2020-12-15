/**
  ******************************************************************************
  * @file    config.h
  * @author  LoopEdison
  * @version V1.0
  * @date    12-Dec-2020
  * @brief   Main configuration file
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Private includes ----------------------------------------------------------*/
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define USE_USER_ASSERT             (1)                             /* ASSERT */
#define M_PI                        (3.14159265359)
#define USE_DEBUG_PRINT             (1)                             /* DEBUG  */
#define COUNTOF(__BUFFER__)         (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/* Exported functions prototypes ---------------------------------------------*/
#ifdef USE_USER_ASSERT
#define ASSERT(expr) ((expr) ? (void)0 : AssertFail(__FILE__, __LINE__))
void AssertFail(char *file, int line);
#endif /* USE_USER_ASSERT */

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __CONFIG_H */

/************************ (C) COPYRIGHT LOOPEDISON *********END OF FILE********/
