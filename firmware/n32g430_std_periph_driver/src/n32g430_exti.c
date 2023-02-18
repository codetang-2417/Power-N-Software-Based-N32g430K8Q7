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
*\*\file n32g430_exti.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#include "n32g430_exti.h"


/**
*\*\name    EXTI_Reset.
*\*\fun     Reset the EXTI registers.
*\*\return  none
**/
void EXTI_Reset(void)
{
    EXTI->IMASK  = 0x00000000;
    EXTI->EMASK  = 0x00000000;
    EXTI->RT_CFG = 0x00000000;
    EXTI->FT_CFG = 0x00000000;
    EXTI->PEND   = 0x00FFFFFF;
}

/**
*\*\name    EXTI_Peripheral_Initializes.
*\*\fun     Initializes the EXTI according to EXTI_InitStruct.
*\*\param   EXTI_InitStruct :
*\*\          - EXTI_Mode
*\*\            - EXTI_Mode_Interrupt
*\*\            - EXTI_Mode_Event
*\*\          - EXTI_Trigger
*\*\            - EXTI_Trigger_Rising
*\*\            - EXTI_Trigger_Falling
*\*\            - EXTI_Trigger_Rising_Falling
*\*\          - EXTI_Line
*\*\            - EXTI_LINE0              
*\*\            - EXTI_LINE1            
*\*\            - EXTI_LINE2              
*\*\            - EXTI_LINE3             
*\*\            - EXTI_LINE4              
*\*\            - EXTI_LINE5 
*\*\            - EXTI_LINE6              
*\*\            - EXTI_LINE7                
*\*\            - EXTI_LINE8              
*\*\            - EXTI_LINE9              
*\*\            - EXTI_LINE10              
*\*\            - EXTI_LINE11            
*\*\            - EXTI_LINE12            
*\*\            - EXTI_LINE13   
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15   
*\*\            - EXTI_LINE16   
*\*\            - EXTI_LINE17   
*\*\            - EXTI_LINE18   
*\*\            - EXTI_LINE19     
*\*\            - EXTI_LINE20   
*\*\            - EXTI_LINE21   
*\*\            - EXTI_LINE22 
*\*\            - EXTI_LINE23  
*\*\          - EXTI_LineCmd
*\*\            - ENABLE
*\*\            - DISABLE
*\*\return  none
**/
void EXTI_Peripheral_Initializes(EXTI_InitType* EXTI_InitStruct)
{
    EXTI_Work_Mode_Config(EXTI_InitStruct->EXTI_Line,EXTI_InitStruct->EXTI_Mode);
    EXTI_Trigger_Config(EXTI_InitStruct->EXTI_Line,EXTI_InitStruct->EXTI_Trigger);
    EXTI_LineCmd_Disable(EXTI_InitStruct->EXTI_Line,EXTI_InitStruct->EXTI_LineCmd,EXTI_InitStruct->EXTI_Mode);
}

/**
*\*\name    EXTI_Work_Mode_Config.
*\*\fun     Config the EXTI according to EXTI_Mode.
*\*\param   exti_mode :
*\*\            - EXTI_Mode_Interrupt
*\*\            - EXTI_Mode_Event
*\*\param   exti_line :
*\*\            - EXTI_LINE0              
*\*\            - EXTI_LINE1            
*\*\            - EXTI_LINE2              
*\*\            - EXTI_LINE3             
*\*\            - EXTI_LINE4              
*\*\            - EXTI_LINE5 
*\*\            - EXTI_LINE6              
*\*\            - EXTI_LINE7                
*\*\            - EXTI_LINE8              
*\*\            - EXTI_LINE9              
*\*\            - EXTI_LINE10              
*\*\            - EXTI_LINE11            
*\*\            - EXTI_LINE12            
*\*\            - EXTI_LINE13   
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15   
*\*\            - EXTI_LINE16   
*\*\            - EXTI_LINE17   
*\*\            - EXTI_LINE18   
*\*\            - EXTI_LINE19     
*\*\            - EXTI_LINE20   
*\*\            - EXTI_LINE21   
*\*\            - EXTI_LINE22 
*\*\            - EXTI_LINE23 
*\*\return  none
**/
void EXTI_Work_Mode_Config(uint32_t exti_line,uint32_t exti_mode)
{
    uint32_t temp_value = 0;    
    temp_value = (uint32_t)EXTI_BASE;    
    /* Clear work mode configuration */
    EXTI->IMASK &= ~exti_line;
    EXTI->EMASK &= ~exti_line;
   /* Select the work mode */
    temp_value += exti_mode;
    *(__IO uint32_t*)temp_value |= exti_line;
}

/**
*\*\name    EXTI_EXTI_Trigger_Config.
*\*\fun     Config the EXTI according to EXTI_Trigger.
*\*\param   exti_trigger :
*\*\            - EXTI_Trigger_Rising
*\*\            - EXTI_Trigger_Falling
*\*\            - EXTI_Trigger_Rising_Falling
*\*\param   exti_line :
*\*\            - EXTI_LINE0              
*\*\            - EXTI_LINE1            
*\*\            - EXTI_LINE2              
*\*\            - EXTI_LINE3             
*\*\            - EXTI_LINE4              
*\*\            - EXTI_LINE5 
*\*\            - EXTI_LINE6              
*\*\            - EXTI_LINE7                
*\*\            - EXTI_LINE8              
*\*\            - EXTI_LINE9              
*\*\            - EXTI_LINE10              
*\*\            - EXTI_LINE11            
*\*\            - EXTI_LINE12            
*\*\            - EXTI_LINE13   
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15   
*\*\            - EXTI_LINE16   
*\*\            - EXTI_LINE17   
*\*\            - EXTI_LINE18   
*\*\            - EXTI_LINE19     
*\*\            - EXTI_LINE20   
*\*\            - EXTI_LINE21  
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\return  none
**/
void EXTI_Trigger_Config(uint32_t exti_line,uint32_t exti_trigger)
{
    uint32_t temp_value = 0;    
    temp_value = (uint32_t)EXTI_BASE;      
    /* Clear Rising Falling edge configuration */
    EXTI->RT_CFG &= ~exti_line;
    EXTI->FT_CFG &= ~exti_line;

   /* Select the trigger method */
    if(exti_trigger == EXTI_Trigger_Rising_Falling)
    {
        EXTI->RT_CFG |= exti_line;
        EXTI->FT_CFG |= exti_line;
    }
    else
    {
        temp_value = (uint32_t)EXTI_BASE;
        temp_value += exti_trigger;

        *(__IO uint32_t*)temp_value |= exti_line;      
    }    

}

/**
*\*\name    EXTI_EXTI_LineCmd_Disable.
*\*\fun     Config the EXTI according to EXTI_LineCmd.
*\*\param   exti_linecmd :   
*\*\            - ENABLE
*\*\            - DISABLE
*\*\param   exti_mode :
*\*\            - EXTI_Mode_Interrupt
*\*\            - EXTI_Mode_Event
*\*\param   exti_line :
*\*\            - EXTI_LINE0              
*\*\            - EXTI_LINE1            
*\*\            - EXTI_LINE2              
*\*\            - EXTI_LINE3             
*\*\            - EXTI_LINE4              
*\*\            - EXTI_LINE5 
*\*\            - EXTI_LINE6              
*\*\            - EXTI_LINE7                
*\*\            - EXTI_LINE8              
*\*\            - EXTI_LINE9              
*\*\            - EXTI_LINE10              
*\*\            - EXTI_LINE11            
*\*\            - EXTI_LINE12            
*\*\            - EXTI_LINE13   
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15   
*\*\            - EXTI_LINE16   
*\*\            - EXTI_LINE17   
*\*\            - EXTI_LINE18   
*\*\            - EXTI_LINE19     
*\*\            - EXTI_LINE20   
*\*\            - EXTI_LINE21 
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23 
*\*\return  none
**/
void EXTI_LineCmd_Disable(uint32_t exti_line,uint32_t exti_linecmd,uint32_t exti_mode)
{
    uint32_t temp_value = 0;    
    temp_value = (uint32_t)EXTI_BASE;    
     /* Disable the selected external lines */
    if(exti_linecmd == DISABLE)
    {
        temp_value += exti_mode;
        /* Disable the selected external lines */
        *(__IO uint32_t*)temp_value &= ~exti_line;             
    }
}


/**
*\*\name    EXTI_Structure_Initializes.
*\*\fun     Fills each EXTI_InitStruct member with its default value.
*\*\param   EXTI_InitStruct :   
*\*\            - EXTI_Line
*\*\            - EXTI_Mode
*\*\            - EXTI_Trigger
*\*\            - EXTI_LineCmd  
*\*\return  none
**/
void EXTI_Structure_Initializes(EXTI_InitType* EXTI_InitStruct)
{
    EXTI_InitStruct->EXTI_Line    = EXTI_LINENONE;
    EXTI_InitStruct->EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}


/**
*\*\name    EXTI_Software_Interrupt_Trigger.
*\*\fun     Generates a Software interrupt.
*\*\param   exti_line :   
*\*\            - EXTI_LINE0              
*\*\            - EXTI_LINE1            
*\*\            - EXTI_LINE2              
*\*\            - EXTI_LINE3             
*\*\            - EXTI_LINE4              
*\*\            - EXTI_LINE5 
*\*\            - EXTI_LINE6              
*\*\            - EXTI_LINE7                
*\*\            - EXTI_LINE8              
*\*\            - EXTI_LINE9              
*\*\            - EXTI_LINE10              
*\*\            - EXTI_LINE11            
*\*\            - EXTI_LINE12            
*\*\            - EXTI_LINE13   
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15   
*\*\            - EXTI_LINE16   
*\*\            - EXTI_LINE17   
*\*\            - EXTI_LINE18   
*\*\            - EXTI_LINE19     
*\*\            - EXTI_LINE20   
*\*\            - EXTI_LINE21 
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\return  none
**/
void EXTI_Software_Interrupt_Trigger(uint32_t exti_line)
{
    /* Set the EXTI_SWIE ON bit, The EXTI generates a Software interrupt */
    EXTI->SWIE |= exti_line;
}



/**
*\*\name    EXTI_Flag_Status_Get.
*\*\fun     Get EXTI line flag status.
*\*\param   exti_line :   
*\*\            - EXTI_LINE0              
*\*\            - EXTI_LINE1            
*\*\            - EXTI_LINE2              
*\*\            - EXTI_LINE3             
*\*\            - EXTI_LINE4              
*\*\            - EXTI_LINE5 
*\*\            - EXTI_LINE6              
*\*\            - EXTI_LINE7                
*\*\            - EXTI_LINE8              
*\*\            - EXTI_LINE9              
*\*\            - EXTI_LINE10              
*\*\            - EXTI_LINE11            
*\*\            - EXTI_LINE12            
*\*\            - EXTI_LINE13   
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15   
*\*\            - EXTI_LINE16   
*\*\            - EXTI_LINE17   
*\*\            - EXTI_LINE18   
*\*\            - EXTI_LINE19     
*\*\            - EXTI_LINE20   
*\*\            - EXTI_LINE21 
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\return  SET or RESET
**/
FlagStatus EXTI_Flag_Status_Get(uint32_t exti_line)
{
    if ((EXTI->PEND & exti_line) != (uint32_t)RESET)
    {
        /* EXTI line flag status is set */
        return SET;
    }
    else
    {
        /* EXTI line flag status is reset */
        return RESET;
    }
}

/**
*\*\name    EXTI_Flag_Status_Clear.
*\*\fun     Clear EXTI line flag status.
*\*\param   exti_line :   
*\*\            - EXTI_LINE0              
*\*\            - EXTI_LINE1            
*\*\            - EXTI_LINE2              
*\*\            - EXTI_LINE3             
*\*\            - EXTI_LINE4              
*\*\            - EXTI_LINE5 
*\*\            - EXTI_LINE6              
*\*\            - EXTI_LINE7                
*\*\            - EXTI_LINE8              
*\*\            - EXTI_LINE9              
*\*\            - EXTI_LINE10              
*\*\            - EXTI_LINE11            
*\*\            - EXTI_LINE12            
*\*\            - EXTI_LINE13   
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15   
*\*\            - EXTI_LINE16   
*\*\            - EXTI_LINE17   
*\*\            - EXTI_LINE18   
*\*\            - EXTI_LINE19     
*\*\            - EXTI_LINE20   
*\*\            - EXTI_LINE21 
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\return  none
**/
void EXTI_Flag_Status_Clear(uint32_t exti_line)
{
    /* Clear EXTI line flag status. */
    EXTI->PEND = exti_line;
}




/**
*\*\name    EXTI_Interrupt_Status_Get.
*\*\fun     GET EXTI line interrupt status.
*\*\param   exti_line :   
*\*\            - EXTI_LINE0              
*\*\            - EXTI_LINE1            
*\*\            - EXTI_LINE2              
*\*\            - EXTI_LINE3             
*\*\            - EXTI_LINE4              
*\*\            - EXTI_LINE5 
*\*\            - EXTI_LINE6              
*\*\            - EXTI_LINE7                
*\*\            - EXTI_LINE8              
*\*\            - EXTI_LINE9              
*\*\            - EXTI_LINE10              
*\*\            - EXTI_LINE11            
*\*\            - EXTI_LINE12            
*\*\            - EXTI_LINE13   
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15   
*\*\            - EXTI_LINE16   
*\*\            - EXTI_LINE17   
*\*\            - EXTI_LINE18   
*\*\            - EXTI_LINE19     
*\*\            - EXTI_LINE20   
*\*\            - EXTI_LINE21 
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\return  SET or RESET
**/
INTStatus EXTI_Interrupt_Status_Get(uint32_t exti_line)
{


    if (((EXTI->PEND & exti_line) != (uint32_t)RESET) && ((EXTI->IMASK & exti_line) != (uint32_t)RESET))
    {
        /* EXTI line interrupt status is set */
        return SET;
    }
    else
    {
        /* EXTI line interrupt status is reset */
        return RESET;
    }

}


/**
*\*\name    EXTI_Interrupt_Status_Clear.
*\*\fun     Clear EXTI line interrupt pend bit.
*\*\param   exti_line :   
*\*\            - EXTI_LINE0              
*\*\            - EXTI_LINE1            
*\*\            - EXTI_LINE2              
*\*\            - EXTI_LINE3             
*\*\            - EXTI_LINE4              
*\*\            - EXTI_LINE5 
*\*\            - EXTI_LINE6              
*\*\            - EXTI_LINE7                
*\*\            - EXTI_LINE8              
*\*\            - EXTI_LINE9              
*\*\            - EXTI_LINE10              
*\*\            - EXTI_LINE11            
*\*\            - EXTI_LINE12            
*\*\            - EXTI_LINE13   
*\*\            - EXTI_LINE14
*\*\            - EXTI_LINE15   
*\*\            - EXTI_LINE16   
*\*\            - EXTI_LINE17   
*\*\            - EXTI_LINE18   
*\*\            - EXTI_LINE19     
*\*\            - EXTI_LINE20   
*\*\            - EXTI_LINE21 
*\*\            - EXTI_LINE22
*\*\            - EXTI_LINE23
*\*\return  none
**/
void EXTI_Interrupt_Status_Clear(uint32_t exti_line)
{

    /* Clear EXTI line interrupt pend bit. */
    EXTI->PEND = exti_line;
}

/**
*\*\name    EXTI_RTC_Time_Stamp_Select.
*\*\fun     Select the input of TimeStamp event.
*\*\param   exti_tssel_line :   
*\*\            - EXTI_TSSEL_Line0             
*\*\            - EXTI_TSSEL_Line1            
*\*\            - EXTI_TSSEL_Line2             
*\*\            - EXTI_TSSEL_Line3             
*\*\            - EXTI_TSSEL_Line4               
*\*\            - EXTI_TSSEL_Line5 
*\*\            - EXTI_TSSEL_Line6              
*\*\            - EXTI_TSSEL_Line7                
*\*\            - EXTI_TSSEL_Line8              
*\*\            - EXTI_TSSEL_Line9              
*\*\            - EXTI_TSSEL_Line10              
*\*\            - EXTI_TSSEL_Line11            
*\*\            - EXTI_TSSEL_Line12            
*\*\            - EXTI_TSSEL_Line13   
*\*\            - EXTI_TSSEL_Line14
*\*\            - EXTI_TSSEL_Line15   
*\*\return  none
**/
void EXTI_RTC_Time_Stamp_Select(uint32_t exti_tssel_line)
{
    /* Select the input of TimeStamp event */
    EXTI->TS_SEL &= EXTI_TSSEL_LINE_MASK;
    EXTI->TS_SEL |= exti_tssel_line;
}


