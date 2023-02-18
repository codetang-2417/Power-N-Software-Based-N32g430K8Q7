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
*\*\file n32g430_dbg.h
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

#define DBG_SLEEP               DBG_CTRL_SLEEP
#define DBG_STOP                DBG_CTRL_STOP
#define DBG_STANDBY             DBG_CTRL_STDBY
#define DBG_IWDG_STOP           DBG_CTRL_IWDG_STOP
#define DBG_WWDG_STOP           DBG_CTRL_WWDG_STOP
#define DBG_TIM1_STOP           DBG_CTRL_TIM1_STOP
#define DBG_TIM2_STOP           DBG_CTRL_TIM2_STOP
#define DBG_TIM3_STOP           DBG_CTRL_TIM3_STOP
#define DBG_TIM4_STOP           DBG_CTRL_TIM4_STOP
#define DBG_CAN_STOP            DBG_CTRL_CAN_STOP
#define DBG_I2C1SMBUS_TIMEOUT   DBG_CTRL_I2C1SMBUS_TO
#define DBG_I2C2SMBUS_TIMEOUT   DBG_CTRL_I2C2SMBUS_TO
#define DBG_TIM8_STOP           DBG_CTRL_TIM8_STOP
#define DBG_TIM5_STOP           DBG_CTRL_TIM5_STOP
#define DBG_TIM6_STOP           DBG_CTRL_TIM6_STOP


void UCID_Get(uint8_t *UCIDbuf);
void UID_Get(uint8_t *UIDbuf);
uint32_t DBG_Revision_Number_Get(void);
uint32_t DBG_Device_Number_Get(void);
void DBG_Peripheral_ON(uint32_t DBG_Periph);
void DBG_Peripheral_OFF(uint32_t DBG_Periph);


#ifdef __cplusplus
}
#endif

#endif /* __N32G430_DBG_H__ */
