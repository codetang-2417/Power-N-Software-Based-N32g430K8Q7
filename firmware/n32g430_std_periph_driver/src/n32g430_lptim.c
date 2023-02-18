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
*\*\file      n32g430_lptim.c
*\*\author    Nations
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved. 
 */

#include "n32g430_lptim.h"
#include "n32g430_rcc.h"
 
/* LPTIM Driving Functions Declaration */

/**
*\*\name    LPTIM_Reset.
*\*\fun     Reset the LPTIME.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  none
**/
void LPTIM_Reset(LPTIM_Module *LPTIMx)
{
    /* LPTIME Reset */
    RCC_LPTIM_Reset();
}


/**
*\*\name    LPTIM_OFF.
*\*\fun     OFF the LPTIME instance.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  none
**/
void LPTIM_OFF(LPTIM_Module *LPTIMx)
{
  LPTIMx->CTRL &= (~LPTIM_CTRL_LPTIMEN);
}


/**
*\*\name    LPTIM_ON.
*\*\fun     ON the LPTIME instance.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  none
**/
void LPTIM_ON(LPTIM_Module *LPTIMx)
{
  LPTIMx->CTRL |= LPTIM_CTRL_LPTIMEN;
}


/**
*\*\name    LPTIM_Initializes_Structure.
*\*\fun     Set each fields of the LPTIM_InitStruct structure to its default value.
*\*\param   LPTIM_InitStruct
*\*\return  none
**/
void LPTIM_Initializes_Structure(LPTIM_InitType* LPTIM_InitStruct)
{
  /* Set the default configuration */
  LPTIM_InitStruct->ClockSource = LPTIM_CLK_SOURCE_INTERNAL;
  LPTIM_InitStruct->Prescaler   = LPTIM_PRESCALER_DIV1;
  LPTIM_InitStruct->Waveform    = LPTIM_OUTPUT_WAVEFORM_PWM;
  LPTIM_InitStruct->Polarity    = LPTIM_OUTPUT_POLARITY_REGULAR;
}


/**
*\*\name    LPTIM_Initializes.
*\*\fun     Configure the LPTIMx peripheral according to the specified parameters.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   LPTIM_InitStruct :
*\*\          -ClockSource
*\*\           -LPTIM_CLK_SOURCE_INTERNAL
*\*\           -LPTIM_CLK_SOURCE_EXTERNAL
*\*\          -Prescaler
*\*\           -LPTIM_PRESCALER_DIV1
*\*\           -LPTIM_PRESCALER_DIV2 
*\*\           -LPTIM_PRESCALER_DIV4 
*\*\           -LPTIM_PRESCALER_DIV8 
*\*\           -LPTIM_PRESCALER_DIV16
*\*\           -LPTIM_PRESCALER_DIV32
*\*\           -LPTIM_PRESCALER_DIV64
*\*\           -LPTIM_PRESCALER_DIV128
*\*\          -Waveform
*\*\           -LPTIM_OUTPUT_WAVEFORM_PWM
*\*\           -LPTIM_OUTPUT_WAVEFORM_SETONCE
*\*\          -Polarity
*\*\           -LPTIM_OUTPUT_POLARITY_REGULAR
*\*\           -LPTIM_OUTPUT_POLARITY_INVERSE
*\*\return  - SUCCESS: LPTIMx instance has been initialized
*\*\        - ERROR: LPTIMx instance hasn't been initialized
**/
ErrorStatus LPTIM_Initializes(LPTIM_Module *LPTIMx, LPTIM_InitType* LPTIM_InitStruct)
{
  ErrorStatus result = SUCCESS;

  /* The LPTIMx_CFG register must only be modified when the LPTIM is disabled 
     (ENABLE bit is reset to 0).
  */
  if (LPTIMx->CTRL & LPTIM_CTRL_LPTIMEN)
  {
    result = ERROR;
  }
  else
  {
    /* Set CKSEL bitfield according to ClockSource value */
    LPTIM_Clock_Source_Set(LPTIMx, LPTIM_InitStruct->ClockSource);
    /* Set PRESC bitfield according to Prescaler value */
    LPTIM_Prescaler_Set(LPTIMx, LPTIM_InitStruct->Prescaler);
    /* Set WAVE  bitfield according to Waveform value */
    LPTIM_Waveform_Set(LPTIMx, LPTIM_InitStruct->Waveform);
    /* Set WAVEPOL bitfield according to Polarity value */
    LPTIM_Polarity_Set(LPTIMx, LPTIM_InitStruct->Polarity);
  }
  return result;
}


/**
*\*\name    LPTIM_Counter_Start.
*\*\fun     Starts the LPTIM counter in the desired mode.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   OperatingMode
*\*\          -LPTIM_OPERATING_MODE_CONTINUOUS
*\*\          -LPTIM_OPERATING_MODE_ONESHOT
*\*\return  none
**/
void LPTIM_Counter_Start(LPTIM_Module *LPTIMx, uint32_t OperatingMode)
{
    /* Clear LPTIM_CTRL SNGMST and TSTCM bits */
    LPTIMx->CTRL &= ~(LPTIM_CTRL_TSTCM | LPTIM_CTRL_SNGMST);
    /* Set LPTIM_CTRL SNGMST and TSTCM bits */
    LPTIMx->CTRL |= OperatingMode;
}


/**
*\*\name    LPTIM_Update_Mode_Set.
*\*\fun     Set the LPTIM registers update mode (enable/disable register preload).
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   UpdateMode
*\*\          -LPTIM_UPDATE_MODE_IMMEDIATE
*\*\          -LPTIM_UPDATE_MODE_ENDOFPERIOD
*\*\return  none
**/
void LPTIM_Update_Mode_Set(LPTIM_Module *LPTIMx, uint32_t UpdateMode)
{
    /* Clear LPTIM_CFG RELOAD bits */
    LPTIMx->CFG &= ~LPTIM_CFG_RELOAD;
    /* Set LPTIM_CFG RELOAD bits */
    LPTIMx->CFG |= UpdateMode;
}


/**
*\*\name    LPTIM_Update_Mode_Get.
*\*\fun     Get the LPTIM registers update mode.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  
*\*\         -LPTIM_UPDATE_MODE_IMMEDIATE
*\*\         -LPTIM_UPDATE_MODE_ENDOFPERIOD
**/
uint32_t LPTIM_Update_Mode_Get(LPTIM_Module *LPTIMx)
{
    /* Return LPTIM_CFG RELOAD bits */
    return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_RELOAD);
}


/**
*\*\name    LPTIM_Auto_Reload_Set.
*\*\fun     Set the auto reload value.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   AutoReload
*\*\          -Value between Min_Data=0x00 and Max_Data=0xFFFF
*\*\return  none
**/
void LPTIM_Auto_Reload_Set(LPTIM_Module *LPTIMx, uint16_t AutoReload)
{
    /* Set the AutoReload to LPTIM_ARR registers */
    LPTIMx->ARR = AutoReload;
}


/**
*\*\name    LPTIM_Auto_Reload_Get.
*\*\fun     Get actual auto reload value.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  -Value between Min_Data=0x00 and Max_Data=0xFFFF   
**/
uint16_t LPTIM_Auto_Reload_Get(LPTIM_Module *LPTIMx)
{
    /* Return the value of LPTIM_ARR registers */
    return (uint16_t)LPTIMx->ARR;
}


/**
*\*\name    LPTIM_Compare_Set.
*\*\fun     Set the compare value.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   AutoReload
*\*\          -Value between Min_Data=0x00 and Max_Data=0xFFFF
*\*\return  none
**/
void LPTIM_Compare_Set(LPTIM_Module *LPTIMx, uint16_t CompareValue)
{
    /* Set the CompareValue to LPTIM_COMP registers */
    LPTIMx->COMPx = CompareValue;
}


/**
*\*\name    LPTIM_Compare_Get.
*\*\fun     Get actual compare value.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  -Value between Min_Data=0x00 and Max_Data=0xFFFF
**/
uint16_t LPTIM_Compare_Get(LPTIM_Module *LPTIMx)
{
    /* Return the value of LPTIM_COMP registers */
    return (uint16_t)LPTIMx->COMPx;
}


/**
*\*\name    LPTIM_Counter_Get.
*\*\fun     Get actual counter value.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  -Counter value
**/
uint16_t LPTIM_Counter_Get(LPTIM_Module *LPTIMx)
{
    /* Return the value of LPTIM_CNT registers */
    return (uint16_t)LPTIMx->CNT;
}


/**
*\*\name    LPTIM_Counter_Mode_Set.
*\*\fun     Set the counter mode (selection of the LPTIM counter clock source).
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   CounterMode
*\*\          -LPTIM_COUNTER_MODE_INTERNAL
*\*\          -LPTIM_COUNTER_MODE_EXTERNAL
*\*\return  none
**/
void LPTIM_Counter_Mode_Set(LPTIM_Module *LPTIMx, uint32_t CounterMode)
{
    /* Clear LPTIM_CFG CNTMEN bits */
    LPTIMx->CFG &= ~LPTIM_CFG_CNTMEN;
    /* Set LPTIM_CFG CNTMEN bits */
    LPTIMx->CFG |= CounterMode;
}


/**
*\*\name    LPTIM_Counter_Mode_Get.
*\*\fun     Get the counter mode.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  
*\*\        -LPTIM_COUNTER_MODE_INTERNAL
*\*\        -LPTIM_COUNTER_MODE_EXTERNAL
**/
uint32_t LPTIM_Counter_Mode_Get(LPTIM_Module *LPTIMx)
{
    /* Return LPTIM_CFG CNTMEN bits */
    return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_CNTMEN);
}


/**
*\*\name    LPTIM_Output_Config.
*\*\fun     Configure the LPTIM instance output (LPTIMx_OUT).
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   Waveform
*\*\          -LPTIM_OUTPUT_WAVEFORM_PWM
*\*\          -LPTIM_OUTPUT_WAVEFORM_SETONCE
*\*\param   Polarity
*\*\          -LPTIM_OUTPUT_POLARITY_REGULAR
*\*\          -LPTIM_OUTPUT_POLARITY_INVERSE
*\*\return  none
**/
void LPTIM_Output_Config(LPTIM_Module *LPTIMx, uint32_t Waveform, uint32_t Polarity)
{
    /* Clear LPTIM_CFG WAVE and WAVEPOL bits */
    LPTIMx->CFG &= ~(LPTIM_CFG_WAVE | LPTIM_CFG_WAVEPOL);
    /* Set LPTIM_CTRL WAVE and WAVEPOL bits */
    LPTIMx->CFG |= Waveform | Polarity;
}


/**
*\*\name    LPTIM_Waveform_Set.
*\*\fun     Set  waveform shape.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   Waveform
*\*\          -LPTIM_OUTPUT_WAVEFORM_PWM
*\*\          -LPTIM_OUTPUT_WAVEFORM_SETONCE
*\*\return  none
**/
void LPTIM_Waveform_Set(LPTIM_Module *LPTIMx, uint32_t Waveform)
{
    /* Clear LPTIM_CFG WAVE bits */
    LPTIMx->CFG &= ~LPTIM_CFG_WAVE;
    /* Set LPTIM_CFG WAVE bits */
    LPTIMx->CFG |= Waveform;
}


/**
*\*\name    LPTIM_Waveform_Get.
*\*\fun      Get actual waveform shape.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  
*\*\        -LPTIM_OUTPUT_WAVEFORM_PWM
*\*\        -LPTIM_OUTPUT_WAVEFORM_SETONCE
**/
uint32_t LPTIM_Waveform_Get(LPTIM_Module *LPTIMx)
{
    /* Return LPTIM_CFG WAVE bits */
    return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_WAVE);
}


/**
*\*\name    LPTIM_Polarity_Set.
*\*\fun     Set  output polarity.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   Polarity
*\*\          -LPTIM_OUTPUT_POLARITY_REGULAR
*\*\          -LPTIM_OUTPUT_POLARITY_INVERSE
*\*\return  none
**/
void LPTIM_Polarity_Set(LPTIM_Module *LPTIMx, uint32_t Polarity)
{
    /* Clear LPTIM_CFG WAVEPOL bits */
    LPTIMx->CFG &= ~LPTIM_CFG_WAVEPOL;
    /* Set LPTIM_CFG WAVEPOL bits */
    LPTIMx->CFG |= Polarity;
}

/**
*\*\name    LPTIM_Polarity_Get.
*\*\fun     Get actual output polarity.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  
*\*\        -LPTIM_OUTPUT_POLARITY_REGULAR
*\*\        -LPTIM_OUTPUT_POLARITY_INVERSE
**/
uint32_t LPTIM_Polarity_Get(LPTIM_Module *LPTIMx)
{
    /* Return LPTIM_CFG WAVEPOL bits */
    return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_WAVEPOL);
}


/**
*\*\name    LPTIM_Prescaler_Set.
*\*\fun     Set actual prescaler division ratio.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   Prescaler
*\*\         -LPTIM_PRESCALER_DIV1
*\*\         -LPTIM_PRESCALER_DIV2
*\*\         -LPTIM_PRESCALER_DIV4
*\*\         -LPTIM_PRESCALER_DIV8
*\*\         -LPTIM_PRESCALER_DIV16
*\*\         -LPTIM_PRESCALER_DIV32
*\*\         -LPTIM_PRESCALER_DIV64
*\*\         -LPTIM_PRESCALER_DIV128
*\*\return  none
**/
void LPTIM_Prescaler_Set(LPTIM_Module *LPTIMx, uint32_t Prescaler)
{
    /* Clear LPTIM_CFG CLKPRE bits */
    LPTIMx->CFG &= ~LPTIM_CFG_CLKPRE;
    /* Set LPTIM_CFG CLKPRE bits */
    LPTIMx->CFG |= Prescaler;
}


/**
*\*\name    LPTIM_Prescaler_Get.
*\*\fun     Get actual prescaler division ratio.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  
*\*\        -LPTIM_PRESCALER_DIV1
*\*\        -LPTIM_PRESCALER_DIV2
*\*\        -LPTIM_PRESCALER_DIV4
*\*\        -LPTIM_PRESCALER_DIV8
*\*\        -LPTIM_PRESCALER_DIV16
*\*\        -LPTIM_PRESCALER_DIV32
*\*\        -LPTIM_PRESCALER_DIV64
*\*\        -LPTIM_PRESCALER_DIV128
**/
uint32_t LPTIM_Prescaler_Get(LPTIM_Module *LPTIMx)
{
    /* Return LPTIM_CFG CLKPRE bits */
    return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_CLKPRE);
}


/** LPTIM_EF_Trigger_Configuration Trigger Configuration **/


/**
*\*\name    LPTIM_Timeout_Enable.
*\*\fun     Enable the timeout function.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  none
**/
void LPTIM_Timeout_Enable(LPTIM_Module *LPTIMx)
{
    /* Set LPTIM_CFG TIMOUTEN bits */
    LPTIMx->CFG |= LPTIM_CFG_TIMOUTEN;
}


/**
*\*\name    LPTIM_Timeout_Disable.
*\*\fun     Disable the timeout function.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  none
**/
void LPTIM_Timeout_Disable(LPTIM_Module *LPTIMx)
{
    /* Clear LPTIM_CFG TIMOUTEN bits */
    LPTIMx->CFG &= ~LPTIM_CFG_TIMOUTEN;
}


/**
*\*\name   LPTIM_Timeout_Get.
*\*\fun    Indicate whether the timeout function is enabled.
*\*\param  LPTIMx 
*\*\        -Low-Power Timer instance
*\*\return 
*\*\        -ENABLE
*\*\        -DISABLE      
**/
FunctionalState LPTIM_Timeout_Get(LPTIM_Module *LPTIMx)
{
    /* Return LPTIM_CFG TIMOUTEN bits */
    return (((LPTIMx->CFG & LPTIM_CFG_TIMOUTEN) == LPTIM_CFG_TIMOUTEN) ? ENABLE : DISABLE);
}


/**
*\*\name    LPTIM_Software_Trigger.
*\*\fun     Start the LPTIM counter on software trig.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  none
**/
void LPTIM_Software_Trigger(LPTIM_Module *LPTIMx)
{
    LPTIMx->CFG &= ~LPTIM_CFG_TRGEN;
}


/**
*\*\name    LPTIM_Trigger_Config.
*\*\fun     Configure the external trigger used as a trigger event for the LPTIM.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   Source
*\*\         -LPTIM_TRIG_SOURCE_GPIO
*\*\         -LPTIM_TRIG_SOURCE_RTCALARMA
*\*\         -LPTIM_TRIG_SOURCE_RTCALARMB
*\*\         -LPTIM_TRIG_SOURCE_RTCTAMP1
*\*\         -LPTIM_TRIG_SOURCE_RTCTAMP2
*\*\         -LPTIM_TRIG_SOURCE_RTCTAMP3
*\*\         -LPTIM_TRIG_SOURCE_COMP1
*\*\         -LPTIM_TRIG_SOURCE_COMP2
*\*\         -LPTIM_TRIG_SOURCE_COMP3
*\*\param   Filter 
*\*\         -LPTIM_TRIG_FILTER_NONE
*\*\         -LPTIM_TRIG_FILTER_2
*\*\         -LPTIM_TRIG_FILTER_4
*\*\         -LPTIM_TRIG_FILTER_8
*\*\param   Polarity 
*\*\         -LPTIM_TRIG_POLARITY_RISING
*\*\         -LPTIM_TRIG_POLARITY_FALLING
*\*\         -LPTIM_TRIG_POLARITY_RISING_FALLING
*\*\return  none
**/

void LPTIM_Trigger_Config(LPTIM_Module *LPTIMx, uint32_t Source, uint32_t Filter, uint32_t Polarity)
{
  LPTIMx->CFG &= ~(LPTIM_CFG_TRGSEL | LPTIM_CFG_TRIGFLT | LPTIM_CFG_TRGEN);
  LPTIMx->CFG |= (Source | Filter | Polarity);
}

/**
*\*\name   LPTIM_Trigger_Source_Get.
*\*\fun    Get actual external trigger source.
*\*\param  LPTIMx 
*\*\        -Low-Power Timer instance
*\*\return 
*\*\       -LPTIM_TRIG_SOURCE_GPIO
*\*\       -LPTIM_TRIG_SOURCE_RTCALARMA
*\*\       -LPTIM_TRIG_SOURCE_RTCALARMB
*\*\       -LPTIM_TRIG_SOURCE_RTCTAMP1
*\*\       -LPTIM_TRIG_SOURCE_RTCTAMP2
*\*\       -LPTIM_TRIG_SOURCE_RTCTAMP3
*\*\       -LPTIM_TRIG_SOURCE_COMP1
*\*\       -LPTIM_TRIG_SOURCE_COMP2
*\*\       -LPTIM_TRIG_SOURCE_COMP3
*\*\        
**/
uint32_t LPTIM_Trigger_Source_Get(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_TRGSEL);
}

/**
*\*\name   LPTIM_Trigger_Filter_Get.
*\*\fun    Get actual external trigger filter.
*\*\param  LPTIMx 
*\*\        -Low-Power Timer instance
*\*\return 
*\*\       -LPTIM_TRIG_FILTER_NONE
*\*\       -LPTIM_TRIG_FILTER_2
*\*\       -LPTIM_TRIG_FILTER_4
*\*\       -LPTIM_TRIG_FILTER_8
*\*\        
**/
uint32_t LPTIM_Trigger_Filter_Get(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_TRIGFLT);
}

/**
*\*\name   LPTIM_Trigger_Polarity_Get.
*\*\fun    Get actual external trigger polarity.
*\*\param  LPTIMx 
*\*\        -Low-Power Timer instance
*\*\return 
*\*\       -LPTIM_TRIG_POLARITY_RISING
*\*\       -LPTIM_TRIG_POLARITY_FALLING
*\*\       -LPTIM_TRIG_POLARITY_RISING_FALLING       
**/
uint32_t LPTIM_Trigger_Polarity_Get(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_TRGEN);
}



/** LPTIM_EF_Clock_Configuration Clock Configuration **/
  


/**
*\*\name    LPTIM_Clock_Source_Set.
*\*\fun     Set the source of the clock used by the LPTIM instance.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   ClockSource
*\*\         -LPTIM_CLK_SOURCE_INTERNAL
*\*\         -LPTIM_CLK_SOURCE_EXTERNAL
*\*\return  none
**/
void LPTIM_Clock_Source_Set(LPTIM_Module *LPTIMx, uint32_t ClockSource)
{
  LPTIMx->CFG &= ~LPTIM_CFG_CLKSEL;
  LPTIMx->CFG |= ClockSource;
}

/**
*\*\name   LPTIM_Clock_Source_Get.
*\*\fun    Get actual LPTIM instance clock source.
*\*\param  LPTIMx 
*\*\        -Low-Power Timer instance
*\*\return 
*\*\       -LPTIM_CLK_SOURCE_INTERNAL
*\*\       -LPTIM_CLK_SOURCE_EXTERNAL     
**/
uint32_t LPTIM_Clock_Source_Get(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_CLKSEL);
}

/**
*\*\name    LPTIM_Clock_Config.
*\*\fun     Configure the active edge or edges used by the counter when the LPTIM is clocked by an external clock source.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   ClockFilter
*\*\         -LPTIM_CLK_FILTER_NONE
*\*\         -LPTIM_CLK_FILTER_2
*\*\         -LPTIM_CLK_FILTER_4
*\*\         -LPTIM_CLK_FILTER_8
*\*\param   ClockPolarity 
*\*\         -LPTIM_CLK_POLARITY_RISING
*\*\         -LPTIM_CLK_POLARITY_FALLING
*\*\         -LPTIM_CLK_POLARITY_RISING_FALLING
*\*\return  none
**/
void LPTIM_Clock_Config(LPTIM_Module *LPTIMx, uint32_t ClockFilter, uint32_t ClockPolarity)
{
  LPTIMx->CFG &= ~(LPTIM_CFG_CLKFLT | LPTIM_CFG_CLKPOL);
  LPTIMx->CFG |= (ClockFilter | ClockPolarity);
}

/**
*\*\name   LPTIM_Clock_Polarity_Get.
*\*\fun    Get actual clock polarity.
*\*\param  LPTIMx 
*\*\        -Low-Power Timer instance
*\*\return 
*\*\        -LPTIM_CLK_POLARITY_RISING
*\*\        -LPTIM_CLK_POLARITY_FALLING
*\*\        -LPTIM_CLK_POLARITY_RISING_FALLING    
**/
uint32_t LPTIM_Clock_Polarity_Get(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_CLKPOL);
}

/**
*\*\name   LPTIM_Clock_Filter_Get.
*\*\fun    Get actual clock digital filter.
*\*\param  LPTIMx 
*\*\        -Low-Power Timer instance
*\*\return 
*\*\        -LPTIM_CLK_FILTER_NONE
*\*\        -LPTIM_CLK_FILTER_2
*\*\        -LPTIM_CLK_FILTER_4
*\*\        -LPTIM_CLK_FILTER_8
**/
uint32_t LPTIM_Clock_Filter_Get(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_CLKFLT);
}


/** LPTIM_EF_Encoder_Mode Encoder Mode **/


/**
*\*\name    LPTIM_Encoder_Mode_Set.
*\*\fun     Configure the encoder mode.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   ClockPolarity 
*\*\         -LPTIM_ENCODER_MODE_RISING
*\*\         -LPTIM_ENCODER_MODE_FALLING
*\*\         -LPTIM_ENCODER_MODE_RISING_FALLING
*\*\return  none
**/
void LPTIM_Encoder_Mode_Set(LPTIM_Module *LPTIMx, uint32_t EncoderMode)
{
  LPTIMx->CFG &= ~LPTIM_CFG_CLKPOL;
  LPTIMx->CFG |= EncoderMode;
}

/**
*\*\name   LPTIM_Encoder_Mode_Get.
*\*\fun    Get actual encoder mode.
*\*\param  LPTIMx 
*\*\        -Low-Power Timer instance
*\*\return 
*\*\        -LPTIM_ENCODER_MODE_RISING
*\*\        -LPTIM_ENCODER_MODE_FALLING
*\*\        -LPTIM_ENCODER_MODE_RISING_FALLING
**/
uint32_t LPTIM_Encoder_Mode_Get(LPTIM_Module *LPTIMx)
{
  return (uint32_t)(LPTIMx->CFG & LPTIM_CFG_CLKPOL);
}

/**
*\*\name    LPTIM_Encoder_Mode_Enable.
*\*\fun     Enable the encoder mode.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  none
**/
void LPTIM_Encoder_Mode_Enable(LPTIM_Module *LPTIMx)
{
  LPTIMx->CFG |= LPTIM_CFG_ENC;
}

/**
*\*\name    LPTIM_Encoder_Mode_Disable.
*\*\fun     Disable the encoder mode.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  none
**/
void LPTIM_Encoder_Mode_Disable(LPTIM_Module *LPTIMx)
{
  LPTIMx->CFG &= ~LPTIM_CFG_ENC;
}

/**
*\*\name    LPTIM_NoEncoder_Mode_Enable.
*\*\fun     Enable the non-orthogonal encoder mode.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  none
**/
void LPTIM_NoEncoder_Mode_Enable(LPTIM_Module *LPTIMx)
{
  LPTIMx->CFG |= LPTIM_CFG_NENC;
}

/**
*\*\name    LPTIM_NoEncoder_Mode_Disable.
*\*\fun     Disable the non-orthogonal encoder mode.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  none
**/
void LPTIM_NoEncoder_Mode_Disable(LPTIM_Module *LPTIMx)
{
  LPTIMx->CFG &= ~LPTIM_CFG_NENC;
}


/**
*\*\name    LPTIM_Encoder_Mode_Check.
*\*\fun     Check the encoder mode is enable or disable.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\return  
*\*\        -ENABLE
*\*\        -DISABLE
**/

FunctionalState LPTIM_Encoder_Mode_Check(LPTIM_Module *LPTIMx)
{
  return (((LPTIMx->CFG & LPTIM_CFG_ENC) == LPTIM_CFG_ENC) ? ENABLE : DISABLE);
}

/**
*\*\name    LPTIM_Input1_Option.
*\*\fun     Option LPTIN input1 connected.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   option 
*\*\          -LPTIM_INTPUT1_CONNECT_TO_GPIO
*\*\          -LPTIM_INTPUT1_CONNECT_TO_COMP1_OUT
*\*\          -LPTIM_INTPUT1_CONNECT_TO_COMP2_OUT
*\*\          -LPTIM_INTPUT1_CONNECT_TO_COMP3_OUT
*\*\return  none
**/

void LPTIM_Input1_Option(LPTIM_Module *LPTIMx, uint32_t option)
{
  LPTIMx->OPT &= LPTIM_INTPUT1_MASK;
  LPTIMx->OPT |= option;
}


/**
*\*\name    LPTIM_Input2_Option.
*\*\fun     Option LPTIN input2 connected.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   option 
*\*\          -LPTIM_INTPUT2_CONNECT_TO_GPIO
*\*\          -LPTIM_INTPUT2_CONNECT_TO_COMP1_OUT
*\*\          -LPTIM_INTPUT2_CONNECT_TO_COMP2_OUT
*\*\          -LPTIM_INTPUT2_CONNECT_TO_COMP3_OUT
*\*\return  none
**/

void LPTIM_Input2_Option(LPTIM_Module *LPTIMx, uint32_t option)
{
  LPTIMx->OPT &= LPTIM_INTPUT2_MASK;
  LPTIMx->OPT |= option;
}

/** LPTIM_EF_FLAG_Management FLAG Management **/

/**
*\*\name    LPTIM_FLAG_Clear.
*\*\fun     Clear the low power timer flag.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   LPTIM_flag_clear 
*\*\         -LPTIM_CLEAR_FLAG_CMPM      the compare match flag
*\*\         -LPTIM_CLEAR_FLAG_ARRM      the autoreload match flag
*\*\         -LPTIM_CLEAR_FLAG_EXTRIG    the external trigger valid edge flag
*\*\         -LPTIM_CLEAR_FLAG_CMPUPD    the compare register update interrupt flag
*\*\         -LPTIM_CLEAR_FLAG_ARRUPD    the autoreload register update interrupt flag
*\*\         -LPTIM_CLEAR_FLAG_UP        the counter direction change to up interrupt flag
*\*\         -LPTIM_CLEAR_FLAG_DOWN      the counter direction change to down interrupt flag
*\*\return  none
**/
void LPTIM_FLAG_Clear(LPTIM_Module *LPTIMx, uint32_t LPTIM_flag_clear)
{
  LPTIMx->INTCLR |= LPTIM_flag_clear;
}


/**
*\*\name    LPTIM_FLAG_Clear.
*\*\fun     Check the low power timer flag.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   LPTIM_flag_check 
*\*\         -LPTIM_INTSTS_FLAG_CMPM     compare match interrupt 
*\*\         -LPTIM_INTSTS_FLAG_ARRM     a autoreload match interrupt
*\*\         -LPTIM_INTSTS_FLAG_EXTRIG   a valid edge on the selected external trigger input
*\*\         -LPTIM_INTSTS_FLAG_CMPUPD   the APB bus write operation to the LPTIMx_CMP register has been successfully completed
*\*\         -LPTIM_INTSTS_FLAG_ARRUPD   the APB bus write operation to the LPTIMx_ARR register has been successfully completed
*\*\         -LPTIM_INTSTS_FLAG_UP       the counter direction has changed from down to up (when the LPTIM instance operates in encoder mode)
*\*\         -LPTIM_INTSTS_FLAG_DOWN     the counter direction has changed from up to down (when the LPTIM instance operates in encoder mode)
*\*\return  none
**/
FlagStatus LPTIM_Flag_Get(LPTIM_Module *LPTIMx, uint32_t LPTIM_flag)
{
  return (((LPTIMx->INTSTS & LPTIM_flag) == LPTIM_flag) ? SET : RESET);
}


/** LPTIM_EF_IT_Management Interrupt Management **/


/**
*\*\name    LPTIM_Interrupt_Enable.
*\*\fun     Enable the low-power Timer interrupt.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   LPTIM_interrupt_flag
*\*\         -LPTIM_INT_CMPMIE     compare match interrupt
*\*\         -LPTIM_INT_ARRMIE     autoreload match interrupt
*\*\         -LPTIM_INT_EXTRIGIE   external trigger valid edge interrupt
*\*\         -LPTIM_INT_CMPUPDIE   compare register write completed interrupt
*\*\         -LPTIM_INT_ARRUPDIE   autoreload register write completed interrupt
*\*\         -LPTIM_INT_UPIE       direction change to up interrupt
*\*\         -LPTIM_INT_DOWNIE     direction change to down interrupt
*\*\return  none
**/
void LPTIM_Interrupt_Enable(LPTIM_Module *LPTIMx, uint32_t LPTIM_interrupt_flag)
{
  LPTIMx->INTEN |= LPTIM_interrupt_flag;
}



/**
*\*\name    LPTIM_Interrupt_Disable.
*\*\fun     Disable the low-power Timer interrupt.
*\*\param   LPTIMx 
*\*\          -Low-Power Timer instance
*\*\param   LPTIM_interrupt_flag
*\*\         -LPTIM_INT_CMPMIE    compare match interrupt
*\*\         -LPTIM_INT_ARRMIE    autoreload match interrupt
*\*\         -LPTIM_INT_EXTRIGIE  external trigger valid edge interrupt
*\*\         -LPTIM_INT_CMPUPDIE  compare register write completed interrupt
*\*\         -LPTIM_INT_ARRUPDIE  autoreload register write completed interrupt
*\*\         -LPTIM_INT_UPIE      direction change to up interrupt
*\*\         -LPTIM_INT_DOWNIE    direction change to down interrupt
*\*\return  none
**/
void LPTIM_Interrupt_Disable(LPTIM_Module *LPTIMx, uint32_t LPTIM_interrupt_flag)
{
  LPTIMx->INTEN &= ~LPTIM_interrupt_flag;
}


/**
*\*\name    LPTIM_Interrupt_Check.
*\*\fun     Check the low-power Timer interrupt.
*\*\param   LPTIMx 
*\*\         -Low-Power Timer instance
*\*\param   LPTIM_interrupt
*\*\         -LPTIM_INT_CMPMIE    compare match interrupt
*\*\         -LPTIM_INT_ARRMIE    the autoreload match interrupt
*\*\         -LPTIM_INT_EXTRIGIE  external trigger valid edge interrupt
*\*\         -LPTIM_INT_CMPUPDIE  compare register write completed interrupt
*\*\         -LPTIM_INT_ARRUPDIE  autoreload register write completed interrupt
*\*\         -LPTIM_INT_UPIE      direction change to up interrupt
*\*\         -LPTIM_INT_DOWNIE    direction change to down interrupt
*\*\return  none
**/

INTStatus LPTIM_Interrupt_Check(LPTIM_Module *LPTIMx, uint32_t LPTIM_interrupt)
{
  return (((LPTIMx->INTEN & LPTIM_interrupt) == LPTIM_interrupt) ? SET : RESET);
}

