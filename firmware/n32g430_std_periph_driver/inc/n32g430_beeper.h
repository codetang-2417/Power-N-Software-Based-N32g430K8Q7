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
*\*\file n32g430_beeper.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32G430_BEEPER_H__
#define __N32G430_BEEPER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

/* Beeper clock source */
#define BEEPER_CLK_SOURCE_APB        (BEEPER_CTRL_CLKSEL_0)  /* APB clock */
#define BEEPER_CLK_SOURCE_LSI        (BEEPER_CTRL_CLKSEL_1)  /* LSI clock */
#define BEEPER_CLK_SOURCE_LSE        (BEEPER_CTRL_CLKSEL)    /* LSE clock */


#define BEEPER_ENABLE                (BEERPER_CTRL_BEEPEN)   /* Enable Beeper */
#define BEEPER_DISABLE               (~BEERPER_CTRL_BEEPEN)  /* Disable Beeper */

/* Beeper reverse enable */
#define BEEPER_INV_ENABLE            (BEERPER_CTRL_INVEN)    /* Only one output, the other output is off */
#define BEEPER_INV_DISABLE           (~BEERPER_CTRL_INVEN)   /* Both outputs are on, and the outputs are complementary */

/* Bypass the selected clock signal to the output ports define */
#define BEEPER_BYPASS                (BEEPER_CTRL_BYPASSEN)

/* Mask Define */
#define BEEPER_DIV_MASK              (~BEEPER_CTRL_BEEPDIV)
#define BEEPER_CLK_MASK              (~BEEPER_CTRL_CLKSEL)
#define BEEPER_FREQUENCY_MASK        (~BEEPER_CTRL_PSC)

#define BEEPER_PSC_BIT_MASK          (16U)
#define BEEPER_BEEPDIV_BIT_MASK      (4U)

void BEEPER_Reset(void);
void BEEPER_Clock_Select(uint32_t clock_selection);
void BEEPER_APB_Clock_Prescale_Set(uint32_t prescale_factor);
void BEEPER_Div_Factor_Select(uint32_t div_factor);
void BEEPER_Initialize(uint32_t clock_selection, uint32_t prescale_factor, uint32_t div_factor);
void BEEPER_Bypass_Clock_Signal(void);
void BEEPER_Inverted_Enable(void);
void BEEPER_Inverted_Disable(void);
void BEEPER_Enable(void);
void BEEPER_Disable(void);

#ifdef __cplusplus
}
#endif

#endif /* __N32G430_BEEPER_H__ */

