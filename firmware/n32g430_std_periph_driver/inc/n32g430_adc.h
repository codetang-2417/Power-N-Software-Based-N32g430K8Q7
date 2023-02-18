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
*\*\file n32g430_adc.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

 
#ifndef __N32G430_ADC_H__
#define __N32G430_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"
#include <stdbool.h>


/** ADC init structure definition **/
typedef struct
{
    FunctionalState MultiChEn;      /* Specifies whether the conversion is performed in
                                       Scan (multichannels) or Single (one channel) mode */

    FunctionalState ContinueConvEn; /* Specifies whether the conversion is performed in
                                       Continuous or Single mode */

    uint32_t ExtTrigSelect;         /* Defines the external trigger used to start the analog
                                       to digital conversion of regular channels */

    uint32_t DatAlign;              /* Specifies whether the ADC data alignment is left or right */

    uint32_t ChsNumber;             /* Specifies the number of ADC channels that will be converted
                                       using the sequencer for regular channel group */
} ADC_InitType;

/** ADC scan conversion define **/
#define ADC_MULTCH_ENABLE                    ((uint32_t)(ADC_CTRL1_SCANMD)) /* ADC_CTRL1 SCANMD bits */ 
#define ADC_MULTCH_DISABLE                   ((uint32_t)(~ADC_CTRL1_SCANMD)) 

/** ADC continue conversion define **/
#define ADC_CTU_ENABLE                       ((uint32_t)(ADC_CTRL2_CTU)) /* ADC_CTRL1 CTU bits */
#define ADC_CTU_DISABLE                      ((uint32_t)(~ADC_CTRL2_CTU)) 

/** ADC external trigger sources for regular channels conversion define **/
#define ADC_EXT_TRIGCONV_REGULAR_MASK        ((uint32_t)(~ADC_CTRL2_EXTRSEL)) /* ADC_CTRL2 EXTRSEL[2:0] bits Mask */
#define ADC_EXT_TRIGCONV_REGULAR_T1_CC1      ((uint32_t)0x00000000) 
#define ADC_EXT_TRIGCONV_REGULAR_T1_CC2      ((uint32_t)0x00020000) 
#define ADC_EXT_TRIGCONV_REGULAR_T1_CC3      ((uint32_t)0x00040000)
#define ADC_EXT_TRIGCONV_REGULAR_T2_CC2      ((uint32_t)0x00060000) 
#define ADC_EXT_TRIGCONV_REGULAR_T3_TRGO     ((uint32_t)0x00080000) 
#define ADC_EXT_TRIGCONV_REGULAR_T4_CC4      ((uint32_t)0x000A0000) 
#define ADC_EXT_TRIGCONV_REGULAR_EXT_INT11_TIM8_TRGO ((uint32_t)0x000C0000) 
#define ADC_EXT_TRIGCONV_REGULAR_SWSTRRCH    ((uint32_t)0x000E0000) 

/** ADC data alignment define **/
#define ADC_ALIG_MASK                        ((uint32_t)(~ADC_CTRL2_ALIG)) /* ADC_CTRL2 ALIG bits Mask */
#define ADC_DAT_ALIGN_R                      ((uint32_t)0x00000000)
#define ADC_DAT_ALIGN_L                      ((uint32_t)0x00000800)

/** ADC regular channel sequence length define **/
#define ADC_REGULAR_LEN_MSAK                 ((uint32_t)(~ADC_RSEQ1_LEN)) /* ADC_RSEQ1 LEN[3:0] bits Mask */
#define ADC_REGULAR_LEN_1                    ((uint32_t)0x00000000)
#define ADC_REGULAR_LEN_2                    ((uint32_t)0x00100000)
#define ADC_REGULAR_LEN_3                    ((uint32_t)0x00200000)
#define ADC_REGULAR_LEN_4                    ((uint32_t)0x00300000)
#define ADC_REGULAR_LEN_5                    ((uint32_t)0x00400000)
#define ADC_REGULAR_LEN_6                    ((uint32_t)0x00500000)
#define ADC_REGULAR_LEN_7                    ((uint32_t)0x00600000)
#define ADC_REGULAR_LEN_8                    ((uint32_t)0x00700000)
#define ADC_REGULAR_LEN_9                    ((uint32_t)0x00800000)
#define ADC_REGULAR_LEN_10                   ((uint32_t)0x00900000)
#define ADC_REGULAR_LEN_11                   ((uint32_t)0x00A00000)
#define ADC_REGULAR_LEN_12                   ((uint32_t)0x00B00000)
#define ADC_REGULAR_LEN_13                   ((uint32_t)0x00C00000)
#define ADC_REGULAR_LEN_14                   ((uint32_t)0x00D00000)
#define ADC_REGULAR_LEN_15                   ((uint32_t)0x00E00000)
#define ADC_REGULAR_LEN_16                   ((uint32_t)0x00F00000)

/** ADC channels define **/
#define ADC_CH_0                             ((uint8_t)0x00)
#define ADC_CH_1                             ((uint8_t)0x01)
#define ADC_CH_2                             ((uint8_t)0x02)
#define ADC_CH_3                             ((uint8_t)0x03)
#define ADC_CH_4                             ((uint8_t)0x04)
#define ADC_CH_5                             ((uint8_t)0x05)
#define ADC_CH_6                             ((uint8_t)0x06)
#define ADC_CH_7                             ((uint8_t)0x07)
#define ADC_CH_8                             ((uint8_t)0x08)
#define ADC_CH_9                             ((uint8_t)0x09)
#define ADC_CH_10                            ((uint8_t)0x0A)
#define ADC_CH_11                            ((uint8_t)0x0B)
#define ADC_CH_12                            ((uint8_t)0x0C)
#define ADC_CH_13                            ((uint8_t)0x0D)
#define ADC_CH_14                            ((uint8_t)0x0E)
#define ADC_CH_15                            ((uint8_t)0x0F)
#define ADC_CH_16                            ((uint8_t)0x10)
#define ADC_CH_17                            ((uint8_t)0x11)
#define ADC_CH_18                            ((uint8_t)0x12)
#define ADC_CH_TEMP_SENSOR                   ((uint8_t)ADC_CH_17)
#define ADC_CH_INT_VREF                      ((uint8_t)ADC_CH_0)
#define ADC_CH_BUFF_VREF                     ((uint8_t)ADC_CH_18)

#define ADC_Channel_01_PA0                  ((uint8_t)0x01)
#define ADC_Channel_02_PA1                  ((uint8_t)0x02)
#define ADC_Channel_03_PA2                  ((uint8_t)0x03)
#define ADC_Channel_04_PA3                  ((uint8_t)0x04)
#define ADC_Channel_05_PA4                  ((uint8_t)0x05)
#define ADC_Channel_06_PA5                  ((uint8_t)0x06)
#define ADC_Channel_07_PA6                  ((uint8_t)0x07)
#define ADC_Channel_08_PA7                  ((uint8_t)0x08)
#define ADC_Channel_09_PB0                  ((uint8_t)0x09)
#define ADC_Channel_10_PB1                  ((uint8_t)0x0A)
#define ADC_Channel_11_PB2                  ((uint8_t)0x0B)
#define ADC_Channel_12_PB10                 ((uint8_t)0x0C)
#define ADC_Channel_13_PB11                 ((uint8_t)0x0D)
#define ADC_Channel_14_PB12                 ((uint8_t)0x0E)
#define ADC_Channel_15_PB13                 ((uint8_t)0x0F)
#define ADC_Channel_16_PB14                 ((uint8_t)0x10)

/** ADC converter operation define **/
#define ADC_TURN_ON                          ((uint32_t)ADC_CTRL2_ON)    /* ADC_CTRL2 ON bit */
#define ADC_TURN_OFF                         ((uint32_t)(~ADC_CTRL2_ON)) 

/** ADC DMA Config define **/
#define ADC_DMA_ENABLE                       ((uint32_t)ADC_CTRL2_ENDMA)    /* ADC_CTRL2 ENDMA bit */
#define ADC_DMA_DISABLE                      ((uint32_t)(~ADC_CTRL2_ENDMA)) 

/** ADC interrupts define **/
#define ADC_INT_ENDC                         ((uint32_t)ADC_CTRL1_ENDCIEN)   /* ADC_CTRL1 ENDCIEN bits */
#define ADC_INT_AWD                          ((uint32_t)ADC_CTRL1_AWDGIEN)   /* ADC_CTRL1 AWDGIEN bits */
#define ADC_INT_JENDC                        ((uint32_t)ADC_CTRL1_JENDCIEN)  /* ADC_CTRL1 JENDCIEN bits */
#define ADC_INT_ENDCA                        ((uint32_t)ADC_CTRL3_ENDCAIEN)  /* ADC_CTRL3 ENDCAIEN bits */
#define ADC_INT_JENDCA                       ((uint32_t)ADC_CTRL3_JENDCAIEN) /* ADC_CTRL3 JENDCAIEN bits */

/** ADC calibration operation define **/
#define ADC_CALIBRATION_ENABLE               ((uint32_t)0x00000001)
#define ADC_CALIBRATION_STS                  ((uint32_t)0x00000002)

/** ADC regular channels software conversion operation define **/
#define ADC_EXTRTRIG_SWSTRRCH_ENABLE         ((uint32_t)(ADC_CTRL2_EXTRTRIG | ADC_CTRL2_SWSTRRCH))
#define ADC_EXTRTRIG_SWSTRRCH_DISABLE        ((uint32_t)(~(ADC_CTRL2_EXTRTRIG | ADC_CTRL2_SWSTRRCH)))
#define ADC_EXTRTRIG_SWSTRRCH_GET_STS        ((uint32_t)ADC_CTRL2_SWSTRRCH)

/** ADC channels count of discontinuous mode define **/
#define ADC_CHANNEL_COUNT_MASK               ((uint32_t)(~ADC_CTRL1_DCTU)) /* ADC_CTRL1 DCTU[2:0] bit Mask */
#define ADC_CHANNEL_COUNT_1                  ((uint32_t)0x00000000)
#define ADC_CHANNEL_COUNT_2                  ((uint32_t)0x00002000)
#define ADC_CHANNEL_COUNT_3                  ((uint32_t)0x00004000)
#define ADC_CHANNEL_COUNT_4                  ((uint32_t)0x00006000)
#define ADC_CHANNEL_COUNT_5                  ((uint32_t)0x00008000)
#define ADC_CHANNEL_COUNT_6                  ((uint32_t)0x0000A000)
#define ADC_CHANNEL_COUNT_7                  ((uint32_t)0x0000C000)
#define ADC_CHANNEL_COUNT_8                  ((uint32_t)0x0000E000)

/** ADC discontinuous mode on regular or injected group operation define **/
#define ADC_DISCMODE_REGULAR_ENABLE          ((uint32_t)ADC_CTRL1_DREGCH)
#define ADC_DISCMODE_REGULAR_DISABLE         ((uint32_t)(~ADC_CTRL1_DREGCH))
#define ADC_DISCMODE_INJECTED_ENABLE         ((uint32_t)ADC_CTRL1_DJCH)
#define ADC_DISCMODE_INJECTED_DISABLE        ((uint32_t)(~ADC_CTRL1_DJCH))

/** ADC sampling time define **/
#define ADC_SAMP_TIME_UNIT                   ((uint32_t)0x00000007)
#define ADC_SAMP_TIME_UNIT_OFFSET            ((uint8_t)0x03) //kuohao
#define ADC_SAMP_TIME_MASK(offset)           ((uint32_t)(~(ADC_SAMP_TIME_UNIT << ((offset) * ADC_SAMP_TIME_UNIT_OFFSET))))
#define ADC_SAMP_TIME_1CYCLES5               ((uint8_t)0x00)
#define ADC_SAMP_TIME_7CYCLES5               ((uint8_t)0x01)
#define ADC_SAMP_TIME_13CYCLES5              ((uint8_t)0x02)
#define ADC_SAMP_TIME_28CYCLES5              ((uint8_t)0x03)
#define ADC_SAMP_TIME_41CYCLES5              ((uint8_t)0x04)
#define ADC_SAMP_TIME_55CYCLES5              ((uint8_t)0x05)
#define ADC_SAMP_TIME_71CYCLES5              ((uint8_t)0x06)
#define ADC_SAMP_TIME_239CYCLES5             ((uint8_t)0x07)

/** ADC regular sequence number define **/
#define ADC_REG_SEQ_NUM_OFFSET1              ((uint8_t)0x05)
#define ADC_REG_SEQ_NUM_OFFSET2              ((uint8_t)0x0B)
#define ADC_REG_SEQ_NUM_OFFSET3              ((uint8_t)(ADC_REG_SEQ_NUM_OFFSET2 - ADC_REG_SEQ_NUM_OFFSET1))
#define ADC_REG_SEQ_NUM_OFFSET4              ((uint8_t)0x0C)
#define ADC_REGULAR_NUM_UNIT                 ((uint32_t)0x0000001F)
#define ADC_REGULAR_NUM_UNIT_OFFSET          ((uint8_t)0x05)
#define ADC_REGULAR_NUMBER_MASK(num)         ((uint32_t)(~(ADC_REGULAR_NUM_UNIT << ((num) * ADC_REGULAR_NUM_UNIT_OFFSET))))
#define ADC_REGULAR_NUMBER_SET(ch, num)      ((uint32_t)((ch) << ((num) * ADC_REGULAR_NUM_UNIT_OFFSET)))
#define ADC_REGULAR_NUMBER_1                 ((uint8_t)0x00)
#define ADC_REGULAR_NUMBER_2                 ((uint8_t)0x01)
#define ADC_REGULAR_NUMBER_3                 ((uint8_t)0x02)
#define ADC_REGULAR_NUMBER_4                 ((uint8_t)0x03)
#define ADC_REGULAR_NUMBER_5                 ((uint8_t)0x04)
#define ADC_REGULAR_NUMBER_6                 ((uint8_t)0x05)
#define ADC_REGULAR_NUMBER_7                 ((uint8_t)0x06)
#define ADC_REGULAR_NUMBER_8                 ((uint8_t)0x07)
#define ADC_REGULAR_NUMBER_9                 ((uint8_t)0x08)
#define ADC_REGULAR_NUMBER_10                ((uint8_t)0x09)
#define ADC_REGULAR_NUMBER_11                ((uint8_t)0x0A)
#define ADC_REGULAR_NUMBER_12                ((uint8_t)0x0B)
#define ADC_REGULAR_NUMBER_13                ((uint8_t)0x0C)
#define ADC_REGULAR_NUMBER_14                ((uint8_t)0x0D)
#define ADC_REGULAR_NUMBER_15                ((uint8_t)0x0E)
#define ADC_REGULAR_NUMBER_16                ((uint8_t)0x0F)

/** ADC external trigger source enable or disable define **/
#define ADC_EXTTRIGCONV_REGULAR_ENABLE       ((uint32_t)ADC_CTRL2_EXTRTRIG)    /* ADC_CTRL2 EXTRTRIG bit */
#define ADC_EXTTRIGCONV_REGULAR_DISABLE      ((uint32_t)(~ADC_CTRL2_EXTRTRIG)) 
#define ADC_EXTTRIGCONV_INJECTED_ENABLE      ((uint32_t)ADC_CTRL2_EXTJTRIG)    /* ADC_CTRL2 EXTJTRIG bit */
#define ADC_EXTTRIGCONV_INJECTED_DISABLE     ((uint32_t)(~ADC_CTRL2_EXTJTRIG)) 

/** ADC injected group auto conversion mode define **/
#define ADC_INJECTED_AUTOCONV_ENABLE         ((uint32_t)ADC_CTRL1_AUTOJC)    
#define ADC_INJECTED_AUTOCONV_DISABLE        ((uint32_t)(~ADC_CTRL1_AUTOJC)) 

/** ADC external trigger sources for injected channels conversion define **/
#define ADC_EXT_TRIGCONV_INJECTED_MASK       ((uint32_t)(~ADC_CTRL2_EXTJSEL)) /* EXTRSEL[2:0] bits Mask */
#define ADC_EXT_TRIGCONV_INJECTED_T1_TRGO    ((uint32_t)0x00000000)
#define ADC_EXT_TRIGCONV_INJECTED_T1_CC4     ((uint32_t)0x00001000) 
#define ADC_EXT_TRIGCONV_INJECTED_T2_TRGO    ((uint32_t)0x00002000) 
#define ADC_EXT_TRIGCONV_INJECTED_T2_CC1     ((uint32_t)0x00003000) 
#define ADC_EXT_TRIGCONV_INJECTED_T3_CC4     ((uint32_t)0x00004000) 
#define ADC_EXT_TRIGCONV_INJECTED_T4_TRGO    ((uint32_t)0x00005000)
#define ADC_EXT_TRIGCONV_INJECTED_EXT_INT15_TIM8_CC4 ((uint32_t)0x00006000) 
#define ADC_EXT_TRIGCONV_INJECTED_SWSTRJCH   ((uint32_t)0x00007000) 

/** ADC injected channels software conversion operation define **/
#define ADC_EXTJTRIG_SWSTRJCH_ENABLE         ((uint32_t)(ADC_CTRL2_EXTJTRIG | ADC_CTRL2_SWSTRJCH))
#define ADC_EXTJTRIG_SWSTRJCH_DISABLE        ((uint32_t)(~(ADC_CTRL2_EXTJTRIG | ADC_CTRL2_SWSTRJCH)))
#define ADC_EXTJTRIG_SWSTRJCH_GET_STS        ((uint32_t)ADC_CTRL2_SWSTRJCH)

/** ADC injected sequence number define **/
#define ADC_INJECTED_NUM_UNIT                ((uint32_t)0x0000001F) 
#define ADC_INJECTED_NUM_UNIT_NUM            ((uint8_t)0x05) 
#define ADC_INJECTED_NUMBER_MASK(num)        ((uint32_t)(~(ADC_INJECTED_NUM_UNIT << ((num) * ADC_INJECTED_NUM_UNIT_NUM))))
#define ADC_INJECTED_NUMBER_SET(ch, num)     ((uint32_t)((ch) << ((num) * ADC_INJECTED_NUM_UNIT_NUM)))
#define ADC_INJECTED_NUMBER_1                ((uint8_t)0x00)
#define ADC_INJECTED_NUMBER_2                ((uint8_t)0x01)
#define ADC_INJECTED_NUMBER_3                ((uint8_t)0x02)
#define ADC_INJECTED_NUMBER_4                ((uint8_t)0x03)

/** ADC injected channel sequence length define **/
#define ADC_INJECTED_LEN_MSAK                ((uint32_t)(~ADC_JSEQ_JLEN)) /* ADC_JSEQ LEN[3:0] bits Mask */
#define ADC_INJECTED_LEN_1                   ((uint32_t)0x00000000) /* Start conversion in the order of 4 */
#define ADC_INJECTED_LEN_2                   ((uint32_t)0x00100000) /* Start conversion in the order of 3, 4 */
#define ADC_INJECTED_LEN_3                   ((uint32_t)0x00200000) /* Start conversion in the order of 2, 3, 4 */
#define ADC_INJECTED_LEN_4                   ((uint32_t)0x00300000) /* Start conversion in the order of 1, 2, 3, 4 */

/** ADC select injected channel registers offset define **/ 
#define ADC_INJECTED_DATA_REG_1              ((uint8_t)0x14)
#define ADC_INJECTED_DATA_REG_2              ((uint8_t)0x18)
#define ADC_INJECTED_DATA_REG_3              ((uint8_t)0x1C)
#define ADC_INJECTED_DATA_REG_4              ((uint8_t)0x20)

/** ADC JDATx registers offset define **/
#define ADC_JDAT_REG_OFFSET                  ((uint8_t)0x28)

/** ADC analog watchdog mode define **/
#define ADC_ANALOG_WTDG_MODE_MASK            ((uint32_t)(~ADC_CTRL1_AWDGSGLEN))
#define ADC_ANALOG_WTDG_SINGLE_MODE          ((uint32_t)ADC_CTRL1_AWDGSGLEN)
#define ADC_ANALOG_WTDG_SCAN_MODE            ((uint32_t)0x00000000)

/** ADC analog watchdog single mode channel define**/
#define ADC_ANALOG_WTDG_SINGLE_CH_MASK       ((uint32_t)(~ADC_CTRL1_AWDGCH))
#define ADC_ANALOG_WTDG_SINGLE_CH0           ((uint8_t)ADC_CH_0)
#define ADC_ANALOG_WTDG_SINGLE_CH1           ((uint8_t)ADC_CH_1)
#define ADC_ANALOG_WTDG_SINGLE_CH2           ((uint8_t)ADC_CH_2)
#define ADC_ANALOG_WTDG_SINGLE_CH3           ((uint8_t)ADC_CH_3)
#define ADC_ANALOG_WTDG_SINGLE_CH4           ((uint8_t)ADC_CH_4)
#define ADC_ANALOG_WTDG_SINGLE_CH5           ((uint8_t)ADC_CH_5)
#define ADC_ANALOG_WTDG_SINGLE_CH6           ((uint8_t)ADC_CH_6)
#define ADC_ANALOG_WTDG_SINGLE_CH7           ((uint8_t)ADC_CH_7)
#define ADC_ANALOG_WTDG_SINGLE_CH8           ((uint8_t)ADC_CH_8)
#define ADC_ANALOG_WTDG_SINGLE_CH9           ((uint8_t)ADC_CH_9)
#define ADC_ANALOG_WTDG_SINGLE_CH10          ((uint8_t)ADC_CH_10)
#define ADC_ANALOG_WTDG_SINGLE_CH11          ((uint8_t)ADC_CH_11)
#define ADC_ANALOG_WTDG_SINGLE_CH12          ((uint8_t)ADC_CH_12)
#define ADC_ANALOG_WTDG_SINGLE_CH13          ((uint8_t)ADC_CH_13)
#define ADC_ANALOG_WTDG_SINGLE_CH14          ((uint8_t)ADC_CH_14)
#define ADC_ANALOG_WTDG_SINGLE_CH15          ((uint8_t)ADC_CH_15)
#define ADC_ANALOG_WTDG_SINGLE_CH16          ((uint8_t)ADC_CH_16)
#define ADC_ANALOG_WTDG_SINGLE_CH17          ((uint8_t)ADC_CH_17)
#define ADC_ANALOG_WTDG_SINGLE_CH18          ((uint8_t)ADC_CH_18)

/** ADC ADC Analog watchdog on regular channels define **/
#define ADC_ANALOG_WTDG_REGULAR              ((uint32_t)ADC_CTRL1_AWDGERCH)    /* ADC_CTRL1 AWDGERCH bit */
/** ADC ADC Analog watchdog on injected channels define **/
#define ADC_ANALOG_WTDG_INJECTED             ((uint32_t)ADC_CTRL1_AWDGEJCH)    /* ADC_CTRL1 AWDGEJCH bit */

/** ADC Temperature sensor and Vrefint define **/
#define ADC_TS_VREFINT_CHANNEL_ENABLE        ((uint32_t)ADC_CTRL2_TEMPEN)      /* ADC_CTRL2 TEMPEN bit */
#define ADC_TS_VREFINT_CHANNEL_DISABLE       ((uint32_t)(~ADC_CTRL2_TEMPEN))  
/* AFEC registers about temperature sensor and vrefint operation define */
#define VREF1P2_CTRL                         (*(uint32_t*)(0x40001800+0x20))
#define _EnVref1p2()                         do{VREF1P2_CTRL|=(1<<10);}while(0);
#define _DisVref1p2()                        do{VREF1P2_CTRL&=~(1<<10);}while(0);

/** ADC flags definition **/
#define ADC_RUN_FLAG                         ((uint8_t)0x01)
#define ADC_RD_FLAG                          ((uint8_t)0x02)

#define ADC_INT_FLAG_AWDG                    ((uint8_t)0x01)
#define ADC_INT_FLAG_ENDC                    ((uint8_t)0x02)
#define ADC_INT_FLAG_JENDC                   ((uint8_t)0x04)
#define ADC_INT_FLAG_ENDCA                   ((uint8_t)0x20)
#define ADC_INT_FLAG_JENDCA                  ((uint8_t)0x40)

#define ADC_FLAG_AWDG                        ((uint8_t)0x01)
#define ADC_FLAG_ENDC                        ((uint8_t)0x02)
#define ADC_FLAG_JENDC                       ((uint8_t)0x04)
#define ADC_FLAG_JSTR                        ((uint8_t)0x08)
#define ADC_FLAG_STR                         ((uint8_t)0x10)
#define ADC_FLAG_ENDCA                       ((uint8_t)0x20)
#define ADC_FLAG_JENDCA                      ((uint8_t)0x40)
/** ADC flags ex definition **/
#define ADC_FLAG_RDY                         ((uint8_t)0x20)
#define ADC_FLAG_PD_RDY                      ((uint8_t)0x40)

/** ADC sample time level define **/
#define ADC_SAMPLE3_TIME_LEVEL_MASK          ((uint32_t)(~ADC_SAMPT3_SAMPSEL))
#define ADC_SAMPLE3_TIME_LEVEL_0             ((uint32_t)0x00000000)
#define ADC_SAMPLE3_TIME_LEVEL_1             ((uint32_t)ADC_SAMPT3_SAMPSEL)

/** ADC clock mode define **/
typedef enum
{
    ADC_CKMOD_AHB = 0,
    ADC_CKMOD_PLL = 1,
}ADC_CKMOD;

/** fllowing bit seg in ex register  **/
/** ADC channels ex style **/
typedef struct
{
    FunctionalState VbatMinitEn;
    FunctionalState DeepPowerModEn;
    FunctionalState JendcIntEn;
    FunctionalState EndcIntEn;
    ADC_CKMOD ClkMode;
    FunctionalState CalAtuoLoadEn;
    FunctionalState DifModCal;
    uint32_t ResBit;
    uint32_t SampSecondStyle;
} ADC_InitTypeEx;

/** ADC_SAMPT3 only have samp time and smp18[2:0],samp18 is refint ch, change to row function **/
/** ADC_IPTST reseverd register ,not to do it **/

/** ADC sampt3 definition **/
#define ADC_SAMPLE_LEVEL_MASK        ((uint32_t)(~ADC_SAMPT3_SAMPSEL))
#define ADC_SAMPLE_LEVEL_0           ((uint32_t)0x00000000)
#define ADC_SAMPLE_LEVEL_1           ((uint32_t)ADC_SAMPT3_SAMPSEL)

/** ADC ctrl3 definition **/ 
#define ADC_VBAT_MONITOR_ENABLE      ((uint32_t)ADC_CTRL3_VBATMEN)    
#define ADC_VBAT_MONITOR_DISABLE     ((uint32_t)(~ADC_CTRL3_VBATMEN))  

#define ADC_DEEP_POWER_ENABLE        ((uint32_t)ADC_CTRL3_DPWMOD)
#define ADC_DEEP_POWER_DISABLE       ((uint32_t)~ADC_CTRL3_DPWMOD)

#define ADC_JENDCAIEN_MSK            ((uint32_t)ADC_CTRL3_JENDCAIEN)
#define ADC_ENDCAIEN_MSK             ((uint32_t)ADC_CTRL3_ENDCAIEN)

#define ADC_BYPASSES_CAL_ENABLE      ((uint32_t)ADC_CTRL3_BPCAL)
#define ADC_BYPASSES_CAL_DISABLE     ((uint32_t)~ADC_CTRL3_BPCAL)

#define ADC_POWER_DOWN_RDY_MSK       ((uint32_t)ADC_CTRL3_PDRDY)
#define ADC_RDY_MSK                  ((uint32_t)ADC_CTRL3_RDY)

#define ADC_CLOCK_PLL                ((uint32_t)ADC_CTRL3_CKMOD)
#define ADC_CLOCK_AHB                ((uint32_t)~ADC_CTRL3_CKMOD)

#define ADC_CALALD_ENABLE            ((uint32_t)ADC_CTRL3_CALALD)
#define ADC_CALALD_DISABLE           ((uint32_t)~ADC_CTRL3_CALALD)

#define ADC_CALDIF_ENABLE            ((uint32_t)ADC_CTRL3_CALDIF)
#define ADC_CALDIF_DISABLE           ((uint32_t)~ADC_CTRL3_CALDIF)

#define ADC_RES_MSK                  ((uint32_t)~ADC_CTRL3_RES)

/** ADC bit num definition **/
#define ADC_RST_BIT_12      ((uint32_t)0x03)
#define ADC_RST_BIT_10      ((uint32_t)0x02)
#define ADC_RST_BIT_8       ((uint32_t)0x01)
#define ADC_RST_BIT_6       ((uint32_t)0x00)

/** ADC differential select channel definition **/
#define ADC_DIFSEL_CHS_MASK ((uint32_t)~ADC_DIFSEL_DIFSEL)
#define ADC_DIFSEL_CHS_0    ((uint32_t)ADC_DIFSEL_DIFSEL_0)
#define ADC_DIFSEL_CHS_1    ((uint32_t)ADC_DIFSEL_DIFSEL_1)
#define ADC_DIFSEL_CHS_2    ((uint32_t)ADC_DIFSEL_DIFSEL_2)
#define ADC_DIFSEL_CHS_3    ((uint32_t)ADC_DIFSEL_DIFSEL_3)
#define ADC_DIFSEL_CHS_4    ((uint32_t)ADC_DIFSEL_DIFSEL_4)
#define ADC_DIFSEL_CHS_5    ((uint32_t)ADC_DIFSEL_DIFSEL_5)
#define ADC_DIFSEL_CHS_6    ((uint32_t)ADC_DIFSEL_DIFSEL_6)
#define ADC_DIFSEL_CHS_7    ((uint32_t)ADC_DIFSEL_DIFSEL_7)
#define ADC_DIFSEL_CHS_8    ((uint32_t)ADC_DIFSEL_DIFSEL_8)
#define ADC_DIFSEL_CHS_9    ((uint32_t)ADC_DIFSEL_DIFSEL_9)
#define ADC_DIFSEL_CHS_10   ((uint32_t)ADC_DIFSEL_DIFSEL_10)
#define ADC_DIFSEL_CHS_11   ((uint32_t)ADC_DIFSEL_DIFSEL_11)
#define ADC_DIFSEL_CHS_12   ((uint32_t)ADC_DIFSEL_DIFSEL_12)
#define ADC_DIFSEL_CHS_13   ((uint32_t)ADC_DIFSEL_DIFSEL_13)
#define ADC_DIFSEL_CHS_14   ((uint32_t)ADC_DIFSEL_DIFSEL_14) 
#define ADC_DIFSEL_CHS_15   ((uint32_t)ADC_DIFSEL_DIFSEL_15)
#define ADC_DIFSEL_CHS_16   ((uint32_t)ADC_DIFSEL_DIFSEL_16)
#define ADC_DIFSEL_CHS_17   ((uint32_t)ADC_DIFSEL_DIFSEL_17)
#define ADC_DIFSEL_CHS_18   ((uint32_t)ADC_DIFSEL_DIFSEL_18)

/** ADC Driving Functions Declaration **/

void ADC_Reset(void);

void ADC_Multichannels_Enable(void);
void ADC_Multichannels_Disable(void);

void ADC_Continue_Conversion_Enable(void);
void ADC_Continue_Conversion_Disable(void);

void ADC_Regular_Group_External_Trigger_Source_Config(uint32_t external_trigger_sources);
void ADC_Data_Alignment_Config(uint32_t data_alignment);
void ADC_Regular_Channels_Number_Config(uint32_t channels_number);

void ADC_Initializes(ADC_InitType* ADC_initstruct);
void ADC_Initializes_Structure(ADC_InitType* ADC_initstruct);

void ADC_ON(void);
void ADC_OFF(void);

void ADC_DMA_Transfer_Enable(void);
void ADC_DMA_Transfer_Disable(void);

void ADC_Interrupts_Enable(uint32_t adc_interrupt);
void ADC_Interrupts_Disable(uint32_t adc_interrupt);

FlagStatus ADC_Calibration_Operation(uint32_t calibration_operation);

FlagStatus ADC_Regular_Channels_Software_Conversion_Operation(uint32_t conversion_operation);

void ADC_Discontinuous_Mode_Channel_Count_Config(uint32_t channel_count);
void ADC_Discontinuous_Mode_Config(uint32_t group_operation);

void ADC_Channel_Sample_Time_Config(uint8_t channel, uint8_t sample_time);
void ADC_Regular_Sequence_Conversion_Number_Config(uint8_t channel, uint8_t number);
void ADC_External_Trigger_Conversion_Config(uint32_t group_operation);
uint16_t ADC_Regular_Group_Conversion_Data_Get(void);

void ADC_Injected_Group_Autoconversion_Enable(void);
void ADC_Injected_Group_Autoconversion_Disable(void);

void ADC_Injected_Group_External_Trigger_Source_Config(uint32_t external_trigger_sources);
FlagStatus ADC_Injected_Channels_Software_Conversion_Operation(uint32_t conversion_operation);
void ADC_Injected_Sequence_Conversion_Number_Config(uint8_t channel, uint8_t number);
void ADC_Injected_Channels_Number_Config(uint32_t channels_number);
void ADC_Injected_Channels_Offset_Config(uint8_t injected_channel, uint16_t offset_data);
uint16_t ADC_Injected_Group_Conversion_Data_Get(uint8_t reg_offset);

void ADC_Analog_Watchdog_Mode_Channel_Config(uint32_t mode, uint8_t channel);
void ADC_Analog_Watchdog_Enable(uint32_t wcdg_mode);
void ADC_Analog_Watchdog_Disable(uint32_t wcdg_mode);
void ADC_Analog_Watchdog_HighThresholds_Config(uint16_t high_thresholds);
void ADC_Analog_Watchdog_LowThresholds_Config(uint16_t low_thresholds);

void ADC_Temperature_Sensor_And_Vrefint_Channel_Enable(void);
void ADC_Temperature_Sensor_And_Vrefint_Channel_Disable(void);

FlagStatus ADC_INTFlag_Status_Get(uint8_t adc_flag);
FlagStatus ADC_Flag_Status_Get(uint8_t selflag, uint8_t adc_runflag, uint8_t adc_rdflag);
void ADC_INTFlag_Status_Clear(uint8_t adc_flag);
void ADC_Flag_Status_Clear(uint8_t adc_flag);

void ADC_Vbat_Monitor_Enable(void);
void ADC_Vbat_Monitor_Disable(void);

void ADC_Deep_Power_Mode_Enable(void);
void ADC_Deep_Power_Mode_Disable(void);

void ADC_AHB_Clock_Mode_Config(void);
void ADC_PLL_Clock_Mode_Config(void);

void ADC_Calibration_Auto_Load_Enable(void);
void ADC_Calibration_Auto_Load_Disable(void);

void ADC_Differential_Mode_Enable(void);
void ADC_Differential_Mode_Disable(void);

void ADC_Data_Resolution_Config(uint32_t resbit);
void ADC_Sample_Time_Level_Config(uint32_t sample_time_level);

void ADC_Initializes_Ex(ADC_InitTypeEx* ADC_initstructEx);
void ADC_Initializes_StructureEx(ADC_InitTypeEx* ADC_initstructEx);

void ADC_Bypass_Calibration_Enable(void);
void ADC_Bypass_Calibration_Disable(void);

void ADC_Differential_Channels_Config(uint32_t difchs);
void ADC_Clock_Mode_Config(ADC_CKMOD ADC_clkmode, uint32_t RCC_ADCHCLKprescaler);
uint32_t ADC_Vrefint_Get(void);

#ifdef __cplusplus
}
#endif

#endif /*__N32G430_ADC_H__ */



