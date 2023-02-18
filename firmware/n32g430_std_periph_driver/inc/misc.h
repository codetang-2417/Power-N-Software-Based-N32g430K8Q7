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
*\*\file misc.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#ifndef __MISC_H__
#define __MISC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

/** MISC Driving Functions Declaration **/

/** NVIC Init Structure definition **/
typedef struct
{
    uint8_t NVIC_IRQChannel; /* Specifies the IRQ channel to be enabled or disabled. */

    uint8_t NVIC_IRQChannelPreemptionPriority; /* Specifies the pre-emption priority for the IRQ channel
                                                  specified in NVIC_IRQChannel. */

    uint8_t NVIC_IRQChannelSubPriority; /* Specifies the subpriority level for the IRQ channel specified
                                           in NVIC_IRQChannel. */

    FunctionalState NVIC_IRQChannelCmd; /* Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                           will be enabled or disabled. */
} NVIC_InitType;

/** MISC driver modules **/
#define AIRCR_VECTKEY_MASK       ((uint32_t)0x05FA0000) /* access key */

/** Vector_Table_Base **/
#define NVIC_VECTTAB_RAM         ((uint32_t)0x20000000) /* RAM start address*/
#define NVIC_VECTTAB_FLASH       ((uint32_t)0x08000000) /* FLASH start address*/
#define NVIC_VECTTAB_MASK        (SCB_VTOR_TBLOFF)

/** System_Low_Power **/
#define NVIC_LP_SEVONPEND        (SCB_SCR_SEVONPEND)
#define NVIC_LP_SLEEPDEEP        (SCB_SCR_SLEEPDEEP)
#define NVIC_LP_SLEEPONEXIT      (SCB_SCR_SLEEPONEXIT)

/** Preemption_Sub_Priority_Group **/
#define NVIC_PER0_SUB4_PRIORITYGROUP (SCB_AIRCR_PRIGROUP7) /* 0 bits for pre-emption priority 4 bits for subpriority */
#define NVIC_PER1_SUB3_PRIORITYGROUP (SCB_AIRCR_PRIGROUP6) /* 1 bits for pre-emption priority 3 bits for subpriority */
#define NVIC_PER2_SUB2_PRIORITYGROUP (SCB_AIRCR_PRIGROUP5) /* 2 bits for pre-emption priority 2 bits for subpriority */
#define NVIC_PER3_SUB1_PRIORITYGROUP (SCB_AIRCR_PRIGROUP4) /* 3 bits for pre-emption priority 1 bits for subpriority */
#define NVIC_PER4_SUB0_PRIORITYGROUP (SCB_AIRCR_PRIGROUP3) /* 4 bits for pre-emption priority 0 bits for subpriority */
#define NVIC_PRIORITYGROUP_MASK      (SCB_AIRCR_PRIGROUP)  /* PRIGROUP[2:0] bits (Priority group) */
#define NVIC_IRQCHANNEL_MASK         ((uint8_t)0x1F) 
#define NVIC_ISER_BIT_LENGTH         ((uint8_t)0x05)
#define NVIC_PRE_SUB_SUM             ((uint8_t)0x04)
#define SCB_AIRCR_OFFSET             ((uint8_t)REG_BIT8_OFFSET) 
#define NVIC_IP_OFFSET               ((uint8_t)REG_BIT4_OFFSET) 

/** Preemption_Priority_Group **/
#define NVIC_PER_PRIORITY_0           ((uint8_t)0x00)
#define NVIC_PER_PRIORITY_1           ((uint8_t)0x01)
#define NVIC_PER_PRIORITY_2           ((uint8_t)0x02)
#define NVIC_PER_PRIORITY_3           ((uint8_t)0x03)
#define NVIC_PER_PRIORITY_4           ((uint8_t)0x04)
#define NVIC_PER_PRIORITY_5           ((uint8_t)0x05)
#define NVIC_PER_PRIORITY_6           ((uint8_t)0x06)
#define NVIC_PER_PRIORITY_7           ((uint8_t)0x07)
#define NVIC_PER_PRIORITY_8           ((uint8_t)0x08)
#define NVIC_PER_PRIORITY_9           ((uint8_t)0x09)
#define NVIC_PER_PRIORITY_10          ((uint8_t)0x0A)
#define NVIC_PER_PRIORITY_11          ((uint8_t)0x0B)
#define NVIC_PER_PRIORITY_12          ((uint8_t)0x0C)
#define NVIC_PER_PRIORITY_13          ((uint8_t)0x0D)
#define NVIC_PER_PRIORITY_14          ((uint8_t)0x0E)
#define NVIC_PER_PRIORITY_15          ((uint8_t)0x0F)

/** Sub_Priority_Group **/
#define NVIC_SUB_PRIORITY_0           ((uint8_t)0x00)
#define NVIC_SUB_PRIORITY_1           ((uint8_t)0x01)
#define NVIC_SUB_PRIORITY_2           ((uint8_t)0x02)
#define NVIC_SUB_PRIORITY_3           ((uint8_t)0x03)
#define NVIC_SUB_PRIORITY_4           ((uint8_t)0x04)
#define NVIC_SUB_PRIORITY_5           ((uint8_t)0x05)
#define NVIC_SUB_PRIORITY_6           ((uint8_t)0x06)
#define NVIC_SUB_PRIORITY_7           ((uint8_t)0x07)
#define NVIC_SUB_PRIORITY_8           ((uint8_t)0x08)
#define NVIC_SUB_PRIORITY_9           ((uint8_t)0x09)
#define NVIC_SUB_PRIORITY_10          ((uint8_t)0x0A)
#define NVIC_SUB_PRIORITY_11          ((uint8_t)0x0B)
#define NVIC_SUB_PRIORITY_12          ((uint8_t)0x0C)
#define NVIC_SUB_PRIORITY_13          ((uint8_t)0x0D)
#define NVIC_SUB_PRIORITY_14          ((uint8_t)0x0E)
#define NVIC_SUB_PRIORITY_15          ((uint8_t)0x0F)

/** SysTick_clock_source **/
#define SYSTICK_CLKSOURCE_HCLK_DIV8  (~SysTick_CTRL_CLKSOURCE)
#define SYSTICK_CLKSOURCE_HCLK       (SysTick_CTRL_CLKSOURCE)

/** MISC_Exported_Functions **/
void NVIC_Priority_Group_Set(uint32_t NVIC_priority_group);
void NVIC_Initializes(NVIC_InitType* NVIC_structure_initializes);
void NVIC_Vector_Table_Set(uint32_t NVIC_vecter_table, uint32_t offset);
void NVIC_System_LowPower_Enable(uint8_t low_power_mode);
void NVIC_System_Low_Power_Disable(uint8_t low_power_mode);
void SysTick_Clock_Source_Set(uint32_t systick_clock_source);

#ifdef __cplusplus
}
#endif

#endif /* __MISC_H__ */

