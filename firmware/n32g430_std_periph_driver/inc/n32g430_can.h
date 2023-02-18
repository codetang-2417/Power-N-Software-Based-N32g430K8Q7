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
*\*\file n32g430_can.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/
#ifndef __N32G430_CAN_H__
#define __N32G430_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"


/** CAN init structure definition **/
typedef struct
{
    uint16_t BaudRatePrescaler; /* Specifies the length of a time quantum. */

    uint8_t OperatingMode; /* Specifies the CAN operating mode. */

    uint8_t RSJW; /* Specifies the maximum number of time quanta
                          the CAN hardware is allowed to lengthen or
                          shorten a bit to perform resynchronization. */

    uint8_t TBS1; /* Specifies the number of time quanta in Bit Segment 1. */

    uint8_t TBS2; /* Specifies the number of time quanta in Bit Segment 2. */

    FunctionalState TTCM; /* Enable or disable the time triggered communication mode. */

    FunctionalState ABOM; /* Enable or disable the automatic bus-off management. */

    FunctionalState AWKUM; /* Enable or disable the automatic wake-up mode. */

    FunctionalState NART; /* Enable or disable the no-automatic retransmission mode. */

    FunctionalState RFLM; /* Enable or disable the Receive DATFIFO Locked mode. */

    FunctionalState TXFP; /* Enable or disable the transmit DATFIFO priority. */
} CAN_InitType;

/** CAN filter init structure definition **/
typedef struct
{
    uint16_t Filter_HighId; /* Specifies the filter identification number (MSBs for a 32-bit
                                        configuration, first one for a 16-bit configuration). */

    uint16_t Filter_LowId; /* Specifies the filter identification number (LSBs for a 32-bit
                                       configuration, second one for a 16-bit configuration). */

    uint16_t FilterMask_HighId; /* Specifies the filter mask number or identification number,
                                            according to the mode (MSBs for a 32-bit configuration,
                                            first one for a 16-bit configuration). */

    uint16_t FilterMask_LowId; /* Specifies the filter mask number or identification number,
                                           according to the mode (LSBs for a 32-bit configuration,
                                           second one for a 16-bit configuration). */

    uint16_t Filter_FIFOAssignment; /* Specifies the DATFIFO (0 or 1) which will be assigned to the filter. */

    uint8_t Filter_Num; /* Specifies the filter which will be initialized. */

    uint8_t Filter_Mode; /* Specifies the filter mode to be initialized. */

    uint8_t Filter_Scale; /* Specifies the filter scale. */

    FunctionalState Filter_Act; /* Enable or disable the filter. */
} CAN_FilterInitType;

/** CAN Tx message structure definition **/
typedef struct
{
    uint32_t StdId; /* Specifies the standard identifier.
                         This parameter can be a value between 0 to 0x7FF. */

    uint32_t ExtId; /* Specifies the extended identifier.
                         This parameter can be a value between 0 to 0x1FFFFFFF. */

    uint8_t IDE; /* Specifies the type of identifier for the message that
                      will be transmitted. This parameter can be a value
                      of @ref CAN_identifier_type */

    uint8_t RTR; /* Specifies the type of frame for the message that will
                      be transmitted. This parameter can be a value of
                      @ref CAN_remote_transmission_request */

    uint8_t DLC; /* Specifies the length of the frame that will be
                      transmitted. This parameter can be a value between
                      0 to 8 */

    uint8_t Data[8]; /* Contains the data to be transmitted. It ranges from 0
                          to 0xFF. */
} CanTxMessage;

/**  CAN Rx message structure definition **/
typedef struct
{
    uint32_t StdId; /* Specifies the standard identifier.
                         This parameter can be a value between 0 to 0x7FF. */

    uint32_t ExtId; /* Specifies the extended identifier.
                         This parameter can be a value between 0 to 0x1FFFFFFF. */

    uint8_t IDE; /* Specifies the type of identifier for the message that
                      will be received. */

    uint8_t RTR; /* Specifies the type of frame for the received message. */

    uint8_t DLC; /* Specifies the length of the frame that will be received.
                      This parameter can be a value between 0 to 8 */

    uint8_t Data[8]; /* Contains the data to be received. It ranges from 0 to
                          0xFF. */

    uint8_t FMI; /* Specifies the index of the filter the message stored in
                      the mailbox passes through. This parameter can be a
                      value between 0 to 0xFF */
} CanRxMessage;

typedef enum
{
    CAN_STS_Failed = 0,
    CAN_STS_Success
} CAN_Status;

typedef enum
{
    CAN_TXSTS_FAILED = 0,       /* CAN transmission failed */
    CAN_TXSTS_OK,               /* CAN transmission succeeded */
    CAN_TXSTS_PENDING           /* CAN transmission pending */
} CAN_Tx_Status;

/** CAN Master Control Register bits **/    
#define CAN_INIT_REQUEST     (CAN_MCTRL_INIRQ)     /* Initialization Request */
#define CAN_SLEEP_REQUEST    (CAN_MCTRL_SLPRQ)     /* Sleep Mode Request */
#define CAN_TX_FIFO_PRIO     (CAN_MCTRL_TXFP)      /* Transmit DATFIFO Priority */
#define CAN_RX_FIFO_LOCKED   (CAN_MCTRL_RFLM)      /* Receive DATFIFO Locked Mode */ 
#define CAN_AUTO_RETRANS_OFF (CAN_MCTRL_NART)      /* No Automatic Retransmission */ 
#define CAN_AUTO_WAKE_UP     (CAN_MCTRL_AWKUM)     /* Automatic Wakeup Mode */
#define CAN_AUTO_BUS_OFF     (CAN_MCTRL_ABOM)      /* Automatic Bus-Off Management */
#define CAN_TIME_TRI_MODE    (CAN_MCTRL_TTCM)      /* Time Triggered Communication Mode */
#define CAN_DEBUG_FREEZE     (CAN_MCTRL_DBGF)      /* Debug freeze */
#define CAN_SW_MASTER_RESET  (CAN_MCTRL_MRST)      /* software master reset */

/** CAN Master status Register bits **/
#define CAN_INIT_WAIT           (CAN_MSTS_INIAK)    /* Initialization Acknowledge */
#define CAN_SLEEP_WAIT          (CAN_MSTS_SLPAK)    /* Sleep Acknowledge */
#define CAN_ERROR_INT           (CAN_MSTS_ERRINT)   /* Error Interrupt */
#define CAN_WAKE_UP_INT         (CAN_MSTS_WKUINT)   /* Wakeup Interrupt */
#define CAN_SLEEP_WAITINT       (CAN_MSTS_SLAKINT)  /* Sleep Acknowledge Interrupt */
#define CAN_TX_MODE             (CAN_MSTS_TXMD)     /* Transmit Mode */
#define CAN_RX_MODE             (CAN_MSTS_RXMD)     /* Receive Mode */
#define CAN_LAST_SAMPLE_POINT   (CAN_MSTS_LSMP)     /* Last Sample Point */
#define CAN_RX_SIGNAL           (CAN_MSTS_RXS)      /* CAN Rx Signal */

/** CAN mailbox data length control and time stamp register bits **/
#define CAN_TX_GLOBAL_TIME0     CAN_TMDT0_TGT       /* Transmit Global Time */
#define CAN_TX_GLOBAL_TIME1     CAN_TMDT1_TGT       /* Transmit Global Time */
#define CAN_TX_GLOBAL_TIME2     CAN_TMDT2_TGT       /* Transmit Global Time */

/** CAN Mailbox Transmit Request **/
#define CAN_TMIX_TXRQ       (CAN_TMI0_TXRQ | CAN_TMI1_TXRQ) /* Transmit mailbox request */

/** CAN Filter Master Register bits **/
#define CAN_FILTER_INIT     (CAN_FMC_FINITM) /* Filter init mode */

/** Time out for INAK bit */
#define INIAK_TIMEOUT ((uint32_t)0x0000FFFF)
/** Time out for SLAK bit */
#define SLPAK_TIMEOUT ((uint32_t)0x0000FFFF)


/** Mailboxes definition **/
#define CAN_TXSTS_MAILBOX0  ((uint8_t)0x00) /* CAN transmit mailbox number 0 */
#define CAN_TXSTS_MAILBOX1  ((uint8_t)0x01) /* CAN transmit mailbox number 1 */
#define CAN_TXSTS_MAILBOX2  ((uint8_t)0x02) /* CAN transmit mailbox number 2 */
#define CAN_TXSTS_NOMAILBOX ((uint8_t)0x04) /* CAN cell did not provide an empty mailbox */

#define CAN_MODE_MASK       (CAN_MSTS_INIAK | CAN_MSTS_SLPAK)

/** OperatingMode **/
#define CAN_NORMAL_MODE          ((uint8_t)0x00) /* normal mode */
#define CAN_LOOPBACK_MODE        ((uint8_t)0x01) /* loopback mode */
#define CAN_SILENT_MODE          ((uint8_t)0x02) /* silent mode */
#define CAN_SILENT_LOOPBACK_MODE ((uint8_t)0x03) /* loopback combined with silent mode */

/** CAN_operating_mode **/
#define CAN_OPERATING_INITMODE      ((uint8_t)0x00) /* Initialization mode */
#define CAN_OPERATING_NORMALMODE    ((uint8_t)0x01) /* Normal mode */
#define CAN_OPERATING_SLEEPMODE     ((uint8_t)0x02) /* sleep mode */
#define CAN_OPERATING_MODE_OFFSET   (REG_BIT30_OFFSET)

/** CAN_synchronisation_jump_width **/
#define CAN_RSJW_1TQ        ((uint8_t)0x00) /* 1 time quantum */
#define CAN_RSJW_2TQ        ((uint8_t)0x01) /* 2 time quantum */
#define CAN_RSJW_3TQ        ((uint8_t)0x02) /* 3 time quantum */
#define CAN_RSJW_4TQ        ((uint8_t)0x03) /* 4 time quantum */
#define CAN_RSJW_OFFSET     (REG_BIT24_OFFSET)

/** CAN_time_quantum_in_bit_segment_1 **/
#define CAN_TBS1_1TQ  ((uint8_t)0x00) /* 1 time quantum */
#define CAN_TBS1_2TQ  ((uint8_t)0x01) /* 2 time quantum */
#define CAN_TBS1_3TQ  ((uint8_t)0x02) /* 3 time quantum */
#define CAN_TBS1_4TQ  ((uint8_t)0x03) /* 4 time quantum */
#define CAN_TBS1_5TQ  ((uint8_t)0x04) /* 5 time quantum */
#define CAN_TBS1_6TQ  ((uint8_t)0x05) /* 6 time quantum */
#define CAN_TBS1_7TQ  ((uint8_t)0x06) /* 7 time quantum */
#define CAN_TBS1_8TQ  ((uint8_t)0x07) /* 8 time quantum */
#define CAN_TBS1_9TQ  ((uint8_t)0x08) /* 9 time quantum */
#define CAN_TBS1_10TQ ((uint8_t)0x09) /* 10 time quantum */
#define CAN_TBS1_11TQ ((uint8_t)0x0A) /* 11 time quantum */
#define CAN_TBS1_12TQ ((uint8_t)0x0B) /* 12 time quantum */
#define CAN_TBS1_13TQ ((uint8_t)0x0C) /* 13 time quantum */
#define CAN_TBS1_14TQ ((uint8_t)0x0D) /* 14 time quantum */
#define CAN_TBS1_15TQ ((uint8_t)0x0E) /* 15 time quantum */
#define CAN_TBS1_16TQ ((uint8_t)0x0F) /* 16 time quantum */
#define CAN_TBS1_OFFSET     (REG_BIT16_OFFSET)

/** CAN_time_quantum_in_bit_segment_2 **/
#define CAN_TBS2_1TQ ((uint8_t)0x00) /* 1 time quantum */
#define CAN_TBS2_2TQ ((uint8_t)0x01) /* 2 time quantum */
#define CAN_TBS2_3TQ ((uint8_t)0x02) /* 3 time quantum */
#define CAN_TBS2_4TQ ((uint8_t)0x03) /* 4 time quantum */
#define CAN_TBS2_5TQ ((uint8_t)0x04) /* 5 time quantum */
#define CAN_TBS2_6TQ ((uint8_t)0x05) /* 6 time quantum */
#define CAN_TBS2_7TQ ((uint8_t)0x06) /* 7 time quantum */
#define CAN_TBS2_8TQ ((uint8_t)0x07) /* 8 time quantum */
#define CAN_TBS2_OFFSET     (REG_BIT20_OFFSET)

/** CAN_filter_mode **/
#define CAN_FILTER_IDMASKMODE ((uint8_t)0x00) /* identifier/mask mode */
#define CAN_FILTER_IDLISTMODE ((uint8_t)0x01) /* identifier list mode */

/** CAN_filter_scale **/
#define CAN_FILTER_16BITSCALE ((uint8_t)0x00) /* Two 16-bit filters */
#define CAN_FILTER_32BITSCALE ((uint8_t)0x01) /* One 32-bit filter */

/** CAN_filter_FIFO **/
#define CAN_FILTER_FIFO0            ((uint8_t)0x00) /* Filter DATFIFO 0 assignment for filter x */
#define CAN_FILTER_FIFO1            ((uint8_t)0x01) /* Filter DATFIFO 1 assignment for filter x */

/** CAN_identifier_type **/
#define CAN_STANDARD_ID         ((uint32_t)0x00000000) /* Standard Id */
#define CAN_EXTENDED_ID         ((uint32_t)0x00000004) /* Extended Id */
#define CAN_FRX_ID_OFFSET       (REG_BIT16_OFFSET)
#define CAN_TMI_STDID_OFFSET    (REG_BIT21_OFFSET)
#define CAN_TMI_EXTID_OFFSET    (REG_BIT3_OFFSET)

/** CAN_remote_transmission_request **/
#define CAN_RTRQ_DATA    ((uint32_t)0x00000000) /* Data frame */
#define CAN_RTRQ_REMOTE  ((uint32_t)0x00000002) /* Remote frame */

/** CAN_receive_FIFO_number_constants **/
#define CAN_FIFO0 ((uint8_t)0x00) /* CAN DATFIFO 0 used to receive */
#define CAN_FIFO1 ((uint8_t)0x01) /* CAN DATFIFO 1 used to receive */

/** CAN_Error_Code_constants **/
#define CAN_ERRORCODE_NOERR           ((uint8_t)0x00)                   /* No Error */
#define CAN_ERRORCODE_STUFFERR        (CAN_ESTS_LEC_0)                  /* Stuff Error */
#define CAN_ERRORCODE_FORMERR         (CAN_ESTS_LEC_1)                  /* Form Error */
#define CAN_ERRORCODE_ACKERR          (CAN_ESTS_LEC_0 | CAN_ESTS_LEC_1) /* Acknowledgment Error */
#define CAN_ERRORCODE_BITRECESSIVEERR (CAN_ESTS_LEC_2)                  /* Bit Recessive Error */
#define CAN_ERRORCODE_BITDOMINANTERR  (CAN_ESTS_LEC_0 | CAN_ESTS_LEC_2) /* Bit Dominant Error */
#define CAN_ERRORCODE_CRCERR          (CAN_ESTS_LEC_1 | CAN_ESTS_LEC_2) /* CRC Error  */
#define CAN_ERRORCODE_SWSETERR        (CAN_ESTS_LEC)                    /* Software Set Error */

#define CAN_TX_ERROR_COUNT            (CAN_ESTS_TXEC) /* Least significant byte of the 9-bit Transmit Error Counter */
#define CAN_RX_ERROR_COUNT            (CAN_ESTS_RXEC) /* Receive Error Counter */
#define CAN_ESTS_RX_ERROR_OFFSET      (REG_BIT24_OFFSET)
#define CAN_ESTS_TX_ERROR_OFFSET      (REG_BIT16_OFFSET)

#define CAN_ERROR_WARN_FLAG (CAN_ESTS_EWGFL) /* Error Warning Flag */
#define CAN_ERROR_PASS_FLAG (CAN_ESTS_EPVFL) /* Error Passive Flag */
#define CAN_BUS_OFF_FLAG    (CAN_ESTS_BOFFL) /* Bus-Off Flag */

/*** CAN_flags ***/
/** If the flag is 0x3XXXXXXX, it means that it can be used with CAN_GetFlagSTS()
   and CAN_ClearFlag() functions. **/
/** If the flag is 0x1XXXXXXX, it means that it can only be used with CAN_GetFlagSTS() function.  **/

#define CAN_FLAG_MASK   ((uint32_t)0x000FFFFF)

/** Transmit Flags **/
#define CAN_FLAG_RQCPM0 ((uint32_t)0x38000001) /* Request MailBox0 Flag */
#define CAN_FLAG_RQCPM1 ((uint32_t)0x38000100) /* Request MailBox1 Flag */
#define CAN_FLAG_RQCPM2 ((uint32_t)0x38010000) /* Request MailBox2 Flag */

/** Receive Flags **/
#define CAN_FLAG_FFMP0  ((uint32_t)0x12000003) /* DATFIFO 0 Message Pending Flag */
#define CAN_FLAG_FFULL0 ((uint32_t)0x32000008) /* DATFIFO 0 Full Flag            */
#define CAN_FLAG_FFOVR0 ((uint32_t)0x32000010) /* DATFIFO 0 Overrun Flag         */
#define CAN_FLAG_FFMP1  ((uint32_t)0x14000003) /* DATFIFO 1 Message Pending Flag */
#define CAN_FLAG_FFULL1 ((uint32_t)0x34000008) /* DATFIFO 1 Full Flag            */
#define CAN_FLAG_FFOVR1 ((uint32_t)0x34000010) /* DATFIFO 1 Overrun Flag         */

/** Operating Mode Flags **/
#define CAN_FLAG_WKU  ((uint32_t)0x31000008) /* Wake up Flag */
#define CAN_FLAG_SLAK ((uint32_t)0x31000012) /* Sleep acknowledge Flag */
/** Note: When SLAK intterupt is disabled (SLKIE=0), no polling on SLAKI is possible.
         In this case the SLAK bit can be polled. **/

/** Error Flags **/
#define CAN_FLAG_EWGFL ((uint32_t)0x10F00001) /* Error Warning Flag   */
#define CAN_FLAG_EPVFL ((uint32_t)0x10F00002) /* Error Passive Flag   */
#define CAN_FLAG_BOFFL ((uint32_t)0x10F00004) /* Bus-Off Flag         */
#define CAN_FLAG_LEC   ((uint32_t)0x30F00070) /* Last error code Flag */

/** Flags in TSTS register */
#define CAN_FLAGS_TSTS ((uint32_t)0x08000000)
/** Flags in RFF1 register */
#define CAN_FLAGS_RFF1 ((uint32_t)0x04000000)
/** Flags in RFF0 register */
#define CAN_FLAGS_RFF0 ((uint32_t)0x02000000)
/** Flags in MSTS register */
#define CAN_FLAGS_MSTS ((uint32_t)0x01000000)
/** Flags in ESTS register */
#define CAN_FLAGS_ESTS ((uint32_t)0x00F00000)

/** CAN_interrupts **/
#define CAN_INT_TME    (CAN_INTE_TMEITE) /* Transmit mailbox empty Interrupt*/

/** Flags named as Interrupts : kept only for FW compatibility **/
#define CAN_INT_RQCPM0 (CAN_INT_TME)
#define CAN_INT_RQCPM1 (CAN_INT_TME)
#define CAN_INT_RQCPM2 (CAN_INT_TME)

/** Receive Interrupts **/
#define CAN_INT_FMP0 (CAN_INTE_FMPITE0) /* DATFIFO 0 message pending Interrupt*/
#define CAN_INT_FF0  (CAN_INTE_FFITE0) /* DATFIFO 0 full Interrupt*/
#define CAN_INT_FOV0 (CAN_INTE_FOVITE0) /* DATFIFO 0 overrun Interrupt*/
#define CAN_INT_FMP1 (CAN_INTE_FMPITE1) /* DATFIFO 1 message pending Interrupt*/
#define CAN_INT_FF1  (CAN_INTE_FFITE1) /* DATFIFO 1 full Interrupt*/
#define CAN_INT_FOV1 (CAN_INTE_FOVITE1) /* DATFIFO 1 overrun Interrupt*/

/** Operating Mode Interrupts **/
#define CAN_INT_WKU (CAN_INTE_WKUITE) /* Wake-up Interrupt*/
#define CAN_INT_SLK (CAN_INTE_SLKITE) /* Sleep acknowledge Interrupt*/

/** Error Interrupts **/
#define CAN_INT_EWG (CAN_INTE_EWGITE) /* Error warning Interrupt*/
#define CAN_INT_EPV (CAN_INTE_EPVITE) /* Error passive Interrupt*/
#define CAN_INT_BOF (CAN_INTE_BOFITE) /* Bus-off Interrupt*/
#define CAN_INT_LEC (CAN_INTE_LECITE) /* Last error code Interrupt*/
#define CAN_INT_ERR (CAN_INTE_ERRITE) /* Error Interrupt*/

/** Bit definition for CAN_TMDTx register **/
#define CAN_TMDTx_DLC       (CAN_TMDT0_DLC | CAN_TMDT1_DLC) /* Data Length Code */
#define CAN_TMDTx_DLC_MASK  (~CAN_TMDTx_DLC)

/** Bit definition for CAN_TSTS register **/
#define CAN_TX_MAILBOX_EMPTY0 (CAN_TSTS_TMEM0) /* Transmit Mailbox 0 Empty */
#define CAN_TX_MAILBOX_EMPTY1 (CAN_TSTS_TMEM1) /* Transmit Mailbox 1 Empty */
#define CAN_TX_MAILBOX_EMPTY2 (CAN_TSTS_TMEM2) /* Transmit Mailbox 2 Empty */

#define CAN_TX_MAILBOX_CODE   (CAN_TSTS_CODE)    /* Mailbox Code */
#define CAN_TX_MAILBOX_0      (CAN_TSTS_CODE_0)  /* Mailbox 0 */
#define CAN_TX_MAILBOX_1      (CAN_TSTS_CODE_1)  /* Mailbox 1 */

#define CAN_MAILBOX0_RQ_OK (CAN_TSTS_RQCPM0) /* Request Completed Mailbox0 */
#define CAN_MAILBOX0_TX_OK (CAN_TSTS_TXOKM0) /* Transmission OK of Mailbox0 */
#define CAN_MAILBOX1_RQ_OK (CAN_TSTS_RQCPM1) /* Request Completed Mailbox1 */
#define CAN_MAILBOX1_TX_OK (CAN_TSTS_TXOKM1) /* Transmission OK of Mailbox1 */
#define CAN_MAILBOX2_RQ_OK (CAN_TSTS_RQCPM2) /* Request Completed Mailbox2 */
#define CAN_MAILBOX2_TX_OK (CAN_TSTS_TXOKM2) /* Transmission OK of Mailbox 2 */

#define CAN_MAILBOX0_RQ_AB (CAN_TSTS_ABRQM0) /* Abort Request for Mailbox0 */
#define CAN_MAILBOX1_RQ_AB (CAN_TSTS_ABRQM1) /* Abort Request for Mailbox1 */
#define CAN_MAILBOX2_RQ_AB (CAN_TSTS_ABRQM2) /* Abort Request for Mailbox2 */

/** Bit definition for CAN_RMIx register **/
#define CAN_RMIx_RTRQ  (CAN_RMI0_RTRQ | CAN_RMI1_RTRQ) /* Remote Transmission Request */
#define CAN_RMIx_IDE   (CAN_RMI0_IDE | CAN_RMI1_IDE) /* Identifier Extension */
#define CAN_RMIx_EXTID (CAN_RMI0_EXTID | CAN_RMI1_EXTID) /* Extended Identifier */
#define CAN_RMIx_STDID (CAN_RMI0_STDID | CAN_RMI1_STDID) /* Standard Identifier or Extended Identifier */
#define CAN_EXTID_MASK (CAN_RMIx_EXTID | CAN_RMIx_STDID)
#define CAN_RMI_STDID_OFFSET    (REG_BIT21_OFFSET)
#define CAN_RMI_EXTID_OFFSET    (REG_BIT3_OFFSET)

/** CAN receive FIFO mailbox data register **/
#define CAN_RMDT_OFFSET             REG_BIT8_OFFSET
#define CAN_DATA_FIFO_MASK          ((CAN_RMDT0_FMI | CAN_RMDT1_FMI) >> CAN_RMDT_OFFSET)
#define CAN_RMDL_DATA1_OFFSET       REG_BIT8_OFFSET
#define CAN_RMDL_DATA2_OFFSET       REG_BIT16_OFFSET
#define CAN_RMDL_DATA3_OFFSET       REG_BIT24_OFFSET
#define CAN_RMDH_DATA5_OFFSET       REG_BIT8_OFFSET
#define CAN_RMDH_DATA6_OFFSET       REG_BIT16_OFFSET
#define CAN_RMDH_DATA7_OFFSET       REG_BIT24_OFFSET

/** Bit definition for CAN_RFFx register **/
#define CAN_FIFO0_PENDING           (CAN_RFF0_FFMP0) /* DATFIFO 0 Message Pending */
#define CAN_FIFO1_PENDING           (CAN_RFF1_FFMP1) /* DATFIFO 0 Message Pending */
#define CAN_FIFOX_PENDING_0         ((uint8_t)0x00)
#define CAN_FIFOX_PENDING_1         (CAN_RFF0_FFMP0_0)
#define CAN_FIFOX_PENDING_2         (CAN_RFF0_FFMP0_1)
#define CAN_FIFOX_PENDING_3         (CAN_RFF0_FFMP0)

#define CAN_RELEASE_FIFO_0 (CAN_RFF0_RFFOM0) /* Release DATFIFO 0 Output Mailbox */
#define CAN_RELEASE_FIFO_1 (CAN_RFF1_RFFOM1) /* Release DATFIFO 1 Output Mailbox */

#define CAN_FULL_FIFO_0 (CAN_RFF0_FFULL0) /* DATFIFO 0 Full */
#define CAN_OVER_FIFO_0 (CAN_RFF0_FFOVR0) /* DATFIFO 0 Overrun */
#define CAN_FULL_FIFO_1 (CAN_RFF1_FFULL1) /* DATFIFO 1 Full */
#define CAN_OVER_FIFO_1 (CAN_RFF1_FFOVR1) /* DATFIFO 1 Overrun */


/**  Function used to set the CAN configuration to the default reset state **/
void CAN_Reset(CAN_Module* CANx);

/** Initialization functions **/
void CAN_Sleep_Mode_Exit(CAN_Module* CANx);
void CAN_Initializes_Enable(CAN_Module* CANx);
void CAN_Initializes_Disable(CAN_Module* CANx);
void CAN_Initializes_Wait(CAN_Module* CANx);
void CAN_Initializes_Leave_Wait(CAN_Module* CANx);
void CAN_Time_Trigger_Mode_Enable(CAN_Module* CANx);
void CAN_Time_Trigger_Mode_Disable(CAN_Module* CANx);
void CAN_Bus_Off_Enable(CAN_Module* CANx);
void CAN_Bus_Off_Disable(CAN_Module* CANx);
void CAN_Wake_Up_Mode_Enable(CAN_Module* CANx);
void CAN_Wake_Up_Mode_Disable(CAN_Module* CANx);
void CAN_No_Retransmission_Enable(CAN_Module* CANx);
void CAN_No_Retransmission_Disable(CAN_Module* CANx);
void CAN_DATA_FIFO_Receive_Lock_Enable(CAN_Module* CANx);
void CAN_DATA_FIFO_Receive_Lock_Disable(CAN_Module* CANx);
void CAN_DATA_FIFO_Transmit_Priority_Enable(CAN_Module* CANx);
void CAN_DATA_FIFO_Transmit_Priority_Disable(CAN_Module* CANx);
void CAN_Bit_Timing_Set(CAN_Module* CANx, CAN_InitType* CAN_initializes_parameter);
CAN_Status CAN_Initializes(CAN_Module* CANx, CAN_InitType* CAN_initializes_parameter);

/** Filter Initialization functions **/
void CAN_Filter_Initializes_Enable(void);
void CAN_Filter_Initializes_Disable(void);
void CAN_Filter_Initializes(CAN_FilterInitType* CAN_filter_initializes_structure);

/** Configuration functions**/
void CAN_Structure_Initializes(CAN_InitType* CAN_initializes_parameter);
void CAN_Debug_Freeze_Enable(CAN_Module* CANx);
void CAN_Debug_Freeze_Disable(CAN_Module* CANx);
void CAN_Time_Stamp_Sent_Enable(CAN_Module* CANx);
void CAN_Time_Stamp_Sent_Disable(CAN_Module* CANx);

/** Transmit functions **/
uint8_t CAN_Transmit_Message_initializes(CAN_Module* CANx, CanTxMessage* transmit_message);
CAN_Tx_Status CAN_Transmit_Status_Get(CAN_Module* CANx, uint8_t mailbox_queue);
void CAN_Transmit_Message_Cancel(CAN_Module* CANx, uint8_t mailbox_queue);

/** Receive functions **/
void CAN_Message_Receive(CAN_Module* CANx, uint8_t FIFO_number, CanRxMessage* receive_message);
void CAN_FIFO_Release(CAN_Module* CANx, uint8_t FIFO_number);
uint8_t CAN_Message_Pending_Get(CAN_Module* CANx, uint8_t FIFO_number);

/** Operation modes functions **/
CAN_Status CAN_Operating_Mode_Select(CAN_Module* CANx, uint8_t CAN_operating_mode);
CAN_Status CAN_Sleep_Mode_Enter(CAN_Module* CANx);
CAN_Status CAN_Wake_Up_Enable(CAN_Module* CANx);

/** Error management functions **/
uint8_t CAN_Last_Error_Code_Get(CAN_Module* CANx);
uint8_t CAN_Receive_Error_Counter_Get(CAN_Module* CANx);
uint8_t CAN_LSB_Transmit_Error_Counter_Get(CAN_Module* CANx);

/** Interrupts and flags management functions **/
void CAN_Config_Interrupt_Enable(CAN_Module* CANx, uint32_t CAN_interrupt);
void CAN_Config_Interrupt_Disable(CAN_Module* CANx, uint32_t CAN_interrupt);
FlagStatus CAN_Flag_status_Get(CAN_Module* CANx, uint32_t CAN_flag);
void CAN_Flag_Status_Clear(CAN_Module* CANx, uint32_t CAN_flag);
INTStatus CAN_Interrupt_Status_Get(CAN_Module* CANx, uint32_t CAN_interrupt);
void CAN_Interrupt_Status_Clear(CAN_Module* CANx, uint32_t CAN_interrupt);



/************************************************************************************/
void CAN_Filter_Deactivation(uint32_t filter_position);
void CAN_Filter_Scale_16bit_Set(CAN_FilterInitType* CAN_filter_initializes_structure, \
                            uint32_t filter_position);
void CAN_Filter_Scale_32bit_Set(CAN_FilterInitType* CAN_filter_initializes_structure, \
                            uint32_t filter_position);
void CAN_Filter_Mode_Set(uint8_t filter_mode, uint32_t filter_position);
void CAN_Filter_DATA_FIFO_Assign(uint16_t filter_assign, uint32_t filter_position);
void CAN_Filter_Activate(uint32_t filter_position);

void CAN_Transmit_Message_ID_Config(CAN_Module* CANx, CanTxMessage* transmit_message, \
                                            uint8_t mailbox_queue);
void CAN_Transmit_Message_DLC_Config(CAN_Module* CANx, uint8_t data_length, \
                                            uint8_t mailbox_queue);
void CAN_Transmit_Message_Data_Config(CAN_Module* CANx, CanTxMessage* transmit_message, \
                                            uint8_t mailbox_queue);
void CAN_Transmit_Enable(CAN_Module* CANx, uint8_t mailbox_queue);


void CAN_Software_Reset(CAN_Module* CANx);
FlagStatus CAN_Transmit_Fail_Status_Get(CAN_Module* CANx,uint8_t mailbox_queue);
FlagStatus CAN_Arbitration_Lost_Status_Get(CAN_Module* CANx,uint8_t mailbox_queue);
FlagStatus CAN_Flag_Lowest_Priority_Get(CAN_Module* CANx,uint8_t mailbox_queue);
FlagStatus CAN_Flag_Transmit_Mailbox_Empty_Get(CAN_Module* CANx,uint8_t mailbox_queue);
FlagStatus CAN_Receive_Signal_Get(CAN_Module* CANx);
FlagStatus CAN_Last_Sample_Point_Get(CAN_Module* CANx);
FlagStatus CAN_Receive_Mode_Get(CAN_Module* CANx);
FlagStatus CAN_Transmit_Mode_Get(CAN_Module* CANx);
uint8_t CAN_Mailbox_Code_Get(CAN_Module* CANx);


#ifdef __cplusplus
}
#endif

#endif /* __N32G430_CAN_H__ */

