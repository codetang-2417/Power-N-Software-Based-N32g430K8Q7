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
*\*\file n32g430_tim.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/
#include "n32g430_tim.h"
#include "n32g430_rcc.h"

/**
*\*\name    TIM_Reset.
*\*\fun     Reset the TIM registers.
*\*\param   TIMx :
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\return  none
**/
void TIM_Reset(TIM_Module* TIMx)
{

    if (TIMx == TIM1)
    {
        RCC_APB2_Peripheral_Reset(RCC_APB2_PERIPH_TIM1);
    }
    else if (TIMx == TIM2)
    {
        RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_TIM2);
    }
    else if (TIMx == TIM3)
    {
        RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_TIM3);
    }
    else if (TIMx == TIM4)
    {
        RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_TIM4);
    }
    else if (TIMx == TIM5)
    {
        RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_TIM5);
    }
    else if (TIMx == TIM6)
    {
        RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_TIM6);
    }

    else if (TIMx == TIM8)
    {
        RCC_APB2_Peripheral_Reset(RCC_APB2_PERIPH_TIM8);
    }
}

/**
*\*\name    TIM_Base_Count_Mode_Set.
*\*\fun     Initializes the TIM cnt mode in up mode or down mode.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   cnt_mode
*\*\          - TIM_CNT_MODE_UP
*\*\          - TIM_CNT_MODE_DOWN
*\*\          - TIM_CNT_MODE_CENTER_ALIGN1    TIM Center Aligned Mode1
*\*\          - TIM_CNT_MODE_CENTER_ALIGN2    TIM Center Aligned Mode2
*\*\          - TIM_CNT_MODE_CENTER_ALIGN3    TIM Center Aligned Mode3
*\*\return  none
*\*\note    The counting direction of TIM6 is fixed upward counting
**/
void TIM_Base_Count_Mode_Set(TIM_Module* TIMx, uint32_t cnt_mode)
{
    uint32_t temp_value = 0;

    temp_value = TIMx->CTRL1;
    /* Reset the CMS and DIR Bits */
    temp_value &= (uint32_t)(~((uint32_t)(TIM_CTRL1_DIR | TIM_CTRL1_CAMSEL)));
    /* Set the Counter Mode */
    temp_value |= cnt_mode;
    /* Write to TIMx CTRL1 register */
    TIMx->CTRL1 = temp_value;
}

/**
*\*\name    TIM_Base_Center_Aligned_Mode_OC4_7_8_9_Trigger_Set.
*\*\param   TIMx:
*\*\          - TIM1
*\*\param   trigger_mode_in_center_aligned_mode
*\*\          - TIM_UP_COUNTING_OC4_7_8_9_TRIGGER_VALID
*\*\          - TIM_DOWN_COUNTING_OC4_7_8_9_TRIGGER_VALID
*\*\          - TIM_UP_DOWN_COUNTING_OC4_7_8_9_TRIGGER_VALID
*\*\return  none
**/
void TIM_Base_Center_Aligned_Mode_OC4_7_8_9_Trigger_Set(TIM_Module* TIMx, uint32_t trigger_mode_in_center_aligned_mode)
{
    uint32_t temp_value = 0;

    temp_value = TIMx->CTRL1;
    /* Reset the CMS and DIR Bits */
    temp_value &= (uint32_t)(~((uint32_t)TIM_CENTER_ALIGNED_OC4_7_8_9_MASK));
    /* Set the Counter Mode */
    temp_value |= trigger_mode_in_center_aligned_mode;
    /* Write to TIMx CTRL1 register */
    TIMx->CTRL1 = temp_value;
}


/**
*\*\name    TIM_Asymmetric_Enable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  none
**/
void TIM_Asymmetric_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL1 |= TIM_ASMMETRIC_ENABLE;
}

/**
*\*\name    TIM_Asymmetric_Disable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  none
**/
void TIM_Asymmetric_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL1 &= (uint32_t)(~((uint32_t)TIM_ASMMETRIC_ENABLE));
}

/**
*\*\name    TIM_Base_Auto_Reload_Set.
*\*\fun     Initializes the TIM AR value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   auto_reload：
              - [1, 0xffff]
*\*\return  none
**/
void TIM_Base_Auto_Reload_Set(TIM_Module* TIMx, uint16_t auto_reload)
{
    TIMx->AR = auto_reload;
}

/**
*\*\name    TIM_Base_Prescaler_Set.
*\*\fun     Initializes the TIM PSC value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   prescaler
*\*\return  none
**/
void TIM_Base_Prescaler_Set(TIM_Module* TIMx, uint16_t prescaler)
{
    TIMx->PSC = prescaler;
}

/**
*\*\name    TIM_Base_Reload_Mode_Set.
*\*\fun     Initializes the TIM reload mode
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   prescaler_reload_mode:
**\           - TIM_PSC_RELOAD_MODE_IMMEDIATE
**\           - TIM_PSC_RELOAD_MODE_UPDATE
*\*\return  none
**/
void TIM_Base_Reload_Mode_Set(TIM_Module* TIMx, uint16_t prescaler_reload_mode)
{
    TIMx->EVTGEN = prescaler_reload_mode;
}

/**
*\*\name    TIM_Base_Repeat_Count_Set.
*\*\fun     Initializes the TIM repeat cnt
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   repeat_cnt
*\*\          - [0,255]
*\*\return  none
**/
void TIM_Base_Repeat_Count_Set(TIM_Module* TIMx, uint8_t repeat_cnt)
{
    TIMx->REPCNT = repeat_cnt;
}

/**
*\*\name    TIM_Base_Channel1.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   channel_selection:
**\           - 1
**\             CH1 is from COMP
**\           - 0
**\             CH1 is from IO
*\*\return  none
*\*\note    not for TIM6
**/
void TIM_Base_Channel1(TIM_Module* TIMx, bool channel_selection)
{
    if(channel_selection)
    {
        TIMx->CTRL1 |= TIM_CH1_SEL;
    }
    else
    {
        TIMx->CTRL1 &= (uint32_t)(~TIM_CH1_SEL);
    }    
}

/**
*\*\name    TIM_Base_Channel2.
*\*\param   TIMx:
*\*\          - TIM2
*\*\param   channel_selection:
**\           - 1
**\             CH2 is from LSE
**\           - 0
**\             CH2 is from IO
*\*\return  none
**/
void TIM_Base_Channel2(TIM_Module* TIMx, bool channel_selection)
{
    if(channel_selection)
    {
        TIMx->CTRL1 |= TIM_CH2_SEL;
    }
    else
    {
        TIMx->CTRL1 &= (uint32_t)(~TIM_CH2_SEL);
    }    
}

/**
*\*\name    TIM_Base_Channel3.
*\*\param   TIMx:
*\*\          - TIM2
*\*\param   channel_selection:
**\           - 1
**\             CH3 is from LSI
**\           - 0
**\             CH3 is from IO
*\*\return  none
**/
void TIM_Base_Channel3(TIM_Module* TIMx, bool channel_selection)
{
    if(channel_selection)
    {
        TIMx->CTRL1 |= TIM_CH3_SEL;
    }
    else
    {
        TIMx->CTRL1 &= (uint32_t)(~TIM_CH3_SEL);
    }    
}

/**
*\*\name    TIM_Base_Channel4.
*\*\param   TIMx:
*\*\          - TIM2
*\*\param   channel_selection:
**\           - 1
**\             CH4 is from HSE/128
**\           - 0
**\             CH4 is from IO
*\*\return  none
**/
void TIM_Base_Channel4(TIM_Module* TIMx, bool channel_selection)
{
    if(channel_selection)
    {
        TIMx->CTRL1 |= TIM_CH4_SEL;
    }
    else
    {
        TIMx->CTRL1 &= (uint32_t)(~TIM_CH4_SEL);
    }    
}

/**
*\*\name    TIM_Base_OCrefClear.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM8
*\*\param   OCrefClear_selection:
**\           - 1
**\             OCrefClear is from ETR
**\           - 0
**\             OCrefClear is from COMP
*\*\return  none 
*\*\note    Not for TIM5 and TIM6
**/
void TIM_Base_OCrefClear(TIM_Module* TIMx, bool OCrefClear_selection)
{
    if (OCrefClear_selection)
    {
        TIMx->CTRL1 |= TIM_OCREF_CLEAR_SEL;
    }
    else
    {
        TIMx->CTRL1 &= (uint32_t)(~TIM_OCREF_CLEAR_SEL);
    }
}

/**
*\*\name    TIM_Base_Init.
*\*\fun     Initializes the TIMx Time Base Unit peripheral according to
*\*\        the specified parameters in the TIM_TimeBaseInitStruct.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   TIM_TimeBaseInitStruct:
*\*\          - refer to the definition of TIM_TimeBaseInitType
*\*\return  none
**/
void TIM_Base_Initialize(TIM_Module* TIMx, TIM_TimeBaseInitType* TIM_TimeBaseInitStruct)
{
    if (TIMx != TIM6)
    {
        TIM_Base_Count_Mode_Set(TIMx, TIM_TimeBaseInitStruct->CntMode);
        TIM_Clock_Division_Set(TIMx, TIM_TimeBaseInitStruct->ClkDiv);
    }
    else
    {
        /* none */
    }

    TIM_Base_Auto_Reload_Set(TIMx, TIM_TimeBaseInitStruct->Period);

    TIM_Base_Prescaler_Set(TIMx, TIM_TimeBaseInitStruct->Prescaler);

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        TIM_Base_Repeat_Count_Set(TIMx,TIM_TimeBaseInitStruct->RepetCnt);
    }
    else
    {
        /* none */
    }

    TIM_Base_Reload_Mode_Set(TIMx, TIM_PSC_RELOAD_MODE_IMMEDIATE);

    if ((TIMx != TIM6))
    {
        TIM_Base_Channel1(TIMx, TIM_TimeBaseInitStruct->CapCh1Sel);
    }
    else 
    {
        /* none */
    }
    
    if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) )
    {
        TIM_Base_OCrefClear(TIMx, TIM_TimeBaseInitStruct->CapEtrClrFromCompEn);
    }
    else 
    {
        /* none */
    }
    
    if(TIMx == TIM2)
    {
        TIM_Base_Channel2(TIMx, TIM_TimeBaseInitStruct->CapCh2Sel);
        TIM_Base_Channel3(TIMx, TIM_TimeBaseInitStruct->CapCh3Sel);
        TIM_Base_Channel4(TIMx, TIM_TimeBaseInitStruct->CapCh4Sel);
    }
    else 
    {
        /* none */
    }
}

void TIM_Base_Struct_Initialize(TIM_TimeBaseInitType* TIM_TimeBaseInitStruct)
{
    /* Set the default configuration */
    TIM_TimeBaseInitStruct->Period    = 0xFFFF;
    TIM_TimeBaseInitStruct->Prescaler = 0x0000;
    TIM_TimeBaseInitStruct->ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseInitStruct->CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseInitStruct->RepetCnt  = 0x0000;

    TIM_TimeBaseInitStruct->CapCh1Sel    = false;
    TIM_TimeBaseInitStruct->CapCh2Sel    = false;
    TIM_TimeBaseInitStruct->CapCh3Sel    = false;
    TIM_TimeBaseInitStruct->CapCh4Sel    = false;
    TIM_TimeBaseInitStruct->CapEtrClrFromCompEn = false;
    TIM_TimeBaseInitStruct->CapEtrSelFromTscEn  = false;    
}
/**
*\*\name    TIM_Base_Count_Set.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   count:
*\*\return  none
**/
void TIM_Base_Count_Set(TIM_Module* TIMx, uint16_t count)
{
    TIMx->CNT= count;
}
/**
*\*\name    TIM_Base_Count_Get.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\return  the value of count register
**/
uint16_t TIM_Base_Count_Get(TIM_Module* TIMx)
{
    /* Get the value of count register */
    return TIMx->CNT;
}

/**
*\*\name    TIM_Auto_Reload_Get.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\return  the value of auto reload register
**/
uint16_t TIM_Auto_Reload_Get(TIM_Module* TIMx)
{
    /* Get the value of auto reload register */
    return TIMx->AR;
}

/**
*\*\name    TIM_Base_Prescaler_Get.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\return  the value of prescaler register
**/
uint16_t TIM_Base_Prescaler_Get(TIM_Module* TIMx)
{
    /* Get the value of prescaler register */
    return TIMx->PSC;
}


/**
*\*\name    TIM_Enable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\return  none
**/
void TIM_On(TIM_Module* TIMx)
{
    TIMx->CTRL1 |= TIM_ON;
}

/**
*\*\name    TIM_Disable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\return  none
**/
void TIM_Off(TIM_Module* TIMx)
{
    TIMx->CTRL1 &= (uint32_t)(~((uint32_t)TIM_ON));
}

/**
*\*\name    TIM_Output_Channel1_Preload_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_preload 
*\*\          - TIM_OC_PRELOAD_ENABLE
*\*\          - TIM_OC_PRELOAD_DISABLE
*\*\return  none
**/
void TIM_Output_Channel1_Preload_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_preload)
{
    uint16_t temp_value = 0;

    temp_value = TIMx->CCMOD1;
    /* Reset the OC1PE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC1_PRELOAD_MASK);
    /* Enable or Disable the Output Compare Preload feat_value |= (uint16_t)TIM_output_channel_preload;*/
    temp_value |= TIM_output_channel_preload;
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel2_Preload_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_preload 
*\*\          - TIM_OC_PRELOAD_ENABLE
*\*\          - TIM_OC_PRELOAD_DISABLE
*\*\return  none
**/
void TIM_Output_Channel2_Preload_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_preload)
{
    uint16_t temp_value = 0;

    temp_value = TIMx->CCMOD1;
    /* Reset the OC1PE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC2_PRELOAD_MASK);
    /* Enable or Disable the Output Compare Preload feature */
    temp_value |= (uint16_t)(TIM_output_channel_preload << 8);
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel3_Preload_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_preload 
*\*\          - TIM_OC_PRELOAD_ENABLE
*\*\          - TIM_OC_PRELOAD_DISABLE
*\*\return  none
**/
void TIM_Output_Channel3_Preload_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_preload)
{
    uint16_t temp_value = 0;

    temp_value = TIMx->CCMOD2;
    /* Reset the OC1PE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC3_PRELOAD_MASK);
    /* Enable or Disable the Output Compare Preload feature */
    temp_value |= TIM_output_channel_preload;
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD2 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel4_Preload_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_preload 
*\*\          - TIM_OC_PRELOAD_ENABLE
*\*\          - TIM_OC_PRELOAD_DISABLE
*\*\return  none
**/
void TIM_Output_Channel4_Preload_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_preload)
{
    uint16_t temp_value = 0;

    temp_value = TIMx->CCMOD2;
    /* Reset the OC1PE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC4_PRELOAD_MASK);
    /* Enable or Disable the Output Compare Preload feature */
    temp_value |= (uint16_t)(TIM_output_channel_preload << 8);
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD2 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel5_Preload_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   TIM_output_channel_preload 
*\*\          - TIM_OC_PRELOAD_ENABLE
*\*\          - TIM_OC_PRELOAD_DISABLE
*\*\return  none
**/
void TIM_Output_Channel5_Preload_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_preload)
{
    uint16_t temp_value = 0;

    temp_value = TIMx->CCMOD3;
    /* Reset the OC1PE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC5_PRELOAD_MASK);
    /* Enable or Disable the Output Compare Preload feature */
    temp_value |= TIM_output_channel_preload;
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel6_Preload_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\param   TIM_output_channel_preload 
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_Output_Channel6_Preload_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_preload)
{
    uint16_t temp_value = 0;

    temp_value = TIMx->CCMOD3;
    /* Reset the OC1PE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC6_PRELOAD_MASK);
    /* Enable or Disable the Output Compare Preload feature */
    temp_value |=  (uint16_t)(TIM_output_channel_preload << 8);
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel7_Preload_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\param   TIM_output_channel_preload 
*\*\          - TIM_OC_PRELOAD_ENABLE
*\*\          - TIM_OC_PRELOAD_DISABLE
*\*\return  none
**/
void TIM_Output_Channel7_Preload_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_preload)
{
    if(TIM_OC_PRELOAD_ENABLE == TIM_output_channel_preload)
    {
        TIMx->CCMOD2 |= TIM_OC7_PRELOAD_ENABLE;
    }
    else if(TIM_OC_PRELOAD_DISABLE == TIM_output_channel_preload)
    {
        TIMx->CCMOD2 &= (uint32_t)(~TIM_OC7_PRELOAD_ENABLE);
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_Output_Channel8_Preload_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\param   TIM_output_channel_preload 
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_Output_Channel8_Preload_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_preload)
{
    if(TIM_OC_PRELOAD_ENABLE == TIM_output_channel_preload)
    {
        TIMx->CCMOD2 |= TIM_OC8_PRELOAD_ENABLE;
    }
    else if(TIM_OC_PRELOAD_DISABLE == TIM_output_channel_preload)
    {
        TIMx->CCMOD2 &= (uint32_t)(~TIM_OC8_PRELOAD_ENABLE);
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_Output_Channel9_Preload_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\param   TIM_output_channel_preload 
*\*\          - TIM_OC_PRE_LOAD_ENABLE
*\*\          - TIM_OC_PRE_LOAD_DISABLE
*\*\return  none
**/
void TIM_Output_Channel9_Preload_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_preload)
{
    if(TIM_OC_PRELOAD_ENABLE == TIM_output_channel_preload)
    {
        TIMx->CCMOD2 |= TIM_OC9_PRELOAD_ENABLE;
    }
    else if(TIM_OC_PRELOAD_DISABLE == TIM_output_channel_preload)
    {
        TIMx->CCMOD2 &= (uint32_t)(~TIM_OC9_PRELOAD_ENABLE);
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_Auto_Reload_Preload_Enable
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\return  none
**/
void TIM_Auto_Reload_Preload_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL1 |= TIM_AR_PRELOAD_ENABLE;
}

/**
*\*\name    TIM_Auto_Reload_Preload_Disable
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\return  none
**/
void TIM_Auto_Reload_Preload_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL1 &= (uint32_t) ~((uint32_t)TIM_AR_PRELOAD_ENABLE);
}


/**
*\*\name    TIM_Update_Event_Enable
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\return  none
**/
void TIM_Update_Event_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL1 &= (uint32_t) ~((uint32_t)TIM_UPDATE_EVENT_DISABLE);
}

/**
*\*\name    TIM_Update_Event_Disable
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
**/
void TIM_Update_Event_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL1 |= TIM_UPDATE_EVENT_DISABLE;
}

/**
*\*\name    TIM_Update_Request_Source_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   TIM_update_source:
*\*\          - TIM_UPDATE_SRC_REGULAR    Source of update is counter overflow/underflow
*\*\          - TIM_UPDATE_SRC_GLOBAL     Source of update is the counter overflow/underflow
*\*\                                      or the setting of UG bit, or an update generation
*\*\                                      through the slave mode controller.
*\*\note    TIM6 does note support slave mode and underflow counter
*\*\return  none
**/
void TIM_Update_Request_Source_Set(TIM_Module* TIMx, uint16_t TIM_update_source)
{
    if (TIM_update_source != TIM_UPDATE_SRC_GLOBAL)
    {
        /* Set the URS Bit */
        TIMx->CTRL1 |= TIM_UPRS_REGULAR;
    }
    else
    {
        /* Reset the URS Bit */
        TIMx->CTRL1 &= (uint32_t) ~((uint32_t)TIM_UPRS_REGULAR);
    }
}

/**
*\*\fun     Enables or disables the preload register of auto reload register.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   TIM_event_source 
*\*\          - TIM_EVT_SRC_UPDATE    Timer update Event source
*\*\          - TIM_EVT_SRC_CC1       Timer Capture Compare 1 Event source
*\*\          - TIM_EVT_SRC_CC2       Timer Capture Compare 2 Event source
*\*\          - TIM_EVT_SRC_CC3       Timer Capture Compare 3 Event source
*\*\          - TIM_EVT_SRC_CC4       Timer Capture Compare 4 Event source
*\*\          - TIM_EVT_SRC_COM       Timer COM event source
*\*\          - TIM_EVT_SRC_TRIG      Timer Trigger Event source
*\*\          - TIM_EVT_SRC_BREAK     Timer Break event source
*\*\return  none
*\*\note    TIM6 and TIM7 can only generate an update event. 
*\*\     TIM_EVT_SRC_COM and TIM_EVT_SRC_BREAK are used only with TIM1 and TIM8.
**/
void TIM_Event_Generate(TIM_Module* TIMx, uint16_t TIM_event_source)
{
    TIMx->EVTGEN = TIM_event_source;
}

/**
*\*\name    TIM_Commutation_Event_Enable
*\*\fun     Enables the preload register of auto reload register.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  none
**/
void TIM_Commutation_Event_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL2 |= TIM_CCUSEL_COM_AND_TRIG;
}

/**
*\*\name    TIM_Commutation_Event_Disable
*\*\fun     Disables the preload register of auto reload register.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  none
**/
void TIM_Commutation_Event_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL2 &= (uint32_t) ~((uint32_t)TIM_CCUSEL_MASK);
}

/**
*\*\name    TIM_Capture_Compare_Control_Preload_Enable
*\*\fun     Disables the preload register of auto reload register.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
**/
void TIM_Capture_Compare_Control_Preload_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL2 |= TIM_CCPCTL_PRELOAD;
}

/**
*\*\name    TIM_Capture_Compare_Control_Preload_Disable
*\*\fun     Disables the preload register of auto reload register.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
**/
void TIM_Capture_Compare_Control_Preload_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL2 &= (uint32_t) ~((uint32_t)TIM_CCPCTL_PRELOAD);
}

/**
*\*\name    TIM_Compare1_Set
*\*\fun     Sets the TIMx Capture compare1 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   compare1:
*\*\          - [0,0xffff]
**/
void TIM_Compare1_Set(TIM_Module* TIMx, uint16_t compare1)
{
    uint32_t temp_value = TIMx->CCDAT1;
    temp_value &= (uint32_t)(~TIM_CCDAT1_MASK);
    temp_value |= compare1;
    TIMx->CCDAT1 = temp_value;
}

/**
*\*\name    TIM_Compare2_Set
*\*\fun     Sets the TIMx Capture compare2 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   compare2:
*\*\          - [0,0xffff]
**/
void TIM_Compare2_Set(TIM_Module* TIMx, uint16_t compare2)
{
    uint32_t temp_value = TIMx->CCDAT2;
    temp_value &= (uint32_t)(~TIM_CCDAT2_MASK);
    temp_value |= compare2;
    TIMx->CCDAT2 = temp_value;
}

/**
*\*\name    TIM_Compare3_Set
*\*\fun     Sets the TIMx Capture compare3 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   compare3:
*\*\          - [0,0xffff]
**/
void TIM_Compare3_Set(TIM_Module* TIMx, uint16_t compare3)
{
    uint32_t temp_value = TIMx->CCDAT3;
    temp_value &= (uint32_t)(~TIM_CCDAT3_MASK);
    temp_value |= compare3;
    TIMx->CCDAT3 = temp_value;
}

/**
*\*\name    TIM_Compare4_Set
*\*\fun     Sets the TIMx Capture compare4 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   compare4:
*\*\          - [0,0xffff]
**/
void TIM_Compare4_Set(TIM_Module* TIMx, uint16_t compare4)
{
    uint32_t temp_value = TIMx->CCDAT4;
    temp_value &= (uint32_t)(~TIM_CCDAT4_MASK);
    temp_value |= compare4;
    TIMx->CCDAT4 = temp_value;
}

/**
*\*\name    TIM_Compare5_Set
*\*\fun     Sets the TIMx Capture compare5 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   compare5:
*\*\          - [0,0xffff]
**/
void TIM_Compare5_Set(TIM_Module* TIMx, uint16_t compare5)
{
    TIMx->CCDAT5 = compare5;  
}

/**
*\*\name    TIM_Compare6_Set
*\*\fun     Sets the TIMx Capture compare6 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   compare6:
*\*\          - [0,0xffff]
**/
void TIM_Compare6_Set(TIM_Module* TIMx, uint16_t compare6)
{
    TIMx->CCDAT6 = compare6;
}

/**
*\*\name    TIM_Compare7_Set
*\*\fun     Sets the TIMx Capture compare7 Register value
*\*\param   TIMx
*\*\          - TIM1
*\*\param   compare7:
*\*\          - [0,0xffff]
*\*\return  none
*\*\note    only for TIM1
**/
void TIM_Compare7_Set(TIM_Module* TIMx, uint16_t compare7)
{
    TIMx->CCDAT7 = compare7;
}

/**
*\*\name    TIM_Compare8_Set
*\*\fun     Sets the TIMx Capture compare8 Register value
*\*\param   TIMx
*\*\          - TIM1
*\*\param   compare8:
*\*\          - [0,0xffff]
*\*\return  none
*\*\note    only for TIM1
**/
void TIM_Compare8_Set(TIM_Module* TIMx, uint16_t compare8)
{
    TIMx->CCDAT8 = compare8;
}

/**
*\*\name    TIM_Compare9_Set
*\*\fun     Sets the TIMx Capture compare9 Register value
*\*\param   TIMx
*\*\          - TIM1
*\*\param   compare9:
*\*\          - [0,0xffff]
*\*\return  none
*\*\note    only for TIM1
**/
void TIM_Compare9_Set(TIM_Module* TIMx, uint16_t compare9)
{
    TIMx->CCDAT9 = compare9;
}

/**
*\*\name    TIM_Compare1_D_Set
*\*\fun     Sets the CCDDAT1[16:31] in TIM1_CCDAT1 register
*\*\param   TIMx
*\*\          - TIM1
*\*\param   compare1:
*\*\          - [0,0xffff]
*\*\return  none
*\*\note    only for TIM1
**/
void TIM_Compare1_D_Set(TIM_Module* TIMx, uint16_t compare1)
{
    uint32_t temp_value = TIMx->CCDAT1;
    temp_value &= (uint32_t)(~TIM_CCDDAT1_MASK);
    temp_value |= (((uint32_t)compare1) << TIM_CCDDAT1_OFFSET);
    TIMx->CCDAT1 = temp_value;
}

/**
*\*\name    TIM_Compare2_D_Set
*\*\fun     Sets the CCDDAT2[16:31] in TIM1_CCDAT2 register
*\*\param   TIMx
*\*\          - TIM1
*\*\param   compare2:
*\*\          - [0,0xffff]
*\*\return  none
*\*\note    only for TIM1
**/
void TIM_Compare2_D_Set(TIM_Module* TIMx, uint16_t compare2)
{
    uint32_t temp_value = TIMx->CCDAT2;
    temp_value &= (uint32_t)(~TIM_CCDDAT2_MASK);
    temp_value |= (((uint32_t)compare2) << TIM_CCDDAT2_OFFSET);
    TIMx->CCDAT2 = temp_value;
}

/**
*\*\name    TIM_Compare3_D_Set
*\*\fun     Sets the CCDDAT3[16:31] in TIM1_CCDAT3 register
*\*\param   TIMx
*\*\          - TIM1
*\*\param   compare3:
*\*\          - [0,0xffff]
*\*\return  none
*\*\note    only for TIM1
**/
void TIM_Compare3_D_Set(TIM_Module* TIMx, uint16_t compare3)
{
    uint32_t temp_value = TIMx->CCDAT3;
    temp_value &= (uint32_t)(~TIM_CCDDAT3_MASK);
    temp_value |= (((uint32_t)compare3) << TIM_CCDDAT3_OFFSET);
    TIMx->CCDAT3 = temp_value;
}

/**
*\*\name    TIM_Compare4_D_Set
*\*\fun     Sets the CCDDAT4[16:31] in TIM1_CCDAT4 register
*\*\param   TIMx
*\*\          - TIM1
*\*\param   compare4:
*\*\          - [0,0xffff]
*\*\return  none
*\*\note    only for TIM1
**/
void TIM_Compare4_D_Set(TIM_Module* TIMx, uint16_t compare4)
{
    uint32_t temp_value = TIMx->CCDAT4;
    temp_value &= (uint32_t)(~TIM_CCDDAT4_MASK);
    temp_value |= (((uint32_t)compare4) << TIM_CCDDAT4_OFFSET);
    TIMx->CCDAT4 = temp_value;
}

/**
*\*\name    TIM_Compare_Capture1_Get 
*\*\fun     Get the TIMx compare1 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\return  uin16_t:
*\*\          - [0 , 0xffff]
**/
uint16_t TIM_Compare_Capture1_Get(TIM_Module* TIMx)
{
    return (uint16_t)(TIMx->CCDAT1);
}

/**
*\*\name    TIM_Compare_Capture2_Get 
*\*\fun     Get the TIMx Compare2 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\return  uin16_t:
*\*\          - [0 , 0xffff]
**/
uint16_t TIM_Compare_Capture2_Get(TIM_Module* TIMx)
{
    return (uint16_t)(TIMx->CCDAT2);
}

/**
*\*\name    TIM_Compare_Capture3_Get 
*\*\fun     Get the TIMx Compare3 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\return  uin16_t:
*\*\          - [0 , 0xffff]
**/
uint16_t TIM_Compare_Capture3_Get(TIM_Module* TIMx)
{
    return (uint16_t)(TIMx->CCDAT3);
}

/**
*\*\name    TIM_Compare_Capture4_Get 
*\*\fun     Get the TIMx Compare4 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\return  uin16_t:
*\*\          - [0 , 0xffff]
**/
uint16_t TIM_Compare_Capture4_Get(TIM_Module* TIMx)
{
    return (uint16_t)(TIMx->CCDAT4);
}

/**
*\*\name    TIM_Compare_Capture5_Get 
*\*\fun     Get the TIMx Compare5 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  uin16_t:
*\*\          - [0 , 0xffff]
**/
uint16_t TIM_Compare_Capture5_Get(TIM_Module* TIMx)
{
    return TIMx->CCDAT5;
}

/**
*\*\name    TIM_Compare_Capture6_Get
*\*\fun     Get the TIMx Compare6 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  uin16_t:
*\*\          - [0 , 0xffff]
**/
uint16_t TIM_Compare_Capture6_Get(TIM_Module* TIMx)
{
    return TIMx->CCDAT6;
}

/**
*\*\name    TIM_Compare_Capture7_Get
*\*\fun     Sets the TIMx Capture compare7 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  uint16_t:
*\*\          - [0 , 0xffff]         
*\*\note    only for TIM1
**/
uint16_t TIM_Compare_Capture7_Get(TIM_Module* TIMx)
{
    return TIMx->CCDAT7;
}

/**
*\*\name    TIM_Compare_Capture8_Get
*\*\fun     Sets the TIMx Capture compare8 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  uint16_t:
*\*\          - [0 , 0xffff]         
*\*\note    only for TIM1
**/
uint16_t TIM_Compare_Capture8_Get(TIM_Module* TIMx)
{
    return TIMx->CCDAT8;
}

/**
*\*\name    TIM_Compare_Capture9_Get
*\*\fun     Sets the TIMx Capture compare9 Register value
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  uint16_t:
*\*\          - [0 , 0xffff]         
*\*\note    only for TIM1
**/
uint16_t TIM_Compare_Capture9_Get(TIM_Module* TIMx)
{
    return TIMx->CCDAT9;
}

/**
*\*\name    TIM_Compare_Capture1_D_Get
*\*\fun     Gets the CCDDAT1[16:31] in TIMx_CCDAT1 register
*\*\param   TIMx：
*\*\          - TIM1
*\*\return  uint16_t:
*\*\          - [0 , 0xffff]         
*\*\note    only for TIM1
**/
uint16_t TIM_Compare_Capture1_D_Get(TIM_Module* TIMx)
{
    return (uint16_t)((TIMx->CCDAT1 & TIM_CCDDAT1_MASK) >> 16);
}

/**
*\*\name    TIM_Compare_Capture2_D_Get
*\*\fun     Gets the CCDDAT2[16:31] in TIMx_CCDAT2 register
*\*\param   TIMx：
*\*\          - TIM1
*\*\return  uint16_t:
*\*\          - [0 , 0xffff]         
*\*\note    only for TIM1
**/
uint16_t TIM_Compare_Capture2_D_Get(TIM_Module* TIMx)
{
    return (uint16_t)((TIMx->CCDAT2 & TIM_CCDDAT2_MASK) >> 16);
}

/**
*\*\name    TIM_Compare_Capture3_D_Get
*\*\fun     Gets the CCDDAT3[16:31] in TIMx_CCDAT3 register
*\*\param   TIMx：
*\*\          - TIM1
*\*\return  uint16_t:
*\*\          - [0 , 0xffff]         
*\*\note    only for TIM1
**/
uint16_t TIM_Compare_Capture3_D_Get(TIM_Module* TIMx)
{
    return (uint16_t)((TIMx->CCDAT3 & TIM_CCDDAT3_MASK) >> 16);
}

/**
*\*\name    TIM_Compare_Capture4_D_Get
*\*\fun     Gets the CCDDAT4[16:31] in TIMx_CCDAT4 register
*\*\param   TIMx：
*\*\          - TIM1
*\*\return  uint16_t:
*\*\          - [0 , 0xffff]         
*\*\note    only for TIM1
**/
uint16_t TIM_Compare_Capture4_D_Get(TIM_Module* TIMx)
{
    return (uint16_t)((TIMx->CCDAT4 & TIM_CCDDAT4_MASK) >> 16);
}


/**
*\*\name    TIM_Trigger_Source_Select
*\*\fun     Selects the Input Trigger source
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_trigger_source
*\*\          - TIM_TRIG_SEL_IN_TR0     Internal Trigger 0
*\*\          - TIM_TRIG_SEL_IN_TR1     Internal Trigger 1
*\*\          - TIM_TRIG_SEL_IN_TR2     Internal Trigger 2
*\*\          - TIM_TRIG_SEL_IN_TR3     Internal Trigger 3
*\*\          - TIM_TRIG_SEL_TI1F_ED    TI1 Edge Detector
*\*\          - TIM_TRIG_SEL_TI1FP1     Filtered Timer Input 1
*\*\          - TIM_TRIG_SEL_TI2FP2     Filtered Timer Input 2
*\*\          - TIM_TRIG_SEL_ETRF       External Trigger input
*\*\return  none
**/
void TIM_Trigger_Source_Select(TIM_Module* TIMx, uint16_t TIM_trigger_source)
{
    uint16_t temp_value = 0;

    /* Get the TIMx SMCTRL register value */
    temp_value = TIMx->SMCTRL;
    /* Reset the TS Bits */
    temp_value &= (uint16_t)(~((uint16_t)TIM_TRIG_SEL_MASK));
    /* Set the Input Trigger source */
    temp_value |= TIM_trigger_source;
    /* Write to TIMx SMCTRL */
    TIMx->SMCTRL = temp_value;
}


/**
*\*\name    Input_Channel1_Config
*\*\fun     Configure the TI1 as Input.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   input_channel_polarity The Input Polarity.
*\*\  This parameter can be one of the following values:
*\*\          - TIM_IC_POLARITY_RISING
*\*\          - TIM_IC_POLARITY_FALLING
*\*\param   input_channel_selection specifies the input to be used.
*\*\  This parameter can be one of the following values:
*\*\          - TIM_IC_SELECTION_DIRECTTI      TIM Input 1 is selected to be connected to IC1.
*\*\          - TIM_IC_SELECTION_INDIRECTTI    TIM Input 1 is selected to be connected to IC2.
*\*\          - TIM_IC_SELECTION_TRC           TIM Input 1 is selected to be connected to TRC.
*\*\param   input_channel_filter Specifies the Input Capture Filter.
*\*\            [0x00 0xF]
*\*\return  none
**/
void Input_Channel1_Config(TIM_Module* TIMx, uint16_t input_channel_polarity, 
                               uint16_t input_channel_selection, uint16_t input_channel_filter)
{
    uint16_t temp_ccmod1 = 0;
    uint32_t temp_ccen  = 0;
    /* Disable the Channel 1: Reset the CC1E Bit */
    TIMx->CCEN &= (uint32_t) ~((uint32_t)TIM_CC1EN);
    temp_ccmod1 = TIMx->CCMOD1;
    temp_ccen  = TIMx->CCEN;
    /* Select the Input and set the filter */
    temp_ccmod1 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_IC1_SELECTION_MASK)) & ((uint16_t) ~((uint16_t)TIM_IC1_FILTER_MASK)));
    temp_ccmod1 |= (uint16_t)(input_channel_selection | (uint16_t)(input_channel_filter << (uint16_t)4));

    if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
    {
        /* Select the Polarity and set the CC1E Bit */
        temp_ccen &= (uint32_t) ~((uint32_t)(TIM_CC1P));
        temp_ccen |= (uint32_t)(input_channel_polarity | (uint32_t)TIM_CC1EN);
    }
    else
    {
        /* Select the Polarity and set the CC1E Bit */
        temp_ccen &= (uint32_t) ~((uint32_t)(TIM_CC1P | TIM_CC1NP));
        temp_ccen |= (uint32_t)(input_channel_polarity | (uint32_t)TIM_CC1EN);
    }

    /* Write to TIMx CCMOD1 and CCEN registers */
    TIMx->CCMOD1 = temp_ccmod1;
    TIMx->CCEN   = temp_ccen;
}

/**
*\*\name    Input_Channel2_Config
*\*\fun     Configure the TI2 as Input.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   input_channel_polarity The Input Polarity.
*\*\  This parameter can be one of the following values:
*\*\          - TIM_IC_POLARITY_RISING
*\*\          - TIM_IC_POLARITY_FALLING
*\*\param   input_channel_selection specifies the input to be used.
*\*\  This parameter can be one of the following values:
*\*\          - TIM_IC_SELECTION_DIRECTTI      TIM Input 2 is selected to be connected to IC2.
*\*\          - TIM_IC_SELECTION_INDIRECTTI    TIM Input 2 is selected to be connected to IC1.
*\*\          - TIM_IC_SELECTION_TRC           TIM Input 2 is selected to be connected to TRC.
*\*\param   input_channel_filter Specifies the Input Capture Filter.
*\*\            [0x00 0x0F]
*\*\return  none
**/
void Input_Channel2_Config(TIM_Module* TIMx, uint16_t input_channel_polarity, 
                           uint16_t input_channel_selection, uint16_t input_channel_filter)
{
    uint16_t temp_ccmod1 = 0;
    uint32_t temp_ccen = 0, temp_value = 0;
    /* Disable the Channel 2: Reset the CC2E Bit */
    TIMx->CCEN &= (uint32_t) ~((uint32_t)TIM_CC2EN);
    temp_ccmod1 = TIMx->CCMOD1;
    temp_ccen = TIMx->CCEN;
    temp_value = (uint32_t)(input_channel_polarity << 4);
    /* Select the Input and set the filter */
    temp_ccmod1 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_IC2_SELECTION_MASK)) & ((uint16_t) ~((uint16_t)TIM_IC2_FILTER_MASK)));
    temp_ccmod1 |= (uint16_t)(input_channel_filter << 12);
    temp_ccmod1 |= (uint16_t)(input_channel_selection << 8);

    if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
    {
        /* Select the Polarity and set the CC2E Bit */
        temp_ccen &= (uint32_t) ~((uint32_t)(TIM_CC2P));
        temp_ccen |= (uint32_t)(temp_value | (uint32_t)TIM_CC2EN);
    }
    else
    {
        /* Select the Polarity and set the CC2E Bit */
        temp_ccen &= (uint32_t) ~((uint32_t)(TIM_CC2P | TIM_CC2NP));
        temp_ccen |= (uint32_t)(input_channel_polarity | (uint32_t)TIM_CC2EN);
    }

    /* Write to TIMx CCMOD1 and CCEN registers */
    TIMx->CCMOD1 = temp_ccmod1;
    TIMx->CCEN   = temp_ccen;
}


/**
*\*\name    Input_Channel3_Config
*\*\fun     Configure the TI3 as Input.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   input_channel_polarity The Input Polarity.
*\*\  This parameter can be one of the following values:
*\*\          - TIM_IC_POLARITY_RISING
*\*\          - TIM_IC_POLARITY_FALLING
*\*\param   input_channel_selection specifies the input to be used.
*\*\  This parameter can be one of the following values:
*\*\          - TIM_IC_SELECTION_DIRECTTI      TIM Input 3 is selected to be connected to IC3.
*\*\          - TIM_IC_SELECTION_INDIRECTTI    TIM Input 3 is selected to be connected to IC4.
*\*\          - TIM_IC_SELECTION_TRC           TIM Input 3 is selected to be connected to TRC.
*\*\param   input_channel_filter Specifies the Input Capture Filter.
*\*\            [0x00 0x0F]
*\*\return  none
**/
void Input_Channel3_Config(TIM_Module* TIMx, uint16_t input_channel_polarity, 
                           uint16_t input_channel_selection, uint16_t input_channel_filter)
{
    uint16_t temp_ccmod2 = 0;
    uint32_t temp_ccen = 0, temp_value = 0;
    /* Disable the Channel 3: Reset the CC3E Bit */
    TIMx->CCEN &= (uint32_t) ~((uint32_t)TIM_CC3EN);
    temp_ccmod2 = TIMx->CCMOD2;
    temp_ccen = TIMx->CCEN;
    temp_value = (uint32_t)(input_channel_polarity << 8);
    /* Select the Input and set the filter */
    temp_ccmod2 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_IC3_SELECTION_MASK)) & ((uint16_t) ~((uint16_t)TIM_IC3_FILTER_MASK)));
    temp_ccmod2 |= (uint16_t)(input_channel_selection | (uint16_t)(input_channel_filter << (uint16_t)4));

    if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
    {
        /* Select the Polarity and set the CC3E Bit */
        temp_ccen &= (uint32_t) ~((uint32_t)(TIM_CC3P));
        temp_ccen |= (uint32_t)(temp_value | (uint32_t)TIM_CC3EN);
    }
    else
    {
        /* Select the Polarity and set the CC3E Bit */
        temp_ccen &= (uint32_t) ~((uint32_t)(TIM_CC3P | TIM_CC3NP));
        temp_ccen |= (uint32_t)(input_channel_polarity | (uint32_t)TIM_CC3EN);
    }

    /* Write to TIMx CCMOD2 and CCEN registers */
    TIMx->CCMOD2 = temp_ccmod2;
    TIMx->CCEN   = temp_ccen;
}

/**
*\*\name    Input_Channel4_Config
*\*\fun     Configure the TI4 as Inputt.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   input_channel_polarity The Input Polarity.
*\*\  This parameter can be one of the following values:
*\*\          - TIM_IC_POLARITY_RISING
*\*\          - TIM_IC_POLARITY_FALLING
*\*\param   input_channel_selection specifies the input to be used.
*\*\  This parameter can be one of the following values:
*\*\          - TIM_IC_SELECTION_DIRECTTI      TIM Input 4 is selected to be connected to IC4.
*\*\          - TIM_IC_SELECTION_INDIRECTTI    TIM Input 4 is selected to be connected to IC3.
*\*\          - TIM_IC_SELECTION_TRC           TIM Input 4 is selected to be connected to TRC.
*\*\param   input_channel_filter Specifies the Input Capture Filter.
*\*\            [0x00 0x0F]
*\*\return  none
**/
void Input_Channel4_Config(TIM_Module* TIMx, uint16_t input_channel_polarity, 
                           uint16_t input_channel_selection, uint16_t input_channel_filter)
{
    uint16_t temp_ccmod2 = 0;
    uint32_t temp_ccen = 0, temp_value = 0;

    /* Disable the Channel 4: Reset the CC4E Bit */
    TIMx->CCEN &= (uint32_t) ~((uint32_t)TIM_CC4EN);
    temp_ccmod2 = TIMx->CCMOD2;
    temp_ccen = TIMx->CCEN;
    temp_value = (uint32_t)(input_channel_polarity << 12);
    /* Select the Input and set the filter */
    temp_ccmod2 &= (uint16_t)((uint16_t)(~(uint16_t)TIM_IC4_SELECTION_MASK) & ((uint16_t) ~((uint16_t)TIM_IC4_FILTER_MASK)));
    temp_ccmod2 |= (uint16_t)(input_channel_selection << 8);
    temp_ccmod2 |= (uint16_t)(input_channel_filter << 12);

    if ((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
    {
        /* Select the Polarity and set the CC4E Bit */
        temp_ccen &= (uint32_t) ~((uint32_t)(TIM_CC4P));
        temp_ccen |= (uint32_t)(temp_value | (uint32_t)TIM_CC4EN);
    }
    else
    {
        /* Select the Polarity and set the CC4E Bit */
        temp_ccen &= (uint32_t) ~((uint32_t)(TIM_CC4P));
        temp_ccen |= (uint32_t)(input_channel_polarity | (uint32_t)TIM_CC4EN);
    }
    /* Write to TIMx CCMOD2 and CCEN registers */
    TIMx->CCMOD2 = temp_ccmod2;
    TIMx->CCEN   = temp_ccen;
}

/**
*\*\name    TIM_External_Trigger_Filter_Set
*\*\fun     Configures the filter of TIMx External Trigger.
*\*\param   TIMx 
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   external_trigger_filter 
*\*\          - [0x0,0xF]
*\*\return  none
**/
void TIM_External_Trigger_Filter_Set(TIM_Module* TIMx,
                                     uint16_t external_trigger_filter)
{
    /* Reset the ETRPSC Bits */
    uint16_t temp_value = TIMx->SMCTRL;
    temp_value &= (uint16_t)(~((uint16_t)TIM_EXT_TRIG_FILTER_MASK));
    /* Set the Prescaler, the Filter value and the Polarity */
    temp_value |= (uint16_t)(external_trigger_filter << (uint16_t)8);
    TIMx->SMCTRL = temp_value;
}


/**
*\*\name    TIM_External_Trigger_Prescaler_Set
*\*\fun     Configures the prescaler of  External Trigger (ETR).
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   external_trigger_prescaler 
*\*\          - TIM_EXT_TRG_PSC_OFF ETRP Prescaler OFF.
*\*\          - TIM_EXT_TRG_PSC_DIV2 ETRP frequency divided by 2.
*\*\          - TIM_EXT_TRG_PSC_DIV4 ETRP frequency divided by 4.
*\*\          - TIM_EXT_TRG_PSC_DIV8 ETRP frequency divided by 8.
*\*\return  - none
**/
void TIM_External_Trigger_Prescaler_Set(TIM_Module* TIMx,
                                        uint16_t external_trigger_prescaler)
{
    /* Reset the ETRPSC Bits */
    uint16_t temp_value = TIMx->SMCTRL;
    temp_value &= (uint16_t)(~((uint16_t)TIM_EXT_TRG_PSC_MASK));
    /* Set the Prescaler, the Filter value and the Polarity */
    temp_value |= (uint16_t)(external_trigger_prescaler);
    TIMx->SMCTRL = temp_value;
}

/**
*\*\name    TIM_External_Trigger_Polarity_Set
*\*\\fun Configures the polarity of TIMx External Trigger.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   external_trigger_polarity T
*\*\          - TIM_EXT_TRIG_POLARITY_INVERTED active low or falling edge active.
*\*\          - TIM_EXT_TRIG_POLARITY_NONINVERTED active high or rising edge active.
*\*\return  none
**/
void TIM_External_Trigger_Polarity_Set(TIM_Module* TIMx,
                                       uint16_t external_trigger_polarity)
{
    if(external_trigger_polarity == TIM_EXT_TRIG_POLARITY_INVERTED)
    {
        TIMx->SMCTRL |= TIM_EXT_TRIG_POLARITY_INVERTED;
    }
    else
    {
        TIMx->SMCTRL &= (uint16_t)(~((uint16_t)TIM_EXT_TRIG_POLARITY_INVERTED));
    }
}

/**
*\*\name    TIM_Clock_Division_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   clock_division 
 *   This parameter can be one of the following value:
*\*\          - TIM_CLK_DIV1 TDTS = Tck_tim
*\*\          - TIM_CLK_DIV2 TDTS = 2*Tck_tim
*\*\          - TIM_CLK_DIV4 TDTS = 4*Tck_tim
*\*\return  none
*\*\note
*\*\          - not for TIM6
**/
void TIM_Clock_Division_Set(TIM_Module* TIMx, uint16_t clock_division)
{
    TIMx->CTRL1 &= (uint32_t) ~((uint32_t)TIM_CLK_DIV_MASK);
    /* Set the CKD value */
    TIMx->CTRL1 |= clock_division;
}


/**
*\*\name    TIM_Internal_Clock_Set.
*\*\fun     Configures the TIMx internal Clock
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\return  none
**/
void TIM_Internal_Clock_Set(TIM_Module* TIMx)
{
    /* Disable slave mode to clock the prescaler directly with the internal clock */
    TIMx->SMCTRL &= (uint16_t)(~((uint16_t)TIM_SLAVE_MODE_MASK));
}


/**
*\*\name    TIM_Input_Capture1_Prescaler_Set
*\*\fun     Sets the TIMx Input Capture 1 prescaler.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_input_capture_prescaler 
*\*\          - TIM_IC_PSC_DIV1    no prescaler
*\*\          - TIM_IC_PSC_DIV2    capture is done once every 2 events
*\*\          - TIM_IC_PSC_DIV4    capture is done once every 4 events
*\*\          - TIM_IC_PSC_DIV8    capture is done once every 8 events
*\*\return  none
**/
void TIM_Input_Capture1_Prescaler_Set(TIM_Module* TIMx, uint16_t TIM_input_capture_prescaler)
{
    TIMx->CCMOD1 &= (uint16_t) ~((uint16_t)TIM_IC1_PSC_MASK);
    /* Set the IC1PSC value */
    TIMx->CCMOD1 |= TIM_input_capture_prescaler;    
}

/**
*\*\name    TIM_Input_Capture2_Prescaler_Set
*\*\fun     Sets the TIMx Input Capture 2 prescaler.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_input_capture_prescaler 
*\*\          - TIM_IC_PSC_DIV1    no prescaler
*\*\          - TIM_IC_PSC_DIV2    capture is done once every 2 events
*\*\          - TIM_IC_PSC_DIV4    capture is done once every 4 events
*\*\          - TIM_IC_PSC_DIV8    capture is done once every 8 events
*\*\return  none
**/
void TIM_Input_Capture2_Prescaler_Set(TIM_Module* TIMx, uint16_t TIM_input_capture_prescaler)
{
    TIMx->CCMOD1 &= (uint16_t) ~((uint16_t)TIM_IC2_PSC_MASK);
    /* Set the IC1PSC value */
    TIMx->CCMOD1 |= (uint16_t)(TIM_input_capture_prescaler << 8);    
}

/**
*\*\name    TIM_Input_Capture3_Prescaler_Set
*\*\fun     Sets the TIMx Input Capture 3 prescaler.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_input_capture_prescaler 
*\*\          - TIM_IC_PSC_DIV1    no prescaler
*\*\          - TIM_IC_PSC_DIV2    capture is done once every 2 events
*\*\          - TIM_IC_PSC_DIV4    capture is done once every 4 events
*\*\          - TIM_IC_PSC_DIV8    capture is done once every 8 events
*\*\return  none 
**/
void TIM_Input_Capture3_Prescaler_Set(TIM_Module* TIMx, uint16_t TIM_input_capture_prescaler)
{
    TIMx->CCMOD2 &= (uint16_t) ~((uint16_t)TIM_IC3_PSC_MASK);
    /* Set the IC1PSC value */
    TIMx->CCMOD2 |= TIM_input_capture_prescaler;    
}

/**
*\*\name    TIM_Input_Capture4_Prescaler_Set
*\*\fun     Sets the TIMx Input Capture 4 prescaler.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_input_capture_prescaler 
*\*\          - TIM_IC_PSC_DIV1    no prescaler
*\*\          - TIM_IC_PSC_DIV2    capture is done once every 2 events
*\*\          - TIM_IC_PSC_DIV4    capture is done once every 4 events
*\*\          - TIM_IC_PSC_DIV8    capture is done once every 8 events
*\*\return  none 
**/
void TIM_Input_Capture4_Prescaler_Set(TIM_Module* TIMx, uint16_t TIM_input_capture_prescaler)
{
    TIMx->CCMOD2 &= (uint16_t) ~((uint16_t)TIM_IC4_PSC_MASK);
    /* Set the IC1PSC value */
    TIMx->CCMOD2 |= (TIM_input_capture_prescaler << 8);    
}

/**
*\*\name    TIM_Internal_Trig_To_Ext_Set.
*\*\fun     Configures the TIMx Internal Trigger as External Clock
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   input_trigger_source:
*\*\          - TIM_TRIG_SEL_IN_TR0    Internal Trigger 0
*\*\          - TIM_TRIG_SEL_IN_TR1    Internal Trigger 1
*\*\          - TIM_TRIG_SEL_IN_TR2    Internal Trigger 2
*\*\          - TIM_TRIG_SEL_IN_TR3    Internal Trigger 3
*\*\return  none
**/
void TIM_Internal_Trig_To_Ext_Set(TIM_Module* TIMx, uint16_t input_trigger_source)
{
    /* Select the Internal Trigger */
    TIM_Trigger_Source_Select(TIMx, input_trigger_source);

    /* Select the External clock mode1 */
    TIMx->SMCTRL |= TIM_SLAVE_MODE_EXT1;
}


/**
*\*\name    TIM_Trigger_As_External_Clock.
*\*\fun     Configures the TIMx Trigger as External Clock
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   external_clock_source
*\*\          - TIM_EXT_CLK_SRC_TI1ED    TI1 Edge Detector
*\*\          - TIM_EXT_CLK_SRC_TI1      Filtered Timer Input 1
*\*\          - TIM_EXT_CLK_SRC_TI2      Filtered Timer Input 2
*\*\param   input_channel_polarity specifies the TIx Polarity.
*\*\          - TIM_IC_POLARITY_RISING
*\*\          - TIM_IC_POLARITY_FALLING
*\*\param   input_channel_filter 
*\*\          - [0x0 0xF]
*\*\return  none
**/
void TIM_Trigger_As_External_Clock(TIM_Module* TIMx, uint16_t external_clock_source, 
                                   uint16_t input_channel_polarity, 
                                   uint16_t input_channel_filter)
{
    /* Configure the Timer Input Clock Source */
    if (external_clock_source == TIM_EXT_CLK_SRC_TI2)
    {
        Input_Channel2_Config(TIMx, input_channel_polarity, TIM_IC_SELECTION_DIRECTTI, input_channel_filter);
    }
    else
    {
        Input_Channel1_Config(TIMx, input_channel_polarity, TIM_IC_SELECTION_DIRECTTI, input_channel_filter);
    }
    /* Select the Trigger source */
    TIM_Trigger_Source_Select(TIMx, external_clock_source);
    /* Select the External clock mode1 */
    TIMx->SMCTRL |= TIM_SLAVE_MODE_EXT1;
}

/**
*\*\name    TIM_External_Clock_Mode1_Set.
*\*\fun     Configures the External clock Mode1
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   external_trigger_prescaler
*\*\          - TIM_EXT_TRG_PSC_OFF     ETRP Prescaler OFF.
*\*\          - TIM_EXT_TRG_PSC_DIV2    ETRP frequency divided by 2.
*\*\          - TIM_EXT_TRG_PSC_DIV4    ETRP frequency divided by 4.
*\*\          - TIM_EXT_TRG_PSC_DIV8    ETRP frequency divided by 8.
 * @param external_trigger_polarity The external Trigger Polarity.
*\*\          - TIM_EXT_TRIG_POLARITY_INVERTED active low or falling edge active.
*\*\          - TIM_EXT_TRIG_POLARITY_NONINVERTED active high or rising edge active.
*\*\param   external_trigger_filter 
*\*\          - [0x0 0xF]
*\*\return  none
**/
void TIM_External_Clock_Mode1_Set(TIM_Module* TIMx, uint16_t external_trigger_prescaler,
                                         uint16_t external_trigger_polarity, 
                                         uint16_t external_trigger_filter)
{
    uint16_t temp_value = 0;

    TIM_External_Trigger_Filter_Set(TIMx, external_trigger_filter);
    TIM_External_Trigger_Polarity_Set(TIMx, external_trigger_polarity);
    TIM_External_Trigger_Prescaler_Set(TIMx, external_trigger_prescaler);

    /* Get the TIMx SMCTRL register value */
    temp_value = TIMx->SMCTRL;
    /* Reset the SMS Bits */
    temp_value &= (uint16_t)(~((uint16_t)TIM_SLAVE_MODE_MASK));
    /* Select the External clock mode1 */
    temp_value |= TIM_SLAVE_MODE_EXT1;
    /* Select the Trigger selection : ETRF */
    temp_value &= (uint16_t)(~((uint16_t)TIM_TRIG_SEL_MASK));
    temp_value |= TIM_TRIG_SEL_ETRF;
    /* Write to TIMx SMCTRL */
    TIMx->SMCTRL = temp_value;
}

/**
*\*\name    TIM_ConfigExtClkMode2.
*\*\fun     Configures the External clock Mode1
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   external_trigger_prescaler
*\*\          - TIM_EXT_TRG_PSC_OFF ETRP Prescaler OFF.
*\*\          - TIM_EXT_TRG_PSC_DIV2 ETRP frequency divided by 2.
*\*\          - TIM_EXT_TRG_PSC_DIV4 ETRP frequency divided by 4.
*\*\          - TIM_EXT_TRG_PSC_DIV8 ETRP frequency divided by 8.
 * @param external_trigger_polarity The external Trigger Polarity.
*\*\          - TIM_EXT_TRIG_POLARITY_INVERTED active low or falling edge active.
*\*\          - TIM_EXT_TRIG_POLARITY_NONINVERTED active high or rising edge active.
*\*\param   external_trigger_filter 
*\*\          - [0x0 0xF]
*\*\return  none
**/
void TIM_External_Clock_Mode2_Set(TIM_Module* TIMx,
                                  uint16_t external_trigger_prescaler,
                                  uint16_t external_trigger_polarity,
                                  uint16_t external_trigger_filter)
{
    TIM_External_Trigger_Filter_Set(TIMx, external_trigger_filter);

    TIM_External_Trigger_Polarity_Set(TIMx, external_trigger_polarity);

    TIM_External_Trigger_Prescaler_Set(TIMx, external_trigger_prescaler);

    TIMx->SMCTRL |= TIM_EXT_CLOCK_MODE2_ENABLE;

}

/**
*\*\name    TIM_Slave_Mode_Select.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_slave_mode:
*\*\          - TIM_SLAVE_MODE_RESET    Rising edge of the selected trigger signal (TRGI) re-initializes
*\*\                                    the counter and triggers an update of the registers.
*\*\          - TIM_SLAVE_MODE_GATED    The counter clock is enabled when the trigger signal (TRGI) is high.
*\*\          - TIM_SLAVE_MODE_TRIG     The counter starts at a rising edge of the trigger TRGI.
*\*\          - TIM_SLAVE_MODE_EXT1     Rising edges of the selected trigger (TRGI) clock the counter.
*\*\return  none
**/
void TIM_Slave_Mode_Select(TIM_Module* TIMx, uint16_t TIM_slave_mode)
{
    /* Reset the SMS Bits */
    TIMx->SMCTRL &= (uint16_t) ~((uint16_t)TIM_SLAVE_MODE_MASK);
    /* Select the Slave Mode */
    TIMx->SMCTRL |= TIM_slave_mode;
}

/**
*\*\name    TIM_Break_And_Dead_Time_Set.
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_slave_mode:
*\*\          - TIM_MASTER_SLAVE_MODE_ENABLE    synchronization between the current timer
*\*\                                            and its slaves (through TRGO).
*\*\          - TIM_MASTER_SLAVE_MODE_DISABLE   No action
*\*\return  none
**/
void TIM_Master_Slave_Mode_Set(TIM_Module* TIMx, uint16_t TIM_master_slave_mode)
{
    /* Reset the MSM Bit */
    TIMx->SMCTRL &= (uint16_t) ~((uint16_t)TIM_MASTER_SLAVE_MODE_MASK);

    /* Set or Reset the MSM Bit */
    TIMx->SMCTRL |= TIM_master_slave_mode;
}



/**
*\*\name    TIM_Output_Trigger_Select.
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   TIM_TRGOSource
*\*\          For all TIMx:
*\*\          - TIM_TRGO_SRC_RESET           The UG bit in the TIM_EVTGEN register is used as the trigger output (TRGO).
*\*\          - TIM_TRGO_SRC_ENABLE          The Counter Enable CEN is used as the trigger output (TRGO).
*\*\          - TIM_TRGO_SRC_UPDATE          The update event is selected as the trigger output (TRGO).
*\*\          For all TIMx except TIM6:
*\*\          - TIM_TRGO_SRC_OC1             The trigger output sends a positive pulse when the CC1IF flag
*\*\                                         is to be set, as soon as a capture or compare match occurs (TRGO).
*\*\          - TIM_TRGO_SRC_OC1REF          OC1REF signal is used as the trigger output (TRGO).
*\*\          - TIM_TRGO_SRC_OC2REF          OC2REF signal is used as the trigger output (TRGO).
*\*\          - TIM_TRGO_SRC_OC3REF          OC3REF signal is used as the trigger output (TRGO).
*\*\          - TIM_TRGO_SRC_OC4REF          OC4REF signal is used as the trigger output (TRGO).
*\*\          For TIM1：
*\*\          - TIM_TRGO_SRC_OC4_7_8_9REF    OC4REF signal is used as the trigger output (TRGO).
*\*\return  none
**/
void TIM_Output_Trigger_Select(TIM_Module* TIMx, uint16_t TIM_trigger_output_source)
{
    /* Reset the MMS Bits */
    TIMx->CTRL2 &= (uint32_t) ~((uint32_t)TIM_TRGO_SRC_MASK);
    /* Select the TRGO source */
    TIMx->CTRL2 |= TIM_trigger_output_source;
}


/**
*\*\name    TIM_OC4REF_Trigger_To_ADC_Enable
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  none
**/
void TIM_OC4REF_Trigger_To_ADC_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL2 |= TIM_OCREF4_TRIGGER_TO_ADC_ENABLE;
}

/**
*\*\name    TIM_OC4REF_Trigger_To_ADC_Disable
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  none
**/
void TIM_OC4REF_Trigger_To_ADC_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL2 &= (uint32_t)(~TIM_OCREF4_TRIGGER_TO_ADC_ENABLE);
}


/**
*\*\name    TIM_OC7REF_Trigger_To_ADC_Enable
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  none
**/
void TIM_OC7REF_Trigger_To_ADC_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL2 |= TIM_OCREF7_TRIGGER_TO_ADC_ENABLE;
}

/**
*\*\name    TIM_OC7REF_Trigger_To_ADC_Disable
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  none
**/
void TIM_OC7REF_Trigger_To_ADC_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL2 &= (uint32_t)(~TIM_OCREF7_TRIGGER_TO_ADC_ENABLE);
}


/**
*\*\name    TIM_OC8REF_Trigger_To_ADC_Enable
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  none
**/
void TIM_OC8REF_Trigger_To_ADC_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL2 |= TIM_OCREF8_TRIGGER_TO_ADC_ENABLE;
}

/**
*\*\name    TIM_OC8REF_Trigger_To_ADC_Disable
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  none
**/
void TIM_OC8REF_Trigger_To_ADC_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL2 &= (uint32_t)(~TIM_OCREF8_TRIGGER_TO_ADC_ENABLE);
}


/**
*\*\name    TIM_OC9REF_Trigger_To_ADC_Enable
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  none
**/
void TIM_OC9REF_Trigger_To_ADC_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL2 |= TIM_OCREF9_TRIGGER_TO_ADC_ENABLE;
}

/**
*\*\name    TIM_OC9REF_Trigger_To_ADC_Disable
*\*\param   TIMx:
*\*\          - TIM1
*\*\return  none
**/
void TIM_OC9REF_Trigger_To_ADC_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL2 &= (uint32_t)(~TIM_OCREF9_TRIGGER_TO_ADC_ENABLE);
}



/**
*\*\name    TIM_One_Pulse_Mode_Select.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_slave_mode:
*\*\          - TIM_OPMODE_SINGLE
*\*\          - TIM_OPMODE_REPET
*\*\return  none
**/
void TIM_One_Pulse_Mode_Select(TIM_Module* TIMx, uint16_t TIM_one_pulse_mode)
{
    /* Reset the OPM Bit */
    TIMx->CTRL1 &= (uint32_t) ~((uint32_t)TIM_OPMODE_MASK);
    /* Configure the OPM Mode */
    TIMx->CTRL1 |= TIM_one_pulse_mode;    
}

/**
*\*name TIM_Input_Struct_Initialize
*\*\fun     Initialize the TIM_ICInitStruct
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_ICInitStruct 
*\*\          - refer to the definition of TIM_ICInitType
*\*\return  none
**/
void TIM_Input_Struct_Initialize(TIM_ICInitType* TIM_ICInitStruct)
{
    /* Set the default configuration */
    TIM_ICInitStruct->IcPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStruct->IcSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStruct->IcPrescaler = TIM_IC_PSC_DIV1;
    TIM_ICInitStruct->IcFilter    = 0x00;    
}

/**
*\*\name    TIM_Input_Channel_Initialize
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_ICInitStruct 
*\*           - refer to the definition of TIM_ICInitType
*\*\return  none
**/
void TIM_Input_Channel_Initialize(TIM_Module* TIMx, TIM_ICInitType* TIM_ICInitStruct)
{
    if (TIM_ICInitStruct->Channel == TIM_CH_1)
    {
        /* TI1 Configuration */
        Input_Channel1_Config(TIMx, TIM_ICInitStruct->IcPolarity, TIM_ICInitStruct->IcSelection, TIM_ICInitStruct->IcFilter);
        /* Set the Input Capture Prescaler value */
        TIM_Input_Capture1_Prescaler_Set(TIMx, TIM_ICInitStruct->IcPrescaler);
    }
    else if (TIM_ICInitStruct->Channel == TIM_CH_2)
    {
        /* TI2 Configuration */
        Input_Channel2_Config(TIMx, TIM_ICInitStruct->IcPolarity, TIM_ICInitStruct->IcSelection, TIM_ICInitStruct->IcFilter);
        /* Set the Input Capture Prescaler value */
        TIM_Input_Capture2_Prescaler_Set(TIMx, TIM_ICInitStruct->IcPrescaler);
    }
    else if (TIM_ICInitStruct->Channel == TIM_CH_3)
    {
        /* TI3 Configuration */
        Input_Channel3_Config(TIMx, TIM_ICInitStruct->IcPolarity, TIM_ICInitStruct->IcSelection, TIM_ICInitStruct->IcFilter);
        /* Set the Input Capture Prescaler value */
        TIM_Input_Capture3_Prescaler_Set(TIMx, TIM_ICInitStruct->IcPrescaler);
    }
    else
    {
        /* TI4 Configuration */
        Input_Channel4_Config(TIMx, TIM_ICInitStruct->IcPolarity, TIM_ICInitStruct->IcSelection, TIM_ICInitStruct->IcFilter);
        /* Set the Input Capture Prescaler value */
        TIM_Input_Capture4_Prescaler_Set(TIMx, TIM_ICInitStruct->IcPrescaler);
    }
}


/**
*\*\name    TIM_PWM_Input_Channel_Operation
*\*\fun     Configures the TIM peripheral according to the specified
 *          parameters in the TIM_ICInitStruct to measure an external PWM signal.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_ICInitStruct 
*\*           - refer to the definition of TIM_ICInitType
*\*\return  none
**/
void TIM_PWM_Input_Channel_Config(TIM_Module* TIMx, TIM_ICInitType* TIM_ICInitStruct)
{
    uint16_t input_channel_opposite_polarity  = TIM_IC_POLARITY_RISING;
    uint16_t input_channel_opposite_selection = TIM_IC_SELECTION_DIRECTTI;
    /* Select the Opposite Input Polarity */
    if (TIM_ICInitStruct->IcPolarity == TIM_IC_POLARITY_RISING)
    {
        input_channel_opposite_polarity = TIM_IC_POLARITY_FALLING;
    }
    else
    {
        input_channel_opposite_polarity = TIM_IC_POLARITY_RISING;
    }
    /* Select the Opposite Input */
    if (TIM_ICInitStruct->IcSelection == TIM_IC_SELECTION_DIRECTTI)
    {
        input_channel_opposite_selection = TIM_IC_SELECTION_INDIRECTTI;
    }
    else
    {
        input_channel_opposite_selection = TIM_IC_SELECTION_DIRECTTI;
    }
    if (TIM_ICInitStruct->Channel == TIM_CH_1)
    {
        /* TI1 Configuration */
        Input_Channel1_Config(TIMx, TIM_ICInitStruct->IcPolarity, TIM_ICInitStruct->IcSelection, TIM_ICInitStruct->IcFilter);
        /* Set the Input Capture Prescaler value */
        TIM_Input_Capture1_Prescaler_Set(TIMx, TIM_ICInitStruct->IcPrescaler);
        /* TI2 Configuration */
        Input_Channel2_Config(TIMx, input_channel_opposite_polarity, input_channel_opposite_selection, TIM_ICInitStruct->IcFilter);
        /* Set the Input Capture Prescaler value */
        TIM_Input_Capture2_Prescaler_Set(TIMx, TIM_ICInitStruct->IcPrescaler);
    }
    else
    {
        /* TI2 Configuration */
        Input_Channel2_Config(TIMx, TIM_ICInitStruct->IcPolarity, TIM_ICInitStruct->IcSelection, TIM_ICInitStruct->IcFilter);
        /* Set the Input Capture Prescaler value */
        TIM_Input_Capture2_Prescaler_Set(TIMx, TIM_ICInitStruct->IcPrescaler);
        /* TI1 Configuration */
        Input_Channel1_Config(TIMx, input_channel_opposite_polarity, input_channel_opposite_selection, TIM_ICInitStruct->IcFilter);
        /* Set the Input Capture Prescaler value */
        TIM_Input_Capture1_Prescaler_Set(TIMx, TIM_ICInitStruct->IcPrescaler);
    }
}



/**
*\*\name    TIM_Output_Channel_Polarity_Set.
*\*\fun     set the polarity of TIMx channel
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   output_channel_polarity:
**\           - TIM_OC_POLARITY_LOW
**\           - TIM_OC_POLARITY_HIGH
*\*\param   channel:
**\           - TIM_CH_1
**\           - TIM_CH_2
**\           - TIM_CH_3
**\           - TIM_CH_4
**\           - TIM_CH_5
**\           - TIM_CH_6
*\*\return  none
*\*\note    - TIM2 TIM3 TIM4 TIM5 does not support channel 5 and channel 6
**/
void TIM_Output_Channel_Polarity_Set(TIM_Module* TIMx, uint32_t output_channel_polarity, uint16_t channel)
{
    uint32_t temp_value = TIMx->CCEN;
    /* Clear the CCxEN bit */
    temp_value &= (uint32_t)(~(uint32_t)(TIM_OC_POLARITY_MASK << channel));

    /* Set the CCxEN bit */
    temp_value |= (uint32_t)(output_channel_polarity << channel);

    /* Write to TIMx CCEN register */
    TIMx->CCEN = temp_value;
}

/**
*\*\name    TIM_Output_Channel_N_Polarity_Set.
*\*\fun     set the mode of polarity of TIMx channel
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   output_channel_N_polarity:
**\           - TIM_OCN_POLARITY_LOW
**\           - TIM_OCN_POLARITY_HIGH
*\*\param   channel:
**\           - TIM_CH_1
**\           - TIM_CH_2
**\           - TIM_CH_3
**\           - TIM_CH_4
*\*\return  none
*\*\note    This function is only for TIM1 and TIM8
**/
void TIM_Output_Channel_N_Polarity_Set(TIM_Module* TIMx, uint32_t output_channel_N_polarity, uint16_t channel)
{
    uint32_t temp_value = TIMx->CCEN;
    /* Clear the CCxEN bit */
    temp_value &= (uint32_t)(~(uint32_t)(TIM_OCN_POLARITY_MASK << channel));

    /* Set the CCxEN bit */
    temp_value |= (uint32_t)(output_channel_N_polarity << channel);

    TIMx->CCEN = temp_value;
}

/**
*\*\name    TIM_Capture_Compare_Ch_Enable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   channel:
**\           - TIM_CH_1
**\           - TIM_CH_2
**\           - TIM_CH_3
**\           - TIM_CH_4
**\           - TIM_CH_5
**\           - TIM_CH_6
*\*\return  none
*\*\note    - TIM2 TIM3 TIM4 TIM5 does not support channel 5 and channel 6
**/
void TIM_Capture_Compare_Ch_Enable(TIM_Module* TIMx, uint16_t channel)
{
    TIMx->CCEN |= (uint32_t)(TIM_CAP_CMP_ENABLE << channel);
}

/**
*\*\name    TIM_Capture_Compare_Ch_Disable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   channel:
**\           - TIM_CH_1
**\           - TIM_CH_2
**\           - TIM_CH_3
**\           - TIM_CH_4
**\           - TIM_CH_5
**\           - TIM_CH_6
*\*\return  none
*\*\note    - TIM2 TIM3 TIM4 TIM5 does not support channel 5 and channel 6
**/
void TIM_Capture_Compare_Ch_Disable(TIM_Module* TIMx, uint16_t channel)
{
    TIMx->CCEN &= (uint32_t)(~(TIM_CAP_CMP_ENABLE << channel));
}

/**
*\*\name    TIM_Capture_Compare_Ch_N_Enable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   channel:
**\           - TIM_CH_1
**\           - TIM_CH_2
**\           - TIM_CH_3
**\           - TIM_CH_4
*\*\return  none
*\*\note    - TIM_CH_4 is only for TIM1, only TIM1 has CH4N.
**/
void TIM_Capture_Compare_Ch_N_Enable(TIM_Module* TIMx, uint16_t channel)
{
    TIMx->CCEN |= (uint32_t)(TIM_CAP_CMP_N_ENABLE << channel);
}

/**
*\*\name    TIM_Capture_Compare_Ch_N_Disable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   channel:
**\           - TIM_CH_1
**\           - TIM_CH_2
**\           - TIM_CH_3
**\           - TIM_CH_4
*\*\return  none
*\*\note    - TIM_CH_4 is only for TIM1, only TIM1 has CH4N.
**/
void TIM_Capture_Compare_Ch_N_Disable(TIM_Module* TIMx, uint16_t channel)
{
    TIMx->CCEN &= (uint32_t)(~(TIM_CAP_CMP_N_ENABLE << channel));
}

/**
*\*\name    TIM_CCEN_Status_Get
*\*\fun     Checks whether the specified TIM flag is set or not.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_CCEN:
*\*\          - TIM_CC1EN Bit
*\*\          - TIM_CC1NEN Bit
*\*\          - TIM_CC2EN Bit
*\*\          - TIM_CC2NEN Bit
*\*\          - TIM_CC3EN Bit
*\*\          - TIM_CC3NEN Bit
*\*\          - TIM_CC4EN Bit
*\*\          - TIM_CC4NEN Bit
*\*\          - TIM_CC5EN Bit
*\*\          - TIM_CC6EN Bit
*\*\return:
*\*\          - SET
*\*\          - RESET
*\*\note：
*\*\          - TIM_CC1NEN TIM_CC2NEN TIM_CC3NEN is used only with TIM1, TIM8.
*\*\          - TIM_CC4NEN is used only with TIM1.
**/
FlagStatus TIM_CCEN_Status_Get(TIM_Module* TIMx, uint32_t TIM_CCEN)
{
    if ((TIMx->CCEN & TIM_CCEN) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name    TIM_Output_Channel_Mode_Set.
*\*\fun     set the mode of output channel of TIMx
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   output_channel_mode:
*\*\          - TIM_OCMODE_TIMING
*\*\          - TIM_OCMODE_ACTIVE
*\*\          - TIM_OCMODE_TOGGLE
*\*\          - TIM_OCMODE_PWM1
*\*\          - TIM_OCMODE_PWM2
*\*\          - TIM_FORCED_ACTION_ACTIVE
*\*\          - TIM_FORCED_ACTION_INACTIVE
*\*\param   channel:
**\           - TIM_CH_1
**\           - TIM_CH_2
**\           - TIM_CH_3
**\           - TIM_CH_4
*\*\return  none
*\*\note    - This function disables the selected channel before changing the Output Compare Mode.
*\*\           User has to enable this channel using TIM_Capture_Compare_Ch_Enable,TIM_Capture_Compare_Ch_N_Enable functions.
**/
void TIM_Output_Channel_Mode_Set(TIM_Module* TIMx, uint32_t output_channel_mode, uint16_t channel)
{
    uint32_t temp  = 0;
    uint16_t temp1 = 0;

    temp = (uint32_t)TIMx;
    temp += CAPCMPMOD_OFFSET;

    temp1 = CAPCMPEN_CCE_SET << (uint16_t)channel;

    /* Disable the channel: Reset the CCxE Bit */
    TIMx->CCEN &= (uint16_t)~temp1;

    if ((channel == TIM_CH_1) || (channel == TIM_CH_3))
    {
        temp += (channel >> 1);

        /* Reset the OCxM bits in the CCMRx register */
        *(__IO uint32_t*)temp &= (uint32_t) ~((uint32_t)TIM_OC1MODE_MASK);

        /* Configure the OCxM bits in the CCMRx register */
        *(__IO uint32_t*)temp |= output_channel_mode;
    }
    else
    {
        temp += (uint16_t)(channel - (uint16_t)4) >> (uint16_t)1;

        /* Reset the OCxM bits in the CCMRx register */
        *(__IO uint32_t*)temp &= (uint32_t) ~((uint32_t)TIM_OC2MODE_MASK);

        /* Configure the OCxM bits in the CCMRx register */
        *(__IO uint32_t*)temp |= (uint16_t)(output_channel_mode << 8);
    }
}

/**
*\*\name    TIM_Forced_Output_Channel1_Set.
*\*\fun     set the mode of output channel of TIMx
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_forced_action:
*\*\          - TIM_FORCED_ACTION_ACTIVE Force active level on OC1REF
*\*\          - TIM_FORCED_ACTION_INACTIVE Force inactive level on OC1REF.
*\*\return  none
**/
void TIM_Forced_Output_Channel1_Set(TIM_Module* TIMx, uint16_t TIM_forced_action)
{
    uint16_t temp_value = 0;
    /* Check the parameters */
    temp_value = TIMx->CCMOD1;
    /* Reset the OC1M Bits */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC1MODE_MASK);
    /* Configure The Forced output Mode */
    temp_value |= TIM_forced_action;
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = temp_value;    
}

/**
*\*\name    TIM_Output_Channe2_Mode_Set.
*\*\fun     set the mode of output channe2 of TIMx
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_forced_action:
*\*\          - TIM_FORCED_ACTION_ACTIVE Force active level on OC2REF
*\*\          - TIM_FORCED_ACTION_INACTIVE Force inactive level on OC2REF.
*\*\return  none
**/
void TIM_Forced_Output_Channel2_Set(TIM_Module* TIMx, uint16_t TIM_forced_action)
{
    uint16_t temp_value = 0;
    /* Check the parameters */
    temp_value = TIMx->CCMOD1;
    /* Reset the OC1M Bits */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC2MODE_MASK);
    /* Configure The Forced output Mode */
    temp_value |= (uint16_t)(TIM_forced_action << 8);
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = temp_value;    
}

/**
*\*\name    TIM_Output_Channe3_Mode_Set.
*\*\fun     set the mode of output channe3 of TIMx
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_forced_action:
*\*\          - TIM_FORCED_ACTION_ACTIVE Force active level on OC3REF
*\*\          - TIM_FORCED_ACTION_INACTIVE Force inactive level on OC3REF.
*\*\return  none
**/
void TIM_Forced_Output_Channel3_Set(TIM_Module* TIMx, uint16_t TIM_forced_action)
{
    uint16_t temp_value = 0;
    /* Check the parameters */
    temp_value = TIMx->CCMOD2;
    /* Reset the OC1M Bits */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC3MODE_MASK);
    /* Configure The Forced output Mode */
    temp_value |= TIM_forced_action;
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD2 = temp_value;    
}

/**
*\*\name    TIM_Output_Channe4_Mode_Set.
*\*\fun     set the mode of output channe4 of TIMx
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_forced_action:
*\*\          - TIM_FORCED_ACTION_ACTIVE Force active level on OC4REF
*\*\          - TIM_FORCED_ACTION_INACTIVE Force inactive level on OC4REF.
*\*\return  none
**/
void TIM_Forced_Output_Channel4_Set(TIM_Module* TIMx, uint16_t TIM_forced_action)
{
    uint16_t temp_value = 0;
    /* Check the parameters */
    temp_value = TIMx->CCMOD2;
    /* Reset the OC1M Bits */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC4MODE_MASK);
    /* Configure The Forced output Mode */
    temp_value |= (uint16_t)(TIM_forced_action << 8);
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD2 = temp_value;    
}

/**
*\*\name    TIM_Output_Channe5_Mode_Set.
*\*\fun     set the mode of output channe5 of TIMx
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   TIM_forced_action:
*\*\          - TIM_FORCED_ACTION_ACTIVE Force active level on OC5REF
*\*\          - TIM_FORCED_ACTION_INACTIVE Force inactive level on OC5REF.
*\*\return  none
**/
void TIM_Forced_Output_Channel5_Set(TIM_Module* TIMx, uint16_t TIM_forced_action)
{
    uint16_t temp_value = 0;
    /* Check the parameters */
    temp_value = TIMx->CCMOD3;
    /* Reset the OC1M Bits */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC5MODE_MASK);
    /* Configure The Forced output Mode */
    temp_value |= TIM_forced_action;
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = temp_value;    
}

/**
*\*\name    TIM_Output_Channe6_Mode_Set.
*\*\fun     set the mode of output channe6 of TIMx
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   TIM_forced_action:
*\*\          - TIM_FORCED_ACTION_ACTIVE Force active level on OC6REF
*\*\          - TIM_FORCED_ACTION_INACTIVE Force inactive level on OC6REF.
*\*\return  none
**/
void TIM_Forced_Output_Channel6_Set(TIM_Module* TIMx, uint16_t TIM_forced_action)
{
    uint16_t temp_value = 0;
    /* Check the parameters */
    temp_value = TIMx->CCMOD3;
    /* Reset the OC1M Bits */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC6MODE_MASK);
    /* Configure The Forced output Mode */
    temp_value |= (uint16_t)(TIM_forced_action << 8);
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel1_Fast_Set
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_fast:
*\*\          - TIM_OC_FAST_ENABLE TIM Output fast enable
*\*\          - TIM_OC_FAST_DISABLE TIM Output fast disable
*\*\return  none
**/
void TIM_Output_Channel1_Fast_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_fast)
{
    uint16_t temp_value = 0;
    /* Get the TIMx CCMOD1 register value */
    temp_value = TIMx->CCMOD1;
    /* Reset the OC1FE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC_FAST_ENABLE);
    /* Enable or Disable the Output Compare Fast Bit */
    temp_value |= TIM_output_channel_fast;
    /* Write to TIMx CCMOD1 */
    TIMx->CCMOD1 = temp_value;
}

/**
*\*\name    TIM_Output_Channel2_Fast_Set
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_fast:
*\*\          - TIM_OC_FAST_ENABLE TIM Output fast enable
*\*\          - TIM_OC_FAST_DISABLE TIM Output fast disable
*\*\return  none
**/
void TIM_Output_Channel2_Fast_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_fast)
{
    uint16_t temp_value = 0;
    /* Get the TIMx CCMOD1 register value */
    temp_value = TIMx->CCMOD1;
    /* Reset the OC1FE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_CCMOD1_OC2FEN);
    /* Enable or Disable the Output Compare Fast Bit */
    temp_value |= (uint16_t)(TIM_output_channel_fast << 8);
    /* Write to TIMx CCMOD1 */
    TIMx->CCMOD1 = temp_value;
}

/**
*\*\name    TIM_Output_Channel3_Fast_Set
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_fast:
*\*\          - TIM_OC_FAST_ENABLE TIM Output fast enable
*\*\          - TIM_OC_FAST_DISABLE TIM Output fast disable
*\*\return  none
**/
void TIM_Output_Channel3_Fast_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_fast)
{
    uint16_t temp_value = 0;
    /* Get the TIMx CCMOD1 register value */
    temp_value = TIMx->CCMOD2;
    /* Reset the OC1FE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_CCMOD2_OC3FEN);
    /* Enable or Disable the Output Compare Fast Bit */
    temp_value |= TIM_output_channel_fast;
    /* Write to TIMx CCMOD2 */
    TIMx->CCMOD2 = temp_value;
}

/**
*\*\name    TIM_Output_Channel4_Fast_Set
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_fast:
*\*\          - TIM_OC_FAST_ENABLE TIM Output fast enable
*\*\          - TIM_OC_FAST_DISABLE TIM Output fast disable
*\*\return  none
**/
void TIM_Output_Channel4_Fast_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_fast)
{
    uint16_t temp_value = 0;
    /* Get the TIMx CCMOD1 register value */
    temp_value = TIMx->CCMOD2;
    /* Reset the OC1FE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_CCMOD2_OC4FEN);
    /* Enable or Disable the Output Compare Fast Bit */
    temp_value |= (uint16_t)(TIM_output_channel_fast << 8);
    /* Write to TIMx CCMOD2 */
    TIMx->CCMOD2 = temp_value;
}

/**
*\*\name    TIM_Output_Channel5_Fast_Set
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   TIM_output_channel_fast:
*\*\          - TIM_OC_FAST_ENABLE TIM Output fast enable
*\*\          - TIM_OC_FAST_DISABLE TIM Output fast disable
*\*\return  none
**/
void TIM_Output_Channel5_Fast_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_fast)
{
    uint16_t temp_value = 0;
    /* Get the TIMx CCMOD1 register value */
    temp_value = TIMx->CCMOD3;
    /* Reset the OC1FE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_CCMOD3_OC5FEN);
    /* Enable or Disable the Output Compare Fast Bit */
    temp_value |= TIM_output_channel_fast;
    /* Write to TIMx CCMOD3 */
    TIMx->CCMOD3 = temp_value;
}

/**
*\*\name    TIM_Output_Channel6_Fast_Set
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   TIM_output_channel_fast:
*\*\          - TIM_OC_FAST_ENABLE TIM Output fast enable
*\*\          - TIM_OC_FAST_DISABLE TIM Output fast disable
*\*\return  none
**/
void TIM_Output_Channel6_Fast_Set(TIM_Module* TIMx, uint16_t TIM_output_channel_fast)
{
    uint16_t temp_value = 0;
    /* Get the TIMx CCMOD3 register value */
    temp_value = TIMx->CCMOD3;
    /* Reset the OC1FE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_CCMOD3_OC6FEN);
    /* Enable or Disable the Output Compare Fast Bit */
    temp_value |= (uint16_t)(TIM_output_channel_fast << 8);
    /* Write to TIMx CCMOD3 */
    TIMx->CCMOD3 = temp_value;
}

/**
*\*\name    TIM_Output_Channel1_Reference_Clear
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_clear:
*\*\          - TIM_OC_CLEAR_ENABLE TIM Output clear enable
*\*\          - TIM_OC_CLEAR_DISABLE TIM Output clear disable
*\*\return  none
**/
void TIM_Output_Channel1_Reference_Clear(TIM_Module* TIMx, uint16_t TIM_output_channel_clear)
{
    uint16_t temp_value = 0;
    /* Check the parameters */

    temp_value = TIMx->CCMOD1;

    /* Reset the OC1CE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC1_CLEAR_MASK);
    /* Enable or Disable the Output Compare Clear Bit */
    temp_value |= TIM_output_channel_clear;
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel2_Reference_Clear
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_clear:
*\*\          - TIM_OC_CLEAR_ENABLE TIM Output clear enable
*\*\          - TIM_OC_CLEAR_DISABLE TIM Output clear disable
*\*\return  none
**/
void TIM_Output_Channel2_Reference_Clear(TIM_Module* TIMx, uint16_t TIM_output_channel_clear)
{
    uint16_t temp_value = 0;
    /* Check the parameters */

    temp_value = TIMx->CCMOD1;

    /* Reset the OC1CE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC2_CLEAR_MASK);
    /* Enable or Disable the Output Compare Clear Bit */
    temp_value |= (uint16_t)(TIM_output_channel_clear << 8);
    /* Write to TIMx CCMOD1 register */
    TIMx->CCMOD1 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel3_Reference_Clear
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_clear:
*\*\          - TIM_OC_CLEAR_ENABLE TIM Output clear enable
*\*\          - TIM_OC_CLEAR_DISABLE TIM Output clear disable
*\*\return  none
**/
void TIM_Output_Channel3_Reference_Clear(TIM_Module* TIMx, uint16_t TIM_output_channel_clear)
{
    uint16_t temp_value = 0;
    /* Check the parameters */

    temp_value = TIMx->CCMOD2;

    /* Reset the OC1CE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC3_CLEAR_MASK);
    /* Enable or Disable the Output Compare Clear Bit */
    temp_value |= TIM_output_channel_clear;
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD2 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel4_Reference_Clear
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_output_channel_clear:
*\*\          - TIM_OC_CLEAR_ENABLE TIM Output clear enable
*\*\          - TIM_OC_CLEAR_DISABLE TIM Output clear disable
*\*\return  none
**/
void TIM_Output_Channel4_Reference_Clear(TIM_Module* TIMx, uint16_t TIM_output_channel_clear)
{
    uint16_t temp_value = 0;
    /* Check the parameters */

    temp_value = TIMx->CCMOD2;

    /* Reset the OC1CE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC4_CLEAR_MASK);
    /* Enable or Disable the Output Compare Clear Bit */
    temp_value |= (uint16_t)(TIM_output_channel_clear << 8);
    /* Write to TIMx CCMOD2 register */
    TIMx->CCMOD2 = temp_value;    
}
/**
*\*\name    TIM_Output_Channel5_Reference_Clear
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   TIM_output_channel_clear:
*\*\          - TIM_OC_CLEAR_ENABLE TIM Output clear enable
*\*\          - TIM_OC_CLEAR_DISABLE TIM Output clear disable
*\*\return  none
**/
void TIM_Output_Channel5_Reference_Clear(TIM_Module* TIMx, uint16_t TIM_output_channel_clear)
{
    uint16_t temp_value = 0;
    /* Check the parameters */

    temp_value = TIMx->CCMOD3;

    /* Reset the OC1CE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC5_CLEAR_MASK);
    /* Enable or Disable the Output Compare Clear Bit */
    temp_value |= TIM_output_channel_clear;
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel6_Reference_Clear
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   TIM_output_channel_clear:
*\*\          - TIM_OC_CLEAR_ENABLE TIM Output clear enable
*\*\          - TIM_OC_CLEAR_DISABLE TIM Output clear disable
*\*\return  none
**/
void TIM_Output_Channel6_Reference_Clear(TIM_Module* TIMx, uint16_t TIM_output_channel_clear)
{
    uint16_t temp_value = 0;
    /* Check the parameters */

    temp_value = TIMx->CCMOD3;

    /* Reset the OC1CE Bit */
    temp_value &= (uint16_t) ~((uint16_t)TIM_OC6_CLEAR_MASK);
    /* Enable or Disable the Output Compare Clear Bit */
    temp_value |= (uint16_t)(TIM_output_channel_clear << 8);
    /* Write to TIMx CCMOD3 register */
    TIMx->CCMOD3 = temp_value;    
}

/**
*\*\name    TIM_Output_Channel1_Initialize
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_OCInitStruct:
*\*\          - Refer to the definition of OCInitType.
*\*\return  none
**/
void TIM_Output_Channel1_Initialize(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint16_t temp_value1 = 0;
    uint32_t temp_value2 = 0;

    /* Disable the Channel 1， Reset the CC1EN Bit */
    TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_1);

    /* Get the TIMx CTRL2 register value */
    temp_value2 = TIMx->CTRL2;

    /* Get the TIMx CCMOD1 register value */
    temp_value1 = TIMx->CCMOD1;

    /* Reset the Output Compare Mode Bits */
    temp_value1 &= (uint16_t)(~((uint16_t)TIM_OC1MODE_MASK));
    temp_value1 &= (uint16_t)(~((uint16_t)TIM_IC1_SELECTION_MASK));

    /* Select the Output Compare Mode */
    temp_value1 |= TIM_OCInitStruct->OcMode;

    TIM_Output_Channel_Polarity_Set(TIMx, TIM_OCInitStruct->OcPolarity, TIM_CH_1);

    /* Set the Output State */
    if(TIM_OCInitStruct->OutputState)
    {
        TIM_Capture_Compare_Ch_Enable(TIMx, TIM_CH_1);
    }
    else
    {
        TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_1);
    }

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        /* Set the Output N Polarity level */
        TIM_Output_Channel_N_Polarity_Set(TIMx, TIM_OCInitStruct->OcNPolarity, TIM_CH_1);

        /* Set the Output N State */
        if(TIM_OCInitStruct->OutputNState)
        {
            TIM_Capture_Compare_Ch_N_Enable(TIMx, TIM_CH_1);
        }
        else
        {
            TIM_Capture_Compare_Ch_N_Disable(TIMx, TIM_CH_1);
        }

        /* Reset the Output Compare and Output Compare N IDLE State */
        temp_value2 &= (uint32_t)(~((uint32_t)TIM_OC1_IDLE_STATE_MASK));
        temp_value2 &= (uint32_t)(~((uint32_t)TIM_OC1N_IDLE_STATE_MASK));

        /* Set the Output Idle state */
        temp_value2 |= TIM_OCInitStruct->OcIdleState;
        /* Set the Output N Idle state */
        temp_value2 |= TIM_OCInitStruct->OcNIdleState;
    }
    /* Write to TIMx CTRL2 */
    TIMx->CTRL2 = temp_value2;

    /* Write to TIMx CCMOD1 */
    TIMx->CCMOD1 = temp_value1;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT1 = TIM_OCInitStruct->Pulse;
    
}

/**
*\*\name    TIM_Output_Channel2_Initialize
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_OCInitStruct:
*\*\          - Refer to the definition of OCInitType.
*\*\return  none
**/
void TIM_Output_Channel2_Initialize(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint16_t temp_value1 = 0;
    uint32_t temp_value2 = 0;

    /* Disable the Channel 2， Reset the CC2EN Bit */
    TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_2);

    /* Get the TIMx CTRL2 register value */
    temp_value2 = TIMx->CTRL2;

    /* Get the TIMx CCMOD1 register value */
    temp_value1 = TIMx->CCMOD1;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    temp_value1 &= (uint16_t)(~((uint16_t)TIM_OC2MODE_MASK));
    temp_value1 &= (uint16_t)(~((uint16_t)TIM_IC2_SELECTION_MASK));

    /* Select the Output Compare Mode */
    temp_value1 |= (uint16_t)(TIM_OCInitStruct->OcMode << 8);

    TIM_Output_Channel_Polarity_Set(TIMx, TIM_OCInitStruct->OcPolarity, TIM_CH_2);

    /* Set the Output State */
    if(TIM_OCInitStruct->OutputState)
    {
        TIM_Capture_Compare_Ch_Enable(TIMx, TIM_CH_2);
    }
    else
    {
        TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_2);
    }

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        /* Set the Output N Polarity level */
        TIM_Output_Channel_N_Polarity_Set(TIMx, TIM_OCInitStruct->OcNPolarity, TIM_CH_2);

        /* Set the Output N State */
        if(TIM_OCInitStruct->OutputNState)
        {
            TIM_Capture_Compare_Ch_N_Enable(TIMx, TIM_CH_2);
        }
        else
        {
            TIM_Capture_Compare_Ch_N_Disable(TIMx, TIM_CH_2);
        }

        /* Reset the Output Compare and Output Compare N IDLE State */
        temp_value2 &= (uint32_t)(~((uint32_t)TIM_OC2_IDLE_STATE_MASK));
        temp_value2 &= (uint32_t)(~((uint32_t)TIM_OC2N_IDLE_STATE_MASK));

        /* Set the Output Idle state */
        temp_value2 |= (uint32_t)(TIM_OCInitStruct->OcIdleState << 2);
        /* Set the Output N Idle state */
        temp_value2 |= (uint32_t)(TIM_OCInitStruct->OcNIdleState << 2);
    }
    /* Write to TIMx CTRL2 */
    TIMx->CTRL2 = temp_value2;

    /* Write to TIMx CCMOD1 */
    TIMx->CCMOD1 = temp_value1;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT2 = TIM_OCInitStruct->Pulse;

}

/**
*\*\name    TIM_Output_Channel3_Initialize
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_OCInitStruct:
*\*\              - Refer to the definition of OCInitType.
*\*\return  none
**/
void TIM_Output_Channel3_Initialize(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint16_t temp_value1 = 0;
    uint32_t temp_value2 = 0;

    /* Disable the Channel 3， Reset the CC3EN Bit */
    TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_3);

    /* Get the TIMx CTRL2 register value */
    temp_value2 = TIMx->CTRL2;

    /* Get the TIMx CCMOD2 register value */
    temp_value1 = TIMx->CCMOD2;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    temp_value1 &= (uint16_t)(~((uint16_t)TIM_OC3MODE_MASK));
    temp_value1 &= (uint16_t)(~((uint16_t)TIM_IC3_SELECTION_MASK));
    /* Select the Output Compare Mode */
    temp_value1 |= TIM_OCInitStruct->OcMode;

    TIM_Output_Channel_Polarity_Set(TIMx, TIM_OCInitStruct->OcPolarity, TIM_CH_3);

    /* Set the Output State */
    if(TIM_OCInitStruct->OutputState)
    {
        TIM_Capture_Compare_Ch_Enable(TIMx, TIM_CH_3);
    }
    else
    {
        TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_3);
    }

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        /* Set the Output N Polarity level */
        TIM_Output_Channel_N_Polarity_Set(TIMx, TIM_OCInitStruct->OcNPolarity, TIM_CH_3);

        /* Set the Output N State */
        if(TIM_OCInitStruct->OutputNState)
        {
            TIM_Capture_Compare_Ch_N_Enable(TIMx, TIM_CH_3);
        }
        else
        {
            TIM_Capture_Compare_Ch_N_Disable(TIMx, TIM_CH_3);
        }
        /* Reset the Output Compare and Output Compare N IDLE State */
        temp_value2 &= (uint32_t)(~((uint32_t)TIM_OC3_IDLE_STATE_MASK));
        temp_value2 &= (uint32_t)(~((uint32_t)TIM_OC3N_IDLE_STATE_MASK));
        /* Set the Output Idle state */
        temp_value2 |= (uint32_t)(TIM_OCInitStruct->OcIdleState << 4);
        /* Set the Output N Idle state */
        temp_value2 |= (uint32_t)(TIM_OCInitStruct->OcNIdleState << 4);
    }
    /* Write to TIMx CTRL2 */
    TIMx->CTRL2 = temp_value2;

    /* Write to TIMx CCMOD2 */
    TIMx->CCMOD2 = temp_value1;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT3 = TIM_OCInitStruct->Pulse;

}

/**
*\*\name    TIM_Output_Channel4_Initialize
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_OCInitStruct:
*\*\              - Refer to the definition of OCInitType.
*\*\return  none
*\*\note    The CH4N is only for TIM1.
**/
void TIM_Output_Channel4_Initialize(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint16_t temp_value1 = 0;
    uint32_t temp_value2 = 0;

    /* Disable the Channel 4， Reset the CC4EN Bit */
    TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_4);

    /* Get the TIMx CTRL2 register value */
    temp_value2 = TIMx->CTRL2;

    /* Get the TIMx CCMOD2 register value */
    temp_value1 = TIMx->CCMOD2;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    temp_value1 &= (uint16_t)(~((uint16_t)TIM_OC4MODE_MASK));
    temp_value1 &= (uint16_t)(~((uint16_t)TIM_IC4_SELECTION_MASK));

    /* Select the Output Compare Mode */
    temp_value1 |= (uint16_t)(TIM_OCInitStruct->OcMode << 8);

    TIM_Output_Channel_Polarity_Set(TIMx, TIM_OCInitStruct->OcPolarity, TIM_CH_4);

    /* Set the Output State */
    if(TIM_OCInitStruct->OutputState)
    {
        TIM_Capture_Compare_Ch_Enable(TIMx, TIM_CH_4);
    }
    else
    {
        TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_4);
    }

    if (TIMx == TIM1)
    {
        /* Set the Output N Polarity level */
        TIM_Output_Channel_N_Polarity_Set(TIMx, TIM_OCInitStruct->OcNPolarity, TIM_CH_4);

        /* Set the Output N State */
        if(TIM_OCInitStruct->OutputNState)
        {
            TIM_Capture_Compare_Ch_N_Enable(TIMx, TIM_CH_4);
        }
        else
        {
            TIM_Capture_Compare_Ch_N_Disable(TIMx, TIM_CH_4);
        }
        /* Reset the Output Compare and Output Compare N IDLE State */
        temp_value2 &= (uint32_t)(~((uint32_t)TIM_OC4_IDLE_STATE_MASK));
        temp_value2 &= (uint32_t)(~((uint32_t)TIM_OC4N_IDLE_STATE_MASK));
        /* Set the Output Idle state */
        temp_value2 |= (uint32_t)(TIM_OCInitStruct->OcIdleState << 6);
        /* Set the Output N Idle state */
        temp_value2 |= (uint32_t)(TIM_OCInitStruct->OcNIdleState << 8);
    }
    else if(TIMx == TIM8)
    {
        /* Reset the Output Compare IDLE State */
        temp_value2 &= (uint32_t)(~((uint32_t)TIM_OC4_IDLE_STATE_MASK));
        /* Set the Output Idle state */
        temp_value2 |= (uint32_t)(TIM_OCInitStruct->OcIdleState << 6);
    }
    else
    {
        /* none */
    }
    /* Write to TIMx CTRL2 */
    TIMx->CTRL2 = temp_value2;

    /* Write to TIMx CCMOD2 */
    TIMx->CCMOD2 = temp_value1;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT4 = TIM_OCInitStruct->Pulse;

}

/**
*\*\name    TIM_Output_Channel5_Initialize
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   TIM_OCInitStruct:
*\*\              - Refer to the definition of OCInitType.
*\*\return  none
**/
void TIM_Output_Channel5_Initialize(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint16_t temp_value1 = 0;
    uint32_t temp_value2 = 0;

    /* Disable the Channel 5， Reset the CC5EN Bit */
    TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_5);

    /* Get the TIMx CTRL2 register value */
    temp_value2 = TIMx->CTRL2;

    /* Get the TIMx CCMOD3 register value */
    temp_value1 = TIMx->CCMOD3;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    temp_value1 &= (uint16_t)(~((uint16_t)TIM_OC5MODE_MASK));

    /* Select the Output Compare Mode */
    temp_value1 |= (uint16_t)(TIM_OCInitStruct->OcMode);

    TIM_Output_Channel_Polarity_Set(TIMx, TIM_OCInitStruct->OcPolarity, TIM_CH_5);

    /* Set the Output State */
    if(TIM_OCInitStruct->OutputState)
    {
        TIM_Capture_Compare_Ch_Enable(TIMx, TIM_CH_5);
    }
    else
    {
        TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_5);
    }

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        
        /* Reset the Output Compare IDLE State */
        temp_value2 &= (uint32_t)(~((uint32_t)TIM_OC5_IDLE_STATE_MASK));
        /* Set the Output Idle state */
        temp_value2 |= (uint32_t)(TIM_OCInitStruct->OcIdleState << 8);
    }
    /* Write to TIMx CTRL2 */
    TIMx->CTRL2 = temp_value2;

    /* Write to TIMx CCMOD3 */
    TIMx->CCMOD3 = temp_value1;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT5 = TIM_OCInitStruct->Pulse;

}

/**
*\*\name    TIM_Output_Channel6_Initialize
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   TIM_OCInitStruct:
*\*\              - Refer to the definition of OCInitType.
*\*\return  none
**/
void TIM_Output_Channel6_Initialize(TIM_Module* TIMx, OCInitType* TIM_OCInitStruct)
{
    uint16_t temp_value1 = 0;
    uint32_t temp_value2 = 0;

    /* Disable the Channel 6， Reset the CC6EN Bit */
    TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_6);

    /* Get the TIMx CTRL2 register value */
    temp_value2 = TIMx->CTRL2;

    /* Get the TIMx CCMOD3 register value */
    temp_value1 = TIMx->CCMOD3;

    /* Reset the Output Compare mode and Capture/Compare selection Bits */
    temp_value1 &= (uint16_t)(~((uint16_t)TIM_OC6MODE_MASK));

    /* Select the Output Compare Mode */
    temp_value1 |= (uint16_t)(TIM_OCInitStruct->OcMode << 8);

    TIM_Output_Channel_Polarity_Set(TIMx, TIM_OCInitStruct->OcPolarity, TIM_CH_6);

    /* Set the Output State */
    if(TIM_OCInitStruct->OutputState)
    {
        TIM_Capture_Compare_Ch_Enable(TIMx, TIM_CH_6);
    }
    else
    {
        TIM_Capture_Compare_Ch_Disable(TIMx, TIM_CH_6);
    }

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        
        /* Reset the Output Compare IDLE State */
        temp_value2 &= (uint32_t)(~((uint32_t)TIM_OC6_IDLE_STATE_MASK));
        /* Set the Output Idle state */
        temp_value2 |= (uint32_t)(TIM_OCInitStruct->OcIdleState << 10);
    }
    /* Write to TIMx CTRL2 */
    TIMx->CTRL2 = temp_value2;

    /* Write to TIMx CCMOD3 */
    TIMx->CCMOD3 = temp_value1;

    /* Set the Capture Compare Register value */
    TIMx->CCDAT6 = TIM_OCInitStruct->Pulse;

}


/**
*\*\name    TIM_PWM_Output_Enable.
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  none
**/
void TIM_PWM_Output_Enable(TIM_Module* TIMx)
{
    TIMx->BKDT |= TIM_MAIN_OUTPUT_ENABLE;
}

/**
*\*\name    TIM_PWM_Output_Disable.
*\*\fun     Initializes the TIM break and dead time register
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  none
**/
void TIM_PWM_Output_Disable(TIM_Module* TIMx)
{
    TIMx->BKDT &= (uint16_t)(~((uint16_t)TIM_MAIN_OUTPUT_ENABLE));
}



void TIM_Output_Channel_Struct_Initialize(OCInitType* TIM_OCInitStruct)
{
    /* Set the default configuration */
    TIM_OCInitStruct->OcMode       = TIM_OCMODE_TIMING;
    TIM_OCInitStruct->OutputState  = TIM_OUTPUT_STATE_DISABLE;
    TIM_OCInitStruct->OutputNState = TIM_OUTPUT_NSTATE_DISABLE;
    TIM_OCInitStruct->Pulse        = 0x0000;
    TIM_OCInitStruct->OcPolarity   = TIM_OC_POLARITY_HIGH;
    TIM_OCInitStruct->OcNPolarity  = TIM_OC_POLARITY_HIGH;
    TIM_OCInitStruct->OcIdleState  = TIM_OC_IDLE_STATE_RESET;
    TIM_OCInitStruct->OcNIdleState = TIM_OCN_IDLE_STATE_RESET;
}


/**
*\*\name    TIM_Lock_Up_Break_Enable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  none
**/
void TIM_Lock_Up_Break_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL1 |= TIM_LOCKUP_AS_BREAK_IN;
}
/**
*\*\name    TIM_Lock_Up_Break_Disable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  none
**/
void TIM_Lock_Up_Break_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL1 &= (uint32_t)(~TIM_LOCKUP_AS_BREAK_IN);
}
/**
*\*\name    TIM_Pvd_Break_Enable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  none
**/
void TIM_Pvd_Break_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL1 |= TIM_PVD_AS_BREAK_IN;
}

/**
*\*\name    TIM_Pvd_Break_Disable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  none
**/
void TIM_Pvd_Break_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL1 &= (uint32_t)(~TIM_PVD_AS_BREAK_IN);
}

/**
*\*\name    TIM_IOM_Comp_Break.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   IOM_Comp_Selection:
*\*\          - true     Comp as break in source
*\*\          - false    IOM as break in source
*\*\return  none
**/
void TIM_IOM_Comp_Break(TIM_Module* TIMx, bool IOM_Comp_Selection)
{
    if(IOM_Comp_Selection)
    {
        TIMx->CTRL1 |= TIM_COMP_AS_BREAK_IN;
    }
    else
    {
        TIMx->CTRL1 &= (uint32_t)(~TIM_COMP_AS_BREAK_IN);
    }
}

/**
*\*\name    TIM_Break_And_Dead_Time_Set.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   TIM_BDTRInitStruct:
*\*\          - refer to the definition of TIM_BDTRInitType
*\*\return  none
**/
void  TIM_Break_And_Dead_Time_Set(TIM_Module* TIMx, TIM_BDTRInitType* TIM_BDTRInitStruct)
{
    /* Set the Lock level, the Break enable Bit and the Ploarity, the OSSR State,
       the OSSI State, the dead time value and the Automatic Output Enable Bit */
    TIMx->BKDT = (uint16_t)TIM_BDTRInitStruct->OssrState | TIM_BDTRInitStruct->OssiState | TIM_BDTRInitStruct->LockLevel
                 | TIM_BDTRInitStruct->DeadTime | TIM_BDTRInitStruct->Break | TIM_BDTRInitStruct->BreakPolarity
                 | TIM_BDTRInitStruct->AutomaticOutput;

    /*IOMBKPEN 0 meaning iom as break enable*/
    if (TIM_BDTRInitStruct->IomBreakEn)
    {
        TIM_IOM_Comp_Break(TIMx, false);
    }
    /*IOMBKPEN 1 meaning comp as break enable*/
    else
    {
        TIM_IOM_Comp_Break(TIMx, true);
    }
    
    if (TIM_BDTRInitStruct->LockUpBreakEn)
    {
        TIM_Lock_Up_Break_Enable(TIMx);
    }
    else
    {
        TIM_Lock_Up_Break_Disable(TIMx);
    }
    
    if(TIM_BDTRInitStruct->PvdBreakEn)
    {
        TIM_Pvd_Break_Enable(TIMx);
    }
    else
    {
        TIM_Pvd_Break_Disable(TIMx);
    }
}


/**
*\*\name    TIM_Break_And_Dead_Time_Struct_Initialize.
*\*\param   TIM_BDTRInitStruct:
*\*\          - refer to the definition of TIM_BDTRInitType
*\*\return  none
**/
void TIM_Break_And_Dead_Time_Struct_Initialize(TIM_BDTRInitType* TIM_BDTRInitStruct)
{
    /* Set the default configuration */
    TIM_BDTRInitStruct->OssrState       = TIM_OSSR_STATE_DISABLE;
    TIM_BDTRInitStruct->OssiState       = TIM_OSSI_STATE_DISABLE;
    TIM_BDTRInitStruct->LockLevel       = TIM_LOCK_LEVEL_OFF;
    TIM_BDTRInitStruct->DeadTime        = 0x00;
    TIM_BDTRInitStruct->Break           = TIM_BREAK_IN_DISABLE;
    TIM_BDTRInitStruct->BreakPolarity   = TIM_BREAK_POLARITY_LOW;
    TIM_BDTRInitStruct->AutomaticOutput = TIM_AUTO_OUTPUT_DISABLE;
    TIM_BDTRInitStruct->IomBreakEn      = false;
    TIM_BDTRInitStruct->LockUpBreakEn   = false;
    TIM_BDTRInitStruct->PvdBreakEn      = false;
}

/**
*\*\name    TIM_Interrupt_Enable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   TIM_IT
*\*\          - TIM_INT_UPDATE    TIM update Interrupt source
*\*\          - TIM_INT_CC1       TIM Capture Compare 1 Interrupt source
*\*\          - TIM_INT_CC2       TIM Capture Compare 2 Interrupt source
*\*\          - TIM_INT_CC3       TIM Capture Compare 3 Interrupt source
*\*\          - TIM_INT_CC4       TIM Capture Compare 4 Interrupt source
*\*\          - TIM_INT_COM       TIM Commutation Interrupt source
*\*\          - TIM_INT_TRIG      TIM Trigger Interrupt source
*\*\          - TIM_INT_BREAK     TIM Break Interrupt source
*\*\note
*\*\          - TIM6 can only generate an update interrupt.
*\*\          - TIM_INT_BREAK is used only with TIM1, TIM8.
*\*\          - TIM_INT_COM is used only with TIM1, TIM8.
*\*\return  none
**/
void TIM_Interrupt_Enable(TIM_Module* TIMx, uint16_t TIM_IT)
{
    TIMx->DINTEN |= TIM_IT;
}

/**
*\*\name    TIM_Interrupt_Disable.
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   TIM_IT
*\*\          - TIM_INT_UPDATE    TIM update Interrupt source
*\*\          - TIM_INT_CC1       TIM Capture Compare 1 Interrupt source
*\*\          - TIM_INT_CC2       TIM Capture Compare 2 Interrupt source
*\*\          - TIM_INT_CC3       TIM Capture Compare 3 Interrupt source
*\*\          - TIM_INT_CC4       TIM Capture Compare 4 Interrupt source
*\*\          - TIM_INT_COM       TIM Commutation Interrupt source
*\*\          - TIM_INT_TRIG      TIM Trigger Interrupt source
*\*\          - TIM_INT_BREAK     TIM Break Interrupt source
*\*\note
*\*\          - TIM6 can only generate an update interrupt.
*\*\          - TIM_INT_BREAK is used only with TIM1, TIM8.
*\*\          - TIM_INT_COM is used only with TIM1, TIM8.
*\*\return  none
**/
void TIM_Interrupt_Disable(TIM_Module* TIMx, uint16_t TIM_IT)
{
    TIMx->DINTEN &= (uint16_t)(~TIM_IT);
}



/**
*\*\name    TIM_Interrupt_Status_Get
*\*\param   TIMx where x can be 1 to 8 to select the TIM peripheral.
*\*\param   TIM_IT specifies the TIM interrupt source to check.
*\*\          - TIM_INT_UPDATE    TIM update Interrupt source
*\*\          - TIM_INT_CC1       TIM Capture Compare 1 Interrupt source
*\*\          - TIM_INT_CC2       TIM Capture Compare 2 Interrupt source
*\*\          - TIM_INT_CC3       TIM Capture Compare 3 Interrupt source
*\*\          - TIM_INT_CC4       TIM Capture Compare 4 Interrupt source
*\*\          - TIM_INT_COM       TIM Commutation Interrupt source
*\*\          - TIM_INT_TRIG      TIM Trigger Interrupt source
*\*\          - TIM_INT_BREAK     TIM Break Interrupt source
*\*\note
*\*\          - TIM6 and TIM7 can generate only an update interrupt.
*\*\          - TIM_INT_BREAK is used only with TIM1, TIM8.
*\*\          - TIM_INT_COM is used only with TIM1, TIM8.
*\*\return
*\*\          - SET
*\*\          - RESET
**/
INTStatus TIM_Interrupt_Status_Get(TIM_Module* TIMx, uint32_t TIM_IT)
{
    uint32_t interrupt_status = 0x0, interrupt_enable = 0x0;

    interrupt_status = TIMx->STS & TIM_IT;

    interrupt_enable = TIMx->DINTEN & TIM_IT;
    if ((interrupt_status != (uint32_t)RESET) && (interrupt_enable != (uint32_t)RESET))
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name    TIM_Interrupt_Pending_Bit_Clear
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   TIM_IT
*\*\          - TIM_INT_UPDATE TIM1 update Interrupt source
*\*\          - TIM_INT_CC1 TIM Capture Compare 1 Interrupt source
*\*\          - TIM_INT_CC2 TIM Capture Compare 2 Interrupt source
*\*\          - TIM_INT_CC3 TIM Capture Compare 3 Interrupt source
*\*\          - TIM_INT_CC4 TIM Capture Compare 4 Interrupt source
*\*\          - TIM_INT_COM TIM Commutation Interrupt source
*\*\          - TIM_INT_TRIG TIM Trigger Interrupt source
*\*\          - TIM_INT_BREAK TIM Break Interrupt source
*\*\note
*\*\          - TIM6 and TIM7 can have only one update flag.
*\*\          - TIM_FLAG_BREAK is used only with TIM1, TIM8.
*\*\          - TIM_FLAG_COM is used only with TIM1, TIM8.
*\*\return  none
**/
void TIM_Interrupt_Status_Clear(TIM_Module* TIMx, uint32_t TIM_IT)
{
    TIMx->STS = (uint32_t)~TIM_IT;
}


/**
*\*\name    TIM_Flag_Status_Get
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   TIM_IT
*\*\This parameter can be one of the following values:
*\*\          - TIM_FLAG_UPDATE TIM update Flag
*\*\          - TIM_FLAG_CC1 TIM Capture Compare 1 Flag
*\*\          - TIM_FLAG_CC2 TIM Capture Compare 2 Flag
*\*\          - TIM_FLAG_CC3 TIM Capture Compare 3 Flag
*\*\          - TIM_FLAG_CC4 TIM Capture Compare 4 Flag
*\*\          - TIM_FLAG_COM TIM Commutation Flag
*\*\          - TIM_FLAG_TRIG TIM Trigger Flag
*\*\          - TIM_FLAG_BREAK TIM Break Flag
*\*\          - TIM_FLAG_CC1OF TIM Capture Compare 1 overcapture Flag
*\*\          - TIM_FLAG_CC2OF TIM Capture Compare 2 overcapture Flag
*\*\          - TIM_FLAG_CC3OF TIM Capture Compare 3 overcapture Flag
*\*\          - TIM_FLAG_CC4OF TIM Capture Compare 4 overcapture Flag
*\*\          - TIM_FLAG_CC5 TIM Capture Compare 5 Flag
*\*\          - TIM_FLAG_CC6 TIM Capture Compare 6 Flag
*\*\note
*\*\          - TIM6 and TIM7 can have only one update flag.
*\*\          - TIM_FLAG_BREAK is used only with TIM1, TIM8.
*\*\          - TIM_FLAG_COM is used only with TIM1, TIM8.
*\*\return  The new state of TIM_FLAG (SET or RESET).
**/
FlagStatus TIM_Flag_Status_Get(TIM_Module* TIMx, uint32_t TIM_FLAG)
{
    if ((TIMx->STS & TIM_FLAG) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name    TIM_Flag_Clear
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM6
*\*\          - TIM8
*\*\param   TIM_IT
*\*\          - TIM_FLAG_UPDATE TIM update Flag
*\*\          - TIM_FLAG_CC1 TIM Capture Compare 1 Flag
*\*\          - TIM_FLAG_CC2 TIM Capture Compare 2 Flag
*\*\          - TIM_FLAG_CC3 TIM Capture Compare 3 Flag
*\*\          - TIM_FLAG_CC4 TIM Capture Compare 4 Flag
*\*\          - TIM_FLAG_COM TIM Commutation Flag
*\*\          - TIM_FLAG_TRIG TIM Trigger Flag
*\*\          - TIM_FLAG_BREAK TIM Break Flag
*\*\          - TIM_FLAG_CC1OF TIM Capture Compare 1 overcapture Flag
*\*\          - TIM_FLAG_CC2OF TIM Capture Compare 2 overcapture Flag
*\*\          - TIM_FLAG_CC3OF TIM Capture Compare 3 overcapture Flag
*\*\          - TIM_FLAG_CC4OF TIM Capture Compare 4 overcapture Flag
*\*\          - TIM_FLAG_CC5 TIM Capture Compare 5 Flag
*\*\          - TIM_FLAG_CC6 TIM Capture Compare 6 Flag
*\*\note
*\*\          - TIM6 and TIM7 can have only one update flag.
*\*\          - TIM_FLAG_BREAK is used only with TIM1, TIM8.
*\*\          - TIM_FLAG_COM is used only with TIM1, TIM8.
*\*\return  none
**/
void TIM_Flag_Clear(TIM_Module* TIMx, uint32_t TIM_FLAG)
{
    TIMx->STS = (uint32_t)~TIM_FLAG;
}


/**
*\*\name    TIM_Dma_Config
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_DMABase:
*\*\         - TIM_DMABASE_CTRL1
*\*\         - TIM_DMABASE_CTRL2
*\*\         - TIM_DMABASE_SMCTRL
*\*\         - TIM_DMABASE_DMAINTEN
*\*\         - TIM_DMABASE_STS
*\*\         - TIM_DMABASE_EVTGEN
*\*\         - TIM_DMABASE_CAPCMPMOD1
*\*\         - TIM_DMABASE_CAPCMPMOD2
*\*\         - TIM_DMABASE_CAPCMPEN
*\*\         - TIM_DMABASE_CNT
*\*\         - TIM_DMABASE_PSC
*\*\         - TIM_DMABASE_AR
*\*\         - TIM_DMABASE_REPCNT
*\*\         - TIM_DMABASE_CAPCMPDAT1
*\*\         - TIM_DMABASE_CAPCMPDAT2
*\*\         - TIM_DMABASE_CAPCMPDAT3
*\*\         - TIM_DMABASE_CAPCMPDAT4
*\*\         - TIM_DMABASE_BKDT
*\*\         - TIM_DMABASE_DMACTRL
*\*\         - TIM_DMABASE_DMAADDR
*\*\         - TIM_DMABASE_CAPCMPMOD3
*\*\         - TIM_DMABASE_CAPCMPDAT5
*\*\         - TIM_DMABASE_CAPCMPDAT6
*\*\         - TIM_DMABASE_CAPCMPDAT7
*\*\         - TIM_DMABASE_CAPCMPDAT8
*\*\         - TIM_DMABASE_CAPCMPDAT9
*\*\         - TIM_DMABASE_BRKFILT
*\*\         - TIM_DMABASE_C1FLIT
*\*\         - TIM_DMABASE_C2FLIT
*\*\         - TIM_DMABASE_C3FLIT
*\*\         - TIM_DMABASE_C4FLIT
*\*\         - TIM_DMABASE_FILTO
*\*\param   TIM_DMABurstLength:
*\*\         - TIM_DMABURST_LENGTH_1TRANSFER
*\*\         - TIM_DMABURST_LENGTH_2TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_3TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_4TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_5TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_6TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_7TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_8TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_9TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_10TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_11TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_12TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_13TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_14TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_15TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_16TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_17TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_18TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_19TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_20TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_21TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_22TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_23TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_24TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_25TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_26TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_27TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_28TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_29TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_30TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_31TRANSFERS
*\*\         - TIM_DMABURST_LENGTH_32TRANSFERS
*\*\return  none
**/
void TIM_Dma_Config(TIM_Module* TIMx, uint16_t TIM_DMA_base, uint16_t TIM_DMA_burst_length)
{
    TIMx->DCTRL = TIM_DMA_base | TIM_DMA_burst_length;
}
/**
*\*\name    TIM_Dma_Enable
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_DMA_source:
*\*\          - TIM_DMA_UPDATE    TIM update Interrupt source
*\*\          - TIM_DMA_CC1       TIM Capture Compare 1 DMA source
*\*\          - TIM_DMA_CC2       TIM Capture Compare 2 DMA source
*\*\          - TIM_DMA_CC3       TIM Capture Compare 3 DMA source
*\*\          - TIM_DMA_CC4       TIM Capture Compare 4 DMA source
*\*\          - TIM_DMA_COM       TIM Commutation DMA source
*\*\          - TIM_DMA_TRIG      TIM Trigger DMA source
*\*\return  none
**/
void TIM_Dma_Enable(TIM_Module* TIMx, uint16_t TIM_DMA_source)
{
    TIMx->DINTEN |= TIM_DMA_source;
}

/**
*\*\name    TIM_Dma_Disable
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_DMA_source: 
*\*\          - TIM_DMA_UPDATE    TIM update Interrupt source
*\*\          - TIM_DMA_CC1       TIM Capture Compare 1 DMA source
*\*\          - TIM_DMA_CC2       TIM Capture Compare 2 DMA source
*\*\          - TIM_DMA_CC3       TIM Capture Compare 3 DMA source
*\*\          - TIM_DMA_CC4       TIM Capture Compare 4 DMA source
*\*\          - TIM_DMA_COM       TIM Commutation DMA source
*\*\          - TIM_DMA_TRIG      TIM Trigger DMA source
*\*\return  none
**/
void TIM_Dma_Disable(TIM_Module* TIMx, uint16_t TIM_DMA_source)
{
    TIMx->DINTEN &= (uint16_t)~TIM_DMA_source;
}

/**
*\*\name    TIM_Hall_Sensor_Enable
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\return  none
**/
void TIM_Hall_Sensor_Enable(TIM_Module* TIMx)
{
    TIMx->CTRL2 |= TIM_TI1_SEL;
}
/**
*\*\name    TIM_Hall_Sensor_Disable
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\return  none
**/
void TIM_Hall_Sensor_Disable(TIM_Module* TIMx)
{
    TIMx->CTRL2 &= (uint32_t) ~((uint32_t)TIM_TI1_SEL);
}


/**
*\*\name    TIM_Encoder_Interface_Set
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\          - TIM8
*\*\param   TIM_encoder_modes: 
*\*\          - TIM_ENCODE_MODE_TI1 Counter counts on TI1FP1 edge depending on TI2FP2 level.
*\*\          - TIM_ENCODE_MODE_TI2 Counter counts on TI2FP2 edge depending on TI1FP1 level.
*\*\          - TIM_ENCODE_MODE_TI12 Counter counts on both TI1FP1 and TI2FP2 edges depending on the level of the other input.
*\*\param   TIM_input_channel1_polarity specifies the IC1 Polarity
*\*\          - TIM_IC_POLARITY_FALLING IC Falling edge.
*\*\          - TIM_IC_POLARITY_RISING IC Rising edge.
*\*\param   TIM_input_channel2_polarity specifies the IC2 Polarity
*\*\          - TIM_IC_POLARITY_FALLING IC Falling edge.
*\*\          - TIM_IC_POLARITY_RISING IC Rising edge.
*\*\return  none
**/
void TIM_Encoder_Interface_Set(TIM_Module* TIMx,uint16_t TIM_encoder_mode,
                                uint16_t TIM_input_channel1_polarity, uint16_t TIM_input_channel2_polarity)
{
    uint16_t temp_valuel  = 0;
    uint16_t temp_value2 = 0;
    uint32_t temp_value3  = 0;

    /* Get the TIMx SMCTRL register value */
    temp_valuel = TIMx->SMCTRL;

    /* Get the TIMx CCMOD1 register value */
    temp_value2 = TIMx->CCMOD1;

    /* Get the TIMx CCEN register value */
    temp_value3 = TIMx->CCEN;

    /* Set the encoder Mode */
    temp_valuel &= (uint16_t)(~((uint16_t)TIM_SMCTRL_SMSEL));
    temp_valuel |= TIM_encoder_mode;

    /* Select the Capture Compare 1 and the Capture Compare 2 as input */
    temp_value2 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CCMOD1_CC1SEL)) & (uint16_t)(~((uint16_t)TIM_CCMOD1_CC2SEL)));
    temp_value2 |= TIM_CCMOD1_CC1SEL_0 | TIM_CCMOD1_CC2SEL_0;

    /* Set the TI1 and the TI2 Polarities */
    temp_value3 &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_CCEN_CC1P)) & ((uint32_t) ~((uint32_t)TIM_CCEN_CC2P)));
    temp_value3 |= (uint32_t)(TIM_input_channel1_polarity | (uint16_t)(TIM_input_channel2_polarity << (uint16_t)4));

    /* Write to TIMx SMCTRL */
    TIMx->SMCTRL = temp_valuel;
    /* Write to TIMx CCMOD1 */
    TIMx->CCMOD1 = temp_value2;
    /* Write to TIMx CCEN */
    TIMx->CCEN = temp_value3;
}

/**
*\*\name    TIM_Channel1_Filter_Config
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\param   TIM_FilterInitStruct: 
*\*\          - refer to the definition of TIM_FilterInitType
*\*\return  none
**/
void TIM_Channel1_Filter_Config(TIM_Module* TIMx, TIM_FilterInitType* TIM_FilterInitStruct)
{
    uint32_t temp_value = 0;
    
    temp_value &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_FILTER_THRESH_MASK)) & 
                             ((uint32_t) ~((uint32_t)TIM_FILTER_WSIZE_MASK)) &
                             ((uint32_t) ~((uint32_t)TIM_FILTER_PSC_MASK)));

    temp_value |= (uint32_t)(TIM_FilterInitStruct->ThreshHold << (uint32_t)(TIM_FILTER_THRESH_OFFSET) | 
                             TIM_FilterInitStruct->WindowSize << (uint32_t)(TIM_FILTER_WSIZE_OFFSET) |
                             TIM_FilterInitStruct->Prescaler);

    if ((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
    {
        TIMx->C1FILT = temp_value;
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_Channel2_Filter_Config
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\param   TIM_FilterInitStruct: 
*\*\          - refer to the definition of TIM_FilterInitType
*\*\return  none
**/
void TIM_Channel2_Filter_Config(TIM_Module* TIMx, TIM_FilterInitType* TIM_FilterInitStruct)
{
    uint32_t temp_value = 0;
    
    temp_value &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_FILTER_THRESH_MASK)) & 
                             ((uint32_t) ~((uint32_t)TIM_FILTER_WSIZE_MASK)) &
                             ((uint32_t) ~((uint32_t)TIM_FILTER_PSC_MASK)));

    temp_value |= (uint32_t)(TIM_FilterInitStruct->ThreshHold << (uint32_t)(TIM_FILTER_THRESH_OFFSET) | 
                             TIM_FilterInitStruct->WindowSize << (uint32_t)(TIM_FILTER_WSIZE_OFFSET) |
                             TIM_FilterInitStruct->Prescaler);

    if ((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
    {
        TIMx->C2FILT = temp_value;
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_Channel3_Filter_Config
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\param   TIM_FilterInitStruct: 
*\*\          - refer to the definition of TIM_FilterInitType
*\*\return  none
**/
void TIM_Channel3_Filter_Config(TIM_Module* TIMx, TIM_FilterInitType* TIM_FilterInitStruct)
{
    uint32_t temp_value = 0;
    
    temp_value &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_FILTER_THRESH_MASK)) & 
                             ((uint32_t) ~((uint32_t)TIM_FILTER_WSIZE_MASK)) &
                             ((uint32_t) ~((uint32_t)TIM_FILTER_PSC_MASK)));

    temp_value |= (uint32_t)(TIM_FilterInitStruct->ThreshHold << (uint32_t)(TIM_FILTER_THRESH_OFFSET) | 
                             TIM_FilterInitStruct->WindowSize << (uint32_t)(TIM_FILTER_WSIZE_OFFSET) |
                             TIM_FilterInitStruct->Prescaler);

    if ((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
    {
        TIMx->C3FILT = temp_value;
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_Channel4_Filter_Config
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\param   TIM_FilterInitStruct: 
*\*\          - refer to the definition of TIM_FilterInitType
*\*\return  none
**/
void TIM_Channel4_Filter_Config(TIM_Module* TIMx, TIM_FilterInitType* TIM_FilterInitStruct)
{
    uint32_t temp_value = 0;
    
    temp_value &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_FILTER_THRESH_MASK)) & 
                             ((uint32_t) ~((uint32_t)TIM_FILTER_WSIZE_MASK)) &
                             ((uint32_t) ~((uint32_t)TIM_FILTER_PSC_MASK)));

    temp_value |= (uint32_t)(TIM_FilterInitStruct->ThreshHold << (uint32_t)(TIM_FILTER_THRESH_OFFSET) | 
                             TIM_FilterInitStruct->WindowSize << (uint32_t)(TIM_FILTER_WSIZE_OFFSET) |
                             TIM_FilterInitStruct->Prescaler);

    if ((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5))
    {
        TIMx->C4FILT = temp_value;
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_Break_Filter_Config
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\param   TIM_FilterInitStruct: 
*\*\          - refer to the definition of TIM_FilterInitType
*\*\return  none
**/
void TIM_Break_Filter_Config(TIM_Module* TIMx, TIM_FilterInitType* TIM_FilterInitStruct)
{
    uint32_t temp_value = 0;
    
    temp_value &= (uint32_t)(((uint32_t) ~((uint32_t)TIM_FILTER_THRESH_MASK)) & 
                             ((uint32_t) ~((uint32_t)TIM_FILTER_WSIZE_MASK)) &
                             ((uint32_t) ~((uint32_t)TIM_FILTER_PSC_MASK)));

    temp_value |= (uint32_t)(TIM_FilterInitStruct->ThreshHold << (uint32_t)(TIM_FILTER_THRESH_OFFSET) | 
                             TIM_FilterInitStruct->WindowSize << (uint32_t)(TIM_FILTER_WSIZE_OFFSET) |
                             TIM_FilterInitStruct->Prescaler);

    if ((TIMx == TIM1) || (TIMx == TIM8))
    {
        TIMx->BRK_FILT = temp_value;
    }
    else
    {
        /* none */
    }
}

/**
*\*\name    TIM_Channel1_Filter_Enable
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\return  none
**/
void TIM_Channel1_Filter_Enable(TIM_Module* TIMx)
{
    TIMx->C1FILT |= (uint32_t)(TIM_FILTER_ENABLE); 
}

/**
*\*\name    TIM_Channel1_Filter_Disable
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\return  none
**/
void TIM_Channel1_Filter_Disable(TIM_Module* TIMx)
{
    TIMx->C1FILT &= (uint32_t)(~TIM_FILTER_ENABLE);
}

/**
*\*\name    TIM_Channel2_Filter_Enable
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\return  none
**/
void TIM_Channel2_Filter_Enable(TIM_Module* TIMx)
{
    TIMx->C2FILT |= (uint32_t)(TIM_FILTER_ENABLE); 
}

/**
*\*\name    TIM_Channel2_Filter_Disable
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\return  none
**/
void TIM_Channel2_Filter_Disable(TIM_Module* TIMx)
{
    TIMx->C2FILT &= (uint32_t)(~TIM_FILTER_ENABLE);
}

/**
*\*\name    TIM_Channel3_Filter_Enable
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\return  none
**/
void TIM_Channel3_Filter_Enable(TIM_Module* TIMx)
{
    TIMx->C3FILT |= (uint32_t)(TIM_FILTER_ENABLE); 
}

/**
*\*\name    TIM_Channel3_Filter_Disable
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\return  none
**/
void TIM_Channel3_Filter_Disable(TIM_Module* TIMx)
{
    TIMx->C3FILT &= (uint32_t)(~TIM_FILTER_ENABLE);
}

/**
*\*\name    TIM_Channel4_Filter_Enable
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\return  none
**/
void TIM_Channel4_Filter_Enable(TIM_Module* TIMx)
{
    TIMx->C4FILT |= (uint32_t)(TIM_FILTER_ENABLE); 
}

/**
*\*\name    TIM_Channel4_Filter_Disable
*\*\param   TIMx:
*\*\          - TIM2
*\*\          - TIM3
*\*\          - TIM4
*\*\          - TIM5
*\*\return  none
**/
void TIM_Channel4_Filter_Disable(TIM_Module* TIMx)
{
    TIMx->C4FILT &= (uint32_t)(~TIM_FILTER_ENABLE);
}

/**
*\*\name    TIM_Break_Filter_Config
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  none
**/
void TIM_Break_Filter_Enable(TIM_Module * TIMx)
{
    TIMx->BRK_FILT |= (uint32_t)(TIM_FILTER_ENABLE); 
}

/**
*\*\name    TIM_Break_Filter_Config
*\*\param   TIMx:
*\*\          - TIM1
*\*\          - TIM8
*\*\return  none
**/
void TIM_Break_Filter_Disable(TIM_Module * TIMx)
{
    TIMx->BRK_FILT &= (uint32_t)(~TIM_FILTER_ENABLE);
}

