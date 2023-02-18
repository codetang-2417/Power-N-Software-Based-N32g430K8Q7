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
*\*\file n32g430_pwr.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#ifndef __N32G430_PWR_H__
#define __N32G430_PWR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

/*** PWR Structure Definition Start ***/

/** PWR sleep status enmu definition **/
typedef enum
{
    PWR_SLEEP_NOW = 0,
    PWR_SLEEP_ON_EXIT = 1,
} PWR_SLEEPONEXIT_STATUS; 

/** PWR wakeup PINx enmu definition **/
typedef enum
{
    WAKEUP_PIN1 = 0x0100,
    WAKEUP_PIN2 = 0x0200,
    WAKEUP_PIN3 = 0x0400,
} WAKEUP_PINX;

/*** PWR Structure Definition End ***/

/*** PWR Macro Definition Start ***/

/** PWR registers bit address in the alias region **/
#define PWR_OFFSET (PWR_BASE - PERIPH_BASE)

/** Alias word address of DBKP bit **/
#define PWR_CTRL_OFFSET       (PWR_OFFSET + 0x00)
#define PWR_DBKP_BIT_NUM      (0x08)
#define PWR_CTRL_DBKP_BITBAND (PERIPH_BB_BASE + (PWR_CTRL_OFFSET * 32) + (PWR_DBKP_BIT_NUM * 4))

/** Alias word address of PVDEN bit **/
#define PWR_PVDEN_BIT_NUM      (0x04)
#define PWR_CTRL_PVDEN_BITBAND (PERIPH_BB_BASE + (PWR_CTRL_OFFSET * 32) + (PWR_PVDEN_BIT_NUM * 4))

/** Alias word address of WKUP3PS bit **/
#define PWR_CTRLSTS_OFFSET         (PWR_OFFSET + 0x04)
#define PWR_WKUP3PS_BIT_NUM         (0x0E)
#define PWR_CTRLSTS_WKUP3PS_BITBAND (PERIPH_BB_BASE + (PWR_CTRLSTS_OFFSET * 32) + (PWR_WKUP3PS_BIT_NUM * 4))

/** Alias word address of WKUP2PS bit **/
#define PWR_WKUP2PS_BIT_NUM         (0x0D)
#define PWR_CTRLSTS_WKUP2PS_BITBAND (PERIPH_BB_BASE + (PWR_CTRLSTS_OFFSET * 32) + (PWR_WKUP2PS_BIT_NUM * 4))

/** Alias word address of WKUP1PS bit **/
#define PWR_WKUP1PS_BIT_NUM         (0x0C)
#define PWR_CTRLSTS_WKUP1PS_BITBAND (PERIPH_BB_BASE + (PWR_CTRLSTS_OFFSET * 32) + (PWR_WKUP1PS_BIT_NUM * 4))

/** Alias word address of WKUPRTCEN bit **/
#define PWR_WKUPRTCEN_BIT_NUM         (0x0B)
#define PWR_CTRLSTS_WKUPRTCEN_BITBAND (PERIPH_BB_BASE + (PWR_CTRLSTS_OFFSET * 32) + (PWR_WKUPRTCEN_BIT_NUM * 4))

/** Alias word address of WKUP3EN bit **/
#define PWR_WKUP3EN_BIT_NUM         (0x0A)
#define PWR_CTRLSTS_WKUP3EN_BITBAND (PERIPH_BB_BASE + (PWR_CTRLSTS_OFFSET * 32) + (PWR_WKUP3EN_BIT_NUM * 4))

/** Alias word address of WKUP2EN bit **/
#define PWR_WKUP2EN_BIT_NUM         (0x09)
#define PWR_CTRLSTS_WKUP2EN_BITBAND (PERIPH_BB_BASE + (PWR_CTRLSTS_OFFSET * 32) + (PWR_WKUP2EN_BIT_NUM * 4))

/** Alias word address of WKUP1EN bit **/
#define PWR_WKUP1EN_BIT_NUM         (0x08)
#define PWR_CTRLSTS_WKUP1EN_BITBAND (PERIPH_BB_BASE + (PWR_CTRLSTS_OFFSET * 32) + (PWR_WKUP1EN_BIT_NUM * 4))

/** PWR CTRL register bit mask definition **/
#define PWR_CTRL_LPSPDS_MASK ((uint32_t)0xFFFFFFFC)
#define PWR_CTRL_PLSMSB_MASK ((uint32_t)0xFFFFFD1F)

/** PWR wakup PIN polarity definition **/
#define PWR_PIN_RISING  ((uint32_t)0x00000000)
#define PWR_PIN_FALLING ((uint32_t)0x00000001)

/** PWR PVD output Flag definition **/
#define PWR_PVD_OUTPUT_FLAG ((uint32_t)PWR_CTRLSTS_PVDO)

/** PWR Standby Flag definition **/
#define PWR_STBY_FLAG ((uint32_t)PWR_CTRLSTS_STBYF)

/** PWR Clear Standby Flag definition **/
#define PWR_CLEAR_STBY_FLAG ((uint32_t)PWR_CTRL_CSTBYF)

/** PWR PA8/PA0/PC13/RTC wakeup Flag definition **/
#define PWR_WKUP_FLAG_PA8  ((uint32_t)PWR_CTRLSTS_WKUPF1)
#define PWR_WKUP_FLAG_PA0  ((uint32_t)PWR_CTRLSTS_WKUPF2)
#define PWR_WKUP_FLAG_PC13 ((uint32_t)PWR_CTRLSTS_WKUPF3)
#define PWR_WKUP_FLAG_RTC  ((uint32_t)PWR_CTRLSTS_WKUPRTCF)

/** PWR Clear PA8/PA0/PC13/RTC wakeup Flag definition **/
#define PWR_CLEAR_WKUPF_ALL  ((uint32_t)(PWR_CTRL_CLRWKUP1 \
                                      | PWR_CTRL_CLRWKUP2 \
                                      | PWR_CTRL_CLRWKUP3 \
                                      | PWR_CTRL_CLRRTCWKUP))
#define PWR_CLEAR_WKUPF_PA8  ((uint32_t)PWR_CTRL_CLRWKUP1)
#define PWR_CLEAR_WKUPF_PA0  ((uint32_t)PWR_CTRL_CLRWKUP2)
#define PWR_CLEAR_WKUPF_PC13 ((uint32_t)PWR_CTRL_CLRWKUP3)
#define PWR_CLEAR_WKUPF_RTC  ((uint32_t)PWR_CTRL_CLRRTCWKUP)

/** PWR wakup PIN definition **/
#define PWR_WKUPPA8_ENABLE  ((uint32_t)PWR_CTRLSTS_WKUP1EN)
#define PWR_WKUPPA0_ENABLE  ((uint32_t)PWR_CTRLSTS_WKUP2EN)
#define PWR_WKUPPC13_ENABLE ((uint32_t)PWR_CTRLSTS_WKUP3EN)
 
/** PWR PVD threshold level definition **/
#define PWR_PVD_LEVEL_2V18 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    & PWR_CTRL_PLS_1 \
                                    & PWR_CTRL_PLS_2))     /* 2.18v PWR_CTRL bit9:0; bit[7:5]:000*/
#define PWR_PVD_LEVEL_2V28 ((uint32_t)PWR_CTRL_PLS_0)      /* 2.28v PWR_CTRL bit9:0; bit[7:5]:001*/
#define PWR_PVD_LEVEL_2V38 ((uint32_t)PWR_CTRL_PLS_1)      /* 2.38v PWR_CTRL bit9:0; bit[7:5]:010*/
#define PWR_PVD_LEVEL_2V48 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_1))     /* 2.48v PWR_CTRL bit9:0; bit[7:5]:011*/
#define PWR_PVD_LEVEL_2V58 ((uint32_t)PWR_CTRL_PLS_2)      /* 2.58v PWR_CTRL bit9:0; bit[7:5]:100*/
#define PWR_PVD_LEVEL_2V68 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_2))     /* 2.68v PWR_CTRL bit9:0; bit[7:5]:101*/
#define PWR_PVD_LEVEL_2V78 ((uint32_t)(PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_2))     /* 2.78v PWR_CTRL bit9:0; bit[7:5]:110*/
#define PWR_PVD_LEVEL_2V88 ((uint32_t)(PWR_CTRL_PLS_0 \
                                    | PWR_CTRL_PLS_1 \
                                    | PWR_CTRL_PLS_2))     /* 2.88v PWR_CTRL bit9:0; bit[7:5]:111*/
#define PWR_PVD_LEVEL_1V78 ((uint32_t)(PWR_CTRL_MSB \
                                    | PWR_PVD_LEVEL_2V18)) /* 1.78v PWR_CTRL bit9:1; bit[7:5]:000*/
#define PWR_PVD_LEVEL_1V88 ((uint32_t)(PWR_CTRL_MSB \
                                    | PWR_PVD_LEVEL_2V28)) /* 1.88v PWR_CTRL bit9:1; bit[7:5]:001*/
#define PWR_PVD_LEVEL_1V98 ((uint32_t)(PWR_CTRL_MSB \
                                    | PWR_PVD_LEVEL_2V38)) /* 1.98v PWR_CTRL bit9:1; bit[7:5]:010*/
#define PWR_PVD_LEVEL_2V08 ((uint32_t)(PWR_CTRL_MSB \
                                    | PWR_PVD_LEVEL_2V48)) /* 2.08v PWR_CTRL bit9:1; bit[7:5]:011*/
#define PWR_PVD_LEVEL_3V28 ((uint32_t)(PWR_CTRL_MSB \
                                    | PWR_PVD_LEVEL_2V58)) /* 3.28v PWR_CTRL bit9:1; bit[7:5]:100*/
#define PWR_PVD_LEVEL_3V38 ((uint32_t)(PWR_CTRL_MSB \
                                    | PWR_PVD_LEVEL_2V68)) /* 3.38v PWR_CTRL bit9:1; bit[7:5]:101*/
#define PWR_PVD_LEVEL_3V48 ((uint32_t)(PWR_CTRL_MSB \
                                    | PWR_PVD_LEVEL_2V78)) /* 3.48v PWR_CTRL bit9:1; bit[7:5]:110*/
#define PWR_PVD_LEVEL_3V58 ((uint32_t)(PWR_CTRL_MSB \
                                    | PWR_PVD_LEVEL_2V88)) /* 3.58v PWR_CTRL bit9:1; bit[7:5]:111*/


/** PWR regulator status definition **/
#define PWR_REGULATOR_ON       ((uint32_t)0x00000000)   /* STOP mode with regulator ON */
#define PWR_REGULATOR_LOWPOWER ((uint32_t)PWR_CTRL_LPS) /* STOP mode with regulator in low power mode */

/** PWR STANDBY mode entry definition **/
#define PWR_STANDBY_ENTRY_WFI ((uint8_t)0x01) /* enter STANDBY mode with WFI instruction */
#define PWR_STANDBY_ENTRY_WFE ((uint8_t)0x02) /* enter STANDBY mode with WFE instruction */

/** PWR STOP0 mode entry definition **/
#define PWR_STOP0_ENTRY_WFI ((uint8_t)0x01) /* enter STOP0 mode with WFI instruction */
#define PWR_STOP0_ENTRY_WFE ((uint8_t)0x02) /* enter STOP0 mode with WFE instruction */

/** PWR STOP2 mode entry definition **/
#define PWR_STOP2_ENTRY_WFI ((uint8_t)0x01) /* enter STOP2 mode with WFI instruction */
#define PWR_STOP2_ENTRY_WFE ((uint8_t)0x02) /* enter STOP2 mode with WFE instruction */

/** PWR SLEEP mode entry definition **/
#define PWR_SLEEP_ENTRY_WFI ((uint8_t)0x01) /* enter SLEEP mode with WFI instruction */
#define PWR_SLEEP_ENTRY_WFE ((uint8_t)0x02) /* enter SLEEP mode with WFE instruction */

/** PWR STOP2 mode definition **/
#define PWR_STOP2_ENABLE ((uint32_t)PWR_CTRL2_STOP2S)

/** PWR bit shift number definition **/
#define PWR_BIT_SHIFT_2 ((uint32_t)REG_BIT2_OFFSET)
#define PWR_BIT_SHIFT_7 ((uint32_t)REG_BIT7_OFFSET)

/*** PWR Macro Definition End ***/

/*** PWR Driving Functions Declaration ***/

void PWR_Reset(void);
void PWR_RTC_Backup_Access_Enable(void);
void PWR_RTC_Backup_Access_Disable(void);
void PWR_PVD_Enable(void);
void PWR_PVD_Disable(void);
void PWR_PVD_Level_Config(uint32_t level);
void PWR_Wakeup_Pin_Enable(WAKEUP_PINX pin, uint32_t polarity);
void PWR_Wakeup_Pin_Disable(WAKEUP_PINX pin);
void PWR_RTC_Wakeup_Enable(void);
void PWR_RTC_Wakeup_Disable(void);
void PWR_SLEEP_Mode_Enter(PWR_SLEEPONEXIT_STATUS status, uint8_t enter_mode);
void PWR_STOP0_Mode_Enter(uint32_t status, uint8_t enter_mode);
void PWR_STOP2_Mode_Enter(uint8_t enter_mode);
void PWR_STANDBY_Mode_Enter(uint8_t enter_mode);
FlagStatus PWR_Flag_Status_Get(uint32_t flag);
void PWR_Flag_Status_Clear(uint32_t flag);


#ifdef __cplusplus
}
#endif

#endif /* __N32G430_PWR_H__ */

