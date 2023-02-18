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
*\*\file n32g430_iwdg.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32G430_IWDG_H__
#define __N32G430_IWDG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"


typedef enum 
{
    IWDG_PVU_FLAG  = IWDG_STS_PVU,
    IWDG_CRVU_FLAG = IWDG_STS_CRVU
}IWDG_STATUS_FLAG;

/** KEY register bit mask **/
#define KEY_RELOAD_COUNTER                 ((uint16_t)0xAAAA)
#define KEY_ENABLE_COUNTER                 ((uint16_t)0xCCCC)
#define IWDG_FREEZE                        ((uint16_t)0x4567)
#define IWDG_UNFREEZE                      ((uint16_t)0x89AB)

/** PREDIV and RELV register write permission **/
typedef enum 
{
    IWDG_WRITE_CONFIG_ENABLE  = 0x5555,
    IWDG_WRITE_CONFIG_DISABLE = 0x0000
}IWDOG_WRITE_CONFIG;


typedef enum 
{
    IWDG_CONFIG_PRESCALER_DIV4   = (~IWDG_PREDIV_PD),
    IWDG_CONFIG_PRESCALER_DIV8   = (IWDG_PREDIV_PD0),
    IWDG_CONFIG_PRESCALER_DIV16  = (IWDG_PREDIV_PD1),
    IWDG_CONFIG_PRESCALER_DIV32  = (IWDG_PREDIV_PD1 | IWDG_PREDIV_PD0),
    IWDG_CONFIG_PRESCALER_DIV64  = (IWDG_PREDIV_PD2),
    IWDG_CONFIG_PRESCALER_DIV128 = (IWDG_PREDIV_PD2 | IWDG_PREDIV_PD0),
    IWDG_CONFIG_PRESCALER_DIV256 = (IWDG_PREDIV_PD2 | IWDG_PREDIV_PD1 | IWDG_PREDIV_PD0)
}IWDG_CONFIG_PRESCALER;


void IWDG_Write_Protection_Disable(void);
void IWDG_Write_Protection_Enable(void);
void IWDG_Prescaler_Division_Set(IWDG_CONFIG_PRESCALER IWDG_prescaler);
void IWDG_Counter_Reload(uint16_t reload_value);
void IWDG_Key_Reload(void);
void IWDG_Enable(void);
void IWDG_Freeze_Enable(void);
void IWDG_Restore_From_Freeze(void);
FlagStatus IWDG_Status_Get(IWDG_STATUS_FLAG IWDG_flag);


#ifdef __cplusplus
}
#endif

#endif /* __N32G430_IWDG_H__ */
