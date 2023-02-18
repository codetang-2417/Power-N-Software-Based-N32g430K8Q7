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
*\*\file n32g430_rtc.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/
 
#include "n32g430_rtc.h"
#include "n32g430_rcc.h"
#include "stdio.h"

static void RTC_Hour_Format_Set(uint32_t hour_format);
static void RTC_Prescale_Config(uint32_t synch_prediv, uint32_t asynch_prediv);
static void RTC_Registers_Reset(void);
static uint8_t RTC_Byte_To_Bcd2(uint8_t Value);
static uint8_t RTC_Bcd2_To_Byte(uint8_t Value);

/**
*\*\name    RTC_Structure_Initializes.
*\*\fun     Fills each RTC_InitStruct member with its default value.
*\*\param   RTC_InitStruct :    RTC_InitStruct pointer to a RTC_InitType structure which will beinitialized. 
*\*\            - RTC_HourFormat
*\*\                - RTC_24HOUR_FORMAT
*\*\                - RTC_12HOUR_FORMAT
*\*\            - RTC_AsynchPrediv  the value must lower than 0x7F
*\*\            - RTC_SynchPrediv   the value must lower than 0x7FFF          
*\*\return  none
**/
void RTC_Structure_Initializes(RTC_InitType* RTC_InitStruct)
{
    /* Initialize the RTC_HourFormat member */
    RTC_InitStruct->RTC_HourFormat = RTC_24HOUR_FORMAT;
    /* Initialize the RTC_AsynchPrediv member */
    RTC_InitStruct->RTC_AsynchPrediv = (uint32_t)0x7F;
    /* Initialize the RTC_SynchPrediv member */
    RTC_InitStruct->RTC_SynchPrediv = (uint32_t)0xFF;
}

/**
*\*\name    RTC_Write_Protection_Enable.
*\*\fun     Enable the RTC registers write protection.
*\*\param   none
*\*\return  none
**/
void RTC_Write_Protection_Enable(void)
{
    /* Enable the write protection for RTC registers */
    RTC->WRP = 0xFF;
}

/**
*\*\name    RTC_Write_Protection_Disable.
*\*\fun     Disable the RTC registers write protection.
*\*\param   none
*\*\return  none
**/
void RTC_Write_Protection_Disable(void)
{
    /* Disable the write protection for RTC registers */
    RTC->WRP = 0xCA;
    RTC->WRP = 0x53;
}

/**
*\*\name    RTC_Initialization_Mode_Enter.
*\*\fun     Enters the RTC Initialization mode.
*\*\return   ErrorStatus
*\*\            - SUCCESS: RTC is in Init mode
*\*\            - ERROR: RTC is not in Init mode
**/
ErrorStatus RTC_Initialization_Mode_Enter(void)
{
    uint32_t temp_value = 0x00;
    uint32_t temp_value1 = 0x00;
    
    /* Check if the Initialization mode is set */
    if ((RTC->INITSTS & RTC_FLAG_INITF) == (uint32_t)RESET)
    {
        /* Set the Initialization mode */
        RTC->INITSTS = (uint32_t)RTC_FLAG_INITM;

        /* Wait untill RTC is in INIT state and if Time out is reached exit */
        do
        {
            temp_value1 = RTC->INITSTS & RTC_FLAG_INITF;
            temp_value++;
        } while ((temp_value != INITMODE_TIMEOUT) && (temp_value1 == 0x00));

        if ((RTC->INITSTS & RTC_FLAG_INITF) != RESET)
        {
            return SUCCESS;
        }
        else
        {
            return ERROR;
        }
    }
    else
    {
        return SUCCESS;
    }
}

/**
*\*\name    RTC_Initialization_Mode_Exit.
*\*\fun     When the initialization sequence is complete, the calendar restarts counting after 4 RTCCLK cycles.
*\*\return  none
**/
void RTC_Initialization_Mode_Exit(void)
{
    /* Exit Initialization mode */
    RTC->INITSTS &= (uint32_t)~RTC_FLAG_INITM;
}

/**
*\*\name    RTC_Hour_Format_Set.
*\*\fun     Set RTC hour format.
*\*\param   hour_format :
*\*\            - RTC_24HOUR_FORMAT
*\*\            - RTC_12HOUR_FORMAT
*\*\return  none
**/
static void RTC_Hour_Format_Set(uint32_t hour_format)
{
    /* Clear RTC CTRL HFMT Bit */
    RTC->CTRL &= ((uint32_t) ~(RTC_CTRL_HFMT));
    /* Set RTC_CTRL register */
    RTC->CTRL |= hour_format;
}

/**
*\*\name    RTC_Prescale_Config.
*\*\fun     Set RTC prescale.
*\*\param   synch_prediv    the value in the 0-0x7F range
*\*\param   asynch_prediv   the value in the 0-0x7FFF range
*\*\return  none
**/
static void RTC_Prescale_Config(uint32_t synch_prediv, uint32_t asynch_prediv)
{
    RTC->PRE = synch_prediv;
    RTC->PRE |= (uint32_t)(asynch_prediv << 16);
}

/**
*\*\name    RTC_Registers_Reset.
*\*\fun     Reset RTC registers.
*\*\param   none
*\*\return  none
**/
static void RTC_Registers_Reset(void)
{
    /* Reset RTC registers */
    RTC->CTRL   &= (uint32_t)0x00000000;
    RTC->WKUPT   = (uint32_t)0x0000FFFF;
    RTC->PRE     = (uint32_t)0x007F00FF;
    RTC->ALARMA  = (uint32_t)0x00000000;
    RTC->ALARMB  = (uint32_t)0x00000000;
    RTC->SCTRL   = (uint32_t)0x00000000;
    RTC->CALIB   = (uint32_t)0x00000000;
    RTC->ALRMASS = (uint32_t)0x00000000;
    RTC->ALRMBSS = (uint32_t)0x00000000;

    /* Reset INTSTS register and exit initialization mode */
    RTC->INITSTS = (uint32_t)0x00000000;

    RTC->OPT     = (uint32_t)0x00000000;
}

/**
*\*\name    RTC_Deinitializes.
*\*\fun     Deinitializes the RTC registers to their default reset values.
*\*\return  ErrorStatus
*\*\            - SUCCESS: RTC registers are deinitialized
*\*\            - ERROR: RTC registers are not deinitialized
*\*\
**/
ErrorStatus RTC_Deinitializes(void)
{
    uint32_t temp_value = 0x00;
    uint32_t temp_value1 = 0x00;
    ErrorStatus status_value = ERROR;

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Set Initialization mode */
    if (RTC_Initialization_Mode_Enter() == ERROR)
    {
        status_value = ERROR;
    }
    else
    {
        /* Reset TSH, DAT and CTRL registers */
        RTC->TSH  = (uint32_t)0x00000000;
        RTC->DATE = (uint32_t)0x00002101;

        /* Reset All CTRL bits except CTRL[2:0] */
        RTC->CTRL &= RTC_CTRL_WKUPSEL;

        /* Wait till RTC WTWF flag is set and if Time out is reached exit */
        do
        {
            temp_value1 = RTC->INITSTS & RTC_FLAG_WTWF;
            temp_value++;
        } while ((temp_value != INITMODE_TIMEOUT) && (temp_value1 == 0x00));

        if ((RTC->INITSTS & RTC_FLAG_WTWF) == RESET)
        {
            status_value = ERROR;
        }
        else
        {
            RTC_Registers_Reset();
            /* Wait till the RTC RSYF flag is set */
            if (RTC_Wait_For_Synchronization() == ERROR)
            {
                status_value = ERROR;
            }
            else
            {
                status_value = SUCCESS;
            }
        }
    }

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();

    return status_value;
}

/**
*\*\name    RTC_Wait_For_Resynchronization.
*\*\fun     Waits until the RTC Time and Date registers (RTC_TSH and RTC_DATE) are synchronized with RTC APB clock.
*\*\return  ErrorStatus :
*\*\            - SUCCESS:  RTC registers are synchronised
*\*\            - ERROR:    RTC registers are not synchronised
**/
ErrorStatus RTC_Wait_For_Synchronization(void)
{
    uint32_t temp_value = 0;    
    uint32_t temp_value1 = 0x00;
    ErrorStatus status_value = ERROR;

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Clear RSYF flag */
    RTC->INITSTS &= (uint32_t)RTC_RSF_MASK;

    /* Wait the registers to be synchronised */
    do
    {
        temp_value1 = RTC->INITSTS & RTC_FLAG_RSYF;
        temp_value++;
    } while ((temp_value != SYNCHRO_TIMEOUT) && (temp_value1 == 0x00));

    if ((RTC->INITSTS & RTC_FLAG_RSYF) != RESET)
    {
        status_value = SUCCESS;
    }
    else
    {
        status_value = ERROR;
    }

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();

    return status_value;
}

/**
*\*\name    RTC_Reference_Clock_Enable.
*\*\fun     Enables the RTC reference clock detection.
*\*\param   none
*\*\return  none 
**/
ErrorStatus RTC_Reference_Clock_Enable(void)
{
    ErrorStatus status_value = ERROR;

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Set Initialization mode */
    if (RTC_Initialization_Mode_Enter() == ERROR)
    {
        status_value = ERROR;
    }
    else
    {
        /* Enable the RTC reference clock detection */
        RTC->CTRL |= RTC_REFERENCE_DETECT_ENABLE;

        /* Exit Initialization mode */
        RTC_Initialization_Mode_Exit();

        status_value = SUCCESS;
    }

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();

    return status_value;
}


/**
*\*\name    RTC_Reference_Clock_Disable.
*\*\fun     Disables the RTC reference clock detection.
*\*\param   none
*\*\return  none 
**/
ErrorStatus RTC_Reference_Clock_Disable(void)
{
    ErrorStatus status_value = ERROR;

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Set Initialization mode */
    if (RTC_Initialization_Mode_Enter() == ERROR)
    {
        status_value = ERROR;
    }
    else
    {
        /* Disable the RTC reference clock detection */
        RTC->CTRL &= ~RTC_REFERENCE_DETECT_ENABLE;

        /* Exit Initialization mode */
        RTC_Initialization_Mode_Exit();

        status_value = SUCCESS;
    }

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();

    return status_value;
}

/**
*\*\name    RTC_By_Pass_Shadow_Enable.
*\*\fun     Calendar value read from Calendar register.
*\*\param   none
*\*\return  none 
**/
void RTC_Bypass_Shadow_Enable(void)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Set the BYPS bit */
    RTC->CTRL |= (uint8_t)RTC_BYPASS_UPDATE;
    
    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_By_Pass_Shadow_Disable.
*\*\fun     Calendar value read from Shadow register.
*\*\param   none
*\*\return  none 
**/
void RTC_Bypass_Shadow_Disable(void)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Reset the BYPS bit */
    RTC->CTRL &= (uint8_t)~RTC_BYPASS_UPDATE;

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_Time_Struct_Initializes.
*\*\fun     Fills each RTC_TimeStruct member with its default value
*\*\        (Time = 00h:00min:00sec).
*\*\param   RTC_TimeStruct : RTC_TimeStruct pointer to a RTC_TimeType structure that contains
*\*\                         the time configuration information for the RTC.
*\*\            - Hours
*\*\                - if RTC_AM_H12 is select the value in the 0-23 range
*\*\                - if RTC_PM_H12 is select the value in the 1-12 range
*\*\            - Minutes  the value set in the 0-59 range
*\*\            - Seconds  the value set in the 0-59 range
*\*\            - H12
*\*\                - RTC_AM_H12
*\*\                - RTC_PM_H12
*\*\return  none 
**/
void RTC_Time_Struct_Initializes(RTC_TimeType* RTC_TimeStruct)
{
    /* Time = 00h:00min:00sec */
    RTC_TimeStruct->H12     = RTC_AM_H12;
    RTC_TimeStruct->Hours   = 0;
    RTC_TimeStruct->Minutes = 0;
    RTC_TimeStruct->Seconds = 0;
}

/**
*\*\name    RTC_Time_Get.
*\*\fun     Get the RTC current Time.
*\*\param   RTC_Format : specifies the format of the returned parameters.
*\*\            - RTC_FORMAT_BIN 
*\*\            - RTC_FORMAT_BCD 
*\*\param   RTC_TimeStruct : RTC_TimeStruct pointer to a RTC_TimeType structure.
*\*\return  none 
**/
void RTC_Time_Get(uint32_t RTC_Format, RTC_TimeType* RTC_TimeStruct)
{
    uint32_t temp_value = 0;

    /* Get the RTC_TSH register */
    temp_value = (uint32_t)(RTC->TSH & RTC_TR_RESERVED_MASK);

    /* Fill the structure fields with the read parameters */
    RTC_TimeStruct->Hours   = (uint8_t)((temp_value & (RTC_TSH_HOT | RTC_TSH_HOU)) >> 16);
    RTC_TimeStruct->Minutes = (uint8_t)((temp_value & (RTC_TSH_MIT | RTC_TSH_MIU)) >> 8);
    RTC_TimeStruct->Seconds = (uint8_t)(temp_value & (RTC_TSH_SCT | RTC_TSH_SCU));
    RTC_TimeStruct->H12     = (uint8_t)((temp_value & (RTC_TSH_APM)) >> 16);

    /* Check the input parameters format */
    if (RTC_Format == RTC_FORMAT_BIN)
    {
        /* Convert the structure parameters to Binary format */
        RTC_TimeStruct->Hours   = (uint8_t)RTC_Bcd2_To_Byte(RTC_TimeStruct->Hours);
        RTC_TimeStruct->Minutes = (uint8_t)RTC_Bcd2_To_Byte(RTC_TimeStruct->Minutes);
        RTC_TimeStruct->Seconds = (uint8_t)RTC_Bcd2_To_Byte(RTC_TimeStruct->Seconds);
    }
}

/**
*\*\name    RTC_SubSecond_Get.
*\*\fun     Gets the RTC current Calendar Subseconds value.
*\*\return  RTC current Calendar Subseconds value. 
**/
uint32_t RTC_SubSecond_Get(void)
{
    /* Get subseconds values from the correspondent registers*/
    return RTC->SUBS;
}

#ifdef RTC_DELAY_USE_TIM6
#define RTC_DELAY_1S_PRESCALER_VALUE_TIM6 (100)
#define RTC_DELAY_1S_RELOAD_VALUE_TIM6    (SystemClockFrequency/1000)
static NVIC_InitType TIM6_NVIC_Init;
#else
#define RTC_DELAY_1S_RELOAD_VALUE_SYSTICK (SystemClockFrequency/10)
#endif

volatile uint32_t RTC_Delay_Flag = 0;

/**
*\*\name    RTC_Calendar_Initializes.
*\*\fun     Calendar initialization configuration.
*\*\param   RTC_Format : specifies the format of the returned parameters.
*\*\          - RTC_FORMAT_BIN 
*\*\          - RTC_FORMAT_BCD 
*\*\param   RTC_InitStruct: pointer to a RTC_InitType structure that contains the configuration
*\*\        information for the RTC peripheral.When the user does not need to configure this 
*\*\        parameter, note that NULL can be passed in. 
*\*\            - RTC_HourFormat
*\*\                - RTC_24HOUR_FORMAT
*\*\                - RTC_12HOUR_FORMAT
*\*\            - RTC_AsynchPrediv  the value in the 0-0x7F range
*\*\            - RTC_SynchPrediv   the value in the 0-0x7FFF range
*\*\param   RTC_DateStruct : RTC_DateStruct pointer to a RTC_DateType structure that contains
*\*\        the date configuration information for the RTC,note that NULL can be passed in.
*\*\            - WeekDay 
*\*\                - RTC_WEEKDAY_MONDAY
*\*\                - RTC_WEEKDAY_TUESDAY
*\*\                - RTC_WEEKDAY_WEDNESDAY
*\*\                - RTC_WEEKDAY_THURSDAY
*\*\                - RTC_WEEKDAY_FRIDAY
*\*\                - RTC_WEEKDAY_SATURDAY
*\*\                - RTC_WEEKDAY_SUNDAY
*\*\            - Month 
*\*\                - RTC_MONTH_JANUARY
*\*\                - RTC_MONTH_FEBRURY
*\*\                - RTC_MONTH_MARCH
*\*\                - RTC_MONTH_APRIL
*\*\                - RTC_MONTH_MAY
*\*\                - RTC_MONTH_JUNE
*\*\                - RTC_MONTH_JULY
*\*\                - RTC_MONTH_AUGUST
*\*\                - RTC_MONTH_SEPTEMBER
*\*\                - RTC_MONTH_OCTOBER
*\*\                - RTC_MONTH_NOVEMBER
*\*\                - RTC_MONTH_DECEMBER
*\*\            - Date    the value in the 1-31 range 
*\*\            - Year    the value in the 0-99 range
*\*\param   RTC_TimeStruct : RTC_TimeStruct pointer to a RTC_TimeType structure that contains
*\*\        the time configuration information for the RTC.When the user does not need to configure this 
*\*\        parameter, note that NULL can be passed in.
*\*\            - Hours
*\*\                - if RTC_AM_H12 is select the value in the 0-23 range
*\*\                - if RTC_PM_H12 is select the value in the 1-12 range
*\*\            - Minutes  the value set in the 0-59 range
*\*\            - Seconds  the value set in the 0-59 range
*\*\            - H12
*\*\                - RTC_AM_H12
*\*\                - RTC_PM_H12
*\*\param   RTC_DelayCmd: Enable or disable 1 second delay.
*\*\        This parameter can be: ENABLE or DISABLE.
*\*\  Note: 1. This parameter is configured according to the user's needs. If the user needs
*\*\        to call this function multiple times within 1 second to configure the calendar, it must
*\*\        be enabled, because we stipulate that the interval between two calendar configurations 
*\*\        must be at least 1 second.
*\*\        2. If this parameter is enabled, We provide two timers to help users complete this delay 
*\*\        operation (SysTick and TIM6). Users can choose which timer to use according to their needs,
*\*\        and use the macro RTC_DELAY_USE_TIM6 to select. At the same time, the user should also pay  
*\*\        attention to the usage of the watchdog. If necessary, the dog can be fed in the interrupt 
*\*\        handler to prevent the watchdog generating a system reset due to the delay in this function.
*\*\return  ErrorStatus
*\*\            - SUCCESS:  RTC PRE register, Date register, Time register is configured
*\*\            - ERROR:    RTC PRE register, Date register, Time register is not configured
**/
ErrorStatus RTC_Calendar_Initializes(uint32_t RTC_Format, RTC_InitType* RTC_InitStruct, RTC_DateType* RTC_DateStruct, RTC_TimeType* RTC_TimeStruct, FunctionalState RTC_DelayCmd)
{
    static uint32_t first_init_flag = 1;
    uint32_t temp_value1 = 0, temp_value2 = 0;
    ErrorStatus status_value    = ERROR;
    
    if(RTC_DateStruct != NULL)
    {
        if ((RTC_Format == RTC_FORMAT_BIN) && ((RTC_DateStruct->Month & 0x10) == 0x10))
        {
            RTC_DateStruct->Month = (RTC_DateStruct->Month & (uint32_t) ~(0x10)) + 0x0A;
        }
    }
    
    /* Check the input parameters format */
    if (RTC_Format != RTC_FORMAT_BIN)
    {
        if(RTC_DateStruct != NULL)
        {
            temp_value1 = ((((uint32_t)RTC_DateStruct->Year) << 16) | (((uint32_t)RTC_DateStruct->Month) << 8)
                       | ((uint32_t)RTC_DateStruct->Date) | (((uint32_t)RTC_DateStruct->WeekDay) << 13));
        }
        
        if(RTC_TimeStruct != NULL)
        {
            temp_value2 = (((uint32_t)(RTC_TimeStruct->Hours) << 16) | ((uint32_t)(RTC_TimeStruct->Minutes) << 8)
                       | ((uint32_t)RTC_TimeStruct->Seconds) | ((uint32_t)(RTC_TimeStruct->H12) << 16));
        }
    }
    else
    {
        if(RTC_DateStruct != NULL)
        {
            temp_value1 = (((uint32_t)RTC_Byte_To_Bcd2(RTC_DateStruct->Year) << 16)
                       | ((uint32_t)RTC_Byte_To_Bcd2(RTC_DateStruct->Month) << 8)
                       | ((uint32_t)RTC_Byte_To_Bcd2(RTC_DateStruct->Date)) | ((uint32_t)RTC_DateStruct->WeekDay << 13));
        }
        
        if(RTC_TimeStruct != NULL)
        {
            temp_value2 = (uint32_t)(((uint32_t)RTC_Byte_To_Bcd2(RTC_TimeStruct->Hours) << 16)
                       | ((uint32_t)RTC_Byte_To_Bcd2(RTC_TimeStruct->Minutes) << 8)
                       | ((uint32_t)RTC_Byte_To_Bcd2(RTC_TimeStruct->Seconds)) | (((uint32_t)RTC_TimeStruct->H12) << 16));
        }
    }

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    if(RTC_DelayCmd == ENABLE)
    {
        /* The first initialization does not execute the delay */
        if(!first_init_flag)
        {
            /* Wait for the 1.1 second delay flag to be set */
            while(!RTC_Delay_Flag);
            RTC_Delay_Flag = 0;
        }
    }
    /* Set Initialization mode */
    if (RTC_Initialization_Mode_Enter() == ERROR)
    {
        status_value = ERROR;
    }
    else
    {
        if(RTC_InitStruct != NULL)
        {
            /* Set rtc hour format*/
            RTC_Hour_Format_Set(RTC_InitStruct->RTC_HourFormat);
            /* Configure the RTC PRE */
            RTC_Prescale_Config(RTC_InitStruct->RTC_SynchPrediv, RTC_InitStruct->RTC_AsynchPrediv);
        }

        if(RTC_DateStruct != NULL)
        {
            /* Set the RTC_DATE register */
            RTC->DATE = (uint32_t)(temp_value1 & RTC_DATE_RESERVED_MASK);
        }

        if(RTC_TimeStruct != NULL)
        {
            /* Set the RTC_TSH register */
            RTC->TSH = (uint32_t)(temp_value2 & RTC_TR_RESERVED_MASK);
        }
        
        /* Exit Initialization mode */
        RTC_Initialization_Mode_Exit();

        /* If  RTC_CTRL_BYPS bit = 0, wait for synchro else this check is not needed */
        if ((RTC->CTRL & RTC_CTRL_BYPS) == RESET)
        {
            if (RTC_Wait_For_Synchronization() == ERROR)
            {
                status_value = ERROR;
            }
            else
            {
                status_value = SUCCESS;
            }
        }
        else
        {
            status_value = SUCCESS;
        }
        
        if(RTC_DelayCmd == ENABLE)
        {
            if(first_init_flag)
            {
                /* Clear the first initialization flag */
                first_init_flag = 0;
            }
            
#ifdef RTC_DELAY_USE_TIM6
            /* Set Interrupt Priority */            
            TIM6_NVIC_Init.NVIC_IRQChannel = TIM6_IRQn;
            TIM6_NVIC_Init.NVIC_IRQChannelPreemptionPriority = 0;
            TIM6_NVIC_Init.NVIC_IRQChannelSubPriority = 1;
            TIM6_NVIC_Init.NVIC_IRQChannelCmd = ENABLE;
            NVIC_Initializes(&TIM6_NVIC_Init);
            /* Enable the TIM6 clock*/
            RCC->APB1PCLKEN |= RCC_APB1_PERIPH_TIM6;
            RCC->APB1PRST |= RCC_APB1_PERIPH_TIM6;
            RCC->APB1PRST &= ~RCC_APB1_PERIPH_TIM6;
            /* Set the Autoreload value */
            TIM6->AR = RTC_DELAY_1S_RELOAD_VALUE_TIM6;
            /* Prescaler configuration */
            TIM6->PSC = RTC_DELAY_1S_PRESCALER_VALUE_TIM6 - 1;
            /* Set or reset the UG Bit */
            TIM6->EVTGEN = TIM_PSC_RELOAD_MODE_IMMEDIATE;
            /* TIM6 enable update irq */
            TIM6->DINTEN |= TIM_INT_UPDATE;
            /* Clear the flag */
            TIM6->STS &= (uint32_t)~TIM_FLAG_UPDATE;
            /* TIM6 enable counter */
            TIM6->CTRL1 |= TIM_CTRL1_CNTEN;
#else
            /* Set Interrupt Priority */
            NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
            /* set reload register */
            SysTick->LOAD  = (RTC_DELAY_1S_RELOAD_VALUE_SYSTICK & SysTick_LOAD_RELOAD_Msk) - 1;
            /* Load the SysTick Counter Value */
            SysTick->VAL   = 0;
            /* Enable SysTick IRQ and SysTick Timer */
            SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                             SysTick_CTRL_TICKINT_Msk   |
                             SysTick_CTRL_ENABLE_Msk;
#endif
        }
    }
    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();

    return status_value;
}


/**
*\*\name    RTC_Date_Struct_Initializes.
*\*\fun     Fills each RTC_DateStruct member with its default value (Monday, January 01 xx00).
*\*\param   RTC_DateStruct : RTC_DateStruct pointer to a RTC_DateType structure that contains
*\*\                       the date configuration information for the RTC.
*\*\            - WeekDay 
*\*\                - RTC_WEEKDAY_MONDAY
*\*\                - RTC_WEEKDAY_TUESDAY
*\*\                - RTC_WEEKDAY_WEDNESDAY
*\*\                - RTC_WEEKDAY_THURSDAY
*\*\                - RTC_WEEKDAY_FRIDAY
*\*\                - RTC_WEEKDAY_SATURDAY
*\*\                - RTC_WEEKDAY_SUNDAY
*\*\            - Month 
*\*\                - RTC_MONTH_JANUARY
*\*\                - RTC_MONTH_FEBRURY
*\*\                - RTC_MONTH_MARCH
*\*\                - RTC_MONTH_APRIL
*\*\                - RTC_MONTH_MAY
*\*\                - RTC_MONTH_JUNE
*\*\                - RTC_MONTH_JULY
*\*\                - RTC_MONTH_AUGUST
*\*\                - RTC_MONTH_SEPTEMBER
*\*\                - RTC_MONTH_OCTOBER
*\*\                - RTC_MONTH_NOVEMBER
*\*\                - RTC_MONTH_DECEMBER
*\*\            - Date    the value in the 1-31 range 
*\*\            - Year    the value in the 0-99 range
*\*\return  none 
**/
void RTC_Date_Struct_Initializes(RTC_DateType* RTC_DateStruct)
{
    /* Monday, January 01 xx00 */
    RTC_DateStruct->WeekDay = RTC_WEEKDAY_MONDAY;
    RTC_DateStruct->Date    = 1;
    RTC_DateStruct->Month   = RTC_MONTH_JANUARY;
    RTC_DateStruct->Year    = 0;
}

/**
*\*\name    RTC_Date_Get.
*\*\fun      Get the RTC current date.
*\*\param   RTC_Format : specifies the format of the returned parameters.
*\*\            - RTC_FORMAT_BIN 
*\*\            - RTC_FORMAT_BCD 
*\*\param   RTC_DateType : RTC_DateStruct pointer to a RTC_DateType structure that will
*\*\                       contain the returned current date configuration.
*\*\return  none 
**/
void RTC_Date_Get(uint32_t RTC_Format, RTC_DateType* RTC_DateStruct)
{
    uint32_t temp_value = 0;

    /* Get the RTC_TSH register */
    temp_value = (uint32_t)(RTC->DATE & RTC_DATE_RESERVED_MASK);

    /* Fill the structure fields with the read parameters */
    RTC_DateStruct->Year    = (uint8_t)((temp_value & (RTC_DATE_YRT | RTC_DATE_YRU)) >> 16);
    RTC_DateStruct->Month   = (uint8_t)((temp_value & (RTC_DATE_MOT | RTC_DATE_MOU)) >> 8);
    RTC_DateStruct->Date    = (uint8_t)(temp_value & (RTC_DATE_DAT | RTC_DATE_DAU));
    RTC_DateStruct->WeekDay = (uint8_t)((temp_value & (RTC_DATE_WDU)) >> 13);

    /* Check the input parameters format */
    if (RTC_Format == RTC_FORMAT_BIN)
    {
        /* Convert the structure parameters to Binary format */
        RTC_DateStruct->Year  = (uint8_t)RTC_Bcd2_To_Byte(RTC_DateStruct->Year);
        RTC_DateStruct->Month = (uint8_t)RTC_Bcd2_To_Byte(RTC_DateStruct->Month);
        RTC_DateStruct->Date  = (uint8_t)RTC_Bcd2_To_Byte(RTC_DateStruct->Date);
    }
}

/**
*\*\name    RTC_Alarm_Set.
*\*\fun     Set the specified RTC Alarm.
*\*\param   RTC_Format : specifies the format of the returned parameters.
*\*\            - RTC_FORMAT_BIN 
*\*\            - RTC_FORMAT_BCD 
*\*\param   RTC_Alarm : RTC_Alarm specifies the alarm to be configured.
*\*\            - RTC_A_ALARM 
*\*\            - RTC_B_ALARM 
*\*\param   RTC_AlarmStruct : RTC_AlarmStruct pointer to a RTC_AlarmType structure that
*\*\                          contains the alarm configuration parameters.
*\*\            - AlarmTime   RTC_TimeStruct pointer to a RTC_TimeType structure that contains
*\*\                         the time configuration information for the RTC.
*\*\            - Hours
*\*\                - if RTC_AM_H12 is select the value in the 0-23 range
*\*\                - if RTC_PM_H12 is select the value in the 1-12 range
*\*\            - Minutes  the value set in the 0-59 range
*\*\            - Seconds  the value set in the 0-59 range
*\*\            - H12
*\*\                - RTC_AM_H12
*\*\                - RTC_PM_H12
*\*\            - AlarmMask 
*\*\                - RTC_ALARMMASK_NONE
*\*\                - RTC_ALARMMASK_WEEKDAY
*\*\                - RTC_ALARMMASK_HOURS
*\*\                - RTC_ALARMMASK_MINUTES
*\*\                - RTC_ALARMMASK_SECONDS
*\*\                - RTC_ALARMMASK_ALL
*\*\            - DateWeekMode 
*\*\                - RTC_ALARM_SEL_WEEKDAY_DATE
*\*\                - RTC_ALARM_SEL_WEEKDAY_WEEKDAY
*\*\            - DateWeekValue 
*\*\                - RTC_WEEKDAY_MONDAY
*\*\                - RTC_WEEKDAY_TUESDAY
*\*\                - RTC_WEEKDAY_WEDNESDAY
*\*\                - RTC_WEEKDAY_THURSDAY
*\*\                - RTC_WEEKDAY_FRIDAY
*\*\                - RTC_WEEKDAY_SATURDAY
*\*\                - RTC_WEEKDAY_SUNDAY
*\*\return  none 
**/
void RTC_Alarm_Set(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmType* RTC_AlarmStruct)
{
    uint32_t temp_value = 0;

    if (RTC_Format == RTC_FORMAT_BIN)
    {
        if ((RTC->CTRL & RTC_CTRL_HFMT) == (uint32_t)RESET)
        {
            RTC_AlarmStruct->AlarmTime.H12 = 0x00;
        }
    }
    else
    {
        if ((RTC->CTRL & RTC_CTRL_HFMT) == (uint32_t)RESET)
        {
            RTC_AlarmStruct->AlarmTime.H12 = 0x00;
        }
    }

    /* Check the input parameters format */
    if (RTC_Format != RTC_FORMAT_BIN)
    {
        temp_value =
            (((uint32_t)(RTC_AlarmStruct->AlarmTime.Hours) << 16)
             | ((uint32_t)(RTC_AlarmStruct->AlarmTime.Minutes) << 8) | ((uint32_t)RTC_AlarmStruct->AlarmTime.Seconds)
             | ((uint32_t)(RTC_AlarmStruct->AlarmTime.H12) << 16) | ((uint32_t)(RTC_AlarmStruct->DateWeekValue) << 24)
             | ((uint32_t)RTC_AlarmStruct->DateWeekMode) | ((uint32_t)RTC_AlarmStruct->AlarmMask));
    }
    else
    {
        temp_value = (((uint32_t)RTC_Byte_To_Bcd2(RTC_AlarmStruct->AlarmTime.Hours) << 16)
                       | ((uint32_t)RTC_Byte_To_Bcd2(RTC_AlarmStruct->AlarmTime.Minutes) << 8)
                       | ((uint32_t)RTC_Byte_To_Bcd2(RTC_AlarmStruct->AlarmTime.Seconds))
                       | ((uint32_t)(RTC_AlarmStruct->AlarmTime.H12) << 16)
                       | ((uint32_t)RTC_Byte_To_Bcd2(RTC_AlarmStruct->DateWeekValue) << 24)
                       | ((uint32_t)RTC_AlarmStruct->DateWeekMode) | ((uint32_t)RTC_AlarmStruct->AlarmMask));
    }

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Configure the Alarm register */
    if (RTC_Alarm == RTC_A_ALARM)
    {
        RTC->ALARMA = (uint32_t)temp_value;
    }
    else
    {
        RTC->ALARMB = (uint32_t)temp_value;
    }

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_Alarm_Struct_Initializes.
*\*\fun     Fills each RTC_AlarmStruct member with its default value
*\*\        (Time = 00h:00mn:00sec / Date = 1st day of the month/Mask =
*\*\        all fields are masked).
*\*\param   RTC_AlarmStruct : RTC_AlarmStruct pointer to a RTC_AlarmType structure that
*\*\                          contains the alarm configuration parameters.
*\*\            - AlarmTime   RTC_TimeStruct pointer to a RTC_TimeType structure that contains
*\*\                         the time configuration information for the RTC.
*\*\            - Hours
*\*\                - if RTC_AM_H12 is select the value in the 0-23 range
*\*\                - if RTC_PM_H12 is select the value in the 1-12 range
*\*\            - Minutes  the value set in the 0-59 range
*\*\            - Seconds  the value set in the 0-59 range
*\*\            - H12
*\*\                - RTC_AM_H12
*\*\                - RTC_PM_H12
*\*\            - AlarmMask 
*\*\                - RTC_ALARMMASK_NONE
*\*\                - RTC_ALARMMASK_WEEKDAY
*\*\                - RTC_ALARMMASK_HOURS
*\*\                - RTC_ALARMMASK_MINUTES
*\*\                - RTC_ALARMMASK_SECONDS
*\*\                - RTC_ALARMMASK_ALL
*\*\            - DateWeekMode 
*\*\                - RTC_ALARM_SEL_WEEKDAY_DATE
*\*\                - RTC_ALARM_SEL_WEEKDAY_WEEKDAY
*\*\            - DateWeekValue 
*\*\                - RTC_WEEKDAY_MONDAY
*\*\                - RTC_WEEKDAY_TUESDAY
*\*\                - RTC_WEEKDAY_WEDNESDAY
*\*\                - RTC_WEEKDAY_THURSDAY
*\*\                - RTC_WEEKDAY_FRIDAY
*\*\                - RTC_WEEKDAY_SATURDAY
*\*\                - RTC_WEEKDAY_SUNDAY
*\*\return  none 
**/
void RTC_Alarm_Struct_Initializes(RTC_AlarmType* RTC_AlarmStruct)
{
    /* Alarm Time Settings : Time = 00h:00mn:00sec */
    RTC_AlarmStruct->AlarmTime.H12     = RTC_AM_H12;
    RTC_AlarmStruct->AlarmTime.Hours   = 0;
    RTC_AlarmStruct->AlarmTime.Minutes = 0;
    RTC_AlarmStruct->AlarmTime.Seconds = 0;

    /* Alarm Date Settings : Date = 1st day of the month */
    RTC_AlarmStruct->DateWeekMode  = RTC_ALARM_SEL_WEEKDAY_DATE;
    RTC_AlarmStruct->DateWeekValue = 1;

    /* Alarm Masks Settings : Mask =  all fields are not masked */
    RTC_AlarmStruct->AlarmMask = RTC_ALARMMASK_NONE;
}

/**
*\*\name    RTC_Alarm_Get.
*\*\fun     Get the RTC Alarm value and masks.
*\*\param   RTC_Format : specifies the format of the output parameters.
*\*\            - RTC_FORMAT_BIN 
*\*\            - RTC_FORMAT_BCD 
*\*\param   RTC_Alarm : specifies the alarm to be read.
*\*\            - RTC_A_ALARM 
*\*\            - RTC_B_ALARM 
*\*\param   RTC_AlarmStruct : pointer to a RTC_AlarmType structure that will
*\*\        contains the output alarm configuration values.
*\*\          
*\*\return  none 
**/
void RTC_Alarm_Get(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmType* RTC_AlarmStruct)
{
    uint32_t temp_value = 0;

    /* Get the RTC_ALARMx register */
    if (RTC_Alarm == RTC_A_ALARM)
    {
        temp_value = (uint32_t)(RTC->ALARMA);
    }
    else
    {
        temp_value = (uint32_t)(RTC->ALARMB);
    }

    /* Fill the structure with the read parameters */
    RTC_AlarmStruct->AlarmTime.Hours   = (uint32_t)((temp_value & (RTC_ALARMA_HOT | RTC_ALARMA_HOU)) >> 16);
    RTC_AlarmStruct->AlarmTime.Minutes = (uint32_t)((temp_value & (RTC_ALARMA_MIT | RTC_ALARMA_MIU)) >> 8);
    RTC_AlarmStruct->AlarmTime.Seconds = (uint32_t)(temp_value & (RTC_ALARMA_SET | RTC_ALARMA_SEU));
    RTC_AlarmStruct->AlarmTime.H12     = (uint32_t)((temp_value & RTC_ALARMA_APM) >> 16);
    RTC_AlarmStruct->DateWeekValue     = (uint32_t)((temp_value & (RTC_ALARMA_DTT | RTC_ALARMA_DTU)) >> 24);
    RTC_AlarmStruct->DateWeekMode      = (uint32_t)(temp_value & RTC_ALARMA_WKDSEL);
    RTC_AlarmStruct->AlarmMask         = (uint32_t)(temp_value & RTC_ALARMMASK_ALL);
    
    if (RTC_Format == RTC_FORMAT_BIN)
    {
        RTC_AlarmStruct->AlarmTime.Hours   = RTC_Bcd2_To_Byte(RTC_AlarmStruct->AlarmTime.Hours);
        RTC_AlarmStruct->AlarmTime.Minutes = RTC_Bcd2_To_Byte(RTC_AlarmStruct->AlarmTime.Minutes);
        RTC_AlarmStruct->AlarmTime.Seconds = RTC_Bcd2_To_Byte(RTC_AlarmStruct->AlarmTime.Seconds);
        RTC_AlarmStruct->DateWeekValue     = RTC_Bcd2_To_Byte(RTC_AlarmStruct->DateWeekValue);
    }
}

/**
*\*\name    RTC_Alarm_Enable.
*\*\fun     Enable the specified RTC Alarm.
*\*\param   RTC_Alarm : specifies the alarm to be configured.
*\*\            - RTC_A_ALARM 
*\*\            - RTC_B_ALARM 
*\*\return  ErrorStatus : 
*\*\            - SUCCESS: RTC Alarm is Enable
*\*\            - ERROR:   RTC Alarm is not Enable
**/
ErrorStatus RTC_Alarm_Enable(uint32_t RTC_Alarm)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Configure the Alarm state */
    RTC->CTRL |= (uint32_t)RTC_Alarm;

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();

    return SUCCESS;
}
 
/**
*\*\name    RTC_Alarm_Disable.
*\*\fun     Disable the specified RTC Alarm.
*\*\param   RTC_Alarm : specifies the alarm to be configured.
*\*\            - RTC_A_ALARM 
*\*\            - RTC_B_ALARM 
*\*\return  ErrorStatus : An ErrorStatus enumeration value
*\*\          - SUCCESS: RTC Alarm is Disable
*\*\          - ERROR:   RTC Alarm is not Disable
**/
ErrorStatus RTC_Alarm_Disable(uint32_t RTC_Alarm)
{
    uint32_t temp_value = 0x00;
    uint32_t temp_value1 = 0x00;
    ErrorStatus status_value = ERROR;

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Disable the Alarm in RTC_CTRL register */
    RTC->CTRL &= (uint32_t)~RTC_Alarm;
    /* Wait till RTC ALxWF flag is set and if Time out is reached exit */
    do
    {
        temp_value1 = RTC->INITSTS & (RTC_Alarm >> 8);
        temp_value++;
    } while ((temp_value != INITMODE_TIMEOUT) && (temp_value1 == 0x00));
    if ((RTC->INITSTS & (RTC_Alarm >> 8)) == RESET)
    {
        status_value = SUCCESS;
    }
    else
    {
        status_value = ERROR;
    }
    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
    return status_value;
}


 /**
*\*\name    RTC_Alarm_SubSecond_Config.
*\*\fun     Configure the RTC AlarmA/B Subseconds value and mask
*\*\param   RTC_Alarm : specifies the alarm to be configured.
*\*\            - RTC_A_ALARM : select Alarm A.
*\*\            - RTC_B_ALARM : select Alarm B.
*\*\param   RTC_AlarmSubSecondValue : specifies the Subseconds value, the value in the 0-0x00007FFF range
*\*\param   RTC_AlarmSubSecondMask : specifies the Subseconds Mask.
*\*\            - RTC_SUBS_MASK_ALL     : Alarm SS fields are masked There is no comparison on sub seconds for Alarm.
*\*\            - RTC_SUBS_MASK_SS14_1  : SS[14:1] are don't care in Alarm comparison Only SS[0] is compared
*\*\            - RTC_SUBS_MASK_SS14_2  : SS[14:2] are don't care in Alarm comparison Only SS[1:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_3  : SS[14:3] are don't care in Alarm comparison Only SS[2:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_4  : SS[14:4] are don't care in Alarm comparison Only SS[3:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_5  : SS[14:5] are don't care in Alarm comparison Only SS[4:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_6  : SS[14:6] are don't care in Alarm comparison Only SS[5:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_7  : SS[14:7] are don't care in Alarm comparison Only SS[6:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_8  : SS[14:8] are don't care in Alarm comparison Only SS[7:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_9  : SS[14:9] are don't care in Alarm comparison Only SS[8:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_10 : SS[14:10] are don't care in Alarm comparison Only SS[9:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_11 : SS[14:11] are don't care in Alarm comparison Only SS[10:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_12 : SS[14:12] are don't care in Alarm comparison Only SS[11:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_13 : SS[14:13] are don't care in Alarm comparison Only SS[12:0] are compared
*\*\            - RTC_SUBS_MASK_SS14_14 : SS[14] is don't care in Alarm comparison Only SS[13:0] are compared.
*\*\            - RTC_SUBS_MASK_NONE    : SS[14:0] are compared and must match to activate alarm.
*\*\return  None
**/
void RTC_Alarm_SubSecond_Config(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint32_t RTC_AlarmSubSecondMask)
{
    uint32_t temp_value = 0;

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Configure the Alarm A or Alarm B SubSecond registers */
    temp_value = (uint32_t)(uint32_t)(RTC_AlarmSubSecondValue) | (uint32_t)(RTC_AlarmSubSecondMask);

    if (RTC_Alarm == RTC_A_ALARM)
    {
        /* Configure the AlarmA SubSecond register */
        RTC->ALRMASS = temp_value;
    }
    else
    {
        /* Configure the Alarm B SubSecond register */
        RTC->ALRMBSS = temp_value;
    }

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}


/**
*\*\name    RTC_Alarm_SubSecond_Get.
*\*\fun     Gets the RTC Alarm Subseconds value.
*\*\param   RTC_Alarm : specifies the alarm to be read.
*\*\            - RTC_A_ALARM : select Alarm A.
*\*\            - RTC_B_ALARM : select Alarm B.
*\*\return  RTC Alarm Subseconds value.
**/
uint32_t RTC_Alarm_SubSecond_Get(uint32_t RTC_Alarm)
{
    uint32_t temp_value = 0;

    /* Get the RTC_ALARMx register */
    if (RTC_Alarm == RTC_A_ALARM)
    {
        temp_value = (uint32_t)((RTC->ALRMASS) & RTC_ALRMASS_SSV);
    }
    else
    {
        temp_value = (uint32_t)((RTC->ALRMBSS) & RTC_ALRMBSS_SSV);
    }

    return (temp_value);
}


/**
*\*\name    RTC_WAKE_UP_CLOCK_Select.
*\*\fun     Configures the RTC Wakeup clock source.
*\*\param   RTC_WakeUpClock : RTC_WakeUpClock Wakeup Clock source.
*\*\            - RTC_WKUPCLK_RTCCLK_DIV16 : RTC Wakeup Counter Clock = RTCCLK/16.
*\*\            - RTC_WKUPCLK_RTCCLK_DIV8 : RTC Wakeup Counter Clock = RTCCLK/8.
*\*\            - RTC_WKUPCLK_RTCCLK_DIV4 : RTC Wakeup Counter Clock = RTCCLK/4.
*\*\            - RTC_WKUPCLK_RTCCLK_DIV2 : RTC Wakeup Counter Clock = RTCCLK/2.
*\*\            - RTC_WKUPCLK_CK_SPRE_16BITS : RTC Wakeup Counter Clock = CK_SPRE.
*\*\            - RTC_WKUPCLK_CK_SPRE_17BITS : RTC Wakeup Counter Clock = CK_SPRE,and wakeup timer count is 2^16.
*\*\return  none
**/
void RTC_WakeUp_Clock_Select(RTC_WAKE_UP_CLOCK RTC_WakeUp_Clock)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Clear the Wakeup Timer clock source bits in CTRL register */
    RTC->CTRL &= (uint32_t)~RTC_CTRL_WKUPSEL;

    /* Configure the clock source */
    RTC->CTRL |= (uint32_t)RTC_WakeUp_Clock;

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_WakeUp_Counter_Set.
*\*\fun     Configures the RTC Wakeup counter.
*\*\param   RTC_WakeUpCounter : specifies the WakeUp counter, the value in the 0-0xFFFF range
*\*\return  none
**/
void RTC_WakeUp_Counter_Set(uint32_t RTC_WakeUpCounter)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* wait subs synchronize*/
    while(RTC->SUBS != (RTC->PRE & 0X7FFF));
    /* Configure the Wakeup Timer counter */
    RTC->WKUPT = (uint32_t)RTC_WakeUpCounter;

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_WakeUp_Counter_Get.
*\*\fun     Returns the RTC WakeUp timer counter value.
*\*\return  The RTC WakeUp Counter value.
**/
uint32_t RTC_WakeUp_Counter_Get(void)
{
    /* Get the counter value */
    return ((uint32_t)(RTC->WKUPT & RTC_WKUPT_WKUPT));
}

/**
*\*\name    RTC_WakeUp_Enable
*\*\fun     Enable the RTC WakeUp timer.
*\*\param   none
*\*\return  SUCCESS
**/
ErrorStatus RTC_WakeUp_Enable(void)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Enable the Wakeup Timer */
    RTC->CTRL |= (uint32_t)RTC_CTRL_WTEN;
    
    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();

    return SUCCESS;
}

/**
*\*\name    RTC_WakeUp_Disable
*\*\fun     Disable the RTC WakeUp timer.
*\*\return  ErrorStatus
*\*\          - SUCCESS
*\*\          - ERROR
**/
ErrorStatus RTC_WakeUp_Disable(void)
{
    uint32_t temp_value = 0x00;
    uint32_t temp_value1 = 0x00;
    ErrorStatus status_value = ERROR;

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Disable the Wakeup Timer */
    RTC->CTRL &= (uint32_t)~RTC_CTRL_WTEN;
    /* Wait till RTC WTWF flag is set and if Time out is reached exit */
    do
    {
        temp_value1 = RTC->INITSTS & RTC_FLAG_WTWF;
        temp_value++;
    } while ((temp_value != INITMODE_TIMEOUT) && (temp_value1 == 0x00));

    if ((RTC->INITSTS & RTC_FLAG_WTWF) == RESET)
    {
        status_value = SUCCESS;
    }
    else
    {
        status_value = ERROR;
    }
    
    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();

    return status_value;
}

/**
*\*\name    RTC_Day_Light_Saving_Config
*\*\fun     Adds or substract one hour from the current time.
*\*\param   RTC_DayLightSaving : the value of hour adjustment.
*\*\            - RTC_DAYLIGHT_SAVING_SUB1H : Substract one hour (winter time).
*\*\            - RTC_DAYLIGHT_SAVING_ADD1H : Add one hour (summer time).
*\*\param   RTC_StoreOperation : Specifies the value to be written in the BCK bit
*\*\        in CTRL register to store the operation.
*\*\            - RTC_STORE_OPERATION_RESET :  BCK Bit Reset.
*\*\            - RTC_STORE_OPERATION_SET : BCK Bit Set.
*\*\return  none
**/
void RTC_Day_Light_Saving_Config(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Clear the bits to be configured */
    RTC->CTRL &= (uint32_t) ~(RTC_STORE_OPERATION_SET);
    /* Clear the SU1H and AD1H bits to be configured */
    RTC->CTRL &= (uint32_t) ~(RTC_DAYLIGHT_SAVING_SUB1H & RTC_DAYLIGHT_SAVING_ADD1H);
    /* Configure the RTC_CTRL register */
    RTC->CTRL |= (uint32_t)(RTC_DayLightSaving | RTC_StoreOperation);

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_Store_Operation_Get
*\*\fun     Returns the RTC Day Light Saving stored operation.
*\*\return  RTC Day Light Saving stored operation.
*\*\            - RTC_STORE_OPERATION_RESET
*\*\            - RTC_STORE_OPERATION_SET
**/
uint32_t RTC_Store_Operation_Get(void)
{
    return (RTC->CTRL & RTC_STORE_OPERATION_SET);
}

/**
*\*\name    RTC_Output_Config
*\*\fun     Configures the RTC output source (AFO_ALARM).
*\*\param   RTC_Output : RTC_Output Specifies which signal will be routed to the RTC output.
*\*\            - RTC_OUTPUT_DIS : No output selected
*\*\            - RTC_OUTPUT_ALA : signal of AlarmA mapped to output.
*\*\            - RTC_OUTPUT_ALB : signal of AlarmB mapped to output.
*\*\            - RTC_OUTPUT_WKUP: signal of WakeUp mapped to output.
*\*\param   RTC_OutputPolarity : Specifies the polarity of the output signal.
*\*\            - RTC_OUTPOL_HIGH: The output pin is high when the ALRAF/ALRBF/WUTF is high (depending on OSEL).
*\*\            - RTC_OUTPOL_LOW : The output pin is low when the ALRAF/ALRBF/WUTF is high (depending on OSEL).
*\*\return  none
**/
void RTC_Output_Config(uint32_t RTC_Output, uint32_t RTC_OutputPolarity)
{
    __IO uint32_t temp = 0;

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Clear the bits to be configured */
    RTC->CTRL &= (uint32_t) ~(RTC_CTRL_OUTSEL | RTC_CTRL_OPOL);

    /* Configure the output selection and polarity */
    RTC->CTRL |= (uint32_t)(RTC_Output | RTC_OutputPolarity);

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_Calibration_Output_Enable
*\*\fun     Enable the RTC clock to be output through the relative pin.
*\*\return  none
**/
void RTC_Calibration_Output_Enable(void)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Enable the RTC clock output */
    RTC->CTRL |= (uint32_t)RTC_CTRL_COEN;
    
    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_Calibration_Output_Disable
*\*\fun     Disable the RTC clock to be output through the relative pin.
*\*\return  none
**/
void RTC_Calibration_Output_Disable(void)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Disable the RTC clock output */
    RTC->CTRL &= (uint32_t)~RTC_CTRL_COEN;
    
    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_Calibration_Output_Config
*\*\fun     Configure the Calibration Pinout (RTC_CALIB) Selection (1Hz or 256Hz).
*\*\param   RTC_CalibOutput Select the Calibration output Selection .
*\*\            - RTC_CALIB_OUTPUT_256HZ : A signal has a regular waveform at 256Hz.
*\*\            - RTC_CALIB_OUTPUT_1HZ   : A signal has a regular waveform at 1Hz.
*\*\return  none
**/
void RTC_Calibration_Output_Config(uint32_t RTC_CalibOutput)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /*clear flags before config*/
    RTC->CTRL &= (uint32_t) ~(RTC_CTRL_CALOSEL);

    /* Configure the RTC_CTRL register */
    RTC->CTRL |= (uint32_t)RTC_CalibOutput;

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_Smooth_Calibration_Config
*\*\fun     Configures the Smooth Calibration Settings.
*\*\param   RTC_SmoothCalibPeriod : RTC_SmoothCalibPeriod Select the Smooth Calibration Period.
*\*\            - SMOOTH_CALIB_32SEC : The smooth calibration periode is 32s.
*\*\            - SMOOTH_CALIB_16SEC : The smooth calibration periode is 16s.
*\*\            - SMOOTH_CALIB_8SEC  : The smooth calibartion periode is 8s.
*\*\param   RTC_SmoothCalibPlusPulses : Set or reset the CALP bit.
*\*\            - RTC_SMOOTH_CALIB_PLUS_PULSES_SET : Add one RTCCLK puls every 2**11 pulses.
*\*\            - RTC_SMOOTH_CALIB_PLUS_PULSES_RESET : No RTCCLK pulses are added.
*\*\param   RTC_SmouthCalibMinusPulsesValue : Set the value of CALM[8:0] bits, the value in the 0-0x000001FF range 
*\*\return  ErrorStatus
*\*\            - SUCCESS : RTC Calib registers are configured
*\*\            - ERROR   : RTC Calib registers are not configured
**/
ErrorStatus RTC_Smooth_Calibration_Config(uint32_t RTC_SmoothCalibPeriod,
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmouthCalibMinusPulsesValue)
{
    ErrorStatus status    = ERROR;
    uint32_t recalpfcount = 0;

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* check if a calibration is pending*/
    if ((RTC->INITSTS & RTC_FLAG_RECPF) != RESET)
    {
        /* wait until the Calibration is completed*/
        while (((RTC->INITSTS & RTC_FLAG_RECPF) != RESET) && (recalpfcount != RECALPF_TIMEOUT))
        {
            recalpfcount++;
        }
    }

    /* check if the calibration pending is completed or if there is no calibration operation at all*/
    if ((RTC->INITSTS & RTC_FLAG_RECPF) == RESET)
    {
        /* Configure the Smooth calibration settings */
        RTC->CALIB = (uint32_t)((uint32_t)RTC_SmoothCalibPeriod | (uint32_t)RTC_SmoothCalibPlusPulses
                                | (uint32_t)RTC_SmouthCalibMinusPulsesValue);

        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();

    return (ErrorStatus)(status);
}

/**
*\*\name    RTC_TimeStamp_Enable
*\*\fun     Enable the RTC TimeStamp functionality with the specified time stamp pin stimulating edge.
*\*\param   RTC_TimeStampEdge : Specifies the pin edge on which the TimeStamp is activated.
*\*\            - RTC_TIMESTAMP_EDGE_RISING : the Time stamp event occurs on the rising edge of the related pin.
*\*\            - RTC_TIMESTAMP_EDGE_FALLING : the Time stamp event occurs on the falling edge of the related pin.
*\*\return  none
**/
void RTC_TimeStamp_Enable(uint32_t RTC_TimeStampEdge)
{
    uint32_t temp_value = 0;

    /* Get the RTC_CTRL register and clear the bits to be configured */
    temp_value = (uint32_t)(RTC->CTRL & (uint32_t) ~(RTC_CTRL_TEDGE | RTC_CTRL_TSEN));

    /* Get the new configuration */

    temp_value |= (uint32_t)(RTC_TimeStampEdge | RTC_CTRL_TSEN);
    
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Configure the Time Stamp TSEDGE and Enable bits */
    RTC->CTRL = (uint32_t)temp_value;

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_TimeStamp_Disable
*\*\fun     Disable the RTC TimeStamp functionality
*\*\param   none
*\*\return  none
**/
void RTC_TimeStamp_Disable(void)
{
    uint32_t temp_value = 0;

    /* Get the RTC_CTRL register and clear the bits to be configured */
    temp_value = (uint32_t)(RTC->CTRL & (uint32_t) ~(RTC_CTRL_TEDGE | RTC_CTRL_TSEN));

    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Configure the Time Stamp TSEDGE and Enable bits */
    RTC->CTRL = (uint32_t)temp_value;

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_TimeStamp_Get
*\*\fun     Get the RTC TimeStamp value and masks.
*\*\param   RTC_Format : specifies the format of the output parameters.
*\*\            - RTC_FORMAT_BIN : Binary data format
*\*\            - RTC_FORMAT_BCD : BCD data format
*\*\param   RTC_StampTimeStruct : pointer to a RTC_TimeType structure that will
*\*\        contains the TimeStamp time values.
*\*\param   RTC_StampDateStruct : pointer to a RTC_DateType structure that will
*\*\        contains the TimeStamp date values.
*\*\return  none
**/
void RTC_TimeStamp_Get(uint32_t RTC_Format, RTC_TimeType* RTC_StampTimeStruct, RTC_DateType* RTC_StampDateStruct)
{
    uint32_t tmptime = 0, tmpdate = 0;

    /* Get the TimeStamp time and date registers values */
    tmptime = (uint32_t)(RTC->TST & RTC_TR_RESERVED_MASK);
    tmpdate = (uint32_t)(RTC->TSD & RTC_DATE_RESERVED_MASK);
    
    /* Fill the Time structure fields with the read parameters */
    RTC_StampTimeStruct->Hours   = (uint8_t)((tmptime & (RTC_TSH_HOT | RTC_TSH_HOU)) >> 16);
    RTC_StampTimeStruct->Minutes = (uint8_t)((tmptime & (RTC_TSH_MIT | RTC_TSH_MIU)) >> 8);
    RTC_StampTimeStruct->Seconds = (uint8_t)(tmptime & (RTC_TSH_SCT | RTC_TSH_SCU));
    RTC_StampTimeStruct->H12     = (uint8_t)((tmptime & (RTC_TSH_APM)) >> 16);

    /* Fill the Date structure fields with the read parameters */
    RTC_StampDateStruct->Year    = (uint8_t)((tmpdate & (RTC_DATE_YRT | RTC_DATE_YRU)) >> 16);
    RTC_StampDateStruct->Month   = (uint8_t)((tmpdate & (RTC_DATE_MOT | RTC_DATE_MOU)) >> 8);
    RTC_StampDateStruct->Date    = (uint8_t)(tmpdate & (RTC_DATE_DAT | RTC_DATE_DAU));
    RTC_StampDateStruct->WeekDay = (uint8_t)((tmpdate & (RTC_DATE_WDU)) >> 13);

    /* Check the input parameters format */
    if (RTC_Format == RTC_FORMAT_BIN)
    {
        /* Convert the Time structure parameters to Binary format */
        RTC_StampTimeStruct->Hours   = (uint8_t)RTC_Bcd2_To_Byte(RTC_StampTimeStruct->Hours);
        RTC_StampTimeStruct->Minutes = (uint8_t)RTC_Bcd2_To_Byte(RTC_StampTimeStruct->Minutes);
        RTC_StampTimeStruct->Seconds = (uint8_t)RTC_Bcd2_To_Byte(RTC_StampTimeStruct->Seconds);

        /* Convert the Date structure parameters to Binary format */
        RTC_StampDateStruct->Month   = (uint8_t)RTC_Bcd2_To_Byte(RTC_StampDateStruct->Month);
        RTC_StampDateStruct->Date    = (uint8_t)RTC_Bcd2_To_Byte(RTC_StampDateStruct->Date);
        RTC_StampDateStruct->WeekDay = (uint8_t)RTC_Bcd2_To_Byte(RTC_StampDateStruct->WeekDay);
    }
}

/**
*\*\name    RTC_TimeStamp_SubSecond_Get
*\*\fun     Get the RTC timestamp Subseconds value.
*\*\return  RTC current timestamp Subseconds value.
**/
uint32_t RTC_TimeStamp_SubSecond_Get(void)
{
    /* Get timestamp subseconds values from the correspondent registers */
    return (uint32_t)(RTC->TSSS);
}


/**
*\*\name    RTC_Output_Mode_Config
*\*\fun     Configures the RTC Output Pin mode.
*\*\param   RTC_OutputType : specifies the RTC Output (PC13) pin mode.
*\*\            - RTC_OUTPUT_OPENDRAIN : RTC Output (PC13) is configured in  Open Drain mode.
*\*\            - RTC_OUTPUT_PUSHPULL : RTC Output (PC13) is configured in Push Pull mode.
*\*\return  none
**/
void RTC_Output_Mode_Config(uint32_t RTC_OutputType)
{
    RTC->OPT &= (uint32_t) ~(RTC_OPT_TYPE);
    RTC->OPT |= (uint32_t)(RTC_OutputType);
}


/**
*\*\name    RTC_Synchronization_Shift_Config
*\*\fun     Configures the Synchronization Shift Control Settings.
*\*\param   RTC_ShiftAdd1S : Select to add or not 1 second to the time Calendar.
*\*\            - RTC_SHIFT_SUB1S_DISABLE : Add one second to the clock calendar.
*\*\            - RTC_SHIFT_SUB1S_ENABLE : No effect.
*\*\param   RTC_ShiftAddFS : Select the number of Second Fractions to Substitute.
*\*\          This parameter can be one any value from 0 to 0x7FFF.
*\*\return  ErrorStatus :
*\*\            - SUCCESS : RTC Shift registers are configured
*\*\            - ERROR : RTC Shift registers are not configured
**/
ErrorStatus RTC_Synchronization_Shift_Config(uint32_t RTC_ShiftAddFS, uint32_t RTC_ShiftSub1s)
{
    uint32_t temp_value = 0;
    ErrorStatus status_value = ERROR;
    
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Check if a Shift is pending*/
    if ((RTC->INITSTS & RTC_FLAG_SHOPF) != RESET)
    {
        /* Wait until the shift is completed*/
        while (((RTC->INITSTS & RTC_FLAG_SHOPF) != RESET) && (temp_value != SHPF_TIMEOUT))
        {
            temp_value++;
        }
    }

    /* Check if the Shift pending is completed or if there is no Shift operation at all*/
    if ((RTC->INITSTS & RTC_FLAG_SHOPF) == RESET)
    {
        
        /* check if the reference clock detection is disabled */
        if ((RTC->CTRL & RTC_CTRL_REFCLKEN) == RESET)
        {
            /* Configure the Shift settings */
            RTC->SCTRL = (uint32_t)(uint32_t)(RTC_ShiftAddFS) | (uint32_t)(RTC_ShiftSub1s);

            if (RTC_Wait_For_Synchronization() == ERROR)
            {
                status_value = ERROR;
            }
            else
            {
                status_value = SUCCESS;
            }
        }
        else
        {
            status_value = ERROR;
        }
    }
    else
    {
        status_value = ERROR;
    }

    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();

    return status_value;
}


/**
*\*\name    RTC_Interrupts_Enable
*\*\fun     Enable the specified RTC interrupts.
*\*\param   RTC_INT : specifies the RTC interrupt sources to be enabled .
*\*\            - RTC_INT_TST : TimeStamp interrupt mask.
*\*\            - RTC_INT_WUT : WakeUp Timer interrupt mask.
*\*\            - RTC_INT_ALRB : Alarm B interrupt mask.
*\*\            - RTC_INT_ALRA : Alarm A interrupt mask.
*\*\return  none
**/
void RTC_Interrupts_Enable(uint32_t RTC_INT)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Configure the Interrupts in the RTC_CTRL register */
    RTC->CTRL |= RTC_INT ;
    
    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_Interrupts_Disable
*\*\fun     Disable the specified RTC interrupts.
*\*\param   RTC_INT : specifies the RTC interrupt sources to be disabled.
*\*\            - RTC_INT_TST : TimeStamp interrupt mask.
*\*\            - RTC_INT_WUT : WakeUp Timer interrupt mask.
*\*\            - RTC_INT_ALRB : Alarm B interrupt mask.
*\*\            - RTC_INT_ALRA : Alarm A interrupt mask.
*\*\return  none
**/
void RTC_Interrupts_Disable(uint32_t RTC_INT)
{
    /* Disable the write protection for RTC registers */
    RTC_Write_Protection_Disable();

    /* Configure the Interrupts in the RTC_CTRL register */
    RTC->CTRL &= (uint32_t) ~(RTC_INT);
    
    /* Enable the write protection for RTC registers */
    RTC_Write_Protection_Enable();
}

/**
*\*\name    RTC_Flag_Status_Get
*\*\fun     Checks whether the specified RTC flag is set or not.
*\*\param   RTC_INT : specifies the flag to check.
*\*\          - RTC_FLAG_RECPF  : RECALPF event flag.
*\*\          - RTC_FLAG_TAM3F  : Tamp3 detect flag.
*\*\          - RTC_FLAG_TAM2F  : Tamp2 detect flag.
*\*\          - RTC_FLAG_TAM1F  : Tamp1 detect flag.
*\*\          - RTC_FLAG_TISOVF : Time Stamp OverFlow flag.
*\*\          - RTC_FLAG_TISF   : Time Stamp event flag.
*\*\          - RTC_FLAG_WTF    : WakeUp Timer flag.
*\*\          - RTC_FLAG_ALBF   : Alarm B flag.
*\*\          - RTC_FLAG_ALAF   : Alarm A flag.
*\*\          - RTC_FLAG_INITF  : Initialization mode flag.
*\*\          - RTC_FLAG_RSYF   : Registers Synchronized flag.
*\*\          - RTC_FLAG_INITSF : Registers Configured flag.
*\*\          - RTC_FLAG_SHOPF  : Shift operation pending flag.
*\*\          - RTC_FLAG_WTWF   : WakeUp Timer Write flag.
*\*\          - RTC_FLAG_ALBWF  : Alarm B Write flag.
*\*\          - RTC_FLAG_ALAWF  : Alarm A write flag.
*\*\return  FlagStatus
*\*\          - SET  : 
*\*\          - RESET : 
**/
FlagStatus RTC_Flag_Status_Get(uint32_t RTC_FLAG)
{
    uint32_t temp_value = 0;

    /* Get all the flags */
    temp_value = (uint32_t)(RTC->INITSTS & RTC_FLAGS_MASK);

    /* Return the status of the flag */
    if ((temp_value & RTC_FLAG) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name    RTC_Flag_Clear
*\*\fun     Clears the RTC's flags.
*\*\param   RTC_FLAG : RTC_FLAG specifies the RTC flag to clear.
*\*\          - RTC_FLAG_TAM3F  : Tamp3 detect flag.
*\*\          - RTC_FLAG_TAM2F  : Tamp2 detect flag.
*\*\          - RTC_FLAG_TAM1F  : Tamp1 detect flag.
*\*\          - RTC_FLAG_TISOVF  : Time Stamp Overflow flag.
*\*\          - RTC_FLAG_TISF    : Time Stamp event flag.
*\*\          - RTC_FLAG_WTF     : WakeUp Timer flag
*\*\          - RTC_FLAG_ALBF    : Alarm B flag.
*\*\          - RTC_FLAG_ALAF    : Alarm A flag.
*\*\          - RTC_FLAG_RSYF    : Registers Synchronized flag.
*\*\return  none
**/
void RTC_Flag_Clear(uint32_t RTC_FLAG)
{
    /* Clear the Flags in the RTC_INITSTS register */
    RTC->INITSTS = (uint32_t)((uint32_t)(~((RTC_FLAG | RTC_FLAG_INITM) & 0x0000FFFF) | (uint32_t)(RTC->INITSTS & RTC_FLAG_INITM)));
}

/**
*\*\name    RTC_Interrupt_Status_Get
*\*\fun     Checks whether the specified RTC interrupt has occurred or not.
*\*\param   RTC_INT : specifies the RTC interrupt source to check.
*\*\          - RTC_INT_TAMP3 : Tamper3 interrupt.
*\*\          - RTC_INT_TAMP2 : Tamper2 interrupt.
*\*\          - RTC_INT_TAMP1 : Tamper1 interrupt.
*\*\          - RTC_INT_TST   : Timestamp interrupt.
*\*\          - RTC_INT_WUT   : WakeUp Timer interrupt.
*\*\          - RTC_INT_ALRB  : Alarm B interrupt.
*\*\          - RTC_INT_ALRA  : Alarm A interrupt.
*\*\return  INTStatus
*\*\          - SET   : 
*\*\          - RESET : 
**/
INTStatus RTC_Interrupt_Status_Get(uint32_t RTC_INT)
{
    uint32_t temp_value = 0, status_value = 0;

    /* Get the Interrupt enable Status */
    if ((RTC_INT == RTC_INT_TAMP1) || (RTC_INT == RTC_INT_TAMP2)|| (RTC_INT == RTC_INT_TAMP3))
    {
        temp_value = ((RTC->TMPCFG & 0x00ff0000)>>16);
        if (temp_value > 0)
        {
            status_value = SET;
        }
    }
    else
    {
       status_value = (uint32_t)((RTC->CTRL & RTC_INT));
    }

    /* Get the Interrupt bit */
    temp_value = (uint32_t)((RTC->INITSTS & (uint32_t)(RTC_INT >> 4)));

    /* Get the status of the Interrupt */
    if ((status_value != (uint32_t)RESET) && ((temp_value & 0x0000FFFF) != (uint32_t)RESET))
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name    RTC_Interrupt_Status_Clear
*\*\fun     Clears the RTC's interrupt pending bits.
*\*\param   RTC_INT : specifies the RTC interrupt pending bit to clear.
*\*\          - RTC_INT_TAMP3 : Tamper3 interrupt.
*\*\          - RTC_INT_TAMP2 : Tamper2 interrupt.
*\*\          - RTC_INT_TAMP1 : Tamper1 interrupt.
*\*\          - RTC_INT_TST   : Timestamp interrupt.
*\*\          - RTC_INT_WUT   : WakeUp Timer interrupt
*\*\          - RTC_INT_ALRB  : Alarm B interrupt
*\*\          - RTC_INT_ALRA  : Alarm A interrupt
*\*\return  none
**/
void RTC_Interrupt_Status_Clear(uint32_t RTC_INT)
{
    uint32_t temp_value = 0;

    /* Get the RTC_INITSTS Interrupt pending bits mask */
    temp_value = (uint32_t)(RTC_INT >> 4);

    /* Clear the interrupt pending bits in the RTC_INITSTS register */
    RTC->INITSTS = (uint32_t)((uint32_t)(~((temp_value | RTC_FLAG_INITM) & 0x0000FFFF) | (uint32_t)(RTC->INITSTS & RTC_FLAG_INITM))); 

}

/**
*\*\name    RTC_Tamper_Trigger_Config
*\*\fun     Configures the select Tamper pin edge.
*\*\param   RTC_Tamper: Selected tamper pin.
*\*\          - RTC_TAMPER_1: Select Tamper 1.
*\*\          - RTC_TAMPER_2: Select Tamper 2.
*\*\          - RTC_TAMPER_3: Select Tamper 3.
*\*\param   RTC_TamperTrigger: Specifies the trigger on the tamper pin that stimulates tamper event. 
*\*\          - RTC_TamperTrigger_RisingEdge: Rising Edge of the tamper pin causes tamper event.
*\*\          - RTC_TamperTrigger_FallingEdge: Falling Edge of the tamper pin causes tamper event.
*\*\          - RTC_TamperTrigger_LowLevel: Low Level of the tamper pin causes tamper event.
*\*\          - RTC_TamperTrigger_HighLevel: High Level of the tamper pin causes tamper event.
*\*\return  none
**/
void RTC_Tamper_Trigger_Config(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger)
{
    if (RTC_Tamper == RTC_TAMPER_3)
    {
        RTC_TamperTrigger <<= 5;
    }  
    else if (RTC_Tamper == RTC_TAMPER_2)
    {
        RTC_TamperTrigger <<= 3;
    }     
    /* Configure the RTC_TAMPCR register */
    RTC->TMPCFG |= (uint32_t)(RTC_Tamper | RTC_TamperTrigger);     
    
}

/**
*\*\name    RTC_Tamper_Enable
*\*\fun     Enable the Tamper detection.
*\*\param   RTC_Tamper: Selected tamper pin.
*\*\          - RTC_TAMPER_1: Select Tamper 1.
*\*\          - RTC_TAMPER_2: Select Tamper 2.
*\*\          - RTC_TAMPER_3: Select Tamper 3.
*\*\return  none
**/
void RTC_Tamper_Enable(uint32_t RTC_Tamper)
{
    /* Enable the selected Tamper pin */
    RTC->TMPCFG |= (uint32_t)RTC_Tamper;
}

/**
*\*\name    RTC_Tamper_Disable
*\*\fun     Disable the Tamper detection.
*\*\param   RTC_Tamper: Selected tamper pin.
*\*\          - RTC_TAMPER_1: Select Tamper 1.
*\*\          - RTC_TAMPER_2: Select Tamper 2.
*\*\          - RTC_TAMPER_3: Select Tamper 3.
*\*\return  none
**/
void RTC_Tamper_Disable(uint32_t RTC_Tamper)
{
    /* Disable the selected Tamper pin */
    RTC->TMPCFG &= (uint32_t)~RTC_Tamper;    

}

/**
*\*\name    RTC_Tamper_Filter_Config
*\*\fun     Configures the Tampers Filter.
*\*\param   RTC_TamperFilter: Selected tamper pin.
*\*\            - RTC_TamperFilter_Disable: Tamper filter is disabled.
*\*\            - RTC_TamperFilter_2Sample: Tamper is activated after 2 consecutive samples at the active level.
*\*\            - RTC_TamperFilter_4Sample: Tamper is activated after 4 consecutive samples at the active level.
*\*\            - RTC_TamperFilter_8Sample: Tamper is activated after 8 consecutive samples at the active level.
*\*\return  none
**/
void RTC_Tamper_Filter_Config(uint32_t RTC_TamperFilter)
{   
    /* Clear TAMPFLT[1:0] bits in the RTC_TAMPCR register */
    RTC->TMPCFG &= (uint32_t)~(RTC_TMPCFG_TPFLT);

    /* Configure the RTC_TAMPCR register */
    RTC->TMPCFG |= (uint32_t)RTC_TamperFilter;
}

/**
*\*\name    RTC_Tamper_Sampling_Frequency_Config
*\*\fun     Configures the Tampers Sampling Frequency.
*\*\param   RTC_TamperSamplingFreq: Selected tamper pin.
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div32768
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div16384
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div8192
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div4096
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div2048
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div1024
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div512
*\*\            - RTC_TamperSamplingFreq_RTCCLK_Div256
*\*\return  none
**/
void RTC_Tamper_Sampling_Frequency_Config(uint32_t RTC_TamperSamplingFreq)
{ 
  /* Clear TAMPFREQ[2:0] bits in the RTC_TAMPCR register */
  RTC->TMPCFG &= (uint32_t)~(RTC_TAMPCR_TAMPFREQ);

  /* Configure the RTC_TAMPCR register */
  RTC->TMPCFG |= (uint32_t)RTC_TamperSamplingFreq;
}

/**
*\*\name    RTC_Tamper_Pins_Precharge_Duration
*\*\fun     Configures the Tampers Pins input Precharge Duration.
*\*\param   RTC_TamperPrechargeDuration: Selected tamper pin.
*\*\            - RTC_TamperPrechargeDuration_1RTCCLK
*\*\            - RTC_TamperPrechargeDuration_2RTCCLK
*\*\            - RTC_TamperPrechargeDuration_4RTCCLK
*\*\            - RTC_TamperPrechargeDuration_8RTCCLK
*\*\return  none
**/
void RTC_Tamper_Pins_Precharge_Duration(uint32_t RTC_TamperPrechargeDuration)
{   
  /* Clear TAMPPRCH[1:0] bits in the RTC_TAMPCR register */
  RTC->TMPCFG &= (uint32_t)~(RTC_TMPCFG_TPPRCH);

  /* Configure the RTC_TAMPCR register */
  RTC->TMPCFG |= (uint32_t)RTC_TamperPrechargeDuration;
}

/**
*\*\name    RTC_TimeStamp_On_Tamper_Detection_Enable
*\*\fun     The timestamp is valid even the TSEN bit in tamper control register is reset.   
*\*\param   none
*\*\return  none
**/
void RTC_TimeStamp_On_Tamper_Detection_Enable(void)
{   
    /* Save timestamp on tamper detection event */
    RTC->TMPCFG |= (uint32_t)RTC_TMPCFG_TPTS;
}

/**
*\*\name    RTC_TimeStamp_On_Tamper_Detection_Disable
*\*\fun     The timestamp is invalid even the TSEN bit in tamper control register is reset.   
*\*\param   none
*\*\return  none
**/
void RTC_TimeStamp_On_Tamper_Detection_Disable(void)
{   
    /* Tamper detection does not cause a timestamp to be saved */
    RTC->TMPCFG &= (uint32_t)~RTC_TMPCFG_TPTS;    
}

/**
*\*\name    RTC_Tamper_Precharge_Enable
*\*\fun     Enable the Precharge of Tamper pin. 
*\*\param   none
*\*\return  none
**/
void RTC_Tamper_Precharge_Enable(void)
{  
    /* Enable precharge of the selected Tamper pin */
    RTC->TMPCFG &= (uint32_t)~RTC_TMPCFG_TPPUDIS; 
}

/**
*\*\name    RTC_Tamper_Precharge_Disable
*\*\fun     Enables or Disables the Precharge of Tamper pin. 
*\*\param   none
*\*\return  none
**/
void RTC_Tamper_Precharge_Disable(void)
{  
    /* Disable precharge of the selected Tamper pin */
    RTC->TMPCFG |= (uint32_t)RTC_TMPCFG_TPPUDIS;    
}

/**
*\*\name    RTC_Tamper_Interrput_Enable
*\*\fun     Enable the Tamper interrupt.
*\*\param   TAMPx_INT: Selected tamper number.
*\*\            - RTC_TAMPER1_INT
*\*\            - RTC_TAMPER2_INT
*\*\            - RTC_TAMPER3_INT
*\*\return  none
**/
void RTC_Tamper_Interrput_Enable(uint32_t TAMPx_INT)
{
    /* Enable the selected Tamper pin */
    RTC->TMPCFG |= (uint32_t)TAMPx_INT;
}

/**
*\*\name    RTC_Tamper_Interrput_Disable
*\*\fun     Disable the Tamper interrupt.
*\*\param   TAMPx_INT: Selected tamper number.
*\*\            - RTC_TAMPER1_INT
*\*\            - RTC_TAMPER2_INT
*\*\            - RTC_TAMPER3_INT
*\*\return  none
**/
void RTC_Tamper_Interrput_Disable(uint32_t TAMPx_INT)
{
    /* Disable the selected Tamper pin */
    RTC->TMPCFG &= (uint32_t)~TAMPx_INT;
}

/**
*\*\name    RTC_Tamper_Backup_Register_Clear_Disable
*\*\fun     Enable the Tamper do not clear backup register.
*\*\param   RTC_Tamper: Selected tamper event.
*\*\          - RTC_TAMPER1_NOE: Select Tamper 1.
*\*\          - RTC_TAMPER2_NOE: Select Tamper 2.
*\*\          - RTC_TAMPER3_NOE: Select Tamper 3.
*\*\return  none
**/
void RTC_Tamper_Backup_Register_Clear_Disable(uint32_t RTC_TAMPERx_NOE)
{
    /* Enable Tamper clear backup register */
    RTC->TMPCFG |= (uint32_t)RTC_TAMPERx_NOE;
}

/**
*\*\name    RTC_Tamper_Backup_Register_Clear_Enable
*\*\fun     Enable the Tamper clear backup register.
*\*\param   RTC_Tamper: Selected tamper event.
*\*\          - RTC_TAMPER1_NOE: Select Tamper 1.
*\*\          - RTC_TAMPER2_NOE: Select Tamper 2.
*\*\          - RTC_TAMPER3_NOE: Select Tamper 3.
*\*\return  none
**/
void RTC_Tamper_Backup_Register_Clear_Enable(uint32_t RTC_TAMPERx_NOE)
{
    /* Enable Tamper clear backup register */
    RTC->TMPCFG &= (uint32_t)~RTC_TAMPERx_NOE;
}

/**
*\*\name    RTC_Backup_Registers_Write
*\*\fun     Write a data in a specified RTC Backup data register.
*\*\param   register_num: Selected register number.
*\*\            RTC_BACKUP_REGISTER_1
*\*\            RTC_BACKUP_REGISTER_2
*\*\            RTC_BACKUP_REGISTER_3
*\*\            RTC_BACKUP_REGISTER_4
*\*\            RTC_BACKUP_REGISTER_5
*\*\            RTC_BACKUP_REGISTER_6
*\*\            RTC_BACKUP_REGISTER_7
*\*\            RTC_BACKUP_REGISTER_8
*\*\            RTC_BACKUP_REGISTER_9
*\*\            RTC_BACKUP_REGISTER_10
*\*\            RTC_BACKUP_REGISTER_11
*\*\            RTC_BACKUP_REGISTER_12
*\*\            RTC_BACKUP_REGISTER_13
*\*\            RTC_BACKUP_REGISTER_14
*\*\            RTC_BACKUP_REGISTER_15
*\*\            RTC_BACKUP_REGISTER_16
*\*\            RTC_BACKUP_REGISTER_17
*\*\            RTC_BACKUP_REGISTER_18
*\*\            RTC_BACKUP_REGISTER_19
*\*\            RTC_BACKUP_REGISTER_20
*\*\param   Data: Data write.
*\*\return  none
**/
void RTC_Backup_Register_Write(RTC_BACKUP_REGISTER register_num, uint32_t Data)
{
    volatile uint32_t *temp_value;

    temp_value = &RTC->BKP1R;
    temp_value += (register_num-1);

    /* Write register */
    *(__IO uint32_t *)temp_value = (uint32_t)Data;
}

/**
*\*\name    RTC_Backup_Register_Read
*\*\fun     Read a data in a specified RTC Backup data register.
*\*\param   register_num: Selected register number.
*\*\            RTC_BACKUP_REGISTER_1
*\*\            RTC_BACKUP_REGISTER_2
*\*\            RTC_BACKUP_REGISTER_3
*\*\            RTC_BACKUP_REGISTER_4
*\*\            RTC_BACKUP_REGISTER_5
*\*\            RTC_BACKUP_REGISTER_6
*\*\            RTC_BACKUP_REGISTER_7
*\*\            RTC_BACKUP_REGISTER_8
*\*\            RTC_BACKUP_REGISTER_9
*\*\            RTC_BACKUP_REGISTER_10
*\*\            RTC_BACKUP_REGISTER_11
*\*\            RTC_BACKUP_REGISTER_12
*\*\            RTC_BACKUP_REGISTER_13
*\*\            RTC_BACKUP_REGISTER_14
*\*\            RTC_BACKUP_REGISTER_15
*\*\            RTC_BACKUP_REGISTER_16
*\*\            RTC_BACKUP_REGISTER_17
*\*\            RTC_BACKUP_REGISTER_18
*\*\            RTC_BACKUP_REGISTER_19
*\*\            RTC_BACKUP_REGISTER_20
*\*\return  Register data
**/
uint32_t RTC_Backup_Register_Read(RTC_BACKUP_REGISTER register_num)
{
    volatile uint32_t *temp_value;

    temp_value = &RTC->BKP1R;
    temp_value += (register_num-1);

    /* Read register */
    return (*(__IO uint32_t *)temp_value);
}

/**
*\*\name    RTC_Byte_To_Bcd2
*\*\fun     Converts a 2 digit decimal to BCD format.
*\*\param   value : Value Byte to be converted.
*\*\return  Converted byte
**/
static uint8_t RTC_Byte_To_Bcd2(uint8_t value)
{
    uint8_t temp_value = 0;

    while (value >= 10)
    {
        temp_value++;
        value -= 10;
    }
    return ((uint8_t)(temp_value << 4) | value);
}

/**
*\*\name    RTC_Bcd2_To_Byte
*\*\fun     Convert from 2 digit BCD to Binary.
*\*\param   Value : Value BCD value to be converted.
*\*\return  Converted byte
**/
static uint8_t RTC_Bcd2_To_Byte(uint8_t value)
{
    uint8_t temp_value = 0;
    temp_value = ((uint8_t)(value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    return (temp_value + (value & (uint8_t)0x0F));
}

/**
*\*\}
 */
