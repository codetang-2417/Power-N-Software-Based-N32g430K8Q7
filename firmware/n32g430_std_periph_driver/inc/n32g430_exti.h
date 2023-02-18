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
*\*\file n32g430_exti.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/
#ifndef __N32G430_EXTI_H__
#define __N32G430_EXTI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

/*** EXTI Structure Definition Start ***/

/** EXTI mode enumeration **/

typedef enum
{
    EXTI_Mode_Interrupt = 0x00,
    EXTI_Mode_Event     = 0x04
} EXTI_ModeType;


/** EXTI Trigger enumeration **/

typedef enum
{
    EXTI_Trigger_Rising         = 0x08,
    EXTI_Trigger_Falling        = 0x0C,
    EXTI_Trigger_Rising_Falling = 0x10
} EXTI_TriggerType;


/** EXTI Init Structure definition **/

typedef struct
{
    uint32_t EXTI_Line; /* Specifies the EXTI lines to be enabled or disabled. */

    EXTI_ModeType EXTI_Mode; /* Specifies the mode for the EXTI lines. */

    EXTI_TriggerType EXTI_Trigger; /* Specifies the trigger signal active edge for the EXTI lines. */

    FunctionalState EXTI_LineCmd; /* Specifies the new state of the selected EXTI lines. */
} EXTI_InitType;

/*** EXTI Structure Definition End ***/


/*** EXTI Macro Definition Start ***/

/** EXTI_Lines **/

#define EXTI_LINENONE ((uint32_t)0x00000) /* No interrupt selected */

#define EXTI_LINE0  ((uint32_t)0x00001) /* External interrupt line 0 */
#define EXTI_LINE1  ((uint32_t)0x00002) /* External interrupt line 1 */
#define EXTI_LINE2  ((uint32_t)0x00004) /* External interrupt line 2 */
#define EXTI_LINE3  ((uint32_t)0x00008) /* External interrupt line 3 */
#define EXTI_LINE4  ((uint32_t)0x00010) /* External interrupt line 4 */
#define EXTI_LINE5  ((uint32_t)0x00020) /* External interrupt line 5 */
#define EXTI_LINE6  ((uint32_t)0x00040) /* External interrupt line 6 */
#define EXTI_LINE7  ((uint32_t)0x00080) /* External interrupt line 7 */
#define EXTI_LINE8  ((uint32_t)0x00100) /* External interrupt line 8 */
#define EXTI_LINE9  ((uint32_t)0x00200) /* External interrupt line 9 */
#define EXTI_LINE10 ((uint32_t)0x00400) /* External interrupt line 10 */
#define EXTI_LINE11 ((uint32_t)0x00800) /* External interrupt line 11 */
#define EXTI_LINE12 ((uint32_t)0x01000) /* External interrupt line 12 */
#define EXTI_LINE13 ((uint32_t)0x02000) /* External interrupt line 13 */
#define EXTI_LINE14 ((uint32_t)0x04000) /* External interrupt line 14 */
#define EXTI_LINE15 ((uint32_t)0x08000) /* External interrupt line 15 */
#define EXTI_LINE16 ((uint32_t)0x10000) /* External interrupt line 16 Connected to the PVD Output */
#define EXTI_LINE17 ((uint32_t)0x20000) /* External interrupt line 17 Connected to the RTC Alarm event */
#define EXTI_LINE18 ((uint32_t)0x40000) /* External interrupt line 18 Connected to the RTC Time stamp event */
#define EXTI_LINE19 ((uint32_t)0x80000)  /* External interrupt line 19 Connected to the RTC Wakeup event */
#define EXTI_LINE20 ((uint32_t)0x100000) /* External interrupt line 20 Connected to the LPTIM Global interrupt */
#define EXTI_LINE21 ((uint32_t)0x200000) /* External interrupt line 21 Connected to the COMP1 Global interrupt */
#define EXTI_LINE22 ((uint32_t)0x400000) /* External interrupt line 22 Connected to the COMP2 Global interrupt */
#define EXTI_LINE23 ((uint32_t)0x800000) /* External interrupt line 23 Connected to the COMP3 Global interrupt */


/** EXTI_TSSEL_Line **/
#define EXTI_TSSEL_LINE_MASK ((uint32_t)0x00000)
#define EXTI_TSSEL_LINE0     ((uint32_t)0x00000) /* External interrupt line 0 */
#define EXTI_TSSEL_LINE1     ((uint32_t)0x00001) /* External interrupt line 1 */
#define EXTI_TSSEL_LINE2     ((uint32_t)0x00002) /* External interrupt line 2 */
#define EXTI_TSSEL_LINE3     ((uint32_t)0x00003) /* External interrupt line 3 */
#define EXTI_TSSEL_LINE4     ((uint32_t)0x00004) /* External interrupt line 4 */
#define EXTI_TSSEL_LINE5     ((uint32_t)0x00005) /* External interrupt line 5 */
#define EXTI_TSSEL_LINE6     ((uint32_t)0x00006) /* External interrupt line 6 */
#define EXTI_TSSEL_LINE7     ((uint32_t)0x00007) /* External interrupt line 7 */
#define EXTI_TSSEL_LINE8     ((uint32_t)0x00008) /* External interrupt line 8 */
#define EXTI_TSSEL_LINE9     ((uint32_t)0x00009) /* External interrupt line 9 */
#define EXTI_TSSEL_LINE10    ((uint32_t)0x0000A) /* External interrupt line 10 */
#define EXTI_TSSEL_LINE11    ((uint32_t)0x0000B) /* External interrupt line 11 */
#define EXTI_TSSEL_LINE12    ((uint32_t)0x0000C) /* External interrupt line 12 */
#define EXTI_TSSEL_LINE13    ((uint32_t)0x0000D) /* External interrupt line 13 */
#define EXTI_TSSEL_LINE14    ((uint32_t)0x0000E) /* External interrupt line 14 */
#define EXTI_TSSEL_LINE15    ((uint32_t)0x0000F) /* External interrupt line 15 */
/*** EXTI Macro Definition End ***/

/** EXTI Driving Functions Declaration **/

void EXTI_Reset(void);
void EXTI_Peripheral_Initializes(EXTI_InitType* EXTI_InitStruct);
void EXTI_Work_Mode_Config(uint32_t exti_line,uint32_t exti_mode);
void EXTI_Trigger_Config(uint32_t exti_line,uint32_t exti_trigger);
void EXTI_LineCmd_Disable(uint32_t exti_line,uint32_t exti_linecmd,uint32_t exti_mode);
void EXTI_Structure_Initializes(EXTI_InitType* EXTI_InitStruct);
void EXTI_Software_Interrupt_Trigger(uint32_t exti_line);
FlagStatus EXTI_Flag_Status_Get(uint32_t exti_line);
void EXTI_Flag_Status_Clear(uint32_t exti_line);
INTStatus EXTI_Interrupt_Status_Get(uint32_t exti_line);
void EXTI_Interrupt_Status_Clear(uint32_t exti_line);
void EXTI_RTC_Time_Stamp_Select(uint32_t exti_tssel_line);

#ifdef __cplusplus
}
#endif

#endif 
/** **/


