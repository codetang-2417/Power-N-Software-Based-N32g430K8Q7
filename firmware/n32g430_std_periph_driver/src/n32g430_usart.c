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
*\*\file n32g430_usart.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#include "n32g430_usart.h"
#include "n32g430_rcc.h"


/**
*\*\name    USART_Reset
*\*\fun     Reset the USARTx registers.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/

void USART_Reset(USART_Module* USARTx)
{

    if (USARTx == USART1)
    {
        /* USART1 Reset */
        RCC_APB2_Peripheral_Reset(RCC_APB2_PERIPH_USART1);
    }
    else if (USARTx == USART2)
    {
        /* USART2 Reset */
        RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_USART2);
    }
    else if (USARTx == UART3)
    {
        /* USART3 Reset */
        RCC_APB2_Peripheral_Reset(RCC_APB2_PERIPH_UART3);
    }
    else if (USARTx == UART4)
    {
        /* UART4 Reset */
        RCC_APB2_Peripheral_Reset(RCC_APB2_PERIPH_UART4);
    }
}

/**
*\*\name    USART_Initializes
*\*\fun     Initializes the USARTx peripheral according to USART_InitStruct .
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_InitStruct :
*\*\          - buad_rate :
*\*\            - (((buad_rate) > 0) && ((buad_rate) < 0x00337F99))
*\*\          - WordLength
*\*\            - USART_WL_8B
*\*\            - USART_WL_9B
*\*\          - StopBits
*\*\            - USART_STPB_1
*\*\            - USART_STPB_0_5
*\*\            - USART_STPB_2
*\*\            - USART_STPB_1_5
*\*\          - Parity
*\*\            - USART_PE_NO
*\*\            - USART_PE_EVEN
*\*\            - USART_PE_ODD
*\*\          - Mode
*\*\            - USART_MODE_RX
*\*\            - USART_MODE_TX
*\*\          - HardwareFlowControl
*\*\            - USART_HFCTRL_NONE
*\*\            - USART_HFCTRL_RTS
*\*\            - USART_HFCTRL_CTS
*\*\            - USART_HFCTRL_RTS_CTS
*\*\return  none
**/

void USART_Initializes(USART_Module* USARTx, USART_InitType* USART_InitStruct)
{
    USART_Baud_Rate_Config(USARTx,USART_InitStruct->BaudRate);
    USART_Word_Length_Config(USARTx,USART_InitStruct->WordLength);
    USART_Stop_Bits_Config(USARTx,USART_InitStruct->StopBits);
    USART_Parity_Config(USARTx,USART_InitStruct->Parity);
    USART_Mode_Config(USARTx,USART_InitStruct->Mode);  
    USART_Hardware_Flow_Control_Config(USARTx,USART_InitStruct->HardwareFlowControl);  
}

/**
*\*\name    USART_Baud_Rate_Config
*\*\fun     Configure the baud rate of the USART.
*\*\          The baud rate is computed using the following formula:
*\*\          - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->BaudRate)))
*\*\          - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   buad_rate :
*\*\          - (((buad_rate) > 0) && ((buad_rate) < 0x00337F99))
*\*\return  none
**/
void USART_Baud_Rate_Config(USART_Module* USARTx,uint32_t buad_rate)
{
    uint32_t temp_value = 0x00, apb_clock_value = 0x00;
    uint32_t integer_divider_value    = 0x00;
    uint32_t fractional_divider_value = 0x00;
    uint32_t base_value        = 0;
    RCC_ClocksType RCC_ClocksStatus; 
    base_value = (uint32_t)USARTx;       
    RCC_Clocks_Frequencies_Value_Get(&RCC_ClocksStatus);
    if ((base_value == USART1_BASE) || (base_value == UART3_BASE) || (base_value == UART4_BASE))
    {
        apb_clock_value = RCC_ClocksStatus.Pclk2Freq;
    }
    else
    {
        apb_clock_value = RCC_ClocksStatus.Pclk1Freq;
    }

    /* Determine the integer part */
    integer_divider_value = ((25 * apb_clock_value) / (4 * buad_rate));
    temp_value = (integer_divider_value / 100) << USART_BUAD_INTEGER_OFFSET;

    /* Determine the fractional part */
    fractional_divider_value = integer_divider_value - (100 * (temp_value >> USART_BUAD_FRACTIONAL_OFFSET));

    /* Implement the fractional part in the register */   
    temp_value |= ((((fractional_divider_value * 16) + 50) / 100)) & ((uint8_t)0x0F);

    /* Write to USART PBC */
    USARTx->BRCF = (uint16_t)temp_value;

}

/**
*\*\name    USART_Word_Length_Config
*\*\fun     Configure the word length of the USART.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   word_length :
*\*\            - USART_WL_8B
*\*\            - USART_WL_9B
*\*\return  none
**/
void USART_Word_Length_Config(USART_Module* USARTx,uint16_t word_length)
{
    uint32_t temp_value   = 0x00; 
    temp_value = USARTx->CTRL1;    
    /* Clear M bit */
    temp_value &= USART_WL_MASK;
    /* Configure the USART Word Length */
    temp_value |= word_length;
    USARTx->CTRL1 = (uint16_t)temp_value;

}

/**
*\*\name    USART_Stop_Bits_Config
*\*\fun     Configure the stop bits of the USART.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   stop_bits :
*\*\            - USART_STPB_1
*\*\            - USART_STPB_0_5
*\*\            - USART_STPB_2
*\*\            - USART_STPB_1_5
*\*\return  none
**/
void USART_Stop_Bits_Config(USART_Module* USARTx,uint16_t stop_bits)
{
    uint32_t temp_value   = 0x00;
    temp_value = USARTx->CTRL2;
    /* Clear STOP[13:12] bits */
    temp_value &= CTRL2_STPB_CLR_MASK;
    /* Set STOP[13:12] bits according to stop bits value */
    temp_value |= stop_bits;
    USARTx->CTRL2 = (uint16_t)temp_value;    
}

/**
*\*\name    USART_Parity_Config
*\*\fun     Configure the parity of the USART.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   parity :
*\*\            - USART_PE_NO
*\*\            - USART_PE_EVEN
*\*\            - USART_PE_ODD
*\*\return  none
**/
void USART_Parity_Config(USART_Module* USARTx,uint16_t parity)
{
    uint32_t temp_value   = 0x00; 
    temp_value = USARTx->CTRL1;    
    /* Clear parity[10:9] bits */
    temp_value &= USART_PE_MASK;
    /* Configure the USART parity */
    temp_value |= parity;
    USARTx->CTRL1 = (uint16_t)temp_value;   
}

/**
*\*\name    USART_Mode_Config
*\*\fun     Configure the mode of the USART.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   mode :
*\*\            - USART_MODE_RX
*\*\            - USART_MODE_TX
*\*\return  none
**/
void USART_Mode_Config(USART_Module* USARTx,uint16_t mode)
{
    uint32_t temp_value   = 0x00;   
    temp_value = USARTx->CTRL1;    
    /* Clear mode[3:2] bits */
    temp_value &= USART_MODE_MASK;
    /* Configure the USART parity */
    temp_value |= mode;
    USARTx->CTRL1 = (uint16_t)temp_value; 
}

/**
*\*\name    USART_Hardware_Flow_Control_Config
*\*\fun     Configure the hardware flow control of the USART.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   hardware_flow_control :
*\*\            - USART_HFCTRL_NONE
*\*\            - USART_HFCTRL_RTS
*\*\            - USART_HFCTRL_CTS
*\*\            - USART_HFCTRL_RTS_CTS
*\*\return  none
**/
void USART_Hardware_Flow_Control_Config(USART_Module* USARTx,uint16_t hardware_flow_control)
{
    uint32_t temp_value   = 0x00;  
    temp_value = USARTx->CTRL3;    
    /* Clear hardware_flow_control[9:8] bits */
    temp_value &= USART_HFCTRL_MASK;
    /* Configure the USART hardware_flow_control */
    temp_value |= hardware_flow_control;
    USARTx->CTRL3 = (uint16_t)temp_value; 
}

/**
*\*\name    USART_Structure_Initializes.
*\*\fun     Fills each USART_InitStruct member with its default value.
*\*\param   USART_InitStruct :
*\*\          - BaudRate
*\*\          - WordLength
*\*\          - StopBits
*\*\          - Parity
*\*\          - Mode
*\*\          - HardwareFlowControl
*\*\return  none
**/

void USART_Structure_Initializes(USART_InitType* USART_InitStruct)  
{
    /* USART_InitStruct members default value */
    USART_InitStruct->BaudRate            = 9600;
    USART_InitStruct->WordLength          = USART_WL_8B;
    USART_InitStruct->StopBits            = USART_STPB_1;
    USART_InitStruct->Parity              = USART_PE_NO;
    USART_InitStruct->Mode                = USART_MODE_RX | USART_MODE_TX;
    USART_InitStruct->HardwareFlowControl = USART_HFCTRL_NONE;
}

/**
*\*\name    USART_Clock_Initializes
*\*\fun     Initializes the USARTx peripheral Clock according to the 
            specified parameters in the USART_ClockInitStruct .
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\param   USART_ClockInitStruct :
*\*\          - Clock :
*\*\            - USART_CLK_DISABLE
*\*\            - USART_CLK_ENABLE
*\*\          - Polarity
*\*\            - USART_CLKPOL_LOW
*\*\            - USART_CLKPOL_HIGH
*\*\          - Phase
*\*\            - USART_CLKPHA_1EDGE
*\*\            - USART_CLKPHA_2EDGE
*\*\          - LastBit
*\*\            - USART_CLKLB_DISABLE
*\*\            - USART_CLKLB_ENABLE
*\*\return  none
**/

void USART_Clock_Initializes(USART_Module* USARTx, USART_ClockInitType* USART_ClockInitStruct)
{
    USART_Clock_Config(USARTx,USART_ClockInitStruct->Clock);
    USART_Polarity_Config(USARTx,USART_ClockInitStruct->Polarity);
    USART_Phase_Config(USARTx,USART_ClockInitStruct->Phase);
    USART_Last_Bit_Config(USARTx,USART_ClockInitStruct->LastBit);

}

/**
*\*\name    USART_Clock_Config.
*\*\fun     Enable or disable the USART clock
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\param   clock :
*\*\          - USART_CLK_DISABLE
*\*\          - USART_CLK_ENABLE
*\*\return  none
**/

void USART_Clock_Config(USART_Module* USARTx,uint16_t clock)
{
    uint32_t temp_value = 0x00;
    temp_value = USARTx->CTRL2; 
    /* Clear CLKEN bit */  
    temp_value &= USART_CLK_MASK;   
    /* Set CLKEN bit according to clock value */
    temp_value |= clock;       
    USARTx->CTRL2 = (uint16_t)temp_value; 
}

/**
*\*\name    USART_Polarity_Config.
*\*\fun     Configure USART clock polarity.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\param   polarity :
*\*\          - USART_CLKPOL_LOW
*\*\          - USART_CLKPOL_HIGH
*\*\return  none
**/

void USART_Polarity_Config(USART_Module* USARTx,uint16_t polarity)
{
    uint32_t temp_value = 0x00;
    temp_value = USARTx->CTRL2; 
    /* Clear CLKPOL bit */  
    temp_value &= USART_CLKPOL_MASK;   
    /* Set CLKPOL bit according to clock value */
    temp_value |= polarity;       
    USARTx->CTRL2 = (uint16_t)temp_value; 
}

/**
*\*\name    USART_Phase_Config.
*\*\fun     Configure USART clock phase.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\param   phase :
*\*\          - USART_CLKPHA_1EDGE
*\*\          - USART_CLKPHA_2EDGE
*\*\return  none
**/

void USART_Phase_Config(USART_Module* USARTx,uint16_t phase)
{
    uint32_t temp_value = 0x00;
    temp_value = USARTx->CTRL2; 
    /* Clear CLKPHA bit */  
    temp_value &= USART_CLKPHA_MASK;   
    /* Set CLKPHA bit according to clock value */
    temp_value |= phase;       
    USARTx->CTRL2 = (uint16_t)temp_value; 
}

/**
*\*\name    USART_Last_Bit_Config.
*\*\fun     Configure last bit clock pulse.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\param   last_bit :
*\*\          - USART_CLKLB_DISABLE
*\*\          - USART_CLKLB_ENABLE
*\*\return  none
**/

void USART_Last_Bit_Config(USART_Module* USARTx,uint16_t last_bit)
{
    uint32_t temp_value = 0x00;
    temp_value = USARTx->CTRL2; 
    /* Clear CLKLB bit */  
    temp_value &= USART_CLKLB_MASK;   
    /* Set CLKLB bit according to clock value */
    temp_value |= last_bit;       
    USARTx->CTRL2 = (uint16_t)temp_value; 
}


/**
*\*\name    USART_Initializes_Clock_Structure.
*\*\fun     Fills each USART_ClockInitStruct member with its default value.
*\*\param   USART_ClockInitStruct :
*\*\          - Clock
*\*\          - Polarity
*\*\          - Phase
*\*\          - LastBit
*\*\return  none
**/

void USART_Clock_Structure_Initializes(USART_ClockInitType* USART_ClockInitStruct)
{
    /* USART_ClockInitStruct members default value */
    USART_ClockInitStruct->Clock    = USART_CLK_DISABLE;
    USART_ClockInitStruct->Polarity = USART_CLKPOL_LOW;
    USART_ClockInitStruct->Phase    = USART_CLKPHA_1EDGE;
    USART_ClockInitStruct->LastBit  = USART_CLKLB_DISABLE;
}


/**
*\*\name    USART_Enable.
*\*\fun     Enables the specified USART peripheral.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/
void USART_Enable(USART_Module* USARTx)  
{
    /* Enable the selected USART by setting the UE bit in the CTRL1 register */
    USARTx->CTRL1 |= CTRL1_UEN_SET;
}

/**
*\*\name    USART_Disable.
*\*\fun     Disables the specified USART peripheral.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/
void USART_Disable(USART_Module* USARTx)
{
    /* Disable the selected USART by clearing the UE bit in the CTRL1 register */
    USARTx->CTRL1 &= CTRL1_UEN_RESET;
}

/**
*\*\name    USART_Interrput_Enable.
*\*\fun     Enables the specified USART interrupts.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_interrupt :
*\*\          - USART_INT_PEF
*\*\          - USART_INT_TXDE
*\*\          - USART_INT_TXC
*\*\          - USART_INT_RXDNE
*\*\          - USART_INT_IDLEF
*\*\          - USART_INT_LINBD
*\*\          - USART_INT_CTSF
*\*\          - USART_INT_ERRF
*\*\return  none
**/

void USART_Interrput_Enable(USART_Module* USARTx, uint16_t USART_interrupt)
{
    uint32_t register_value = 0x00, interrupt_position = 0x00, temp_value = 0x00;
    uint32_t base_value = 0x00;

    base_value = (uint32_t)USARTx;

    /* Get the USART register index */
    register_value = (((uint8_t)USART_interrupt) >> USART_CTRL_INDEX_OFFSET);

    /* Get the interrupt position */
    interrupt_position  = USART_interrupt & INT_MASK;
    temp_value = (((uint32_t)0x01) << interrupt_position);

    if (register_value == 0x01) /* The IT is in CTRL1 register */
    {
        base_value += 0x0C;
    }
    else if (register_value == 0x02) /* The IT is in CTRL2 register */
    {
        base_value += 0x10;
    }
    else /* The IT is in CTRL3 register */
    {
        base_value += 0x14;
    }

    *(__IO uint32_t*)base_value |= temp_value;

}

/**
*\*\name    USART_Interrput_Disable.
*\*\fun     Disables the specified USART interrupts.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_interrupt :
*\*\          - USART_INT_PEF
*\*\          - USART_INT_TXDE
*\*\          - USART_INT_TXC
*\*\          - USART_INT_RXDNE
*\*\          - USART_INT_IDLEF
*\*\          - USART_INT_LINBD
*\*\          - USART_INT_CTSF
*\*\          - USART_INT_ERRF
*\*\return  none
**/

void USART_Interrput_Disable(USART_Module* USARTx, uint16_t USART_interrupt)
{
    uint32_t register_value = 0x00, interrupt_position = 0x00, temp_value = 0x00;
    uint32_t base_value = 0x00;
    base_value = (uint32_t)USARTx;

    /* Get the USART register index */
    register_value = (((uint8_t)USART_interrupt) >> USART_CTRL_INDEX_OFFSET);

    /* Get the interrupt position */
    interrupt_position  = USART_interrupt & INT_MASK;
    temp_value = (((uint32_t)0x01) << interrupt_position);

    if (register_value == 0x01) /* The IT is in CTRL1 register */
    {
        base_value += 0x0C;
    }
    else if (register_value == 0x02) /* The IT is in CTRL2 register */
    {
        base_value += 0x10;
    }
    else /* The IT is in CTRL3 register */
    {
        base_value += 0x14;
    }

    *(__IO uint32_t*)base_value &= ~temp_value;

}

/**
*\*\name    USART_DMA_Transfer_Enable.
*\*\fun     Enables the DMA transfer for selected requests.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_DMA_request :
*\*\          - USART_DMAREQ_TX
*\*\          - USART_DMAREQ_RX
*\*\return  none
**/

void USART_DMA_Transfer_Enable(USART_Module* USARTx, uint16_t USART_DMA_request)
{

    /* Enable the DMA transfer for selected requests by setting the DMAT and/or
        DADDR bits in the USART CTRL3 register */
    USARTx->CTRL3 |= USART_DMA_request;

}

/**
*\*\name    USART_DMA_Transfer_Disable.
*\*\fun     Disables the DMA transfer for selected requests.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_DMA_request :
*\*\          - USART_DMAREQ_TX
*\*\          - USART_DMAREQ_RX
*\*\return  none
**/

void USART_DMA_Transfer_Disable(USART_Module* USARTx, uint16_t USART_DMA_request)
{


    /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
        DADDR bits in the USART CTRL3 register */
    USARTx->CTRL3 &= (uint16_t)~USART_DMA_request;

}

/**
*\*\name    USART_Address_Set.
*\*\fun     Sets the address of the USART node.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_address :
*\*\          - (((USART_address)>=0x00)&&((USART_address)<0x10))
*\*\return  none
**/

void USART_Address_Set(USART_Module* USARTx, uint8_t USART_address)
{
    /* Clear the USART address */
    USARTx->CTRL2 &= CTRL2_ADDR_MASK;
    /* Set the USART address node */
    USARTx->CTRL2 |= USART_address;
}

/**
*\*\name    USART_WakeUp_Mode_Set.
*\*\fun     Selects the USART WakeUp method.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_wake_up_mode :
*\*\          - USART_WUM_IDLELINE
*\*\          - USART_WUM_ADDRMASK
*\*\return  none
**/

void USART_WakeUp_Mode_Set(USART_Module* USARTx, uint16_t USART_wake_up_mode)
{

    USARTx->CTRL1 &= CTRL1_WUM_MASK;
    USARTx->CTRL1 |= USART_wake_up_mode;
}

/**
*\*\name    USART_Receiver_Wakeup_Enable.
*\*\fun     Enable the USART mute mode.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/
void USART_Receiver_Wakeup_Enable(USART_Module* USARTx)
{
    /* Enable the USART mute mode  by setting the RWU bit in the CTRL1 register */
    USARTx->CTRL1 |= CTRL1_RCVWU_SET;
}

/**
*\*\name    USART_Receiver_Wakeup_Disable.
*\*\fun     Disable the USART mute mode.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/
void USART_Receiver_Wakeup_Disable(USART_Module* USARTx)
{
    /* Disable the USART mute mode by clearing the RWU bit in the CTRL1 register */
    USARTx->CTRL1 &= CTRL1_RCVWU_RESET;

}

/**
*\*\name    USART_LIN_Break_Detect_Length_Set.
*\*\fun     Sets the USART LIN Break detection length.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_LIN_break_detect_length :
*\*\          - USART_LINBDL_10B
*\*\          - USART_LINBDL_11B
*\*\return  none
**/
void USART_LIN_Break_Detect_Length_Set(USART_Module* USARTx, uint16_t USART_LIN_break_detect_length)
{
    USARTx->CTRL2 &= CTRL2_LINBDL_MASK;
    USARTx->CTRL2 |= USART_LIN_break_detect_length;
}

/**
*\*\name    USART_LIN_Enable.
*\*\fun     Enables the USART's LIN mode.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/
void USART_LIN_Enable(USART_Module* USARTx)
{

    /* Enable the LIN mode by setting the LINEN bit in the CTRL2 register */
    USARTx->CTRL2 |= CTRL2_LINMEN_SET;

}

/**
*\*\name    USART_LIN_Disable.
*\*\fun     Disables the USART's LIN mode.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/
void USART_LIN_Disable(USART_Module* USARTx)
{
    /* Disable the LIN mode by clearing the LINEN bit in the CTRL2 register */
    USARTx->CTRL2 &= CTRL2_LINMEN_RESET;
}

/**
*\*\name    USART_Data_Send.
*\*\fun     Transmits single data through the USARTx peripheral.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   data :
*\*\          - The data to transmit.
*\*\return  none
**/
void USART_Data_Send(USART_Module* USARTx, uint16_t data)
{
    /* Transmit Data */
    USARTx->DAT = (data & (uint16_t)0x01FF);
}

/**
*\*\name    USART_Data_Receive.
*\*\fun     Returns the most recent received data by the USARTx peripheral.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  The received data.
**/
uint16_t USART_Data_Receive(USART_Module* USARTx)
{
    /* Receive Data */
    return (uint16_t)(USARTx->DAT & (uint16_t)0x01FF);
}

/**
*\*\name    USART_Break_Frame_Send.
*\*\fun     Transmits break characters.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/
void USART_Break_Frame_Send(USART_Module* USARTx)
{
    /* Send break characters */
    USARTx->CTRL1 |= CTRL1_SDBRK_SET;
}

/**
*\*\name    USART_Guard_Time_Set.
*\*\fun     Sets the specified USART guard time.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\param   USART_guard_time :
*\*\          - Specifies the guard time
*\*\return  none
**/
void USART_Guard_Time_Set(USART_Module* USARTx, uint8_t USART_guard_time)
{
    /* Clear the USART Guard time */
    USARTx->GTP &= GTP_LSB_MASK;
    /* Set the USART guard time */
    USARTx->GTP |= (uint16_t)((uint16_t)USART_guard_time << USART_GTP_GTV_OFFSET);
}

/**
*\*\name    USART_prescaler_Set.
*\*\fun     Sets the system clock prescaler.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_prescaler :
*\*\          - Specifies the prescaler clock.
*\*\return  none
**/
void USART_Prescaler_Set(USART_Module* USARTx, uint8_t USART_prescaler)
{
    /* Clear the USART prescaler */
    USARTx->GTP &= GTP_MSB_MASK;
    /* Set the USART prescaler */
    USARTx->GTP |= USART_prescaler;
}

/**
*\*\name    USART_Smart_Card_Enable.
*\*\fun     Enables the USART's Smart Card mode.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\return  none
**/

void USART_Smart_Card_Enable(USART_Module* USARTx)
{

    
    /* Enable the SC mode by setting the SCEN bit in the CTRL3 register */
    USARTx->CTRL3 |= CTRL3_SCMEN_SET;

}

/**
*\*\name    USART_Smart_Card_Disable.
*\*\fun     Disables the USART's Smart Card mode.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\return  none
**/

void USART_Smart_Card_Disable(USART_Module* USARTx)
{
    /* Disable the Smart Card mode by clearing the SCEN bit in the CTRL3 register */
    USARTx->CTRL3 &= CTRL3_SCMEN_RESET;
}

/**
*\*\name    USART_Smart_Card_NACK_Enable.
*\*\fun     Enables Smart Card NACK transmission.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\return  none
**/
void USART_Smart_Card_NACK_Enable(USART_Module* USARTx)
{

    /* Enable the Smart Card NACK transmission by setting the NACK bit in the CTRL3 register */
    USARTx->CTRL3 |= CTRL3_SCNACK_SET;

}

/**
*\*\name    USART_Smart_Card_NACK_Disable.
*\*\fun     Disables NACK transmission.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\return  none
**/
void USART_Smart_Card_NACK_Disable(USART_Module* USARTx)
{

    /* Disable the NACK transmission by clearing the NACK bit in the CTRL3 register */
    USARTx->CTRL3 &= CTRL3_SCNACK_RESET;

}

/**
*\*\name    USART_Half_Duplex_Enable.
*\*\fun     Enables the USART's Half Duplex communication.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/

void USART_Half_Duplex_Enable(USART_Module* USARTx)
{

    /* Enable the Half-Duplex mode by setting the HDSEL bit in the CTRL3 register */
    USARTx->CTRL3 |= CTRL3_HDMEN_SET;

}

/**
*\*\name    USART_Half_Duplex_Disable.
*\*\fun     Disables the USART's Half Duplex communication.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/

void USART_Half_Duplex_Disable(USART_Module* USARTx)
{

    /* Disable the Half-Duplex mode by clearing the HDSEL bit in the CTRL3 register */
    USARTx->CTRL3 &= CTRL3_HDMEN_RESET;

}

/**
*\*\name    USART_IrDA_Mode_Set.
*\*\fun     Configures the USART's IrDA interface.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_IrDA_mode :
*\*\          - USART_IRDAMODE_LOWPPWER
*\*\          - USART_IRDAMODE_NORMAL
*\*\return  none
**/

void USART_IrDA_Mode_Set(USART_Module* USARTx, uint16_t USART_IrDA_mode)
{

    USARTx->CTRL3 &= CTRL3_IRDALP_MASK;
    USARTx->CTRL3 |= USART_IrDA_mode;
}

/**
*\*\name    USART_IrDA_Enable.
*\*\fun     Enables the USART's IrDA interface.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/

void USART_IrDA_Enable(USART_Module* USARTx)
{

    /* Enable the IrDA mode by setting the IREN bit in the CTRL3 register */
    USARTx->CTRL3 |= CTRL3_IRDAMEN_SET;

}

/**
*\*\name    USART_IrDA_Disable.
*\*\fun     Disables the USART's IrDA interface.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\return  none
**/

void USART_IrDA_Disable(USART_Module* USARTx)
{

    /* Disable the IrDA mode by clearing the IREN bit in the CTRL3 register */
    USARTx->CTRL3 &= CTRL3_IRDAMEN_RESET;

}

/**
*\*\name    USART_Flag_Status_Get.
*\*\fun     Checks whether the specified USART flag is set or not.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_flag :
*\*\          - USART_FLAG_CTSF
*\*\          - USART_FLAG_LINBD
*\*\          - USART_FLAG_TXDE
*\*\          - USART_FLAG_TXC
*\*\          - USART_FLAG_RXDNE
*\*\          - USART_FLAG_IDLEF
*\*\          - USART_FLAG_OREF
*\*\          - USART_FLAG_NEF
*\*\          - USART_FLAG_FEF
*\*\          - USART_FLAG_PEF
*\*\return  SET or RESET
**/

FlagStatus USART_Flag_Status_Get(USART_Module* USARTx, uint16_t USART_flag)
{

    if ((USARTx->STS & USART_flag) != (uint16_t)RESET)
    {
       return SET;
    }
    else
    {
        return RESET;
    }

}

/**
*\*\name    USART_Flag_Clear.
*\*\fun     Clears the USARTx's pending flags.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_flag :
*\*\          - USART_FLAG_CTSF
*\*\          - USART_FLAG_LINBD
*\*\          - USART_FLAG_TXC
*\*\          - USART_FLAG_RXDNE
*\*\return  none
**/

void USART_Flag_Clear(USART_Module* USARTx, uint16_t USART_flag)
{

    USARTx->STS = (uint16_t)~USART_flag;
}

/**
*\*\name    USART_Interrupt_Status_Get.
*\*\fun     Checks whether the specified USART interrupt has occurred or not.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_interrupt :
*\*\          - USART_INT_CTSF
*\*\          - USART_INT_LINBD
*\*\          - USART_INT_TXDE
*\*\          - USART_INT_TXC
*\*\          - USART_INT_RXDNE
*\*\          - USART_INT_IDLEF
*\*\          - USART_INT_OREF
*\*\          - USART_INT_NEF
*\*\          - USART_INT_FEF
*\*\          - USART_INT_PEF
*\*\return  SET or RESET
**/

INTStatus USART_Interrupt_Status_Get(USART_Module* USARTx, uint16_t USART_interrupt)
{
    uint32_t bit_position = 0x00, temp_value = 0x00, register_value = 0x00;



    /* Get the USART register index */
    register_value = (((uint8_t)USART_interrupt) >> USART_CTRL_INDEX_OFFSET);
    /* Get the interrupt position */
    temp_value = USART_interrupt & INT_MASK;
    temp_value = (uint32_t)0x01 << temp_value;

    if (register_value == 0x01) /* The IT  is in CTRL1 register */
    {
        temp_value &= USARTx->CTRL1;
    }
    else if (register_value == 0x02) /* The IT  is in CTRL2 register */
    {
        temp_value &= USARTx->CTRL2;
    }
    else /* The IT  is in CTRL3 register */
    {
        temp_value &= USARTx->CTRL3;
    }

    bit_position = USART_interrupt >> USART_STS_INT_BIT_OFFSET;
    bit_position = (uint32_t)0x01 << bit_position;
    bit_position &= USARTx->STS;
    if ((temp_value != (uint16_t)RESET) && (bit_position != (uint16_t)RESET))
    {
        return SET;
    }
    else
    {
        return RESET;
    }


}

/**
*\*\name    USART_Interrupt_Status_Clear.
*\*\fun     Clears the USARTx's interrupt Status.
*\*\param   USARTx :
*\*\          - USART1
*\*\          - USART2
*\*\          - UART3
*\*\          - UART4
*\*\param   USART_Interrupt :
*\*\          - USART_INT_CTSF
*\*\          - USART_INT_LINBD
*\*\          - USART_INT_TXC
*\*\          - USART_INT_RXDNE
*\*\return  none
**/

void USART_Interrupt_Status_Clear(USART_Module* USARTx, uint16_t USART_Interrupt)
{
    uint16_t bit_position = 0x00, temp_value = 0x00;

    bit_position      = USART_Interrupt >> USART_STS_INT_BIT_OFFSET;
    temp_value    = ((uint16_t)0x01 << (uint16_t)bit_position);
    USARTx->STS = (uint16_t)~temp_value;
}

