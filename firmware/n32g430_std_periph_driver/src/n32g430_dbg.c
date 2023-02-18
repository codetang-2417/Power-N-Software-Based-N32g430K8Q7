/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
*\*\file n32g430_dbg.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32G430_DBG_H__
#define __N32G430_DBG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

#define IDCODE_DEVID_MASK ((uint32_t)0x00000FFF)

/**
*\*\name    UCID_Get.
*\*\fun     get unique customer id.
*\*\param   UCIDbuf
*\*\return  none
**/
void UCID_Get(uint8_t *UCIDbuf)
{
    uint8_t num = 0;
    uint32_t* ucid_addr = (void*)0;
    uint32_t temp = 0;

    ucid_addr = (uint32_t*)UCID_BASE;
    
    for (num = 0; num < UCID_LENGTH;)
    {
        temp = *(__IO uint32_t*)(ucid_addr++); 
        UCIDbuf[num++] = (temp & 0xFF);
        UCIDbuf[num++] = (temp & 0xFF00) >> 8;
        UCIDbuf[num++] = (temp & 0xFF0000) >> 16;
        UCIDbuf[num++] = (temp & 0xFF000000) >> 24;
    }
}

/**
*\*\name    UID_Get.
*\*\fun     get unique device id.
*\*\param   UIDbuf
*\*\return  none
**/
void UID_Get(uint8_t *UIDbuf)
{
    uint8_t num = 0;
    uint32_t* uid_addr = (void*)0;
    uint32_t temp = 0;
    
    uid_addr = (uint32_t*)UID_BASE;
        
    for (num = 0; num < UID_LENGTH;)
    {
        temp = *(__IO uint32_t*)(uid_addr++);
        UIDbuf[num++] = (temp & 0xFF);
        UIDbuf[num++] = (temp & 0xFF00) >> 8;
        UIDbuf[num++] = (temp & 0xFF0000) >> 16;
        UIDbuf[num++] = (temp & 0xFF000000) >> 24;
    }
}

/**
*\*\name    DBG_Revision_Number_Get.
*\*\fun     get the revision number.
*\*\param   none
*\*\return  revision number
**/
uint32_t DBG_Revision_Number_Get(void)
{
    return (DBG->ID & 0x00FF);
}

/**
*\*\name    DBG_Device_Number_Get.
*\*\fun     get the device identifer.
*\*\param   none
*\*\return  Device identifier
**/
uint32_t DBG_Device_Number_Get(void)
{
    uint32_t id = DBG->ID;
    return ((id & 0x00F00000) >> 20) | ((id & 0xFF00) >> 4);
}

/**
*\*\name    DBG_Peripheral_ON.
*\*\fun     Configures the specified peripheral run when the MCU under Debug mode.
*\*\param   DBG_Periph :
                - DBG_SLEEP             \* Keep debugger connection during SLEEP mode *\
                - DBG_STOP              \* Keep debugger connection during STOP mode *\
                - DBG_STANDBY           \* Keep debugger connection during STANDBY mode *\
                - DBG_IWDG_STOP         \* IWDG stopped when Core is halted. *\
                - DBG_WWDG_STOP         \* WWDG stopped when Core is halted. *\
                - DBG_TIM1_STOP         \* TIM1 counter stopped when Core is halted. *\
                - DBG_TIM2_STOP         \* TIM2 counter stopped when Core is halted. *\
                - DBG_TIM3_STOP         \* TIM3 counter stopped when Core is halted. *\
                - DBG_TIM4_STOP         \* TIM4 counter stopped when Core is halted. *\
                - DBG_CAN_STOP          \* CAN  stopped when Core is halted. *\
                - DBG_I2C1SMBUS_TIMEOUT \* I2C1 SMBUS timeout mode stopped when Core is halted. *\
                - DBG_I2C2SMBUS_TIMEOUT \* I2C2 SMBUS timeout mode stopped when Core is halted. *\
                - DBG_TIM8_STOP         \* TIM8 counter stopped when Core is halted. *\
                - DBG_TIM5_STOP         \* TIM5 counter stopped when Core is halted. *\
                - DBG_TIM6_STOP         \* TIM6 counter stopped when Core is halted. *\
*\*\return  none
**/
void DBG_Peripheral_ON(uint32_t DBG_Periph)
{
    DBG->CTRL |= DBG_Periph;
}

/**
*\*\name    DBG_Peripheral_OFF.
*\*\fun     Configures the specified peripheral run or stop when the MCU under Debug mode.
*\*\param   DBG_Periph :
                - DBG_SLEEP             \* Debugger disconnect during SLEEP mode *\
                - DBG_STOP              \* Debugger disconnect during STOP mode *\
                - DBG_STANDBY           \* Debugger disconnect during STANDBY mode *\
                - DBG_IWDG_STOP         \* IWDG don't stop when Core is halted. *\
                - DBG_WWDG_STOP         \* WWDG don't stop when Core is halted. *\
                - DBG_TIM1_STOP         \* TIM1 counter don't stop when Core is halted. *\
                - DBG_TIM2_STOP         \* TIM2 counter don't stop when Core is halted. *\
                - DBG_TIM3_STOP         \* TIM3 counter don't stop when Core is halted. *\
                - DBG_TIM4_STOP         \* TIM4 counter don't stop when Core is halted. *\
                - DBG_CAN_STOP          \* CAN  stopped when Core is halted. *\
                - DBG_I2C1SMBUS_TIMEOUT \* I2C1 SMBUS timeout mode don't stop when Core is halted. *\
                - DBG_I2C2SMBUS_TIMEOUT \* I2C2 SMBUS timeout mode don't stop when Core is halted. *\
                - DBG_TIM8_STOP         \* TIM8 counter don't stop when Core is halted. *\
                - DBG_TIM5_STOP         \* TIM5 counter don't stop when Core is halted. *\
                - DBG_TIM6_STOP         \* TIM6 counter don't stop when Core is halted. *\
*\*\return  none
**/
void DBG_Peripheral_OFF(uint32_t DBG_Periph)
{
    DBG->CTRL &= ~DBG_Periph;
}

#ifdef __cplusplus
}
#endif

#endif /*__N32G430_DBG_H__ */
