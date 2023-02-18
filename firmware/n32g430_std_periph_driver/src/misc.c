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
*\*\file misc.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/
#include "misc.h"

/** MISC Driving Functions Declaration **/

/**
*\*\name    NVIC_Priority_Group_Set
*\*\fun     Configures the priority grouping: pre-emption priority and subpriority.
*\*\param   NVIC_priority_group :
*\*\            - NVIC_PER0_SUB4_PRIORITYGROUP    0 bits for pre-emption priority 4 bits for subpriority
*\*\            - NVIC_PER1_SUB3_PRIORITYGROUP    1 bits for pre-emption priority 3 bits for subpriority
*\*\            - NVIC_PER2_SUB2_PRIORITYGROUP    2 bits for pre-emption priority 2 bits for subpriority
*\*\            - NVIC_PER3_SUB1_PRIORITYGROUP    3 bits for pre-emption priority 1 bits for subpriority
*\*\            - NVIC_PER4_SUB0_PRIORITYGROUP    4 bits for pre-emption priority 0 bits for subpriorit
*\*\return  none
**/
void NVIC_Priority_Group_Set(uint32_t NVIC_priority_group)
{
    /* Set the PRIGROUP[10:8] bits according to NVIC_priority_group value */
    SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_priority_group;
}

/**
*\*\name    NVIC_Initializes
*\*\fun     Initializes the NVIC peripheral according to the specified parameters in the NVIC_structure_initializes.
*\*\param   NVIC_structure_initializes :
*\*\              - NVIC_IRQChannel :
*\*\                   -  IRQn_Type    N32G430 Interrupt Number Definition
*\*\        if NVIC_priority_group is NVIC_PER0_SUB4_PRIORITYGROUP :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PER_PRIORITY_0
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0
*\*\                   -  NVIC_SUB_PRIORITY_1
*\*\                   -  NVIC_SUB_PRIORITY_2
*\*\                   -  NVIC_SUB_PRIORITY_3
*\*\                   -  NVIC_SUB_PRIORITY_4
*\*\                   -  NVIC_SUB_PRIORITY_5
*\*\                   -  NVIC_SUB_PRIORITY_6
*\*\                   -  NVIC_SUB_PRIORITY_7
*\*\                   -  NVIC_SUB_PRIORITY_8
*\*\                   -  NVIC_SUB_PRIORITY_9
*\*\                   -  NVIC_SUB_PRIORITY_10
*\*\                   -  NVIC_SUB_PRIORITY_11
*\*\                   -  NVIC_SUB_PRIORITY_12
*\*\                   -  NVIC_SUB_PRIORITY_13
*\*\                   -  NVIC_SUB_PRIORITY_14
*\*\                   -  NVIC_SUB_PRIORITY_15
*\*\        if NVIC_priority_group is NVIC_PER1_SUB3_PRIORITYGROUP :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PER_PRIORITY_0
*\*\                   -  NVIC_PER_PRIORITY_1
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0 to NVIC_SUB_PRIORITY_7
*\*\        if NVIC_priority_group is NVIC_PER2_SUB2_PRIORITYGROUP :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PER_PRIORITY_0 to NVIC_PER_PRIORITY_3
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0 to NVIC_SUB_PRIORITY_3
*\*\        if NVIC_priority_group is NVIC_PER3_SUB1_PRIORITYGROUP :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PER_PRIORITY_0 to NVIC_PER_PRIORITY_7
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0
*\*\                   -  NVIC_SUB_PRIORITY_1
*\*\        if NVIC_priority_group is NVIC_PER4_SUB0_PRIORITYGROUP :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PER_PRIORITY_0
*\*\                   -  NVIC_PER_PRIORITY_1
*\*\                   -  NVIC_PER_PRIORITY_2
*\*\                   -  NVIC_PER_PRIORITY_3
*\*\                   -  NVIC_PER_PRIORITY_4
*\*\                   -  NVIC_PER_PRIORITY_5
*\*\                   -  NVIC_PER_PRIORITY_6
*\*\                   -  NVIC_PER_PRIORITY_7
*\*\                   -  NVIC_PER_PRIORITY_8
*\*\                   -  NVIC_PER_PRIORITY_9
*\*\                   -  NVIC_PER_PRIORITY_10
*\*\                   -  NVIC_PER_PRIORITY_11
*\*\                   -  NVIC_PER_PRIORITY_12
*\*\                   -  NVIC_PER_PRIORITY_13
*\*\                   -  NVIC_PER_PRIORITY_14
*\*\                   -  NVIC_PER_PRIORITY_15
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0
*\*\              - NVIC_IRQChannelCmd :
*\*\                   -  ENABLE
*\*\                   -  DISABLE
*\*\return  none
**/
void NVIC_Initializes(NVIC_InitType* NVIC_structure_initializes)
{
    uint32_t temp_priority_value = 0x00, temp_pre_value = 0x00, temp_sub_value = 0x0F;

    if (NVIC_structure_initializes->NVIC_IRQChannelCmd != DISABLE)
    {
        /* Compute the Corresponding IRQ Priority */
        temp_priority_value = \
        (NVIC_PRIORITYGROUP_MASK - ((SCB->AIRCR) & NVIC_PRIORITYGROUP_MASK)) >> SCB_AIRCR_OFFSET;
        
        temp_pre_value      = (NVIC_PRE_SUB_SUM - temp_priority_value);
        temp_sub_value      = temp_sub_value >> temp_priority_value;

        temp_priority_value = \
        (uint32_t)NVIC_structure_initializes->NVIC_IRQChannelPreemptionPriority << temp_pre_value;

        temp_priority_value |= \
        NVIC_structure_initializes->NVIC_IRQChannelSubPriority & temp_sub_value;

        temp_priority_value = temp_priority_value << NVIC_IP_OFFSET;

        NVIC->IP[NVIC_structure_initializes->NVIC_IRQChannel] = temp_priority_value;

        /* Enable the Selected IRQ Channels */
        NVIC->ISER[NVIC_structure_initializes->NVIC_IRQChannel >> NVIC_ISER_BIT_LENGTH] = \
        (uint32_t)0x01 << (NVIC_structure_initializes->NVIC_IRQChannel & NVIC_IRQCHANNEL_MASK);
    }
    else
    {
        /* Disable the Selected IRQ Channels */
        NVIC->ICER[NVIC_structure_initializes->NVIC_IRQChannel >> NVIC_ISER_BIT_LENGTH] = \
        (uint32_t)0x01 << (NVIC_structure_initializes->NVIC_IRQChannel & NVIC_IRQCHANNEL_MASK);
    }
}

/**
*\*\name    NVIC_Vector_Table_Set
*\*\fun     Sets the vector table location and Offset.
*\*\param   NVIC_vecter_table specifies if the vector table is in RAM or FLASH memory.
*\*\        This parameter can be one of the following values:
*\*\            - NVIC_VECTTAB_RAM
*\*\            - NVIC_VECTTAB_FLASH
*\*\param   offset Vector Table base offset field. This value must be a multiple of 0x200.
*\*\return  none
**/
void NVIC_Vector_Table_Set(uint32_t NVIC_vecter_table, uint32_t offset)
{
    SCB->VTOR = NVIC_vecter_table | (offset & (uint32_t)NVIC_VECTTAB_MASK);
}

/**
*\*\name    NVIC_System_Low_Power_Enable
*\*\fun     Selects the condition for the system to enter low power mode.
*\*\param   low_power_mode Specifies the new mode for the system to enter low power mode.
*\*\        This parameter can be one of the following values:
*\*\            - NVIC_LP_SEVONPEND
*\*\            - NVIC_LP_SLEEPDEEP
*\*\            - NVIC_LP_SLEEPONEXIT
*\*\return  none
 */
void NVIC_System_LowPower_Enable(uint8_t low_power_mode)
{
    SCB->SCR |= low_power_mode;
}

/**
*\*\name    NVIC_System_Low_Power_Disable
*\*\fun     Selects the condition for the system to enter low power mode.
*\*\param   low_power_mode :
*\*\            - NVIC_LP_SEVONPEND
*\*\            - NVIC_LP_SLEEPDEEP
*\*\            - NVIC_LP_SLEEPONEXIT
*\*\return  none
 */
void NVIC_System_Low_Power_Disable(uint8_t low_power_mode)
{
    SCB->SCR &= (uint32_t)(~(uint32_t)low_power_mode);
}

/**
*\*\name  SysTick_Clock_Source_Set
*\*\fun   Configures the SysTick clock source.
*\*\param systick_clock_source :
*\*\       - SYSTICK_CLKSOURCE_HCLK_DIV8    External clock selected as SysTick clock source.
*\*\       - SYSTICK_CLKSOURCE_HCLK         AHB clock selected as SysTick clock source.
*\*\return  none
 */
void SysTick_Clock_Source_Set(uint32_t systick_clock_source)
{
    if (systick_clock_source == SYSTICK_CLKSOURCE_HCLK)
    {
        SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
    }
    else
    {
        SysTick->CTRL &= SYSTICK_CLKSOURCE_HCLK_DIV8;
    }
}


