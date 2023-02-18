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
*\*\file n32g430_adc.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#include "n32g430_adc.h"
#include "n32g430_rcc.h"

/** ADC Private Defines**/

/** API interface function definition**/
uint32_t vrefint_value; 
typedef enum
{
    CMD_CR_SUCCESS  = 0x00,
    CMD_CR_FAILED   = 0x01,
}CMD_RETURN_CR;

CMD_RETURN_CR (*Program_NVR)(uint32_t addr, uint32_t  data) = (CMD_RETURN_CR (*)(uint32_t ,uint32_t ))0x1FFF01D1;
CMD_RETURN_CR     (*Get_NVR)(uint32_t addr, uint32_t* data) = (CMD_RETURN_CR (*)(uint32_t ,uint32_t*))0x1FFF02A5;

/**
*\*\name    ADC_Vrefint_Get.
*\*\fun     Return the Vrefint value of NVR.
*\*\return  vrefint_value
**/
uint32_t ADC_Vrefint_Get(void)
{
		Get_NVR(0x1FFFF268, &vrefint_value);
		return vrefint_value;
}

/** ADC Driving Functions Declaration**/

/**
*\*\name    ADC_Reset.
*\*\fun     Reset the ADC registers.
*\*\return  none
**/
void ADC_Reset(void)
{
    RCC_AHB_Peripheral_Reset(RCC_AHB_PERIPH_ADC);
}

/**
*\*\name    ADC_Multichannels_Enable.
*\*\fun     Configures the ADC according conversion is performed in
*\*\        Scan (multichannels) mode.
*\*\return  none
**/
void ADC_Multichannels_Enable(void)
{
    /* Set ADC_CTRL1 SCANMD bit */
    ADC->CTRL1 |= ADC_MULTCH_ENABLE;
}

/**
*\*\name    ADC_Multichannels_Disable.
*\*\fun     Configures the ADC according conversion is performed in
*\*\        Single (one channel) mode.
*\*\return  none
**/
void ADC_Multichannels_Disable(void)
{
    /* Clear ADC_CTRL1 SCANMD bit */
    ADC->CTRL1 &= ADC_MULTCH_DISABLE;
}

/**
*\*\name    ADC_Continue_Conversion_Enable.
*\*\fun     Configures the ADC according conversion is performed in
*\*\        Continuous mode.
*\*\return  none
**/
void ADC_Continue_Conversion_Enable(void)
{
    /* Set ADC_CTRL2 CTU bit */
    ADC->CTRL2 |= ADC_CTU_ENABLE;
}

/**
*\*\name    ADC_Continue_Conversion_Disable.
*\*\fun     Configures the ADC according conversion is performed in
*\*\        Single mode.
*\*\return  none
**/
void ADC_Continue_Conversion_Disable(void)
{
    /* Clear ADC_CTRL2 CTU bit */
    ADC->CTRL2 &= ADC_CTU_DISABLE;
}

/**
*\*\name    ADC_Regular_Group_External_Trigger_Source_Config.
*\*\fun     Configures the ADC external trigger source for regular group channels.
*\*\param   external_trigger_sources :
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T1_CC1                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T1_CC2                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T1_CC3                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T2_CC2                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T3_TRGO               
*\*\          - ADC_EXT_TRIGCONV_REGULAR_T4_CC4                
*\*\          - ADC_EXT_TRIGCONV_REGULAR_EXT_INT11_TIM8_TRGO   
*\*\          - ADC_EXT_TRIGCONV_REGULAR_SWSTRRCH              
*\*\return  none
**/
void ADC_Regular_Group_External_Trigger_Source_Config(uint32_t external_trigger_sources)
{
    /* Clear ADC_CTRL2 EXTRSEL[2:0] bit */
    ADC->CTRL2 &= ADC_EXT_TRIGCONV_REGULAR_MASK;
    /* Set ADC_CTRL2 EXTJSEL[2:0] bit */
    ADC->CTRL2 |= external_trigger_sources;
}

/**
*\*\name    ADC_Data_Alignment_Config.
*\*\fun     Configures the ADC data alignment is left or right.
*\*\param   data_alignment :
*\*\          - ADC_DAT_ALIGN_R
*\*\          - ADC_DAT_ALIGN_L
*\*\return  none
**/
void ADC_Data_Alignment_Config(uint32_t data_alignment)
{
    /* Clear ADC_CTRL2 ALIG bit */
    ADC->CTRL2 &= ADC_ALIG_MASK;
    /* Set ADC_CTRL2 ALIG bit */
    ADC->CTRL2 |= data_alignment;
}

/**
*\*\name    ADC_Regular_Channels_Number_Config.
*\*\fun     Configures the ADC total number of conversion channels.
*\*\param   channels_number :
*\*\          - ADC_REGULAR_LEN_1
*\*\          - ADC_REGULAR_LEN_2
*\*\          - ADC_REGULAR_LEN_3
*\*\          - ADC_REGULAR_LEN_4
*\*\          - ADC_REGULAR_LEN_5
*\*\          - ADC_REGULAR_LEN_6
*\*\          - ADC_REGULAR_LEN_7
*\*\          - ADC_REGULAR_LEN_8
*\*\          - ADC_REGULAR_LEN_9
*\*\          - ADC_REGULAR_LEN_10
*\*\          - ADC_REGULAR_LEN_11
*\*\          - ADC_REGULAR_LEN_12
*\*\          - ADC_REGULAR_LEN_13
*\*\          - ADC_REGULAR_LEN_14
*\*\          - ADC_REGULAR_LEN_15
*\*\          - ADC_REGULAR_LEN_16
*\*\return  none
**/
void ADC_Regular_Channels_Number_Config(uint32_t channels_number)
{
    /* Clear ADC_RSEQ1 LEN[3:0] bit */
    ADC->RSEQ1 &= ADC_REGULAR_LEN_MSAK;
    /* Set ADC_RSEQ1 LEN[3:0] bit */
    ADC->RSEQ1 |= channels_number;
}

/**
*\*\name    ADC_Initializes.
*\*\fun     Initializes the ADC according to ADC_initstruct.
*\*\param   ADC_initstruct :
*\*\          - MultiChEn
*\*\            - DISABLE
*\*\            - ENABLE
*\*\          - ContinueConvEn
*\*\            - DISABLE
*\*\            - ENABLE
*\*\          - ExtTrigSelect
*\*\            - ADC_EXT_TRIGCONV_REGULAR_T1_CC1                
*\*\            - ADC_EXT_TRIGCONV_REGULAR_T1_CC2                
*\*\            - ADC_EXT_TRIGCONV_REGULAR_T1_CC3                
*\*\            - ADC_EXT_TRIGCONV_REGULAR_T2_CC2                
*\*\            - ADC_EXT_TRIGCONV_REGULAR_T3_TRGO               
*\*\            - ADC_EXT_TRIGCONV_REGULAR_T4_CC4                
*\*\            - ADC_EXT_TRIGCONV_REGULAR_EXT_INT11_TIM8_TRGO   
*\*\            - ADC_EXT_TRIGCONV_REGULAR_SWSTRRCH              
*\*\          - DatAlign
*\*\            - ADC_DAT_ALIGN_R
*\*\            - ADC_DAT_ALIGN_L
*\*\          - ChsNumber
*\*\            - ADC_REGULAR_LEN_1
*\*\            - ADC_REGULAR_LEN_2
*\*\            - ADC_REGULAR_LEN_3
*\*\            - ADC_REGULAR_LEN_4
*\*\            - ADC_REGULAR_LEN_5
*\*\            - ADC_REGULAR_LEN_6
*\*\            - ADC_REGULAR_LEN_7
*\*\            - ADC_REGULAR_LEN_8
*\*\            - ADC_REGULAR_LEN_9
*\*\            - ADC_REGULAR_LEN_10
*\*\            - ADC_REGULAR_LEN_11
*\*\            - ADC_REGULAR_LEN_12
*\*\            - ADC_REGULAR_LEN_13
*\*\            - ADC_REGULAR_LEN_14
*\*\            - ADC_REGULAR_LEN_15
*\*\            - ADC_REGULAR_LEN_16
*\*\return  none
**/
void ADC_Initializes(ADC_InitType* ADC_initstruct)
{
    if(ADC_initstruct->MultiChEn)
    {
        ADC_Multichannels_Enable();
    }
    else
    {
        ADC_Multichannels_Disable();
    }

    if(ADC_initstruct->ContinueConvEn)
    {
        ADC_Continue_Conversion_Enable();
    }
    else
    {
        ADC_Continue_Conversion_Disable();
    }

    ADC_Regular_Group_External_Trigger_Source_Config(ADC_initstruct->ExtTrigSelect);
    ADC_Data_Alignment_Config(ADC_initstruct->DatAlign);
    ADC_Regular_Channels_Number_Config(ADC_initstruct->ChsNumber);
}

/**
*\*\name    ADC_Initializes_Structure.
*\*\fun     Fills each ADC_initstruct member with its default value.
*\*\param   ADC_initstruct :
*\*\          - MultiChEn
*\*\          - ContinueConvEn
*\*\          - ExtTrigSelect
*\*\          - DatAlign
*\*\          - ChsNumber
*\*\return  none
**/
void ADC_Initializes_Structure(ADC_InitType* ADC_initstruct)
{
    /* Reset ADC init structure parameters values */
    /* initialize the MultiChEn member */
    ADC_initstruct->MultiChEn      = DISABLE;
    /* Initialize the ContinueConvEn member */
    ADC_initstruct->ContinueConvEn = DISABLE;
    /* Initialize the ExtTrigSelect member */
    ADC_initstruct->ExtTrigSelect  = ADC_EXT_TRIGCONV_REGULAR_T1_CC1;
    /* Initialize the DatAlign member */
    ADC_initstruct->DatAlign       = ADC_DAT_ALIGN_R;
    /* Initialize the ChsNumber member */
    ADC_initstruct->ChsNumber      = ADC_REGULAR_LEN_1;
}

/**
*\*\name    ADC_ON.
*\*\fun     ADC turn ON.
*\*\return  none
**/
void ADC_ON(void)
{
    /* Set the ADC_CTRL2 ON bit to wake up the ADC from power down mode */
    ADC->CTRL2 |= ADC_TURN_ON;
}

/**
*\*\name    ADC_OFF.
*\*\fun     ADC turn OFF.
*\*\return  none
**/
void ADC_OFF(void)
{
    /* Clear the ADC_CTRL2 ON bit, then ADC go to power down mode */
    ADC->CTRL2 &= ADC_TURN_OFF;
}

/**
*\*\name    ADC_DMA_Transfer_Enable.
*\*\fun     Enable ADC DMA transfer.
*\*\return  none
**/
void ADC_DMA_Transfer_Enable(void)
{
    /* Set the ADC_CTRL2 ENDMA bit to enable DMA transfer */
    ADC->CTRL2 |= ADC_DMA_ENABLE;
}

/**
*\*\name    ADC_DMA_Transfer_Disable.
*\*\fun     Disable ADC DMA transfer.
*\*\return  none
**/
void ADC_DMA_Transfer_Disable(void)
{
    /* Clean the ADC_CTRL2 ENDMA bit to disable DMA transfer */
    ADC->CTRL2 &= ADC_DMA_DISABLE;
}

/**
*\*\name    ADC_Interrupts_Enable.
*\*\fun     Enable ADC interrupts.
*\*\param   adc_interrupt :
*\*\          - ADC_INT_ENDC      ADC_CTRL1
*\*\          - ADC_INT_AWD       ADC_CTRL1
*\*\          - ADC_INT_JENDC     ADC_CTRL1
*\*\          - ADC_INT_ENDCA     ADC_CTRL3
*\*\          - ADC_INT_JENDCA    ADC_CTRL3
*\*\return  none
**/
void ADC_Interrupts_Enable(uint32_t adc_interrupt)
{
    if(adc_interrupt <= ADC_INT_JENDC)
    {
        /* Set the ADC_CTRL1 ENDCIEN/AWDGIEN/JENDCIEN bit to enable ADC interrupts */
        ADC->CTRL1 |= adc_interrupt;
    }
    else
    {
        /* Set the ADC_CTRL3 ENDCAIEN/JENDCAIEN bit to enable ADC interrupts */
        ADC->CTRL3 |= adc_interrupt;
    }
}

/**
*\*\name    ADC_Interrupts_Disable.
*\*\fun     Disable ADC interrupts.
*\*\param   adc_interrupt :
*\*\          - ADC_INT_ENDC      ADC_CTRL1
*\*\          - ADC_INT_AWD       ADC_CTRL1
*\*\          - ADC_INT_JENDC     ADC_CTRL1
*\*\          - ADC_INT_ENDCA     ADC_CTRL3   
*\*\          - ADC_INT_JENDCA    ADC_CTRL3
*\*\return  none
**/
void ADC_Interrupts_Disable(uint32_t adc_interrupt)
{
    if(adc_interrupt <= ADC_INT_JENDC)
    {
        /* Clean the ADC_CTRL1 ENDCIEN/AWDGIEN/JENDCIEN bit to disable ADC interrupts */
        ADC->CTRL1 &= (~adc_interrupt);
    }
    else
    {
        /* Clean the ADC_CTRL3 ENDCAIEN/JENDCAIEN bikt to disable ADC interrupts */
        ADC->CTRL3 &= (~adc_interrupt);
    }
}

/**
*\*\name    ADC_Calibration_Operation.
*\*\fun     ADC calibration operation.
*\*\param   calibration_operation :
*\*\          - ADC_CALIBRATION_ENABLE
*\*\          - ADC_CALIBRATION_STS
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus ADC_Calibration_Operation(uint32_t calibration_operation)
{
    if(calibration_operation == ADC_CALIBRATION_ENABLE)
    {
        /* ADC calibration Enable */
        if(ADC->CALFACT == 0)
        {
            ADC->CTRL2 |= ADC_CTRL2_ENCAL;
        }
    }
    else if(calibration_operation == ADC_CALIBRATION_STS)
    {
        /* Get ADC_CTRL2 CAL bit */
        if ((ADC->CTRL2 & ADC_CTRL2_ENCAL) != (uint32_t)RESET)
        {
            if(ADC->CALFACT != 0)
            {
                return RESET;
            }
            else
            {
                return SET;
            }
        }
        else
        {
            return RESET;
        }
        
        
    }
    return RESET;
}

/**
*\*\name    ADC_Regular_Channels_Software_Conversion_Operation.
*\*\fun     ADC regular channels software conversion operation.
*\*\param   conversion_operation :
*\*\          - ADC_EXTRTRIG_SWSTRRCH_ENABLE
*\*\          - ADC_EXTRTRIG_SWSTRRCH_DISABLE
*\*\          - ADC_EXTRTRIG_SWSTRRCH_GET_STS
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus ADC_Regular_Channels_Software_Conversion_Operation(uint32_t conversion_operation)
{
    if(conversion_operation == ADC_EXTRTRIG_SWSTRRCH_ENABLE)
    {
        /* Enable the ADC external trigger conversion mode for regular channels */
        ADC->CTRL2 |= conversion_operation;
    }
    else if(conversion_operation == ADC_EXTRTRIG_SWSTRRCH_DISABLE)
    {
        /* Disable the ADC external trigger conversion mode for regular channels */
        ADC->CTRL2 &= conversion_operation;
    }
    else if(conversion_operation == ADC_EXTRTRIG_SWSTRRCH_GET_STS)
    {
        /* Get ADC_CTRL2 SWSTRRCH bit */
        if ((ADC->CTRL2 & conversion_operation) != (uint32_t)RESET)
        {
            return SET;
        }
        else
        {
            return RESET;
        }
    }
    return RESET;
}

/**
*\*\name    ADC_Discontinuous_Mode_Channel_Count_Config.
*\*\fun     Configures ADC discontinuous mode channel count .
*\*\param   channel_count :
*\*\          - ADC_CHANNEL_COUNT_1
*\*\          - ADC_CHANNEL_COUNT_2
*\*\          - ADC_CHANNEL_COUNT_3
*\*\          - ADC_CHANNEL_COUNT_4
*\*\          - ADC_CHANNEL_COUNT_5
*\*\          - ADC_CHANNEL_COUNT_6
*\*\          - ADC_CHANNEL_COUNT_7
*\*\          - ADC_CHANNEL_COUNT_8
*\*\return  none
**/
void ADC_Discontinuous_Mode_Channel_Count_Config(uint32_t channel_count)
{
    /* Clear ADC_CTRL1 DCTU[2:0] */
    ADC->CTRL1 &= ADC_CHANNEL_COUNT_MASK;
    /* Set ADC_CTRL1 DCTU[2:0] */
    ADC->CTRL1 |= channel_count;
}

/**
*\*\name    ADC_Discontinuous_Mode_Config.
*\*\fun     Configures ADC discontinuous mode on regular or injected group channels.
*\*\param   group_operation :
*\*\          - ADC_DISCMODE_REGULAR_ENABLE
*\*\          - ADC_DISCMODE_REGULAR_DISABLE
*\*\          - ADC_DISCMODE_INJECTED_ENABLE
*\*\          - ADC_DISCMODE_INJECTED_DISABLE
*\*\return  none
**/
void ADC_Discontinuous_Mode_Config(uint32_t group_operation)
{
    if(group_operation == ADC_DISCMODE_REGULAR_ENABLE)
    {
        /* Enables the discontinuous mode on regular group channels */
        ADC->CTRL1 |= group_operation;
    }
    else if(group_operation == ADC_DISCMODE_REGULAR_DISABLE)
    {
        /* Disables the discontinuous mode on regular group channels */
        ADC->CTRL1 &= group_operation;
    }
    else if(group_operation == ADC_DISCMODE_INJECTED_ENABLE)
    {
        /* Enables the discontinuous mode on injected group channels */
        ADC->CTRL1 |= group_operation;
    }
    else if(group_operation == ADC_DISCMODE_INJECTED_DISABLE)
    {
        /* Disables the discontinuous mode on injected group channels */
        ADC->CTRL1 &= group_operation;
    }
}

/**
*\*\name    ADC_Channel_Sample_Time_Config.
*\*\fun     Configures ADC channel sample time.
*\*\param   channel :
*\*\          - ADC_CH_0
*\*\          - ADC_CH_1
*\*\          - ADC_CH_2
*\*\          - ADC_CH_3
*\*\          - ADC_CH_4
*\*\          - ADC_CH_5
*\*\          - ADC_CH_6
*\*\          - ADC_CH_7
*\*\          - ADC_CH_8
*\*\          - ADC_CH_9
*\*\          - ADC_CH_10
*\*\          - ADC_CH_11
*\*\          - ADC_CH_12
*\*\          - ADC_CH_13
*\*\          - ADC_CH_14
*\*\          - ADC_CH_15
*\*\          - ADC_CH_16
*\*\          - ADC_CH_17
*\*\          - ADC_CH_18
*\*\param   sample_time :
*\*\          - ADC_SAMP_TIME_1CYCLES5
*\*\          - ADC_SAMP_TIME_7CYCLES5
*\*\          - ADC_SAMP_TIME_13CYCLES5
*\*\          - ADC_SAMP_TIME_28CYCLES5
*\*\          - ADC_SAMP_TIME_41CYCLES5
*\*\          - ADC_SAMP_TIME_55CYCLES5
*\*\          - ADC_SAMP_TIME_71CYCLES5
*\*\          - ADC_SAMP_TIME_239CYCLES5
*\*\return  none
**/
void ADC_Channel_Sample_Time_Config(uint8_t channel, uint8_t sample_time)
{
    uint32_t temp_value = 0;
    
    /* ADC_Channel include in ADC_Channel_[0..9] */
    if(channel <= ADC_CH_9)
    {
        temp_value = channel;
        ADC->SAMPT2 &= ADC_SAMP_TIME_MASK(temp_value);
        ADC->SAMPT2 |= (uint32_t)(sample_time << temp_value * ADC_SAMP_TIME_UNIT_OFFSET);
    }
    /* ADC_Channel include in ADC_Channel_[10..17] */
    else if(channel <= ADC_CH_17)
    {
        temp_value = channel - ADC_CH_10;
        ADC->SAMPT1 &= ADC_SAMP_TIME_MASK(temp_value);
        ADC->SAMPT1 |= (uint32_t)(sample_time << temp_value * ADC_SAMP_TIME_UNIT_OFFSET);
    }
    /* ADC_Channel include in ADC_Channel_18 */
    else
    {
        ADC->SAMPT3 &= ADC_SAMP_TIME_MASK(temp_value);
        ADC->SAMPT3 |= (uint32_t)sample_time;
    }
}

/**
*\*\name    ADC_Regular_Sequence_Conversion_Number_Config.
*\*\fun     Configures ADC channel conversion number in regular sequence.
*\*\param   channel :
*\*\          - ADC_CH_0
*\*\          - ADC_CH_1
*\*\          - ADC_CH_2
*\*\          - ADC_CH_3
*\*\          - ADC_CH_4
*\*\          - ADC_CH_5
*\*\          - ADC_CH_6
*\*\          - ADC_CH_7
*\*\          - ADC_CH_8
*\*\          - ADC_CH_9
*\*\          - ADC_CH_10
*\*\          - ADC_CH_11
*\*\          - ADC_CH_12
*\*\          - ADC_CH_13
*\*\          - ADC_CH_14
*\*\          - ADC_CH_15
*\*\          - ADC_CH_16
*\*\          - ADC_CH_17
*\*\          - ADC_CH_18
*\*\param   number :
*\*\          - ADC_REGULAR_NUMBER_1
*\*\          - ADC_REGULAR_NUMBER_2
*\*\          - ADC_REGULAR_NUMBER_3
*\*\          - ADC_REGULAR_NUMBER_4
*\*\          - ADC_REGULAR_NUMBER_5
*\*\          - ADC_REGULAR_NUMBER_6
*\*\          - ADC_REGULAR_NUMBER_7
*\*\          - ADC_REGULAR_NUMBER_8
*\*\          - ADC_REGULAR_NUMBER_9
*\*\          - ADC_REGULAR_NUMBER_10
*\*\          - ADC_REGULAR_NUMBER_11
*\*\          - ADC_REGULAR_NUMBER_12
*\*\          - ADC_REGULAR_NUMBER_13
*\*\          - ADC_REGULAR_NUMBER_14
*\*\          - ADC_REGULAR_NUMBER_15
*\*\          - ADC_REGULAR_NUMBER_16
*\*\return  none
**/
void ADC_Regular_Sequence_Conversion_Number_Config(uint8_t channel, uint8_t number)
{
    /* ADC regular sequence register3 configures channel1 to channel6 */
    if(number <= ADC_REG_SEQ_NUM_OFFSET1)
    {
        ADC->RSEQ3 &= ADC_REGULAR_NUMBER_MASK(number);
        ADC->RSEQ3 |= ADC_REGULAR_NUMBER_SET(channel, number);
    }
    /* ADC regular sequence register2 configures channel7 to channel12 */
    else if(number <= ADC_REG_SEQ_NUM_OFFSET2)
    {
        ADC->RSEQ2 &= ADC_REGULAR_NUMBER_MASK((number - ADC_REG_SEQ_NUM_OFFSET3));
        ADC->RSEQ2 |= ADC_REGULAR_NUMBER_SET(channel, (number - ADC_REG_SEQ_NUM_OFFSET3));
    }
    /* ADC regular sequence register1 configures channel13 to channel16 */
    else
    {
        ADC->RSEQ1 &= ADC_REGULAR_NUMBER_MASK((number - ADC_REG_SEQ_NUM_OFFSET4));
        ADC->RSEQ1 |= ADC_REGULAR_NUMBER_SET(channel, (number - ADC_REG_SEQ_NUM_OFFSET4));
    }
}

/**
*\*\name    ADC_External_Trigger_Conversion_Config.
*\*\fun     ADC conversion through external trigger enable.
*\*\param   group_operation :
*\*\          - ADC_EXTTRIGCONV_REGULAR_ENABLE
*\*\          - ADC_EXTTRIGCONV_REGULAR_DISABLE
*\*\          - ADC_EXTTRIGCONV_INJECTED_ENABLE
*\*\          - ADC_EXTTRIGCONV_INJECTED_DISABLE
*\*\return  none
**/
void ADC_External_Trigger_Conversion_Config(uint32_t group_operation)
{
    if(group_operation == ADC_EXTTRIGCONV_REGULAR_ENABLE)
    {
        /* Enable ADC regular group channels conversion on external event */
        ADC->CTRL2 |= group_operation;
    }
    else if(group_operation == ADC_EXTTRIGCONV_REGULAR_DISABLE)
    {
        /* Disables ADC regular group channels conversion on external event */
        ADC->CTRL2 &= group_operation;
    }
    else if(group_operation == ADC_EXTTRIGCONV_INJECTED_ENABLE)
    {
        /* Enables ADC injected group channels conversion on external event */
        ADC->CTRL2 |= group_operation;
    }
    else if(group_operation == ADC_EXTTRIGCONV_INJECTED_DISABLE)
    {
        /* Disables ADC injected group channels conversion on external event */
        ADC->CTRL2 &= group_operation;
    }
}

/**
*\*\name    ADC_Regular_Group_Conversion_Data_Get.
*\*\fun     Get ADC regular group conversion data.
*\*\return  ADC regular group conversion data.
**/
uint16_t ADC_Regular_Group_Conversion_Data_Get(void)
{
    /* Return the conversion value */
    return (uint16_t)ADC->DAT;
}

/**
*\*\name    ADC_Injected_Group_Autoconversion_Enable.
*\*\fun     Enable ADC injected group auto conversion mode.
*\*\return  none
**/
void ADC_Injected_Group_Autoconversion_Enable(void)
{
    /* Set the ADC_CTRL1 AUTOJC bit to enable ADC injected group auto conversion mode */
    ADC->CTRL1 |= ADC_INJECTED_AUTOCONV_ENABLE;
}

/**
*\*\name    ADC_Injected_Group_Autoconversion_Disable.
*\*\fun     Disable ADC injected group auto conversion mode.
*\*\return  none
**/
void ADC_Injected_Group_Autoconversion_Disable(void)
{
    /* Clean the ADC_CTRL1 AUTOJC bit to disable ADC injected group auto conversion mode */
    ADC->CTRL1 &= ADC_INJECTED_AUTOCONV_DISABLE;
}

/**
*\*\name    ADC_Injected_Group_External_Trigger_Source_Config.
*\*\fun     Configures the ADC external trigger for injected group channels.
*\*\param   external_trigger_sources :
*\*\          - ADC_EXT_TRIGCONV_INJECTED_T1_TRGO           
*\*\          - ADC_EXT_TRIGCONV_INJECTED_T1_CC4            
*\*\          - ADC_EXT_TRIGCONV_INJECTED_T2_TRGO            
*\*\          - ADC_EXT_TRIGCONV_INJECTED_T2_CC1            
*\*\          - ADC_EXT_TRIGCONV_INJECTED_T3_CC4            
*\*\          - ADC_EXT_TRIGCONV_INJECTED_T4_TRGO          
*\*\          - ADC_EXT_TRIGCONV_INJECTED_EXT_INT15_TIM8_CC4 
*\*\          - ADC_EXT_TRIGCONV_INJECTED_SWSTRJCH          
*\*\return  none
**/
void ADC_Injected_Group_External_Trigger_Source_Config(uint32_t external_trigger_sources)
{
    /* Clear ADC_CTRL2 EXTJSEL[2:0] bit */
    ADC->CTRL2 &= ADC_EXT_TRIGCONV_INJECTED_MASK;
    /* Set ADC_CTRL2 EXTJSEL[2:0] bit */
    ADC->CTRL2 |= external_trigger_sources;
}

/**
*\*\name    ADC_Injected_Channels_Software_Conversion_Operation.
*\*\fun     Configures ADC injected channels software conversion.
*\*\param   conversion_operation :
*\*\          - ADC_EXTJTRIG_SWSTRJCH_ENABLE
*\*\          - ADC_EXTJTRIG_SWSTRJCH_DISABLE
*\*\          - ADC_EXTJTRIG_SWSTRJCH_GET_STS
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus ADC_Injected_Channels_Software_Conversion_Operation(uint32_t conversion_operation)
{
    if(conversion_operation == ADC_EXTJTRIG_SWSTRJCH_ENABLE)
    {
        /* Enable the ADC external trigger conversion mode for injected channels */
        ADC->CTRL2 |= conversion_operation;
    }
    else if(conversion_operation == ADC_EXTJTRIG_SWSTRJCH_DISABLE)
    {
        /* Disable the ADC external trigger conversion mode for injected channels */
        ADC->CTRL2 &= conversion_operation;
    }
    else if(conversion_operation == ADC_EXTJTRIG_SWSTRJCH_GET_STS)
    {
        /* Get ADC_CTRL2 SWSTRJCH bit */
        if ((ADC->CTRL2 & conversion_operation) != (uint32_t)RESET)
        {
            return SET;
        }
        else
        {
            return RESET;
        }
    }
    return RESET;
}

/**
*\*\name    ADC_Injected_Sequence_Conversion_Number_Config.
*\*\fun     Configures ADC channel conversion number in injected sequence.
*\*\param   channel :
*\*\          - ADC_CH_0
*\*\          - ADC_CH_1
*\*\          - ADC_CH_2
*\*\          - ADC_CH_3
*\*\          - ADC_CH_4
*\*\          - ADC_CH_5
*\*\          - ADC_CH_6
*\*\          - ADC_CH_7
*\*\          - ADC_CH_8
*\*\          - ADC_CH_9
*\*\          - ADC_CH_10
*\*\          - ADC_CH_11
*\*\          - ADC_CH_12
*\*\          - ADC_CH_13
*\*\          - ADC_CH_14
*\*\          - ADC_CH_15
*\*\          - ADC_CH_16
*\*\          - ADC_CH_17
*\*\          - ADC_CH_18
*\*\param   number :
*\*\          - ADC_INJECTED_NUMBER_1
*\*\          - ADC_INJECTED_NUMBER_2
*\*\          - ADC_INJECTED_NUMBER_3
*\*\          - ADC_INJECTED_NUMBER_4
*\*\return  none
**/
void ADC_Injected_Sequence_Conversion_Number_Config(uint8_t channel, uint8_t number)
{
    /* ADC Injected sequence register configures conversion sequence*/
    ADC->JSEQ &= ADC_INJECTED_NUMBER_MASK(number);
    ADC->JSEQ |= ADC_INJECTED_NUMBER_SET(channel, number);
}

/**
*\*\name    ADC_Injected_Channels_Number_Config.
*\*\fun     Configures the number of ADC channels that will be converted
*\*\        using the sequencer for Injected channel group.
*\*\param   channels_number :
*\*\          - ADC_INJECTED_LEN_1
*\*\          - ADC_INJECTED_LEN_2
*\*\          - ADC_INJECTED_LEN_3
*\*\          - ADC_INJECTED_LEN_4
*\*\return  none
**/
void ADC_Injected_Channels_Number_Config(uint32_t channels_number)
{
    /* Clear ADC_JSEQ LEN[3:0] bit */
    ADC->JSEQ &= ADC_INJECTED_LEN_MSAK;
    /* Set ADC_RSEQ1 LEN[3:0] bit */
    ADC->JSEQ |= channels_number;
}

/**
*\*\name    ADC_Injected_Channels_Offset_Config.
*\*\fun     Configures the injected channels conversion value offset.
*\*\param   channels_number :
*\*\          - ADC_INJECTED_DATA_REG_1
*\*\          - ADC_INJECTED_DATA_REG_2
*\*\          - ADC_INJECTED_DATA_REG_3
*\*\          - ADC_INJECTED_DATA_REG_4
*\*\param   Offset_data : 12bit offset value(0 ~ 0xFFF)
*\*\return  none
**/
void ADC_Injected_Channels_Offset_Config(uint8_t injected_channel, uint16_t offset_data)
{
    __IO uint32_t temp_value = 0;

    temp_value = (uint32_t)ADC;
    temp_value += injected_channel;

    /* Set the selected injected channel data offset */
    *(__IO uint32_t*)temp_value = (uint32_t)offset_data;
}

/**
*\*\name    ADC_Injected_Group_Conversion_Data_Get.
*\*\fun     Get ADC injected group conversion data.
*\*\param   channels_number :
*\*\          - ADC_INJECTED_DATA_REG_1
*\*\          - ADC_INJECTED_DATA_REG_2
*\*\          - ADC_INJECTED_DATA_REG_3
*\*\          - ADC_INJECTED_DATA_REG_4
*\*\return  ADC injected group conversion data.
**/
uint16_t ADC_Injected_Group_Conversion_Data_Get(uint8_t reg_offset)
{
    __IO uint32_t temp_value = 0;

    temp_value = (uint32_t)ADC;
    temp_value += reg_offset + ADC_JDAT_REG_OFFSET;

    /* Return the injected group conversion data */
    return (uint16_t)(*(__IO uint32_t*)temp_value);
}

/**
*\*\name    ADC_Analog_Watchdog_Mode_Channel_Config.
*\*\fun     Configures ADC analog watchdog single mode or scan mode,
*\*\        and single mode channel operation.
*\*\param   mode :
*\*\          - ADC_ANALOG_WTDG_SINGLE_MODE
*\*\          - ADC_ANALOG_WTDG_SCAN_MODE
*\*\param   channel :
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH0
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH1
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH2
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH3
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH4
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH5
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH6
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH7
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH8
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH9
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH10
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH11
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH12
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH13
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH14
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH15
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH16
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH17
*\*\          - ADC_ANALOG_WTDG_SINGLE_CH18
*\*\return  none
**/
void ADC_Analog_Watchdog_Mode_Channel_Config(uint32_t mode, uint8_t channel)
{
    /* ADC analog watchdog single mode */
    if(mode == ADC_ANALOG_WTDG_SINGLE_MODE)
    {
        ADC->CTRL1 |= mode;
        /* Clear ADC analog watchdog single mode channel */
        ADC->CTRL1 &= ADC_ANALOG_WTDG_SINGLE_CH_MASK;
        /* Select ADC analog watchdog single mode channel */
        ADC->CTRL1 |= (uint32_t)channel;
    }
    /* ADC analog watchdog scan mode */
    else
    {
        ADC->CTRL1 &= ADC_ANALOG_WTDG_MODE_MASK;
    }
}

/**
*\*\name    ADC_Analog_Watchdog_Enable.
*\*\fun     Enable ADC Analog watchdog.
*\*\param   wcdg_mode :
*\*\          - ADC_ANALOG_WTDG_REGULAR
*\*\          - ADC_ANALOG_WTDG_INJECTED
*\*\return  none
**/
void ADC_Analog_Watchdog_Enable(uint32_t wcdg_mode)
{
    /* Set the ADC_CTRL1 AWDGERCH bit */
    ADC->CTRL1 |= wcdg_mode;
}

/**
*\*\name    ADC_Analog_Watchdog_Disable.
*\*\fun     Disable ADC Analog watchdog.
*\*\param   wcdg_mode :
*\*\          - ADC_ANALOG_WTDG_REGULAR
*\*\          - ADC_ANALOG_WTDG_INJECTED
*\*\return  none
**/
void ADC_Analog_Watchdog_Disable(uint32_t wcdg_mode)
{
    /* Clean the ADC_CTRL1 AWDGERCH bit */
    ADC->CTRL1 &= (~wcdg_mode);
}


/**
*\*\name    ADC_Analog_Watchdog_HighThresholds_Config.
*\*\fun     Configures the high thresholds of the analog watchdog.
*\*\param   high_thresholds : 12bit high thresholds value(0 ~ 0xFFF)
*\*\return  none
**/
void ADC_Analog_Watchdog_HighThresholds_Config(uint16_t high_thresholds)
{
    /* Set the ADC high thresholds */
    ADC->WDGHIGH = high_thresholds;
}

/**
*\*\name    ADC_Analog_Watchdog_LowThresholds_Config.
*\*\fun     Configures the low thresholds of the analog watchdog.
*\*\param   low_thresholds : 12bit low thresholds value(0 ~ 0xFFF)
*\*\return  none
**/
void ADC_Analog_Watchdog_LowThresholds_Config(uint16_t low_thresholds)
{
    /* Set the ADC low thresholds */
    ADC->WDGLOW = low_thresholds;
}

/**
*\*\name    ADC_Temperature_Sensor_And_Vrefint_Channel_Enable.
*\*\fun     Enable ADC Temperature sensor and VREFINT channel.
*\*\return  none
**/
void ADC_Temperature_Sensor_And_Vrefint_Channel_Enable(void)
{
    /* Enable the temperature sensor and Vrefint channel*/
    ADC->CTRL2 |= ADC_TS_VREFINT_CHANNEL_ENABLE;
    /* Enable the temperature sensor and Vrefint in AEFC register */
    _EnVref1p2()
}

/**
*\*\name    ADC_Temperature_Sensor_And_Vrefint_Channel_Disable.
*\*\fun     Disable ADC Temperature sensor and VREFINT channel.
*\*\return  none
**/
void ADC_Temperature_Sensor_And_Vrefint_Channel_Disable(void)
{
    /* Disable the temperature sensor and Vrefint channel*/
    ADC->CTRL2 &= ADC_TS_VREFINT_CHANNEL_DISABLE;
    /* Disable the temperature sensor and Vrefint in AEFC register */
    _DisVref1p2()
}

/**
*\*\name    ADC_INTFlag_Status_Get.
*\*\fun     Get ADC flag Status.
*\*\param   adc_flag :
*\*\          - ADC_INT_FLAG_AWDG
*\*\          - ADC_INT_FLAG_ENDC
*\*\          - ADC_INT_FLAG_JENDC
*\*\          - ADC_INT_FLAG_ENDCA
*\*\          - ADC_INT_FLAG_JENDCA
*\*\return  SET or RESET
**/
FlagStatus ADC_INTFlag_Status_Get(uint8_t adc_flag)
{
    /* Check the status of ADC flag */
    if ((ADC->STS & adc_flag) != (uint8_t)RESET)
    {
        /* ADC_FLAG is set */
        return SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        return RESET;
    }
}

/**
*\*\name    ADC_Flag_Status_Get.
*\*\fun     Get ADC flag Status.
*\*\param   selflag :
*\*\          - ADC_RUN_FLAG
*\*\          - ADC_RD_FLAG
*\*\param   adc_runflag :
*\*\          - ADC_FLAG_AWDG
*\*\          - ADC_FLAG_ENDC
*\*\          - ADC_FLAG_JENDC
*\*\          - ADC_FLAG_JSTR
*\*\          - ADC_FLAG_STR
*\*\          - ADC_FLAG_ENDCA
*\*\          - ADC_FLAG_JENDCA
*\*\param   adc_rdflag :
*\*\          - ADC_FLAG_RDY
*\*\          - ADC_FLAG_PD_RDY
*\*\return  SET or RESET
**/
FlagStatus ADC_Flag_Status_Get(uint8_t selflag, uint8_t adc_runflag, uint8_t adc_rdflag)
{
    if(selflag == ADC_RUN_FLAG)
    {    
        /* Check the status of ADC flag */
        if ((ADC->STS & adc_runflag) != (uint8_t)RESET)
        {
            /* ADC_FLAG is set */
            return SET;
        }
        else
        {
            /* ADC_FLAG is reset */
            return RESET;
        }
    }
    else
    {
        if ((ADC->CTRL3 & adc_rdflag) != (uint8_t)RESET)
        {
            /* ADC_FLAG is set */
            return SET;
        }
        else
        {
            /* ADC_FLAG is reset */
            return RESET;
        }
    }
}


/**
*\*\name    ADC_INTFlag_Status_Clear.
*\*\fun     Clear ADC flag Status.
*\*\param   adc_flag :
*\*\          - ADC_INT_FLAG_AWDG
*\*\          - ADC_INT_FLAG_ENDC
*\*\          - ADC_INT_FLAG_JENDC
*\*\          - ADC_INT_FLAG_ENDCA
*\*\          - ADC_INT_FLAG_JENDCA
*\*\return  SET or RESET
**/
void ADC_INTFlag_Status_Clear(uint8_t adc_flag)
{
    /* Clear the selected ADC flag Status */
    ADC->STS &= ~(uint32_t)adc_flag;
}

/**
*\*\name    ADC_Flag_Status_Clear.
*\*\fun     Clear ADC flag Status.
*\*\param   adc_flag :
*\*\          - ADC_FLAG_AWDG
*\*\          - ADC_FLAG_ENDC
*\*\          - ADC_FLAG_JENDC
*\*\          - ADC_FLAG_JSTR
*\*\          - ADC_FLAG_STR
*\*\          - ADC_FLAG_ENDCA
*\*\          - ADC_FLAG_JENDCA
*\*\return  SET or RESET
**/
void ADC_Flag_Status_Clear(uint8_t adc_flag)
{
    /* Clear the selected ADC flag Status */
    ADC->STS &= ~(uint32_t)adc_flag;
}
/**
*\*\name    ADC_Vbat_Monitor_Enable.
*\*\fun     Enable ADC Vbat monitor.
*\*\return  none
**/
void ADC_Vbat_Monitor_Enable(void)
{
    /* Enable Vbat monitor */
    ADC->CTRL3 |= ADC_VBAT_MONITOR_ENABLE;
    /* Enable Vbat monitor in AFEC register */
    _EnVref1p2()
}

/**
*\*\name    ADC_Vbat_Monitor_Disable.
*\*\fun     Disable ADC Vbat monitor.
*\*\return  none
**/
void ADC_Vbat_Monitor_Disable(void)
{
    /* Disable Vbat monitor */
    ADC->CTRL3 &= ADC_VBAT_MONITOR_DISABLE;
    /* Disable Vbat monitor in AFEC register */
    _DisVref1p2()
}

/**
*\*\name    ADC_Deep_Power_Mode_Enable.
*\*\fun     Enable ADC deep power mode.
*\*\return  none
**/
void ADC_Deep_Power_Mode_Enable(void)
{   
    /* Set the ADC_CTRL3 DPWMOD bit to enable ADC deep power mode */
    ADC->CTRL3 |= ADC_DEEP_POWER_ENABLE;
}

/**
*\*\name    ADC_Deep_Power_Mode_Disable.
*\*\fun     Disable ADC deep power mode.
*\*\return  none
**/
void ADC_Deep_Power_Mode_Disable(void)
{   
    /* Clear the ADC_CTRL3 DPWMOD bit to disable ADC deep power mode */
    ADC->CTRL3 &= ADC_DEEP_POWER_DISABLE;
}

/**
*\*\name    ADC_AHB_Clock_Mode_Config.
*\*\fun     Configures the ADC AHB clock mode.
*\*\return  none
**/
void ADC_AHB_Clock_Mode_Config(void)
{   
    /* Clear the ADC_CTRL3 CKMOD bit */
    ADC->CTRL3 &= ADC_CLOCK_AHB;  
}

/**
*\*\name    ADC_PLL_Clock_Mode_Config.
*\*\fun     Configures the ADC PLL clock mode.
*\*\return  none
**/
void ADC_PLL_Clock_Mode_Config(void)
{   
    /* Set the ADC_CTRL3 CKMOD bit to select clock mode*/
    ADC->CTRL3 |= ADC_CLOCK_PLL;  
}

/**
*\*\name    ADC_Calibration_Auto_Load_Enable.
*\*\fun     Enable ADC Calibration Auto Load mode.
*\*\return  none
**/
void ADC_Calibration_Auto_Load_Enable(void)
{   
    /* Set the ADC_CTRL3 CALALD bit to enable or disable ADC Calibration Auto Load */
    ADC->CTRL3 |= ADC_CALALD_ENABLE;
}

/**
*\*\name    ADC_Calibration_Auto_Load_Disable.
*\*\fun     Disable ADC Calibration Auto Load mode.
*\*\return  none
**/
void ADC_Calibration_Auto_Load_Disable(void)
{   
    /* Clear the ADC_CTRL3 CALALD bit */
    ADC->CTRL3 &= ADC_CALALD_DISABLE;
}

/**
*\*\name    ADC_Differential_Mode_Enable.
*\*\fun     Enable ADC Calibration Auto Load mode.
*\*\return  none
**/
void ADC_Differential_Mode_Enable(void)
{   
    /* Set the ADC_CTRL3 CALDIF bit */
    ADC->CTRL3 |= ADC_CALDIF_ENABLE;
}

/**
*\*\name    ADC_Differential_Mode_Disable.
*\*\fun     Disable ADC Calibration Auto Load mode.
*\*\return  none
**/
void ADC_Differential_Mode_Disable(void)
{   
    /* Clear the ADC_CTRL3 CALDIF bit */
    ADC->CTRL3 &= ADC_CALDIF_DISABLE;
}

/**
*\*\name    ADC_Data_Resolution_Config
*\*\fun     Configures ADC data resolution conversion.
*\*\param   resbit :
*\*\          - ADC_RST_BIT_12  
*\*\          - ADC_RST_BIT_10  
*\*\          - ADC_RST_BIT_8    
*\*\          - ADC_RST_BIT_6    
*\*\return  none
**/
void ADC_Data_Resolution_Config(uint32_t resbit)
{   
    /* Clear the ADC_CTRL3 RES[1:0] bit */
    ADC->CTRL3 &= ADC_RES_MSK;
    /* Set the ADC_CTRL3 RES[1:0] bit to select data resolution*/
    ADC->CTRL3 |= resbit;
}

/**
*\*\name    ADC_Sample_Time_Level_Config.
*\*\fun     Configures the level of sample time.
*\*\param   sample_time_level :
*\*\          - ADC_SAMPLE_LEVEL_0
*\*\          - ADC_SAMPLE_LEVEL_1
*\*\return  none
**/
void ADC_Sample_Time_Level_Config(uint32_t sample_time_level)
{   
    /* Clear the ADC_SAMPT3 SAMSEL bit */
    ADC->SAMPT3 &= ADC_SAMPLE_LEVEL_MASK;
    /* Set the ADC_SAMPT3 SAMSEL bit to select sample time*/
    ADC->SAMPT3 |= sample_time_level;  
}

/**
*\*\name    ADC_Initializes_Ex.
*\*\fun     Initializes the ADC according to ADC_initstructEx.
*\*\param   ADC_initstructEx :
*\*\          - VbatMinitEn
*\*\          - DeepPowerModEn    
*\*\          - JendcIntEn
*\*\          - EndcIntEn    
*\*\          - ClkMode    
*\*\          - CalAtuoLoadEn
*\*\          - DifModCal
*\*\          - ResBit    
*\*\          - SampSecondStyle
*\*\return  none
**/
void ADC_Initializes_Ex(ADC_InitTypeEx* ADC_initstructEx)
{
    if (ADC_initstructEx->VbatMinitEn)
        ADC_Vbat_Monitor_Enable();
    else
        ADC_Vbat_Monitor_Disable();
    
    if (ADC_initstructEx->DeepPowerModEn)
        ADC_Deep_Power_Mode_Enable();
    else
        ADC_Deep_Power_Mode_Disable();

    if (ADC_initstructEx->JendcIntEn)
        ADC_Interrupts_Enable(ADC_INT_JENDCA);
    else
        ADC_Interrupts_Disable(ADC_INT_JENDCA);

    if (ADC_initstructEx->EndcIntEn)
        ADC_Interrupts_Enable(ADC_INT_ENDCA);
    else
        ADC_Interrupts_Disable(ADC_INT_ENDCA);
    
    if (ADC_initstructEx->ClkMode == ADC_CKMOD_PLL)
        ADC_PLL_Clock_Mode_Config();
    else
        ADC_AHB_Clock_Mode_Config();

    if (ADC_initstructEx->CalAtuoLoadEn)
        ADC_Calibration_Auto_Load_Enable();
    else
        ADC_Calibration_Auto_Load_Disable();

    if (ADC_initstructEx->DifModCal)
        ADC_Differential_Mode_Enable();
    else
        ADC_Differential_Mode_Disable();

    ADC_Data_Resolution_Config(ADC_initstructEx->ResBit);
    ADC_Sample_Time_Level_Config(ADC_initstructEx->SampSecondStyle);

}

/**
*\*\name    ADC_Initializes_StructureEx.
*\*\fun     Fills each ADC_initstructEx member with its default value.
*\*\param   ADC_initstructEx :
*\*\          - VbatMinitEn
*\*\          - DeepPowerModEn    
*\*\          - JendcIntEn
*\*\          - EndcIntEn    
*\*\          - ClkMode    
*\*\          - CalAtuoLoadEn
*\*\          - DifModCal
*\*\          - ResBit    
*\*\          - SampSecondStyle
*\*\return  none
**/
void ADC_Initializes_StructureEx(ADC_InitTypeEx* ADC_initstructEx)
{
    /* Reset ADC init structure_ex parameters values */
    /* Initialize the VbatMinitEn member */
    ADC_initstructEx->VbatMinitEn       = DISABLE;
    /* initialize the DeepPowerModEn member */
    ADC_initstructEx->DeepPowerModEn    = DISABLE;
    /* Initialize the JendcIntEn member */
    ADC_initstructEx->JendcIntEn        = DISABLE;
    /* initialize the EndcIntEn member */
    ADC_initstructEx->EndcIntEn         = DISABLE;
    /* Initialize the ClkMode member */
    ADC_initstructEx->ClkMode           = ADC_CKMOD_AHB;
    /* initialize the CalAtuoLoadEn member */
    ADC_initstructEx->CalAtuoLoadEn     = DISABLE;
    /* Initialize the DifModCal member */
    ADC_initstructEx->DifModCal         = DISABLE;
    /* initialize the ResBit member */
    ADC_initstructEx->ResBit            = ADC_RST_BIT_12;
    /* Initialize the SampSecondStyle member */
    ADC_initstructEx->SampSecondStyle   = ADC_SAMPLE_LEVEL_0;
}

/**
*\*\name    ADC_Bypass_Calibration_Enable
*\*\fun     Enable ADC Calibration Bypass Load .
*\*\return  none
**/
void ADC_Bypass_Calibration_Enable(void)
{
    /* Set the ADC_CTRL3 BPCAL bit */
    ADC->CTRL3 |= ADC_BYPASSES_CAL_ENABLE;
}

/**
*\*\name    ADC_Bypass_Calibration_Disable
*\*\fun     Disable ADC Calibration Bypass Load .
*\*\return  none
**/
void ADC_Bypass_Calibration_Disable(void)
{
    /* Clear the ADC_CTRL3 BPCAL bit */
    ADC->CTRL3 &= ADC_BYPASSES_CAL_DISABLE;
}

/**
*\*\name    ADC_Differential_Channels_Config.
*\*\fun     Configures the ADC Differential mode.
*\*\param   DifChs :
*\*\          - ADC_DIFSEL_CHS_1    
*\*\          - ADC_DIFSEL_CHS_2    
*\*\          - ADC_DIFSEL_CHS_3    
*\*\          - ADC_DIFSEL_CHS_4    
*\*\          - ADC_DIFSEL_CHS_5    
*\*\          - ADC_DIFSEL_CHS_6   
*\*\          - ADC_DIFSEL_CHS_7   
*\*\          - ADC_DIFSEL_CHS_8    
*\*\          - ADC_DIFSEL_CHS_9    
*\*\          - ADC_DIFSEL_CHS_10 
*\*\          - ADC_DIFSEL_CHS_11  
*\*\          - ADC_DIFSEL_CHS_12   
*\*\          - ADC_DIFSEL_CHS_13   
*\*\          - ADC_DIFSEL_CHS_14   
*\*\          - ADC_DIFSEL_CHS_15   
*\*\          - ADC_DIFSEL_CHS_16   
*\*\          - ADC_DIFSEL_CHS_17   
*\*\          - ADC_DIFSEL_CHS_18
*\*\return  none
**/
void ADC_Differential_Channels_Config(uint32_t difchs)
{
    /* Clear the ADC_DIFSEL DIFSEL[18:1] bit */
    ADC->DIFSEL &= ADC_DIFSEL_CHS_MASK;
    /* Set the ADC_DIFSEL DIFSEL[18:1] bit */
    ADC->DIFSEL |= difchs;
}

/**
*\*\name    ADC_Clock_Mode_Config
*\*\fun     Configures the ADCHCLK prescaler.
*\*\param   ADC_clkmode:
*\*\          - ADC_CKMOD_AHB
*\*\          - ADC_CKMOD_PLL
*\*\param   RCC_ADCHCLKprescaler:
*\*\          - RCC_ADCHCLK_DIV1 
*\*\          - RCC_ADCHCLK_DIV2 
*\*\          - RCC_ADCHCLK_DIV4 
*\*\          - RCC_ADCHCLK_DIV6 
*\*\          - RCC_ADCHCLK_DIV8 
*\*\          - RCC_ADCHCLK_DIV10 
*\*\          - RCC_ADCHCLK_DIV12 
*\*\          - RCC_ADCHCLK_DIV16 
*\*\          - RCC_ADCHCLK_DIV32

*\*\          - RCC_ADCPLLCLK_DIV1 
*\*\          - RCC_ADCPLLCLK_DIV2 
*\*\          - RCC_ADCPLLCLK_DIV4 
*\*\          - RCC_ADCPLLCLK_DIV6 
*\*\          - RCC_ADCPLLCLK_DIV8
*\*\          - RCC_ADCPLLCLK_DIV10
*\*\          - RCC_ADCPLLCLK_DIV12 
*\*\          - RCC_ADCPLLCLK_DIV16 
*\*\          - RCC_ADCPLLCLK_DIV32 
*\*\          - RCC_ADCPLLCLK_DIV64 
*\*\          - RCC_ADCPLLCLK_DIV128 
*\*\          - RCC_ADCPLLCLK_DIV256 
*\*\
**/
void ADC_Clock_Mode_Config(ADC_CKMOD ADC_clkmode, uint32_t RCC_ADCHCLKprescaler)
{
    RCC_ADC_Hclk_Enable();
    if(ADC_clkmode == ADC_CKMOD_AHB)
    {
        RCC_ADC_PLL_Clock_Disable();
        RCC_ADC_Hclk_Config(RCC_ADCHCLKprescaler);
        ADC_AHB_Clock_Mode_Config();
    }
    else
    {
        RCC_ADC_PLL_Clock_Prescaler_Enable(RCC_ADCHCLKprescaler);
        ADC_PLL_Clock_Mode_Config();
    }
}

