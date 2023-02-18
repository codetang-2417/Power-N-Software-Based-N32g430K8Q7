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
*\*\file n32g430_wwdg.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/


#ifndef __N32G430_WWDG_H__
#define __N32G430_WWDG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"


#define WWDG_PRESCALER_DIV1             ((uint32_t)0x00000000)
#define WWDG_PRESCALER_DIV2             ((uint32_t)WWDG_CFG_TIMERB0)
#define WWDG_PRESCALER_DIV4             ((uint32_t)WWDG_CFG_TIMERB1)
#define WWDG_PRESCALER_DIV8             ((uint32_t)(WWDG_CFG_TIMERB1 | WWDG_CFG_TIMERB0))


/** WWDG registers bit address in the alias region **/
#define WWDG_OFFADDR                    (WWDG_BASE - PERIPH_BASE)

/** Alias word address of EWINT bit **/
#define CFG_OFFADDR                     (WWDG_OFFADDR + 0x04)
#define EWINT_BIT                       (0x10)
#define CFG_EWINT_BB                    (PERIPH_BB_BASE + (CFG_OFFADDR * 32) + (EWINT_BIT * 4))

/** CTRL register bit mask **/
#define CTRL_ACTB_SET                   ((uint32_t)WWDG_CTRL_ACTB)

/* CFG register bit mask **/
#define CFG_TIMERB_MASK                 ((uint32_t)0xFFFF3FFF)
#define CFG_W_MASK                      ((uint32_t)0xFFFFC000)
#define BIT_MASK                        ((uint16_t)0x3FFF)


void WWDG_Reset(void);
void WWDG_Prescaler_Division_Set(uint32_t prescaler_division);
void WWDG_Window_Value_Set(uint16_t window_value);
void WWDG_Interrupt_Enable(void);
void WWDG_Counter_Value_Set(uint16_t counter_value);
void WWDG_Enable(uint16_t counter_value);
FlagStatus WWDG_EWINTF_Flag_Get(void);
void WWDG_EWINTF_Flag_Clear(void);



#endif /* __N32G430_WWDG_H__ */

