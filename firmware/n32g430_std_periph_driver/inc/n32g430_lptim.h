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
*\*\file      n32g430_lptim.h
*\*\author    Nations
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved. 
**/
#ifndef __N32G430_LPTIM_H
#define __N32G430_LPTIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

/** n32g430_StdPeriph_Driver **/

//#if defined (LPTIM)

/** LPTIM Init structure definition **/
typedef struct
{
  uint32_t ClockSource;    /* Specifies the source of the clock used by the LPTIM instance.
                              This parameter can be a value of @ref LPTIM_EC_CLK_SOURCE.

                              This feature can be modified afterwards using unitary function @ref LPTIM_SetClockSource().*/

  uint32_t Prescaler;      /* Specifies the prescaler division ratio.
                              This parameter can be a value of @ref LPTIM_EC_PRESCALER.

                              This feature can be modified afterwards using using unitary function @ref LPTIM_SetPrescaler().*/

  uint32_t Waveform;       /* Specifies the waveform shape.
                              This parameter can be a value of @ref LPTIM_EC_OUTPUT_WAVEFORM.

                                This feature can be modified afterwards using unitary function @ref LPTIM_ConfigOutput().*/

  uint32_t Polarity;       /* Specifies waveform polarity.
                              This parameter can be a value of @ref LPTIM_EC_OUTPUT_POLARITY.

                              This feature can be modified afterwards using unitary function @ref LPTIM_ConfigOutput().*/
} LPTIM_InitType;



/* Exported constants */

/** LPTIM_Exported_Constants LPTIM Exported Constants **/

/** LPTIM_FLAG_Clear  Defines **/
#define LPTIM_CLEAR_FLAG_CMPM             LPTIM_INTCLR_CMPMCF    /* Compare match */
#define LPTIM_CLEAR_FLAG_ARRM             LPTIM_INTCLR_ARRMCF    /* Autoreload match */
#define LPTIM_CLEAR_FLAG_EXTRIG           LPTIM_INTCLR_EXTRIGCF  /* External trigger edge event */
#define LPTIM_CLEAR_FLAG_CMPUPD           LPTIM_INTCLR_CMPUPDCF  /* Compare register update OK */
#define LPTIM_CLEAR_FLAG_ARRUPD           LPTIM_INTCLR_ARRUPDCF  /* Autoreload register update OK */
#define LPTIM_CLEAR_FLAG_UP               LPTIM_INTCLR_UPCF      /* Counter direction change down to up */
#define LPTIM_CLEAR_FLAG_DOWN             LPTIM_INTCLR_DOWNCF    /* Counter direction change up to down */


/** LPTIM_Flag_Get Get Flags Defines **/
#define LPTIM_INTSTS_FLAG_CMPM            LPTIM_INTSTS_CMPM      /* Compare match */
#define LPTIM_INTSTS_FLAG_ARRM            LPTIM_INTSTS_ARRM      /* Autoreload match */
#define LPTIM_INTSTS_FLAG_EXTRIG          LPTIM_INTSTS_EXTRIG    /* External trigger edge event */
#define LPTIM_INTSTS_FLAG_CMPUPD          LPTIM_INTSTS_CMPUPD    /* Compare register update OK */
#define LPTIM_INTSTS_FLAG_ARRUPD          LPTIM_INTSTS_ARRUPD    /* Autoreload register update OK */
#define LPTIM_INTSTS_FLAG_UP              LPTIM_INTSTS_UP        /* Counter direction change down to up */
#define LPTIM_INTSTS_FLAG_DOWN            LPTIM_INTSTS_DOWN      /* Counter direction change up to down */

/** Interrupt Defines **/
#define LPTIM_INT_CMPMIE                  LPTIM_INTEN_CMPMIE     /* Compare match Interrupt Enable */
#define LPTIM_INT_ARRMIE                  LPTIM_INTEN_ARRMIE     /* Autoreload match Interrupt Enable */
#define LPTIM_INT_EXTRIGIE                LPTIM_INTEN_EXTRIGIE   /* External trigger valid edge Interrupt Enable */
#define LPTIM_INT_CMPUPDIE                LPTIM_INTEN_CMPUPDIE   /* Compare register update OK Interrupt Enable */
#define LPTIM_INT_ARRUPDIE                LPTIM_INTEN_ARRUPDIE   /* Autoreload register update OK Interrupt Enable */
#define LPTIM_INT_UPIE                    LPTIM_INTEN_UPIE       /* Direction change to UP Interrupt Enable */
#define LPTIM_INT_DOWNIE                  LPTIM_INTEN_DOWNIE     /* Direction change to down Interrupt Enable */


/** LPTIM_EC_OPERATING_MODE Operating Mode **/
#define LPTIM_OPERATING_MODE_CONTINUOUS    LPTIM_CTRL_TSTCM  /* LP Timer starts in continuous mode*/
#define LPTIM_OPERATING_MODE_ONESHOT       LPTIM_CTRL_SNGMST /* LP Tilmer starts in single mode*/


/** LPTIM_EC_UPDATE_MODE Update Mode **/
#define LPTIM_UPDATE_MODE_IMMEDIATE        0x00000000U        /* Preload is disabled: registers are updated after each APB bus write access*/
#define LPTIM_UPDATE_MODE_ENDOFPERIOD      LPTIM_CFG_RELOAD   /* preload is enabled: registers are updated at the end of the current LPTIM period*/


/** LPTIM_EC_COUNTER_MODE Counter Mode **/
#define LPTIM_COUNTER_MODE_INTERNAL        0x00000000U          /* The counter is incremented following each internal clock pulse*/
#define LPTIM_COUNTER_MODE_EXTERNAL        LPTIM_CFG_CNTMEN     /* The counter is incremented following each valid clock pulse on the LPTIM external Input1*/


/** LPTIM_EC_OUTPUT_WAVEFORM Output Waveform Type **/
#define LPTIM_OUTPUT_WAVEFORM_PWM          0x00000000U     /* LPTIM generates either a PWM waveform or a One pulse waveform depending on chosen operating mode CONTINOUS or SINGLE*/
#define LPTIM_OUTPUT_WAVEFORM_SETONCE      LPTIM_CFG_WAVE  /* LPTIM generates a Set Once waveform*/


/** LPTIM_EC_OUTPUT_POLARITY Output Polarity **/
#define LPTIM_OUTPUT_POLARITY_REGULAR      0x00000000U         /* The LPTIM output reflects the compare results between LPTIMx_ARR and LPTIMx_CMP registers*/
#define LPTIM_OUTPUT_POLARITY_INVERSE      LPTIM_CFG_WAVEPOL   /* The LPTIM output reflects the inverse of the compare results between LPTIMx_ARR and LPTIMx_CMP registers*/


/** LPTIM_EC_PRESCALER Prescaler Value **/
#define LPTIM_PRESCALER_DIV1               0x00000000U                               /* Prescaler division factor is set to 1*/
#define LPTIM_PRESCALER_DIV2               LPTIM_CFG_CLKPRE_0                        /* Prescaler division factor is set to 2*/
#define LPTIM_PRESCALER_DIV4               LPTIM_CFG_CLKPRE_1                        /* Prescaler division factor is set to 4*/
#define LPTIM_PRESCALER_DIV8               (LPTIM_CFG_CLKPRE_1 | LPTIM_CFG_CLKPRE_0) /* Prescaler division factor is set to 8*/
#define LPTIM_PRESCALER_DIV16              LPTIM_CFG_CLKPRE_2                        /* Prescaler division factor is set to 16*/
#define LPTIM_PRESCALER_DIV32              (LPTIM_CFG_CLKPRE_2 | LPTIM_CFG_CLKPRE_0) /* Prescaler division factor is set to 32*/
#define LPTIM_PRESCALER_DIV64              (LPTIM_CFG_CLKPRE_2 | LPTIM_CFG_CLKPRE_1) /* Prescaler division factor is set to 64*/
#define LPTIM_PRESCALER_DIV128             LPTIM_CFG_CLKPRE                          /* Prescaler division factor is set to 128*/


/** LPTIM_EC_TRIG_SOURCE Trigger Source **/

#define LPTIM_TRIG_SOURCE_GPIO             0x00000000U                                                    /* External input trigger is connected to TIMx_ETR input*/
#define LPTIM_TRIG_SOURCE_RTCALARMA        LPTIM_CFG_TRGSEL_0                                             /* External input trigger is connected to RTC Alarm A*/
#define LPTIM_TRIG_SOURCE_RTCALARMB        LPTIM_CFG_TRGSEL_1                                             /* External input trigger is connected to RTC Alarm B*/
#define LPTIM_TRIG_SOURCE_RTCTAMP1         (LPTIM_CFG_TRGSEL_1 | LPTIM_CFG_TRGSEL_0)                      /* External input trigger is connected to RTC Tamper 1*/
#define LPTIM_TRIG_SOURCE_RTCTAMP2         LPTIM_CFG_TRGSEL_2                                             /* External input trigger is connected to RTC Tamper 2*/
#define LPTIM_TRIG_SOURCE_RTCTAMP3         (LPTIM_CFG_TRGSEL_2 | LPTIM_CFG_TRGSEL_0)                      /* External input trigger is connected to RTC Tamper 3*/
#define LPTIM_TRIG_SOURCE_COMP1            (LPTIM_CFG_TRGSEL_2 | LPTIM_CFG_TRGSEL_1)                      /* External input trigger is connected to COMP1 output*/
#define LPTIM_TRIG_SOURCE_COMP2            (LPTIM_CFG_TRGSEL_2 | LPTIM_CFG_TRGSEL_1 | LPTIM_CFG_TRGSEL_0) /* External input trigger is connected to COMP2 output*/
#define LPTIM_TRIG_SOURCE_COMP3            LPTIM_CFG_TRGSEL_3                                             /* External input trigger is connected to COMP3 output*/

/** LPTIM_EC_TRIG_FILTER Trigger Filter **/
#define LPTIM_TRIG_FILTER_NONE             0x00000000U         /* Any trigger active level change is considered as a valid trigger*/
#define LPTIM_TRIG_FILTER_2                LPTIM_CFG_TRIGFLT_0 /* Trigger active level change must be stable for at least 2 clock periods before it is considered as valid trigger*/
#define LPTIM_TRIG_FILTER_4                LPTIM_CFG_TRIGFLT_1 /* Trigger active level change must be stable for at least 4 clock periods before it is considered as valid trigger*/
#define LPTIM_TRIG_FILTER_8                LPTIM_CFG_TRIGFLT   /* Trigger active level change must be stable for at least 8 clock periods before it is considered as valid trigger*/


/** LPTIM_EC_TRIG_POLARITY Trigger Polarity **/
#define LPTIM_TRIG_POLARITY_FALLING        LPTIM_CFG_TRGEN_0 /* LPTIM counter starts when a falling edge is detected*/
#define LPTIM_TRIG_POLARITY_RISING         LPTIM_CFG_TRGEN_1 /* LPTIM counter starts when a rising edge is detected*/
#define LPTIM_TRIG_POLARITY_RISING_FALLING LPTIM_CFG_TRGEN   /* LPTIM counter starts when a rising or a falling edge is detected*/


/** LPTIM_EC_CLK_SOURCE Clock Source **/
#define LPTIM_CLK_SOURCE_INTERNAL          0x00000000U      /* LPTIM is clocked by internal clock source (APB clock or any of the embedded oscillators)*/
#define LPTIM_CLK_SOURCE_EXTERNAL          LPTIM_CFG_CLKSEL /* LPTIM is clocked by an external clock source through the LPTIM external Input1*/


/** LPTIM_EC_CLK_FILTER Clock Filter **/
#define LPTIM_CLK_FILTER_NONE              0x00000000U        /* Any external clock signal level change is considered as a valid transition*/
#define LPTIM_CLK_FILTER_2                 LPTIM_CFG_CLKFLT_0 /* External clock signal level change must be stable for at least 2 clock periods before it is considered as valid transition*/
#define LPTIM_CLK_FILTER_4                 LPTIM_CFG_CLKFLT_1 /* External clock signal level change must be stable for at least 4 clock periods before it is considered as valid transition*/
#define LPTIM_CLK_FILTER_8                 LPTIM_CFG_CLKFLT   /* External clock signal level change must be stable for at least 8 clock periods before it is considered as valid transition*/


/** LPTIM_EC_CLK_POLARITY Clock Polarity **/
#define LPTIM_CLK_POLARITY_RISING          0x00000000U        /* The rising edge is the active edge used for counting*/
#define LPTIM_CLK_POLARITY_FALLING         LPTIM_CFG_CLKPOL_0 /* The falling edge is the active edge used for counting*/
#define LPTIM_CLK_POLARITY_RISING_FALLING  LPTIM_CFG_CLKPOL_1 /* Both edges are active edges*/


/** LPTIM_EC_ENCODER_MODE Encoder Mode **/
#define LPTIM_ENCODER_MODE_RISING          0x00000000U        /* The rising edge is the active edge used for counting*/
#define LPTIM_ENCODER_MODE_FALLING         LPTIM_CFG_CLKPOL_0 /* The falling edge is the active edge used for counting*/
#define LPTIM_ENCODER_MODE_RISING_FALLING  LPTIM_CFG_CLKPOL_1 /* Both edges are active edges*/

/** LPTIM_INPUT1_OPTION option the input1 is connected**/
#define LPTIM_INTPUT1_MASK                  (~LPTIM_OPT_OPT1)
#define LPTIM_INTPUT1_CONNECT_TO_GPIO        0x00000000U 
#define LPTIM_INTPUT1_CONNECT_TO_COMP1_OUT  (LPTIM_OPT_OPT1_0)
#define LPTIM_INTPUT1_CONNECT_TO_COMP2_OUT  (LPTIM_OPT_OPT1_1)
#define LPTIM_INTPUT1_CONNECT_TO_COMP3_OUT  (LPTIM_OPT_OPT1_0 |LPTIM_OPT_OPT1_1)

/** LPTIM_INPUT2_OPTION option the input2 is connected**/
#define LPTIM_INTPUT2_MASK                  (~LPTIM_OPT_OPT2)
#define LPTIM_INTPUT2_CONNECT_TO_GPIO        0x00000000U
#define LPTIM_INTPUT2_CONNECT_TO_COMP1_OUT  (LPTIM_OPT_OPT2_0)
#define LPTIM_INTPUT2_CONNECT_TO_COMP2_OUT  (LPTIM_OPT_OPT2_1)
#define LPTIM_INTPUT2_CONNECT_TO_COMP3_OUT  (LPTIM_OPT_OPT2_0 |LPTIM_OPT_OPT2_1)

/* Exported functions --------------------------------------------------------*/

void LPTIM_Reset(LPTIM_Module *LPTIMx);
void LPTIM_OFF(LPTIM_Module *LPTIMx);
void LPTIM_ON(LPTIM_Module *LPTIMx);


void LPTIM_Initializes_Structure(LPTIM_InitType* LPTIM_InitStruct);
ErrorStatus LPTIM_Initializes(LPTIM_Module *LPTIMx, LPTIM_InitType* LPTIM_InitStruct);

void LPTIM_Counter_Start(LPTIM_Module *LPTIMx, uint32_t OperatingMode);
void LPTIM_Update_Mode_Set(LPTIM_Module *LPTIMx, uint32_t UpdateMode);
uint32_t LPTIM_Update_Mode_Get(LPTIM_Module *LPTIMx);
void LPTIM_Auto_Reload_Set(LPTIM_Module *LPTIMx, uint16_t AutoReload);
uint16_t LPTIM_Auto_Reload_Get(LPTIM_Module *LPTIMx);
void LPTIM_Compare_Set(LPTIM_Module *LPTIMx, uint16_t CompareValue);
uint16_t LPTIM_Compare_Get(LPTIM_Module *LPTIMx);
uint16_t LPTIM_Counter_Get(LPTIM_Module *LPTIMx);
void LPTIM_Counter_Mode_Set(LPTIM_Module *LPTIMx, uint32_t CounterMode);
uint32_t LPTIM_Counter_Mode_Get(LPTIM_Module *LPTIMx);
void LPTIM_Output_Config(LPTIM_Module *LPTIMx, uint32_t Waveform, uint32_t Polarity);
void LPTIM_Waveform_Set(LPTIM_Module *LPTIMx, uint32_t Waveform);
uint32_t LPTIM_Waveform_Get(LPTIM_Module *LPTIMx);
void LPTIM_Polarity_Set(LPTIM_Module *LPTIMx, uint32_t Polarity);
uint32_t LPTIM_Polarity_Get(LPTIM_Module *LPTIMx);
void LPTIM_Prescaler_Set(LPTIM_Module *LPTIMx, uint32_t Prescaler);
uint32_t LPTIM_Prescaler_Get(LPTIM_Module *LPTIMx);
void LPTIM_Timeout_Enable(LPTIM_Module *LPTIMx);
void LPTIM_Timeout_Disable(LPTIM_Module *LPTIMx);
FunctionalState LPTIM_Timeout_Get(LPTIM_Module *LPTIMx);
void LPTIM_Software_Trigger(LPTIM_Module *LPTIMx);

void LPTIM_Trigger_Config(LPTIM_Module *LPTIMx, uint32_t Source, uint32_t Filter, uint32_t Polarity);
uint32_t LPTIM_Trigger_Source_Get(LPTIM_Module *LPTIMx);
uint32_t LPTIM_Trigger_Filter_Get(LPTIM_Module *LPTIMx);
uint32_t LPTIM_Trigger_Polarity_Get(LPTIM_Module *LPTIMx);

void LPTIM_Clock_Source_Set(LPTIM_Module *LPTIMx, uint32_t ClockSource);
uint32_t LPTIM_Clock_Source_Get(LPTIM_Module *LPTIMx);

void LPTIM_Clock_Config(LPTIM_Module *LPTIMx, uint32_t ClockFilter, uint32_t ClockPolarity);
uint32_t LPTIM_Clock_Polarity_Get(LPTIM_Module *LPTIMx);
uint32_t LPTIM_Clock_Filter_Get(LPTIM_Module *LPTIMx);

void LPTIM_Encoder_Mode_Set(LPTIM_Module *LPTIMx, uint32_t EncoderMode);
FunctionalState LPTIM_Encoder_Mode_Check(LPTIM_Module *LPTIMx);
void LPTIM_Encoder_Mode_Enable(LPTIM_Module *LPTIMx);
void LPTIM_Encoder_Mode_Disable(LPTIM_Module *LPTIMx);
void LPTIM_NoEncoder_Mode_Enable(LPTIM_Module *LPTIMx);
void LPTIM_NoEncoder_Mode_Disable(LPTIM_Module *LPTIMx);

void LPTIM_Input1_Option(LPTIM_Module *LPTIMx, uint32_t option);
void LPTIM_Input2_Option(LPTIM_Module *LPTIMx, uint32_t option);

void LPTIM_FLAG_Clear(LPTIM_Module *LPTIMx, uint32_t LPTIM_flag_clear);
FlagStatus LPTIM_Flag_Get(LPTIM_Module *LPTIMx, uint32_t LPTIM_flag);
void LPTIM_Interrupt_Enable(LPTIM_Module *LPTIMx, uint32_t LPTIM_interrupt_flag);
void LPTIM_Interrupt_Disable(LPTIM_Module *LPTIMx, uint32_t LPTIM_interrupt_flag);
INTStatus LPTIM_Interrupt_Check(LPTIM_Module *LPTIMx, uint32_t LPTIM_interrupt_flag);



#ifdef __cplusplus
}
#endif

#endif /* __N32G430_LPTIM_H */


