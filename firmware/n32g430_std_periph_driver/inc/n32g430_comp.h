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
*\*\file n32g430_comp.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32G430_COMP_H__
#define __N32G430_COMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"
#include <stdbool.h>

/** Bit operation definition **/
#define SetBitMsk(reg, bit, msk) ((reg) = ((reg) & ~(msk) | (bit)))
#define ClrBit(reg, bit)         ((reg) &= ~(bit))
#define SetBit(reg, bit)         ((reg) |= (bit))
#define GetBit(reg, bit)         ((reg) & (bit))

/** COMPx enum definition **/
typedef enum
{
    COMP1 = 0,
    COMP2 = 1,
    COMP3 = 2,
} COMPX;

/** COMP init structure definition **/
typedef struct
{
    /* ctrl define */         
    uint32_t Blking;             /* Specifies which timer can control the comp output blanking with its capture event */
    uint32_t Hyst;               /* Specifies the comp hysteresis level with low/medium/high level */
    uint32_t PolRev;             /* Specifies the comp output polarity */
    uint32_t OutSel;             /* Specifies which timer input that can be connecte to the comp output */
    uint32_t InpSel;             /* Specifies the comp inpsel */
    uint32_t InmSel;             /* Specifies the comp inmsel */
    uint32_t En;                 /* enable or disable the comp */

    /* filter define */
    uint8_t SampWindow;          /* Initializes comp sampwindow value ~5bit */
    uint8_t Threshold;           /* ~5bit ,need > SampWindow/2 */
    uint8_t FilterEn;            /* enable or disable the comp filter */

    /* filter prescale */
    uint16_t ClkPsc;             /* Initializes comp clkpsc value ~5bit */
} COMP_InitType;

/** COMPx blanking definition **/
#define COMP_BLANKING_MASK                ((uint32_t)(~COMP1_CTRL_BLKING))
#define COMP_BLANKING_NO                  ((uint32_t)0x00000000)
#define COMP_BLANKING_TIM1_OC5            ((uint32_t)COMP1_CTRL_BLKING_0)
#define COMP_BLANKING_TIM8_OC5            ((uint32_t)COMP1_CTRL_BLKING_1)

/** COMPx hysteresis definition **/
#define COMP_HYST_MASK                    ((uint32_t)(~COMP1_CTRL_HYST))
#define COMP_HYST_NO                      ((uint32_t)0x00000000)
#define COMP_HYST_LOW                     ((uint32_t)COMP1_CTRL_HYST_0)
#define COMP_HYST_MID                     ((uint32_t)COMP1_CTRL_HYST_1)
#define COMP_HYST_HIGH                    ((uint32_t)(COMP1_CTRL_HYST_0 | COMP1_CTRL_HYST_1))

/** COMPx output polarity definition **/
#define COMP_OUTPOL_MASK                  ((uint32_t)(~COMP1_CTRL_POL))
#define COMP_OUTPOL_FLIP                  ((uint32_t)COMP1_CTRL_POL)
#define COMP_OUTPOL_NFLIP                 ((uint32_t)0x00000000)
 
/** COMPx inverting input definition **/
#define COMP_INPSEL_MASK                  ((uint32_t)(~COMP1_CTRL_INPSEL))
#define COMP_INPSEL_RES                   ((uint32_t)0x00000000)
/** comp1 inp sel **/  
#define COMP1_INPSEL_PA0                  ((uint32_t)0x00000000)
#define COMP1_INPSEL_PA2                  ((uint32_t)0x00000020)
#define COMP1_INPSEL_PA12                 ((uint32_t)0x00000040)
#define COMP1_INPSEL_PB3                  ((uint32_t)0x00000060)
#define COMP1_INPSEL_PB4                  ((uint32_t)0x00000080)
#define COMP1_INPSEL_PB10                 ((uint32_t)0x000000A0)
#define COMP1_INPSEL_PA1                  ((uint32_t)0x000000C0)
#define COMP1_INPSEL_FLOAT                ((uint32_t)0x000000E0)
/** comp2 inp sel **/
#define COMP2_INPSEL_PA1                  ((uint32_t)0x00000000) /* Window mode connection */  
#define COMP2_INPSEL_PA3                  ((uint32_t)0x00000020)
#define COMP2_INPSEL_PA6                  ((uint32_t)0x00000040)
#define COMP2_INPSEL_PA7                  ((uint32_t)0x00000060)
#define COMP2_INPSEL_PA11                 ((uint32_t)0x00000080)
#define COMP2_INPSEL_PA15                 ((uint32_t)0x000000A0)
#define COMP2_INPSEL_PB7                  ((uint32_t)0x000000C0)
#define COMP2_INPSEL_FLOAT                ((uint32_t)0x000000E0)
/** comp3 inp sel **/
#define COMP3_INPSEL_PA0                  ((uint32_t)0x00000000)
#define COMP3_INPSEL_PB1                  ((uint32_t)0x00000020)
#define COMP3_INPSEL_PB11                 ((uint32_t)0x00000040)
#define COMP3_INPSEL_PB15                 ((uint32_t)0x00000060)
#define COMP3_INPSEL_PB3                  ((uint32_t)0x00000080)
#define COMP3_INPSEL_PB5                  ((uint32_t)0x000000A0)
#define COMP3_INPSEL_FLOAT1               ((uint32_t)0x000000C0)
#define COMP3_INPSEL_FLOAT2               ((uint32_t)0x000000E0)

/** COMPx non inverting input definition **/
#define COMP_INMSEL_MASK                  ((uint32_t)(~COMP1_CTRL_INMSEL))
#define COMP_INMSEL_RES                   ((uint32_t)0x00000000)
/** comp1 inm sel **/
#define COMP1_INMSEL_VREF_VC1             ((uint32_t)0x00000000)
#define COMP1_INMSEL_PA4                  ((uint32_t)0x00000002)
#define COMP1_INMSEL_PA0                  ((uint32_t)0x00000004)
#define COMP1_INMSEL_PA5                  ((uint32_t)0x00000006)
#define COMP1_INMSEL_PB5                  ((uint32_t)0x00000008)
#define COMP1_INMSEL_FLOAT                ((uint32_t)0x0000000A)
#define COMP1_INMSEL_FLOAT1               ((uint32_t)0x0000000C)
#define COMP1_INMSEL_FLOAT2               ((uint32_t)0x0000000E)
/** comp2 inm sel **/
#define COMP2_INMSEL_VREF_VC2             ((uint32_t)0x00000000)
#define COMP2_INMSEL_PA2                  ((uint32_t)0x00000002)
#define COMP2_INMSEL_PA5                  ((uint32_t)0x00000004)
#define COMP2_INMSEL_PA6                  ((uint32_t)0x00000006)
#define COMP2_INMSEL_PB3                  ((uint32_t)0x00000008)
#define COMP2_INMSEL_PA4                  ((uint32_t)0x0000000A)
#define COMP2_INMSEL_FLOAT1               ((uint32_t)0x0000000C)
#define COMP2_INMSEL_FLOAT2               ((uint32_t)0x0000000E)
/** comp3 inm sel **/
#define COMP3_INMSEL_VREF_VC3             ((uint32_t)0x00000000)
#define COMP3_INMSEL_PA3                  ((uint32_t)0x00000002)
#define COMP3_INMSEL_PB0                  ((uint32_t)0x00000004)
#define COMP3_INMSEL_PB2                  ((uint32_t)0x00000006)
#define COMP3_INMSEL_PB14                 ((uint32_t)0x00000008)
#define COMP3_INMSEL_FLOAT                ((uint32_t)0x0000000A)
#define COMP3_INMSEL_FLOAT1               ((uint32_t)0x0000000C)
#define COMP3_INMSEL_FLOAT2               ((uint32_t)0x0000000E)

/** COMPx output connection definition **/
#define COMP_OUTSEL_MASK                  ((uint32_t)(~COMP1_CTRL_OUTTRG))
#define COMP_OUTSEL_RES                   ((uint32_t)0x00000000)
/** comp1 out trig **/
#define COMP1_OUTSEL_TIM1_BKIN            ((uint32_t)0x00000200)
#define COMP1_OUTSEL_TIM1_OCREFCLEAR      ((uint32_t)0x00000400)
#define COMP1_OUTSEL_TIM1_IC1             ((uint32_t)0x00000600)
#define COMP1_OUTSEL_TIM2_IC1             ((uint32_t)0x00000800)
#define COMP1_OUTSEL_TIM2_OCREFCLEAR      ((uint32_t)0x00000A00)
#define COMP1_OUTSEL_TIM3_IC1             ((uint32_t)0x00000C00)
#define COMP1_OUTSEL_TIM3_OCREFCLEAR      ((uint32_t)0x00000E00)
#define COMP1_OUTSEL_TIM4_OCREFCLEAR      ((uint32_t)0x00001000)
#define COMP1_OUTSEL_TIM5_IC1             ((uint32_t)0x00001200)
#define COMP1_OUTSEL_TIM8_IC1             ((uint32_t)0x00001400)
#define COMP1_OUTSEL_TIM8_OCREFCLEAR      ((uint32_t)0x00001600)
#define COMP1_OUTSEL_TIM8_BKIN            ((uint32_t)0x00001A00)
#define COMP1_OUTSEL_TIM1_BKIN_TIM8_BKIN  ((uint32_t)0x00001C00)
#define COMP1_OUTSEL_LPTIM_ETR            ((uint32_t)0x00001E00)
/** comp2 out trig **/
#define COMP2_OUTSEL_TIM1_BKIN            ((uint32_t)0x00000200)
#define COMP2_OUTSEL_TIM1_OCREFCLEAR      ((uint32_t)0x00000400)
#define COMP2_OUTSEL_TIM1_IC1             ((uint32_t)0x00000600)
#define COMP2_OUTSEL_TIM2_OCREFCLEAR      ((uint32_t)0x00000800)
#define COMP2_OUTSEL_TIM3_OCREFCLEAR      ((uint32_t)0x00000A00)
#define COMP2_OUTSEL_TIM4_IC1             ((uint32_t)0x00000C00)
#define COMP2_OUTSEL_TIM4_OCREFCLEAR      ((uint32_t)0x00000E00)
#define COMP2_OUTSEL_TIM5_IC1             ((uint32_t)0x00001000)
#define COMP2_OUTSEL_TIM8_IC1             ((uint32_t)0x00001200)
#define COMP2_OUTSEL_TIM8_OCREFCLEAR      ((uint32_t)0x00001400)
#define COMP2_OUTSEL_TIM8_BKIN            ((uint32_t)0x00001A00)
#define COMP2_OUTSEL_TIM1_BKIN_TIM8_BKIN  ((uint32_t)0x00001C00)
#define COMP2_OUTSEL_LPTIM_ETR            ((uint32_t)0x00001E00)
/** comp3 out trig **/
#define COMP3_OUTSEL_TIM1_BKIN            ((uint32_t)0x00000200)
#define COMP3_OUTSEL_TIM1_OCREFCLEAR      ((uint32_t)0x00000400)
#define COMP3_OUTSEL_TIM1_IC1             ((uint32_t)0x00000600)
#define COMP3_OUTSEL_TIM2_IC1             ((uint32_t)0x00000800)
#define COMP3_OUTSEL_TIM5_OCREFCLEAR      ((uint32_t)0x00000A00)
#define COMP3_OUTSEL_TIM3_IC1             ((uint32_t)0x00000C00)
#define COMP3_OUTSEL_TIM3_OCREFCLEAR      ((uint32_t)0x00000E00)
#define COMP3_OUTSEL_TIM4_OCREFCLEAR      ((uint32_t)0x00001000)
#define COMP3_OUTSEL_TIM5_IC1             ((uint32_t)0x00001200)
#define COMP3_OUTSEL_TIM8_IC1             ((uint32_t)0x00001600)
#define COMP3_OUTSEL_TIM8_OCREFCLEAR      ((uint32_t)0x00001800)
#define COMP3_OUTSEL_TIM8_BKIN            ((uint32_t)0x00001A00)
#define COMP3_OUTSEL_TIM1_BKIN_TIM8_BKIN  ((uint32_t)0x00001C00)
#define COMP3_OUTSEL_LPTIM_ETR            ((uint32_t)0x00001E00)

/** COMPx switch definition **/
#define COMP_ENABLE                       ((uint32_t)COMP1_CTRL_EN)
#define COMP_DISABLE                      ((uint32_t)(~COMP1_CTRL_EN))

/** COMP window mode definition **/
#define COMP_CMP12MD_ENABLE               ((uint16_t)COMP_WINMODE) /* 1: Comparators 1 and 2 can be used in window mode. */
#define COMP_CMP12MD_DISABLE              ((uint16_t)0x0000)

/** COMP output xor definition **/
#define COMP_CMP2XO_ENABLE                ((uint16_t)COMP2_OSEL_CMP2XO) /* 1: XOR(comparison) output between results of COMP1 and COMP2. */
#define COMP_CMP2XO_DISABLE               ((uint16_t)0x0000)

/** COMPx filter definition **/
#define COMP_FILTER_SAMPW_MASK            ((uint16_t)(~COMP1_FILC_SAMPW)) /* Low filter sample window size. Number of samples to monitor is SAMPWIN+1. */
#define COMP_FILTER_THRESHOLD_MASK        ((uint16_t)(~COMP1_FILC_THRESH)) /* For proper operation, the value of THRESHOLD must be greater than SAMPWIN / 2. */

#define COMP_FILTER_ENBALE                ((uint16_t)COMP1_FILC_FILEN) /* Filter enable. */
#define COMP_FILTER_DISABLE               ((uint16_t)(~COMP1_FILC_FILEN)) /* Filter disable. */ 

/** COMPx filter prescale definition **/
#define COMP_FILTER_CLKPSC_MASK           ((uint16_t)(~COMP1_FILP_CLKPSC)) /* Low filter sample clock prescale.Number of system clocks between samples = CLK_PRE_CYCLE + 1, e.g. */

/** COMPx lock definition**/
#define COMP_LOCK_MSK                     ((uint16_t)(~COMP_LOCK))     
#define COMP1_LOCK_MSK                    ((uint16_t)COMP_LOCK_CMP1LK) /* COMx Lock bit */
#define COMP2_LOCK_MSK                    ((uint16_t)COMP_LOCK_CMP2LK) 
#define COMP3_LOCK_MSK                    ((uint16_t)COMP_LOCK_CMP3LK)

/** COMPx LPCKSEL definition**/   
#define COMP_LPCKSEL_MSK                    ((uint16_t)(~COMP_LPCKSEL))  
#define COMP_NORMAL_MODE                    ((uint16_t)0x0000)				 /* COMP LPCKSEL bit */
#define COMP_LOWPOWER_MODE 					((uint16_t)COMP_LPCKSEL)


/** COMP interrupt enable definition **/
#define COMP_INTEN_MSK                    ((uint16_t)(~COMP_INTEN))      
#define COMP1_INTEN                       ((uint16_t)COMP_INTEN_CMP1IEN) /* This bit control Interrput enable of COMP. */
#define COMP2_INTEN                       ((uint16_t)COMP_INTEN_CMP2IEN)       
#define COMP3_INTEN                       ((uint16_t)COMP_INTEN_CMP3IEN)       

/** COMP interrupt status definition **/
#define COMP_INTSTS_MSK                   ((uint16_t)(~COMP_INTSTS))  
#define COMP1_INTSTS                      ((uint16_t)COMP_INTSTS_COMP1IS) /* This bit control Interrput enable of COMP. */
#define COMP2_INTSTS                      ((uint16_t)COMP_INTSTS_COMP2IS)     
#define COMP3_INTSTS                      ((uint16_t)COMP_INTSTS_COMP3IS)        

/** COMP voltage reference definition **/
#define COMP_VREFSCL_VV3TRM_MSK           ((uint32_t)(COMP_VREFSCL_VV3TRM)) /* Vref3 Voltage scaler triming value. */
#define COMP_VREFSCL_VV3EN_MSK            ((uint32_t)(COMP_VREFSCL_VV3EN))
#define COMP_VREFSCL_VV2TRM_MSK           ((uint32_t)(COMP_VREFSCL_VV2TRM)) /* Vref2 Voltage scaler triming value. */
#define COMP_VREFSCL_VV2EN_MSK            ((uint32_t)(COMP_VREFSCL_VV2EN))
#define COMP_VREFSCL_VV1TRM_MSK           ((uint32_t)(COMP_VREFSCL_VV1TRM)) /* Vref1 Voltage scaler triming value. */
#define COMP_VREFSCL_VV1EN_MSK            ((uint32_t)(COMP_VREFSCL_VV1EN))

/** COMPx output status definition**/
#define COMP_OUT_MASK                     ((uint32_t)COMP1_CTRL_OUT) 


/** ADC Driving Functions Declaration **/
void COMP_Reset(void);

void COMP_Filter_SampWindow_Config(COMPX COMPx, uint8_t sampwin_value);
void COMP_Filter_Threshold_Config(COMPX COMPx, uint8_t threshold_value);
void COMP_Filter_Enable(COMPX COMPx);
void COMP_Filter_Disable(COMPX COMPx);
void COMP_Filter_Clock_Prescale_Config(COMPX COMPx, uint16_t clkpsc_value);
void COMP_Blking_Soucre_Config(COMPX COMPx, uint32_t blking_mode);
void COMP_Hysteresis_Level_Config(COMPX COMPx, uint32_t hyst_mode);
void COMP_Output_Polarity_Config(COMPX COMPx, uint32_t output_pol);
void COMP_InpSel_Config(COMPX COMPx, uint32_t vpsel);
void COMP_InmSel_Config(COMPX COMPx, uint32_t vmsel);
void COMP_Output_Trigger_Config(COMPX COMPx, uint32_t outtrgsel);

void COMP_ON(COMPX COMPx);
void COMP_OFF(COMPX COMPx);

void COMP_Lock_Config(uint32_t Lock);
void COMP_LowPower_Clock_Select(uint32_t lpcksel);
void COMP_Interrupt_Enable(uint32_t IntEn);
void COMP_Interrupt_Disable(uint32_t IntEn);
uint8_t COMP_Interrupt_Status_Get(void);

void COMP_Voltage_Reference_Config(uint8_t vv3trim, bool vv3en,uint8_t vv2trim, bool vv2en, uint8_t vv1trim, bool vv1en);

void COMP_Window_Mode_Enable(void);
void COMP_Window_Mode_Disable(void);
void COMP2_Output_Xor_Enable(void);
void COMP2_Output_Xor_Disable(void);

FlagStatus COMP_Output_Status_Get(COMPX COMPx);

FlagStatus COMP_Interrupt_Status_OneComp_Get(COMPX COMPx);
void COMP_Interrupt_Status_OneComp_Clear(COMPX COMPx);

void COMP_Filter_Control_Config(COMPX COMPx , uint32_t sw, uint8_t threshnum , uint8_t sampwindow);

void COMP_Initializes_Structure(COMP_InitType* COMP_initstruct);
void COMP_Initializes(COMPX COMPx, COMP_InitType* COMP_initstruct);

#ifdef __cplusplus
}
#endif

#endif /*__N32G430_COMP_H */

