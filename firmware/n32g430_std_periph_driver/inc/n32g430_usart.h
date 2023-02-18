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
*\*\file n32g430_usart.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32G430_USART_H__
#define __N32G430_USART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

/*** USART Structure Definition Start ***/

/** USART Init structure definition **/
typedef struct
{
    uint32_t BaudRate;            /* Configures the USART communication baud rate. */

    uint16_t WordLength;          /* Specifies the number of data bits transmitted or received in a frame. */

    uint16_t StopBits;            /* Specifies the number of stop bits transmitted. */

    uint16_t Parity;              /* Specifies the parity mode. */

    uint16_t Mode;                /* Specifies wether the Receive or Transmit mode is enabled or disabled. */

    uint16_t HardwareFlowControl; /* Specifies wether the hardware flow control mode is enabled or disabled. */
} USART_InitType;

/** USART Clock Init Structure definition **/

typedef struct
{
    uint16_t Clock;         /* Specifies whether the USART clock is enabled or disabled. */

    uint16_t Polarity;      /* Specifies the steady state value of the serial clock. */

    uint16_t Phase;         /* Specifies the clock transition on which the bit capture is made. */

    uint16_t LastBit;       /* Specifies whether the clock pulse corresponding to the last transmitted
                               data bit (MSB) has to be output on the SCLK pin in synchronous mode. */
} USART_ClockInitType;


/*** USART Macro Definition Start ***/


/** All register bits are configure to 0 **/     
#define USART_REG_BIT_MASK ((uint16_t)0x0000)  

/** Configures the word length of USART **/
#define USART_WL_MASK   (~USART_CTRL1_WL)     /* word length Mask */
#define USART_WL_8B     (USART_REG_BIT_MASK)  /* 8 bits */
#define USART_WL_9B     (USART_CTRL1_WL)      /* 9 bits */

/** USART STOP bits **/
#define CTRL2_STPB_CLR_MASK  (~USART_CTRL2_STPB)    /* USART CTRL2 STOP Bits Mask */
#define USART_STPB_1         (USART_REG_BIT_MASK)   /* 1 bit */
#define USART_STPB_0_5       (USART_CTRL2_STPB_0)   /* 0.5 bit */  
#define USART_STPB_2         (USART_CTRL2_STPB_1)   /* 2 bits */  
#define USART_STPB_1_5       (USART_CTRL2_STPB)     /* 1.5 bits */

/** USART parity selection **/
#define USART_PE_MASK           (~(USART_CTRL1_PCEN | USART_CTRL1_PSEL))  /* USART parity Mask */
#define USART_PE_NO             (USART_REG_BIT_MASK)                      /* USART parity disable */
#define USART_PE_EVEN           (USART_CTRL1_PCEN)                        /* Even parity */
#define USART_PE_ODD            (USART_CTRL1_PCEN | USART_CTRL1_PSEL)     /* Odd parity */

/** USART is configured as RX or TX **/
#define USART_MODE_MASK     (~(USART_CTRL1_RXEN | USART_CTRL1_TXEN))  /* USART mode Mask */
#define USART_MODE_RX       (USART_CTRL1_RXEN)                        /* Transmitter enable */
#define USART_MODE_TX       (USART_CTRL1_TXEN)                        /* Receiver enable */

/**  CTS or RTS **/
#define USART_HFCTRL_MASK    (~(USART_CTRL3_RTSEN | USART_CTRL3_CTSEN))   /* RTS and CTS Mask */
#define USART_HFCTRL_NONE    (USART_REG_BIT_MASK)                         /* RTS and CTS disable */
#define USART_HFCTRL_RTS     (USART_CTRL3_RTSEN)                          /* RTS enable */
#define USART_HFCTRL_CTS     (USART_CTRL3_CTSEN)                          /* CTS enable */
#define USART_HFCTRL_RTS_CTS (USART_CTRL3_RTSEN | USART_CTRL3_CTSEN)      /* RTS and CTS enable */

/** USART clock **/
#define USART_CLK_MASK        (~USART_CTRL2_CLKEN)  /* USART clock mask */
#define USART_CLK_DISABLE     (USART_REG_BIT_MASK)  /* USART clock disable */ 
#define USART_CLK_ENABLE      (USART_CTRL2_CLKEN)   /* USART clock enable */ 

/** USART clock polarity **/
#define USART_CLKPOL_MASK   (~USART_CTRL2_CLKPOL) /* USART clock polarity Mask */
#define USART_CLKPOL_LOW    (USART_REG_BIT_MASK)  /* USART clock polarity low */
#define USART_CLKPOL_HIGH   (USART_CTRL2_CLKPOL)  /* USART clock polarity high */

/** USART clock phase **/
#define USART_CLKPHA_MASK   (~USART_CTRL2_CLKPHA) /* Clock edge Mask */
#define USART_CLKPHA_1EDGE  (USART_REG_BIT_MASK)  /* First clock edge sampling */
#define USART_CLKPHA_2EDGE  (USART_CTRL2_CLKPHA)  /* Second clock edge sampling */

/** Last bit clock pulse **/
#define USART_CLKLB_MASK          (~USART_CTRL2_LBCLK)
#define USART_CLKLB_DISABLE       (USART_REG_BIT_MASK)
#define USART_CLKLB_ENABLE        (USART_CTRL2_LBCLK)

/** USART enable or disable **/
#define CTRL1_UEN_SET   (USART_CTRL1_UEN)    /* USART Enable  */
#define CTRL1_UEN_RESET (~USART_CTRL1_UEN)   /* USART Disable  */

/** Configure interrupt **/
#define INT_MASK        ((uint16_t)0x001F) /* USART Interrupt Mask */
#define USART_INT_PEF   ((uint16_t)0x0028) /* Parity error interrupt */
#define USART_INT_TXDE  ((uint16_t)0x0727) /* TXDE interrupt */
#define USART_INT_TXC   ((uint16_t)0x0626) /* Transmission complete interrupt */
#define USART_INT_RXDNE ((uint16_t)0x0525) /* RXDEN interrupt */
#define USART_INT_IDLEF ((uint16_t)0x0424) /* IDLE interrupt */
#define USART_INT_LINBD ((uint16_t)0x0846) /* LIN break detection interrupt */
#define USART_INT_CTSF  ((uint16_t)0x096A) /* CTS interrupt */
#define USART_INT_ERRF  ((uint16_t)0x0060) /* Error intrrrupt */
#define USART_INT_OREF  ((uint16_t)0x0360) /* ORE interrupt */
#define USART_INT_NEF   ((uint16_t)0x0260) /* NEF interrupt */
#define USART_INT_FEF   ((uint16_t)0x0160) /* FEF interrupt */

/** Specifies the DMA request **/
#define USART_DMAREQ_TX         (USART_CTRL3_DMATXEN) /* DMA transmit request */
#define USART_DMAREQ_RX         (USART_CTRL3_DMARXEN) /* DMA receive request */

/** USART address Mask **/
#define CTRL2_ADDR_MASK   (~USART_CTRL2_ADDR)  

/** Wake up methods **/
#define CTRL1_WUM_MASK          (~USART_CTRL1_WUM)    /* USART WakeUp Method Mask */
#define USART_WUM_IDLELINE      (USART_REG_BIT_MASK)  /* Idle frame wake up */
#define USART_WUM_ADDRMASK      (USART_CTRL1_WUM)     /* Address mark wake up */

/** Receiver wakeup **/
#define CTRL1_RCVWU_SET   (USART_CTRL1_RCVWU)     /* USART mute mode Enable  */
#define CTRL1_RCVWU_RESET (~USART_CTRL1_RCVWU)    /* USART mute mode Disable  */

/** LIN break detection length **/
#define CTRL2_LINBDL_MASK    (~USART_CTRL2_LINBDL)   /* USART LIN Break detection Mask */
#define USART_LINBDL_10B     (USART_REG_BIT_MASK)    /* 10 bits */
#define USART_LINBDL_11B     (USART_CTRL2_LINBDL)    /* 11 bits */

/** LIN config **/
#define CTRL2_LINMEN_SET   (USART_CTRL2_LINMEN)    /* USART LIN Enable Mask */
#define CTRL2_LINMEN_RESET (~USART_CTRL2_LINMEN)   /* USART LIN Disable Mask */

/** USART Break Character send Mask **/
#define CTRL1_SDBRK_SET   (USART_CTRL1_SDBRK)                

/** Guard Time Register **/
#define GTP_LSB_MASK        (USART_GTP_PSCV)     /* Guard Time Register LSB Mask */
#define GTP_MSB_MASK        (USART_GTP_GTV)      /* Guard Time Register MSB Mask */

/** USART Smart Card Enable or Disable **/
#define CTRL3_SCMEN_SET   (USART_CTRL3_SCMEN)     /* USART Smart Card Enable  */
#define CTRL3_SCMEN_RESET (~USART_CTRL3_SCMEN)    /* USART Smart Card Disable  */

/** USART Smart Card NACK Enable or Disable **/
#define CTRL3_SCNACK_SET   (USART_CTRL3_SCNACK)     /* USART Smart Card NACK Enable  */
#define CTRL3_SCNACK_RESET (~USART_CTRL3_SCNACK)    /* USART Smart Card NACK Disable  */

/** USART Half-Duplex Enable or Disable **/
#define CTRL3_HDMEN_SET   (USART_CTRL3_HDMEN)    /* USART Half-Duplex Enable  */
#define CTRL3_HDMEN_RESET (~USART_CTRL3_HDMEN)   /* USART Half-Duplex Disable  */
                                                                      
/** IRDA mode **/ 
#define CTRL3_IRDAMEN_SET        (USART_CTRL3_IRDAMEN)    /* USART IrDA Enable Mask */
#define CTRL3_IRDAMEN_RESET      (~USART_CTRL3_IRDAMEN)   /* USART IrDA Disable Mask */
#define CTRL3_IRDALP_MASK        (~USART_CTRL3_IRDALP)    /* USART IrDA LowPower mode Mask */
#define USART_IRDAMODE_LOWPPWER  (USART_CTRL3_IRDALP)     /* Low_power mode */
#define USART_IRDAMODE_NORMAL    (USART_REG_BIT_MASK)     /* Normal mode */ 

/* Specifies the flag to check */
#define USART_FLAG_CTSF  (USART_STS_CTSF)     /* CTS flag */
#define USART_FLAG_LINBD (USART_STS_LINBDF)   /* LIN break detection flag */
#define USART_FLAG_TXDE  (USART_STS_TXDE)     /* Transmit data register empty flag */
#define USART_FLAG_TXC   (USART_STS_TXC)      /* Transmission complete flag*/
#define USART_FLAG_RXDNE (USART_STS_RXDNE)    /* Read data register not empty flag*/
#define USART_FLAG_IDLEF (USART_STS_IDLEF)    /* IDLE line detected flag */
#define USART_FLAG_OREF  (USART_STS_OREF)     /* OverRun error flag */
#define USART_FLAG_NEF   (USART_STS_NEF)      /* Noise error flag */
#define USART_FLAG_FEF   (USART_STS_FEF)      /* Framing error flag*/
#define USART_FLAG_PEF   (USART_STS_PEF)      /* Parity error flag */

#define USART_BUAD_INTEGER_OFFSET       (REG_BIT4_OFFSET)      
#define USART_BUAD_FRACTIONAL_OFFSET    (REG_BIT4_OFFSET)  
#define USART_CTRL_INDEX_OFFSET         (REG_BIT5_OFFSET) 
#define USART_STS_INT_BIT_OFFSET        (REG_BIT8_OFFSET) 
#define USART_GTP_GTV_OFFSET            (REG_BIT8_OFFSET) 

void USART_Reset(USART_Module* USARTx);
void USART_Initializes(USART_Module* USARTx, USART_InitType* USART_InitStruct);
void USART_Baud_Rate_Config(USART_Module* USARTx,uint32_t buad_rate);
void USART_Word_Length_Config(USART_Module* USARTx,uint16_t word_length);
void USART_Stop_Bits_Config(USART_Module* USARTx,uint16_t stop_bits);
void USART_Parity_Config(USART_Module* USARTx,uint16_t parity);
void USART_Mode_Config(USART_Module* USARTx,uint16_t mode);
void USART_Hardware_Flow_Control_Config(USART_Module* USARTx,uint16_t hardware_flow_control);
void USART_Structure_Initializes(USART_InitType* USART_InitStruct);
void USART_Clock_Initializes(USART_Module* USARTx, USART_ClockInitType* USART_ClockInitStruct);
void USART_Clock_Config(USART_Module* USARTx,uint16_t clock);
void USART_Polarity_Config(USART_Module* USARTx,uint16_t polarity);
void USART_Phase_Config(USART_Module* USARTx,uint16_t phase);
void USART_Last_Bit_Config(USART_Module* USARTx,uint16_t last_bit);
void USART_Clock_Structure_Initializes(USART_ClockInitType* USART_ClockInitStruct);
void USART_Enable(USART_Module* USARTx);
void USART_Disable(USART_Module* USARTx);
void USART_Interrput_Enable(USART_Module* USARTx, uint16_t USART_interrupt);
void USART_Interrput_Disable(USART_Module* USARTx, uint16_t USART_interrupt);
void USART_DMA_Transfer_Enable(USART_Module* USARTx, uint16_t USART_DMA_request);
void USART_DMA_Transfer_Disable(USART_Module* USARTx, uint16_t USART_DMA_request);
void USART_Address_Set(USART_Module* USARTx, uint8_t USART_address);
void USART_WakeUp_Mode_Set(USART_Module* USARTx, uint16_t USART_wake_up_mode);
void USART_Receiver_Wakeup_Enable(USART_Module* USARTx);
void USART_Receiver_Wakeup_Disable(USART_Module* USARTx);
void USART_LIN_Break_Detect_Length_Set(USART_Module* USARTx, uint16_t USART_LIN_break_detect_length);
void USART_LIN_Enable(USART_Module* USARTx);
void USART_LIN_Disable(USART_Module* USARTx);
void USART_Data_Send(USART_Module* USARTx, uint16_t data);
uint16_t USART_Data_Receive(USART_Module* USARTx);
void USART_Break_Frame_Send(USART_Module* USARTx);
void USART_Guard_Time_Set(USART_Module* USARTx, uint8_t USART_guard_time);
void USART_Prescaler_Set(USART_Module* USARTx, uint8_t USART_prescaler);
void USART_Smart_Card_Enable(USART_Module* USARTx);
void USART_Smart_Card_Disable(USART_Module* USARTx);
void USART_Smart_Card_NACK_Enable(USART_Module* USARTx);
void USART_Smart_Card_NACK_Disable(USART_Module* USARTx);
void USART_Half_Duplex_Enable(USART_Module* USARTx);
void USART_Half_Duplex_Disable(USART_Module* USARTx);
void USART_IrDA_Mode_Set(USART_Module* USARTx, uint16_t USART_IrDA_mode);
void USART_IrDA_Enable(USART_Module* USARTx);
void USART_IrDA_Disable(USART_Module* USARTx);
FlagStatus USART_Flag_Status_Get(USART_Module* USARTx, uint16_t USART_flag);
void USART_Flag_Clear(USART_Module* USARTx, uint16_t USART_flag);
INTStatus USART_Interrupt_Status_Get(USART_Module* USARTx, uint16_t USART_interrupt);
void USART_Interrupt_Status_Clear(USART_Module* USARTx, uint16_t USART_Interrupt);

#ifdef __cplusplus
}
#endif

#endif /* __N32G430_USART_H__ */

