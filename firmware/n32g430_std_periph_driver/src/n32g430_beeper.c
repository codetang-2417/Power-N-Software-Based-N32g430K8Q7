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
*\*\file n32g430_beeper.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#include "n32g430_beeper.h"
#include "n32g430_rcc.h"

/**
*\*\name    BEEPER_Reset.
*\*\fun     Reset the BEEPER register to it's default reset values.
*\*\param   none.
*\*\return  none. 
**/
void BEEPER_Reset(void)
{
	  RCC_APB2_Peripheral_Reset(RCC_APB2_PERIPH_BEEPER);   
}

/**
*\*\name    BEEPER_Clock_Select.
*\*\fun     Beeper clock selection.
*\*\param   clock_selection:  
*\*\          - BEEPER_CLK_SOURCE_APB 
*\*\          - BEEPER_CLK_SOURCE_LSI 
*\*\          - BEEPER_CLK_SOURCE_LSE 
*\*\return  none. 
**/
void BEEPER_Clock_Select(uint32_t clock_selection)
{
	  BEEPER->CTRL &= BEEPER_CLK_MASK;
      BEEPER->CTRL |= clock_selection;    
}

/**
*\*\name    BEEPER_APB_Clock_Prescale_Set.
*\*\fun     Set BEEPER APB clock prescale factor.
*\*\param   prescale_factor:  if LSI or LSE clock is selected, this parameter is ignored
*\*\          - 0 ~ 63  if prescale_factor > 0 and prescale_factor < 64, the APB clock frequency is divided by (prescale_factor + 1)
*\*\return  none. 
**/
void BEEPER_APB_Clock_Prescale_Set(uint32_t prescale_factor)
{
	  BEEPER->CTRL &= BEEPER_FREQUENCY_MASK;
	  BEEPER->CTRL |= (prescale_factor << BEEPER_PSC_BIT_MASK);
}

/**
*\*\name    BEEPER_Div_Factor_Select.
*\*\fun     Beeper division factor selection.
*\*\param   div_factor:  
*\*\          - 0 ~ 511  if div_factor is x, output frequency value divided by (x + 1) * 2
*\*\return  none. 
**/
void BEEPER_Div_Factor_Select(uint32_t div_factor)
{     BEEPER->CTRL &= BEEPER_DIV_MASK;
      BEEPER->CTRL |= (div_factor << BEEPER_BEEPDIV_BIT_MASK);
}

/**
*\*\name    BEEPER_Initialize.
*\*\fun     Init Beeper.
*\*\param   clock_selection:  
*\*\          - BEEPER_CLK_SOURCE_APB 
*\*\          - BEEPER_CLK_SOURCE_LSI 
*\*\          - BEEPER_CLK_SOURCE_LSE
*\*\param   prescale_factor:  if LSI or LSE clock is selected, this parameter is ignored
*\*\          - 0 ~ 63  if prescale_factor > 0 and prescale_factor < 64, the APB clock frequency is divided by (prescale_factor + 1)
*\*\param   div_factor:  
*\*\          - 0 ~ 511  if div_factor is x, output frequency value divided by (x + 1) * 2
*\*\return  none. 
**/
void BEEPER_Initialize(uint32_t clock_selection, uint32_t prescale_factor, uint32_t div_factor)
{
	  BEEPER_Clock_Select(clock_selection);
	  BEEPER_APB_Clock_Prescale_Set(prescale_factor);
	  BEEPER_Div_Factor_Select(div_factor);
}


/**
*\*\name    BEEPER_Bypass_Clock_Signal.
*\*\fun     Bypass the selected clock signal to the output ports.
*\*\param   none. 
*\*\return  none. 
**/
void BEEPER_Bypass_Clock_Signal(void)
{
	  BEEPER->CTRL |= BEEPER_BYPASS;
}


/**
*\*\name    BEEPER_Inverted_Enable.
*\*\fun     Beeper complementary output enable.
*\*\param   none. 
*\*\return  none. 
**/
void BEEPER_Inverted_Enable(void)
{
      BEEPER->CTRL |= BEEPER_INV_ENABLE;
}

/**
*\*\name    BEEPER_Inverted_Disable.
*\*\fun     Beeper complementary output disable.
*\*\param   none. 
*\*\return  none. 
**/
void BEEPER_Inverted_Disable(void)
{
      BEEPER->CTRL &= BEEPER_INV_DISABLE;
}


/**
*\*\name    BEEPER_Enable.
*\*\fun     Enable beeper.
*\*\param   none. 
*\*\return  none. 
**/
void BEEPER_Enable(void)
{
      BEEPER->CTRL |= BEEPER_ENABLE;
}

/**
*\*\name    BEEPER_Disable.
*\*\fun     Disable beeper.
*\*\param   none. 
*\*\return  none. 
**/
void BEEPER_Disable(void)
{
      BEEPER->CTRL &= BEEPER_DISABLE;
}


