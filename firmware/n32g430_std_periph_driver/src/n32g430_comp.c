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
*\*\file n32g430_comp.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#include "n32g430_comp.h"
#include "n32g430_rcc.h"


/** COMP Driving Functions Declaration**/


/**
*\*\name    COMP_Reset.
*\*\fun     Reset the COMP registers.
*\*\return  none
**/
void COMP_Reset(void)
{
    RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_COMP);
    RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_COMP_FILT);  
}

/**
*\*\name    COMP_Initializes_Structure.
*\*\fun     Fills all COMP_initstruct member with default value.
*\*\param   COMP_initstruct :
*\*\          - Blking
*\*\          - Hyst
*\*\          - PolRev
*\*\          - OutSel
*\*\          - InpSel
*\*\          - InmSel
*\*\          - FilterEn
*\*\          - ClkPsc
*\*\          - SampWindow
*\*\          - Threshold
*\*\          - En
*\*\return  none
**/
void COMP_Initializes_Structure(COMP_InitType* COMP_initstruct)
{
    /* Reset COMP init structure parameters values */ 
    /* Initialize the Blking */
    COMP_initstruct->Blking            = COMP_BLANKING_NO;
    /* Initialize the Hyst */
    COMP_initstruct->Hyst              = COMP_HYST_NO;
    /* Initialize the PolRev */
    COMP_initstruct->PolRev            = COMP_OUTPOL_NFLIP;
    /* Initialize the OutSel */
    COMP_initstruct->OutSel            = COMP_OUTSEL_RES;
    /* Initialize the InpSel */
    COMP_initstruct->InpSel            = COMP_INPSEL_RES;
    /* Initialize the InmSel */
    COMP_initstruct->InmSel            = COMP_INMSEL_RES;
    /* Initialize the FilterEn */
    COMP_initstruct->FilterEn          = DISABLE;
    /* Initialize the ClkPsc */
    COMP_initstruct->ClkPsc            = 0;
    /* Initialize the SampWindow */
    COMP_initstruct->SampWindow        = 0;
    /* Initialize the Threshold */
    COMP_initstruct->Threshold         = 0;
    /* Initialize the En */
    COMP_initstruct->En                = DISABLE;
}

/**
*\*\name    COMP_Filter_SampWindow_Config.
*\*\fun     Configures the COMPx filter sampwindow with a correct value. 
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   sampwin;_value:
*\*\          - from 0 to 31.
*\*\return  none
**/
void COMP_Filter_SampWindow_Config(COMPX COMPx, uint8_t sampwin_value)
{
    switch (COMPx)
    {
        case  COMP1:
            /* Clear COMPx_FILC SAMPW[4:0] bits */
            COMP->Cmp1.FILC &= COMP_FILTER_SAMPW_MASK;
            /* Set COMPx_FILC SAMPW[4:0] bits */
            COMP->Cmp1.FILC |= sampwin_value << REG_BIT6_OFFSET;
            break;
        case  COMP2:
            /* Clear COMPx_FILC SAMPW[4:0] bits */
            COMP->Cmp2.FILC &= COMP_FILTER_SAMPW_MASK;
            /* Set COMPx_FILC SAMPW[4:0] bits */
            COMP->Cmp2.FILC |= sampwin_value << REG_BIT6_OFFSET;
            break;
        case  COMP3:
            /* Clear COMPx_FILC SAMPW[4:0] bits */
            COMP->Cmp3.FILC &= COMP_FILTER_SAMPW_MASK;
            /* Set COMPx_FILC SAMPW[4:0] bits */
            COMP->Cmp3.FILC |= sampwin_value << REG_BIT6_OFFSET;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_Filter_Threshold_Config.
*\*\fun     Configures the COMPx filter Threshold with a correct value. 
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   Threshold_value:
*\*\          - Value must be greater than SAMPW / 2 .
*\*\return  none
**/
void COMP_Filter_Threshold_Config(COMPX COMPx, uint8_t Threshold_value)
{
    switch (COMPx)
    {
        case  COMP1:
            /* Clear COMPx_FILC THRESH[4:0] bits */
            COMP->Cmp1.FILC &= COMP_FILTER_THRESHOLD_MASK;
            /* Set COMPx_FILC THRESH[4:0] bits */
            COMP->Cmp1.FILC |= Threshold_value << REG_BIT1_OFFSET;
            break;
        case  COMP2:
            /* Clear COMPx_FILC THRESH[4:0] bits */
            COMP->Cmp2.FILC &= COMP_FILTER_THRESHOLD_MASK;
            /* Set COMPx_FILC THRESH[4:0] bits */
            COMP->Cmp2.FILC |= Threshold_value << REG_BIT1_OFFSET;
            break;
        case  COMP3:
            /* Clear COMPx_FILC THRESH[4:0] bits */
            COMP->Cmp3.FILC &= COMP_FILTER_THRESHOLD_MASK;
            /* Set COMPx_FILC THRESH[4:0] bits */
            COMP->Cmp3.FILC |= Threshold_value << REG_BIT1_OFFSET;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_Filter_Enable.
*\*\fun     Configures COMPx filter enable.
*\*\          - Before the COMPx filter is enabled, the clock of the COMPx filter must be turned on.
*\*\          - Configure RCC_APB1PCLKEN. COMPFILTEN = 1 to enable COMPx filter, the RCC driver function can configure this.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\return  none
**/
void COMP_Filter_Enable(COMPX COMPx)
{
    switch (COMPx)
    {
        case COMP1:
            /* Set COMPx_FILC FILTER bits */
            COMP->Cmp1.FILC |= COMP_FILTER_ENBALE;
            break;
        case COMP2:
            /* Set COMPx_FILC FILTER bits */
            COMP->Cmp2.FILC |= COMP_FILTER_ENBALE;
            break;
        case COMP3:
            /* Set COMPx_FILC FILTER bits */
            COMP->Cmp3.FILC |= COMP_FILTER_ENBALE;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_Filter_Disable.
*\*\fun     Configures COMPx filter disable.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\return  none
**/
void COMP_Filter_Disable(COMPX COMPx)
{
    switch (COMPx)
    {
        case COMP1:
            /* Clear COMPx_FILC FILTER bits */
            COMP->Cmp1.FILC &= COMP_FILTER_DISABLE;
            break;
        case COMP2:
            /* Clear COMPx_FILC FILTER bits */
            COMP->Cmp2.FILC &= COMP_FILTER_DISABLE;
            break;
        case COMP3:
            /* Clear COMPx_FILC FILTER bits */
            COMP->Cmp3.FILC &= COMP_FILTER_DISABLE;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_Filter_Clock_Prescale_Config.
*\*\fun     Configures The COMPx low filter prescale . 
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   clkpsc_value:
*\*\        Value can be set from 0 to 32767.
*\*\return  none
**/
void COMP_Filter_Clock_Prescale_Config(COMPX COMPx, uint16_t clkpsc_value)
{
    switch (COMPx)
    {
        case COMP1:
            /* Clear COMPx_FILP CLKPSC[15:0] bits */
            COMP->Cmp1.FILP &= COMP_FILTER_CLKPSC_MASK;
            /* Set COMPx_FILP CLKPSC[15:0] bits */
            COMP->Cmp1.FILP |= clkpsc_value;
            break;
        case COMP2:
            /* Clear COMPx_FILP CLKPSC[15:0] bits */
            COMP->Cmp2.FILP &= COMP_FILTER_CLKPSC_MASK;
            /* Set COMPx_FILP CLKPSC[15:0] bits */
            COMP->Cmp2.FILP |= clkpsc_value;
            break;
        case COMP3:
            /* Clear COMPx_FILP CLKPSC[15:0] bits */
            COMP->Cmp3.FILP &= COMP_FILTER_CLKPSC_MASK;
            /* Set COMPx_FILP CLKPSC[15:0] bits */
            COMP->Cmp3.FILP |= clkpsc_value;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_Blking_Soucre_Config.
*\*\fun     Configures which TIMx output signal to control COMPx Blking. 
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   blking_mode :
*\*\          - COMP_BLANKING_NO
*\*\          - COMP_BLANKING_TIM1_OC5
*\*\          - COMP_BLANKING_TIM8_OC5
*\*\return  none
**/
void COMP_Blking_Soucre_Config(COMPX COMPx, uint32_t blking_mode)
{
    switch (COMPx)
    {
        case COMP1:
            /* Clear COMPx_CTRL BLKING[2:0] bits */
            COMP->Cmp1.CTRL &= COMP_BLANKING_MASK;
            /* Set COMPx_CTRL BLKING[2:0] bits */
            COMP->Cmp1.CTRL |= blking_mode;
            break;
        case COMP2:
            /* Clear COMPx_CTRL BLKING[2:0] bits */
            COMP->Cmp2.CTRL &= COMP_BLANKING_MASK;
            /* Set COMPx_CTRL BLKING[2:0] bits */
            COMP->Cmp2.CTRL |= blking_mode;
            break;
        case COMP3:
            /* Clear COMPx_CTRL BLKING[2:0] bits */
            COMP->Cmp3.CTRL &= COMP_BLANKING_MASK;
            /* Set COMPx_CTRL BLKING[2:0] bits */
            COMP->Cmp3.CTRL |= blking_mode;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_Hysteresis_Level_Config.
*\*\fun     Configures COMPx hysteresis level.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   hyst_mode :
*\*\          - COMP_HYST_NO   
*\*\          - COMP_HYST_LOW     5.1mV-level
*\*\          - COMP_HYST_MID     15mV-level
*\*\          - COMP_HYST_HIGH    25mV-level   
*\*\return  none
**/
void COMP_Hysteresis_Level_Config(COMPX COMPx, uint32_t hyst_mode)
{
    switch (COMPx)
    {
        case COMP1:
            /* Clear COMPx_CTRL HYST[1:0] bits */
            COMP->Cmp1.CTRL &= COMP_HYST_MASK;
            /* Set COMPx_CTRL HYST[1:0] bits */
            COMP->Cmp1.CTRL |= hyst_mode;
            break;
        case COMP2:
            /* Clear COMPx_CTRL HYST[1:0] bits */
            COMP->Cmp2.CTRL &= COMP_HYST_MASK;
            /* Set COMPx_CTRL HYST[1:0] bits */
            COMP->Cmp2.CTRL |= hyst_mode;
            break;
        case COMP3:
            /* Clear COMPx_CTRL HYST[1:0] bits */
            COMP->Cmp3.CTRL &= COMP_HYST_MASK;
            /* Set COMPx_CTRL HYST[1:0] bits */
            COMP->Cmp3.CTRL |= hyst_mode;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_Output_Polarity_Config.
*\*\fun     Configures COMPx output signal polarity overturn or not.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   output_pol :
*\*\          - COMP_OUTPOL_FLIP   
*\*\          - COMP_OUTPOL_NFLIP   
*\*\return  none
**/
void COMP_Output_Polarity_Config(COMPX COMPx, uint32_t output_pol)
{
    switch (COMPx)
    {
        case COMP1:
            /* Clear COMPx_CTRL POL bits */
            COMP->Cmp1.CTRL &= COMP_OUTPOL_MASK;
            /* Set COMPx_CTRL POL bits */
            COMP->Cmp1.CTRL |= output_pol;
            break;
        case COMP2:
            /* Clear COMPx_CTRL POL bits */
            COMP->Cmp2.CTRL &= COMP_OUTPOL_MASK;
            /* Set COMPx_CTRL POL bits */
            COMP->Cmp2.CTRL |= output_pol;
            break;
        case COMP3:
            /* Clear COMPx_CTRL POL bits */
            COMP->Cmp3.CTRL &= COMP_OUTPOL_MASK;
            /* Set COMPx_CTRL POL bits */
            COMP->Cmp3.CTRL |= output_pol;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_InpSel_Config.
*\*\fun     Configures COMPx inpsel.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   vpsel :
*\*\             comp1 inp sel 
*\*\            - COMP1_INPSEL_PA0                   
*\*\            - COMP1_INPSEL_PA2                   
*\*\            - COMP1_INPSEL_PA12                  
*\*\            - COMP1_INPSEL_PB3                   
*\*\            - COMP1_INPSEL_PB4                   
*\*\            - COMP1_INPSEL_PB10                  
*\*\            - COMP1_INPSEL_PA1                   
*\*\            - COMP1_INPSEL_FLOAT              
*\*\             comp2 inp sel 
*\*\            - COMP2_INPSEL_PA1                   
*\*\            - COMP2_INPSEL_PA3                  
*\*\            - COMP2_INPSEL_PA6                  
*\*\            - COMP2_INPSEL_PA7                  
*\*\            - COMP2_INPSEL_PA11                
*\*\            - COMP2_INPSEL_PA15                
*\*\            - COMP2_INPSEL_PB7                 
*\*\            - COMP2_INPSEL_FLOAT                               
*\*\             comp3 inp sel 
*\*\            - COMP3_INPSEL_PA0               
*\*\            - COMP3_INPSEL_PB1                   
*\*\            - COMP3_INPSEL_PB11                  
*\*\            - COMP3_INPSEL_PB15                  
*\*\            - COMP3_INPSEL_PB3                   
*\*\            - COMP3_INPSEL_PB5                   
*\*\            - COMP3_INPSEL_FLOAT                 
*\*\            - COMP3_INPSEL_FLOAT                               
*\*\return  none
**/
void COMP_InpSel_Config(COMPX COMPx, uint32_t vpsel)
{
    switch (COMPx)
    {
        case COMP1:
            /* Clear COMPx_CTRL INPSEL[2:0] bits */
            COMP->Cmp1.CTRL &= COMP_INPSEL_MASK;
            /* Set COMPx_CTRL INPSEL[2:0] bits */
            COMP->Cmp1.CTRL |= vpsel;
            break;
        case COMP2:
            /* Clear COMPx_CTRL INPSEL[2:0] bits */
            COMP->Cmp2.CTRL &= COMP_INPSEL_MASK;
            /* Set COMPx_CTRL INPSEL[2:0] bits */
            COMP->Cmp2.CTRL |= vpsel;
            break;
        case COMP3:
            /* Clear COMPx_CTRL INPSEL[2:0] bits */
            COMP->Cmp3.CTRL &= COMP_INPSEL_MASK;
            /* Set COMPx_CTRL INPSEL[2:0] bits */
            COMP->Cmp3.CTRL |= vpsel;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_InmSel_Config.
*\*\fun     Configures COMPx inmsel.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   vmsel :
*\*\             comp1 inm sel 
*\*\            - COMP1_INMSEL_VREF_VC1              
*\*\            - COMP1_INMSEL_PA4                   
*\*\            - COMP1_INMSEL_PA0                   
*\*\            - COMP1_INMSEL_PA5                   
*\*\            - COMP1_INMSEL_PB5                   
*\*\            - COMP1_INMSEL_FLOAT                 
*\*\            - COMP1_INMSEL_FLOAT                 
*\*\            - COMP1_INMSEL_FLOAT                            
*\*\             comp2 inm sel 
*\*\            - COMP2_INMSEL_VERF_VC2              
*\*\            - COMP2_INMSEL_PA2                   
*\*\            - COMP2_INMSEL_PA5                   
*\*\            - COMP2_INMSEL_PA6                   
*\*\            - COMP2_INMSEL_PB3                   
*\*\            - COMP2_INMSEL_PA4                   
*\*\            - COMP2_INMSEL_FLOAT                 
*\*\            - COMP2_INMSEL_FLOAT                          
*\*\             comp3 inm sel 
*\*\            - COMP3_INMSEL_VREF_VC3           
*\*\            - COMP3_INMSEL_PA3                 
*\*\            - COMP3_INMSEL_PB0                  
*\*\            - COMP3_INMSEL_PB2                
*\*\            - COMP3_INMSEL_PB14               
*\*\            - COMP3_INMSEL_FLOAT               
*\*\            - COMP3_INMSEL_FLOAT                
*\*\            - COMP3_INMSEL_FLOAT                               
*\*\return  none
**/
void COMP_InmSel_Config(COMPX COMPx, uint32_t vmsel)
{
    switch (COMPx)
    {
        case COMP1:
            /* Clear COMPx_CTRL INMSEL[2:0] bits */
            COMP->Cmp1.CTRL &= COMP_INMSEL_MASK;
            /* Set COMPx_CTRL INMSEL[2:0] bits */
            COMP->Cmp1.CTRL |= vmsel;
            break;
        case COMP2:
            /* Clear COMPx_CTRL INMSEL[2:0] bits */
            COMP->Cmp2.CTRL &= COMP_INMSEL_MASK;
            /* Set COMPx_CTRL INMSEL[2:0] bits */
            COMP->Cmp2.CTRL |= vmsel;
            break;
        case COMP3:
            /* Clear COMPx_CTRL INMSEL[2:0] bits */
            COMP->Cmp3.CTRL &= COMP_INMSEL_MASK;
            /* Set COMPx_CTRL INMSEL[2:0] bits */
            COMP->Cmp3.CTRL |= vmsel;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_Output_Trigger_Config.
*\*\fun     Configures which Timer input must be connected with the comparator output.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   outtrgsel :
*\*\             comp1 out trig 
*\*\            - COMP1_OUTSEL_TIM1_BKIN             
*\*\            - COMP1_OUTSEL_TIM1_OCREFCLEAR       
*\*\            - COMP1_OUTSEL_TIM1_IC1              
*\*\            - COMP1_OUTSEL_TIM2_IC1              
*\*\            - COMP1_OUTSEL_TIM2_OCREFCLEAR       
*\*\            - COMP1_OUTSEL_TIM3_IC1              
*\*\            - COMP1_OUTSEL_TIM3_OCREFCLEAR       
*\*\            - COMP1_OUTSEL_TIM4_OCREFCLEAR       
*\*\            - COMP1_OUTSEL_TIM5_IC1              
*\*\            - COMP1_OUTSEL_TIM8_IC1              
*\*\            - COMP1_OUTSEL_TIM8_OCREFCLEAR       
*\*\            - COMP1_OUTSEL_TIM8_BKIN             
*\*\            - COMP1_OUTSEL_TIM1_BKIN_TIM8_BKIN   
*\*\            - COMP1_OUTSEL_LPTIM_ETR                 
*\*\             comp2 out trig 
*\*\            - COMP2_OUTSEL_TIM1_BKIN             
*\*\            - COMP2_OUTSEL_TIM1_OCREFCLEAR       
*\*\            - COMP2_OUTSEL_TIM1_IC1              
*\*\            - COMP2_OUTSEL_TIM2_OCREFCLEAR       
*\*\            - COMP2_OUTSEL_TIM3_OCREFCLEAR       
*\*\            - COMP2_OUTSEL_TIM4_IC1              
*\*\            - COMP2_OUTSEL_TIM4_OCREFCLEAR       
*\*\            - COMP2_OUTSEL_TIM5_IC1              
*\*\            - COMP2_OUTSEL_TIM8_IC1              
*\*\            - COMP2_OUTSEL_TIM8_OCREFCLEAR       
*\*\            - COMP2_OUTSEL_TIM8_BKIN             
*\*\            - COMP2_OUTSEL_TIM1_BKIN_TIM8_BKIN   
*\*\            - COMP2_OUTSEL_LPTIM_ETR             
*\*\             comp3 out trig 
*\*\            - COMP3_OUTSEL_TIM1_BKIN             
*\*\            - COMP3_OUTSEL_TIM1_OCREFCLEAR       
*\*\            - COMP3_OUTSEL_TIM1_IC1              
*\*\            - COMP3_OUTSEL_TIM2_IC1              
*\*\            - COMP3_OUTSEL_TIM5_OCREFCLEAR       
*\*\            - COMP3_OUTSEL_TIM3_IC1              
*\*\            - COMP3_OUTSEL_TIM3_OCREFCLEAR       
*\*\            - COMP3_OUTSEL_TIM4_OCREFCLEAR       
*\*\            - COMP3_OUTSEL_TIM5_IC1              
*\*\            - COMP3_OUTSEL_TIM8_IC1              
*\*\            - COMP3_OUTSEL_TIM8_OCREFCLEAR       
*\*\            - COMP3_OUTSEL_TIM8_BKIN             
*\*\            - COMP3_OUTSEL_TIM1_BKIN_TIM8_BKIN   
*\*\            - COMP3_OUTSEL_LPTIM_ETR             
*\*\return  none
**/
void COMP_Output_Trigger_Config(COMPX COMPx, uint32_t outtrgsel)
{
    switch (COMPx)
    {
        case COMP1:
            /* Clear COMPx_CTRL OUTTRG[4:0] bits */
            COMP->Cmp1.CTRL &= COMP_OUTSEL_MASK;
            /* Set COMPx_CTRL OUTTRG[4:0] bits */ 
            COMP->Cmp1.CTRL |= outtrgsel;
            break;
        case COMP2:
            /* Clear COMPx_CTRL INMSEL[2:0] bits */
            /* Clear COMPx_CTRL OUTTRG[4:0] bits */
            COMP->Cmp2.CTRL &= COMP_OUTSEL_MASK;
            /* Set COMPx_CTRL OUTTRG[4:0] bits */ 
            COMP->Cmp2.CTRL |= outtrgsel;
            break;
        case COMP3:
            /* Clear COMPx_CTRL OUTTRG[4:0] bits */
            COMP->Cmp3.CTRL &= COMP_OUTSEL_MASK;
            /* Set COMPx_CTRL OUTTRG[4:0] bits */ 
            COMP->Cmp3.CTRL |= outtrgsel;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_ON.
*\*\fun     Enable COMP.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\return  none
**/
void COMP_ON(COMPX COMPx)
{
    switch (COMPx)
    {
        case COMP1:
            /* Set the COMPx_CTRL EN bit to wake up the COMPx from power down mode */
            COMP->Cmp1.CTRL |= COMP_ENABLE;
            break;
        case COMP2:
            /* Set the COMPx_CTRL EN bit to wake up the COMPx from power down mode */
            COMP->Cmp2.CTRL |= COMP_ENABLE;
            break;
        case COMP3:
            /* Set the COMPx_CTRL EN bit to wake up the COMPx from power down mode */
            COMP->Cmp3.CTRL |= COMP_ENABLE;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_OFF.
*\*\fun     Disable COMP.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\return  none
**/
void COMP_OFF(COMPX COMPx)
{
    switch (COMPx)
    {
        case COMP1:
            /* Clear the COMPx_CTRL EN bit, The COMPx go to power down mode */
            COMP->Cmp1.CTRL &= COMP_DISABLE;
            break;
        case COMP2:
            /* Clear the COMPx_CTRL EN bit, The COMPx go to power down mode */
            COMP->Cmp2.CTRL &= COMP_DISABLE;
            break;
        case COMP3:
            /* Clear the COMPx_CTRL EN bit, The COMPx go to power down mode */
            COMP->Cmp3.CTRL &= COMP_DISABLE;
            break;
        default:
            break;
    }
}

/**
*\*\name    COMP_Lock_Config.
*\*\fun     Configures which COMPx will be Locked.
*\*\param   Lock :
*\*\          - COMP1_LOCK_MSK
*\*\          - COMP2_LOCK_MSK
*\*\          - COMP3_LOCK_MSK
*\*\return  none
**/
void COMP_Lock_Config(uint32_t lock)
{
    COMP->LOCK |= lock;
}

/**
*\*\name    COMP_LowPower_Clock_Select.
*\*\fun     Configures comp.
*\*\param   lpcksel :
*\*\          - COMP_NORMAL_MODE
*\*\          - COMP_LOWPOWER_MODE
*\*\return  none
**/
void COMP_LowPower_Clock_Select(uint32_t lpcksel)
{
    COMP->LPCKSEL &= COMP_LPCKSEL_MSK;	
    COMP->LPCKSEL |= lpcksel;
}

/**
*\*\name    COMP_Interrupt_Enable.
*\*\fun     Configures COMPx interrupt enable.
*\*\param   IntEn :
*\*\          - COMP1_INTEN
*\*\          - COMP2_INTEN
*\*\          - COMP3_INTEN
*\*\return  none
**/
void COMP_Interrupt_Enable(uint32_t inten)
{
    COMP->INTEN |= inten;
}

/**
*\*\name    COMP_Interrupt_Disable.
*\*\fun     Configures COMPx interrupt disable.
*\*\param   IntEn :
*\*\          - COMP1_INTEN
*\*\          - COMP2_INTEN
*\*\          - COMP3_INTEN
*\*\return  none
**/
void COMP_Interrupt_Disable(uint32_t inten)
{
    COMP->INTEN &= ~inten;
}

/**
*\*\name    COMP_Interrupt_Status_Get.
*\*\fun     Get COMPx interrupt Status.
*\*\return 
*\*\          - COMP1_INTSTS
*\*\          - COMP2_INTSTS
*\*\          - COMP3_INTSTS
**/
uint8_t COMP_Interrupt_Status_Get(void)
{
    return COMP->INTSTS;
}

/**
*\*\name    COMP_Reference_Voltage_Config.
*\*\fun     Configures the COMP reference voltage. 
*\*\param   Vv3Trim :
*\*\          - Value can be set from 0 to 63.
*\*\param   Vv3En :
*\*\          - false
*\*\          - true
*\*\param   Vv2Trim :
*\*\          - Value can be set from 0 to 63.
*\*\param   Vv2En :
*\*\          - false
*\*\          - true
*\*\param   Vv1Trim :
*\*\           - Value can be set from 0 to 63.     
*\*\param   Vv1En :
*\*\          - false
*\*\          - true
*\*\return  none
**/
void COMP_Voltage_Reference_Config(uint8_t vv3trim, bool vv3en, uint8_t vv2trim, bool vv2en, uint8_t vv1trim, bool vv1en)
{
    __IO uint32_t temp_value = 0;

    SetBitMsk(temp_value, vv3trim << REG_BIT15_OFFSET, COMP_VREFSCL_VV3TRM_MSK);
    SetBitMsk(temp_value, vv3en << REG_BIT14_OFFSET, COMP_VREFSCL_VV3EN_MSK);
    SetBitMsk(temp_value, vv2trim << REG_BIT8_OFFSET, COMP_VREFSCL_VV2TRM_MSK);
    SetBitMsk(temp_value, vv2en << REG_BIT7_OFFSET, COMP_VREFSCL_VV2EN_MSK);
    SetBitMsk(temp_value, vv1trim << REG_BIT1_OFFSET, COMP_VREFSCL_VV1TRM_MSK);
    SetBitMsk(temp_value, vv1en, COMP_VREFSCL_VV1EN_MSK);

    COMP->VREFSCL = temp_value;
}

/**
*\*\name    COMP_Window_Mode_Enable.
*\*\fun     Enable Comp Window Mode (input comparison of COMP1&2 by PA1).
*\*\return  none
**/
void COMP_Window_Mode_Enable(void)
{
    COMP->WINMODE = COMP_CMP12MD_ENABLE;
}

/**
*\*\name    COMP_Window_Mode_Disable.
*\*\fun     Disable Comp Window Mode (input comparison of COMP1&2 by PA1).
*\*\return  none
**/
void COMP_Window_Mode_Disable(void)
{
    COMP->WINMODE = COMP_CMP12MD_DISABLE;
}

/**
*\*\name    COMP2_Output_Xor_Enable.
*\*\fun     Enable the XOR output(comparison of COMP1&2).
*\*\return  none
**/
void COMP2_Output_Xor_Enable(void)
{
    COMP->CMP2OSEL = COMP_CMP2XO_ENABLE;
}

/**
*\*\name    COMP2_Output_Xor_Disable.
*\*\fun     Disable the XOR output(comparison of COMP1&2).
*\*\return  none
**/
void COMP2_Output_Xor_Disable(void)
{
    COMP->CMP2OSEL = COMP_CMP2XO_DISABLE;
}
/**
*\*\name    COMP_Output_Status_Get.
*\*\fun     Get COMPx Output Status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus COMP_Output_Status_Get(COMPX COMPx)
{
    if(COMPx == COMP1)
    {
        return (COMP->Cmp1.CTRL & COMP_OUT_MASK) ? SET : RESET;
    }
    else if(COMPx == COMP2)
    {
        return (COMP->Cmp2.CTRL & COMP_OUT_MASK) ? SET : RESET;
    }
    else
    {
        return (COMP->Cmp3.CTRL & COMP_OUT_MASK) ? SET : RESET;
    }
}
/**
*\*\name    COMP_Interrupt_Status_OneComp_Get.
*\*\fun     Get COMPx Output Status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus COMP_Interrupt_Status_OneComp_Get(COMPX COMPx)
{
    return (COMP->INTSTS & (REG_BIT1_OFFSET << COMPx)) ? SET : RESET;
}
/**
*\*\name    COMP_Interrupt_Status_OneComp_Clear.
*\*\fun     Clear COMPx Output Status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\return  none
**/
void COMP_Interrupt_Status_OneComp_Clear(COMPX COMPx)
{
    COMP->INTSTS = (REG_BIT1_OFFSET << COMPx);
}


/**
*\*\name    COMP_Filter_Control_Config.
*\*\fun     Configures the COMP filter control value.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   sw :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\param   threshnum :
*\*\          - Threshold Value need > SampWindow/2.      
*\*\param   sampwindow :
*\*\          -  Value can be set from 0 to 31.
*\*\return  none
**/
void COMP_Filter_Control_Config(COMPX COMPx , uint32_t sw, uint8_t threshold , uint8_t sampwindow)
{
    COMP_Filter_SampWindow_Config(COMPx, sampwindow);
    COMP_Filter_Threshold_Config(COMPx, threshold);
    if(sw == ENABLE)
    {
        COMP_Filter_Enable(COMPx);
    }
    else
    {
        COMP_Filter_Disable(COMPx);
    }
}

/**
*\*\name    COMP_Initializes.
*\*\fun     Initializes the COMPx according to COMP_initstruct.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\param   COMP_initstruct :
*\*\          - Blking
*\*\            - COMP_BLANKING_NO
*\*\            - COMP_BLANKING_TIM1_OC5
*\*\            - COMP_BLANKING_TIM8_OC5
*\*\          - Hyst
*\*\            - COMP_HYST_NO   
*\*\            - COMP_HYST_LOW    
*\*\            - COMP_HYST_MID    
*\*\            - COMP_HYST_HIGH   
*\*\          - PolRev
*\*\            - COMP_OUTPOL_FLIP             
*\*\            - COMP_OUTPOL_NFLIP              
*\*\          - OutSel  
*\*\             comp1 out trig 
*\*\            - COMP1_OUTSEL_TIM1_BKIN             
*\*\            - COMP1_OUTSEL_TIM1_OCREFCLEAR       
*\*\            - COMP1_OUTSEL_TIM1_IC1              
*\*\            - COMP1_OUTSEL_TIM2_IC1              
*\*\            - COMP1_OUTSEL_TIM2_OCREFCLEAR       
*\*\            - COMP1_OUTSEL_TIM3_IC1              
*\*\            - COMP1_OUTSEL_TIM3_OCREFCLEAR       
*\*\            - COMP1_OUTSEL_TIM4_OCREFCLEAR       
*\*\            - COMP1_OUTSEL_TIM5_IC1              
*\*\            - COMP1_OUTSEL_TIM8_IC1              
*\*\            - COMP1_OUTSEL_TIM8_OCREFCLEAR       
*\*\            - COMP1_OUTSEL_TIM8_BKIN             
*\*\            - COMP1_OUTSEL_TIM1_BKIN_TIM8_BKIN   
*\*\            - COMP1_OUTSEL_LPTIM_ETR                 
*\*\             comp2 out trig 
*\*\            - COMP2_OUTSEL_TIM1_BKIN             
*\*\            - COMP2_OUTSEL_TIM1_OCREFCLEAR       
*\*\            - COMP2_OUTSEL_TIM1_IC1              
*\*\            - COMP2_OUTSEL_TIM2_OCREFCLEAR       
*\*\            - COMP2_OUTSEL_TIM3_OCREFCLEAR       
*\*\            - COMP2_OUTSEL_TIM4_IC1              
*\*\            - COMP2_OUTSEL_TIM4_OCREFCLEAR       
*\*\            - COMP2_OUTSEL_TIM5_IC1              
*\*\            - COMP2_OUTSEL_TIM8_IC1              
*\*\            - COMP2_OUTSEL_TIM8_OCREFCLEAR       
*\*\            - COMP2_OUTSEL_TIM8_BKIN             
*\*\            - COMP2_OUTSEL_TIM1_BKIN_TIM8_BKIN   
*\*\            - COMP2_OUTSEL_LPTIM_ETR             
*\*\             comp3 out trig 
*\*\            - COMP3_OUTSEL_TIM1_BKIN             
*\*\            - COMP3_OUTSEL_TIM1_OCREFCLEAR       
*\*\            - COMP3_OUTSEL_TIM1_IC1              
*\*\            - COMP3_OUTSEL_TIM2_IC1              
*\*\            - COMP3_OUTSEL_TIM5_OCREFCLEAR       
*\*\            - COMP3_OUTSEL_TIM3_IC1              
*\*\            - COMP3_OUTSEL_TIM3_OCREFCLEAR       
*\*\            - COMP3_OUTSEL_TIM4_OCREFCLEAR       
*\*\            - COMP3_OUTSEL_TIM5_IC1              
*\*\            - COMP3_OUTSEL_TIM8_IC1              
*\*\            - COMP3_OUTSEL_TIM8_OCREFCLEAR       
*\*\            - COMP3_OUTSEL_TIM8_BKIN             
*\*\            - COMP3_OUTSEL_TIM1_BKIN_TIM8_BKIN   
*\*\            - COMP3_OUTSEL_LPTIM_ETR              
*\*\          - InpSel                
*\*\             comp1 inp sel 
*\*\            - COMP1_INPSEL_PA0                   
*\*\            - COMP1_INPSEL_PA2                   
*\*\            - COMP1_INPSEL_PA12                  
*\*\            - COMP1_INPSEL_PB3                   
*\*\            - COMP1_INPSEL_PB4                   
*\*\            - COMP1_INPSEL_PB10                  
*\*\            - COMP1_INPSEL_PA1                   
*\*\            - COMP1_INPSEL_FLOAT              
*\*\             comp2 inp sel 
*\*\            - COMP2_INPSEL_PA1                   
*\*\            - COMP2_INPSEL_PA3                  
*\*\            - COMP2_INPSEL_PA6                  
*\*\            - COMP2_INPSEL_PA7                  
*\*\            - COMP2_INPSEL_PA11                
*\*\            - COMP2_INPSEL_PA15                
*\*\            - COMP2_INPSEL_PB7                 
*\*\            - COMP2_INPSEL_FLOAT                               
*\*\             comp3 inp sel 
*\*\            - COMP3_INPSEL_PA0               
*\*\            - COMP3_INPSEL_PB1                   
*\*\            - COMP3_INPSEL_PB11                  
*\*\            - COMP3_INPSEL_PB15                  
*\*\            - COMP3_INPSEL_PB3                   
*\*\            - COMP3_INPSEL_PB5                   
*\*\            - COMP3_INPSEL_FLOAT                 
*\*\            - COMP3_INPSEL_FLOAT                                        
*\*\          - InmSel
*\*\             comp1 inm sel 
*\*\            - COMP1_INMSEL_VREF_VC1              
*\*\            - COMP1_INMSEL_PA4                   
*\*\            - COMP1_INMSEL_PA0                   
*\*\            - COMP1_INMSEL_PA5                   
*\*\            - COMP1_INMSEL_PB5                   
*\*\            - COMP1_INMSEL_FLOAT                 
*\*\            - COMP1_INMSEL_FLOAT                 
*\*\            - COMP1_INMSEL_FLOAT                            
*\*\             comp2 inm sel 
*\*\            - COMP2_INMSEL_VERF_VC2              
*\*\            - COMP2_INMSEL_PA2                   
*\*\            - COMP2_INMSEL_PA5                   
*\*\            - COMP2_INMSEL_PA6                   
*\*\            - COMP2_INMSEL_PB3                   
*\*\            - COMP2_INMSEL_PA4                   
*\*\            - COMP2_INMSEL_FLOAT                 
*\*\            - COMP2_INMSEL_FLOAT                          
*\*\             comp3 inm sel 
*\*\            - COMP3_INMSEL_VREF_VC3           
*\*\            - COMP3_INMSEL_PA3                 
*\*\            - COMP3_INMSEL_PB0                  
*\*\            - COMP3_INMSEL_PB2                
*\*\            - COMP3_INMSEL_PB14               
*\*\            - COMP3_INMSEL_FLOAT               
*\*\            - COMP3_INMSEL_FLOAT                
*\*\            - COMP3_INMSEL_FLOAT                             
*\*\          - En
*\*\            - ENABLE
*\*\            - DISABLE
*\*\          - SampWindow
*\*\            - SampWindow Value ranges from 0~31. 
*\*\          - Threshold
*\*\            - Threshold Value need > SampWindow/2.
*\*\          - FilterEn
*\*\            - ENABLE
*\*\            - DISABLE
*\*\          - ClkPsc
*\*\            - ClkPsc Value ranges from 0~32767. 
*\*\return  none
**/
void COMP_Initializes(COMPX COMPx, COMP_InitType* COMP_initstruct)
{
    /** filter configures **/
    COMP_Filter_SampWindow_Config(COMPx, COMP_initstruct->SampWindow);
    COMP_Filter_Threshold_Config(COMPx, COMP_initstruct->Threshold);
    if(COMP_initstruct->FilterEn == ENABLE)
    {
        COMP_Filter_Enable(COMPx);
    }   
    else
    {
        COMP_Filter_Disable(COMPx);
    }
    /** filter clock Prescale configures **/
    COMP_Filter_Clock_Prescale_Config(COMPx, COMP_initstruct->ClkPsc);
    
    /** ctrl configures**/
    COMP_Blking_Soucre_Config(COMPx, COMP_initstruct->Blking);
    COMP_Hysteresis_Level_Config(COMPx, COMP_initstruct->Hyst);
    COMP_Output_Polarity_Config(COMPx, COMP_initstruct->PolRev);
    COMP_InpSel_Config(COMPx, COMP_initstruct->InpSel);
    COMP_InmSel_Config(COMPx, COMP_initstruct->InmSel);
    COMP_Output_Trigger_Config(COMPx, COMP_initstruct->OutSel);

    /** comp enable or disable configures*/
    if (COMP_initstruct->En == ENABLE)
        COMP_ON(COMPx);
    else
        COMP_OFF(COMPx);
}

