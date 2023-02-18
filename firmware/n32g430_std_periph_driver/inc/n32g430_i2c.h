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
*\*\file n32g430_i2c.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/
#ifndef __N32G430_I2C_H__
#define __N32G430_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

/**  N32G430_StdPeriph_Driver
 * 
 */

/** I2C Init structure definition **/

typedef struct
{
    uint32_t ClkSpeed; /* Specifies the clock frequency. */

    uint16_t BusMode; /* Specifies the I2C mode. */

    uint16_t DutyCycle; /* Specifies the I2C duty cycle. */

    uint16_t OwnAddr1; /* Specifies the first device own address. */

    uint16_t AckEnable; /* Enables or disables the acknowledgement. */

    uint16_t AddrMode; /* Specifies if 7-bit or 10-bit address is acknowledged. */
} I2C_InitType;



#define APB1_FREQ_MAX_VALUE   (32) /*32M*/
#define CLK_SPEED_100K        (100000)
#define CLK_SPEED_400K        (400000)
#define CLK_SPEED_1M          (1000000)
#define SM_CLKCTRL_LOW_LIMIT  (0x04)
#define FM_CLKCTRL_LOW_LIMIT  (0x01)
#define SM_TRISE_100K         (1000) /*1000ns*/
#define FM_TRISE_400K         (300)  /*300ns*/
#define FM_TRISE_1M           (120)  /*120ns*/

/** Register shift macro definition **/
#define  RCC_FLAG_STS2_OFFSET     (REG_BIT16_OFFSET)
#define  RCC_FLAG_GET_OFFSET      (REG_BIT28_OFFSET)
#define  RCC_TMRISE_SDADFW_OFFSET (REG_BIT18_OFFSET)
#define  RCC_TMRISE_SCLDFW_OFFSET (REG_BIT22_OFFSET)
#define  RCC_SDAAFW_SCLAFW_OFFSET (REG_BIT3_OFFSET)

#define I2C_REG_BIT_MASK      ((uint16_t)0x0000)

/* I2C EN mask */
#define I2C_EN_SET      (I2C_CTRL1_EN)
#define I2C_EN_RESET    (~I2C_CTRL1_EN)

/* I2C START mask */
#define I2C_START_SET   (I2C_CTRL1_STARTGEN)
#define I2C_START_RESET (~I2C_CTRL1_STARTGEN)

/* I2C STOP mask */
#define I2C_STOP_SET    (I2C_CTRL1_STOPGEN)
#define I2C_STOP_RESET  (~I2C_CTRL1_STOPGEN)

/* I2C ACK mask */
#define I2C_ACK_SET     (I2C_CTRL1_ACKEN)
#define I2C_ACK_RESET   (~I2C_CTRL1_ACKEN)

/* I2C ENGC mask */
#define I2C_GCEN_SET    (I2C_CTRL1_GCEN)
#define I2C_GCEN_RESET  (~I2C_CTRL1_GCEN)

/* I2C SWRST mask */
#define I2C_SWRESET_SET   (I2C_CTRL1_SWRESET)
#define I2C_SWRESET_RESET (~I2C_CTRL1_SWRESET)

/* I2C PEC mask */
#define I2C_PEC_SET        (I2C_CTRL1_PEC)
#define I2C_PEC_RESET      (~I2C_CTRL1_PEC)

/* I2C ENPEC mask */
#define I2C_PECEN_SET      (I2C_CTRL1_PECEN)
#define I2C_PECEN_RESET    (~I2C_CTRL1_PECEN)

/* I2C ENARP mask */
#define I2C_ARPEN_SET      (I2C_CTRL1_ARPEN)
#define I2C_ARPEN_RESET    (~I2C_CTRL1_ARPEN)

/* I2C NOSTRETCH mask */
#define I2C_NOEXTEND_SET   (I2C_CTRL1_NOEXTEND)
#define I2C_NOEXTEND_RESET (~I2C_CTRL1_NOEXTEND)

/* I2C registers Masks */
#define I2C_BUSMODE_CLR_MASK  (~(I2C_CTRL1_SMBMODE | I2C_CTRL1_SMBTYPE))
#define I2C_ACKEN_CLR_MASK    (~(I2C_CTRL1_ACKEN))
#define I2C_ADDRMODE_CLR_MASK (~(I2C_OADDR1_ADDRMODE))
#define I2C_OADDR_CLR_MASK    (~(I2C_OADDR1_ADDR0 | I2C_OADDR1_ADDR1_7 | I2C_OADDR1_ADDR8_9))

/* I2C DMAEN mask */
#define I2C_DMAEN_SET     (I2C_CTRL2_DMAEN)
#define I2C_DMAEN_RESET   (~I2C_CTRL2_DMAEN)

/* I2C LAST mask */
#define I2C_DMALAST_SET   (I2C_CTRL2_DMALAST)
#define I2C_DMALAST_RESET (~I2C_CTRL2_DMALAST)

/* I2C FREQ mask */
#define I2C_CLKFREQ_RESET (~I2C_CTRL2_CLKFREQ)

/* I2C ADD0 mask */
#define I2C_ADDR0_SET    (I2C_OADDR1_ADDR0)
#define I2C_ADDR0_RESET  (~I2C_OADDR1_ADDR0)

/* I2C ENDUAL mask */
#define I2C_DUALEN_SET   (((uint16_t)I2C_OADDR2_DUALEN))
#define I2C_DUALEN_RESET (~((uint16_t)I2C_OADDR2_DUALEN))

/* I2C ADD2 mask */
#define I2C_ADDR2_SET    ((uint16_t)I2C_OADDR2_ADDR2)
#define I2C_ADDR2_RESET  (~((uint16_t)I2C_OADDR2_ADDR2))

/* I2C F/S mask */
#define I2C_FSMODE_SET  (I2C_CLKCTRL_FSMODE)

/* I2C CHCFG mask */
#define I2C_CLKCTRL_SET (I2C_CLKCTRL_CLKCTRL)

/* I2C TMRISE mask */
#define I2C_SDADFW_MASK  (~I2C_TMRISE_SDADFW)
#define I2C_SCLDFW_MASK  (~I2C_TMRISE_SCLDFW)
#define I2C_SDAAFW_MASK  (~I2C_TMRISE_SDAAFW)
#define I2C_SCLAFW_MASK  (~I2C_TMRISE_SCLAFW)

#define I2C_SDAAFENN_SET  (I2C_TMRISE_SDAAFENN)
#define I2C_SDAAFENN_RESET  (~I2C_TMRISE_SDAAFENN)

#define I2C_SCLAFENN_SET  (I2C_TMRISE_SCLAFENN)
#define I2C_SCLAFENN_RESET  (~I2C_TMRISE_SCLAFENN)

#define I2C_TMRISE_MASK  (I2C_TMRISE_TMRISE)


/* I2C FLAG mask */
#define FLAG_MASK ((uint32_t)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define INTEN_MASK ((uint32_t)0x07000000)


/**  I2C_BusMode **/

#define I2C_BUSMODE_I2C        (I2C_REG_BIT_MASK)
#define I2C_BUSMODE_SMBDEVICE  (I2C_CTRL1_SMBMODE)
#define I2C_BUSMODE_SMBHOST    (I2C_CTRL1_SMBMODE | I2C_CTRL1_SMBTYPE)


/**  I2C_duty_cycle **/
#define I2C_SMDUTYCYCLE_1       (I2C_REG_BIT_MASK) /* I2C standard mode Tlow/Thigh = 1/1 */
#define I2C_FMDUTYCYCLE_16_9    (I2C_CLKCTRL_DUTY) /* I2C fast mode Tlow/Thigh = 16/9 */
#define I2C_FMDUTYCYCLE_2       (~I2C_CLKCTRL_DUTY) /* I2C fast mode Tlow/Thigh = 2 */


/**  I2C_acknowledgement **/

#define I2C_ACKEN               (I2C_CTRL1_ACKEN)
#define I2C_ACKDIS              (I2C_REG_BIT_MASK)


/**  I2C_transfer_direction **/

#define I2C_DIRECTION_SEND          ((uint8_t)0x00)
#define I2C_DIRECTION_RECV          ((uint8_t)0x01)


/**  I2C_acknowledged_address **/
/* Bit 14 Should be kept at 1 by software*/
#define I2C_ADDR_MODE_7BIT    (((uint16_t)0x4000) | I2C_REG_BIT_MASK) 
#define I2C_ADDR_MODE_10BIT   (((uint16_t)0x4000) | I2C_OADDR1_ADDRMODE) 

/**  I2C_registers **/

#define I2C_REG_CTRL1   ((uint8_t)0x00)
#define I2C_REG_CTRL2   ((uint8_t)0x04)
#define I2C_REG_OADDR1  ((uint8_t)0x08)
#define I2C_REG_OADDR2  ((uint8_t)0x0C)
#define I2C_REG_DAT     ((uint8_t)0x10)
#define I2C_REG_STS1    ((uint8_t)0x14)
#define I2C_REG_STS2    ((uint8_t)0x18)
#define I2C_REG_CLKCTRL ((uint8_t)0x1C)
#define I2C_REG_TMRISE  ((uint8_t)0x20)

/**  I2C_SMBus_alert_pin_level **/

#define I2C_SMBALERT_LOW        (I2C_CTRL1_SMBALERT)
#define I2C_SMBALERT_HIGH       (~I2C_CTRL1_SMBALERT)

/**  I2C_PEC_position **/

#define I2C_PEC_POS_NEXT         (I2C_CTRL1_ACKPOS)
#define I2C_PEC_POS_CURRENT      (~I2C_CTRL1_ACKPOS)

/**  I2C_NCAK_position **/

#define I2C_NACK_POS_NEXT         (I2C_CTRL1_ACKPOS)
#define I2C_NACK_POS_CURRENT      (~I2C_CTRL1_ACKPOS)

/**  I2C_Analog_Filter_Width **/

#define I2C_ANALOG_FILTER_WIDTH_5NS   ((uint32_t)0x00000000)
#define I2C_ANALOG_FILTER_WIDTH_15NS  (I2C_TMRISE_SDAAFW_0)
#define I2C_ANALOG_FILTER_WIDTH_25NS  (I2C_TMRISE_SDAAFW_1)
#define I2C_ANALOG_FILTER_WIDTH_35NS  (I2C_TMRISE_SDAAFW_0|I2C_TMRISE_SDAAFW_1)

/**  I2C_interrupts_definition **/

#define I2C_INT_BUF        (I2C_CTRL2_BUFINTEN)
#define I2C_INT_EVENT      (I2C_CTRL2_EVTINTEN)
#define I2C_INT_ERR        (I2C_CTRL2_ERRINTEN)

/**  I2C_interrupts_definition **/

#define I2C_INT_SMBALERT (((uint32_t)0x01000000) | ((uint32_t)I2C_STS1_SMBALERT))
#define I2C_INT_TIMOUT   (((uint32_t)0x01000000) | ((uint32_t)I2C_STS1_TIMOUT))
#define I2C_INT_PECERR   (((uint32_t)0x01000000) | ((uint32_t)I2C_STS1_PECERR))
#define I2C_INT_OVERRUN  (((uint32_t)0x01000000) | ((uint32_t)I2C_STS1_OVERRUN))
#define I2C_INT_ACKFAIL  (((uint32_t)0x01000000) | ((uint32_t)I2C_STS1_ACKFAIL))
#define I2C_INT_ARLOST   (((uint32_t)0x01000000) | ((uint32_t)I2C_STS1_ARLOST))
#define I2C_INT_BUSERR   (((uint32_t)0x01000000) | ((uint32_t)I2C_STS1_BUSERR))
#define I2C_INT_TXDATE   (((uint32_t)0x06000000) | ((uint32_t)I2C_STS1_TXDATE))
#define I2C_INT_RXDATNE  (((uint32_t)0x06000000) | ((uint32_t)I2C_STS1_RXDATNE))
#define I2C_INT_STOPF    (((uint32_t)0x02000000) | ((uint32_t)I2C_STS1_STOPF))
#define I2C_INT_ADDR10F  (((uint32_t)0x02000000) | ((uint32_t)I2C_STS1_ADDR10F))
#define I2C_INT_BYTEF    (((uint32_t)0x02000000) | ((uint32_t)I2C_STS1_BSF))
#define I2C_INT_ADDRF    (((uint32_t)0x02000000) | ((uint32_t)I2C_STS1_ADDRF))
#define I2C_INT_STARTBF  (((uint32_t)0x02000000) | ((uint32_t)I2C_STS1_STARTBF))

/**  I2C_flags_definition **/

/** STS2 register flags **/

#define I2C_FLAG_DUALFLAG  (((uint32_t)I2C_STS2_DUALFLAG)<<16)
#define I2C_FLAG_SMBHADDR  (((uint32_t)I2C_STS2_SMBHADDR)<<16)
#define I2C_FLAG_SMBDADDR  (((uint32_t)I2C_STS2_SMBDADDR)<<16)
#define I2C_FLAG_GCALLADDR (((uint32_t)I2C_STS2_GCALLADDR)<<16)
#define I2C_FLAG_TRF       (((uint32_t)I2C_STS2_TRF)<<16)
#define I2C_FLAG_BUSY      (((uint32_t)I2C_STS2_BUSY)<<16)
#define I2C_FLAG_MSMODE    (((uint32_t)I2C_STS2_MSMODE)<<16)

/** STS1 register flags **/

#define I2C_FLAG_SMBALERT (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_SMBALERT))
#define I2C_FLAG_TIMOUT   (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_TIMOUT))
#define I2C_FLAG_PECERR   (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_PECERR))
#define I2C_FLAG_OVERRUN  (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_OVERRUN))
#define I2C_FLAG_ACKFAIL  (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_ACKFAIL))
#define I2C_FLAG_ARLOST   (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_ARLOST))
#define I2C_FLAG_BUSERR   (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_BUSERR))
#define I2C_FLAG_TXDATE   (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_TXDATE))
#define I2C_FLAG_RXDATNE  (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_RXDATNE))
#define I2C_FLAG_STOPF    (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_STOPF))
#define I2C_FLAG_ADDR10F  (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_ADDR10F))
#define I2C_FLAG_BYTEF    (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_BSF))
#define I2C_FLAG_ADDRF    (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_ADDRF))
#define I2C_FLAG_STARTBF  (((uint32_t)0x10000000) | ((uint32_t)I2C_STS1_STARTBF))


/**  I2C_Events **/

/** I2C Master Events (Events grouped in order of communication) **/
/**
*\*\brief  Communication start
*\*\After sending the START condition (I2C_Generate_Start_Enable() function) the master
*\*\has to wait for this event. It means that the Start condition has been correctly
*\*\released on the I2C bus (the bus is free, no other devices is communicating).
**/

/* MSMODE */ 
#define I2C_ROLE_MASTER (((uint32_t)I2C_STS2_MSMODE)<<16) 
/* EV5 */
/* BUSY, MSMODE and STARTBF flag*/
#define I2C_EVT_MASTER_MODE_FLAG (((uint32_t)I2C_STS1_STARTBF)\
                                |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_MSMODE))<<16))
 

/**
*\*\brief  Address Acknowledge
*\*\After checking on EV5 (start condition correctly released on the bus), the
*\*\master sends the address of the slave(s) with which it will communicate
*\*\(I2C_7bit_Addr_Send() function, it also determines the direction of the communication:
*\*\Master transmitter or Receiver). Then the master has to wait that a slave acknowledges
*\*\his address. If an acknowledge is sent on the bus, one of the following events will
*\*\be set:
*\*\ 1) In case of Master Receiver (7-bit addressing): the I2C_EVT_MASTER_RXMODE_FLAG
*\*\    event is set.
*\*\ 2) In case of Master Transmitter (7-bit addressing): the I2C_EVT_MASTER_TXMODE_FLAG
*\*\    is set
*\*\ 3) In case of 10-Bit addressing mode, the master (just after generating the START
*\*\ and checking on EV5) has to send the header of 10-bit addressing mode (I2C_Data_Send()
*\*\ function). Then master should wait on EV9. It means that the 10-bit addressing
*\*\ header has been correctly sent on the bus. Then master should send the second part of
*\*\ the 10-bit address (LSB) using the function I2C_7bit_Addr_Send(). Then master
*\*\ should wait for event EV6.
 **/

/* --EV6 */
/* BUSY, MSMODE, ADDRF, TXDATE and TRF flags */
#define I2C_EVT_MASTER_TXMODE_FLAG (((uint32_t)I2C_STS1_ADDRF)|((uint32_t)I2C_STS1_TXDATE)\
                                  |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_MSMODE)|((uint32_t)I2C_STS2_TRF))<<16)) 
/* BUSY, MSMODE and ADDRF flags */
#define I2C_EVT_MASTER_RXMODE_FLAG (((uint32_t)I2C_STS1_ADDRF)\
                                  |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_MSMODE))<<16)) 
/* --EV9 */
/* BUSY, MSMODE and ADD10RF flags */
#define I2C_EVT_MASTER_MODE_ADDRESS10_FLAG (((uint32_t)I2C_STS1_ADDR10F)\
                                          |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_MSMODE))<<16))  

/**
*\*\brief Communication events
*\*\If a communication is established (START condition generated and slave address
*\*\acknowledged) then the master has to check on one of the following events for
*\*\communication procedures:
*\*\1) Master Receiver mode: The master has to wait on the event EV7 then to read
*\*\   the data received from the slave (I2C_Data_Recv() function).
*\*\2) Master Transmitter mode: The master has to send data (I2C_Data_Send()
*\*\   function) then to wait on event EV8 or EV8_2.
*\*\   These two events are similar:
*\*\    - EV8 means that the data has been written in the data register and is
*\*\      being shifted out.
*\*\    - EV8_2 means that the data has been physically shifted out and output
*\*\      on the bus.
*\*\    In most cases, using EV8 is sufficient for the application.
*\*\    Using EV8_2 leads to a slower communication but ensure more reliable test.
*\*\    EV8_2 is also more suitable than EV8 for testing on the last data transmission
*\*\    (before Stop condition generation).
*\*\note In case the  user software does not guarantee that this event EV7 is
*\*\ managed before the current byte end of transfer, then user may check on EV7
*\*\ and BSF flag at the same time (ie. (I2C_EVT_MASTER_DATA_RECVD_FLAG | I2C_FLAG_BYTEF)).
*\*\ In this case the communication may be slower.
 **/

/* Master RECEIVER mode -----------------------------*/
/* --EV7 */
/* BUSY, MSMODE and RXDATNE flags */
#define I2C_EVT_MASTER_DATA_RECVD_FLAG (((uint32_t)I2C_STS1_RXDATNE)\
                                       |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_MSMODE))<<16)) 
                                       
/* EV7x shifter register full */
/* BUSY, MSMODE, BSF and RXDATNE flags */
#define I2C_EVT_MASTER_DATA_RECVD_BSF_FLAG (((uint32_t)I2C_STS1_RXDATNE)|((uint32_t)I2C_STS1_BSF)\
                                          |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_MSMODE))<<16))

/* Master TRANSMITTER mode --------------------------*/
/* --EV8 */
/* TRF, BUSY, MSMODE, TXDATE flags */
#define I2C_EVT_MASTER_DATA_SENDING (((uint32_t)I2C_STS1_TXDATE)\
                  |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_MSMODE)|((uint32_t)I2C_STS2_TRF))<<16)) 
/* --EV8_2 */
/* TRF, BUSY, MSMODE, TXDATE and BSF flags */
#define I2C_EVT_MASTER_DATA_SENDED (((uint32_t)I2C_STS1_BSF)|((uint32_t)I2C_STS1_TXDATE)\
                  |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_MSMODE)|((uint32_t)I2C_STS2_TRF))<<16)) 

/*========================================

                     I2C Slave Events (Events grouped in order of communication)
                                                        ==========================================*/

/**
*\*\brief  Communication start events
*\*\Wait on one of these events at the start of the communication. It means that
*\*\the I2C peripheral detected a Start condition on the bus (generated by master
*\*\device) followed by the peripheral address. The peripheral generates an ACK
*\*\condition on the bus (if the acknowledge feature is enabled through function
*\*\I2C_ConfigAck()) and the events listed above are set :
*\*\1) In normal case (only one address managed by the slave), when the address
*\*\  sent by the master matches the own address of the peripheral (configured by
*\*\  OwnAddr1 field) the I2C_EVENT_SLAVE_XXX_ADDRESS_MATCHED event is set
*\*\  (where XXX could be TRANSMITTER or RECEIVER).
*\*\2) In case the address sent by the master matches the second address of the
*\*\  peripheral (configured by the function I2C_ConfigOwnAddr2() and enabled
*\*\  by the function I2C_EnableDualAddr()) the events I2C_EVENT_SLAVE_XXX_SECONDADDRESS_MATCHED
*\*\  (where XXX could be TRANSMITTER or RECEIVER) are set.
*\*\3) In case the address sent by the master is General Call (address 0x00) and
*\*\  if the General Call is enabled for the peripheral (using function I2C_EnableGeneralCall())
*\*\  the following event is set I2C_EVT_SLAVE_GCALLADDR_MATCHED.
 **/

/* --EV1  (all the events below are variants of EV1) */
/* 1) Case of One Single Address managed by the slave */
 /* BUSY and ADDRF flags */
#define I2C_EVT_SLAVE_RECV_ADDR_MATCHED (((uint32_t)I2C_STS1_ADDRF)\
                                       |((((uint32_t)I2C_STS2_BUSY))<<16)) 
 /* TRF, BUSY, TXDATE and ADDRF flags */
#define I2C_EVT_SLAVE_SEND_ADDR_MATCHED (((uint32_t)I2C_STS1_TXDATE)|((uint32_t)I2C_STS1_ADDRF)\
                                       |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_TRF))<<16))

/* 2) Case of Dual address managed by the slave */
 /* DUALF and BUSY flags */
#define I2C_EVT_SLAVE_RECV_ADDR2_MATCHED ((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_DUALFLAG))<<16) 
 /* DUALF, TRF, BUSY and TXDATE flags */
#define I2C_EVT_SLAVE_SEND_ADDR2_MATCHED (((uint32_t)I2C_STS1_TXDATE)\
               |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_DUALFLAG)|((uint32_t)I2C_STS2_TRF))<<16))

/* 3) Case of General Call enabled for the slave */
 /* GENCALL and BUSY flags */
#define I2C_EVT_SLAVE_GCALLADDR_MATCHED ((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_GCALLADDR))<<16) 

/**
*\*\brief  Communication events
*\*\Wait on one of these events when EV1 has already been checked and:
*\*\- Slave RECEIVER mode:
*\*\    - EV2: When the application is expecting a data byte to be received.
*\*\    - EV4: When the application is expecting the end of the communication: master
*\*\      sends a stop condition and data transmission is stopped.
*\*\- Slave Transmitter mode:
*\*\   - EV3: When a byte has been transmitted by the slave and the application is expecting
*\*\     the end of the byte transmission. The two events I2C_EVT_SLAVE_DATA_SENDED and
*\*\     I2C_EVT_SLAVE_DATA_SENDING are similar. The second one can optionally be
*\*\     used when the user software doesn't guarantee the EV3 is managed before the
*\*\     current byte end of transfer.
*\*\   - EV3_2: When the master sends a NACK in order to tell slave that data transmission
*\*\     shall end (before sending the STOP condition). In this case slave has to stop sending
*\*\     data bytes and expect a Stop condition on the bus.
*\*\note In case the  user software does not guarantee that the event EV2 is
*\*\ managed before the current byte end of transfer, then user may check on EV2
*\*\ and BSF flag at the same time (ie. (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_BYTEF)).
*\*\In this case the communication may be slower.
 **/

/* Slave RECEIVER mode --------------------------*/
/* --EV2 */
 /* BUSY and RXDATNE flags */
#define I2C_EVT_SLAVE_DATA_RECVD (((uint32_t)I2C_STS1_RXDATNE)\
                                |((((uint32_t)I2C_STS2_BUSY))<<16))  
/* --EV2x */
 /* no BUSY and RXDATNE flags */
#define I2C_EVT_SLAVE_DATA_RECVD_NOBUSY ((uint32_t)I2C_STS1_RXDATNE)
/* --EV4  */
 /* STOPF flag */
#define I2C_EVT_SLAVE_STOP_RECVD ((uint32_t)I2C_STS1_STOPF)

/* Slave TRANSMITTER mode -----------------------*/
/* --EV3 */
 /* TRF, BUSY, TXDATE and BSF flags */
#define I2C_EVT_SLAVE_DATA_SENDED  (((uint32_t)I2C_STS1_BSF)|((uint32_t)I2C_STS1_TXDATE)\
                                  |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_TRF))<<16)) 
 /* TRF, BUSY and TXDATE flags */
#define I2C_EVT_SLAVE_DATA_SENDING (((uint32_t)I2C_STS1_TXDATE)\
                                  |((((uint32_t)I2C_STS2_BUSY)|((uint32_t)I2C_STS2_TRF))<<16)) 
/* --EV3_2 */
 /* AF flag */
#define I2C_EVT_SLAVE_ACK_MISS ((uint32_t)I2C_STS1_ACKFAIL)

/*===========================      End of Events Description           ==========================================*/


void I2C_Reset(I2C_Module* I2Cx);
void I2C_Initializes(I2C_Module* I2Cx, I2C_InitType* I2C_InitParam);
void I2C_Clock_Speed_Config(I2C_Module* I2Cx, uint32_t clk_speed, uint16_t duty_cycle);
void I2C_Bus_Mode_Config(I2C_Module* I2Cx, uint16_t mode);
void I2C_Acknowledgement_Config(I2C_Module* I2Cx, uint16_t ack);
void I2C_Addressing_Mode_Config(I2C_Module* I2Cx, uint16_t mode);
void I2C_Own_Addr1_Config(I2C_Module* I2Cx, uint16_t addr1);
void I2C_Initializes_Structure(I2C_InitType* I2C_InitStruct);
void I2C_ON(I2C_Module* I2Cx);
void I2C_OFF(I2C_Module* I2Cx);
void I2C_DMA_Transfer_Enable(I2C_Module* I2Cx);
void I2C_DMA_Transfer_Disable(I2C_Module* I2Cx);
void I2C_DMA_Last_Transfer_Enable(I2C_Module* I2Cx);
void I2C_DMA_Last_Transfer_Disable(I2C_Module* I2Cx);
void I2C_Generate_Start_Enable(I2C_Module* I2Cx);
void I2C_Generate_Start_Disable(I2C_Module* I2Cx);
void I2C_Generate_Stop_Enable(I2C_Module* I2Cx);
void I2C_Generate_Stop_Disable(I2C_Module* I2Cx);
void I2C_Acknowledg_Enable(I2C_Module* I2Cx);
void I2C_Acknowledg_Disable(I2C_Module* I2Cx);
void I2C_Own_Addr2_Set(I2C_Module* I2Cx, uint8_t address);
void I2C_Dual_Addr_Enable(I2C_Module* I2Cx);
void I2C_Dual_Addr_Disable(I2C_Module* I2Cx);
void I2C_General_Call_Enable(I2C_Module* I2Cx);
void I2C_General_Call_Disable(I2C_Module* I2Cx);
void I2C_Interrupts_Enable(I2C_Module* I2Cx, uint16_t I2C_IT);
void I2C_Interrupts_Disable(I2C_Module* I2Cx, uint16_t I2C_IT);
void I2C_Data_Send(I2C_Module* I2Cx, uint8_t data);
uint8_t I2C_Data_Recv(I2C_Module* I2Cx);
void I2C_7bit_Addr_Send(I2C_Module* I2Cx, uint8_t address, uint8_t mode);
uint16_t I2C_Register_Value_Get(I2C_Module* I2Cx, uint8_t I2C_Register);
void I2C_Software_Reset_Enable(I2C_Module* I2Cx);
void I2C_Software_Reset_Disable(I2C_Module* I2Cx);
void I2C_NACK_Position_Set(I2C_Module* I2Cx, uint16_t position);
void I2C_SMBus_Alert_Pin_Set(I2C_Module* I2Cx, uint16_t polarity);
void I2C_PEC_Send_Enable(I2C_Module* I2Cx);
void I2C_PEC_Send_Disable(I2C_Module* I2Cx);
void I2C_PEC_Position_Set(I2C_Module* I2Cx, uint16_t position);
void I2C_PEC_Compute_Enable(I2C_Module* I2Cx);
void I2C_PEC_Compute_Disable(I2C_Module* I2Cx);
uint8_t I2C_PEC_Get(I2C_Module* I2Cx);
void I2C_ARP_Enable(I2C_Module* I2Cx);
void I2C_ARP_Disable(I2C_Module* I2Cx);
void I2C_Extend_Clock_Enable(I2C_Module* I2Cx);
void I2C_Extend_Clock_Disable(I2C_Module* I2Cx);
void I2C_Fast_Mode_Duty_Cycle_Set(I2C_Module* I2Cx, uint16_t duty_cycle);
void I2C_SDA_Digital_Filter_Width_Set(I2C_Module* I2Cx, uint8_t width);
void I2C_SCL_Digital_Filter_Width_Set(I2C_Module* I2Cx, uint8_t width);
void I2C_SDA_Analog_Filter_Width_Set(I2C_Module* I2Cx, uint32_t width);
void I2C_SDA_Analog_Filter_Enable(I2C_Module* I2Cx);
void I2C_SDA_Analog_Filter_Disable(I2C_Module* I2Cx);
void I2C_SCL_Analog_Filter_Width_Set(I2C_Module* I2Cx, uint32_t width);
void I2C_SCL_Analog_Filter_Enable(I2C_Module* I2Cx);
void I2C_SCL_Analog_Filter_Disable(I2C_Module* I2Cx);
/**
*\*\name I2C State Monitoring Functions
*\*\fun  This I2C driver provides three different ways for I2C state monitoring
*\*\     depending on the application requirements and constraints:
*\*\
*\*\ 1) Basic state monitoring:
*\*\    Using I2C_Event_Check() function:
*\*\    It compares the status registers (STS1 and STS2) content to a given event
*\*\    (can be the combination of one or more flags).
*\*\    It returns SUCCESS if the current status includes the given flags
*\*\    and returns ERROR if one or more flags are missing in the current status.
*\*\    - When to use:
*\*\      - This function is suitable for most applications as well as for startup
*\*\      activity since the events are fully described in the product reference manual.
*\*\      - It is also suitable for users who need to define their own events.
*\*\    - Limitations:
*\*\      - If an error occurs (ie. error flags are set besides to the monitored flags),
*\*\        the I2C_Event_Check() function may return SUCCESS despite the communication
*\*\        hold or corrupted real state.
*\*\        In this case, it is advised to use error interrupts to monitor the error
*\*\        events and handle them in the interrupt IRQ handler.
*\*\
*\*\        note:
*\*\        For error management, it is advised to use the following functions:
*\*\          - I2C_ConfigInt() to configure and enable the error interrupts (I2C_INT_ERR).
*\*\          - I2Cx_ER_IRQHandler() which is called when the error interrupt occurs.
*\*\            Where x is the peripheral instance (I2C1, I2C2 ...)
*\*\          - I2C_Flag_Status_Get() or I2C_GetIntStatus() to be called into I2Cx_ER_IRQHandler()
*\*\            in order to determine which error occurred.
*\*\          - I2C_Flag_Status_Clear() or I2C_ClrIntPendingBit() and/or I2C_EnableSoftwareReset()
*\*\            and/or I2C_Generate_Stop_Enable() in order to clear the error flag and source,
*\*\            and return to correct communication status.
*\*\
*\*\
*\*\  2) Advanced state monitoring:
*\*\     Using the function I2C_Last_Event_Get() which returns the image of both status
*\*\     registers in a single word (uint32_t) (Status Register 2 value is shifted left
*\*\     by 16 bits and concatenated to Status Register 1).
*\*\     - When to use:
*\*\       - This function is suitable for the same applications above but it allows to
*\*\         overcome the limitations of I2C_Flag_Status_Get() function (see below).
*\*\         The returned value could be compared to events already defined in the
*\*\         library (n32g430_i2c.h) or to custom values defined by user.
*\*\       - This function is suitable when multiple flags are monitored at the same time.
*\*\       - At the opposite of I2C_Event_Check() function, this function allows user to
*\*\         choose when an event is accepted (when all events flags are set and no
*\*\         other flags are set or just when the needed flags are set like
*\*\         I2C_Event_Check() function).
*\*\     - Limitations:
*\*\       - User may need to define his own events.
*\*\       - Same remark concerning the error management is applicable for this
*\*\         function if user decides to check only regular communication flags (and
*\*\         ignores error flags).
*\*\
*\*\
*\*\  3) Flag-based state monitoring:
*\*\     Using the function I2C_Flag_Status_Get() which simply returns the status of
*\*\     one single flag (ie. I2C_FLAG_RXDATNE ...).
*\*\     - When to use:
*\*\        - This function could be used for specific applications or in debug phase.
*\*\        - It is suitable when only one flag checking is needed (most I2C events
*\*\          are monitored through multiple flags).
*\*\     - Limitations:
*\*\        - When calling this function, the Status register is accessed. Some flags are
*\*\          cleared when the status register is accessed. So checking the status
*\*\          of one Flag, may clear other ones.
*\*\        - Function may need to be called twice or more in order to monitor one
*\*\          single event.
*\*\
**/

/** Basic state monitoring **/
ErrorStatus I2C_Event_Check(I2C_Module* I2Cx, uint32_t I2C_event);

/** Advanced state monitoring **/
uint32_t I2C_Last_Event_Get(I2C_Module* I2Cx);
/** Flag-based state monitoring **/
FlagStatus I2C_Flag_Status_Get(I2C_Module* I2Cx, uint32_t I2C_flag);

void I2C_Flag_Status_Clear(I2C_Module* I2Cx, uint32_t I2C_flag);
INTStatus I2C_Interrupt_Status_Get(I2C_Module* I2Cx, uint32_t Interrupt);
void I2C_Interrupt_Statu_Clear(I2C_Module* I2Cx, uint32_t Interrupt);

#ifdef __cplusplus
}
#endif

#endif /*__N32G430_I2C_H */
/**
 * 
 */




