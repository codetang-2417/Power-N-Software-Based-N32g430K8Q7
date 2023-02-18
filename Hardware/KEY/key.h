/**
  **********************************************************************************************************************
  * @file    key.h
  * @brief   该文件提供按键动作识别功能函数原型
  * @author  const_zpc    any question please send mail to const_zpc@163.com
  * @version V3.0.0
  * @date    2022-03-27
  **********************************************************************************************************************
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "keyio.h"

#ifndef NULL
#define NULL   (void *)0
#endif

/* Exported types ----------------------------------------------------------------------------------------------------*/
typedef enum
{
    KEY_ACTION_NO_PRESS = 0,            /*!< 没有按下 */
    KEY_ACTION_PRESS,                   /*!< 持续按下 */
    KEY_ACTION_LOSSEN                   /*!< 按下松开 */
} KeyAction_e;

typedef void (*KeyFunCB)(IoKeyType_e, KeyAction_e);


/* Exported constants ------------------------------------------------------------------------------------------------*/
/* Exported macro ----------------------------------------------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------------------------------------------------*/

extern void KEY_Init(void);

extern void KEY_Register(IoKeyType_e eKey, KeyFunCB pfnKeyFun);
extern void KEY_UnRegister(IoKeyType_e eKey);

extern void KEY_SetNotifyTime(IoKeyType_e eKey, uint16_t time);

extern uint8_t KEY_GetClickCnt(IoKeyType_e eKey, uint16_t time);
extern uint16_t KEY_GetPressTime(IoKeyType_e eKey);
extern uint16_t KEY_GetLossenTime(IoKeyType_e eKey);

extern void KEY_Scan(uint16_t cycleTime);


#endif // !__KEY_H
