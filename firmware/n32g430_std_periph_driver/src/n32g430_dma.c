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
*\*\file n32g430_dma.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#include "n32g430_dma.h"
#include "n32g430_rcc.h"

/** DMA Private Defines **/


/** DMA Driving Functions Declaration **/

/**
*\*\name    DMA_Deinitializes.
*\*\fun     Reset DMA Channelx registers.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\return  none
**/
void DMA_Reset(DMA_ChannelType* DMAChx)
{
    /* Disable the selected DMA Channelx */
    DMAChx->CHCFG &= ~DMA_CHANNEL_ENABLE;

    /* Reset DMA Channelx control register */
    DMAChx->CHCFG = 0;

    /* Reset DMA Channelx remaining bytes register */
    DMAChx->TXNUM = 0;

    /* Reset DMA Channelx peripheral address register */
    DMAChx->PADDR = 0;

    /* Reset DMA Channelx memory address register */
    DMAChx->MADDR = 0;
    
    if (DMAChx == DMA_CH1)
    {
        /* Reset interrupt pending bits for DMA Channel1 */
        DMA->INTCLR |= DMA_CH1_INT_MASK;
    }
    else if (DMAChx == DMA_CH2)
    {
        /* Reset interrupt pending bits for DMA Channel2 */
        DMA->INTCLR |= DMA_CH2_INT_MASK;
    }
    else if (DMAChx == DMA_CH3)
    {
        /* Reset interrupt pending bits for DMA Channel3 */
        DMA->INTCLR |= DMA_CH3_INT_MASK;
    }
    else if (DMAChx == DMA_CH4)
    {
        /* Reset interrupt pending bits for DMA Channel4 */
        DMA->INTCLR |= DMA_CH4_INT_MASK;
    }
    else if (DMAChx == DMA_CH5)
    {
        /* Reset interrupt pending bits for DMA Channel5 */
        DMA->INTCLR |= DMA_CH5_INT_MASK;
    }
    else if (DMAChx == DMA_CH6)
    {
        /* Reset interrupt pending bits for DMA Channel6 */
        DMA->INTCLR |= DMA_CH6_INT_MASK;
    }
    else if (DMAChx == DMA_CH7)
    {
        /* Reset interrupt pending bits for DMA Channel7 */
        DMA->INTCLR |= DMA_CH7_INT_MASK;
    }
    else if (DMAChx == DMA_CH8)
    {
        /* Reset interrupt pending bits for DMA Channel8 */
        DMA->INTCLR |= DMA_CH8_INT_MASK;
    }
}

/**
*\*\name    DMA_Initializes.
*\*\fun     Initializes the DMA Channelx according to DMA_InitParam.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   DMA_InitParam :
*\*\          - PeriphAddr
*\*\          - MemAddr
*\*\          - Direction
*\*\            - DMA_DIR_PERIPH_DST
*\*\            - DMA_DIR_PERIPH_SRC
*\*\          - BufSize
*\*\          - PeriphInc
*\*\            - DMA_PERIPH_INC_MODE_ENABLE
*\*\            - DMA_PERIPH_INC_MODE_DISABLE
*\*\          - MemoryInc
*\*\            - DMA_MEM_INC_MODE_ENABLE
*\*\            - DMA_MEM_INC_MODE_DISABLE
*\*\          - PeriphDataSize
*\*\            - DMA_PERIPH_DATA_WIDTH_BYTE
*\*\            - DMA_PERIPH_DATA_WIDTH_HALFWORD
*\*\            - DMA_PERIPH_DATA_WIDTH_WORD
*\*\          - MemDataSize
*\*\            - DMA_MEM_DATA_WIDTH_BYTE
*\*\            - DMA_MEM_DATA_WIDTH_HALFWORD
*\*\            - DMA_MEM_DATA_WIDTH_WORD
*\*\          - CircularMode
*\*\            - DMA_CIRCULAR_MODE_ENABLE
*\*\            - DMA_CIRCULAR_MODE_DISABLE
*\*\          - Priority
*\*\            - DMA_CH_PRIORITY_HIGHEST
*\*\            - DMA_CH_PRIORITY_HIGH
*\*\            - DMA_CH_PRIORITY_MEDIUM
*\*\            - DMA_CH_PRIORITY_LOW
*\*\          - Mem2Mem
*\*\            - DMA_MEM2MEM_ENABLE
*\*\            - DMA_MEM2MEM_DISABLE
*\*\return  none
**/
void DMA_Initializes(DMA_ChannelType* DMAChx, DMA_InitType* DMA_InitParam)
{
    DMA_Peripheral_Address_Config(DMAChx, DMA_InitParam->PeriphAddr);
    DMA_Memory_Address_Config(DMAChx, DMA_InitParam->MemAddr);
    DMA_Destination_Config(DMAChx, DMA_InitParam->Direction);
    DMA_Buffer_Size_Config(DMAChx, DMA_InitParam->BufSize);
    DMA_Peripheral_Addr_Increment_Config(DMAChx, DMA_InitParam->PeriphInc);
    DMA_Memory_Addr_Increment_Config(DMAChx, DMA_InitParam->MemoryInc);
    DMA_Peripheral_Data_Width_Config(DMAChx, DMA_InitParam->PeriphDataSize);
    DMA_Memory_Data_Width_Config(DMAChx, DMA_InitParam->MemDataSize);
    DMA_Circular_Mode_Config(DMAChx, DMA_InitParam->CircularMode);
    DMA_Priority_Config(DMAChx, DMA_InitParam->Priority);
    DMA_Memory_2_Memory_Config(DMAChx, DMA_InitParam->Mem2Mem);
}

/**
*\*\name    DMA_Peripheral_Address_Config.
*\*\fun     Initializes the DMA Channelx peripheral address.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   addr :
*\*\return  none
**/
void DMA_Peripheral_Address_Config(DMA_ChannelType* DMAChx, uint32_t addr)
{
    /* Write to DMA Channelx PADDR */
    DMAChx->PADDR = addr;
}

/**
*\*\name    DMA_Memory_Address_Config.
*\*\fun     Initializes the DMA Channelx memory address.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   addr :
*\*\return  none
**/
void DMA_Memory_Address_Config(DMA_ChannelType* DMAChx, uint32_t addr)
{
    /* Write to DMA Channelx MADDR */
    DMAChx->MADDR = addr;
}

/**
*\*\name    DMA_Destination_Config.
*\*\fun     Initializes the DMA Channelx Direction value.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   direction :
*\*\          - DMA_DIR_PERIPH_DST
*\*\          - DMA_DIR_PERIPH_SRC
*\*\return  none
**/
void DMA_Destination_Config(DMA_ChannelType* DMAChx, uint32_t direction)
{
    /* Clear DMAChx_CHCFG DIR bits */
    DMAChx->CHCFG &= DMA_DIR_PERIPH_MASK;
    /* Set DMAChx_CHCFG DIR bits */
    DMAChx->CHCFG |= direction;
}

/**
*\*\name    DMA_Buffer_Size_Config.
*\*\fun     Initializes the DMA Channelx buffer size.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   buf_size :
*\*\return  none
**/
void DMA_Buffer_Size_Config(DMA_ChannelType* DMAChx, uint32_t buf_size)
{
    /* Write to DMA Channelx TXNUM */
    DMAChx->TXNUM = buf_size;
}

/**
*\*\name    DMA_Peripheral_Addr_Increment_Config.
*\*\fun     Initializes the DMA Channelx PeriphInc value.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   periph_inc :
*\*\          - DMA_PERIPH_INC_MODE_ENABLE
*\*\          - DMA_PERIPH_INC_MODE_DISABLE
*\*\return  none
**/
void DMA_Peripheral_Addr_Increment_Config(DMA_ChannelType* DMAChx, uint32_t periph_inc)
{
    /* Clear DMAChx_CHCFG PINC bits */
    DMAChx->CHCFG &= DMA_PERIPH_INC_MODE_MASK;
    /* Set DMAChx_CHCFG PINC bits */
    DMAChx->CHCFG |= periph_inc;
}

/**
*\*\name    DMA_Memory_Addr_Increment_Config.
*\*\fun     Initializes the DMA Channelx DMA_MemoryInc value.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   memory_inc :
*\*\          - DMA_MEM_INC_MODE_ENABLE
*\*\          - DMA_MEM_INC_MODE_DISABLE
*\*\return  none
**/
void DMA_Memory_Addr_Increment_Config(DMA_ChannelType* DMAChx, uint32_t memory_inc)
{
    /* Clear DMAChx_CHCFG MINC bits */
    DMAChx->CHCFG &= DMA_MEM_INC_MODE_MASK;
    /* Set DMAChx_CHCFG MINC bits */
    DMAChx->CHCFG |= memory_inc;
}

/**
*\*\name    DMA_Peripheral_Data_Width_Config.
*\*\fun     Initializes the DMA Channelx PeriphDataSize value.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   width :
*\*\          - DMA_PERIPH_DATA_WIDTH_BYTE
*\*\          - DMA_PERIPH_DATA_WIDTH_HALFWORD
*\*\          - DMA_PERIPH_DATA_WIDTH_WORD
*\*\return  none
**/
void DMA_Peripheral_Data_Width_Config(DMA_ChannelType* DMAChx, uint32_t width)
{
    /* Clear DMAChx_CHCFG PSIZE[1:0] bits */
    DMAChx->CHCFG &= DMA_PERIPH_DATA_WIDTH_MASK;
    /* Set DMAChx_CHCFG PSIZE[1:0] bits */
    DMAChx->CHCFG |= width;
}

/**
*\*\name    DMA_Memory_Data_Width_Config.
*\*\fun     Initializes the DMA Channelx MemDataSize value.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   width :
*\*\          - DMA_MEM_DATA_WIDTH_BYTE
*\*\          - DMA_MEM_DATA_WIDTH_HALFWORD
*\*\          - DMA_MEM_DATA_WIDTH_WORD
*\*\return  none
**/
void DMA_Memory_Data_Width_Config(DMA_ChannelType* DMAChx, uint32_t width)
{
    /* Clear DMAChx_CHCFG MSIZE[1:0] bits */
    DMAChx->CHCFG &= DMA_MEM_DATA_WIDTH_MASK;
    /* Set DMAChx_CHCFG MSIZE[1:0] bits */
    DMAChx->CHCFG |= width;
}

/**
*\*\name    DMA_Circular_Mode_Config.
*\*\fun     Initializes the DMA Channelx CircularMode value.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   cmd :
*\*\          - DMA_CIRCULAR_MODE_ENABLE
*\*\          - DMA_CIRCULAR_MODE_DISABLE
*\*\return  none
**/
void DMA_Circular_Mode_Config(DMA_ChannelType* DMAChx, uint32_t cmd)
{
   /* Clear DMAChx_CHCFG CIRC bits */
    DMAChx->CHCFG &= DMA_CIRCULAR_MODE_MASK;
    /* Set DMAChx_CHCFG CIRC bits */
    DMAChx->CHCFG |= cmd;
}

/**
*\*\name    DMA_Priority_Config.
*\*\fun     Initializes the DMA Channelx Priority value.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   priority :
*\*\          - DMA_CH_PRIORITY_HIGHEST
*\*\          - DMA_CH_PRIORITY_HIGH
*\*\          - DMA_CH_PRIORITY_MEDIUM
*\*\          - DMA_CH_PRIORITY_LOW
*\*\return  none
**/
void DMA_Priority_Config(DMA_ChannelType* DMAChx, uint32_t priority)
{
    /* Clear DMAChx_CHCFG PRIOLVL[1:0] bits */
    DMAChx->CHCFG &= DMA_CH_PRIORITY_MASK;
    /* Set DMAChx_CHCFG PRIOLVL[1:0] bits */
    DMAChx->CHCFG |= priority;
}

/**
*\*\name    DMA_Memory_2_Memory_Config.
*\*\fun     Initializes the DMA Channelx Mem2Mem value.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   cmd :
*\*\          - DMA_MEM2MEM_ENABLE
*\*\          - DMA_MEM2MEM_DISABLE
*\*\return  none
**/
void DMA_Memory_2_Memory_Config(DMA_ChannelType* DMAChx, uint32_t cmd)
{
    /* Clear DMAChx_CHCFG MEM2MEM bits */
    DMAChx->CHCFG &= DMA_MEM2MEM_MASK;
    /* Set DMAChx_CHCFG MEM2MEM bits */
    DMAChx->CHCFG |= cmd;
}

/**
*\*\name    DMA_Structure_Initializes.
*\*\fun     Fills each DMA_InitParam member with its default value.
*\*\param   DMA_InitParam :
*\*\          - PeriphAddr
*\*\          - MemAddr
*\*\          - Direction
*\*\          - BufSize
*\*\          - PeriphInc
*\*\          - DMA_MemoryInc
*\*\          - PeriphDataSize
*\*\          - MemDataSize
*\*\          - CircularMode
*\*\          - Priority
*\*\          - Mem2Mem
*\*\return  none
**/
void DMA_Structure_Initializes(DMA_InitType* DMA_InitParam)
{
    /* Reset DMA init structure parameters values */
    /* Initialize the PeriphAddr member */
    DMA_InitParam->PeriphAddr = 0;
    /* Initialize the MemAddr member */
    DMA_InitParam->MemAddr = 0;
    /* Initialize the Direction member */
    DMA_InitParam->Direction = DMA_DIR_PERIPH_SRC;
    /* Initialize the BufSize member */
    DMA_InitParam->BufSize = 0;
    /* Initialize the PeriphInc member */
    DMA_InitParam->PeriphInc = DMA_PERIPH_INC_MODE_DISABLE;
    /* Initialize the MemoryInc member */
    DMA_InitParam->MemoryInc = DMA_MEM_INC_MODE_DISABLE;
    /* Initialize the PeriphDataSize member */
    DMA_InitParam->PeriphDataSize = DMA_PERIPH_DATA_WIDTH_BYTE;
    /* Initialize the MemDataSize member */
    DMA_InitParam->MemDataSize = DMA_MEM_DATA_WIDTH_BYTE;
    /* Initialize the CircularMode member */
    DMA_InitParam->CircularMode = DMA_CIRCULAR_MODE_DISABLE;
    /* Initialize the Priority member */
    DMA_InitParam->Priority = DMA_CH_PRIORITY_LOW;
    /* Initialize the Mem2Mem member */
    DMA_InitParam->Mem2Mem = DMA_MEM2MEM_DISABLE;
}

/**
*\*\name    DMA_Channel_Enable.
*\*\fun     DMA Channelx Channel enable.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\return  none
**/
void DMA_Channel_Enable(DMA_ChannelType* DMAChx)
{
    /* Enable the selected DMA Channelx */
    DMAChx->CHCFG |= DMA_CHANNEL_ENABLE;
}

/**
*\*\name    DMA_Channel_Disable.
*\*\fun     DMA Channelx Channel disable.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\return  none
**/
void DMA_Channel_Disable(DMA_ChannelType* DMAChx)
{
    /* Disable the selected DMA Channelx */
    DMAChx->CHCFG &= DMA_CHANNEL_DISABLE;
}

/**
*\*\name    DMA_Interrupts_Enable.
*\*\fun     DMA Channelx interrupts disable.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   interrupt :
*\*\          - DMA_INT_TXC
*\*\          - DMA_INT_HTX
*\*\          - DMA_INT_ERR
*\*\return  none
**/
void DMA_Interrupts_Enable(DMA_ChannelType* DMAChx, uint32_t interrupt)
{
    /* Enable the selected DMA Channelx interrupts */
    DMAChx->CHCFG |= interrupt;
}

/**
*\*\name    DMA_Interrupts_Disable.
*\*\fun     DMA Channelx interrupts disable.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   interrupt :
*\*\          - DMA_INT_TXC
*\*\          - DMA_INT_HTX
*\*\          - DMA_INT_ERR
*\*\return  none
**/
void DMA_Interrupts_Disable(DMA_ChannelType* DMAChx, uint32_t interrupt)
{
    /* Disable the selected DMA Channelx interrupts */
    DMAChx->CHCFG &= (~interrupt);
}

/**
*\*\name    DMA_Current_Data_Transfer_Number_Set.
*\*\fun     DMA Channelx Set the current number of data transfers.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   num :
*\*\note    This function can only be used when the DMAChx is disabled.
*\*\return  none
**/
void DMA_Current_Data_Transfer_Number_Set(DMA_ChannelType* DMAChx, uint16_t num)
{
    /* Write to DMA Channelx TXNUM */
    DMAChx->TXNUM = num;
}

/**
*\*\name    DMA_Current_Data_Transfer_Number_Get.
*\*\fun     DMA Channelx Gets the current number of data transfers.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\return  Returns the number of bytes remaining to be transferred.
**/
uint16_t DMA_Current_Data_Transfer_Number_Get(DMA_ChannelType* DMAChx)
{
    /* Returns the number of bytes remaining to be transferred for DMA Channelx */
    return ((uint16_t)(DMAChx->TXNUM));
}

/**
*\*\name    DMA_Flag_Status_Get.
*\*\fun     Get DMA Channelx flag status.
*\*\param   DMAx :
*\*\          - DMA
*\*\param   flag :
*\*\          - DMA_CH1_GLBF
*\*\          - DMA_CH1_TXCF
*\*\          - DMA_CH1_HTXF
*\*\          - DMA_CH1_ERRF
*\*\          - DMA_CH2_GLBF
*\*\          - DMA_CH2_TXCF
*\*\          - DMA_CH2_HTXF
*\*\          - DMA_CH2_ERRF
*\*\          - DMA_CH3_GLBF
*\*\          - DMA_CH3_TXCF
*\*\          - DMA_CH3_HTXF
*\*\          - DMA_CH3_ERRF
*\*\          - DMA_CH4_GLBF
*\*\          - DMA_CH4_TXCF
*\*\          - DMA_CH4_HTXF
*\*\          - DMA_CH4_ERRF
*\*\          - DMA_CH5_GLBF
*\*\          - DMA_CH5_TXCF
*\*\          - DMA_CH5_HTXF
*\*\          - DMA_CH5_ERRF
*\*\          - DMA_CH6_GLBF
*\*\          - DMA_CH6_TXCF
*\*\          - DMA_CH6_HTXF
*\*\          - DMA_CH6_ERRF
*\*\          - DMA_CH7_GLBF
*\*\          - DMA_CH7_TXCF
*\*\          - DMA_CH7_HTXF
*\*\          - DMA_CH7_ERRF
*\*\          - DMA_CH8_GLBF
*\*\          - DMA_CH8_TXCF
*\*\          - DMA_CH8_HTXF
*\*\          - DMA_CH8_ERRF
*\*\return  SET or RESET.
**/
FlagStatus DMA_Flag_Status_Get(DMA_Module* DMAx, uint32_t flag)
{
    /* Check the status of the DMA flag */
    if ((DMAx->INTSTS & flag) == (uint32_t)RESET)
    {
        /* DMA_CHx_Flag is reset */
        return RESET;
    }
    else
    {
        /* DMA_CHx_Flag is set */
        return SET;
    }
}

/**
*\*\name    DMA_Flag_Status_Clear.
*\*\fun     Clear DMA Channelx flag status.
*\*\param   DMAx :
*\*\          - DMA
*\*\param   flag :
*\*\          - DMA_CH1_GLBF
*\*\          - DMA_CH1_TXCF
*\*\          - DMA_CH1_HTXF
*\*\          - DMA_CH1_ERRF
*\*\          - DMA_CH2_GLBF
*\*\          - DMA_CH2_TXCF
*\*\          - DMA_CH2_HTXF
*\*\          - DMA_CH2_ERRF
*\*\          - DMA_CH3_GLBF
*\*\          - DMA_CH3_TXCF
*\*\          - DMA_CH3_HTXF
*\*\          - DMA_CH3_ERRF
*\*\          - DMA_CH4_GLBF
*\*\          - DMA_CH4_TXCF
*\*\          - DMA_CH4_HTXF
*\*\          - DMA_CH4_ERRF
*\*\          - DMA_CH5_GLBF
*\*\          - DMA_CH5_TXCF
*\*\          - DMA_CH5_HTXF
*\*\          - DMA_CH5_ERRF
*\*\          - DMA_CH6_GLBF
*\*\          - DMA_CH6_TXCF
*\*\          - DMA_CH6_HTXF
*\*\          - DMA_CH6_ERRF
*\*\          - DMA_CH7_GLBF
*\*\          - DMA_CH7_TXCF
*\*\          - DMA_CH7_HTXF
*\*\          - DMA_CH7_ERRF
*\*\          - DMA_CH8_GLBF
*\*\          - DMA_CH8_TXCF
*\*\          - DMA_CH8_HTXF
*\*\          - DMA_CH8_ERRF
*\*\return  none.
**/
void DMA_Flag_Status_Clear(DMA_Module* DMAx, uint32_t flag)
{
    /* Clear DMA flags */
    DMAx->INTCLR = flag;
}

/**
*\*\name    DMA_Interrupt_Status_Get.
*\*\fun     Get DMA Channelx interrupt status.
*\*\param   DMA :
*\*\          - DMA
*\*\param   interrupt :
*\*\          - DMA_CH1_INT_GLB
*\*\          - DMA_CH1_INT_TXC
*\*\          - DMA_CH1_INT_HTX
*\*\          - DMA_CH1_INT_ERR
*\*\          - DMA_CH2_INT_GLB
*\*\          - DMA_CH2_INT_TXC
*\*\          - DMA_CH2_INT_HTX
*\*\          - DMA_CH2_INT_ERR
*\*\          - DMA_CH3_INT_GLB
*\*\          - DMA_CH3_INT_TXC
*\*\          - DMA_CH3_INT_HTX
*\*\          - DMA_CH3_INT_ERR
*\*\          - DMA_CH4_INT_GLB
*\*\          - DMA_CH4_INT_TXC
*\*\          - DMA_CH4_INT_HTX
*\*\          - DMA_CH4_INT_ERR
*\*\          - DMA_CH5_INT_GLB
*\*\          - DMA_CH5_INT_TXC
*\*\          - DMA_CH5_INT_HTX
*\*\          - DMA_CH5_INT_ERR
*\*\          - DMA_CH6_INT_GLB
*\*\          - DMA_CH6_INT_TXC
*\*\          - DMA_CH6_INT_HTX
*\*\          - DMA_CH6_INT_ERR
*\*\          - DMA_CH7_INT_GLB
*\*\          - DMA_CH7_INT_TXC
*\*\          - DMA_CH7_INT_HTX
*\*\          - DMA_CH7_INT_ERR
*\*\          - DMA_CH8_INT_GLB
*\*\          - DMA_CH8_INT_TXC
*\*\          - DMA_CH8_INT_HTX
*\*\          - DMA_CH8_INT_ERR
*\*\return  SET or RESET.
**/
INTStatus DMA_Interrupt_Status_Get(DMA_Module* DMAx, uint32_t interrupt)
{
    /* Check the status of the specified DMA interrupt */
    if ((DMAx->INTSTS & interrupt) == (uint32_t)RESET)
    {
        /* DMA_CHx_IT is reset */
        return RESET;
    }
    else
    {
        /* DMA_CHx_IT is set */
        return SET;
    }
}

/**
*\*\name    DMA_Interrupt_Status_Clear.
*\*\fun     Clear DMA Channelx interrupt status bits.
*\*\param   DMAx :
*\*\          - DMA
*\*\param   interrupt :
*\*\          - DMA_CH1_INT_GLB
*\*\          - DMA_CH1_INT_TXC
*\*\          - DMA_CH1_INT_HTX
*\*\          - DMA_CH1_INT_ERR
*\*\          - DMA_CH2_INT_GLB
*\*\          - DMA_CH2_INT_TXC
*\*\          - DMA_CH2_INT_HTX
*\*\          - DMA_CH2_INT_ERR
*\*\          - DMA_CH3_INT_GLB
*\*\          - DMA_CH3_INT_TXC
*\*\          - DMA_CH3_INT_HTX
*\*\          - DMA_CH3_INT_ERR
*\*\          - DMA_CH4_INT_GLB
*\*\          - DMA_CH4_INT_TXC
*\*\          - DMA_CH4_INT_HTX
*\*\          - DMA_CH4_INT_ERR
*\*\          - DMA_CH5_INT_GLB
*\*\          - DMA_CH5_INT_TXC
*\*\          - DMA_CH5_INT_HTX
*\*\          - DMA_CH5_INT_ERR
*\*\          - DMA_CH6_INT_GLB
*\*\          - DMA_CH6_INT_TXC
*\*\          - DMA_CH6_INT_HTX
*\*\          - DMA_CH6_INT_ERR
*\*\          - DMA_CH7_INT_GLB
*\*\          - DMA_CH7_INT_TXC
*\*\          - DMA_CH7_INT_HTX
*\*\          - DMA_CH7_INT_ERR
*\*\          - DMA_CH8_INT_GLB
*\*\          - DMA_CH8_INT_TXC
*\*\          - DMA_CH8_INT_HTX
*\*\          - DMA_CH8_INT_ERR
*\*\return  none.
**/
void DMA_Interrupt_Status_Clear(DMA_Module* DMAx, uint32_t interrupt)
{
    /* Clear the selected DMA interrupt status bits */
    DMAx->INTCLR = interrupt;
}

/**
*\*\name    DMA_Channel_Request_Remap.
*\*\fun     Set DMA Channelx's remap request.
*\*\param   DMAChx :
*\*\          - DMA_CH1
*\*\          - DMA_CH2
*\*\          - DMA_CH3
*\*\          - DMA_CH4
*\*\          - DMA_CH5
*\*\          - DMA_CH6
*\*\          - DMA_CH7
*\*\          - DMA_CH8
*\*\param   req_remap :
*\*\          - DMA_REMAP_ADC
*\*\          - DMA_REMAP_USART1_TX
*\*\          - DMA_REMAP_USART1_RX
*\*\          - DMA_REMAP_USART2_TX
*\*\          - DMA_REMAP_USART2_RX
*\*\          - DMA_REMAP_UART3_TX
*\*\          - DMA_REMAP_UART3_RX
*\*\          - DMA_REMAP_UART4_TX
*\*\          - DMA_REMAP_UART4_RX
*\*\          - DMA_REMAP_SPI1_TX
*\*\          - DMA_REMAP_SPI1_RX
*\*\          - DMA_REMAP_SPI2_TX
*\*\          - DMA_REMAP_SPI2_RX
*\*\          - DMA_REMAP_I2C1_TX
*\*\          - DMA_REMAP_I2C1_RX
*\*\          - DMA_REMAP_I2C2_TX
*\*\          - DMA_REMAP_I2C2_RX
*\*\          - DMA_REMAP_TIM1_CH1
*\*\          - DMA_REMAP_TIM1_CH2
*\*\          - DMA_REMAP_TIM1_CH3
*\*\          - DMA_REMAP_TIM1_CH4
*\*\          - DMA_REMAP_TIM1_COM
*\*\          - DMA_REMAP_TIM1_UP
*\*\          - DMA_REMAP_TIM1_TRIG
*\*\          - DMA_REMAP_TIM2_CH1
*\*\          - DMA_REMAP_TIM2_CH2
*\*\          - DMA_REMAP_TIM2_CH3
*\*\          - DMA_REMAP_TIM2_CH4
*\*\          - DMA_REMAP_TIM2_UP
*\*\          - DMA_REMAP_TIM3_CH1
*\*\          - DMA_REMAP_TIM3_CH3
*\*\          - DMA_REMAP_TIM3_CH4
*\*\          - DMA_REMAP_TIM3_UP
*\*\          - DMA_REMAP_TIM3_TRIG
*\*\          - DMA_REMAP_TIM4_CH1
*\*\          - DMA_REMAP_TIM4_CH2
*\*\          - DMA_REMAP_TIM4_CH3
*\*\          - DMA_REMAP_TIM4_UP
*\*\          - DMA_REMAP_TIM5_CH1
*\*\          - DMA_REMAP_TIM5_CH2
*\*\          - DMA_REMAP_TIM5_CH3
*\*\          - DMA_REMAP_TIM5_CH4
*\*\          - DMA_REMAP_TIM5_UP
*\*\          - DMA_REMAP_TIM5_TRIG
*\*\          - DMA_REMAP_TIM6_UP
*\*\          - DMA_REMAP_TIM8_CH1
*\*\          - DMA_REMAP_TIM8_CH2
*\*\          - DMA_REMAP_TIM8_CH3
*\*\          - DMA_REMAP_TIM8_CH4
*\*\          - DMA_REMAP_TIM8_COM
*\*\          - DMA_REMAP_TIM8_UP
*\*\          - DMA_REMAP_TIM8_TRIG
*\*\return  none.
**/
void DMA_Channel_Request_Remap(DMA_ChannelType* DMAChx, uint32_t req_remap)
{
    /* Set the selected DMA request remap */
    DMAChx->CHSEL = req_remap;
}

