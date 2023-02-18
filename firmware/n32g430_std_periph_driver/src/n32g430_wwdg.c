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
*\*\file n32g430_wwdg.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#include "n32g430_wwdg.h"
#include "n32g430_rcc.h"


/**
*\*\name    WWDG_Reset.
*\*\fun     Resets the WWDG peripheral registers to their default reset values.
*\*\return  none
**/
void WWDG_Reset(void)
{
    RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_WWDG);
}


/**
*\*\name    WWDG_Prescaler_Division_Set.
*\*\fun     Set the WWDOG Prescaler Division Value.
*\*\param   prescaler_division : 
*\*\          - WWDG_PRESCALER_DIV1   WWDG Counter Clock (PCLK1 / 4096) / 1
*\*\          - WWDG_PRESCALER_DIV2   WWDG Counter Clock (PCLK1 / 4096) / 2
*\*\          - WWDG_PRESCALER_DIV4   WWDG Counter Clock (PCLK1 / 4096) / 4
*\*\          - WWDG_PRESCALER_DIV8   WWDG Counter Clock (PCLK1 / 4096) / 8
*\*\return  none
**/
void WWDG_Prescaler_Division_Set(uint32_t prescaler_division)
{
    uint32_t temp_value = 0;

    /* Clear TIMERB[1:0] bits */
    temp_value = WWDG->CFG & CFG_TIMERB_MASK;

    /* Set TIMERB[1:0] bits according to prescaler_division value */
    temp_value |= prescaler_division;

    /* Store the new value */
    WWDG->CFG = temp_value;
}


/**
*\*\name    WWDG_Window_Value_Set.
*\*\fun     Set the WWDOG Window Value.
*\*\param   window_value : WWDOG Window Value
*\*\          The value range of this parameter :
*\*\          - 0x0040 ~ 0x3FFF
*\*\return  none
**/
void WWDG_Window_Value_Set(uint16_t window_value)
{
    __IO uint32_t temp_value = 0;

    /* Clear W[13:0] bits */
    temp_value = WWDG->CFG & CFG_W_MASK;

    /* Set W[13:0] bits according to window_value value */
    temp_value |= window_value & (uint32_t)BIT_MASK;

    /* Store the new value */
    WWDG->CFG = temp_value;
}


/**
*\*\name    WWDG_Interrupt_Enable.
*\*\fun     Enable WWDG Early Wakeup interrupt(EWINT).
*\*\return  none
**/
void WWDG_Interrupt_Enable(void)
{
    *(__IO uint32_t*)CFG_EWINT_BB = (uint32_t)ENABLE;
}


/**
*\*\name    WWDG_Counter_Value_Set.
*\*\fun     Set the WWDOG Counter Value.
*\*\param   counter_value : WWDOG Counter value
*\*\          The value range of this parameter :
*\*\          - 0x40 ~ 0x3FFF
*\*\return  none 
**/
void WWDG_Counter_Value_Set(uint16_t counter_value)
{
	uint32_t temp_value = 0x00U;
	temp_value = (counter_value & BIT_MASK);
    /* Write the T[13:0] bits to configure the counter value, which can be written directly 
       without read-modify-write; only write 1 to the ACTB bit to activate the window watchdog */
    WWDG->CTRL = temp_value;
}


/**
*\*\name    WWDG_Enable.
*\*\fun     Set the WWDOG Counter Value and Enable WWDOG .
*\*\param   counter_value : WWDOG Counter value
*\*\          The value range of this parameter :
*\*\          - 0x40 ~ 0x3FFF
*\*\return  none
**/
void WWDG_Enable(uint16_t counter_value)
{
    WWDG->CTRL = CTRL_ACTB_SET | counter_value;
}



/**
*\*\name    WWDG_EWINTF_Flag_Get.
*\*\fun     Get WWDOG Early Wake-up Interrupt Flag.
*\*\return  SET or RESET
**/
FlagStatus WWDG_EWINTF_Flag_Get(void)
{
    return (FlagStatus)(WWDG->STS);
}

/**
*\*\name    WWDG_EWINTF_Flag_Clear.
*\*\fun     Clear WWDOG Early Wake-up Interrupt Flag.
*\*\return  none
**/
void WWDG_EWINTF_Flag_Clear(void)
{
    WWDG->STS = (uint32_t)RESET;
}
