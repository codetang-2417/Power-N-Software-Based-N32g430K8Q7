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
*\*\file n32g430_rtc.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32G430_RTC_H__
#define __N32G430_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

/** RTC Init structure definition **/
typedef struct
{
    uint32_t RTC_HourFormat;    /* Specifies the RTC Hour Format. */

    uint32_t RTC_AsynchPrediv;  /* Specifies the RTC Asynchronous Predivider value */

    uint32_t RTC_SynchPrediv;   /* Specifies the RTC Synchronous Predivider value */
} RTC_InitType;


/** RTC Time structure definition **/
typedef struct
{
    uint8_t Hours;      /* Specifies the RTC Time Hour */

    uint8_t Minutes;    /* Specifies the RTC Time Minutes */

    uint8_t Seconds;    /* Specifies the RTC Time Seconds */

    uint8_t H12;        /* Specifies the RTC AM/PM Time */
} RTC_TimeType;

/** RTC Date structure definition **/
typedef struct
{
    uint8_t WeekDay;    /* Specifies the RTC Date WeekDay */

    uint8_t Month;      /* Specifies the RTC Date Month (in BCD format) */

    uint8_t Date;       /* Specifies the RTC Date */

    uint8_t Year;       /* Specifies the RTC Date Year */
} RTC_DateType;

/** RTC Alarm structure definition **/
typedef struct
{
    RTC_TimeType AlarmTime; /* Specifies the RTC Alarm Time members. */

    uint32_t AlarmMask;     /* Specifies the RTC Alarm Masks */

    uint32_t DateWeekMode;  /* Specifies the RTC Alarm is on Date or WeekDay */

    uint8_t DateWeekValue;  /* Specifies the RTC Alarm Date/WeekDay */
} RTC_AlarmType;

/** RTC backup registers **/
typedef enum
{
    RTC_BACKUP_REGISTER_1 = 1,  /* RTC backup register 1*/
    RTC_BACKUP_REGISTER_2,      /* RTC backup register 2*/
    RTC_BACKUP_REGISTER_3,      /* RTC backup register 3*/
    RTC_BACKUP_REGISTER_4,      /* RTC backup register 4*/
    RTC_BACKUP_REGISTER_5,      /* RTC backup register 5*/
    RTC_BACKUP_REGISTER_6,      /* RTC backup register 6*/
    RTC_BACKUP_REGISTER_7,      /* RTC backup register 7*/
    RTC_BACKUP_REGISTER_8,      /* RTC backup register 8*/
    RTC_BACKUP_REGISTER_9,      /* RTC backup register 9*/
    RTC_BACKUP_REGISTER_10,     /* RTC backup register 10*/
    RTC_BACKUP_REGISTER_11,     /* RTC backup register 11*/
    RTC_BACKUP_REGISTER_12,     /* RTC backup register 12*/
    RTC_BACKUP_REGISTER_13,     /* RTC backup register 13*/
    RTC_BACKUP_REGISTER_14,     /* RTC backup register 14*/
    RTC_BACKUP_REGISTER_15,     /* RTC backup register 15*/
    RTC_BACKUP_REGISTER_16,     /* RTC backup register 16*/
    RTC_BACKUP_REGISTER_17,     /* RTC backup register 17*/
    RTC_BACKUP_REGISTER_18,     /* RTC backup register 18*/
    RTC_BACKUP_REGISTER_19,     /* RTC backup register 19*/
    RTC_BACKUP_REGISTER_20,     /* RTC backup register 20*/
}RTC_BACKUP_REGISTER;


#define RTC_REG_BIT_MASK                        ((uint32_t)0x00000000)

/** RTC_Hour_Formats **/
#define RTC_24HOUR_FORMAT                        (RTC_REG_BIT_MASK)
#define RTC_12HOUR_FORMAT                        (RTC_CTRL_HFMT)

/** Masks Definition **/
#define RTC_TR_RESERVED_MASK                     ((uint32_t)0x007F7F7F)
#define RTC_DATE_RESERVED_MASK                   ((uint32_t)0x00FFFF3F)

#define RTC_RSF_MASK                             ((uint32_t)0xFFFFFFDF)
#define RTC_FLAGS_MASK                           ((uint32_t)(RTC_FLAG_RECPF | RTC_FLAG_TAM3F | RTC_FLAG_TAM2F | RTC_FLAG_TAM1F | RTC_FLAG_TISOVF | RTC_FLAG_TISF | RTC_FLAG_WTF | RTC_FLAG_ALBF | RTC_FLAG_ALAF | RTC_FLAG_INITF        \
                                                 | RTC_FLAG_RSYF | RTC_FLAG_INITSF | RTC_FLAG_SHOPF | RTC_FLAG_WTWF | RTC_FLAG_ALBWF | RTC_FLAG_ALAWF))

/** RTC_TIMEOUT_Definitions**/
#define INITMODE_TIMEOUT                         ((uint32_t)0x00002000)
#define SYNCHRO_TIMEOUT                          ((uint32_t)0x00008000)
#define RECALPF_TIMEOUT                          ((uint32_t)0x00001000)
#define SHPF_TIMEOUT                             ((uint32_t)0x00002000)

/** RTC_AM_PM_Definitions **/
#define RTC_AM_H12                               ((uint8_t)0x00)
#define RTC_PM_H12                               (RTC_CTRL_HFMT)

/** Coded in BCD format **/
#define RTC_MONTH_JANUARY                        ((uint8_t)0x01)
#define RTC_MONTH_FEBRURY                        ((uint8_t)0x02)
#define RTC_MONTH_MARCH                          ((uint8_t)0x03)
#define RTC_MONTH_APRIL                          ((uint8_t)0x04)
#define RTC_MONTH_MAY                            ((uint8_t)0x05)
#define RTC_MONTH_JUNE                           ((uint8_t)0x06)
#define RTC_MONTH_JULY                           ((uint8_t)0x07)
#define RTC_MONTH_AUGUST                         ((uint8_t)0x08)
#define RTC_MONTH_SEPTEMBER                      ((uint8_t)0x09)
#define RTC_MONTH_OCTOBER                        ((uint8_t)0x10)
#define RTC_MONTH_NOVEMBER                       ((uint8_t)0x11)
#define RTC_MONTH_DECEMBER                       ((uint8_t)0x12)

/** RTC_WeekDay_Definitions **/
#define RTC_WEEKDAY_MONDAY                       ((uint8_t)0x01)
#define RTC_WEEKDAY_TUESDAY                      ((uint8_t)0x02)
#define RTC_WEEKDAY_WEDNESDAY                    ((uint8_t)0x03)
#define RTC_WEEKDAY_THURSDAY                     ((uint8_t)0x04)
#define RTC_WEEKDAY_FRIDAY                       ((uint8_t)0x05)
#define RTC_WEEKDAY_SATURDAY                     ((uint8_t)0x06)
#define RTC_WEEKDAY_SUNDAY                       ((uint8_t)0x07)

/** RTC_AlarmDateWeekDay_Definitions **/
#define RTC_ALARM_SEL_WEEKDAY_DATE               (RTC_REG_BIT_MASK)
#define RTC_ALARM_SEL_WEEKDAY_WEEKDAY            (RTC_ALARMA_WKDSEL)

/** RTC_AlarmMask_Definitions **/
#define RTC_ALARMMASK_NONE                       (RTC_REG_BIT_MASK)
#define RTC_ALARMMASK_WEEKDAY                    (RTC_ALARMA_MASK4)
#define RTC_ALARMMASK_HOURS                      (RTC_ALARMA_MASK3)
#define RTC_ALARMMASK_MINUTES                    (RTC_ALARMA_MASK2)
#define RTC_ALARMMASK_SECONDS                    (RTC_ALARMA_MASK1)
#define RTC_ALARMMASK_ALL                        (RTC_ALARMA_MASK4 | RTC_ALARMA_MASK3 | RTC_ALARMA_MASK2 | RTC_ALARMA_MASK1)

/** RTC_Alarms_Definitions **/
#define RTC_A_ALARM                              (RTC_CTRL_ALAEN)
#define RTC_B_ALARM                              (RTC_CTRL_ALBEN)

/** RTC_Bypass_Definitions **/
#define RTC_BYPASS_UPDATE                        (RTC_CTRL_BYPS)

/* RTC_Alarm_Sub_Seconds_Masks_Definitions */
#define RTC_SUBS_MASK_ALL       (RTC_REG_BIT_MASK)  /* All Alarm SS fields are masked There is no comparison on sub seconds for Alarm */
#define RTC_SUBS_MASK_SS14_1    ((uint32_t)0x01000000)  /* SS[14:1] are don't care in Alarm comparison. Only SS[0] is compared */
#define RTC_SUBS_MASK_SS14_2    ((uint32_t)0x02000000)  /* SS[14:2] are don't care in Alarm comparison. Only SS[1:0] are compared */
#define RTC_SUBS_MASK_SS14_3    ((uint32_t)0x03000000)  /* SS[14:3] are don't care in Alarm comparison. Only SS[2:0] are compared */
#define RTC_SUBS_MASK_SS14_4    ((uint32_t)0x04000000)  /* SS[14:4] are don't care in Alarm comparison. Only SS[3:0] are compared */
#define RTC_SUBS_MASK_SS14_5    ((uint32_t)0x05000000)  /* SS[14:5] are don't care in Alarm comparison. Only SS[4:0] are compared */
#define RTC_SUBS_MASK_SS14_6    ((uint32_t)0x06000000)  /* SS[14:6] are don't care in Alarm comparison. Only SS[5:0] are compared */
#define RTC_SUBS_MASK_SS14_7    ((uint32_t)0x07000000)  /* SS[14:7] are don't care in Alarm comparison. Only SS[6:0] are compared */
#define RTC_SUBS_MASK_SS14_8    ((uint32_t)0x08000000)  /* SS[14:8] are don't care in Alarm comparison. Only SS[7:0] are compared */
#define RTC_SUBS_MASK_SS14_9    ((uint32_t)0x09000000)  /* SS[14:9] are don't care in Alarm comparison. Only SS[8:0] are compared */
#define RTC_SUBS_MASK_SS14_10   ((uint32_t)0x0A000000)  /* SS[14:10] are don't care in Alarm comparison. Only SS[9:0] are compared */
#define RTC_SUBS_MASK_SS14_11   ((uint32_t)0x0B000000)  /* SS[14:11] are don't care in Alarm comparison. Only SS[10:0] are compared */
#define RTC_SUBS_MASK_SS14_12   ((uint32_t)0x0C000000)  /* SS[14:12] are don't care in Alarm comparison.Only SS[11:0] are compared */
#define RTC_SUBS_MASK_SS14_13   ((uint32_t)0x0D000000)  /* SS[14:13] are don't care in Alarm comparison. Only SS[12:0] are compared */
#define RTC_SUBS_MASK_SS14_14   ((uint32_t)0x0E000000)  /* SS[14] is don't care in Alarm comparison.Only SS[13:0] are compared */
#define RTC_SUBS_MASK_NONE      ((uint32_t)0x0F000000)  /* SS[14:0] are compared and must match to activate alarm */


typedef enum
{
    RTC_WKUPCLK_RTCCLK_DIV16   = (RTC_REG_BIT_MASK),
    RTC_WKUPCLK_RTCCLK_DIV8    = (RTC_CTRL_WKUPSEL_0),
    RTC_WKUPCLK_RTCCLK_DIV4    = (RTC_CTRL_WKUPSEL_1),
    RTC_WKUPCLK_RTCCLK_DIV2    = (RTC_CTRL_WKUPSEL_0 | RTC_CTRL_WKUPSEL_1),
    RTC_WKUPCLK_CK_SPRE_16BITS = (RTC_CTRL_WKUPSEL_2),
    RTC_WKUPCLK_CK_SPRE_17BITS = (RTC_CTRL_WKUPSEL_1 | RTC_CTRL_WKUPSEL_2),
}RTC_WAKE_UP_CLOCK;


/** RTC_Time_Stamp_Edges_definitions **/
#define RTC_TIMESTAMP_EDGE_RISING                (RTC_REG_BIT_MASK)
#define RTC_TIMESTAMP_EDGE_FALLING               (RTC_CTRL_TEDGE)

/** RTC_Reference_Detection_definitions **/
#define RTC_REFERENCE_DETECT_DISABLE             (RTC_REG_BIT_MASK)
#define RTC_REFERENCE_DETECT_ENABLE              (RTC_CTRL_REFCLKEN)

/** RTC_Output_selection_Definitions **/
#define RTC_OUTPUT_DIS  (RTC_REG_BIT_MASK)
#define RTC_OUTPUT_ALA  (RTC_CTRL_OUTSEL_0)
#define RTC_OUTPUT_ALB  (RTC_CTRL_OUTSEL_1)
#define RTC_OUTPUT_WKUP (RTC_CTRL_OUTSEL_0 | RTC_CTRL_OUTSEL_1)

/** RTC_Output_Polarity_Definitions **/
#define RTC_OUTPOL_HIGH                          (RTC_REG_BIT_MASK)
#define RTC_OUTPOL_LOW                           (RTC_CTRL_OPOL)

/** RTC_Calib_Output_selection_Definitions **/
#define RTC_CALIB_OUTPUT_256HZ                   (RTC_REG_BIT_MASK)
#define RTC_CALIB_OUTPUT_1HZ                     (RTC_CTRL_CALOSEL)

/** if RTCCLK = 32768 Hz, Smooth calibation period is 32s,  else 2exp20 RTCCLK seconds **/
#define SMOOTH_CALIB_32SEC                       (RTC_REG_BIT_MASK)

/** if RTCCLK = 32768 Hz, Smooth calibation period is 16s, else 2exp19 RTCCLK seconds **/
#define SMOOTH_CALIB_16SEC                       (RTC_CALIB_CW16) 

/** if RTCCLK = 32768 Hz, Smooth calibation period is 8s, else 2exp18 RTCCLK seconds **/
#define SMOOTH_CALIB_8SEC                        (RTC_CALIB_CW8) 

/** The number of RTCCLK pulses added during a X -second window = Y - CALM[8:0]  with Y = 512, 256, 128 when X = 32, 16, 8 **/
#define RTC_SMOOTH_CALIB_PLUS_PULSES_SET         (RTC_CALIB_CP)

/** The number of RTCCLK pulses subbstited during a 32-second window =   CALM[8:0] **/
#define RTC_SMOOTH_CALIB_PLUS_PULSES_RESET      (RTC_REG_BIT_MASK) 

/** RTC_DayLightSaving_Definitions **/
#define RTC_DAYLIGHT_SAVING_SUB1H                (RTC_CTRL_SU1H)
#define RTC_DAYLIGHT_SAVING_ADD1H                (RTC_CTRL_AD1H)

#define RTC_STORE_OPERATION_RESET                (RTC_REG_BIT_MASK)
#define RTC_STORE_OPERATION_SET                  (RTC_CTRL_BAKP)

/** RTC_Output_Type_ALARM_OUT **/
#define RTC_OUTPUT_OPENDRAIN                     (RTC_REG_BIT_MASK)
#define RTC_OUTPUT_PUSHPULL                      (RTC_OPT_TYPE)

/** RTC_Add_Fraction_Of_Second_Value **/
#define RTC_SHIFT_SUB1S_DISABLE                  (RTC_REG_BIT_MASK)
#define RTC_SHIFT_SUB1S_ENABLE                   (RTC_SCTRL_AD1S)

/** RTC_Input_parameter_format_definitions **/
#define RTC_FORMAT_BIN                           (RTC_REG_BIT_MASK)     //BIN format
#define RTC_FORMAT_BCD                           (0x00000001)           //register format

/** RTC_Flags_Definitions **/
#define RTC_INT_FLAG_RESERVED_MASK               ((uint32_t)0x0001FFFF)

#define RTC_FLAG_RECPF                           (RTC_INITSTS_RECPF)
#define RTC_FLAG_TAM3F                           (RTC_INITSTS_TAM3F)
#define RTC_FLAG_TAM2F                           (RTC_INITSTS_TAM2F)
#define RTC_FLAG_TAM1F                           (RTC_INITSTS_TAM1F)
#define RTC_FLAG_TISOVF                          (RTC_INITSTS_TISOVF)
#define RTC_FLAG_TISF                            (RTC_INITSTS_TISF)
#define RTC_FLAG_WTF                             (RTC_INITSTS_WTF)
#define RTC_FLAG_ALBF                            (RTC_INITSTS_ALBF)
#define RTC_FLAG_ALAF                            (RTC_INITSTS_ALAF)
#define RTC_FLAG_INITM                           (RTC_INITSTS_INITM)
#define RTC_FLAG_INITF                           (RTC_INITSTS_INITF)
#define RTC_FLAG_RSYF                            (RTC_INITSTS_RSYF)
#define RTC_FLAG_INITSF                          (RTC_INITSTS_INITSF)
#define RTC_FLAG_SHOPF                           (RTC_INITSTS_SHOPF)
#define RTC_FLAG_WTWF                            (RTC_INITSTS_WTWF)
#define RTC_FLAG_ALBWF                           (RTC_INITSTS_ALBWF)
#define RTC_FLAG_ALAWF                           (RTC_INITSTS_ALAWF)

/** RTC_Interrupts_Definitions **/
#define RTC_INT_TAMP3                            ((uint32_t)0x00080000)
#define RTC_INT_TAMP2                            ((uint32_t)0x00040000)
#define RTC_INT_TAMP1                            ((uint32_t)0x00020000)
#define RTC_INT_TST                              (RTC_CTRL_TSIEN)
#define RTC_INT_WUT                              (RTC_CTRL_WTIEN)
#define RTC_INT_ALRB                             (RTC_CTRL_ALBIEN)
#define RTC_INT_ALRA                             (RTC_CTRL_ALAIEN)

/** RTC_Tamper_Trigger_Definitions **/ 
#define RTC_TamperTrigger_RisingEdge            (RTC_REG_BIT_MASK)
#define RTC_TamperTrigger_FallingEdge           ((uint32_t)0x00000002)
#define RTC_TamperTrigger_LowLevel              (RTC_REG_BIT_MASK)
#define RTC_TamperTrigger_HighLevel             ((uint32_t)0x00000002)

/** RTC_Tamper_Filter_Definitions **/ 
#define RTC_TamperFilter_Disable                (RTC_REG_BIT_MASK)  /* Tamper filter is disabled */
#define RTC_TamperFilter_2Sample                (RTC_TMPCFG_TPFLT_0)    /* Tamper is activated after 2 consecutive samples at the active level */
#define RTC_TamperFilter_4Sample                (RTC_TMPCFG_TPFLT_1)    /* Tamper is activated after 4 consecutive samples at the active level */
#define RTC_TamperFilter_8Sample                (RTC_TMPCFG_TPFLT_0 | RTC_TMPCFG_TPFLT_1) /* Tamper is activated after 8 consecutive samples at the active leve */

/** RTC_Tamper_Sampling_Frequencies_Definitions **/ 
#define RTC_TamperSamplingFreq_RTCCLK_Div32768  (RTC_REG_BIT_MASK)  /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 32768 */
#define RTC_TamperSamplingFreq_RTCCLK_Div16384  (RTC_TMPCFG_TPFREQ_0)   /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 16384 */
#define RTC_TamperSamplingFreq_RTCCLK_Div8192   (RTC_TMPCFG_TPFREQ_1)   /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 8192  */
#define RTC_TamperSamplingFreq_RTCCLK_Div4096   (RTC_TMPCFG_TPFREQ_0 | RTC_TMPCFG_TPFREQ_1)     /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 4096  */
#define RTC_TamperSamplingFreq_RTCCLK_Div2048   (RTC_TMPCFG_TPFREQ_2)   /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 2048  */
#define RTC_TamperSamplingFreq_RTCCLK_Div1024   (RTC_TMPCFG_TPFREQ_0 | RTC_TMPCFG_TPFREQ_2)     /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 1024  */
#define RTC_TamperSamplingFreq_RTCCLK_Div512    (RTC_TMPCFG_TPFREQ_1 | RTC_TMPCFG_TPFREQ_2)     /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 512   */
#define RTC_TamperSamplingFreq_RTCCLK_Div256    (RTC_TMPCFG_TPFREQ_0 | RTC_TMPCFG_TPFREQ_1 | RTC_TMPCFG_TPFREQ_2)   /* Each of the tamper inputs are sampled with a frequency =  RTCCLK / 256   */
#define RTC_TAMPCR_TAMPFREQ                     (RTC_TMPCFG_TPFREQ_0 | RTC_TMPCFG_TPFREQ_1 | RTC_TMPCFG_TPFREQ_2)   /* Clear TAMPFREQ[2:0] bits in the RTC_TAMPCR register */

/** RTC_Tamper_Pin_Precharge_Duration_Definitions **/ 
#define RTC_TamperPrechargeDuration_1RTCCLK     (RTC_REG_BIT_MASK)      /* Tamper pins are pre-charged before sampling during 1 RTCCLK cycle */
#define RTC_TamperPrechargeDuration_2RTCCLK     (RTC_TMPCFG_TPPRCH_0)       /* Tamper pins are pre-charged before sampling during 2 RTCCLK cycles */
#define RTC_TamperPrechargeDuration_4RTCCLK     (RTC_TMPCFG_TPPRCH_1)       /* Tamper pins are pre-charged before sampling during 4 RTCCLK cycles */
#define RTC_TamperPrechargeDuration_8RTCCLK     (RTC_TMPCFG_TPPRCH_0 | RTC_TMPCFG_TPPRCH_1)  /* Tamper pins are pre-charged before sampling during 8 RTCCLK cycles */

/** @defgroup RTC_Tamper_Pins_Definitions **/ 
#define RTC_TAMPER_1            RTC_TMPCFG_TP1EN    /* Tamper detection enable for input tamper 1 */
#define RTC_TAMPER_2            RTC_TMPCFG_TP2EN    /* Tamper detection enable for input tamper 2 */
#define RTC_TAMPER_3            RTC_TMPCFG_TP3EN    /* Tamper detection enable for input tamper 3 */

#define RTC_TAMPER1_NOE         RTC_TMPCFG_TP1NOE    /* Tamper1 event do not clear backup register */
#define RTC_TAMPER2_NOE         RTC_TMPCFG_TP2NOE    /* Tamper2 event do not clear backup register */
#define RTC_TAMPER3_NOE         RTC_TMPCFG_TP3NOE    /* Tamper3 event do not clear backup register */

#define RTC_TAMPER1_INT         RTC_TMPCFG_TP1INTEN /* Tamper detection interruput enable */
#define RTC_TAMPER2_INT         RTC_TMPCFG_TP2INTEN /* Tamper detection interruput enable */
#define RTC_TAMPER3_INT         RTC_TMPCFG_TP3INTEN /* Tamper detection interruput enable */

/** Function used to set the RTC configuration to the default reset state **/
ErrorStatus RTC_Deinitializes(void);

/** Initialization and Configuration functions **/
void RTC_Structure_Initializes(RTC_InitType* RTC_InitStruct);
void RTC_Write_Protection_Enable(void);
void RTC_Write_Protection_Disable(void);
ErrorStatus RTC_Calendar_Initializes(uint32_t RTC_Format, RTC_InitType* RTC_InitStruct, RTC_DateType* RTC_DateStruct, RTC_TimeType* RTC_TimeStruct, FunctionalState RTC_DelayCmd);

ErrorStatus RTC_Initialization_Mode_Enter(void);
void RTC_Initialization_Mode_Exit(void);

ErrorStatus RTC_Wait_For_Synchronization(void);

ErrorStatus RTC_Reference_Clock_Enable(void);
ErrorStatus RTC_Reference_Clock_Disable(void);

void RTC_Bypass_Shadow_Enable(void);
void RTC_Bypass_Shadow_Disable(void);

/** Time and Date configuration functions **/
void RTC_Time_Struct_Initializes(RTC_TimeType* RTC_TimeStruct);
void RTC_Time_Get(uint32_t RTC_Format, RTC_TimeType* RTC_TimeStruct);
uint32_t RTC_SubSecond_Get(void);
void RTC_Date_Struct_Initializes(RTC_DateType* RTC_DateStruct);
void RTC_Date_Get(uint32_t RTC_Format, RTC_DateType* RTC_DateStruct);

/** Alarms (Alarm A and Alarm B) configuration functions **/
void RTC_Alarm_Set(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmType* RTC_AlarmStruct);
void RTC_Alarm_Struct_Initializes(RTC_AlarmType* RTC_AlarmStruct);
void RTC_Alarm_Get(uint32_t RTC_Format, uint32_t RTC_Alarm, RTC_AlarmType* RTC_AlarmStruct);
ErrorStatus RTC_Alarm_Enable(uint32_t RTC_Alarm);
ErrorStatus RTC_Alarm_Disable(uint32_t RTC_Alarm);
void RTC_Alarm_SubSecond_Config(uint32_t RTC_Alarm, uint32_t RTC_AlarmSubSecondValue, uint32_t RTC_AlarmSubSecondMask);
uint32_t RTC_Alarm_SubSecond_Get(uint32_t RTC_Alarm);

/** WakeUp Timer configuration functions **/
void RTC_WakeUp_Clock_Select(RTC_WAKE_UP_CLOCK RTC_WakeUp_Clock);
void RTC_WakeUp_Counter_Set(uint32_t RTC_WakeUpCounter);
uint32_t RTC_WakeUp_Counter_Get(void);
ErrorStatus RTC_WakeUp_Enable(void);
ErrorStatus RTC_WakeUp_Disable(void);

/** Daylight Saving configuration functions **/
void RTC_Day_Light_Saving_Config(uint32_t RTC_DayLightSaving, uint32_t RTC_StoreOperation);
uint32_t RTC_Store_Operation_Get(void);

/** Output pin Configuration function **/
void RTC_Output_Config(uint32_t RTC_Output, uint32_t RTC_OutputPolarity);
void RTC_Output_Mode_Config(uint32_t RTC_OutputType);


/** Coarse and Smooth Calibration configuration functions **/
void RTC_Calibration_Output_Enable(void);
void RTC_Calibration_Output_Disable(void);
void RTC_Calibration_Output_Config(uint32_t RTC_CalibOutput);
ErrorStatus RTC_Smooth_Calibration_Config(uint32_t RTC_SmoothCalibPeriod,
                                  uint32_t RTC_SmoothCalibPlusPulses,
                                  uint32_t RTC_SmouthCalibMinusPulsesValue);

/** TimeStamp configuration functions **/
void RTC_TimeStamp_Enable(uint32_t RTC_TimeStampEdge);
void RTC_TimeStamp_Disable(void);
void RTC_TimeStamp_Get(uint32_t RTC_Format, RTC_TimeType* RTC_StampTimeStruct, RTC_DateType* RTC_StampDateStruct);
uint32_t RTC_TimeStamp_SubSecond_Get(void);

/** RTC_Shift_control_synchonisation_functions **/
ErrorStatus RTC_Synchronization_Shift_Config(uint32_t RTC_ShiftAddFS, uint32_t RTC_ShiftSub1s);

/** Interrupts and flags management functions **/
void RTC_Interrupts_Enable(uint32_t RTC_INT);
void RTC_Interrupts_Disable(uint32_t RTC_INT);
FlagStatus RTC_Flag_Status_Get(uint32_t RTC_FLAG);
void RTC_Flag_Clear(uint32_t RTC_FLAG);
INTStatus RTC_Interrupt_Status_Get(uint32_t RTC_INT);
void RTC_Interrupt_Status_Clear(uint32_t RTC_INT);

/** Tamper configuration functions **/
void RTC_Tamper_Trigger_Config(uint32_t RTC_Tamper, uint32_t RTC_TamperTrigger);
void RTC_Tamper_Enable(uint32_t RTC_Tamper);
void RTC_Tamper_Disable(uint32_t RTC_Tamper);
void RTC_Tamper_Filter_Config(uint32_t RTC_TamperFilter);
void RTC_Tamper_Sampling_Frequency_Config(uint32_t RTC_TamperSamplingFreq);
void RTC_Tamper_Pins_Precharge_Duration(uint32_t RTC_TamperPrechargeDuration);
void RTC_TimeStamp_On_Tamper_Detection_Enable(void);
void RTC_TimeStamp_On_Tamper_Detection_Disable(void);
void RTC_Tamper_Precharge_Enable(void);
void RTC_Tamper_Precharge_Disable(void);
void RTC_Tamper_Interrput_Enable(uint32_t TAMPx_INT);
void RTC_Tamper_Interrput_Disable(uint32_t TAMPx_INT);
void RTC_Tamper_Backup_Register_Clear_Disable(uint32_t RTC_TAMPERx_NOE);
void RTC_Tamper_Backup_Register_Clear_Enable(uint32_t RTC_TAMPERx_NOE);

/** Backup Data Registers configuration functions **/
void RTC_Backup_Register_Write(RTC_BACKUP_REGISTER register_num, uint32_t Data);
uint32_t RTC_Backup_Register_Read(RTC_BACKUP_REGISTER register_num);

#ifdef __cplusplus
}
#endif

#endif /*__N32G430_RTC_H__ */

