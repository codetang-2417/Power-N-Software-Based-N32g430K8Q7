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
*\*\file n32g430_rcc.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32G430_RCC_H__
#define __N32G430_RCC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"


/** RCC_Exported_Types **/

typedef struct
{
    uint32_t SysclkFreq;    /* returns SYSCLK clock frequency expressed in Hz */
    uint32_t HclkFreq;      /* returns HCLK clock frequency expressed in Hz */
    uint32_t Pclk1Freq;     /* returns PCLK1 clock frequency expressed in Hz */
    uint32_t Pclk2Freq;     /* returns PCLK2 clock frequency expressed in Hz */
    uint32_t AdcPllClkFreq; /* returns ADCPLLCLK clock frequency expressed in Hz */
    uint32_t AdcHclkFreq;   /* returns ADCHCLK clock frequency expressed in Hz */
} RCC_ClocksType;

typedef enum
{
    SYSCLK_SRC_HSI = 0x00,
    SYSCLK_SRC_HSE = 0x04,
    SYSCLK_SRC_PLL = 0x08
} SysclkSource;

/** RCC registers bit address in the alias region **/
#define RCC_OFFSET (RCC_BASE - PERIPH_BASE)

/** CTRL Register **/
#define CTRL_OFFSET   (RCC_OFFSET + 0x00)

/* Alias word address of HSIEN bit */
#define HSIEN_BIT_NUM    0x00 
#define RCC_HSIEN_BITBAND (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (HSIEN_BIT_NUM * 4)) 
/* Alias word address of CLKSSEN bit */
#define CLKSSEN_BIT_NUM    0x13
#define RCC_CLKSSEN_BITBAND (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (CLKSSEN_BIT_NUM * 4))
/* Alias word address of PLLEN bit */
#define PLLEN_BIT_NUM    0x18
#define RCC_PLLEN_BITBAND (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (PLLEN_BIT_NUM * 4))

/** BDCTRL Register **/
#define BDCTRL_OFFSET   (RCC_OFFSET + 0x20)

/* Alias word address of LSECLKSSEN bit */
#define LSECLKSSEN_BIT_NUM    0x03
#define RCC_LSECLKSSEN_BITBAND  (PERIPH_BB_BASE + (BDCTRL_OFFSET * 32) + (LSECLKSSEN_BIT_NUM * 4))
/* Alias word address of RTCEN bit */
#define RTCEN_BIT_NUM     0x0F
#define RCC_RTCEN_BITBAND  (PERIPH_BB_BASE + (BDCTRL_OFFSET * 32) + (RTCEN_BIT_NUM * 4))
/* Alias word address of BDSFTRST bit */
#define BDSFTRST_BIT_NUM     0x10
#define RCC_BDSFTRST_BITBAND  (PERIPH_BB_BASE + (BDCTRL_OFFSET * 32) + (BDSFTRST_BIT_NUM * 4))

/** CTRLSTS Register **/
#define CTRLSTS_OFFSET   (RCC_OFFSET + 0x24)

/* Alias word address of LSIEN bit */
#define LSIEN_BIT_NUM  0x00
#define RCC_LSIEN_BITBAND (PERIPH_BB_BASE + (CTRLSTS_OFFSET * 32) + (LSIEN_BIT_NUM * 4))

/* BDCTRL register base address */
#define RCC_BDCTRL_ADDR (PERIPH_BASE + BDCTRL_OFFSET)



/** RCC_Exported_Constants **/

/** Register shift macro definition **/
#define  RCC_CFG_PLLMULFCT_OFFSET    (REG_BIT18_OFFSET)
#define  RCC_CFG_AHBPRES_OFFSET      (REG_BIT4_OFFSET)
#define  RCC_CFG_APB1PRES_OFFSET     (REG_BIT8_OFFSET)
#define  RCC_CFG_APB2PRES_OFFSET     (REG_BIT11_OFFSET)
#define  RCC_CFG2_ADCPLLPRES_OFFSET  (REG_BIT4_OFFSET)
#define  RCC_FLAG_OFFSET             (REG_BIT5_OFFSET)
#define  RCC_CLOCK_DIV2_OFFSET       (REG_BIT1_OFFSET)
#define  RCC_CTRL_HSITRIM_OFFSET     (REG_BIT3_OFFSET)
#define  RCC_APB2PRES_OFFSET         (REG_BIT3_OFFSET)


/** RCC R_BIT_MASK **/
#define RCC_REG_BIT_MASK  ((uint32_t)0x00000000)

/** HSE_configuration **/
#define RCC_HSE_DISABLE  (RCC_REG_BIT_MASK)
#define RCC_HSE_ENABLE   (RCC_CTRL_HSEEN)
#define RCC_HSE_BYPASS   (RCC_CTRL_HSEBP)

/** Internal High Speed clock trimming **/
#define RCC_HSITRIM_MASK (~RCC_CTRL_HSITRIM)

/** PLL Mask **/
#define RCC_PLL_MASK        (~(RCC_CFG_PLLSRC | RCC_CFG_PLLHSEPRES | RCC_CFG_PLLMULFCT)) 
#define RCC_PLLHSIPRE_MASK  (~RCC_PLLHSIPRE_PLLHSIPRE)
/** PLL_entry_clock_source **/
#define RCC_PLL_SRC_HSI_DIV1 (RCC_PLLHSIPRE_PLLHSIPRE_HSI)
#define RCC_PLL_SRC_HSI_DIV2 (RCC_PLLHSIPRE_PLLHSIPRE_HSI_DIV2)
#define RCC_PLL_SRC_HSE_DIV1 (RCC_CFG_PLLSRC_HSE | RCC_CFG_PLLHSEPRES_HSE)
#define RCC_PLL_SRC_HSE_DIV2 (RCC_CFG_PLLSRC_HSE | RCC_CFG_PLLHSEPRES_HSE_DIV2)

/** PLL_multiplication_factor **/
#define RCC_PLL_MUL_2   (RCC_CFG_PLLMULFCT2)
#define RCC_PLL_MUL_3   (RCC_CFG_PLLMULFCT3)
#define RCC_PLL_MUL_4   (RCC_CFG_PLLMULFCT4)
#define RCC_PLL_MUL_5   (RCC_CFG_PLLMULFCT5)
#define RCC_PLL_MUL_6   (RCC_CFG_PLLMULFCT6)
#define RCC_PLL_MUL_7   (RCC_CFG_PLLMULFCT7)
#define RCC_PLL_MUL_8   (RCC_CFG_PLLMULFCT8)
#define RCC_PLL_MUL_9   (RCC_CFG_PLLMULFCT9)
#define RCC_PLL_MUL_10  (RCC_CFG_PLLMULFCT10)
#define RCC_PLL_MUL_11  (RCC_CFG_PLLMULFCT11)
#define RCC_PLL_MUL_12  (RCC_CFG_PLLMULFCT12)
#define RCC_PLL_MUL_13  (RCC_CFG_PLLMULFCT13)
#define RCC_PLL_MUL_14  (RCC_CFG_PLLMULFCT14)
#define RCC_PLL_MUL_15  (RCC_CFG_PLLMULFCT15)
#define RCC_PLL_MUL_16  (RCC_CFG_PLLMULFCT16)
#define RCC_PLL_MUL_17  (RCC_CFG_PLLMULFCT17)
#define RCC_PLL_MUL_18  (RCC_CFG_PLLMULFCT18)
#define RCC_PLL_MUL_19  (RCC_CFG_PLLMULFCT19)
#define RCC_PLL_MUL_20  (RCC_CFG_PLLMULFCT20)
#define RCC_PLL_MUL_21  (RCC_CFG_PLLMULFCT21)
#define RCC_PLL_MUL_22  (RCC_CFG_PLLMULFCT22)
#define RCC_PLL_MUL_23  (RCC_CFG_PLLMULFCT23)
#define RCC_PLL_MUL_24  (RCC_CFG_PLLMULFCT24)
#define RCC_PLL_MUL_25  (RCC_CFG_PLLMULFCT25)
#define RCC_PLL_MUL_26  (RCC_CFG_PLLMULFCT26)
#define RCC_PLL_MUL_27  (RCC_CFG_PLLMULFCT27)
#define RCC_PLL_MUL_28  (RCC_CFG_PLLMULFCT28)
#define RCC_PLL_MUL_29  (RCC_CFG_PLLMULFCT29)
#define RCC_PLL_MUL_30  (RCC_CFG_PLLMULFCT30)
#define RCC_PLL_MUL_31  (RCC_CFG_PLLMULFCT31)
#define RCC_PLL_MUL_32  (RCC_CFG_PLLMULFCT32)

/** System_clock_source **/
#define RCC_SYSCLK_SRC_MASK    (~RCC_CFG_SCLKSW)
#define RCC_SYSCLK_SRC_HSI     (RCC_CFG_SCLKSW_HSI)
#define RCC_SYSCLK_SRC_HSE     (RCC_CFG_SCLKSW_HSE)
#define RCC_SYSCLK_SRC_PLLCLK  (RCC_CFG_SCLKSW_PLL)

/** System_clock_status mask **/
#define RCC_SYSCLK_STS_MASK    (RCC_CFG_SCLKSTS)

/** AHB_clock_source **/
#define RCC_SYSCLK_DIV_MASK (~RCC_CFG_AHBPRES)
#define RCC_SYSCLK_DIV1     (RCC_CFG_AHBPRES_DIV1)
#define RCC_SYSCLK_DIV2     (RCC_CFG_AHBPRES_DIV2)
#define RCC_SYSCLK_DIV4     (RCC_CFG_AHBPRES_DIV4)
#define RCC_SYSCLK_DIV8     (RCC_CFG_AHBPRES_DIV8)
#define RCC_SYSCLK_DIV16    (RCC_CFG_AHBPRES_DIV16)
#define RCC_SYSCLK_DIV64    (RCC_CFG_AHBPRES_DIV64)
#define RCC_SYSCLK_DIV128   (RCC_CFG_AHBPRES_DIV128)
#define RCC_SYSCLK_DIV256   (RCC_CFG_AHBPRES_DIV256)
#define RCC_SYSCLK_DIV512   (RCC_CFG_AHBPRES_DIV512)

/** APB1_APB2_clock_source **/
#define RCC_APB1_DIV_MASK   (~RCC_CFG_APB1PRES)
#define RCC_APB2_DIV_MASK   (~RCC_CFG_APB2PRES)
#define RCC_HCLK_DIV1       (RCC_CFG_APB1PRES_DIV1)
#define RCC_HCLK_DIV2       (RCC_CFG_APB1PRES_DIV2)
#define RCC_HCLK_DIV4       (RCC_CFG_APB1PRES_DIV4)
#define RCC_HCLK_DIV8       (RCC_CFG_APB1PRES_DIV8)
#define RCC_HCLK_DIV16      (RCC_CFG_APB1PRES_DIV16)

/** RCC_CFGR2_Config **/
#define RCC_TIM1_8_CLKSRC_MASK      (~RCC_CFG2_TIMCLKSEL) 
#define RCC_TIM1_8_CLKSRC_PCLK2     (RCC_CFG2_TIMCLKSEL_PCLK2)
#define RCC_TIM1_8_CLKSRC_SYSCLK    (RCC_CFG2_TIMCLKSEL_SYSCLK)

#define RCC_ADC1MCLK_SRC_MASK      (~RCC_CFG2_ADC1MSEL)
#define RCC_ADC1MCLK_SRC_HSI       (RCC_CFG2_ADC1MSEL_HSI)
#define RCC_ADC1MCLK_SRC_HSE       (RCC_CFG2_ADC1MSEL_HSE)

#define RCC_ADC1MCLK_DIV_MASK  (~RCC_CFG2_ADC1MPRES)
#define RCC_ADC1MCLK_DIV1      (RCC_CFG2_ADC1MPRES_DIV1)
#define RCC_ADC1MCLK_DIV2      (RCC_CFG2_ADC1MPRES_DIV2)
#define RCC_ADC1MCLK_DIV3      (RCC_CFG2_ADC1MPRES_DIV3)
#define RCC_ADC1MCLK_DIV4      (RCC_CFG2_ADC1MPRES_DIV4)
#define RCC_ADC1MCLK_DIV5      (RCC_CFG2_ADC1MPRES_DIV5)
#define RCC_ADC1MCLK_DIV6      (RCC_CFG2_ADC1MPRES_DIV6)
#define RCC_ADC1MCLK_DIV7      (RCC_CFG2_ADC1MPRES_DIV7)
#define RCC_ADC1MCLK_DIV8      (RCC_CFG2_ADC1MPRES_DIV8)
#define RCC_ADC1MCLK_DIV9      (RCC_CFG2_ADC1MPRES_DIV9)
#define RCC_ADC1MCLK_DIV10     (RCC_CFG2_ADC1MPRES_DIV10)
#define RCC_ADC1MCLK_DIV11     (RCC_CFG2_ADC1MPRES_DIV11)
#define RCC_ADC1MCLK_DIV12     (RCC_CFG2_ADC1MPRES_DIV12)
#define RCC_ADC1MCLK_DIV13     (RCC_CFG2_ADC1MPRES_DIV13)
#define RCC_ADC1MCLK_DIV14     (RCC_CFG2_ADC1MPRES_DIV14)
#define RCC_ADC1MCLK_DIV15     (RCC_CFG2_ADC1MPRES_DIV15)
#define RCC_ADC1MCLK_DIV16     (RCC_CFG2_ADC1MPRES_DIV16)
#define RCC_ADC1MCLK_DIV17     (RCC_CFG2_ADC1MPRES_DIV17)
#define RCC_ADC1MCLK_DIV18     (RCC_CFG2_ADC1MPRES_DIV18)
#define RCC_ADC1MCLK_DIV19     (RCC_CFG2_ADC1MPRES_DIV19)
#define RCC_ADC1MCLK_DIV20     (RCC_CFG2_ADC1MPRES_DIV20)
#define RCC_ADC1MCLK_DIV21     (RCC_CFG2_ADC1MPRES_DIV21)
#define RCC_ADC1MCLK_DIV22     (RCC_CFG2_ADC1MPRES_DIV22)
#define RCC_ADC1MCLK_DIV23     (RCC_CFG2_ADC1MPRES_DIV23)
#define RCC_ADC1MCLK_DIV24     (RCC_CFG2_ADC1MPRES_DIV24)
#define RCC_ADC1MCLK_DIV25     (RCC_CFG2_ADC1MPRES_DIV25)
#define RCC_ADC1MCLK_DIV26     (RCC_CFG2_ADC1MPRES_DIV26)
#define RCC_ADC1MCLK_DIV27     (RCC_CFG2_ADC1MPRES_DIV27)
#define RCC_ADC1MCLK_DIV28     (RCC_CFG2_ADC1MPRES_DIV28)
#define RCC_ADC1MCLK_DIV29     (RCC_CFG2_ADC1MPRES_DIV29)
#define RCC_ADC1MCLK_DIV30     (RCC_CFG2_ADC1MPRES_DIV30)
#define RCC_ADC1MCLK_DIV31     (RCC_CFG2_ADC1MPRES_DIV31)
#define RCC_ADC1MCLK_DIV32     (RCC_CFG2_ADC1MPRES_DIV32)

#define RCC_ADCPLLCLK_MASK       (~RCC_CFG2_ADCPLLPRES)
#define RCC_ADCPLLCLK_DISABLE    (RCC_CFG2_ADCPLLCLK_DISABLE)
#define RCC_ADCPLLCLK_DIV1       (RCC_CFG2_ADCPLLPRES_DIV1)
#define RCC_ADCPLLCLK_DIV2       (RCC_CFG2_ADCPLLPRES_DIV2)
#define RCC_ADCPLLCLK_DIV4       (RCC_CFG2_ADCPLLPRES_DIV4)
#define RCC_ADCPLLCLK_DIV6       (RCC_CFG2_ADCPLLPRES_DIV6)
#define RCC_ADCPLLCLK_DIV8       (RCC_CFG2_ADCPLLPRES_DIV8)
#define RCC_ADCPLLCLK_DIV10      (RCC_CFG2_ADCPLLPRES_DIV10)
#define RCC_ADCPLLCLK_DIV12      (RCC_CFG2_ADCPLLPRES_DIV12)
#define RCC_ADCPLLCLK_DIV16      (RCC_CFG2_ADCPLLPRES_DIV16)
#define RCC_ADCPLLCLK_DIV32      (RCC_CFG2_ADCPLLPRES_DIV32)
#define RCC_ADCPLLCLK_DIV64      (RCC_CFG2_ADCPLLPRES_DIV64)
#define RCC_ADCPLLCLK_DIV128     (RCC_CFG2_ADCPLLPRES_DIV128)
#define RCC_ADCPLLCLK_DIV256     (RCC_CFG2_ADCPLLPRES_DIV256)
#define RCC_ADCPLLCLK_DIV_OTHERS (RCC_CFG2_ADCPLLPRES_DIV256N)

#define RCC_ADCHCLK_DIV_MASK   (~RCC_CFG2_ADCHPRES)
#define RCC_ADCHCLK_DIV1       (RCC_CFG2_ADCHPRES_DIV1)
#define RCC_ADCHCLK_DIV2       (RCC_CFG2_ADCHPRES_DIV2)
#define RCC_ADCHCLK_DIV4       (RCC_CFG2_ADCHPRES_DIV4)
#define RCC_ADCHCLK_DIV6       (RCC_CFG2_ADCHPRES_DIV6)
#define RCC_ADCHCLK_DIV8       (RCC_CFG2_ADCHPRES_DIV8)
#define RCC_ADCHCLK_DIV10      (RCC_CFG2_ADCHPRES_DIV10)
#define RCC_ADCHCLK_DIV12      (RCC_CFG2_ADCHPRES_DIV12)
#define RCC_ADCHCLK_DIV16      (RCC_CFG2_ADCHPRES_DIV16)
#define RCC_ADCHCLK_DIV32      (RCC_CFG2_ADCHPRES_DIV32)
#define RCC_ADCHCLK_DIV_OTHERS (RCC_CFG2_ADCHPRES_OTHERS)
#define RCC_ADCHCLK_ENABLE     (RCC_AHB1CLKEN_ADCHCLKEN)

/** LSE_TRIMR **/
#define LSE_TRIMR_ADDR               ((uint32_t)0x40007010)

#define LSE_NIM_MASK_VALUE           (0x400)
#define LSE_GM_MASK_VALUE            (0x1FF)
#define LSE_GM_MAX_VALUE             (0x1FF)
/** RCC_CFGR3_Config **/

/** LSE_configuration **/
#define RCC_LSE_DISABLE (RCC_REG_BIT_MASK)
#define RCC_LSE_ENABLE  (RCC_BDCTRL_LSEEN)
#define RCC_LSE_BYPASS  (RCC_BDCTRL_LSEBP)

/** LSE_CSS Flag **/
#define RCC_LSE_LSECLKSSF (RCC_BDCTRL_LSECLKSSF)

/** RTC_clock_source **/
#define RCC_RTCCLK_SRC_MASK        (~RCC_BDCTRL_RTCSEL)
#define RCC_RTCCLK_SRC_NONE        (RCC_BDCTRL_RTCSEL_NOCLOCK)
#define RCC_RTCCLK_SRC_LSE         (RCC_BDCTRL_RTCSEL_LSE)
#define RCC_RTCCLK_SRC_LSI         (RCC_BDCTRL_RTCSEL_LSI)
#define RCC_RTCCLK_SRC_HSE_DIV128  (RCC_BDCTRL_RTCSEL_HSE)

/** LPTIM_clock_source **/
#define RCC_LPTIMCLK_SRC_MASK  (~RCC_RDCTRL_LPTIMSEL)
#define RCC_LPTIMCLK_SRC_APB1  (RCC_RDCTRL_LPTIMSEL_APB1)
#define RCC_LPTIMCLK_SRC_LSI   (RCC_RDCTRL_LPTIMSEL_LSI)
#define RCC_LPTIMCLK_SRC_HSI   (RCC_RDCTRL_LPTIMSEL_HSI)
#define RCC_LPTIMCLK_SRC_LSE   (RCC_RDCTRL_LPTIMSEL_LSE)

/** LPTIM_clock_source **/
#define RCC_LPTIMCLK_RESET  (RCC_RDCTRL_LPTIMRST)
#define RCC_LPTIMCLK_ENBLE  (RCC_RDCTRL_LPTIMEN)

/** AHB_peripheral **/
#define RCC_AHB_PERIPH_DMA    (RCC_AHBPCLKEN_DMAEN)
#define RCC_AHB_PERIPH_SRAM   (RCC_AHBPCLKEN_SRAMEN)
#define RCC_AHB_PERIPH_FLITF  (RCC_AHBPCLKEN_FLITFEN)
#define RCC_AHB_PERIPH_CRC    (RCC_AHBPCLKEN_CRCEN)
#define RCC_AHB_PERIPH_GPIOA  (RCC_AHBPCLKEN_IOPAEN)
#define RCC_AHB_PERIPH_GPIOB  (RCC_AHBPCLKEN_IOPBEN)
#define RCC_AHB_PERIPH_GPIOC  (RCC_AHBPCLKEN_IOPCEN)
#define RCC_AHB_PERIPH_GPIOD  (RCC_AHBPCLKEN_IOPDEN)
#define RCC_AHB_PERIPH_ADC    (RCC_AHBPCLKEN_ADCEN)

/** APB2_peripheral **/
#define RCC_APB2_PERIPH_AFIO   (RCC_APB2PCLKEN_AFIOEN)
#define RCC_APB2_PERIPH_BEEPER (RCC_APB2PCLKEN_BEEPEN)
#define RCC_APB2_PERIPH_TIM1   (RCC_APB2PCLKEN_TIM1EN)
#define RCC_APB2_PERIPH_SPI1   (RCC_APB2PCLKEN_SPI1EN)
#define RCC_APB2_PERIPH_TIM8   (RCC_APB2PCLKEN_TIM8EN)
#define RCC_APB2_PERIPH_USART1 (RCC_APB2PCLKEN_USART1EN)
#define RCC_APB2_PERIPH_UART3  (RCC_APB2PCLKEN_UART3EN)
#define RCC_APB2_PERIPH_UART4  (RCC_APB2PCLKEN_UART4EN)
#define RCC_APB2_PERIPH_SPI2   (RCC_APB2PCLKEN_SPI2EN)

/** APB1_peripheral **/
#define RCC_APB1_PERIPH_TIM2       (RCC_APB1PCLKEN_TIM2EN)
#define RCC_APB1_PERIPH_TIM3       (RCC_APB1PCLKEN_TIM3EN)
#define RCC_APB1_PERIPH_TIM4       (RCC_APB1PCLKEN_TIM4EN)
#define RCC_APB1_PERIPH_TIM5       (RCC_APB1PCLKEN_TIM5EN)
#define RCC_APB1_PERIPH_TIM6       (RCC_APB1PCLKEN_TIM6EN)
#define RCC_APB1_PERIPH_COMP       (RCC_APB1PCLKEN_COMPEN)
#define RCC_APB1_PERIPH_COMP_FILT  (RCC_APB1PCLKEN_COMP_FILTEN)
#define RCC_APB1_PERIPH_WWDG       (RCC_APB1PCLKEN_WWDGEN)
#define RCC_APB1_PERIPH_USART2     (RCC_APB1PCLKEN_USART2EN)
#define RCC_APB1_PERIPH_I2C1       (RCC_APB1PCLKEN_I2C1EN)
#define RCC_APB1_PERIPH_I2C2       (RCC_APB1PCLKEN_I2C2EN)
#define RCC_APB1_PERIPH_CAN        (RCC_APB1PCLKEN_CANEN)
#define RCC_APB1_PERIPH_PWR        (RCC_APB1PCLKEN_PWREN)

/** MCO_PLL_prescaler **/
#define RCC_MCO_PLLCLK_DIV_MASK  (~RCC_CFG_MCOPRES)
#define RCC_MCO_PLLCLK_DIV2      (RCC_CFG_MCOPRES_PLLDIV2)
#define RCC_MCO_PLLCLK_DIV3      (RCC_CFG_MCOPRES_PLLDIV3)
#define RCC_MCO_PLLCLK_DIV4      (RCC_CFG_MCOPRES_PLLDIV4)
#define RCC_MCO_PLLCLK_DIV5      (RCC_CFG_MCOPRES_PLLDIV5)
#define RCC_MCO_PLLCLK_DIV6      (RCC_CFG_MCOPRES_PLLDIV6)
#define RCC_MCO_PLLCLK_DIV7      (RCC_CFG_MCOPRES_PLLDIV7)
#define RCC_MCO_PLLCLK_DIV8      (RCC_CFG_MCOPRES_PLLDIV8)
#define RCC_MCO_PLLCLK_DIV9      (RCC_CFG_MCOPRES_PLLDIV9)
#define RCC_MCO_PLLCLK_DIV10     (RCC_CFG_MCOPRES_PLLDIV10)
#define RCC_MCO_PLLCLK_DIV11     (RCC_CFG_MCOPRES_PLLDIV11)
#define RCC_MCO_PLLCLK_DIV12     (RCC_CFG_MCOPRES_PLLDIV12)
#define RCC_MCO_PLLCLK_DIV13     (RCC_CFG_MCOPRES_PLLDIV13)
#define RCC_MCO_PLLCLK_DIV14     (RCC_CFG_MCOPRES_PLLDIV14)
#define RCC_MCO_PLLCLK_DIV15     (RCC_CFG_MCOPRES_PLLDIV15)

/** Clock_source_to_output_on_MCO_pin **/
#define RCC_MCO_MASK   (~RCC_CFG_MCO)
#define RCC_MCO_NOCLK  (RCC_CFG_MCO_NOCLK)
#define RCC_MCO_SYSCLK (RCC_CFG_MCO_SYSCLK)
#define RCC_MCO_HSI    (RCC_CFG_MCO_HSI)
#define RCC_MCO_HSE    (RCC_CFG_MCO_HSE)
#define RCC_MCO_PLLCLK (RCC_CFG_MCO_PLL)
#define RCC_MCO_LSI    (RCC_CFG_MCO_LSI)
#define RCC_MCO_LSE    (RCC_CFG_MCO_LSE)

/** RCC_Flag **/
#define RCC_FLAG_MASK    ((uint8_t)0x1F)
#define RCC_FLAG_HSIRD   ((uint8_t)0x21)
#define RCC_FLAG_HSERD   ((uint8_t)0x31)
#define RCC_FLAG_PLLRD   ((uint8_t)0x39)
#define RCC_FLAG_LSERD   ((uint8_t)0x41)
#define RCC_FLAG_LSIRD   ((uint8_t)0x61)
#define RCC_FLAG_BKPEMC  ((uint8_t)0x75)
#define RCC_FLAG_MMURST  ((uint8_t)0x79)
#define RCC_FLAG_PINRST  ((uint8_t)0x7A)
#define RCC_FLAG_PORRST  ((uint8_t)0x7B)
#define RCC_FLAG_SFTRST  ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST ((uint8_t)0x7E)
#define RCC_FLAG_LPWRRST ((uint8_t)0x7F)

/** RCC_Flag **/
#define RCC_REMOVE_RESET_FLAG (RCC_CTRLSTS_RMRSTF)

/** RCC_Interrupt_source **/
/** Interrupts Flag **/
#define RCC_INT_LSIRDIF    (RCC_CLKINT_LSIRDIF )
#define RCC_INT_LSERDIF    (RCC_CLKINT_LSERDIF)
#define RCC_INT_HSIRDIF    (RCC_CLKINT_HSIRDIF)
#define RCC_INT_HSERDIF    (RCC_CLKINT_HSERDIF)
#define RCC_INT_PLLRDIF    (RCC_CLKINT_PLLRDIF)
#define RCC_INT_CLKSSIF    (RCC_CLKINT_CLKSSIF)
#define RCC_INT_LSESSIF    (RCC_CLKINT_LSESSIF)
/** Interrupts Enable **/
#define RCC_INT_LSIRDIEN   (RCC_CLKINT_LSIRDIEN)
#define RCC_INT_LSERDIEN   (RCC_CLKINT_LSERDIEN)
#define RCC_INT_HSIRDIEN   (RCC_CLKINT_HSIRDIEN)
#define RCC_INT_HSERDIEN   (RCC_CLKINT_HSERDIEN)
#define RCC_INT_PLLRDIEN   (RCC_CLKINT_PLLRDIEN)
#define RCC_INT_LSESSIEN   (RCC_CLKINT_LSESSIEN)
/** Interrupts Clear **/
#define RCC_INT_LSIRDICLR  (RCC_CLKINT_LSIRDICLR)
#define RCC_INT_LSERDICLR  (RCC_CLKINT_LSERDICLR)
#define RCC_INT_HSIRDICLR  (RCC_CLKINT_HSIRDICLR)
#define RCC_INT_HSERDICLR  (RCC_CLKINT_HSERDICLR)
#define RCC_INT_PLLRDICLR  (RCC_CLKINT_PLLRDICLR)
#define RCC_INT_CLKSSICLR  (RCC_CLKINT_CLKSSICLR)
#define RCC_INT_LSESSICLR  (RCC_CLKINT_LSESSICLR)
 

void RCC_Reset(void);
void RCC_HSE_Config(uint32_t RCC_HSE);
ErrorStatus RCC_HSE_Stable_Wait(void);
void RCC_Clock_Security_System_Enable(void);
void RCC_Clock_Security_System_Disable(void);
void RCC_HSI_Calibration_Value_Set(uint8_t calibration_value) ;
void RCC_HSI_Enable(void);
void RCC_HSI_Disable(void);
ErrorStatus RCC_HSI_Stable_Wait(void);
void RCC_PLL_Config(uint32_t PLL_source, uint32_t PLL_multiplication);
void RCC_PLL_Enable(void);
void RCC_PLL_Disable(void);
void RCC_Sysclk_Config(uint32_t sysclk_source);
uint8_t RCC_Sysclk_Source_Get(void);
void RCC_Hclk_Config(uint32_t sysclk_div);
void RCC_Pclk1_Config(uint32_t hclk_div);
void RCC_Pclk2_Config(uint32_t hclk_div);
void RCC_Interrupt_Enable(uint32_t interrupt);
void RCC_Interrupt_Disable(uint32_t interrupt);
void RCC_TIM1_8_Clock_Config(uint32_t timer1_8_clksrc);
void RCC_ADC_1M_Clock_Config(uint32_t ADC1M_clksrc, uint32_t ADC1M_prescaler);
void RCC_ADC_PLL_Clock_Prescaler_Enable(uint32_t ADC_PLLCLK_prescaler);
void RCC_ADC_PLL_Clock_Disable(void);
void RCC_ADC_Hclk_Config(uint32_t ADC_hclk_prescaler);
void RCC_ADC_Hclk_Enable(void);
void RCC_ADC_Hclk_Disable(void);

void RCC_LSE_Config(uint32_t RCC_LSE,uint16_t LSE_Trim);
void RCC_LSE_Clock_Security_System_Enable(void);
void RCC_LSE_Clock_Security_System_Disable(void);
FlagStatus RCC_LSE_Clock_Security_System_Status_Get(void);
ErrorStatus RCC_LSE_Stable_Wait(void);
void RCC_LSI_Enable(void);
void RCC_LSI_Disable(void);
ErrorStatus RCC_LSI_Stable_Wait(void);
void RCC_RTC_Clock_Config(uint32_t rtcclk_source);
void RCC_RTC_Clock_Enable(void);
void RCC_RTC_Clock_Disable(void);
void RCC_LPTIM_Clock_Config(uint32_t clock_source);
void RCC_LPTIM_Reset(void);
void RCC_LPTIM_Enable(void);
void RCC_LPTIM_Disable(void);
void RCC_Clocks_Frequencies_Value_Get(RCC_ClocksType* RCC_clocks);
void RCC_AHB_Peripheral_Clock_Enable(uint32_t AHB_periph);
void RCC_AHB_Peripheral_Clock_Disable(uint32_t AHB_periph);
void RCC_APB2_Peripheral_Clock_Enable(uint32_t APB2_periph);
void RCC_APB2_Peripheral_Clock_Disable(uint32_t APB2_periph);
void RCC_APB1_Peripheral_Clock_Enable(uint32_t APB1_periph);
void RCC_APB1_Peripheral_Clock_Disable(uint32_t APB1_periph);
void RCC_AHB_Peripheral_Reset(uint32_t AHB_periph);
void RCC_APB2_Peripheral_Reset(uint32_t APB2_periph);
void RCC_APB1_Peripheral_Reset(uint32_t APB1_periph);
void RCC_Backup_Reset(void);
void RCC_MCO_PLL_Prescaler_Config(uint32_t MCO_PLL_prescaler);
void RCC_MCO_Source_Config(uint32_t MCO_source);
FlagStatus RCC_Flag_Status_Get(uint8_t RCC_flag);
void RCC_Reset_Flag_Clear(void);
INTStatus RCC_Interrupt_Status_Get(uint32_t interrupt_flag);
void RCC_Interrupt_Status_Clear(uint32_t interrupt_clear);

#ifdef __cplusplus
}
#endif

#endif /* __N32G430_RCC_H__ */



