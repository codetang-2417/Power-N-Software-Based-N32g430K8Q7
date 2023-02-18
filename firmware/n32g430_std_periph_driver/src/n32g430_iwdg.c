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
*\*\file n32g430_iwdg.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#include "n32g430_iwdg.h"


/**
*\*\name    IWDG_Write_Protection_Disable.
*\*\fun     Disable write protection to IWDG_PREDIV and IWDG_RELV registers.
*\*\param   none
*\*\return  none
**/
void IWDG_Write_Protection_Disable(void)
{
    IWDG->KEY = IWDG_WRITE_CONFIG_ENABLE;
}


/**
*\*\name    IWDG_Write_Protection_Enable.
*\*\fun     Enable write protection to IWDG_PREDIV and IWDG_RELV registers.
*\*\param   none
*\*\return  none
**/
void IWDG_Write_Protection_Enable(void)
{
    IWDG->KEY = IWDG_WRITE_CONFIG_DISABLE;
}


/**
*\*\name    IWDG_Prescaler_Division_Set.
*\*\fun     IWDG_Prescaler specifies the IWDG prescaler value.
*\*\param   IWDG_prescaler :
*\*\          - IWDG_CONFIG_PRESCALER_DIV4 
*\*\          - IWDG_CONFIG_PRESCALER_DIV8
*\*\          - IWDG_CONFIG_PRESCALER_DIV16
*\*\          - IWDG_CONFIG_PRESCALER_DIV32
*\*\          - IWDG_CONFIG_PRESCALER_DIV64
*\*\          - IWDG_CONFIG_PRESCALER_DIV128
*\*\          - IWDG_CONFIG_PRESCALER_DIV256
*\*\return  none
**/
void IWDG_Prescaler_Division_Set(IWDG_CONFIG_PRESCALER IWDG_prescaler)
{
    IWDG->PREDIV = IWDG_prescaler;
}


/**
*\*\name    IWDG_Counter_Reload.
*\*\fun     Sets IWDG reload value.
*\*\param   reload_value :
*\*\          -0x000 ~ 0xFFF
*\*\return  none
**/
void IWDG_Counter_Reload(uint16_t reload_value)
{
    IWDG->RELV = reload_value;
}


/**
*\*\name    IWDG_Key_Reload.
*\*\fun     Reload IWDG counter with value defined in IWDG_RELV register.
*\*\return  none
**/
void IWDG_Key_Reload(void)
{
    IWDG->KEY = KEY_RELOAD_COUNTER;
}


/**
*\*\name    IWDG_Enable.
*\*\fun     Start watch dog counter.
*\*\return  none
**/
void IWDG_Enable(void)
{
    IWDG->KEY = KEY_ENABLE_COUNTER;
}

/**
*\*\name    IWDG_Freeze_Enable.
*\*\fun     Freeze and stop IWDG while IWDG is running.
*\*\return  none
**/
void IWDG_Freeze_Enable(void)
{
    IWDG->KEY = IWDG_FREEZE;
}


/**
*\*\name    IWDG_Restore_From_Freeze.
*\*\fun     Restore from run time feeze.
*\*\return  none
**/
void IWDG_Restore_From_Freeze(void)
{
    IWDG->KEY = IWDG_UNFREEZE;
}


/**
*\*\name    IWDG_Status_Get.
*\*\fun     Checks whether the specified IWDG flag is set or not.
*\*\param   IWDG_flag :
*\*\          - IWDG_PVU_FLAG
*\*\          - IWDG_CRVU_FLAG
*\*\return  FlagStatus :
*\*\          - RESET
*\*\          - SET
**/
FlagStatus IWDG_Status_Get(IWDG_STATUS_FLAG IWDG_flag)
{
    if((IWDG->STS & IWDG_flag) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}
