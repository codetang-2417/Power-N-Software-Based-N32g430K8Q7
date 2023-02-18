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
*\*\file bsp_delay.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/


#include "bsp_delay.h"

/**
 *\*\name    DBG_SysTick_Config.
 *\*\fun     System tick configuration.
 *\*\param   ticks :system tick
 *\*\return  none
**/
static uint32_t DBG_SysTick_Config(uint32_t ticks)
{ 
    if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */
                                                               
    SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
    NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */
    SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                     SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
    SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk;
    return (0);                                                  /* Function successful */
}

/**
 *\*\name    SysTick_Delay_Us.
 *\*\fun     microsecond delay.
 *\*\param   us :any number
 *\*\return  none
**/
void SysTick_Delay_Us( __IO uint32_t us)
{
	uint32_t i;	
    RCC_ClocksType RCC_Clocks;
    
    RCC_Clocks_Frequencies_Value_Get(&RCC_Clocks);
    DBG_SysTick_Config(RCC_Clocks.SysclkFreq / 1000000);
	
	for(i=0;i<us;i++)
	{
		/* When the counter value decreases to 0, bit 16 of the CRTL register will be set to 1 */
		/* When set to 1, reading this bit will clear it to 0 */
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	/* Turn off the SysTick timer */
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

/**
 *\*\name    SysTick_Delay_Us.
 *\*\fun     millisecond delay.
 *\*\param   ms :any number
 *\*\return  none
**/
void SysTick_Delay_Ms( __IO uint32_t ms)
{
	uint32_t i;	
    RCC_ClocksType RCC_Clocks;
    
    RCC_Clocks_Frequencies_Value_Get(&RCC_Clocks);
    DBG_SysTick_Config(RCC_Clocks.SysclkFreq / 1000);
	
	for(i=0;i<ms;i++)
	{
		/* When the counter value decreases to 0, bit 16 of the CRTL register will be set to 1 */
		/* When set to 1, reading this bit will clear it to 0 */
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	/* Turn off the SysTick timer */
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

