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
*\*\file n32g430_rcc.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved. 
**/
#include "n32g430_rcc.h"


/** RCC Private Defines **/
static const uint8_t APBAHBPresTable[16]     = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
static const uint8_t ADCHCLKPresTable[16]    = {1, 2, 4, 6, 8, 10, 12, 16, 32, 32, 32, 32, 32, 32, 32, 32};
static const uint16_t ADCPLLCLKPresTable[16] = {1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256, 256, 256, 256, 256};


/** RCC Driving Functions Declaration **/ 

/**
*\*\name    RCC_Reset.
*\*\fun     Reset the RCC registers.
*\*\param   none 
*\*\return  none
**/
void RCC_Reset(void)
{
    /* Set HSIEN bit */
    RCC->CTRL |= RCC_CTRL_HSIEN;            

    /* Reset SCLKSW, AHBPRES, APB1PRES, APB2PRES and MCO bits */   
    RCC->CFG &= ~(RCC_CFG_SCLKSW|RCC_CFG_AHBPRES|RCC_CFG_APB1PRES|RCC_CFG_APB2PRES|RCC_CFG_MCO);

    /* Reset HSEEN, CLKSSEN and PLLEN bits */
    RCC->CTRL &= ~(RCC_CTRL_HSEEN|RCC_CTRL_CLKSSEN|RCC_CTRL_PLLEN);

    /* Reset HSEBP bit */
    RCC->CTRL &= ~RCC_CTRL_HSEBP;

    /* Reset PLLSRC, PLLHSEPRES, PLLMULFCT bits */
    RCC->CFG &= ~(RCC_CFG_PLLSRC|RCC_CFG_PLLHSEPRES|RCC_CFG_PLLMULFCT);

    /* Reset CFG2 register */
    RCC->CFG2 = RCC_CFG2_ADC1MPRES_DIV8;

    /* Reset PLLHSIPRE register */
    RCC->PLLHSIPRE = RCC_REG_BIT_MASK;

    /* Disable all interrupts and clear pending bits  */
    RCC->CLKINT = (RCC_CLKINT_LSIRDICLR|RCC_CLKINT_LSERDICLR|RCC_CLKINT_HSIRDICLR
                  |RCC_CLKINT_HSERDICLR|RCC_CLKINT_PLLRDICLR
                  |RCC_CLKINT_CLKSSICLR|RCC_CLKINT_LSESSICLR);
}


/**
*\*\name    RCC_HSE_Config.
*\*\fun     Configures the External High Speed oscillator (HSE).
*\*\param   RCC_HSE :
*\*\          - RCC_HSE_DISABLE    HSE oscillator OFF 
*\*\          - RCC_HSE_ENABLE     HSE oscillator ON
*\*\          - RCC_HSE_BYPASS     HSE oscillator bypassed with external clock
*\*\return  none:
*\*\note    HSE can not be stopped if it is used directly or through the PLL as system clock
**/
void RCC_HSE_Config(uint32_t RCC_HSE)
{
    /* Reset HSEEN and HSEBP bits before configuring the HSE */
    /* Reset HSEEN bit */
    RCC->CTRL &= (~RCC_HSE_ENABLE);
    /* Reset HSEBP bit */
    RCC->CTRL &= (~RCC_HSE_BYPASS);
    /* Configure HSE (RC_HSE_DISABLE is already covered by the code section above) */
    if(RCC_HSE == RCC_HSE_ENABLE)
    {
        /* Set HSEEN bit */
        RCC->CTRL |= RCC_HSE_ENABLE;
    }   
    else if (RCC_HSE == RCC_HSE_BYPASS)
    {
        /* Set HSEBP and HSEEN bits */
        RCC->CTRL |= RCC_HSE_BYPASS | RCC_HSE_ENABLE;
    }
    else
    {
        /* No process */
    }

}
 
/**
*\*\name    RCC_HSE_Stable_Wait.
*\*\fun     Waits for HSE start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    HSE oscillator is stable and ready to use
 *\*\         - ERROR      HSE oscillator not yet ready
**/
ErrorStatus RCC_HSE_Stable_Wait(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value = 0;  
    FlagStatus status_value     = RESET;
	RCC_ClocksType sysclk_value;

	RCC_Clocks_Frequencies_Value_Get(&sysclk_value);
	timeout_value = (HSE_STARTUP_TIMEOUT/((uint32_t)SYSCLK_FREQ_128M/sysclk_value.SysclkFreq));
	
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_Flag_Status_Get(RCC_FLAG_HSERD);
        counter_value++;
    } while ((counter_value != timeout_value) && (status_value == RESET));
    
    if (RCC_Flag_Status_Get(RCC_FLAG_HSERD) != RESET)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}
 
/**
*\*\name    RCC_Clock_Security_System_Enable.
*\*\fun     Enables the HSE Clock Security System.
*\*\param   none  
*\*\return  none. 
**/
void RCC_Clock_Security_System_Enable(void)
{
    *(__IO uint32_t*)RCC_CLKSSEN_BITBAND = (uint32_t)ENABLE;
}

/**
*\*\name    RCC_Clock_Security_System_Disable.
*\*\fun     Disables the HSE Clock Security System.
*\*\param   none  
*\*\return  none. 
**/
void RCC_Clock_Security_System_Disable(void)
{
    *(__IO uint32_t*)RCC_CLKSSEN_BITBAND = (uint32_t)DISABLE;
}

/**
*\*\name    RCC_HSI_Calibration_Value_Set.
*\*\fun     Adjusts the Internal High Speed oscillator (HSI) calibration value.
*\*\param   calibration_value(the calibration trimming value):
*\*\        This parameter must be a number between 0 and 0x1F
*\*\return  none
**/ 
void RCC_HSI_Calibration_Value_Set(uint8_t calibration_value) 
{
    uint32_t temp_value = 0;

    temp_value = RCC->CTRL;
    /* Clear HSITRIM[4:0] bits */
    temp_value &= RCC_HSITRIM_MASK;
    /* Set the HSITRIM[4:0] bits according to HSICalibrationValue value */
    temp_value |= (uint32_t)calibration_value << RCC_CTRL_HSITRIM_OFFSET; 
    /* Store the new value */
    RCC->CTRL = temp_value;
}

/**
*\*\name    RCC_HSI_Enable.
*\*\fun     Enables the Internal High Speed oscillator (HSI).
*\*\param   none
*\*\return  none
**/ 
void RCC_HSI_Enable(void)
{
    *(__IO uint32_t*)RCC_HSIEN_BITBAND = (uint32_t)ENABLE;
}
 
/**
*\*\name    RCC_HSI_Disable.
*\*\fun     Disables the Internal High Speed oscillator (HSI).
*\*\param   none
*\*\return  none
**/ 
void RCC_HSI_Disable(void)
{
    *(__IO uint32_t*)RCC_HSIEN_BITBAND = (uint32_t)DISABLE;
}

/**
*\*\name    RCC_HSI_Stable_Wait.
*\*\fun     Waits for HSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    HSI oscillator is stable and ready to use
 *\*\         - ERROR      HSI oscillator not yet ready
**/
ErrorStatus RCC_HSI_Stable_Wait(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value = 0;  
    FlagStatus status_value     = RESET;
	RCC_ClocksType sysclk_value;

	RCC_Clocks_Frequencies_Value_Get(&sysclk_value);
	timeout_value = (HSE_STARTUP_TIMEOUT/((uint32_t)SYSCLK_FREQ_128M/sysclk_value.SysclkFreq));

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_Flag_Status_Get(RCC_FLAG_HSIRD);
        counter_value++;
    } while ((counter_value != timeout_value) && (status_value == RESET));
    
    if (RCC_Flag_Status_Get(RCC_FLAG_HSIRD) != RESET)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
*\*\name    RCC_PLL_Config.
*\*\fun     Configures the PLL clock source and multiplication factor.
*\*\param   PLL_source(PLL entry clock source):
*\*\   		  - RCC_PLL_SRC_HSI_DIV1    HSI oscillator clock selected as PLL clock entry
*\*\   		  - RCC_PLL_SRC_HSI_DIV2    HSI oscillator clock divided by 2 selected as PLL clock entry
*\*\  	      - RCC_PLL_SRC_HSE_DIV1    HSE oscillator clock selected as PLL clock entry
*\*\ 	      - RCC_PLL_SRC_HSE_DIV2    HSE oscillator clock divided by 2 selected as PLL clock entry
*\*\param   PLL_multiplication(PLL multiplication factor):
*\*\	      - RCC_PLL_MUL_2 
*\*\	      - RCC_PLL_MUL_3  
*\*\	      - RCC_PLL_MUL_4  
*\*\	      - RCC_PLL_MUL_5  
*\*\	      - RCC_PLL_MUL_6  
*\*\	      - RCC_PLL_MUL_7  
*\*\	      - RCC_PLL_MUL_8  
*\*\	      - RCC_PLL_MUL_9  
*\*\	      - RCC_PLL_MUL_10 
*\*\	      - RCC_PLL_MUL_11 
*\*\	      - RCC_PLL_MUL_12 
*\*\	      - RCC_PLL_MUL_13 
*\*\	      - RCC_PLL_MUL_14 
*\*\	      - RCC_PLL_MUL_15
*\*\	      - RCC_PLL_MUL_16
*\*\	      - RCC_PLL_MUL_17
*\*\	      - RCC_PLL_MUL_18
*\*\	      - RCC_PLL_MUL_19
*\*\	      - RCC_PLL_MUL_20
*\*\	      - RCC_PLL_MUL_21
*\*\	      - RCC_PLL_MUL_22
*\*\	      - RCC_PLL_MUL_23
*\*\	      - RCC_PLL_MUL_24
*\*\	      - RCC_PLL_MUL_25
*\*\	      - RCC_PLL_MUL_26
*\*\	      - RCC_PLL_MUL_27
*\*\	      - RCC_PLL_MUL_28
*\*\	      - RCC_PLL_MUL_29
*\*\	      - RCC_PLL_MUL_30
*\*\	      - RCC_PLL_MUL_31
*\*\	      - RCC_PLL_MUL_32 
*\*\return  none
*\*\note    This function must be used only when the PLL is disabled.
**/
void RCC_PLL_Config(uint32_t PLL_source, uint32_t PLL_multiplication)
{
    uint32_t temp_value1,temp_value2 = 0;  
    
    temp_value1 = RCC->CFG;
    temp_value2 = RCC->PLLHSIPRE;
    /* Clear PLLSRC, PLLHSEPRES and PLLMULFCT[4:0] bits */
    temp_value1 &= RCC_PLL_MASK;
    /* Clear PLLHSIPRE bits */
    temp_value2 &= RCC_PLLHSIPRE_MASK;
    /* Set the PLL configuration bits */
    if((PLL_source == RCC_PLL_SRC_HSI_DIV1) || (PLL_source == RCC_PLL_SRC_HSI_DIV2))
    {
        temp_value1 |= PLL_multiplication;
        temp_value2 |= PLL_source;
    }
    /* (PLL_source == RCC_PLL_SRC_HSE_DIV1) || (PLL_source == RCC_PLL_SRC_HSE_DIV2) */
    else
    {
        temp_value1 |= PLL_source | PLL_multiplication;
    }
    /* Store the new value */
    RCC->CFG       = temp_value1;
    RCC->PLLHSIPRE = temp_value2;
}

/**
*\*\name    RCC_PLL_Enable.
*\*\fun     Enables the PLL.
*\*\param   none
*\*\return  none
**/ 
void RCC_PLL_Enable(void)
{
    *(__IO uint32_t*)RCC_PLLEN_BITBAND = (uint32_t)ENABLE;
}

/**
*\*\name    RCC_PLL_Disable.
*\*\fun     Disables the PLL.
*\*\param   none
*\*\return  none
**/
void RCC_PLL_Disable(void)
{
    *(__IO uint32_t*)RCC_PLLEN_BITBAND = (uint32_t)DISABLE;
}

/**
*\*\name    RCC_Sysclk_Config.
*\*\fun     Configures the system clock (SYSCLK).
*\*\param   sysclk_source(clock source used as system clock):
*\*\	     - RCC_SYSCLK_SRC_HSI       HSI selected as system clock
*\*\	     - RCC_SYSCLK_SRC_HSE       HSE selected as system clock
*\*\	     - RCC_SYSCLK_SRC_PLLCLK    PLL selected as system clock
*\*\return  none
**/
void RCC_Sysclk_Config(uint32_t sysclk_source)
{
    uint32_t temp_value = 0;
    
    temp_value = RCC->CFG;
    /* Clear SCLKSW[1:0] bits */
    temp_value &= RCC_SYSCLK_SRC_MASK;
    /* Set SCLKSW[1:0] bits according to sysclk_source value */
    temp_value |= sysclk_source;
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_Sysclk_Source_Get.
*\*\fun     Returns the clock source used as system clock.
*\*\param   none
*\*\return  (The clock source used as system clock):
*\*\         - 0x00    HSI used as system clock  
*\*\         - 0x04    HSE used as system clock
*\*\         - 0x08    PLL used as system clock
**/
uint8_t RCC_Sysclk_Source_Get(void)  
{  
    return ((uint8_t)(RCC->CFG & RCC_SYSCLK_STS_MASK));
}

/**
*\*\name    RCC_Hclk_Config.
*\*\fun     Configures the AHB clock (HCLK).
*\*\param   sysclk_div(AHB clock is derived from the system clock (SYSCLK)):
*\*\         - RCC_SYSCLK_DIV1      AHB clock = SYSCLK
*\*\         - RCC_SYSCLK_DIV2      AHB clock = SYSCLK/2
*\*\         - RCC_SYSCLK_DIV4      AHB clock = SYSCLK/4
*\*\         - RCC_SYSCLK_DIV8      AHB clock = SYSCLK/8
*\*\         - RCC_SYSCLK_DIV16     AHB clock = SYSCLK/16
*\*\         - RCC_SYSCLK_DIV64     AHB clock = SYSCLK/64
*\*\         - RCC_SYSCLK_DIV128    AHB clock = SYSCLK/128
*\*\         - RCC_SYSCLK_DIV256    AHB clock = SYSCLK/256
*\*\         - RCC_SYSCLK_DIV512    AHB clock = SYSCLK/512
*\*\return  none
**/
void RCC_Hclk_Config(uint32_t sysclk_div)
{
    uint32_t temp_value = 0;
    temp_value = RCC->CFG;
    /* Clear AHBPRES[3:0] bits */
    temp_value &= RCC_SYSCLK_DIV_MASK;
    /* Set AHBPRES[3:0] bits according to rcc_sysclk value */
    temp_value |= sysclk_div;
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_Pclk1_Config.
*\*\fun     Configures the Low Speed APB clock (PCLK1).
*\*\param   hclk_div(APB1 clock is derived from the AHB clock (HCLK)):
*\*\         - RCC_HCLK_DIV1     APB1 clock = HCLK
*\*\         - RCC_HCLK_DIV2     APB1 clock = HCLK/2
*\*\         - RCC_HCLK_DIV4     APB1 clock = HCLK/4
*\*\         - RCC_HCLK_DIV8     APB1 clock = HCLK/8
*\*\         - RCC_HCLK_DIV16    APB1 clock = HCLK/16
*\*\return  none
**/
void RCC_Pclk1_Config(uint32_t hclk_div)
{
    uint32_t temp_value = 0;
    temp_value = RCC->CFG;
    /* Clear APB1PRES[2:0] bits */
    temp_value &= RCC_APB1_DIV_MASK;
    /* Set APB1PRES[2:0] bits according to hclk_div value */
    temp_value |= hclk_div;
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_Pclk2_Config.
*\*\fun     Configures the High Speed APB clock (PCLK2).
*\*\param   hclk_div(APB2 clock is derived from the AHB clock (HCLK)):
*\*\         - RCC_HCLK_DIV1     APB2 clock = HCLK
*\*\         - RCC_HCLK_DIV2     APB2 clock = HCLK/2
*\*\         - RCC_HCLK_DIV4     APB2 clock = HCLK/4
*\*\         - RCC_HCLK_DIV8     APB2 clock = HCLK/8
*\*\         - RCC_HCLK_DIV16    APB2 clock = HCLK/16
*\*\return  none
**/
void RCC_Pclk2_Config(uint32_t hclk_div)
{
    uint32_t temp_value = 0;
    temp_value = RCC->CFG;
    /* Clear APB2PRES[2:0] bits */
    temp_value &= RCC_APB2_DIV_MASK;
    /* Set APB2PRES[2:0] bits according to hclk_div value */
    temp_value |= hclk_div << RCC_APB2PRES_OFFSET; 
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_Interrupt_Enable.
*\*\fun     Enables the specified RCC interrupts.
*\*\param   interrupt(the RCC interrupt sources to be enabled):
*\*\         - RCC_INT_LSIRDIEN    LSI ready interrupt
*\*\         - RCC_INT_LSERDIEN    LSE ready interrupt
*\*\         - RCC_INT_HSIRDIEN    HSI ready interrupt
*\*\         - RCC_INT_HSERDIEN    HSE ready interrupt
*\*\         - RCC_INT_PLLRDIEN    PLL ready interrupt
*\*\         - RCC_INT_LSESSIEN (Clock security system interrupt in LSE
*\*\return  none
**/
void RCC_Interrupt_Enable(uint32_t interrupt)
{
    /* Perform Byte access to RCC_CLKINT bits to enable the selected interrupts */
    RCC->CLKINT |= interrupt;
}

/**
*\*\name    RCC_Interrupt_Disable.
*\*\fun     Disables the specified RCC interrupts.
*\*\param   interrupt(the RCC interrupt sources to be disabled):
*\*\         - RCC_INT_LSIRDIEN    LSI ready interrupt
*\*\         - RCC_INT_LSERDIEN    LSE ready interrupt
*\*\         - RCC_INT_HSIRDIEN    HSI ready interrupt
*\*\         - RCC_INT_HSERDIEN    HSE ready interrupt
*\*\         - RCC_INT_PLLRDIEN    PLL ready interrupt
*\*\         - RCC_INT_LSESSIEN    Clock security system interrupt in LSE
*\*\return  none
**/
void RCC_Interrupt_Disable(uint32_t interrupt)
{
    /* Perform Byte access to RCC_CLKINT bits to disable the selected interrupts */
    RCC->CLKINT &= (~interrupt);
}

/**
*\*\name    RCC_TIM1_8_Clock_Config.
*\*\fun     Configures the TIM1/8 clock source(TIM1/8CLK).
*\*\param   timer1_8_clksrc(TIM1/8 clock source):
*\*\         - RCC_TIM1_8_CLKSRC_PCLK2 
*\*\         - RCC_TIM1_8_CLKSRC_SYSCLK
*\*\return  none
**/
void RCC_TIM1_8_Clock_Config(uint32_t timer1_8_clksrc)  
{
    uint32_t temp_value = 0;

    temp_value = RCC->CFG2;
    /* Clear TIMCLK_SEL bits */
    temp_value &= RCC_TIM1_8_CLKSRC_MASK;
    /* Set TIMCLK_SEL bits according to timer1_8_clksrc value */
    temp_value |= timer1_8_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ADC_1M_Clock_Config.
*\*\fun     Configures the ADCx 1M clock (ADC1MCLK).
*\*\param   ADC1M_clksrc(ADC1M clock source):
*\*\         - RCC_ADC1MCLK_SRC_HSI
*\*\         - RCC_ADC1MCLK_SRC_HSE
*\*\param   ADC1M_prescaler(ADC1M clock prescaler):
*\*\         - RCC_ADC1MCLK_DIV1 
*\*\         - RCC_ADC1MCLK_DIV2 
*\*\         - RCC_ADC1MCLK_DIV3 
*\*\         - RCC_ADC1MCLK_DIV4 
*\*\         - RCC_ADC1MCLK_DIV5 
*\*\         - RCC_ADC1MCLK_DIV6 
*\*\         - RCC_ADC1MCLK_DIV7 
*\*\         - RCC_ADC1MCLK_DIV8 
*\*\         - RCC_ADC1MCLK_DIV9 
*\*\         - RCC_ADC1MCLK_DIV10
*\*\         - RCC_ADC1MCLK_DIV11
*\*\         - RCC_ADC1MCLK_DIV12
*\*\         - RCC_ADC1MCLK_DIV13
*\*\         - RCC_ADC1MCLK_DIV14
*\*\         - RCC_ADC1MCLK_DIV15
*\*\         - RCC_ADC1MCLK_DIV16
*\*\         - RCC_ADC1MCLK_DIV17
*\*\         - RCC_ADC1MCLK_DIV18
*\*\         - RCC_ADC1MCLK_DIV19
*\*\         - RCC_ADC1MCLK_DIV20
*\*\         - RCC_ADC1MCLK_DIV21
*\*\         - RCC_ADC1MCLK_DIV22
*\*\         - RCC_ADC1MCLK_DIV23
*\*\         - RCC_ADC1MCLK_DIV24
*\*\         - RCC_ADC1MCLK_DIV25
*\*\         - RCC_ADC1MCLK_DIV26
*\*\         - RCC_ADC1MCLK_DIV27
*\*\         - RCC_ADC1MCLK_DIV28
*\*\         - RCC_ADC1MCLK_DIV29
*\*\         - RCC_ADC1MCLK_DIV30
*\*\         - RCC_ADC1MCLK_DIV31
*\*\         - RCC_ADC1MCLK_DIV32
*\*\return  none
**/
void RCC_ADC_1M_Clock_Config(uint32_t ADC1M_clksrc, uint32_t ADC1M_prescaler)
{
    uint32_t temp_value = 0;

    temp_value = RCC->CFG2;
    /* Clear ADC1MSEL and ADC1MPRE[4:0] bits */
    temp_value &= RCC_ADC1MCLK_SRC_MASK;
    temp_value &= RCC_ADC1MCLK_DIV_MASK;
    /* Set ADC1MSEL bits according to ADC1M_clksrc value */
    temp_value |= ADC1M_clksrc;
    /* Set ADC1MPRE[4:0] bits according to ADC1M_prescaler value */
    temp_value |= ADC1M_prescaler;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ADC_PLL_Clock_Prescaler_Enable.
*\*\fun     Configures the ADCPLLCLK prescaler, and enable ADCPLLCLK.
*\*\param   ADC_PLLCLK_prescaler(ADCPLLCLK prescaler):
*\*\         - RCC_ADCPLLCLK_DIV1       ADCPLLCLKPRES[4:0] = 10000, Pll Clock Divided By 1
*\*\         - RCC_ADCPLLCLK_DIV2       ADCPLLCLKPRES[4:0] = 10001, Pll Clock Divided By 2
*\*\         - RCC_ADCPLLCLK_DIV4       ADCPLLCLKPRES[4:0] = 10010, Pll Clock Divided By 4
*\*\         - RCC_ADCPLLCLK_DIV6       ADCPLLCLKPRES[4:0] = 10011, Pll Clock Divided By 6
*\*\         - RCC_ADCPLLCLK_DIV8       ADCPLLCLKPRES[4:0] = 10100, Pll Clock Divided By 8
*\*\         - RCC_ADCPLLCLK_DIV10      ADCPLLCLKPRES[4:0] = 10101, Pll Clock Divided By 10
*\*\         - RCC_ADCPLLCLK_DIV12      ADCPLLCLKPRES[4:0] = 10110, Pll Clock Divided By 12
*\*\         - RCC_ADCPLLCLK_DIV16      ADCPLLCLKPRES[4:0] = 10111, Pll Clock Divided By 16
*\*\         - RCC_ADCPLLCLK_DIV32      ADCPLLCLKPRES[4:0] = 11000, Pll Clock Divided By 32
*\*\         - RCC_ADCPLLCLK_DIV64      ADCPLLCLKPRES[4:0] = 11001, Pll Clock Divided By 64
*\*\         - RCC_ADCPLLCLK_DIV128     ADCPLLCLKPRES[4:0] = 11010, Pll Clock Divided By 128
*\*\         - RCC_ADCPLLCLK_DIV256     ADCPLLCLKPRES[4:0] = 11011, Pll Clock Divided By 256
*\*\         - RCC_ADCPLLCLK_DIV_OTHERS ADCPLLCLKPRES[4:0] = others, Pll Clock Divided By 256
*\*\return  none
**/
void RCC_ADC_PLL_Clock_Prescaler_Enable(uint32_t ADC_PLLCLK_prescaler)
{
    uint32_t temp_value = 0;

    temp_value = RCC->CFG2;
    /* Clear ADCPLLPRES[4:0] bits */
    temp_value &= RCC_ADCPLLCLK_MASK;

    temp_value |= ADC_PLLCLK_prescaler;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ADC_PLL_Clock_Disable.
*\*\fun     Disable ADCPLLCLK (ADCPLLCLKPRES[4:0] = 0xxxx, ADC Pll Clock Disable).
*\*\param   none
*\*\return  none
**/
void RCC_ADC_PLL_Clock_Disable(void)
{
    /* Clear ADCPLLPRES[4:0] bit4 */
    RCC->CFG2 &= RCC_ADCPLLCLK_DISABLE;
}

/**
*\*\name    RCC_ADC_Hclk_Config.
*\*\fun     Configures the ADCHCLK prescaler.
*\*\param   ADC_hclk_prescaler(ADCHCLK prescaler):
*\*\         - RCC_ADCHCLK_DIV1        ADCHCLKPRE[3:0] = 0000, HCLK Clock Divided By 1
*\*\         - RCC_ADCHCLK_DIV2        ADCHCLKPRE[3:0] = 0001, HCLK Clock Divided By 2
*\*\         - RCC_ADCHCLK_DIV4        ADCHCLKPRE[3:0] = 0010, HCLK Clock Divided By 4
*\*\         - RCC_ADCHCLK_DIV6        ADCHCLKPRE[3:0] = 0011, HCLK Clock Divided By 6
*\*\         - RCC_ADCHCLK_DIV8        ADCHCLKPRE[3:0] = 0100, HCLK Clock Divided By 8
*\*\         - RCC_ADCHCLK_DIV10       ADCHCLKPRE[3:0] = 0101, HCLK Clock Divided By 10
*\*\         - RCC_ADCHCLK_DIV12       ADCHCLKPRE[3:0] = 0110, HCLK Clock Divided By 12
*\*\         - RCC_ADCHCLK_DIV16       ADCHCLKPRE[3:0] = 0111, HCLK Clock Divided By 16
*\*\         - RCC_ADCHCLK_DIV32       ADCHCLKPRE[3:0] = 1000, HCLK Clock Divided By 32
*\*\         - RCC_ADCHCLK_DIV_OTHERS  ADCHCLKPRE[3:0] = others, HCLK Clock Divided By 32
*\*\return  none
**/
void RCC_ADC_Hclk_Config(uint32_t ADC_hclk_prescaler)
{
    uint32_t temp_value = 0;

    temp_value = RCC->CFG2;
    /* Clear ADCHPRE[3:0] bits */
    temp_value &= RCC_ADCHCLK_DIV_MASK;
    /* Set ADCHPRE[3:0] bits according to ADC_hclk_prescaler value */
    temp_value |= ADC_hclk_prescaler;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ADC_Hclk_Enable.
*\*\fun     Enables the ADC AHB peripheral clock.
*\*\param   none
*\*\return  none
**/
void RCC_ADC_Hclk_Enable(void)
{
    /* Store the new value */
    RCC->AHB1CLKEN |= RCC_ADCHCLK_ENABLE;
}

/**
*\*\name    RCC_ADC_Hclk_Disable.
*\*\fun     Disables the ADC AHB peripheral clock.
*\*\param   none
*\*\return  none
**/
void RCC_ADC_Hclk_Disable(void)
{
    /* Store the new value */
    RCC->AHB1CLKEN &= (~RCC_ADCHCLK_ENABLE);
}

/**
*\*\name  RCC_LSE_Trim_Config.
*\*\fun  Configures the External Low Speed oscillator (LSE) Trim.
*\*\param   LSE_Trim(LSE Driver Trim Level):
*\*\         - 0x00~0x1FF    
*\*\return  none
**/
void RCC_LSE_Trim_Config(uint16_t LSE_Trim)
{
    uint32_t temp_value = 0;
	
    temp_value = *(__IO uint32_t*)LSE_TRIMR_ADDR;
    /*clear lse trim[8:0]*/
    temp_value &= (~(LSE_GM_MASK_VALUE));
	/*Check and set trim value */
    (LSE_Trim>LSE_GM_MAX_VALUE) ? (LSE_Trim = LSE_GM_MAX_VALUE):(LSE_Trim &= LSE_GM_MASK_VALUE);
    /*Set PWR_CR4 bit15 and bit[8:0] */
	temp_value |= (LSE_NIM_MASK_VALUE|LSE_Trim);
	/* Store the new value */
    *(__IO uint32_t*)LSE_TRIMR_ADDR = temp_value;
}

/**
*\*\name    RCC_LSE_Config.
*\*\fun     Configures the External Low Speed oscillator (LSE).
*\*\param   RCC_LSE(the new state of the LSE):
*\*\         - RCC_LSE_DISABLE    LSE oscillator OFF
*\*\         - RCC_LSE_ENABLE     LSE oscillator ON
*\*\         - RCC_LSE_BYPASS     LSE oscillator bypassed with external clock
*\*\param   LSE_Trim(LSE Driver Trim Level):
*\*\         - 0x00~0x1FF(default value:0x141)    
*\*\return  none
*\*\note  When you do not need to modify the TRIM value, LSE_Trim fill default value(0x141)  
**/
void RCC_LSE_Config(uint32_t RCC_LSE,uint16_t LSE_Trim)
{
    /* Enable PWR Clock */
    RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_PWR);
	/* PWR DBKP set 1 */
    PWR->CTRL |=  PWR_CTRL_DBKP;
    
    /* Reset LSEEN LSEBP bits before configuring the LSE */
    *(__IO uint32_t*)RCC_BDCTRL_ADDR &= (~(RCC_LSE_ENABLE | RCC_LSE_BYPASS));
    /* Configure LSE (RCC_LSE_DISABLE is already covered by the code section above) */
    switch (RCC_LSE)
    {
		case RCC_LSE_ENABLE:
			/* Set LSEON bit */
			*(__IO uint32_t*)RCC_BDCTRL_ADDR |= RCC_LSE_ENABLE;
			RCC_LSE_Trim_Config(LSE_Trim);
			break;
		case RCC_LSE_BYPASS:
			/* Set LSEBYP and LSEON bits */
			*(__IO uint32_t*)RCC_BDCTRL_ADDR |= (RCC_LSE_BYPASS | RCC_LSE_ENABLE);
			break;
		default:
			break;
    }
}

/**
*\*\name    RCC_LSE_Clock_Security_System_Enable.
*\*\fun     Enables the LSE Clock Security System.
*\*\param   none
*\*\return  none
**/
void RCC_LSE_Clock_Security_System_Enable(void)
{
    *(__IO uint32_t*)RCC_LSECLKSSEN_BITBAND = (uint32_t)ENABLE;
}

/**
*\*\name    RCC_LSE_Clock_Security_System_Disable.
*\*\fun     Disables the LSE Clock Security System.
*\*\param   none
*\*\return  none
**/
void RCC_LSE_Clock_Security_System_Disable(void)
{
    *(__IO uint32_t*)RCC_LSECLKSSEN_BITBAND = (uint32_t)DISABLE;
}

/**
*\*\name    RCC_LSE_Clock_Security_System_Status_Get.
*\*\fun     Get LSE Clock Security System failure status.
*\*\param   none
*\*\return  FlagStatus ：SET or RESET
**/
FlagStatus RCC_LSE_Clock_Security_System_Status_Get(void)
{
    /* Check the status of LSE Clock Security System */
    if ((RCC->BDCTRL & RCC_LSE_LSECLKSSF) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }

}

/**
*\*\name    RCC_LSE_Stable_Wait.
*\*\fun     Waits for LSE start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    LSE oscillator is stable and ready to use
 *\*\         - ERROR      LSE oscillator not yet ready
**/
ErrorStatus RCC_LSE_Stable_Wait(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value = 0;   
    FlagStatus status_value     = RESET;
	RCC_ClocksType sysclk_value;

	RCC_Clocks_Frequencies_Value_Get(&sysclk_value);
	timeout_value = (HSE_STARTUP_TIMEOUT/((uint32_t)SYSCLK_FREQ_128M/sysclk_value.SysclkFreq));

    /* Wait till LSE is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_Flag_Status_Get(RCC_FLAG_LSERD);
        counter_value++;
    } while ((counter_value != timeout_value) && (status_value == RESET));
    
    if (RCC_Flag_Status_Get(RCC_FLAG_LSERD) != RESET)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
*\*\name    RCC_LSI_Enable.
*\*\fun     Enables the Internal Low Speed oscillator (LSI).
*\*\param   none
*\*\return  none
**/
void RCC_LSI_Enable(void)
{
    *(__IO uint32_t*)RCC_LSIEN_BITBAND = (uint32_t)ENABLE;
}

/**
*\*\name    RCC_LSI_Disable.
*\*\fun     Disables the Internal Low Speed oscillator (LSI).
*\*\param   none
*\*\return  none
*\*\note   LSI can not be disabled if the IWDG is running.
**/
void RCC_LSI_Disable(void)
{
    *(__IO uint32_t*)RCC_LSIEN_BITBAND = (uint32_t)DISABLE;
}

/**
*\*\name    RCC_LSI_Stable_Wait.
*\*\fun     Waits for LSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    LSI oscillator is stable and ready to use
 *\*\         - ERROR      LSI oscillator not yet ready
**/
ErrorStatus RCC_LSI_Stable_Wait(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value = 0;   
    FlagStatus status_value     = RESET;
	RCC_ClocksType sysclk_value;

	RCC_Clocks_Frequencies_Value_Get(&sysclk_value);
	timeout_value = (HSE_STARTUP_TIMEOUT/((uint32_t)SYSCLK_FREQ_128M/sysclk_value.SysclkFreq));

    /* Wait till LSI is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_Flag_Status_Get(RCC_FLAG_LSIRD);
        counter_value++;
    } while ((counter_value != timeout_value) && (status_value == RESET));
    
    if (RCC_Flag_Status_Get(RCC_FLAG_LSIRD) != RESET)
    {
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}

/**
*\*\name    RCC_RTC_Clock_Config.
*\*\fun     Configures the RTC clock (RTCCLK).
*\*\param   rtcclk_source(the RTC clock source):
*\*\         - RCC_RTCCLK_SRC_NONE          No clock selected as RTC clock)
*\*\         - RCC_RTCCLK_SRC_LSE           LSE selected as RTC clock)
*\*\         - RCC_RTCCLK_SRC_LSI           LSI selected as RTC clock)
*\*\         - RCC_RTCCLK_SRC_HSE_DIV128    HSE clock divided by 128 selected as RTC clock
*\*\return  none
*\*\note    Once the RTC clock is selected it can't be changed unless the Backup domain is reset.
**/
void RCC_RTC_Clock_Config(uint32_t rtcclk_source)
{
    /* Clear the RTC clock source */
    RCC->BDCTRL &= RCC_RTCCLK_SRC_MASK;
    /* Select the RTC clock source */
    RCC->BDCTRL |= rtcclk_source;
}

/**
*\*\name    RCC_RTC_Clock_Enable.
*\*\fun     Enables the RTC clock.
*\*\param   none
*\*\return  none
*\*\note    This function must be used only after the RTC clock was selected 
*\*\        using the RCC_Config_Rtc_Clock function.
**/
void RCC_RTC_Clock_Enable(void)
{
    *(__IO uint32_t*)RCC_RTCEN_BITBAND = (uint32_t)ENABLE;
}

/**
*\*\name    RCC_RTC_Clock_Disable.
*\*\fun     Disables the RTC clock.
*\*\param   none
*\*\return  none
**/
void RCC_RTC_Clock_Disable(void)
{
    *(__IO uint32_t*)RCC_RTCEN_BITBAND = (uint32_t)DISABLE;
}

/**
*\*\name  RCC_LPTIM_Clock_Config.
*\*\fun   Configures the LPTIM clock (LPTIMCLK).
*\*\param clock_source  (specifies the LPTIM clock source).
*\*\     - RCC_LPTIMCLK_SRC_APB1  APB1 clock selected as LPTIM clock
*\*\     - RCC_LPTIMCLK_SRC_LSI   LSI selected as LPTIM clock
*\*\     - RCC_LPTIMCLK_SRC_HSI   HSI selected as LPTIM clock
*\*\     - RCC_LPTIMCLK_SRC_LSE   LSE selected as LPTIM clock
*\*\note When switching from comparator1/2 to other clock sources,
*\*\      it is suggested to disable comparators first.
**/
void RCC_LPTIM_Clock_Config(uint32_t clock_source)
{
    //PWR DBP set 1
    RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_PWR);
    PWR->CTRL |=  PWR_CTRL_DBKP;
    /* Clear the LPTIM clock source */
    RCC->RDCTRL &= RCC_LPTIMCLK_SRC_MASK;

    /* Select the LPTIM clock source */
    RCC->RDCTRL |= clock_source;
}

/**
*\*\name    RCC_LPTIM_Reset.
*\*\fun     LPTIM reset.
*\*\param   none  
*\*\return  none. 
**/
void RCC_LPTIM_Reset(void)
{ 
    RCC->RDCTRL |= (RCC_LPTIMCLK_RESET);
    RCC->RDCTRL &= (~RCC_LPTIMCLK_RESET);
}

/**
*\*\name    RCC_LPTIM_Enable.
*\*\fun     Enables LPTIM.
*\*\param   none  
*\*\return  none. 
**/
void RCC_LPTIM_Enable(void)
{ 
    RCC->RDCTRL |= (RCC_LPTIMCLK_ENBLE);
}

/**
*\*\name    RCC_LPTIM_Disable.
*\*\fun     Disables LPTIM.
*\*\param   none  
*\*\return  none. 
**/
void RCC_LPTIM_Disable(void)
{ 
    RCC->RDCTRL &= (~RCC_LPTIMCLK_ENBLE);
}

/**
*\*\name    RCC_Clocks_Frequencies_Value_Get.
*\*\fun     Returns the frequencies of different on chip clocks.
*\*\param   RCC_clocks pointer to a RCC_ClocksType structure which will hold
*\*\        the clocks frequencies.
*\*\return  none
*\*\note    The result of this function could be not correct when using
*\*\        fractional value for HSE crystal.
**/
void RCC_Clocks_Frequencies_Value_Get(RCC_ClocksType* RCC_clocks)
{
    uint32_t temp_value = SYSCLK_SRC_HSI;
    uint32_t pllclk_value = 0, pllmull_value = 0,pllsource_value = 0, presc_value = 0;

    /* Get PLL clock source and multiplication factor */
    pllmull_value   = RCC->CFG & RCC_CFG_PLLMULFCT;
    pllsource_value = RCC->CFG & RCC_CFG_PLLSRC;

    /* Calculate the frequency division factor */
    if ((pllmull_value & RCC_CFG_PLLMULFCT_4) == 0)
    {
        /*  PLLMULFCT[4] = 0 */
        pllmull_value = (pllmull_value >> RCC_CFG_PLLMULFCT_OFFSET) + 2; 
    }
    else
    {
        // PLLMULFCT[4] = 1
        pllmull_value = ((pllmull_value >> RCC_CFG_PLLMULFCT_OFFSET) - 496) + 1; 
    }

    if (pllsource_value == 0) /* HSI as PLL input clock  */
    { 
         /* HSI selected as PLL clock entry */
        if ((RCC->PLLHSIPRE & RCC_PLLHSIPRE_PLLHSIPRE) != (uint32_t)RESET)
        { /* HSI oscillator clock divided by 2 */
            pllclk_value = (HSI_VALUE >> RCC_CLOCK_DIV2_OFFSET) * pllmull_value;
        }
        else
        {
            pllclk_value = HSI_VALUE * pllmull_value;
        }
    }
    else /* HSE as PLL input clock  */
    {
        /* HSE selected as PLL clock entry */
        if ((RCC->CFG & RCC_CFG_PLLHSEPRES) != (uint32_t)RESET)
        { /* HSE oscillator clock divided by 2 */
            pllclk_value = (HSE_VALUE >> RCC_CLOCK_DIV2_OFFSET) * pllmull_value;
        }
        else
        {
            pllclk_value = HSE_VALUE * pllmull_value;
        }
    }

    /* Get SYSCLK source -------------------------------------------------------*/
    temp_value = RCC->CFG & RCC_CFG_SCLKSTS;

    switch (temp_value)
    {
        case SYSCLK_SRC_HSI: 
            /* HSI used as system clock */
            RCC_clocks->SysclkFreq = HSI_VALUE;
            break;
        case SYSCLK_SRC_HSE: 
            /* HSE used as system clock */
            RCC_clocks->SysclkFreq = HSE_VALUE;
            break;
        case SYSCLK_SRC_PLL: 
            /* PLL used as system clock */
            RCC_clocks->SysclkFreq = pllclk_value;
            break;

        default:
            /* default HSI used as system clock */
            RCC_clocks->SysclkFreq = HSI_VALUE;
            break;
    }

    /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
    /* Get HCLK prescaler */
    temp_value   = (RCC->CFG & RCC_CFG_AHBPRES) >> RCC_CFG_AHBPRES_OFFSET; 
    presc_value = APBAHBPresTable[temp_value];
    /* HCLK clock frequency */
    RCC_clocks->HclkFreq = RCC_clocks->SysclkFreq >> presc_value;
    /* Get PCLK1 prescaler */
    temp_value   = (RCC->CFG & RCC_CFG_APB1PRES) >> RCC_CFG_APB1PRES_OFFSET; 
    presc_value = APBAHBPresTable[temp_value];
    /* PCLK1 clock frequency */
    RCC_clocks->Pclk1Freq = RCC_clocks->HclkFreq >> presc_value;
    /* Get PCLK2 prescaler */
    temp_value   = (RCC->CFG & RCC_CFG_APB2PRES) >> RCC_CFG_APB2PRES_OFFSET; 
    presc_value = APBAHBPresTable[temp_value];
    /* PCLK2 clock frequency */
    RCC_clocks->Pclk2Freq = RCC_clocks->HclkFreq >> presc_value;

    /* Get ADCHCLK prescaler */
    temp_value   = RCC->CFG2 & RCC_CFG2_ADCHPRES;
    presc_value = ADCHCLKPresTable[temp_value];
    /* ADCHCLK clock frequency */
    RCC_clocks->AdcHclkFreq = RCC_clocks->HclkFreq / presc_value;
    /* Get ADCPLLCLK prescaler */
    temp_value   = (RCC->CFG2 & RCC_CFG2_ADCPLLPRES) >> RCC_CFG2_ADCPLLPRES_OFFSET; 
    presc_value = ADCPLLCLKPresTable[(temp_value & 0x0F)]; // ignore BIT5
    /* ADCPLLCLK clock frequency */
    RCC_clocks->AdcPllClkFreq = pllclk_value / presc_value;
}

/**
*\*\name    RCC_AHB_Peripheral_Clock_Enable.
*\*\fun     Enables the AHB peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\         - RCC_AHB_PERIPH_DMA    
*\*\         - RCC_AHB_PERIPH_SRAM   
*\*\         - RCC_AHB_PERIPH_FLITF  
*\*\         - RCC_AHB_PERIPH_CRC    
*\*\         - RCC_AHB_PERIPH_GPIOA   
*\*\         - RCC_AHB_PERIPH_GPIOB   
*\*\         - RCC_AHB_PERIPH_GPIOC   
*\*\         - RCC_AHB_PERIPH_GPIOD   
*\*\         - RCC_AHB_PERIPH_ADC     
*\*\return  none
**/
void RCC_AHB_Peripheral_Clock_Enable(uint32_t AHB_periph)
{
    RCC->AHBPCLKEN |= AHB_periph;
}

/**
*\*\name    RCC_AHB_Peripheral_Clock_Disable.
*\*\fun     Disables the AHB peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\         - RCC_AHB_PERIPH_DMA    
*\*\         - RCC_AHB_PERIPH_SRAM   
*\*\         - RCC_AHB_PERIPH_FLITF  
*\*\         - RCC_AHB_PERIPH_CRC    
*\*\         - RCC_AHB_PERIPH_GPIOA   
*\*\         - RCC_AHB_PERIPH_GPIOB   
*\*\         - RCC_AHB_PERIPH_GPIOC   
*\*\         - RCC_AHB_PERIPH_GPIOD   
*\*\         - RCC_AHB_PERIPH_ADC     
*\*\return  none
*\*\note    SRAM and FLITF clock can be disabled only during sleep mode.
**/
void RCC_AHB_Peripheral_Clock_Disable(uint32_t AHB_periph)
{
    RCC->AHBPCLKEN &= ~AHB_periph;
}

/**
*\*\name    RCC_APB2_Peripheral_Clock_Enable.
*\*\fun     Enables the High Speed APB (APB2) peripheral clock.
*\*\param   APB2_periph (APB2 peripheral to gates its clock):
*\*\        - RCC_APB2_PERIPH_AFIO   
*\*\        - RCC_APB2_PERIPH_BEEPER 
*\*\        - RCC_APB2_PERIPH_TIM1   
*\*\        - RCC_APB2_PERIPH_SPI1   
*\*\        - RCC_APB2_PERIPH_TIM8   
*\*\        - RCC_APB2_PERIPH_USART1 
*\*\        - RCC_APB2_PERIPH_UART3  
*\*\        - RCC_APB2_PERIPH_UART4  
*\*\        - RCC_APB2_PERIPH_SPI2   
*\*\return none. 
**/
void RCC_APB2_Peripheral_Clock_Enable(uint32_t APB2_periph)
{
    RCC->APB2PCLKEN |= APB2_periph;
}

/**
*\*\name    RCC_APB2_Peripheral_Clock_Disable.
*\*\fun     Disables the High Speed APB (APB2) peripheral clock.
*\*\param   APB2_periph (APB2 peripheral to gates its clock)：
*\*\        - RCC_APB2_PERIPH_AFIO   
*\*\        - RCC_APB2_PERIPH_BEEPER 
*\*\        - RCC_APB2_PERIPH_TIM1   
*\*\        - RCC_APB2_PERIPH_SPI1   
*\*\        - RCC_APB2_PERIPH_TIM8   
*\*\        - RCC_APB2_PERIPH_USART1 
*\*\        - RCC_APB2_PERIPH_UART3  
*\*\        - RCC_APB2_PERIPH_UART4  
*\*\        - RCC_APB2_PERIPH_SPI2   
*\*\return none. 
**/
void RCC_APB2_Peripheral_Clock_Disable(uint32_t APB2_periph)
{
    RCC->APB2PCLKEN &= ~APB2_periph;
}

/**
*\*\name    RCC_APB1_Peripheral_Clock_Enable.
*\*\fun     Enables the High Speed APB (APB1) peripheral clock.
*\*\param   APB1_periph (APB1 peripheral to gates its clock):
*\*\        - RCC_APB1_PERIPH_TIM2       
*\*\        - RCC_APB1_PERIPH_TIM3       
*\*\        - RCC_APB1_PERIPH_TIM4       
*\*\        - RCC_APB1_PERIPH_TIM5       
*\*\        - RCC_APB1_PERIPH_TIM6       
*\*\        - RCC_APB1_PERIPH_COMP       
*\*\        - RCC_APB1_PERIPH_COMP_FILT  
*\*\        - RCC_APB1_PERIPH_WWDG       
*\*\        - RCC_APB1_PERIPH_USART2     
*\*\        - RCC_APB1_PERIPH_I2C1       
*\*\        - RCC_APB1_PERIPH_I2C2       
*\*\        - RCC_APB1_PERIPH_CAN        
*\*\        - RCC_APB1_PERIPH_PWR        
*\*\return none. 
**/
void RCC_APB1_Peripheral_Clock_Enable(uint32_t APB1_periph)
{
    RCC->APB1PCLKEN |= APB1_periph;
}

/**
*\*\name    RCC_APB1_Peripheral_Clock_Disable.
*\*\fun     Disables the High Speed APB (APB1) peripheral clock.
*\*\param   APB1_periph (APB1 peripheral to gates its clock)：
*\*\        - RCC_APB1_PERIPH_TIM2       
*\*\        - RCC_APB1_PERIPH_TIM3       
*\*\        - RCC_APB1_PERIPH_TIM4       
*\*\        - RCC_APB1_PERIPH_TIM5       
*\*\        - RCC_APB1_PERIPH_TIM6       
*\*\        - RCC_APB1_PERIPH_COMP       
*\*\        - RCC_APB1_PERIPH_COMP_FILT  
*\*\        - RCC_APB1_PERIPH_WWDG       
*\*\        - RCC_APB1_PERIPH_USART2     
*\*\        - RCC_APB1_PERIPH_I2C1       
*\*\        - RCC_APB1_PERIPH_I2C2       
*\*\        - RCC_APB1_PERIPH_CAN        
*\*\        - RCC_APB1_PERIPH_PWR  
*\*\return none. 
**/
void RCC_APB1_Peripheral_Clock_Disable(uint32_t APB1_periph)
{
    RCC->APB1PCLKEN &= ~APB1_periph;
}

/**
*\*\name    RCC_AHB_Peripheral_Reset.
*\*\fun     AHB peripheral reset.
*\*\param   AHB_periph specifies the AHB peripheral to reset.    
*\*\         - RCC_AHB_PERIPH_GPIOA   
*\*\         - RCC_AHB_PERIPH_GPIOB   
*\*\         - RCC_AHB_PERIPH_GPIOC   
*\*\         - RCC_AHB_PERIPH_GPIOD   
*\*\         - RCC_AHB_PERIPH_ADC  
*\*\return none.
**/
void RCC_AHB_Peripheral_Reset(uint32_t AHB_periph)
{
    RCC->AHBPRST |= AHB_periph;
    RCC->AHBPRST &= ~AHB_periph;
}

/**
*\*\name    RCC_APB2_Peripheral_Reset.
*\*\fun     High Speed APB (APB2) peripheral reset.
*\*\param   APB2_periph specifies the APB2 peripheral to reset.
*\*\        - RCC_APB2_PERIPH_AFIO   
*\*\        - RCC_APB2_PERIPH_BEEPER 
*\*\        - RCC_APB2_PERIPH_TIM1   
*\*\        - RCC_APB2_PERIPH_SPI1   
*\*\        - RCC_APB2_PERIPH_TIM8   
*\*\        - RCC_APB2_PERIPH_USART1 
*\*\        - RCC_APB2_PERIPH_UART3  
*\*\        - RCC_APB2_PERIPH_UART4  
*\*\        - RCC_APB2_PERIPH_SPI2 
*\*\return none.
**/
void RCC_APB2_Peripheral_Reset(uint32_t APB2_periph)
{
    RCC->APB2PRST |= APB2_periph;
    RCC->APB2PRST &= ~APB2_periph;
}

/**
*\*\name    RCC_APB1_Peripheral_Reset.
*\*\fun     Low Speed APB (APB1) peripheral reset.
*\*\param   APB1_periph specifies the APB1 peripheral to reset.
*\*\        - RCC_APB1_PERIPH_TIM2       
*\*\        - RCC_APB1_PERIPH_TIM3       
*\*\        - RCC_APB1_PERIPH_TIM4       
*\*\        - RCC_APB1_PERIPH_TIM5       
*\*\        - RCC_APB1_PERIPH_TIM6       
*\*\        - RCC_APB1_PERIPH_COMP               
*\*\        - RCC_APB1_PERIPH_WWDG       
*\*\        - RCC_APB1_PERIPH_USART2     
*\*\        - RCC_APB1_PERIPH_I2C1       
*\*\        - RCC_APB1_PERIPH_I2C2       
*\*\        - RCC_APB1_PERIPH_CAN        
*\*\        - RCC_APB1_PERIPH_PWR  
*\*\return none. 
**/
void RCC_APB1_Peripheral_Reset(uint32_t APB1_periph)
{
    RCC->APB1PRST |= APB1_periph;
    RCC->APB1PRST &= ~APB1_periph;
}

/**
*\*\name    RCC_Backup_Reset.
*\*\fun     Backup domain reset.
*\*\param   none  
*\*\return  none. 
**/
void RCC_Backup_Reset(void)
{
    *(__IO uint32_t*)RCC_BDSFTRST_BITBAND = (uint32_t)ENABLE;
    *(__IO uint32_t*)RCC_BDSFTRST_BITBAND = (uint32_t)DISABLE;
}

/**
*\*\name   RCC_MCO_PLL_Prescaler_Config.
*\*\fun    Configures the MCO PLL clock prescaler.
*\*\param  MCO_PLL_prescaler(MCO PLL clock prescaler): 
*\*\        - RCC_MCO_PLLCLK_DIV2 
*\*\        - RCC_MCO_PLLCLK_DIV3 
*\*\        - RCC_MCO_PLLCLK_DIV4 
*\*\        - RCC_MCO_PLLCLK_DIV5 
*\*\        - RCC_MCO_PLLCLK_DIV6 
*\*\        - RCC_MCO_PLLCLK_DIV7 
*\*\        - RCC_MCO_PLLCLK_DIV8 
*\*\        - RCC_MCO_PLLCLK_DIV9 
*\*\        - RCC_MCO_PLLCLK_DIV10
*\*\        - RCC_MCO_PLLCLK_DIV11
*\*\        - RCC_MCO_PLLCLK_DIV12
*\*\        - RCC_MCO_PLLCLK_DIV13
*\*\        - RCC_MCO_PLLCLK_DIV14
*\*\        - RCC_MCO_PLLCLK_DIV15 
*\*\return  none. 
**/
void RCC_MCO_PLL_Prescaler_Config(uint32_t MCO_PLL_prescaler)
{
    uint32_t temp_value = 0;

    temp_value = RCC->CFG;
    /* Clear MCOPRE[3:0] bits */
    temp_value &= RCC_MCO_PLLCLK_DIV_MASK;
    /* Set MCOPRE[3:0] bits according to MCO_PLL_prescaler value */
    temp_value |= MCO_PLL_prescaler;

    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name   RCC_MCO_Source_Config.
*\*\fun    Selects the clock source to output on MCO pin.
*\*\param  MCO_source(clock source to output): 
*\*\     - RCC_MCO_NOCLK      
*\*\     - RCC_MCO_SYSCLK     
*\*\     - RCC_MCO_HSI        
*\*\     - RCC_MCO_HSE       
*\*\     - RCC_MCO_PLLCLK     
*\*\     - RCC_MCO_LSI     
*\*\     - RCC_MCO_LSE     
*\*\return  none. 
**/
void RCC_MCO_Source_Config(uint32_t MCO_source)
{
    uint32_t temp_value = 0;

    temp_value = RCC->CFG;
    /* Clear MCO[3:0] bits */
    temp_value &= RCC_MCO_MASK;
    /* Set MCO[3:0] bits according to MCO_source value */
    temp_value |= MCO_source;

    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_Flag_Status_Get.
*\*\fun     Checks whether the specified RCC flag is set or not.
*\*\param   RCC_flag:
*\*\	      - RCC_FLAG_HSIRD      HSI oscillator clock ready
*\*\          - RCC_FLAG_HSERD      HSE oscillator clock ready
*\*\	      - RCC_FLAG_PLLRD      PLL clock ready
*\*\	      - RCC_FLAG_LSERD      LSE oscillator clock ready
*\*\	      - RCC_FLAG_LSIRD      LSI oscillator clock ready
*\*\	      - RCC_FLAG_BKPEMC     BackUp EMC reset flag
*\*\	      - RCC_FLAG_MMURST     Mmu reset flag
*\*\	      - RCC_FLAG_PINRST     Pin reset
*\*\	      - RCC_FLAG_PORRST     POR/PDR reset
*\*\	      - RCC_FLAG_SFTRST     Software reset
*\*\	      - RCC_FLAG_IWDGRST    Independent Watchdog reset
*\*\	      - RCC_FLAG_WWDGRST    Window Watchdog reset
*\*\	      - RCC_FLAG_LPWRRST    Low Power reset
*\*\return  FlagStatus:
*\*\      	  - SET 
*\*\  	      - RESET
**/
FlagStatus RCC_Flag_Status_Get(uint8_t RCC_flag)
{
    uint32_t temp_value = 0;
    uint32_t reg_value  = 0;

    /* Get the RCC register index */
    temp_value = RCC_flag >> RCC_FLAG_OFFSET;
    switch(temp_value)
    {
        case 1: /* The flag to check is in CTRL register */
            reg_value = RCC->CTRL;
            break;
        case 2: /* The flag to check is in BDCTRL register */
           reg_value = RCC->BDCTRL;
           break;
        default:/* The flag to check is in CTRLSTS register */
            reg_value = RCC->CTRLSTS;
            break;
    }

    /* Get the flag position */
    temp_value = RCC_flag & RCC_FLAG_MASK;
    if ((reg_value & ((uint32_t)1 << temp_value)) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name    RCC_Reset_Flag_Clear.
*\*\fun     Clears the RCC reset flags.
*\*\param   none
*\*\return  none
**/
void RCC_Reset_Flag_Clear(void)
{
    /* Set RMRSTF bit to clear the reset flags */
    RCC->CTRLSTS |= RCC_REMOVE_RESET_FLAG;
    /* RMRSTF bit should be reset */
    RCC->CTRLSTS &= ~RCC_REMOVE_RESET_FLAG;
}

/**
*\*\name    RCC_Interrupt_Status_Get.
*\*\fun     Checks whether the specified RCC interrupt has occurred or not.
*\*\param   interrupt_flag(RCC interrupt source to check):
*\*\         - RCC_INT_LSIRDIF    LSI ready interrupt
*\*\         - RCC_INT_LSERDIF    LSE ready interrupt
*\*\         - RCC_INT_HSIRDIF    HSI ready interrupt
*\*\         - RCC_INT_HSERDIF    HSE ready interrupt
*\*\         - RCC_INT_PLLRDIF    PLL ready interrupt
*\*\         - RCC_INT_CLKSSIF    Clock Security System interrupt in HSE
*\*\         - RCC_INT_LSESSIF    Clock security system interrupt in LSE
*\*\return  The new state of RccInt 
*\*\         - SET
*\*\         - RESET
**/
INTStatus RCC_Interrupt_Status_Get(uint32_t interrupt_flag)
{

    /* Check the status of the specified RCC interrupt */
    if ((RCC->CLKINT & interrupt_flag) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name    RCC_Interrupt_Status_Clear.
*\*\fun     Clears the RCC's interrupt pending bits.
*\*\param   interrupt_clear(interrupt pending bit to clear):
*\*\         - RCC_INT_LSIRDICLR    LSI ready interrupt
*\*\         - RCC_INT_LSERDICLR    LSE ready interrupt
*\*\         - RCC_INT_HSIRDICLR    HSI ready interrupt
*\*\         - RCC_INT_HSERDICLR    HSE ready interrupt
*\*\         - RCC_INT_PLLRDICLR    PLL ready interrupt
*\*\         - RCC_INT_CLKSSICLR    Clock Security System interrupt in HSE
*\*\         - RCC_INT_LSESSICLR    Clock security system interrupt in LSE
*\*\return  none
**/
void RCC_Interrupt_Status_Clear(uint32_t interrupt_clear)
{
    /* Software set this bit to clear INT flag. */
    RCC->CLKINT |= interrupt_clear;
}


