/**
  **********************************************************************************************************************
  * @file    key.c
  * @brief   该文件提供按键动作识别功能
  * @author  const_zpc  any question please send mail to const_zpc@163.com
  * @version V3.0.0
  * @date    2022-03-27
  *
  * @details  功能详细说明：
  *           + 按键初始化
  *           + 按键动作监听
  *           + 按键动作信息获取
  *           + 按键轮询任务
  *
  **********************************************************************************************************************
  * 源码路径：https://gitee.com/const-zpc/key.git 具体问题及建议可在该网址填写 Issue
  *
  * 使用方式:
  *    1、使用前初始化函数 KEY_Init
  *    2、周期调用函数 KEY_Scan, 用来处理按键动作识别和处理
  *    3、使用其他函数对获取按键动作附加信息
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "key.h"
#include "keyio.h"

/* Private typedef ---------------------------------------------------------------------------------------------------*/

/**
  * @brief 按键动作信息结构体定义
  */
typedef struct
{
    KeyAction_e eKeyAction;                     /*!< 指定所选按键的动作状态 */

    KeyAction_e eKeyActionBak;                  /*!< 指定所选按键的动作状态备份 */

    uint8_t clickCnt;                           /*!< 指定所选按键的单击次数 */

    uint16_t uiPressTic;                        /*!< 指定所选按键的按下累计时间, 该参数单位为1ms,该值初值为0 */

    uint16_t uiLossenTic;                       /*!< 指定所选按键的松开累计时间, 该参数单位为1ms,该值初值为0 */

    uint16_t uiAntiShakeTime;                   /*!< 指定所选按键的防抖时间, 该参数单位为1ms */
    
    uint16_t refreshNotifyTic;					/*!< 指定所选按键的触发回调通知函数的定时计时, 单位为1ms */

    KeyFunCB pfnKeyNotifyFun;                   /*!< 指定所选按键的动作改变回调通知函数 */
} KeyManage_t;

/* Private define ----------------------------------------------------------------------------------------------------*/

/** 按键防抖时间 */
#define KEY_ANTI_SHAKE_TIME      20

/* Private macro -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/

static KeyManage_t sg_tKeyManage[IO_KEY_MAX_NUM];

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/* Private function --------------------------------------------------------------------------------------------------*/

/**
  * @brief 按键初始化
  *
  */
void KEY_Init(void)
{
    uint8_t key;

    for (key = 0; key < IO_KEY_MAX_NUM; key++)
    {
        sg_tKeyManage[key].eKeyAction = KEY_ACTION_NO_PRESS;
        sg_tKeyManage[key].eKeyActionBak = KEY_ACTION_NO_PRESS;
        sg_tKeyManage[key].clickCnt = 0;
        sg_tKeyManage[key].uiPressTic = 0;
        sg_tKeyManage[key].uiLossenTic = 0;
        sg_tKeyManage[key].uiAntiShakeTime = KEY_ANTI_SHAKE_TIME;
        sg_tKeyManage[key].refreshNotifyTic = 0;
        sg_tKeyManage[key].pfnKeyNotifyFun = NULL;
    }

    IoKey_Init();
}

/**
  * @brief      注册按键动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @param[in]  pKeyFun 通知回调函数
  */
void KEY_Register(IoKeyType_e eKey, KeyFunCB pKeyFun)
{
    if (eKey < IO_KEY_MAX_NUM)
    {
        sg_tKeyManage[eKey].pfnKeyNotifyFun = pKeyFun;
    }
}

/**
  * @brief      注销按键动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  */
void KEY_UnRegister(IoKeyType_e eKey)
{
    if (eKey < IO_KEY_MAX_NUM)
    {
        sg_tKeyManage[eKey].pfnKeyNotifyFun = NULL;
    }
}

/**
  * @brief      设置按键触发时间
  * 
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @param[in]  time 下次触发按键事件回调函数的时间
  */
void KEY_SetNotifyTime(IoKeyType_e eKey, uint16_t time)
{
    if (eKey < IO_KEY_MAX_NUM)
    {
        sg_tKeyManage[eKey].refreshNotifyTic = time;
    }
}

/**
  * @brief      获取按键单击次数
  * 
  * @note       调用该函数时不能有关于按键动作的限制条件
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @param[in]  time 每次单击的间隔时间
  * @retval     单击次数.
  */
uint8_t KEY_GetClickCnt(IoKeyType_e eKey, uint16_t time)
{
    if (eKey >= IO_KEY_MAX_NUM)
    {
        return 0;
    }

    /* 连续单击后，会等间隔时间再进行回调通知, 目的在完全松开按键后，可以再次触发返回单击次数，否则记录完成后，由于动作变换在间隔时间内，不会调用返回语句 */
    if (sg_tKeyManage[eKey].eKeyAction == KEY_ACTION_LOSSEN)
    {
        sg_tKeyManage[eKey].refreshNotifyTic = time;
    }
    
    if (sg_tKeyManage[eKey].eKeyAction == KEY_ACTION_PRESS)
    {
        if (sg_tKeyManage[eKey].clickCnt < 0xFF)
        {
            sg_tKeyManage[eKey].clickCnt++;
        }
    }
		
		//回避LOSSEN后的NO_PRESS状态，从而达到连续计数的目的
    if (sg_tKeyManage[eKey].eKeyAction == KEY_ACTION_NO_PRESS && sg_tKeyManage[eKey].uiLossenTic >= time)
    {
        uint8_t cnt = sg_tKeyManage[eKey].clickCnt;
        
        sg_tKeyManage[eKey].clickCnt = 0;
        return cnt;
    }
    
    return 0;
}

/**
  * @brief      获取按键按下时间
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @retval     按键按下时间, 单位ms.
  */
uint16_t KEY_GetPressTime(IoKeyType_e eKey)
{
    if (eKey >= IO_KEY_MAX_NUM)
    {
        return 0;
    }

    return sg_tKeyManage[eKey].uiPressTic;
}

/**
  * @brief      获取按键松开时间
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @retval     按键松开时间, 单位ms.
  */
uint16_t KEY_GetLossenTime(IoKeyType_e eKey)
{
    if (eKey >= IO_KEY_MAX_NUM)
    {
        return 0;
    }

    return sg_tKeyManage[eKey].uiLossenTic;
}

/**
  * @brief      按键扫描周期任务，Action状态进入先后顺序：NO_PRESS -> PRESS -> LOSSEN -> NO_PRESS
  *
  * @param[in]  cycleTime 周期时间, 单位ms.
  */
void KEY_Scan(uint16_t cycleTime)
{
    uint8_t key;
    IoKeyState_e eKeyState;

    IoKey_Scan();//更新IO的状态

    for (key = 0; key < IO_KEY_MAX_NUM; key++)
    {
        eKeyState = IoKey_Read((IoKeyType_e)key);

        if (eKeyState == IO_KEY_OFF)//开
        {
            if (sg_tKeyManage[key].eKeyAction == KEY_ACTION_PRESS)//长按状态
            {
                if (sg_tKeyManage[key].uiLossenTic < (0xFFFF - cycleTime))
                {
                    sg_tKeyManage[key].uiLossenTic += cycleTime;
                }

                if (sg_tKeyManage[key].uiLossenTic >= sg_tKeyManage[key].uiAntiShakeTime)
                {
                    sg_tKeyManage[key].eKeyAction = KEY_ACTION_LOSSEN;
                }
            }
            else//按下松开、未按下。由于LOSSEN状态只出现在消抖PRESS之后，并且只能维持一个cycle，所以LOSSEN之后转变为NO_PRESS
            {
                sg_tKeyManage[key].eKeyAction = KEY_ACTION_NO_PRESS;
                sg_tKeyManage[key].uiPressTic = 0;

                if (sg_tKeyManage[key].uiLossenTic < (0xFFFF - cycleTime))
                {
                    sg_tKeyManage[key].uiLossenTic += cycleTime;
                }
            }
        }
        else//闭
        {
            if (sg_tKeyManage[key].eKeyAction != KEY_ACTION_LOSSEN)//长按，或者未按下 状态
            {
                if (sg_tKeyManage[key].eKeyAction == KEY_ACTION_PRESS)//长按
                {
                    sg_tKeyManage[key].uiLossenTic = 0;
                }

                if (sg_tKeyManage[key].uiPressTic < (0xFFFF - cycleTime))
                {
                    sg_tKeyManage[key].uiPressTic += cycleTime;
                }

                if (sg_tKeyManage[key].uiPressTic >= sg_tKeyManage[key].uiAntiShakeTime)
                {
                    sg_tKeyManage[key].eKeyAction = KEY_ACTION_PRESS;
                }
            }
            else//按下松开状态在这种扫描模式下，不会出现按下松开以后，立马又按下的情况，因为时间片10ms，如果是按下松开立马又按下，会远大于10ms。如果出现，就是抖动
            {
                sg_tKeyManage[key].eKeyAction = KEY_ACTION_NO_PRESS;
                sg_tKeyManage[key].uiPressTic = 0;
                sg_tKeyManage[key].uiLossenTic = 1;
            }
        }
        
        //判断完按键状态以后，开始处理回调函数
        if (sg_tKeyManage[key].pfnKeyNotifyFun != NULL)
        {
            if (sg_tKeyManage[key].refreshNotifyTic > 0)//延迟回调处理，用于长按固定时间，连续短按计数，可有效回避状态的连续转换，从某一个状态劫持
            {
                if (sg_tKeyManage[key].refreshNotifyTic >= cycleTime)
                {
                    sg_tKeyManage[key].refreshNotifyTic -= cycleTime;
                }
                else
                {
                    sg_tKeyManage[key].refreshNotifyTic = 0;
                }
                
                if (sg_tKeyManage[key].refreshNotifyTic == 0)
                {
                    sg_tKeyManage[key].pfnKeyNotifyFun((IoKeyType_e)key, sg_tKeyManage[key].eKeyAction);
                }
            }
            
            if (sg_tKeyManage[key].eKeyAction != sg_tKeyManage[key].eKeyActionBak)//状态改变，立即处理；长按处理，先进入回调函数，在回调函数中修改延迟处理tick，使之大于0，后续回调处理就会处理延时回调任务。
            {
                sg_tKeyManage[key].pfnKeyNotifyFun((IoKeyType_e)key, sg_tKeyManage[key].eKeyAction);
            }
        }

        sg_tKeyManage[key].eKeyActionBak = sg_tKeyManage[key].eKeyAction;
    }
}
