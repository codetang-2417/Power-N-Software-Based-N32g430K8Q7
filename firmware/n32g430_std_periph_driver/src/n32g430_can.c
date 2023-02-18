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
*\*\file n32g430_can.C
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#include "n32g430_can.h"
#include "n32g430_rcc.h"

/** CAN Private Defines**/

static INTStatus Interrupt_Status_Check(uint32_t CAN_register, uint32_t initializes_bit);

/** CAN Driving Functions Declaration **/

/**
*\*\name    CAN_Reset
*\*\fun     Deinitializes the CAN peripheral registers to their default reset values.
*\*\param   CANx:
*\*\             - CAN
*\*\return  none
**/
void CAN_Reset(CAN_Module* CANx)
{
    RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_CAN);
}

/**
*\*\name    CAN_Sleep_Mode_Exit
*\*\fun     Exit from sleep mode
*\*\param   CANx:
*\*\             - CAN
*\*\return  none
**/
void CAN_Sleep_Mode_Exit(CAN_Module* CANx)  
{
    CANx->MCTRL &= (~(uint32_t)CAN_SLEEP_REQUEST);
}

/**
*\*\name   CAN_Initializes_Enable
*\*\fun    Request initialisation
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Initializes_Enable(CAN_Module* CANx)
{
    CANx->MCTRL |= CAN_INIT_REQUEST;
}

/**
*\*\name   CAN_Initializes_Disable
*\*\fun    Request leave initialisation
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Initializes_Disable(CAN_Module* CANx)
{
    CANx->MCTRL &= ~(uint32_t)CAN_INIT_REQUEST;
}

/**
*\*\name   CAN_Initializes_Wait
*\*\fun    Wait the acknowledge
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Initializes_Wait(CAN_Module* CANx)
{
    uint32_t temp_value  = 0x00000000;          
    while (((CANx->MSTS & CAN_INIT_WAIT) != CAN_INIT_WAIT) && (temp_value != INIAK_TIMEOUT))
    {
        temp_value++;
    }
}

/**
*\*\name   CAN_Initializes_Leave_Wait
*\*\fun    Wait the acknowledge for leave
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Initializes_Leave_Wait(CAN_Module* CANx)
{
    uint32_t temp_value  = 0x00000000;
    while (((CANx->MSTS & CAN_INIT_WAIT) == CAN_INIT_WAIT) && (temp_value != INIAK_TIMEOUT))
    {
        temp_value++;
    }
}

/**
*\*\name   CAN_Time_Trigger_Mode_Enable
*\*\fun    Enable the time triggered communication mode
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Time_Trigger_Mode_Enable(CAN_Module* CANx)
{
    CANx->MCTRL |= CAN_TIME_TRI_MODE;
}


/**
*\*\name   CAN_Time_Trigger_Mode_Disable
*\*\fun    Disable the time triggered communication mode
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Time_Trigger_Mode_Disable(CAN_Module* CANx)
{
    CANx->MCTRL &= ~(uint32_t)CAN_TIME_TRI_MODE;
}

/**
*\*\name   CAN_Bus_Off_Enable
*\*\fun    Enable the automatic bus-off management
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Bus_Off_Enable(CAN_Module* CANx)
{
    CANx->MCTRL |= CAN_AUTO_BUS_OFF;
}


/**
*\*\name   CAN_Bus_Off_Disable
*\*\fun    Disable the automatic bus-off management
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Bus_Off_Disable(CAN_Module* CANx)
{
    CANx->MCTRL &= ~(uint32_t)CAN_AUTO_BUS_OFF;
}

/**
*\*\name   CAN_Wake_Up_Mode_Enable
*\*\fun    Enable the automatic wake-up mode
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Wake_Up_Mode_Enable(CAN_Module* CANx)
{
    CANx->MCTRL |= CAN_AUTO_WAKE_UP;
}

/**
*\*\name   CAN_Wake_Up_Mode_Disable
*\*\fun    Disable the automatic wake-up mode
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Wake_Up_Mode_Disable(CAN_Module* CANx)
{
    CANx->MCTRL &= ~(uint32_t)CAN_AUTO_WAKE_UP;
}

/**
*\*\name   CAN_No_Retransmission_Enable
*\*\fun    Enable the no automatic retransmission
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_No_Retransmission_Enable(CAN_Module* CANx)
{
    CANx->MCTRL |= CAN_AUTO_RETRANS_OFF;
}

/**
*\*\name   CAN_No_Retransmission_Disable
*\*\fun    Set the no automatic retransmission
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_No_Retransmission_Disable(CAN_Module* CANx)
{
    CANx->MCTRL &= ~(uint32_t)CAN_AUTO_RETRANS_OFF;
}

/**
*\*\name   CAN_DATA_FIFO_Receive_Lock_Enable
*\*\fun    Set the receive DATAFIFO locked mode
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_DATA_FIFO_Receive_Lock_Enable(CAN_Module* CANx)
{
    CANx->MCTRL |= CAN_RX_FIFO_LOCKED;
}

/**
*\*\name   CAN_DATA_FIFO_Receive_Lock_Disable
*\*\fun    Set the receive DATAFIFO locked mode
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_DATA_FIFO_Receive_Lock_Disable(CAN_Module* CANx)
{
    CANx->MCTRL &= ~(uint32_t)CAN_RX_FIFO_LOCKED;
}

/**
*\*\name   CAN_DATA_FIFO_Transmit_Priority_Enable
*\*\fun    Enable the transmit DATAFIFO priority 
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_DATA_FIFO_Transmit_Priority_Enable(CAN_Module* CANx)
{
    CANx->MCTRL |= CAN_TX_FIFO_PRIO;
}

/**
*\*\name   CAN_DATA_FIFO_Transmit_Priority_Disable
*\*\fun    Set the transmit DATAFIFO priority 
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_DATA_FIFO_Transmit_Priority_Disable(CAN_Module* CANx)
{
    CANx->MCTRL &= ~(uint32_t)CAN_TX_FIFO_PRIO;
}

/**
*\*\name   CAN_Bit_Timing_Set
*\*\fun    Set the bit timing register 
*\*\param  CANx:
*\*\            - CAN
*\*\param  CAN_initializes_parameter :
*\*\            - BaudRatePrescaler
*\*\            - OperatingMode
*\*\            - RSJW
*\*\            - TBS1
*\*\            - TBS2
*\*\return none
**/
void CAN_Bit_Timing_Set(CAN_Module* CANx, CAN_InitType* CAN_initializes_parameter)
{
    CANx->BTIM = (uint32_t)((uint32_t)CAN_initializes_parameter->OperatingMode << CAN_OPERATING_MODE_OFFSET) 
                | ((uint32_t)CAN_initializes_parameter->RSJW << CAN_RSJW_OFFSET)
                | ((uint32_t)CAN_initializes_parameter->TBS1 << CAN_TBS1_OFFSET) 
                | ((uint32_t)CAN_initializes_parameter->TBS2 << CAN_TBS2_OFFSET)
                | ((uint32_t)CAN_initializes_parameter->BaudRatePrescaler - 1);
}

/**
*\*\name   CAN_Initializes
*\*\fun    Initializes the CAN peripheral according to the specified
*\*\       parameters in the CAN_initializes_parameter.
*\*\param  CANx:
*\*\            - CAN
*\*\param  CAN_initializes_parameter :
*\*\            - BaudRatePrescaler
*\*\                - It ranges from 1 to 1024.
*\*\            - OperatingMode
*\*\                - CAN_NORMAL_MODE
*\*\                - CAN_LOOPBACK_MODE
*\*\                - CAN_SILENT_MODE
*\*\                - CAN_SILENT_LOOPBACK_MODE
*\*\            - RSJW
*\*\                - CAN_RSJW_1TQ
*\*\                - CAN_RSJW_2TQ
*\*\                - CAN_RSJW_3TQ
*\*\                - CAN_RSJW_4TQ
*\*\            - TBS1
*\*\                - CAN_TBS1_1TQ
*\*\                - CAN_TBS1_2TQ
*\*\                - CAN_TBS1_3TQ
*\*\                - CAN_TBS1_4TQ
*\*\                - CAN_TBS1_5TQ
*\*\                - CAN_TBS1_6TQ
*\*\                - CAN_TBS1_7TQ
*\*\                - CAN_TBS1_8TQ
*\*\                - CAN_TBS1_9TQ
*\*\                - CAN_TBS1_10TQ
*\*\                - CAN_TBS1_11TQ
*\*\                - CAN_TBS1_12TQ
*\*\                - CAN_TBS1_13TQ
*\*\                - CAN_TBS1_14TQ
*\*\                - CAN_TBS1_15TQ
*\*\                - CAN_TBS1_16TQ
*\*\            - TBS2
*\*\                - CAN_TBS2_1TQ
*\*\                - CAN_TBS2_2TQ
*\*\                - CAN_TBS2_3TQ
*\*\                - CAN_TBS2_4TQ
*\*\                - CAN_TBS2_5TQ
*\*\                - CAN_TBS2_6TQ
*\*\                - CAN_TBS2_7TQ
*\*\                - CAN_TBS2_8TQ
*\*\            - TTCM
*\*\                - DISABLE
*\*\                - ENABLE
*\*\            - ABOM
*\*\                - DISABLE
*\*\                - ENABLE
*\*\            - AWKUM
*\*\                - DISABLE
*\*\                - ENABLE
*\*\            - NART
*\*\                - DISABLE
*\*\                - ENABLE
*\*\            - RFLM
*\*\                - DISABLE
*\*\                - ENABLE
*\*\            - TXFP
*\*\                - DISABLE
*\*\                - ENABLE           
*\*\return CAN_Status :
*\*\            - CAN_STS_Failed
*\*\            - CAN_STS_Success
**/
CAN_Status CAN_Initializes(CAN_Module* CANx, CAN_InitType* CAN_initializes_parameter)
{
    CAN_Sleep_Mode_Exit(CANx);
    CAN_Initializes_Enable(CANx);
    CAN_Initializes_Wait(CANx);

    /* Check acknowledge */
    if ((CANx->MSTS & CAN_INIT_WAIT) != CAN_INIT_WAIT)
    {
        /* At this step, return the status of initialization */
        return CAN_STS_Failed;
    }
    else
    {
        if(CAN_initializes_parameter->TTCM == ENABLE)
        {
            CAN_Time_Trigger_Mode_Enable(CAN);
        }
        else
        {
            CAN_Time_Trigger_Mode_Disable(CAN);
        }
        
        if(CAN_initializes_parameter->ABOM == ENABLE)
        {
            CAN_Bus_Off_Enable(CAN);
        }
        else
        {
            CAN_Bus_Off_Disable(CAN);
        }
        
        if(CAN_initializes_parameter->AWKUM == ENABLE)
        {
            CAN_Wake_Up_Mode_Enable(CAN);
        }
        else
        {
            CAN_Wake_Up_Mode_Disable(CAN);
        }
        
        if(CAN_initializes_parameter->NART == ENABLE)
        {
            CAN_No_Retransmission_Enable(CAN);
        }
        else
        {
            CAN_No_Retransmission_Disable(CAN);
        }
        
        if(CAN_initializes_parameter->RFLM == ENABLE)
        {
            CAN_DATA_FIFO_Receive_Lock_Enable(CANx);
        }
        else
        {
            CAN_DATA_FIFO_Receive_Lock_Disable(CANx);
        }

        if(CAN_initializes_parameter->TXFP == ENABLE)
        {
            CAN_DATA_FIFO_Transmit_Priority_Enable(CANx);
        }
        else
        {
            CAN_DATA_FIFO_Transmit_Priority_Disable(CANx);
        }
        CAN_Bit_Timing_Set(CANx,CAN_initializes_parameter);
        CAN_Initializes_Disable(CANx);
        CAN_Initializes_Leave_Wait(CANx);
        /* ...and check acknowledged */
        if ((CANx->MSTS & CAN_INIT_WAIT) == CAN_INIT_WAIT)
        {
            CAN_Initializes_Disable(CANx);
            CAN_Initializes_Leave_Wait(CANx);
            return CAN_STS_Failed;
        }
        else
        {
            return CAN_STS_Success;
        }
    }
}

/**
*\*\name   CAN_Filter_Initializes_Enable
*\*\fun    Initialisation mode for the filter
*\*\param  none
*\*\return none
**/
void CAN_Filter_Initializes_Enable(void)
{
    CAN->FMC |= CAN_FILTER_INIT;
}

/**
*\*\name   CAN_Filter_Initializes_Disable
*\*\fun    Leave the initialisation mode for the filter
*\*\param  none
*\*\return none
**/
void CAN_Filter_Initializes_Disable(void)
{
    CAN->FMC &= ~CAN_FILTER_INIT;
}

/**
*\*\name   CAN_Filter_Deactivation
*\*\fun    Filter Deactivation
*\*\param  filter_position :
*\*\           - It ranges from 2^(0 to 13).
*\*\return none
**/
void CAN_Filter_Deactivation(uint32_t filter_position)
{
    CAN->FA1 &= ~(uint32_t)filter_position;
}

/**
*\*\name   CAN_Filter_Scale_16bit_Set
*\*\fun    Filter 16bitScale check and configure
*\*\param  filter_position :
*\*\            - It ranges from 2^(0 to 13).
*\*\param  CAN_filter_initializes_structure :
*\*\            - Filter_HighId
*\*\            - Filter_LowId
*\*\            - FilterMask_HighId
*\*\            - FilterMask_LowId
*\*\            - Filter_Num
*\*\            - Filter_Scale
*\*\return none
**/
void CAN_Filter_Scale_16bit_Set(CAN_FilterInitType* CAN_filter_initializes_structure, \
                            uint32_t filter_position)
{
    /* Filter Scale */
    if (CAN_filter_initializes_structure->Filter_Scale == CAN_FILTER_16BITSCALE)
    {
        /* 16-bit scale for the filter */
        CAN->FS1 &= ~(uint32_t)filter_position;

        /* First 16-bit identifier and First 16-bit mask */
        /* Or First 16-bit identifier and Second 16-bit identifier */
        CAN->sFilterRegister[CAN_filter_initializes_structure->Filter_Num].FR1 =
            ((0x0000FFFF & (uint32_t)CAN_filter_initializes_structure->FilterMask_LowId) << CAN_FRX_ID_OFFSET)
            | (0x0000FFFF & (uint32_t)CAN_filter_initializes_structure->Filter_LowId);

        /* Second 16-bit identifier and Second 16-bit mask */
        /* Or Third 16-bit identifier and Fourth 16-bit identifier */
        CAN->sFilterRegister[CAN_filter_initializes_structure->Filter_Num].FR2 =
            ((0x0000FFFF & (uint32_t)CAN_filter_initializes_structure->FilterMask_HighId) << CAN_FRX_ID_OFFSET)
            | (0x0000FFFF & (uint32_t)CAN_filter_initializes_structure->Filter_HighId);
    }
    else
    {
        /*No process*/
    }
}

/**
*\*\name   CAN_Filter_Scale_32bit_Set
*\*\fun    Filter 32bitScale check and configure
*\*\param  filter_position :
*\*\            - It ranges from 2^(0 to 13).
*\*\param  CAN_filter_initializes_structure :
*\*\            - Filter_HighId
*\*\            - Filter_LowId
*\*\            - FilterMask_HighId
*\*\            - FilterMask_LowId
*\*\            - Filter_Num
*\*\            - Filter_Scale
*\*\return none
**/
void CAN_Filter_Scale_32bit_Set(CAN_FilterInitType* CAN_filter_initializes_structure, \
                            uint32_t filter_position)
{
    /* Filter Scale */
    if (CAN_filter_initializes_structure->Filter_Scale == CAN_FILTER_32BITSCALE)
    {
        /* 32-bit scale for the filter */
        CAN->FS1 |= filter_position;
        /* 32-bit identifier or First 32-bit identifier */
        CAN->sFilterRegister[CAN_filter_initializes_structure->Filter_Num].FR1 =
            ((0x0000FFFF & (uint32_t)CAN_filter_initializes_structure->Filter_HighId) << CAN_FRX_ID_OFFSET)
            | (0x0000FFFF & (uint32_t)CAN_filter_initializes_structure->Filter_LowId);
        /* 32-bit mask or Second 32-bit identifier */
        CAN->sFilterRegister[CAN_filter_initializes_structure->Filter_Num].FR2 =
            ((0x0000FFFF & (uint32_t)CAN_filter_initializes_structure->FilterMask_HighId) << CAN_FRX_ID_OFFSET)
            | (0x0000FFFF & (uint32_t)CAN_filter_initializes_structure->FilterMask_LowId);
    }
    else
    {
        /*No process*/
    }
}

/**
*\*\name   CAN_Filter_Mode_Set
*\*\fun    Filter Mode configure
*\*\param  filter_mode :
*\*\            - CAN_FILTER_IDMASKMODE
*\*\            - CAN_FILTER_IDLISTMODE
*\*\param  filter_position :
*\*\            - It ranges from 2^(0 to 13).
*\*\return none
**/
void CAN_Filter_Mode_Set(uint8_t filter_mode, uint32_t filter_position)
{
    /* Filter Mode */
    if (filter_mode == CAN_FILTER_IDMASKMODE)
    {
        /*Id/Mask mode for the filter*/
        CAN->FM1 &= ~(uint32_t)filter_position;
    }
    else /* filter_mode == CAN_FILTER_IDLISTMODE */
    {
        /*Identifier list mode for the filter*/
        CAN->FM1 |= (uint32_t)filter_position;
    }
}

/**
*\*\name   CAN_Filter_DATA_FIFO_Assign
*\*\fun    Filter DATAFIFO assignment
*\*\param  filter_position :
*\*\            - It ranges from 2^(0 to 13).
*\*\param  filter_assign :
*\*\            - CAN_FILTER_FIFO0
*\*\            - CAN_FILTER_FIFO1
*\*\return none
**/
void CAN_Filter_DATA_FIFO_Assign(uint16_t filter_assign, uint32_t filter_position)
{
    /* Filter DATAFIFO assignment */
    if (filter_assign == CAN_FILTER_FIFO0)
    {
        /* DATAFIFO 0 assignation for the filter */
        CAN->FFA1 &= ~(uint32_t)filter_position;
    }
    else
    {
        /*No process*/
    }

    if (filter_assign == CAN_FILTER_FIFO1)
    {
        /* DATAFIFO 1 assignation for the filter */
        CAN->FFA1 |= (uint32_t)filter_position;
    }
    else
    {
        /*No process*/
    }
}

/**
*\*\name   CAN_Filter_Activate
*\*\fun    Filter activation
*\*\param  filter_position :
*\*\            - It ranges from 2^(0 to 13).
*\*\return none
**/
void CAN_Filter_Activate(uint32_t filter_position)
{
    CAN->FA1 |= filter_position;
}


/**
*\*\name   CAN_Filter_Initializes
*\*\fun    Initializes the CAN peripheral according to the specified
*\*\       parameters in the CAN_filter_initializes_structure.
*\*\param  CAN_filter_initializes_structure :
*\*\            - Filter_HighId
*\*\                - It ranges from 0x0000 to 0xFFFF
*\*\            - Filter_LowId
*\*\                - It ranges from 0x0000 to 0xFFFF
*\*\            - FilterMask_HighId
*\*\                - It ranges from 0x0000 to 0xFFFF
*\*\            - FilterMask_LowId
*\*\                - It ranges from 0x0000 to 0xFFFF
*\*\            - Filter_FIFOAssignment
*\*\                - CAN_Filter_FIFO0
*\*\                - CAN_Filter_FIFO1
*\*\            - Filter_Num
*\*\                - It ranges from 0 to 13
*\*\            - Filter_Mode
*\*\                - CAN_FILTER_IDMASKMODE
*\*\                - CAN_FILTER_IDLISTMODE
*\*\            - Filter_Scale
*\*\                - CAN_FILTER_16BITSCALE
*\*\                - CAN_FILTER_32BITSCALE
*\*\            - Filter_Act
*\*\                - ENABLE
*\*\                - DISABLE
*\*\return none
**/
void CAN_Filter_Initializes(CAN_FilterInitType* CAN_filter_initializes_structure)
{
    uint32_t filter_position = 0;
    filter_position = ((uint32_t)1) << CAN_filter_initializes_structure->Filter_Num;

    CAN_Filter_Initializes_Enable();
    CAN_Filter_Deactivation(filter_position);
    CAN_Filter_Scale_16bit_Set(CAN_filter_initializes_structure,filter_position);
    CAN_Filter_Scale_32bit_Set(CAN_filter_initializes_structure,filter_position);
    CAN_Filter_Mode_Set(CAN_filter_initializes_structure->Filter_Mode,filter_position);
    CAN_Filter_DATA_FIFO_Assign(CAN_filter_initializes_structure->Filter_FIFOAssignment,\
                                filter_position);
    if (CAN_filter_initializes_structure->Filter_Act == ENABLE)
    {
        CAN_Filter_Activate(filter_position);
    }
    else
    {
        /*No process*/
    }
    CAN_Filter_Initializes_Disable();
}

/**
*\*\name   CAN_Structure_Initializes
*\*\fun    Fills each CAN_initializes_parameter member with its default value.
*\*\param  CAN_initializes_parameter :
*\*\            - BaudRatePrescaler
*\*\            - OperatingMode
*\*\            - RSJW
*\*\            - TBS1
*\*\            - TBS2
*\*\            - TTCM
*\*\            - ABOM
*\*\            - AWKUM
*\*\            - NART
*\*\            - RFLM
*\*\            - TXFP
*\*\return none
**/
void CAN_Structure_Initializes(CAN_InitType* CAN_initializes_parameter)
{
    /* Reset CAN init structure parameters values */

    /* Initialize the time triggered communication mode */
    CAN_initializes_parameter->TTCM = DISABLE;

    /* Initialize the automatic bus-off management */
    CAN_initializes_parameter->ABOM = DISABLE;

    /* Initialize the automatic wake-up mode */
    CAN_initializes_parameter->AWKUM = DISABLE;

    /* Initialize the no automatic retransmission */
    CAN_initializes_parameter->NART = DISABLE;

    /* Initialize the receive DATAFIFO locked mode */
    CAN_initializes_parameter->RFLM = DISABLE;

    /* Initialize the transmit DATAFIFO priority */
    CAN_initializes_parameter->TXFP = DISABLE;

    /* Initialize the OperatingMode member */
    CAN_initializes_parameter->OperatingMode = CAN_NORMAL_MODE;

    /* Initialize the RSJW member */
    CAN_initializes_parameter->RSJW = CAN_RSJW_1TQ;

    /* Initialize the TBS1 member */
    CAN_initializes_parameter->TBS1 = CAN_TBS1_4TQ;

    /* Initialize the TBS2 member */
    CAN_initializes_parameter->TBS2 = CAN_TBS2_3TQ;

    /* Initialize the BaudRatePrescaler member */
    CAN_initializes_parameter->BaudRatePrescaler = 1;
}

/**
*\*\name   CAN_Debug_Freeze_Enable
*\*\fun    Enables the DBG Freeze for CAN.
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Debug_Freeze_Enable(CAN_Module* CANx)
{
    /* Enable Debug Freeze  */
    CANx->MCTRL |= CAN_DEBUG_FREEZE;    
}


/**
*\*\name   CAN_Debug_Freeze_Disable
*\*\fun    Disables the DBG Freeze for CAN.
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Debug_Freeze_Disable(CAN_Module* CANx)
{
    CANx->MCTRL &= ~CAN_DEBUG_FREEZE;
}

/**
*\*\name   CAN_Time_Stamp_Sent_Enable
*\*\fun    Enables the CAN Time stamp sent.
*\*\param  CANx:
*\*\            - CAN
*\*\note   when enabled, Time stamp (TIME[15:0]) value is sent in the last
*\*\       two data bytes of the 8-byte message: TIME[7:0] in data byte 6
*\*\       and TIME[15:8] in data byte 7
*\*\note   DLC must be programmed as 8 in order Time Stamp (2 bytes) to be
*\*\       sent over the CAN bus.
*\*\return none
**/
void CAN_Time_Stamp_Sent_Enable(CAN_Module* CANx)
{
    /* Enable the TTCM mode */
    CANx->MCTRL |= CAN_TIME_TRI_MODE;

    /* Set TGT bits */
    CANx->sTxMailBox[0].TMDT |= ((uint32_t)CAN_TX_GLOBAL_TIME0);
    CANx->sTxMailBox[1].TMDT |= ((uint32_t)CAN_TX_GLOBAL_TIME1);
    CANx->sTxMailBox[2].TMDT |= ((uint32_t)CAN_TX_GLOBAL_TIME2);
}

/**
*\*\name   CAN_Time_Stamp_Sent_Disable
*\*\fun    Enables or disabes the CAN Time TriggerOperation communication mode.
*\*\param  CANx:
*\*\            - CAN
*\*\return none
**/
void CAN_Time_Stamp_Sent_Disable(CAN_Module* CANx)
{
    /* Disable the TTCM mode */
    CANx->MCTRL &= (uint32_t)(~(uint32_t)CAN_TIME_TRI_MODE);

    /* Reset TGT bits */
    CANx->sTxMailBox[0].TMDT &= ((uint32_t)~CAN_TX_GLOBAL_TIME0);
    CANx->sTxMailBox[1].TMDT &= ((uint32_t)~CAN_TX_GLOBAL_TIME1);
    CANx->sTxMailBox[2].TMDT &= ((uint32_t)~CAN_TX_GLOBAL_TIME2);
}


/**
*\*\name   CAN_Transmit_Message_ID_Config
*\*\fun    Set up the Id.
*\*\param  CANx:
*\*\            - CAN
*\*\param  transmit_message :
*\*\            - StdId
*\*\            - ExtId
*\*\            - IDE
*\*\            - RTR
*\*\param  mailbox_queue :
*\*\            - CAN_TXSTS_MAILBOX0
*\*\            - CAN_TXSTS_MAILBOX1
*\*\            - CAN_TXSTS_MAILBOX2
*\*\return none
**/
void CAN_Transmit_Message_ID_Config(CAN_Module* CANx, CanTxMessage* transmit_message, \
                                            uint8_t mailbox_queue)
{
    CANx->sTxMailBox[mailbox_queue].TMI &= CAN_TMIX_TXRQ;
    if (transmit_message->IDE == CAN_STANDARD_ID)
    {
        CANx->sTxMailBox[mailbox_queue].TMI |= ((transmit_message->StdId << CAN_TMI_STDID_OFFSET) | transmit_message->RTR);
    }
    else
    {
        CANx->sTxMailBox[mailbox_queue].TMI |= ((transmit_message->ExtId << CAN_TMI_EXTID_OFFSET) | transmit_message->IDE | transmit_message->RTR);
    }
}

/**
*\*\name   CAN_Transmit_Message_DLC_Config
*\*\fun    Set up the DLC.
*\*\param  CANx:
*\*\            - CAN
*\*\param  data_length
*\*\            - It ranges from 0 to 8
*\*\param  mailbox_queue :
*\*\            - CAN_TXSTS_MAILBOX0
*\*\            - CAN_TXSTS_MAILBOX1
*\*\            - CAN_TXSTS_MAILBOX2
*\*\return none
**/
void CAN_Transmit_Message_DLC_Config(CAN_Module* CANx, uint8_t data_length, \
                                            uint8_t mailbox_queue)
{
    data_length &= (uint8_t)CAN_TMDTx_DLC;
    CANx->sTxMailBox[mailbox_queue].TMDT &= CAN_TMDTx_DLC_MASK;
    CANx->sTxMailBox[mailbox_queue].TMDT |= data_length;
}

/**
*\*\name   CAN_Transmit_Message_Data_Config
*\*\fun    Set up the data field.
*\*\param  CANx:
*\*\            - CAN
*\*\param  transmit_message :
*\*\            - Data[0-7]
*\*\                - It ranges from 0 to 0xFF
*\*\param  mailbox_queue :
*\*\            - CAN_TXSTS_MAILBOX0
*\*\            - CAN_TXSTS_MAILBOX1
*\*\            - CAN_TXSTS_MAILBOX2
*\*\return none
**/
void CAN_Transmit_Message_Data_Config(CAN_Module* CANx, CanTxMessage* transmit_message, \
                                            uint8_t mailbox_queue)
{
    CANx->sTxMailBox[mailbox_queue].TMDL = (((uint32_t)transmit_message->Data[3] << CAN_RMDL_DATA3_OFFSET) 
                                          | ((uint32_t)transmit_message->Data[2] << CAN_RMDL_DATA2_OFFSET)
                                          | ((uint32_t)transmit_message->Data[1] << CAN_RMDL_DATA1_OFFSET) 
                                          | ((uint32_t)transmit_message->Data[0]));
    CANx->sTxMailBox[mailbox_queue].TMDH = (((uint32_t)transmit_message->Data[7] << CAN_RMDH_DATA7_OFFSET) 
                                          | ((uint32_t)transmit_message->Data[6] << CAN_RMDH_DATA6_OFFSET)
                                          | ((uint32_t)transmit_message->Data[5] << CAN_RMDH_DATA5_OFFSET) 
                                          | ((uint32_t)transmit_message->Data[4]));
}

/**
*\*\name   CAN_Transmit_Enable
*\*\fun    Request transmission.
*\*\param  CANx:
*\*\            - CAN
*\*\param  mailbox_queue :
*\*\            - CAN_TXSTS_MAILBOX0
*\*\            - CAN_TXSTS_MAILBOX1
*\*\            - CAN_TXSTS_MAILBOX2
*\*\return none
**/
void CAN_Transmit_Enable(CAN_Module* CANx, uint8_t mailbox_queue)
{
    CANx->sTxMailBox[mailbox_queue].TMI |= CAN_TMIX_TXRQ;
}

/**
*\*\name   CAN_Transmit_Message_initializes
*\*\fun    initialize the transmission of a message.
*\*\param  CANx:
*\*\            - CAN
*\*\param  transmit_message :
*\*\            - StdId
*\*\                - It ranges from 0 to 0x7FF
*\*\            - ExtId
*\*\                - It ranges from 0 to 0x1FFFFFFF
*\*\            - IDE
*\*\                - CAN_STANDARD_ID
*\*\                - CAN_EXTENDED_ID
*\*\            - RTR
*\*\                - CAN_RTRQ_DATA
*\*\                - CAN_RTRQ_REMOTE
*\*\            - DLC
*\*\                - It ranges from 0 to 8
*\*\            - Data[0-7]
*\*\                - It ranges from 0 to 0xFF
*\*\return  mailbox_queue :
*\*\            - CAN_TXSTS_MAILBOX0
*\*\            - CAN_TXSTS_MAILBOX1
*\*\            - CAN_TXSTS_MAILBOX2
*\*\            - CAN_TXSTS_NOMAILBOX
**/
uint8_t CAN_Transmit_Message_initializes(CAN_Module* CANx, CanTxMessage* transmit_message)
{
    uint8_t mailbox_queue = CAN_TXSTS_MAILBOX0;

    /* Select one empty transmit mailbox */
    if ((CANx->TSTS & CAN_TX_MAILBOX_EMPTY0) == CAN_TX_MAILBOX_EMPTY0)
    {
        mailbox_queue = CAN_TXSTS_MAILBOX0;
    }
    else if ((CANx->TSTS & CAN_TX_MAILBOX_EMPTY1) == CAN_TX_MAILBOX_EMPTY1)
    {
        mailbox_queue = CAN_TXSTS_MAILBOX1;
    }
    else if ((CANx->TSTS & CAN_TX_MAILBOX_EMPTY2) == CAN_TX_MAILBOX_EMPTY2)
    {
        mailbox_queue = CAN_TXSTS_MAILBOX2;
    }
    else
    {
        mailbox_queue = CAN_TXSTS_NOMAILBOX;
    }

    if (mailbox_queue != CAN_TXSTS_NOMAILBOX)
    {
        /* Set up the Id */
        CAN_Transmit_Message_ID_Config(CANx,transmit_message,mailbox_queue);
        /* Set up the DLC */
        CAN_Transmit_Message_DLC_Config(CANx,transmit_message->DLC,mailbox_queue);
        /* Set up the data field */
        CAN_Transmit_Message_Data_Config(CANx,transmit_message,mailbox_queue);
        /* Request transmission */
        CAN_Transmit_Enable(CANx,mailbox_queue);
    }
    else
    {
        /*No process*/
    }

    return mailbox_queue;
}

/**
*\*\name   CAN_Transmit_Status_Get
*\*\fun    Checks the transmission of a message.
*\*\param  CANx:
*\*\            - CAN
*\*\param  mailbox_queue :
*\*\            - CAN_TXSTS_MAILBOX0
*\*\            - CAN_TXSTS_MAILBOX1
*\*\            - CAN_TXSTS_MAILBOX2
*\*\return CAN_Tx_Status :
*\*\            - CAN_TXSTS_FAILED
*\*\            - CAN_TXSTS_OK
*\*\            - CAN_TXSTS_PENDING
**/
CAN_Tx_Status CAN_Transmit_Status_Get(CAN_Module* CANx, uint8_t mailbox_queue)
{
    uint32_t status_value = CAN_TXSTS_FAILED;

    switch (mailbox_queue)
    {
        case (CAN_TXSTS_MAILBOX0):
            status_value = CANx->TSTS & (CAN_MAILBOX0_RQ_OK | CAN_MAILBOX0_TX_OK | CAN_TX_MAILBOX_EMPTY0);
            break;
        case (CAN_TXSTS_MAILBOX1):
            status_value = CANx->TSTS & (CAN_MAILBOX1_RQ_OK | CAN_MAILBOX1_TX_OK | CAN_TX_MAILBOX_EMPTY1);
            break;
        case (CAN_TXSTS_MAILBOX2):
            status_value = CANx->TSTS & (CAN_MAILBOX2_RQ_OK | CAN_MAILBOX2_TX_OK | CAN_TX_MAILBOX_EMPTY2);
            break;
        default:
            status_value = CAN_TXSTS_FAILED;
            break;
    }
    switch (status_value)
    {
        /* transmit pending  */
        case (0x0):
            status_value = CAN_TXSTS_PENDING;
            break;
            /* transmit failed  */
        case (CAN_MAILBOX0_RQ_OK | CAN_TX_MAILBOX_EMPTY0):
            status_value = CAN_TXSTS_FAILED;
            break;
        case (CAN_MAILBOX1_RQ_OK | CAN_TX_MAILBOX_EMPTY1):
            status_value = CAN_TXSTS_FAILED;
            break;
        case (CAN_MAILBOX2_RQ_OK | CAN_TX_MAILBOX_EMPTY2):
            status_value = CAN_TXSTS_FAILED;
            break;
            /* transmit succeeded  */
        case (CAN_MAILBOX0_RQ_OK | CAN_MAILBOX0_TX_OK | CAN_TX_MAILBOX_EMPTY0):
            status_value = CAN_TXSTS_OK;
            break;
        case (CAN_MAILBOX1_RQ_OK | CAN_MAILBOX1_TX_OK | CAN_TX_MAILBOX_EMPTY1):
            status_value = CAN_TXSTS_OK;
            break;
        case (CAN_MAILBOX2_RQ_OK | CAN_MAILBOX2_TX_OK | CAN_TX_MAILBOX_EMPTY2):
            status_value = CAN_TXSTS_OK;
            break;
        default:
            status_value = CAN_TXSTS_FAILED;
            break;
    }
    return (CAN_Tx_Status)status_value;
}

/**
*\*\name   CAN_Transmit_Message_Cancel
*\*\brief  Cancels a transmit request.
*\*\param  CANx:
*\*\            - CAN
*\*\param  mailbox_queue :
*\*\            - CAN_TXSTS_MAILBOX0
*\*\            - CAN_TXSTS_MAILBOX1
*\*\            - CAN_TXSTS_MAILBOX2
*\*\return none
**/
void CAN_Transmit_Message_Cancel(CAN_Module* CANx, uint8_t mailbox_queue) 
{
    /* abort transmission */
    switch (mailbox_queue)
    {
        case (CAN_TXSTS_MAILBOX0):
            CANx->TSTS = CAN_MAILBOX0_RQ_AB;
            break;
        case (CAN_TXSTS_MAILBOX1):
            CANx->TSTS = CAN_MAILBOX1_RQ_AB;
            break;
        case (CAN_TXSTS_MAILBOX2):
            CANx->TSTS = CAN_MAILBOX2_RQ_AB;
            break;
        default:
            break;
    }
}

/**
*\*\name   CAN_Message_Receive
*\*\fun    Receives a message.
*\*\param  CANx:
*\*\            - CAN
*\*\param  FIFO_number :
*\*\            - CAN_FIFO0
*\*\            - CAN_FIFO1
*\*\param  receive_message :
*\*\            - StdId
*\*\                - It ranges from 0 to 0x7FF
*\*\            - ExtId
*\*\                - It ranges from 0 to 0x1FFFFFFF
*\*\            - IDE
*\*\                - CAN_STANDARD_ID
*\*\                - CAN_EXTENDED_ID
*\*\            - RTR
*\*\                - CAN_RTRQ_DATA
*\*\                - CAN_RTRQ_REMOTE
*\*\            - DLC
*\*\                - It ranges from 0 to 8
*\*\            - Data[0-7]
*\*\                - It ranges from 0 to 0xFF
*\*\            - FMI
*\*\                - It ranges from 0 to 0xFF
*\*\return none
**/
void CAN_Message_Receive(CAN_Module* CANx, uint8_t FIFO_number, CanRxMessage* receive_message)
{
    /* Get the Id */
    receive_message->IDE = (uint8_t)CAN_RMIx_IDE & CANx->sFIFOMailBox[FIFO_number].RMI;
    if (receive_message->IDE == CAN_STANDARD_ID)
    {
        receive_message->StdId = (CAN_RMIx_STDID & CANx->sFIFOMailBox[FIFO_number].RMI) >> CAN_RMI_STDID_OFFSET;
    }
    else
    {
        receive_message->ExtId = (CAN_EXTID_MASK & CANx->sFIFOMailBox[FIFO_number].RMI) >> CAN_RMI_EXTID_OFFSET;
    }

    receive_message->RTR = (uint8_t)CAN_RMIx_RTRQ & CANx->sFIFOMailBox[FIFO_number].RMI;
    /* Get the DLC */
    receive_message->DLC = (uint8_t)CAN_TMDTx_DLC & CANx->sFIFOMailBox[FIFO_number].RMDT;
    /* Get the FMI */
    receive_message->FMI = (uint8_t)CAN_DATA_FIFO_MASK & (CANx->sFIFOMailBox[FIFO_number].RMDT >> CAN_RMDT_OFFSET);
    /* Get the data field */
    receive_message->Data[0] = (uint8_t)CAN_DATA_FIFO_MASK & CANx->sFIFOMailBox[FIFO_number].RMDL;
    receive_message->Data[1] = (uint8_t)CAN_DATA_FIFO_MASK & (CANx->sFIFOMailBox[FIFO_number].RMDL >> CAN_RMDL_DATA1_OFFSET);
    receive_message->Data[2] = (uint8_t)CAN_DATA_FIFO_MASK & (CANx->sFIFOMailBox[FIFO_number].RMDL >> CAN_RMDL_DATA2_OFFSET);
    receive_message->Data[3] = (uint8_t)CAN_DATA_FIFO_MASK & (CANx->sFIFOMailBox[FIFO_number].RMDL >> CAN_RMDL_DATA3_OFFSET);
    receive_message->Data[4] = (uint8_t)CAN_DATA_FIFO_MASK & CANx->sFIFOMailBox[FIFO_number].RMDH;
    receive_message->Data[5] = (uint8_t)CAN_DATA_FIFO_MASK & (CANx->sFIFOMailBox[FIFO_number].RMDH >> CAN_RMDH_DATA5_OFFSET);
    receive_message->Data[6] = (uint8_t)CAN_DATA_FIFO_MASK & (CANx->sFIFOMailBox[FIFO_number].RMDH >> CAN_RMDH_DATA6_OFFSET);
    receive_message->Data[7] = (uint8_t)CAN_DATA_FIFO_MASK & (CANx->sFIFOMailBox[FIFO_number].RMDH >> CAN_RMDH_DATA7_OFFSET);
    /* Release the DATAFIFO */
    /* Release FIFO0 */
    if (FIFO_number == CAN_FIFO0)
    {
        CANx->RFF0 |= CAN_RELEASE_FIFO_0;
    }
    /* Release FIFO1 */
    else /* FIFO_number == CAN_FIFO1 */
    {
        CANx->RFF1 |= CAN_RELEASE_FIFO_1;
    }
}

/**
*\*\name   CAN_FIFO_Release
*\*\fun    Releases the specified DATAFIFO.
*\*\param  CANx:
*\*\            - CAN
*\*\param  FIFO_number :
*\*\            - CAN_FIFO0
*\*\            - CAN_FIFO1
*\*\return none
**/
void CAN_FIFO_Release(CAN_Module* CANx, uint8_t FIFO_number)
{
    /* Release FIFO0 */
    if (FIFO_number == CAN_FIFO0)
    {
        CANx->RFF0 |= CAN_RELEASE_FIFO_0;
    }
    /* Release FIFO1 */
    else /* FIFO_number == CAN_FIFO1 */
    {
        CANx->RFF1 |= CAN_RELEASE_FIFO_1;
    }
}

/**
*\*\name   CAN_Message_Pending_Get
*\*\fun    Returns the number of pending messages.
*\*\param  CANx :
*\*\            - CAN
*\*\param  FIFO_number :
*\*\            - CAN_FIFO0
*\*\            - CAN_FIFO1
*\*\return pending_value : 
*\*\            - CAN_FIFOX_PENDING_0
*\*\            - CAN_FIFOX_PENDING_1
*\*\            - CAN_FIFOX_PENDING_2
*\*\            - CAN_FIFOX_PENDING_3
**/
uint8_t CAN_Message_Pending_Get(CAN_Module* CANx, uint8_t FIFO_number)
{
    uint8_t pending_value = CAN_FIFOX_PENDING_0;
    if (FIFO_number == CAN_FIFO0)
    {
        pending_value = (uint8_t)(CANx->RFF0 & CAN_FIFO0_PENDING);
    }
    else if (FIFO_number == CAN_FIFO1)
    {
        pending_value = (uint8_t)(CANx->RFF1 & CAN_FIFO1_PENDING);
    }
    else
    {
        pending_value = CAN_FIFOX_PENDING_0;
    }
    return pending_value;
}

/**
*\*\name   CAN_Operating_Mode_Select
*\*\fun    Select the CAN Operation mode.
*\*\param  CANx:
*\*\            - CAN
*\*\param  CAN_OperatingMode :
*\*\               - CAN_OPERATING_INITMODE
*\*\               - CAN_OPERATING_NORMALMODE
*\*\               - CAN_OPERATING_SLEEPMODE
*\*\return status_value :
*\*\               - CAN_STS_Failed    CAN failed entering the specific mode
*\*\               - CAN_STS_Success   CAN Succeed entering the specific mode
**/
CAN_Status CAN_Operating_Mode_Select(CAN_Module* CANx, uint8_t CAN_operating_mode)
{
    CAN_Status status_value = CAN_STS_Failed;

    /* Timeout for INAK or also for SLAK bits*/
    uint32_t timeout_value = INIAK_TIMEOUT;

    if (CAN_operating_mode == CAN_OPERATING_INITMODE)
    {
        /* Request initialisation */
        CANx->MCTRL = (uint32_t)((CANx->MCTRL & (uint32_t)(~(uint32_t)CAN_SLEEP_REQUEST)) | CAN_INIT_REQUEST);

        /* Wait the acknowledge */
        while (((CANx->MSTS & CAN_MODE_MASK) != CAN_INIT_WAIT) && (timeout_value != 0))
        {
            timeout_value--;
        }
        if ((CANx->MSTS & CAN_MODE_MASK) != CAN_INIT_WAIT)
        {
            status_value = CAN_STS_Failed;
        }
        else
        {
            status_value = CAN_STS_Success;
        }
    }
    else if (CAN_operating_mode == CAN_OPERATING_NORMALMODE)
    {
        /* Request leave initialisation and sleep mode  and enter Normal mode */
        CANx->MCTRL &= (uint32_t)(~(CAN_SLEEP_REQUEST | CAN_INIT_REQUEST));

        /* Wait the acknowledge */
        while (((CANx->MSTS & CAN_MODE_MASK) != RESET) && (timeout_value != 0))
        {
            timeout_value--;
        }

        if ((CANx->MSTS & CAN_MODE_MASK) != RESET)
        {
            status_value = CAN_STS_Failed;
        }
        else
        {
            status_value = CAN_STS_Success;
        }
    }
    else if (CAN_operating_mode == CAN_OPERATING_SLEEPMODE)
    {
        /* Request Sleep mode */
        CANx->MCTRL = (uint32_t)((CANx->MCTRL & (uint32_t)(~(uint32_t)CAN_INIT_REQUEST)) | CAN_SLEEP_REQUEST);

        /* Wait the acknowledge */
        while (((CANx->MSTS & CAN_MODE_MASK) != CAN_SLEEP_WAIT) && (timeout_value != 0))
        {
            timeout_value--;
        }
        if ((CANx->MSTS & CAN_MODE_MASK) != CAN_SLEEP_WAIT)
        {
            status_value = CAN_STS_Failed;
        }
        else
        {
            status_value = CAN_STS_Success;
        }
    }
    else
    {
        status_value = CAN_STS_Failed;
    }

    return status_value;
}

/**
*\*\name   CAN_Sleep_Mode_Enter
*\*\fun    Enters the low power mode.
*\*\param  CANx:
*\*\            - CAN
*\*\return CAN_Status: 
*\*\            - CAN_STS_Success
*\*\            - CAN_STS_Failed
**/
CAN_Status CAN_Sleep_Mode_Enter(CAN_Module* CANx) 
{
    /* Request Sleep mode */
    CANx->MCTRL = (((CANx->MCTRL) & (uint32_t)(~(uint32_t)CAN_INIT_REQUEST)) | CAN_SLEEP_REQUEST);

    /* Sleep mode status */
    if ((CANx->MSTS & CAN_MODE_MASK) == CAN_SLEEP_WAIT)
    {
        /* Sleep mode entered */
        return CAN_STS_Success;
    }
    else
    {
        /* Sleep mode not entered */
        return CAN_STS_Failed;
    }
}

/**
*\*\name   CAN_Wake_Up_Enable
*\*\fun    Wakes the CAN up.
*\*\param  CANx:
*\*\            - CAN
*\*\return CAN_Status: 
*\*\            - CAN_STS_Success
*\*\            - CAN_STS_Failed
**/
CAN_Status CAN_Wake_Up_Enable(CAN_Module* CANx)
{
    uint32_t timeout_value   = SLPAK_TIMEOUT;

    /* Wake up request */
    CANx->MCTRL &= ~(uint32_t)CAN_SLEEP_REQUEST;

    /* Sleep mode status */
    while (((CANx->MSTS & CAN_SLEEP_WAIT) == CAN_SLEEP_WAIT) && (timeout_value != 0x00))
    {
        timeout_value--;
    }
    if ((CANx->MSTS & CAN_SLEEP_WAIT) != CAN_SLEEP_WAIT)
    {
        /* wake up done : Sleep mode exited */
        return CAN_STS_Success;
    }
    else
    {
        return CAN_STS_Failed;
    }
}

/**
*\*\name   CAN_Last_Error_Code_Get
*\*\fun    Returns the CANx's last error code (LEC).
*\*\param  CANx:
*\*\            - CAN
*\*\return error_code_value :
*\*\            - CAN_ERRORCODE_NOERR            No Error
*\*\            - CAN_ERRORCODE_STUFFERR         Stuff Error
*\*\            - CAN_ERRORCODE_FORMERR          Form Error
*\*\            - CAN_ERRORCODE_ACKERR           Acknowledgment Error
*\*\            - CAN_ERRORCODE_BITRECESSIVEERR  Bit Recessive Error
*\*\            - CAN_ERRORCODE_BITDOMINANTERR   Bit Dominant Error
*\*\            - CAN_ERRORCODE_CRCERR           CRC Error
*\*\            - CAN_ERRORCODE_SWSETERR         Software Set Error
**/
uint8_t CAN_Last_Error_Code_Get(CAN_Module* CANx)
{
    uint8_t error_code_value = 0;

    /* Get the error code*/
    error_code_value = (((uint8_t)CANx->ESTS) & (uint8_t)CAN_ERRORCODE_SWSETERR);

    /* Return the error code*/
    return error_code_value;
}

/**
*\*\name   CAN_Receive_Error_Counter_Get
*\*\fun    Returns the CANx Receive Error Counter (REC).
*\*\note   In case of an error during reception, this counter is incremented
*\*\       by 1 or by 8 depending on the error condition as defined by the CAN
*\*\       standard. After every successful reception, the counter is
*\*\       decremented by 1 or reset to 120 if its value was higher than 128.
*\*\       When the counter value exceeds 127, the CAN controller enters the
*\*\       error passive state.
*\*\param  CANx:
*\*\            - CAN
*\*\return counter_value:
*\*\            - It ranges from 0 to 127
**/
uint8_t CAN_Receive_Error_Counter_Get(CAN_Module* CANx)
{
    uint8_t counter_value = 0;

    /* Get the Receive Error Counter*/
    counter_value = (uint8_t)((CANx->ESTS & CAN_RX_ERROR_COUNT) >> CAN_ESTS_RX_ERROR_OFFSET);

    /* Return the Receive Error Counter*/
    return counter_value;
}

/**
*\*\name   CAN_LSB_Transmit_Error_Counter_Get
*\*\fun    Returns the LSB of the 9-bit CANx Transmit Error Counter(TEC).
*\*\param  CAN to to select the CAN peripheral.
*\*\return counter_value:
*\*\            - It ranges from 0 to 127
**/
uint8_t CAN_LSB_Transmit_Error_Counter_Get(CAN_Module* CANx)
{
    uint8_t counter_value = 0;

    /* Get the LSB of the 9-bit CANx Transmit Error Counter(TEC) */
    counter_value = (uint8_t)((CANx->ESTS & CAN_TX_ERROR_COUNT) >> CAN_ESTS_TX_ERROR_OFFSET);

    /* Return the LSB of the 9-bit CANx Transmit Error Counter(TEC) */
    return counter_value;
}

/**
*\*\name   CAN_Config_Interrupt_Enable
*\*\fun    Enables the specified CANx interrupts.
*\*\param  CANx:
*\*\               - CAN
*\*\param  CAN_interrupt :
*\*\               - CAN_INT_TME,
*\*\               - CAN_INT_FMP0,
*\*\               - CAN_INT_FF0,
*\*\               - CAN_INT_FOV0,
*\*\               - CAN_INT_FMP1,
*\*\               - CAN_INT_FF1,
*\*\               - CAN_INT_FOV1,
*\*\               - CAN_INT_EWG,
*\*\               - CAN_INT_EPV,
*\*\               - CAN_INT_BOF,
*\*\               - CAN_INT_LEC,
*\*\               - CAN_INT_ERR,
*\*\               - CAN_INT_WKU,
*\*\               - CAN_INT_SLK.
*\*\return none
**/
void CAN_Config_Interrupt_Enable(CAN_Module* CANx, uint32_t CAN_interrupt)
{
    /* Enable the selected CANx interrupt */
    CANx->INTE |= CAN_interrupt;
}

/**
*\*\name   CAN_Config_Interrupt_Disable
*\*\fun    Disables the specified CANx interrupts.
*\*\param  CANx:
*\*\               - CAN
*\*\param  CAN_interrupt :
*\*\               - CAN_INT_TME,
*\*\               - CAN_INT_FMP0,
*\*\               - CAN_INT_FF0,
*\*\               - CAN_INT_FOV0,
*\*\               - CAN_INT_FMP1,
*\*\               - CAN_INT_FF1,
*\*\               - CAN_INT_FOV1,
*\*\               - CAN_INT_EWG,
*\*\               - CAN_INT_EPV,
*\*\               - CAN_INT_BOF,
*\*\               - CAN_INT_LEC,
*\*\               - CAN_INT_ERR,
*\*\               - CAN_INT_WKU,
*\*\               - CAN_INT_SLK.
*\*\return none
**/
void CAN_Config_Interrupt_Disable(CAN_Module* CANx, uint32_t CAN_interrupt)
{
    /* Disable the selected CANx interrupt */
    CANx->INTE &= ~CAN_interrupt;
}



/**
*\*\name   CAN_Flag_status_Get
*\*\fun    Checks whether the specified CAN flag is set or not.
*\*\param  CANx:
*\*\                - CAN
*\*\param  CAN_flag :
*\*\                - CAN_FLAG_EWGFL
*\*\                - CAN_FLAG_EPVFL
*\*\                - CAN_FLAG_BOFFL
*\*\                - CAN_FLAG_LEC
*\*\                - CAN_FLAG_RQCPM0
*\*\                - CAN_FLAG_RQCPM1
*\*\                - CAN_FLAG_RQCPM2
*\*\                - CAN_FLAG_FFMP1
*\*\                - CAN_FLAG_FFULL1
*\*\                - CAN_FLAG_FFOVR1
*\*\                - CAN_FLAG_FFMP0
*\*\                - CAN_FLAG_FFULL0
*\*\                - CAN_FLAG_FFOVR0
*\*\                - CAN_FLAG_WKU
*\*\                - CAN_FLAG_SLAK
*\*\return  FlagStatus:
*\*\                - SET
*\*\                - RESET
**/
FlagStatus CAN_Flag_status_Get(CAN_Module* CANx, uint32_t CAN_flag)
{
    if ((CAN_flag & CAN_FLAGS_ESTS) != (uint32_t)RESET)
    {
        /* Check the status of the specified CAN flag */
        if ((CANx->ESTS & (CAN_flag & CAN_FLAG_MASK)) != (uint32_t)RESET)
        {
            /* CAN_flag is set */
            return SET;
        }
        else
        {
            /* CAN_flag is reset */
            return RESET;
        }
    }
    else if ((CAN_flag & CAN_FLAGS_MSTS) != (uint32_t)RESET)
    {
        /* Check the status of the specified CAN flag */
        if ((CANx->MSTS & (CAN_flag & CAN_FLAG_MASK)) != (uint32_t)RESET)
        {
            /* CAN_flag is set */
            return SET;
        }
        else
        {
            /* CAN_flag is reset */
            return RESET;
        }
    }
    else if ((CAN_flag & CAN_FLAGS_TSTS) != (uint32_t)RESET)
    {
        /* Check the status of the specified CAN flag */
        if ((CANx->TSTS & (CAN_flag & CAN_FLAG_MASK)) != (uint32_t)RESET)
        {
            /* CAN_flag is set */
            return SET;
        }
        else
        {
            /* CAN_flag is reset */
            return RESET;
        }
    }
    else if ((CAN_flag & CAN_FLAGS_RFF0) != (uint32_t)RESET)
    {
        /* Check the status of the specified CAN flag */
        if ((CANx->RFF0 & (CAN_flag & CAN_FLAG_MASK)) != (uint32_t)RESET)
        {
            /* CAN_flag is set */
            return SET;
        }
        else
        {
            /* CAN_flag is reset */
            return RESET;
        }
    }
    else /* If(CAN_flag & CAN_FLAGS_RFF1 != (uint32_t)RESET) */
    {
        /* Check the status of the specified CAN flag */
        if ((uint32_t)(CANx->RFF1 & (CAN_flag & CAN_FLAG_MASK)) != (uint32_t)RESET)
        {
            /* CAN_flag is set */
            return SET;
        }
        else
        {
            /* CAN_flag is reset */
            return RESET;
        }
    }
}

/**
*\*\name   CAN_Flag_Status_Clear
*\*\fun    Clears the CAN's flag status.
*\*\param  CANx:
*\*\                  - CAN
*\*\param  CAN_flag :
*\*\                  - CAN_FLAG_RQCPM0
*\*\                  - CAN_FLAG_RQCPM1
*\*\                  - CAN_FLAG_RQCPM2
*\*\                  - CAN_FLAG_FFULL1
*\*\                  - CAN_FLAG_FFOVR1
*\*\                  - CAN_FLAG_FFULL0
*\*\                  - CAN_FLAG_FFOVR0
*\*\                  - CAN_FLAG_WKU
*\*\                  - CAN_FLAG_SLAK
*\*\                  - CAN_FLAG_LEC
*\*\return none
**/
void CAN_Flag_Status_Clear(CAN_Module* CANx, uint32_t CAN_flag)
{
    uint32_t temp_value = 0;

    if (CAN_flag == CAN_FLAG_LEC) /* ESTS register */
    {
        /* Clear the selected CAN flags */
        CANx->ESTS = (uint32_t)RESET;
    }
    else /* MSTS or TSTS or RFF0 or RFF1 */
    {
        temp_value = CAN_flag & CAN_FLAG_MASK;

        if ((CAN_flag & CAN_FLAGS_RFF0) != (uint32_t)RESET)
        {
            /* Receive Flags */
            CANx->RFF0 = (uint32_t)(temp_value);
        }
        else if ((CAN_flag & CAN_FLAGS_RFF1) != (uint32_t)RESET)
        {
            /* Receive Flags */
            CANx->RFF1 = (uint32_t)(temp_value);
        }
        else if ((CAN_flag & CAN_FLAGS_TSTS) != (uint32_t)RESET)
        {
            /* Transmit Flags */
            CANx->TSTS = (uint32_t)(temp_value);
        }
        else /* If((CAN_flag & CAN_FLAGS_MSTS)!=(uint32_t)RESET) */
        {
            /* Operating mode Flags */
            CANx->MSTS = (uint32_t)(temp_value);
        }
    }
}

/**
*\*\name   CAN_Interrupt_Status_Get
*\*\fun    Checks whether the specified CANx interrupt has occurred or not.
*\*\param  CANx:
*\*\                    -  CAN
*\*\param  CAN_interrupt :
*\*\                    -  CAN_INT_TME
*\*\                    -  CAN_INT_FMP0
*\*\                    -  CAN_INT_FF0
*\*\                    -  CAN_INT_FOV0
*\*\                    -  CAN_INT_FMP1
*\*\                    -  CAN_INT_FF1
*\*\                    -  CAN_INT_FOV1
*\*\                    -  CAN_INT_WKU
*\*\                    -  CAN_INT_SLK
*\*\                    -  CAN_INT_EWG
*\*\                    -  CAN_INT_EPV
*\*\                    -  CAN_INT_BOF
*\*\                    -  CAN_INT_LEC
*\*\                    -  CAN_INT_ERR
*\*\return INTStatus : 
*\*\                    - SET
*\*\                    - RESET
**/
INTStatus CAN_Interrupt_Status_Get(CAN_Module* CANx, uint32_t CAN_interrupt)
{
    INTStatus status_value = RESET;
    /* check the enable interrupt bit */
    if ((CANx->INTE & CAN_interrupt) != RESET)
    {
        /* in case the Interrupt is enabled, .... */
        switch (CAN_interrupt)
        {
            case CAN_INT_TME:
                /* Check CAN_TSTS_RQCPx bits */
                status_value = Interrupt_Status_Check(CANx->TSTS, CAN_MAILBOX0_RQ_OK | CAN_MAILBOX1_RQ_OK | CAN_MAILBOX2_RQ_OK);
                break;
            case CAN_INT_FMP0:
                /* Check CAN_RFF0_FFMP0 bit */
                status_value = Interrupt_Status_Check(CANx->RFF0, CAN_FIFO0_PENDING);
                break;
            case CAN_INT_FF0:
                /* Check CAN_RFF0_FFULL0 bit */
                status_value = Interrupt_Status_Check(CANx->RFF0, CAN_FULL_FIFO_0);
                break;
            case CAN_INT_FOV0:
                /* Check CAN_RFF0_FFOVR0 bit */
                status_value = Interrupt_Status_Check(CANx->RFF0, CAN_OVER_FIFO_0);
                break;
            case CAN_INT_FMP1:
                /* Check CAN_RFF1_FFMP1 bit */
                status_value = Interrupt_Status_Check(CANx->RFF1, CAN_FIFO1_PENDING);
                break;
            case CAN_INT_FF1:
                /* Check CAN_RFF1_FFULL1 bit */
                status_value = Interrupt_Status_Check(CANx->RFF1, CAN_FULL_FIFO_1);
                break;
            case CAN_INT_FOV1:
                /* Check CAN_RFF1_FFOVR1 bit */
                status_value = Interrupt_Status_Check(CANx->RFF1, CAN_OVER_FIFO_1);
                break;
            case CAN_INT_WKU:
                /* Check CAN_MSTS_WKUINT bit */
                status_value = Interrupt_Status_Check(CANx->MSTS, CAN_WAKE_UP_INT);
                break;
            case CAN_INT_SLK:
                /* Check CAN_MSTS_SLAKINT bit */
                status_value = Interrupt_Status_Check(CANx->MSTS, CAN_SLEEP_WAITINT);
                break;
            case CAN_INT_EWG:
                /* Check CAN_ESTS_EWGFL bit */
                status_value = Interrupt_Status_Check(CANx->ESTS, CAN_ERROR_WARN_FLAG);
                break;
            case CAN_INT_EPV:
                /* Check CAN_ESTS_EPVFL bit */
                status_value = Interrupt_Status_Check(CANx->ESTS, CAN_ERROR_PASS_FLAG);
                break;
            case CAN_INT_BOF:
                /* Check CAN_ESTS_BOFFL bit */
                status_value = Interrupt_Status_Check(CANx->ESTS, CAN_BUS_OFF_FLAG);
                break;
            case CAN_INT_LEC:
                /* Check CAN_ESTS_LEC bit */
                status_value = Interrupt_Status_Check(CANx->ESTS, CAN_ERRORCODE_SWSETERR);
                break;
            case CAN_INT_ERR:
                /* Check CAN_MSTS_ERRINT bit */
                status_value = Interrupt_Status_Check(CANx->MSTS, CAN_ERROR_INT);
                break;
            default:
                /* in case of error, return RESET */
                status_value = RESET;
                break;
        }
    }
    else
    {
        /* in case the Interrupt is not enabled, return RESET */
        status_value = RESET;
    }

    /* Return the CAN_interrupt status */
    return status_value;
}

/**
*\*\name   CAN_Interrupt_Status_Clear
*\*\fun    Clears the CANx's interrupt status.
*\*\param  CANx:
*\*\                -  CAN
*\*\param  CAN_interrupt :
*\*\                -  CAN_INT_TME
*\*\                -  CAN_INT_FF0
*\*\                -  CAN_INT_FOV0
*\*\                -  CAN_INT_FF1
*\*\                -  CAN_INT_FOV1
*\*\                -  CAN_INT_WKU
*\*\                -  CAN_INT_SLK
*\*\                -  CAN_INT_EWG
*\*\                -  CAN_INT_EPV
*\*\                -  CAN_INT_BOF
*\*\                -  CAN_INT_LEC
*\*\                -  CAN_INT_ERR
*\*\return none
**/
void CAN_Interrupt_Status_Clear(CAN_Module* CANx, uint32_t CAN_interrupt)
{
    switch (CAN_interrupt)
    {
    case CAN_INT_TME:
        /* Clear CAN_TSTS_RQCPx (rc_w1)*/
        CANx->TSTS = CAN_MAILBOX0_RQ_OK | CAN_MAILBOX1_RQ_OK | CAN_MAILBOX2_RQ_OK;
        break;
    case CAN_INT_FF0:
        /* Clear CAN_RFF0_FFULL0 (rc_w1)*/
        CANx->RFF0 = CAN_FULL_FIFO_0;
        break;
    case CAN_INT_FOV0:
        /* Clear CAN_RFF0_FFOVR0 (rc_w1)*/
        CANx->RFF0 = CAN_OVER_FIFO_0;
        break;
    case CAN_INT_FF1:
        /* Clear CAN_RFF1_FFULL1 (rc_w1)*/
        CANx->RFF1 = CAN_FULL_FIFO_1;
        break;
    case CAN_INT_FOV1:
        /* Clear CAN_RFF1_FFOVR1 (rc_w1)*/
        CANx->RFF1 = CAN_OVER_FIFO_1;
        break;
    case CAN_INT_WKU:
        /* Clear CAN_MSTS_WKUINT (rc_w1)*/
        CANx->MSTS = CAN_WAKE_UP_INT;
        break;
    case CAN_INT_SLK:
        /* Clear CAN_MSTS_SLAKINT (rc_w1)*/
        CANx->MSTS = CAN_SLEEP_WAITINT;
        break;
    case CAN_INT_EWG:
        /* Clear CAN_MSTS_ERRINT (rc_w1) */
        CANx->MSTS = CAN_ERROR_INT;
        /* Note : the corresponding Flag is cleared by hardware depending
                  of the CAN Bus status*/
        break;
    case CAN_INT_EPV:
        /* Clear CAN_MSTS_ERRINT (rc_w1) */
        CANx->MSTS = CAN_ERROR_INT;
        /* Note : the corresponding Flag is cleared by hardware depending
                  of the CAN Bus status*/
        break;
    case CAN_INT_BOF:
        /* Clear CAN_MSTS_ERRINT (rc_w1) */
        CANx->MSTS = CAN_ERROR_INT;
        /* Note : the corresponding Flag is cleared by hardware depending
                  of the CAN Bus status*/
        break;
    case CAN_INT_LEC:
        /*  Clear LEC bits */
        CANx->ESTS = RESET;
        /* Clear CAN_MSTS_ERRINT (rc_w1) */
        CANx->MSTS = CAN_ERROR_INT;
        break;
    case CAN_INT_ERR:
        /*Clear LEC bits */
        CANx->ESTS = RESET;
        /* Clear CAN_MSTS_ERRINT (rc_w1) */
        CANx->MSTS = CAN_ERROR_INT;
        /* Note : BOFF, EPVF and EWGF Flags are cleared by hardware depending
            of the CAN Bus status*/
        break;
    default:
        break;
    }
}

/**
*\*\name   Interrupt_Status_Check
*\*\fun    Checks whether the CAN interrupt has occurred or not.
*\*\param  CAN_register specifies the CAN interrupt register to check.
*\*\param  interrupt_bit specifies the interrupt source bit to check.
*\*\return INTStatus:
*\*\                    - SET
*\*\                    - RESET
**/
INTStatus Interrupt_Status_Check(uint32_t CAN_register, uint32_t interrupt_bit)
{
    if ((CAN_register & interrupt_bit) != (uint32_t)RESET)
    {
        /* CAN_interrupt is set */
        return SET;
    }
    else
    {
        /* CAN_interrupt is reset */
        return RESET;
    }
}



/**
*\*\name   CAN_Software_Reset
*\*\fun    Enable software reset.
*\*\param  CANx:
*\*\               - CAN
*\*\return none
**/
void CAN_Software_Reset(CAN_Module* CANx)
{
    /* Enable software reset */
    CANx->MCTRL |= CAN_SW_MASTER_RESET;
}


/**
*\*\name   CAN_Transmit_Fail_Status_Get
*\*\fun    Get the status of sending email failure.
*\*\param  CANx:
*\*\               - CAN
*\*\param  mailbox_queue:
*\*\               - CAN_TXSTS_MAILBOX0
*\*\               - CAN_TXSTS_MAILBOX1
*\*\               - CAN_TXSTS_MAILBOX2
*\*\return FlagStatus:
*\*\               - SET
*\*\               - RESET
**/
FlagStatus CAN_Transmit_Fail_Status_Get(CAN_Module* CANx,uint8_t mailbox_queue)
{
    FlagStatus status_value = RESET;
    switch (mailbox_queue)
    {
        case (CAN_TXSTS_MAILBOX0):
            if((CAN->TSTS & CAN_TSTS_TERRM0) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        case (CAN_TXSTS_MAILBOX1):
            if((CAN->TSTS & CAN_TSTS_TERRM1) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        case (CAN_TXSTS_MAILBOX2):
            if((CAN->TSTS & CAN_TSTS_TERRM2) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        default:
            break;
    }
    return status_value;
}

/**
*\*\name   CAN_Arbitration_Lost_Status_Get
*\*\fun    Get the status of arbitration lost.
*\*\param  CANx:
*\*\               - CAN
*\*\param  mailbox_queue:
*\*\               - CAN_TXSTS_MAILBOX0
*\*\               - CAN_TXSTS_MAILBOX1
*\*\               - CAN_TXSTS_MAILBOX2
*\*\return FlagStatus:
*\*\               - SET
*\*\               - RESET
**/
FlagStatus CAN_Arbitration_Lost_Status_Get(CAN_Module* CANx,uint8_t mailbox_queue)
{
    FlagStatus status_value = RESET;
    switch (mailbox_queue)
    {
        case (CAN_TXSTS_MAILBOX0):
            if((CAN->TSTS & CAN_TSTS_ALSTM0) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        case (CAN_TXSTS_MAILBOX1):
            if((CAN->TSTS & CAN_TSTS_ALSTM1) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        case (CAN_TXSTS_MAILBOX2):
            if((CAN->TSTS & CAN_TSTS_ALSTM2) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        default:
            break;
    }
    return status_value;
}


/**
*\*\name   CAN_Flag_Lowest_Priority_Get
*\*\fun    Get the flag of lowest priority.
*\*\param  CANx:
*\*\               - CAN
*\*\param  mailbox_queue:
*\*\               - CAN_TXSTS_MAILBOX0
*\*\               - CAN_TXSTS_MAILBOX1
*\*\               - CAN_TXSTS_MAILBOX2
*\*\return FlagStatus:
*\*\               - SET
*\*\               - RESET
**/
FlagStatus CAN_Flag_Lowest_Priority_Get(CAN_Module* CANx,uint8_t mailbox_queue)
{
    FlagStatus status_value = RESET;
    switch (mailbox_queue)
    {
        case (CAN_TXSTS_MAILBOX0):
            if((CAN->TSTS & CAN_TSTS_LOWM0) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        case (CAN_TXSTS_MAILBOX1):
            if((CAN->TSTS & CAN_TSTS_LOWM1) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        case (CAN_TXSTS_MAILBOX2):
            if((CAN->TSTS & CAN_TSTS_LOWM2) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        default:
            break;
    }
    return status_value;
}


/**
*\*\name   CAN_Flag_Lowest_Priority_Get
*\*\fun    Get the flag of lowest priority.
*\*\param  CANx:
*\*\               - CAN
*\*\param  mailbox_queue:
*\*\               - CAN_TXSTS_MAILBOX0
*\*\               - CAN_TXSTS_MAILBOX1
*\*\               - CAN_TXSTS_MAILBOX2
*\*\return FlagStatus:
*\*\               - SET
*\*\               - RESET
**/
FlagStatus CAN_Flag_Transmit_Mailbox_Empty_Get(CAN_Module* CANx,uint8_t mailbox_queue)
{
    FlagStatus status_value = RESET;
    switch (mailbox_queue)
    {
        case (CAN_TXSTS_MAILBOX0):
            if((CAN->TSTS & CAN_TX_MAILBOX_EMPTY0) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        case (CAN_TXSTS_MAILBOX1):
            if((CAN->TSTS & CAN_TX_MAILBOX_EMPTY1) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        case (CAN_TXSTS_MAILBOX2):
            if((CAN->TSTS & CAN_TX_MAILBOX_EMPTY2) == RESET)
            {
                status_value = RESET;
            }
            else
            {
                status_value = SET;
            }
            break;
        default:
            break;
    }
    return status_value;
}


/**
*\*\name   CAN_Receive_Signal_Get
*\*\fun    Returns the CANx's receive signal value (RXS).
*\*\param  CANx:
*\*\            - CAN
*\*\return FlagStatus:
*\*\            - SET
*\*\            - RESET
**/
FlagStatus CAN_Receive_Signal_Get(CAN_Module* CANx)
{    
    if((CANx->MSTS & CAN_RX_SIGNAL) == RESET)
    {
        return RESET;
    }
    else
    {
        return SET;
    }
}


/**
*\*\name   CAN_Last_Sample_Point_Get
*\*\fun    Returns the CANx's Last sample point (LSMP).
*\*\param  CANx:
*\*\            - CAN
*\*\return FlagStatus:
*\*\            - SET
*\*\            - RESET
**/
FlagStatus CAN_Last_Sample_Point_Get(CAN_Module* CANx)
{    
    if((CANx->MSTS & CAN_LAST_SAMPLE_POINT) == RESET)
    {
        return RESET;
    }
    else
    {
        return SET;
    }
}


/**
*\*\name   CAN_Receive_Mode_Get
*\*\fun    Returns the CANx's receive mode (RXMD).
*\*\param  CANx:
*\*\            - CAN
*\*\return FlagStatus:
*\*\            - SET
*\*\            - RESET
**/
FlagStatus CAN_Receive_Mode_Get(CAN_Module* CANx)
{    
    if((CANx->MSTS & CAN_RX_MODE) == RESET)
    {
        return RESET;
    }
    else
    {
        return SET;
    }
}


/**
*\*\name   CAN_Transmit_Mode_Get
*\*\fun    Returns the CANx's transmit mode (TXMD).
*\*\param  CANx:
*\*\            - CAN
*\*\return FlagStatus:
*\*\            - SET
*\*\            - RESET
**/
FlagStatus CAN_Transmit_Mode_Get(CAN_Module* CANx)
{    
    if((CANx->MSTS & CAN_TX_MODE) == RESET)
    {
        return RESET;
    }
    else
    {
        return SET;
    }
}



/**
*\*\name   CAN_Mailbox_Code_Get
*\*\fun    Returns the CANx's mailbox code (CODE[1:0]).
*\*\param  CANx:
*\*\            - CAN
*\*\return  mailbox_queue :
*\*\            - CAN_TXSTS_MAILBOX0
*\*\            - CAN_TXSTS_MAILBOX1
*\*\            - CAN_TXSTS_MAILBOX2
*\*\            - CAN_TXSTS_NOMAILBOX
**/
uint8_t CAN_Mailbox_Code_Get(CAN_Module* CANx)
{
    uint8_t mailbox_queue = CAN_TXSTS_MAILBOX0;    
    if((CANx->TSTS & CAN_TX_MAILBOX_CODE) == CAN_TXSTS_MAILBOX0)
    {
        mailbox_queue = CAN_TXSTS_MAILBOX0;
    }
    else if((CANx->TSTS & CAN_TX_MAILBOX_CODE) == CAN_TX_MAILBOX_0)
    {
        mailbox_queue = CAN_TXSTS_MAILBOX1;
    }
    else if((CANx->TSTS & CAN_TX_MAILBOX_CODE) == CAN_TX_MAILBOX_1)
    {
        mailbox_queue = CAN_TXSTS_MAILBOX2;
    }
    else
    {
        mailbox_queue = CAN_TXSTS_NOMAILBOX;
    }
    
    return mailbox_queue;
}



