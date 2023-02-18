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
*\*\file n32g430_flash.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/
#ifndef __N32G430_FLASH_H__
#define __N32G430_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

/*** FLASH Status ***/
typedef enum
{
    FLASH_BUSY = 1,
    FLASH_ERR_PG,
    FLASH_ERR_WRP,
    FLASH_EOP,
    FLASH_ERR_RDP2,
    FLASH_ERR_ADD,
    FLASH_TIMEOUT
} FLASH_STS;


/** Flash Access Control Register bits **/
#define FLASH_PRFTBS_MSK  ((uint32_t)FLASH_AC_PRFTBFSTS)
#define FLASH_ICAHRST_MSK ((uint32_t)FLASH_AC_ICAHRST)

/** Flash_Latency **/
#define FLASH_LATENCY_0     ((uint32_t)FLASH_AC_LATENCY_0) /* FLASH Zero Latency cycle */
#define FLASH_LATENCY_1     ((uint32_t)FLASH_AC_LATENCY_1) /* FLASH One Latency cycle */
#define FLASH_LATENCY_2     ((uint32_t)FLASH_AC_LATENCY_2) /* FLASH Two Latency cycles */
#define FLASH_LATENCY_3     ((uint32_t)FLASH_AC_LATENCY_3) /* FLASH Three Latency cycles */
#define FLASH_LATENCY_MASK  ((uint32_t)FLASH_AC_LATENCY)

/** FLASH Keys **/
#define FLASH_KEY1   ((uint32_t)0x45670123)
#define FLASH_KEY2   ((uint32_t)0xCDEF89AB)

/** Flash Control Register bits **/
#define FLASH_CTRL_SET_PG       ((uint32_t)FLASH_CTRL_PG)
#define FLASH_CTRL_RESET_PG     (~((uint32_t)FLASH_CTRL_PG))
#define FLASH_CTRL_SET_PER      ((uint32_t)FLASH_CTRL_PER)
#define FLASH_CTRL_RESET_PER    (~((uint32_t)FLASH_CTRL_PER))
#define FLASH_CTRL_SET_MER      ((uint32_t)FLASH_CTRL_MER)
#define FLASH_CTRL_RESET_MER    (~((uint32_t)FLASH_CTRL_MER))
#define FLASH_CTRL_SET_OPTPG    ((uint32_t)FLASH_CTRL_OPTPG)
#define FLASH_CTRL_RESET_OPTPG  (~((uint32_t)FLASH_CTRL_OPTPG))
#define FLASH_CTRL_SET_OPTER    ((uint32_t)FLASH_CTRL_OPTER)
#define FLASH_CTRL_RESET_OPTER  (~((uint32_t)FLASH_CTRL_OPTER))
#define FLASH_CTRL_SET_START    ((uint32_t)FLASH_CTRL_START)
#define FLASH_CTRL_SET_LOCK     ((uint32_t)FLASH_CTRL_LOCK)
#define FLASH_CTRL_SET_OPTWE    ((uint32_t)FLASH_CTRL_OPTWRE)

/** Option byte **/
#define FLASH_L1_RDP_KEY        ((uint32_t)0xFFFF00A5)  
#define FLASH_L2_RDP_KEY        ((uint32_t)0xFFFF33CC)
#define FLASH_OB_DATA0_MASK      (FLASH_OB_DATA0_MSK)
#define FLASH_OB_DATA1_MASK      (FLASH_OB_DATA1_MSK)


/** OB Register related definition**/
#define FLASH_USER_MASK    (FLASH_USER_USER)
#define FLASH_RDP1_MASK    (FLASH_RDP_RDP1)
#define FLASH_RDP2_MASK    ((uint32_t)0xFF00FFFF)
#define FLASH_FLAG_OBERR   (FLASH_OB_OBERR)


/** FLASH Mask **/
#define FLASH_RDPRTL1_MSK           ((uint32_t)FLASH_OB_RDPRT1)
#define FLASH_RDPRTL2_MSK           ((uint32_t)FLASH_OB_RDPRT2)
#define FLASH_OB_USER_MSK           ((uint32_t)FLASH_OB_USER)
#define FLASH_WRP_WRP1_OFFSET       (REG_BIT8_OFFSET)
#define FLASH_WRP1_DATA_OFFSET      (REG_BIT16_OFFSET)         
#define FLASH_WRP0_MSK              (FLASH_WRP0_WRP0)
#define FLASH_WRP1_MSK              (FLASH_WRP1_WRP1 >> FLASH_WRP_WRP1_OFFSET)

/** Prefetch_Buffer_Enable_Disable **/
#define FLASH_PREFETCHBUF_EN              ((uint32_t)FLASH_AC_PRFTBFEN)            /* FLASH Prefetch Buffer Enable */
#define FLASH_PREFETCHBUF_DIS             (~((uint32_t)FLASH_AC_PRFTBFEN))         /* FLASH Prefetch Buffer Disable */

/** iCache_Enable_Disable **/
#define FLASH_ICACHE_EN              ((uint32_t)FLASH_AC_ICAHEN)           /* FLASH iCache Enable */
#define FLASH_ICACHE_DIS             (~((uint32_t)FLASH_AC_ICAHEN))        /* FLASH iCache Disable */

/** Bit definition for FLASH_CAHR register **/
#define FLASH_CAHR_LOCKSTRT_WAY0    (FLASH_CAHR_LOCKSTRT_0)
#define FLASH_CAHR_LOCKSTRT_WAY1    (FLASH_CAHR_LOCKSTRT_1)
#define FLASH_CAHR_LOCKSTRT_WAY2    (FLASH_CAHR_LOCKSTRT_2)
#define FLASH_CAHR_LOCKSTRT_WAY3    (FLASH_CAHR_LOCKSTRT_3)
#define FLASH_CAHR_LOCK_OFFSET      (REG_BIT4_OFFSET)
#define FLASH_CAHR_LOCKSTOP_WAY0    (FLASH_CAHR_LOCKSTOP_0)
#define FLASH_CAHR_LOCKSTOP_WAY1    (FLASH_CAHR_LOCKSTOP_1)
#define FLASH_CAHR_LOCKSTOP_WAY2    (FLASH_CAHR_LOCKSTOP_2)
#define FLASH_CAHR_LOCKSTOP_WAY3    (FLASH_CAHR_LOCKSTOP_3)

/** Values to be used with N32G430 devices **/
#define FLASH_WRP_Pages0to1    ((uint32_t)0x00000001) /* N32G430 devices: Write protection of page 0 to 1 */
#define FLASH_WRP_Pages2to3    ((uint32_t)0x00000002) /* N32G430 devices: Write protection of page 2 to 3 */
#define FLASH_WRP_Pages4to5    ((uint32_t)0x00000004) /* N32G430 devices: Write protection of page 4 to 5 */
#define FLASH_WRP_Pages6to7    ((uint32_t)0x00000008) /* N32G430 devices: Write protection of page 6 to 7 */
#define FLASH_WRP_Pages8to9    ((uint32_t)0x00000010) /* N32G430 devices: Write protection of page 8 to 9 */
#define FLASH_WRP_Pages10to11  ((uint32_t)0x00000020) /* N32G430 devices: Write protection of page 10 to 11 */
#define FLASH_WRP_Pages12to13  ((uint32_t)0x00000040) /* N32G430 devices: Write protection of page 12 to 13 */
#define FLASH_WRP_Pages14to15  ((uint32_t)0x00000080) /* N32G430 devices: Write protection of page 14 to 15 */
#define FLASH_WRP_Pages16to17  ((uint32_t)0x00000100) /* N32G430 devices: Write protection of page 16 to 17 */
#define FLASH_WRP_Pages18to19  ((uint32_t)0x00000200) /* N32G430 devices: Write protection of page 18 to 19 */
#define FLASH_WRP_Pages20to21  ((uint32_t)0x00000400) /* N32G430 devices: Write protection of page 20 to 21 */
#define FLASH_WRP_Pages22to23  ((uint32_t)0x00000800) /* N32G430 devices: Write protection of page 22 to 23 */
#define FLASH_WRP_Pages24to25  ((uint32_t)0x00001000) /* N32G430 devices: Write protection of page 24 to 25 */
#define FLASH_WRP_Pages26to27  ((uint32_t)0x00002000) /* N32G430 devices: Write protection of page 26 to 27 */
#define FLASH_WRP_Pages28to29  ((uint32_t)0x00004000) /* N32G430 devices: Write protection of page 28 to 29 */
#define FLASH_WRP_Pages30to31  ((uint32_t)0x00008000) /* N32G430 devices: Write protection of page 30 to 31 */

#define FLASH_WRP_AllPages ((uint32_t)0xFFFFFFFF) /* Write protection of all Pages */

/** Option_Bytes_RDPx **/
#define FLASH_OB_RDP1_ENABLE            ((uint8_t)0x00) /* Enable RDP1 */
#define FLASH_OB_RDP1_DISABLE           ((uint8_t)0xA5) /* DISABLE RDP1 */

#define FLASH_OB_RDP2_ENABLE            ((uint8_t)0x33) /* Enable RDP2 */
#define FLASH_OB_RDP2_DISABLE           ((uint8_t)0x00) /* Disable RDP2 */

/** Option_Bytes_IWatchdog **/
#define FLASH_OB_IWDG_SW                ((uint16_t)0x0001) /* Software IWDG selected */
#define FLASH_OB_IWDG_HW                ((uint16_t)0x0000) /* Hardware IWDG selected */

/** Option_Bytes_nRST_STOP **/
#define FLASH_OB_STOP_NORST             ((uint16_t)0x0002) /* No reset generated when entering in STOP */
#define FLASH_OB_STOP_RST               ((uint16_t)0x0000) /* Reset generated when entering in STOP */

/** Option_Bytes_nRST_STDBY **/
#define FLASH_OB_STDBY_NORST             ((uint16_t)0x0004) /* No reset generated when entering in STANDBY */
#define FLASH_OB_STDBY_RST               ((uint16_t)0x0000) /* Reset generated when entering in STANDBY */

/** Option_Bytes_IWatchdog_STOP0 **/
#define FLASH_OB_IWDG_STOP0_FRZ         ((uint16_t)0x0000) /* IWDG freeze in stop0 */
#define FLASH_OB_IWDG_STOP0_NOFRZ       ((uint16_t)0x0008) /* Default no freeze */

/** Option_Bytes_IWatchdog_STOP2 **/
#define FLASH_OB_IWDG_STOP2_FRZ         ((uint16_t)0x0000) /* IWDG freeze in stop2 */
#define FLASH_OB_IWDG_STOP2_NOFRZ       ((uint16_t)0x0010) /* Default no freeze */

/** Option_Bytes_IWatchdog_STDBY **/
#define FLASH_OB_IWDG_STDBY_FRZ         ((uint16_t)0x0000) /* IWDG freeze in standby */
#define FLASH_OB_IWDG_STDBY_NOFRZ       ((uint16_t)0x0020) /* Default no freeze */

/** Option_Bytes_IWatchdog_SLEEP **/
#define FLASH_OB_IWDG_SLEEP_FRZ         ((uint16_t)0x0000) /* IWDG freeze in sleep */
#define FLASH_OB_IWDG_SLEEP_NOFRZ       ((uint16_t)0x0040) /* Default no freeze */

#define FLASH_USER_RPD_OFFSET           (REG_BIT16_OFFSET)
#define FLASH_OB_TO_USER_OFFSET         (REG_BIT14_OFFSET)
#define FLASH_OB_OFFSET                 (REG_BIT2_OFFSET)
#define FLASH_DATA0_DATA1_OFFSET        (REG_BIT16_OFFSET)
#define FLASH_OB_DATA0_OFFSET           (REG_BIT10_OFFSET)
#define FLASH_OB_DATA1_OFFSET           (REG_BIT18_OFFSET)

/** OB2 **/
#define FLASH_OB2_NBOOT0_SET                ((uint8_t)0x01) /* Set nBOOT0 */
#define FLASH_OB2_NBOOT0_CLR                ((uint8_t)0x00) /* Clear nBOOT0 */

#define FLASH_OB2_NBOOT1_SET                ((uint8_t)0x02) /* Set nBOOT1 */
#define FLASH_OB2_NBOOT1_CLR                ((uint8_t)0x00) /* Clear nBOOT1 */

#define FLASH_OB2_NSWBOOT0_SET              ((uint8_t)0x04) /* Set nSWBOOT0 */
#define FLASH_OB2_NSWBOOT0_CLR              ((uint8_t)0x00) /* Clear nSWBOOT0 */

/** Bit definition for FLASH_OB2 register **/
#define FLASH_OB2_nBOOT1_MASK       (FLASH_OB2_nBOOT1)   /* nBOOT1 */
#define FLASH_OB2_nSWBOOT0_MASK     (FLASH_OB2_nSWBOOT0) /* nSWBOOT0 */
#define FLASH_OB2_nBOOT0_MASK       (FLASH_OB2_nBOOT0)   /* nBOOT0 */
#define FLASH_OB2_USER2_OFFSET      (REG_BIT16_OFFSET)

/** FLASH_Interrupts **/
#define FLASH_INT_ERROR    ((uint32_t)FLASH_CTRL_ERRITE) /* PGERR WRPERR ERROR error interrupt source */
#define FLASH_INT_EOP      ((uint32_t)FLASH_CTRL_EOPITE) /* End of FLASH Operation Interrupt source */

/** FLASH_Flags **/
#define FLASH_FLAG_BUSY     ((uint32_t)FLASH_STS_BUSY) /* FLASH Busy flag */
#define FLASH_FLAG_PGERR    ((uint32_t)FLASH_STS_PGERR) /* FLASH Program error flag */
#define FLASH_FLAG_WRPERR   ((uint32_t)FLASH_STS_WRPERR) /* FLASH Write protected error flag */
#define FLASH_FLAG_EOP      ((uint32_t)FLASH_STS_EOP) /* FLASH End of Operation flag */

/** FLASH_STS_CLRFLAG **/
#define FLASH_STS_CLRFLAG   (FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR | FLASH_FLAG_EOP)

/** Delay definition **/
#define ERASE_TIMEOUT   ((uint32_t)0x000B0000)
#define PROGRAM_TIMEOUT ((uint32_t)0x00002000)

#define FLASH_WORD_LENGTH   ((uint32_t)0x00000003)

/*** Functions used for N32G430 devices ***/
void FLASH_Latency_Set(uint32_t flash_latency);
uint8_t FLASH_Latency_Get(void);
void FLASH_Prefetch_Buffer_Enable(void);
void FLASH_Prefetch_Buffer_Disable(void);
void FLASH_ICache_Reset(void);
void FLASH_ICache_Enable(void);
void FLASH_ICache_Disable(void);
FlagStatus FLASH_ICache_Status_Get(void);
void FLASH_Cache_LOCK_Start(uint32_t lock_start_way);
void FLASH_Cache_LOCK_Stop(uint32_t lock_stop_way);
void FLASH_Cache_LOCK_Cancel(uint32_t lock_stop_way);
FlagStatus FLASH_Cache_LOCK_Status_Get(uint32_t lock_way);
void FLASH_Unlock(void);
void FLASH_Lock(void);
void Option_Bytes_Unlock(void);
void Option_Bytes_Lock(void);
FlagStatus Option_Bytes_Lock_Status_Get(void);
FLASH_STS FLASH_One_Page_Erase(uint32_t page_address);
FLASH_STS FLASH_Mass_Erase(void);
FLASH_STS FLASH_Word_Program(uint32_t address, uint32_t data);
FLASH_STS FLASH_Option_Bytes_Erase(void);
FLASH_STS FLASH_Option_Bytes_User_RDP1_Program(uint8_t option_byte_rpd1, uint16_t option_byte_iwdg, \
                                               uint16_t option_byte_stop, uint16_t option_byte_stdby, \
                                               uint16_t option_byte_iwdg_stop0, uint16_t option_byte_iwdg_stop2, \
                                               uint16_t option_byte_iwdg_stdby, uint16_t option_byte_iwdg_sleep);
FLASH_STS FLASH_Option_Bytes_DATA_Program(uint8_t option_byte_data0,uint8_t option_byte_data1);
FLASH_STS FLASH_Write_Protection_Enable(uint32_t flash_pages);
FLASH_STS FLASH_Option_Bytes_User2_RDP2_Program(uint8_t option_byte_rpd2,uint8_t option_byte2_nBOOT0, \
                                                uint8_t option_byte2_nBOOT1, uint8_t option_byte2_nSWBOOT0);
FLASH_STS FLASH_Read_Out_Protection_L1_Enable(void);
FLASH_STS FLASH_Read_Out_Protection_L1_Disable(void);
FLASH_STS FLASH_Read_Out_Protection_L2_Enable(void);
uint32_t FLASH_Option_Bytes_User_Get(void);
FlagStatus FLASH_Option_Bytes2_User_Get(uint32_t boot_bit);
uint32_t FLASH_Option_Bytes_Data0_Get(void);
uint32_t FLASH_Option_Bytes_Data1_Get(void);
uint32_t FLASH_Option_Bytes_Write_Protection_Get(void);
FlagStatus FLASH_Read_Out_Protection_Status_Get(void);
FlagStatus FLASH_Read_Out_Protection_L2_Status_Get(void);
FlagStatus FLASH_Prefetch_Buffer_Status_Get(void);
void FLASH_Interrupt_Enable(uint32_t flash_interrupts);
void FLASH_Interrupt_Disable(uint32_t flash_interrupts);
FlagStatus FLASH_Flag_Status_Get(uint32_t flash_flag);
FlagStatus FLASH_Option_Bytes_Flag_Get(uint32_t flash_flag);
void FLASH_Flag_Status_Clear(uint32_t flash_flag);
FLASH_STS FLASH_Status_Get(void);
FLASH_STS FLASH_Last_Operation_Wait(uint32_t timeout);


#ifdef __cplusplus
}
#endif

#endif  /** __N32G430_FLASH_H__ **/

