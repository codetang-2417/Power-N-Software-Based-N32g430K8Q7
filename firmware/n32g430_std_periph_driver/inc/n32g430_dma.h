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
*\*\file n32g430_dma.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
 
#ifndef __N32G430_DMA_H__
#define __N32G430_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

/*** DMA Structure Definition Start ***/

/** DMA Init structure definition **/
typedef struct
{
    uint32_t PeriphAddr;     /* Specifies the peripheral base address for DMAy Channelx. */

    uint32_t MemAddr;        /* Specifies the memory base address for DMAy Channelx. */

    uint32_t Direction;      /* Specifies if the peripheral is the source or destination. */

    uint32_t BufSize;        /* Specifies the buffer size, in data unit, of the specified Channel.
                                The data unit is equal to the configuration set in PeriphDataSize
                                or MemDataSize members depending in the transfer direction. */

    uint32_t PeriphInc;      /* Specifies whether the Peripheral address register is incremented or not. */

    uint32_t MemoryInc;  /* Specifies whether the memory address register is incremented or not. */

    uint32_t PeriphDataSize; /* Specifies the Peripheral data width. */

    uint32_t MemDataSize;    /* Specifies the Memory data width. */

    uint32_t CircularMode;   /* Specifies the operation mode of the DMAy Channelx.
                                *\*\note: The circular buffer mode cannot be used if the memory-to-memory
                                data transfer is configured on the selected Channel. */

    uint32_t Priority;       /* Specifies the software priority for the DMAy Channelx. */

    uint32_t Mem2Mem;        /* Specifies if the DMAy Channelx will be used in memory-to-memory transfer. */
} DMA_InitType;

/*** DMA Structure Definition End ***/


/*** DMA Macro Definition Start ***/

/** DMA register bit field mask definition **/
#define DMA_REG_BIT_FIELD_MASK ((uint32_t)0x00000000)

/** DMA data transfer direction definition **/
#define DMA_DIR_PERIPH_MASK (~((uint32_t)DMA_CHCFG1_DIR))
#define DMA_DIR_PERIPH_DST  ((uint32_t)DMA_CHCFG1_DIR)
#define DMA_DIR_PERIPH_SRC  ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA peripheral incremented mode definition **/
#define DMA_PERIPH_INC_MODE_MASK    (~((uint32_t)DMA_CHCFG1_PINC))
#define DMA_PERIPH_INC_MODE_ENABLE  ((uint32_t)DMA_CHCFG1_PINC)
#define DMA_PERIPH_INC_MODE_DISABLE ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA memory incremented mode definition **/
#define DMA_MEM_INC_MODE_MASK    (~((uint32_t)DMA_CHCFG1_MINC))
#define DMA_MEM_INC_MODE_ENABLE  ((uint32_t)DMA_CHCFG1_MINC)
#define DMA_MEM_INC_MODE_DISABLE ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA peripheral data width definition **/
#define DMA_PERIPH_DATA_WIDTH_MASK     (~((uint32_t)DMA_CHCFG1_PSIZE))
#define DMA_PERIPH_DATA_WIDTH_BYTE     ((uint32_t)(DMA_CHCFG1_PSIZE_0 & DMA_CHCFG1_PSIZE_1))
#define DMA_PERIPH_DATA_WIDTH_HALFWORD ((uint32_t)DMA_CHCFG1_PSIZE_0)
#define DMA_PERIPH_DATA_WIDTH_WORD     ((uint32_t)DMA_CHCFG1_PSIZE_1)

/** DMA memory data width definition **/
#define DMA_MEM_DATA_WIDTH_MASK     (~((uint32_t)DMA_CHCFG1_MSIZE))
#define DMA_MEM_DATA_WIDTH_BYTE     ((uint32_t)(DMA_CHCFG1_MSIZE_0 & DMA_CHCFG1_MSIZE_1))
#define DMA_MEM_DATA_WIDTH_HALFWORD ((uint32_t)DMA_CHCFG1_MSIZE_0)
#define DMA_MEM_DATA_WIDTH_WORD     ((uint32_t)DMA_CHCFG1_MSIZE_1)

/** DMA circulation mode definition **/
#define DMA_CIRCULAR_MODE_MASK    (~((uint32_t)DMA_CHCFG1_CIRC))
#define DMA_CIRCULAR_MODE_ENABLE  ((uint32_t)DMA_CHCFG1_CIRC)
#define DMA_CIRCULAR_MODE_DISABLE ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA channel priority level definition **/
#define DMA_CH_PRIORITY_MASK    ((uint32_t)(~DMA_CHCFG1_PRIOLVL))
#define DMA_CH_PRIORITY_HIGHEST ((uint32_t)(DMA_CHCFG1_PRIOLVL_0 | DMA_CHCFG1_PRIOLVL_1))
#define DMA_CH_PRIORITY_HIGH    ((uint32_t)DMA_CHCFG1_PRIOLVL_1)
#define DMA_CH_PRIORITY_MEDIUM  ((uint32_t)DMA_CHCFG1_PRIOLVL_0)
#define DMA_CH_PRIORITY_LOW     ((uint32_t)(DMA_CHCFG1_PRIOLVL_0 & DMA_CHCFG1_PRIOLVL_1))

/** DMA memory to memory mode definition **/
#define DMA_MEM2MEM_MASK    (~((uint32_t)DMA_CHCFG1_MEM2MEM))
#define DMA_MEM2MEM_ENABLE  ((uint32_t)DMA_CHCFG1_MEM2MEM)
#define DMA_MEM2MEM_DISABLE ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA channel enable definition **/
#define DMA_CHANNEL_ENABLE  ((uint32_t)DMA_CHCFG1_CHEN)
#define DMA_CHANNEL_DISABLE (~((uint32_t)DMA_CHCFG1_CHEN))

/** DMA interrupts definition **/
#define DMA_INT_TXC ((uint32_t)DMA_CHCFG1_TXCIE) /* Transfer complete interrupt */
#define DMA_INT_HTX ((uint32_t)DMA_CHCFG1_HTXIE) /* Half transfer interrupt */
#define DMA_INT_ERR ((uint32_t)DMA_CHCFG1_ERRIE) /* Transfer error interrupt */

#define DMA_CH1_INT_GLB ((uint32_t)DMA_INTSTS_GLBF1) /* DMA channel1 global interrupt */
#define DMA_CH1_INT_TXC ((uint32_t)DMA_INTSTS_TXCF1) /* DMA channel1 transfer complete interrupt */
#define DMA_CH1_INT_HTX ((uint32_t)DMA_INTSTS_HTXF1) /* DMA channel1 half transfer interrupt */
#define DMA_CH1_INT_ERR ((uint32_t)DMA_INTSTS_ERRF1) /* DMA channel1 transfer error interrupt */
#define DMA_CH2_INT_GLB ((uint32_t)DMA_INTSTS_GLBF2) /* DMA channel2 global interrupt */
#define DMA_CH2_INT_TXC ((uint32_t)DMA_INTSTS_TXCF2) /* DMA channel2 transfer complete interrupt */
#define DMA_CH2_INT_HTX ((uint32_t)DMA_INTSTS_HTXF2) /* DMA channel2 half transfer interrupt */
#define DMA_CH2_INT_ERR ((uint32_t)DMA_INTSTS_ERRF2) /* DMA channel2 transfer error interrupt */
#define DMA_CH3_INT_GLB ((uint32_t)DMA_INTSTS_GLBF3) /* DMA channel3 global interrupt */
#define DMA_CH3_INT_TXC ((uint32_t)DMA_INTSTS_TXCF3) /* DMA channel3 transfer complete interrupt */
#define DMA_CH3_INT_HTX ((uint32_t)DMA_INTSTS_HTXF3) /* DMA channel3 half transfer interrupt */
#define DMA_CH3_INT_ERR ((uint32_t)DMA_INTSTS_ERRF3) /* DMA channel3 transfer error interrupt */
#define DMA_CH4_INT_GLB ((uint32_t)DMA_INTSTS_GLBF4) /* DMA channel4 global interrupt */
#define DMA_CH4_INT_TXC ((uint32_t)DMA_INTSTS_TXCF4) /* DMA channel4 transfer complete interrupt */
#define DMA_CH4_INT_HTX ((uint32_t)DMA_INTSTS_HTXF4) /* DMA channel4 half transfer interrupt */
#define DMA_CH4_INT_ERR ((uint32_t)DMA_INTSTS_ERRF4) /* DMA channel4 transfer error interrupt */
#define DMA_CH5_INT_GLB ((uint32_t)DMA_INTSTS_GLBF5) /* DMA channel5 global interrupt */
#define DMA_CH5_INT_TXC ((uint32_t)DMA_INTSTS_TXCF5) /* DMA channel5 transfer complete interrupt */
#define DMA_CH5_INT_HTX ((uint32_t)DMA_INTSTS_HTXF5) /* DMA channel5 half transfer interrupt */
#define DMA_CH5_INT_ERR ((uint32_t)DMA_INTSTS_ERRF5) /* DMA channel5 transfer error interrupt */
#define DMA_CH6_INT_GLB ((uint32_t)DMA_INTSTS_GLBF6) /* DMA channel6 global interrupt */
#define DMA_CH6_INT_TXC ((uint32_t)DMA_INTSTS_TXCF6) /* DMA channel6 transfer complete interrupt */
#define DMA_CH6_INT_HTX ((uint32_t)DMA_INTSTS_HTXF6) /* DMA channel6 half transfer interrupt */
#define DMA_CH6_INT_ERR ((uint32_t)DMA_INTSTS_ERRF6) /* DMA channel6 transfer error interrupt */
#define DMA_CH7_INT_GLB ((uint32_t)DMA_INTSTS_GLBF7) /* DMA channel7 global interrupt */
#define DMA_CH7_INT_TXC ((uint32_t)DMA_INTSTS_TXCF7) /* DMA channel7 transfer complete interrupt */
#define DMA_CH7_INT_HTX ((uint32_t)DMA_INTSTS_HTXF7) /* DMA channel7 half transfer interrupt */
#define DMA_CH7_INT_ERR ((uint32_t)DMA_INTSTS_ERRF7) /* DMA channel7 transfer error interrupt */
#define DMA_CH8_INT_GLB ((uint32_t)DMA_INTSTS_GLBF8) /* DMA channel8 global interrupt */
#define DMA_CH8_INT_TXC ((uint32_t)DMA_INTSTS_TXCF8) /* DMA channel8 transfer complete interrupt */
#define DMA_CH8_INT_HTX ((uint32_t)DMA_INTSTS_HTXF8) /* DMA channel8 half transfer interrupt */
#define DMA_CH8_INT_ERR ((uint32_t)DMA_INTSTS_ERRF8) /* DMA channel8 transfer error interrupt */

/** DMA flags definition **/
#define DMA_CH1_GLBF ((uint32_t)DMA_INTSTS_GLBF1) /* DMA Channel1 global flag */
#define DMA_CH1_TXCF ((uint32_t)DMA_INTSTS_TXCF1) /* DMA Channel1 transfer complete flag */
#define DMA_CH1_HTXF ((uint32_t)DMA_INTSTS_HTXF1) /* DMA Channel1 half transfer flag */
#define DMA_CH1_ERRF ((uint32_t)DMA_INTSTS_ERRF1) /* DMA Channel1 transfer error flag */
#define DMA_CH2_GLBF ((uint32_t)DMA_INTSTS_GLBF2) /* DMA Channel2 global flag */
#define DMA_CH2_TXCF ((uint32_t)DMA_INTSTS_TXCF2) /* DMA Channel2 transfer complete flag */
#define DMA_CH2_HTXF ((uint32_t)DMA_INTSTS_HTXF2) /* DMA Channel2 half transfer flag */
#define DMA_CH2_ERRF ((uint32_t)DMA_INTSTS_ERRF2) /* DMA Channel2 transfer error flag */
#define DMA_CH3_GLBF ((uint32_t)DMA_INTSTS_GLBF3) /* DMA Channel3 global flag */
#define DMA_CH3_TXCF ((uint32_t)DMA_INTSTS_TXCF3) /* DMA Channel3 transfer complete flag */
#define DMA_CH3_HTXF ((uint32_t)DMA_INTSTS_HTXF3) /* DMA Channel3 half transfer flag */
#define DMA_CH3_ERRF ((uint32_t)DMA_INTSTS_ERRF3) /* DMA Channel3 transfer error flag */
#define DMA_CH4_GLBF ((uint32_t)DMA_INTSTS_GLBF4) /* DMA Channel4 global flag */
#define DMA_CH4_TXCF ((uint32_t)DMA_INTSTS_TXCF4) /* DMA Channel4 transfer complete flag */
#define DMA_CH4_HTXF ((uint32_t)DMA_INTSTS_HTXF4) /* DMA Channel4 half transfer flag */
#define DMA_CH4_ERRF ((uint32_t)DMA_INTSTS_ERRF4) /* DMA Channel4 transfer error flag */
#define DMA_CH5_GLBF ((uint32_t)DMA_INTSTS_GLBF5) /* DMA Channel5 global flag */
#define DMA_CH5_TXCF ((uint32_t)DMA_INTSTS_TXCF5) /* DMA Channel5 transfer complete flag */
#define DMA_CH5_HTXF ((uint32_t)DMA_INTSTS_HTXF5) /* DMA Channel5 half transfer flag */
#define DMA_CH5_ERRF ((uint32_t)DMA_INTSTS_ERRF5) /* DMA Channel5 transfer error flag */
#define DMA_CH6_GLBF ((uint32_t)DMA_INTSTS_GLBF6) /* DMA Channel6 global flag */
#define DMA_CH6_TXCF ((uint32_t)DMA_INTSTS_TXCF6) /* DMA Channel6 transfer complete flag */
#define DMA_CH6_HTXF ((uint32_t)DMA_INTSTS_HTXF6) /* DMA Channel6 half transfer flag */
#define DMA_CH6_ERRF ((uint32_t)DMA_INTSTS_ERRF6) /* DMA Channel6 transfer error flag */
#define DMA_CH7_GLBF ((uint32_t)DMA_INTSTS_GLBF7) /* DMA Channel7 global flag */
#define DMA_CH7_TXCF ((uint32_t)DMA_INTSTS_TXCF7) /* DMA Channel7 transfer complete flag */
#define DMA_CH7_HTXF ((uint32_t)DMA_INTSTS_HTXF7) /* DMA Channel7 half transfer flag */
#define DMA_CH7_ERRF ((uint32_t)DMA_INTSTS_ERRF7) /* DMA Channel7 transfer error flag */
#define DMA_CH8_GLBF ((uint32_t)DMA_INTSTS_GLBF8) /* DMA Channel8 global flag */
#define DMA_CH8_TXCF ((uint32_t)DMA_INTSTS_TXCF8) /* DMA Channel8 transfer complete flag */
#define DMA_CH8_HTXF ((uint32_t)DMA_INTSTS_HTXF8) /* DMA Channel8 half transfer flag */
#define DMA_CH8_ERRF ((uint32_t)DMA_INTSTS_ERRF8) /* DMA Channel9 transfer error flag */

/** DMA remap channel request definition **/
#define DMA_REMAP_ADC       ((uint32_t)0x00000000) /* DMA Request For ADC */
#define DMA_REMAP_USART1_TX ((uint32_t)0x00000001) /* DMA Request For USART1_TX */
#define DMA_REMAP_USART1_RX ((uint32_t)0x00000002) /* DMA Request For USART1_RX */
#define DMA_REMAP_USART2_TX ((uint32_t)0x00000003) /* DMA Request For USART2_TX */
#define DMA_REMAP_USART2_RX ((uint32_t)0x00000004) /* DMA Request For USART2_RX */
#define DMA_REMAP_UART3_TX  ((uint32_t)0x00000005) /* DMA Request For UART3_TX */
#define DMA_REMAP_UART3_RX  ((uint32_t)0x00000006) /* DMA Request For UART3_RX */
#define DMA_REMAP_UART4_TX  ((uint32_t)0x00000007) /* DMA Request For UART4_TX */
#define DMA_REMAP_UART4_RX  ((uint32_t)0x00000008) /* DMA Request For UART4_RX */
#define DMA_REMAP_SPI1_TX   ((uint32_t)0x00000009) /* DMA Request For SPI1_TX */
#define DMA_REMAP_SPI1_RX   ((uint32_t)0x0000000A) /* DMA Request For SPI1_RX */
#define DMA_REMAP_SPI2_TX   ((uint32_t)0x0000000B) /* DMA Request For SPI2_TX */
#define DMA_REMAP_SPI2_RX   ((uint32_t)0x0000000C) /* DMA Request For SPI2_RX */
#define DMA_REMAP_I2C1_TX   ((uint32_t)0x0000000D) /* DMA Request For I2C1_TX */
#define DMA_REMAP_I2C1_RX   ((uint32_t)0x0000000E) /* DMA Request For I2C1_RX */
#define DMA_REMAP_I2C2_TX   ((uint32_t)0x0000000F) /* DMA Request For I2C2_TX */
#define DMA_REMAP_I2C2_RX   ((uint32_t)0x00000010) /* DMA Request For I2C2_RX */
#define DMA_REMAP_TIM1_CH1  ((uint32_t)0x00000011) /* DMA Request For TIM1_CH1 */
#define DMA_REMAP_TIM1_CH2  ((uint32_t)0x00000012) /* DMA Request For TIM1_CH2 */
#define DMA_REMAP_TIM1_CH3  ((uint32_t)0x00000013) /* DMA Request For TIM1_CH3 */
#define DMA_REMAP_TIM1_CH4  ((uint32_t)0x00000014) /* DMA Request For TIM1_CH4 */
#define DMA_REMAP_TIM1_COM  ((uint32_t)0x00000015) /* DMA Request For TIM1_COM */
#define DMA_REMAP_TIM1_UP   ((uint32_t)0x00000016) /* DMA Request For TIM1_UP */
#define DMA_REMAP_TIM1_TRIG ((uint32_t)0x00000017) /* DMA Request For TIM1_TRIG */
#define DMA_REMAP_TIM2_CH1  ((uint32_t)0x00000018) /* DMA Request For TIM2_CH1 */
#define DMA_REMAP_TIM2_CH2  ((uint32_t)0x00000019) /* DMA Request For TIM2_CH2 */
#define DMA_REMAP_TIM2_CH3  ((uint32_t)0x0000001B) /* DMA Request For TIM2_CH3 */
#define DMA_REMAP_TIM2_CH4  ((uint32_t)0x0000001C) /* DMA Request For TIM2_CH4 */
#define DMA_REMAP_TIM2_UP   ((uint32_t)0x0000001A) /* DMA Request For TIM2_UP */
#define DMA_REMAP_TIM3_CH1  ((uint32_t)0x0000001D) /* DMA Request For TIM3_CH1 */
#define DMA_REMAP_TIM3_CH3  ((uint32_t)0x0000001E) /* DMA Request For TIM3_CH3 */
#define DMA_REMAP_TIM3_CH4  ((uint32_t)0x0000001F) /* DMA Request For TIM3_CH4 */
#define DMA_REMAP_TIM3_UP   ((uint32_t)0x00000020) /* DMA Request For TIM3_UP */
#define DMA_REMAP_TIM3_TRIG ((uint32_t)0x00000021) /* DMA Request For TIM3_TRIG */
#define DMA_REMAP_TIM4_CH1  ((uint32_t)0x00000022) /* DMA Request For TIM4_CH1 */
#define DMA_REMAP_TIM4_CH2  ((uint32_t)0x00000023) /* DMA Request For TIM4_CH2 */
#define DMA_REMAP_TIM4_CH3  ((uint32_t)0x00000024) /* DMA Request For TIM4_CH3 */
#define DMA_REMAP_TIM4_UP   ((uint32_t)0x00000025) /* DMA Request For TIM4_UP */
#define DMA_REMAP_TIM5_CH1  ((uint32_t)0x00000026) /* DMA Request For TIM5_CH1 */
#define DMA_REMAP_TIM5_CH2  ((uint32_t)0x00000027) /* DMA Request For TIM5_CH2 */
#define DMA_REMAP_TIM5_CH3  ((uint32_t)0x00000028) /* DMA Request For TIM5_CH3 */
#define DMA_REMAP_TIM5_CH4  ((uint32_t)0x00000029) /* DMA Request For TIM5_CH4 */
#define DMA_REMAP_TIM5_UP   ((uint32_t)0x0000002A) /* DMA Request For TIM5_UP */
#define DMA_REMAP_TIM5_TRIG ((uint32_t)0x0000002B) /* DMA Request For TIM5_TRIG */
#define DMA_REMAP_TIM6_UP   ((uint32_t)0x0000002C) /* DMA Request For TIM6_UP */
#define DMA_REMAP_TIM8_CH1  ((uint32_t)0x0000002D) /* DMA Request For TIM8_CH1 */
#define DMA_REMAP_TIM8_CH2  ((uint32_t)0x0000002E) /* DMA Request For TIM8_CH2 */
#define DMA_REMAP_TIM8_CH3  ((uint32_t)0x0000003F) /* DMA Request For TIM8_CH3 */
#define DMA_REMAP_TIM8_CH4  ((uint32_t)0x00000030) /* DMA Request For TIM8_CH4 */
#define DMA_REMAP_TIM8_COM  ((uint32_t)0x00000031) /* DMA Request For TIM8_COM */
#define DMA_REMAP_TIM8_UP   ((uint32_t)0x00000032) /* DMA Request For TIM8_UP */
#define DMA_REMAP_TIM8_TRIG ((uint32_t)0x00000033) /* DMA Request For TIM8_TRIG */

/** DMA Channelx interrupt pending bit masks definition **/
#define DMA_CH1_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF1 | DMA_INTSTS_TXCF1 | DMA_INTSTS_HTXF1 | DMA_INTSTS_ERRF1))
#define DMA_CH2_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF2 | DMA_INTSTS_TXCF2 | DMA_INTSTS_HTXF2 | DMA_INTSTS_ERRF2))
#define DMA_CH3_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF3 | DMA_INTSTS_TXCF3 | DMA_INTSTS_HTXF3 | DMA_INTSTS_ERRF3))
#define DMA_CH4_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF4 | DMA_INTSTS_TXCF4 | DMA_INTSTS_HTXF4 | DMA_INTSTS_ERRF4))
#define DMA_CH5_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF5 | DMA_INTSTS_TXCF5 | DMA_INTSTS_HTXF5 | DMA_INTSTS_ERRF5))
#define DMA_CH6_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF6 | DMA_INTSTS_TXCF6 | DMA_INTSTS_HTXF6 | DMA_INTSTS_ERRF6))
#define DMA_CH7_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF7 | DMA_INTSTS_TXCF7 | DMA_INTSTS_HTXF7 | DMA_INTSTS_ERRF7))
#define DMA_CH8_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF8 | DMA_INTSTS_TXCF8 | DMA_INTSTS_HTXF8 | DMA_INTSTS_ERRF8))

/*** DMA Macro Definition End ***/


/*** DMA Driving Functions Declaration ***/
void DMA_Reset(DMA_ChannelType* DMAChx);
void DMA_Initializes(DMA_ChannelType* DMAChx, DMA_InitType* DMA_InitParam);
void DMA_Peripheral_Address_Config(DMA_ChannelType* DMAChx, uint32_t addr);
void DMA_Memory_Address_Config(DMA_ChannelType* DMAChx, uint32_t addr);
void DMA_Destination_Config(DMA_ChannelType* DMAChx, uint32_t direction);
void DMA_Buffer_Size_Config(DMA_ChannelType* DMAChx, uint32_t buf_size);
void DMA_Peripheral_Addr_Increment_Config(DMA_ChannelType* DMAChx, uint32_t periph_inc);
void DMA_Memory_Addr_Increment_Config(DMA_ChannelType* DMAChx, uint32_t memory_inc);
void DMA_Peripheral_Data_Width_Config(DMA_ChannelType* DMAChx, uint32_t width);
void DMA_Memory_Data_Width_Config(DMA_ChannelType* DMAChx, uint32_t width);
void DMA_Circular_Mode_Config(DMA_ChannelType* DMAChx, uint32_t cmd);
void DMA_Priority_Config(DMA_ChannelType* DMAChx, uint32_t priority);
void DMA_Memory_2_Memory_Config(DMA_ChannelType* DMAChx, uint32_t cmd);
void DMA_Structure_Initializes(DMA_InitType* DMA_InitParam);
void DMA_Channel_Enable(DMA_ChannelType* DMAChx);
void DMA_Channel_Disable(DMA_ChannelType* DMAChx);
void DMA_Interrupts_Enable(DMA_ChannelType* DMAChx, uint32_t interrupt);
void DMA_Interrupts_Disable(DMA_ChannelType* DMAChx, uint32_t interrupt);
void DMA_Current_Data_Transfer_Number_Set(DMA_ChannelType* DMAChx, uint16_t num);
uint16_t DMA_Current_Data_Transfer_Number_Get(DMA_ChannelType* DMAChx);
FlagStatus DMA_Flag_Status_Get(DMA_Module* DMAx, uint32_t flag);
void DMA_Flag_Status_Clear(DMA_Module* DMAx, uint32_t flag);
INTStatus DMA_Interrupt_Status_Get(DMA_Module* DMAx, uint32_t interrupt);
void DMA_Interrupt_Status_Clear(DMA_Module* DMAx, uint32_t interrupt);
void DMA_Channel_Request_Remap(DMA_ChannelType* DMAChx, uint32_t req_remap);

#ifdef __cplusplus
}
#endif

#endif /*__N32G430_DMA_H__ */

