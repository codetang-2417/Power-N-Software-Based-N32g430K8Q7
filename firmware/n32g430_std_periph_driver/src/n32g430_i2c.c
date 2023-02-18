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
*\*\file n32g430_i2c.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/
#include "n32g430_i2c.h"
#include "n32g430_rcc.h"

//** I2C Private Defines **/

/** I2C Driving Functions Declaration **/


/**
*\*\name    I2C_Reset.
*\*\fun     Reset the I2Cx registers.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Reset(I2C_Module* I2Cx)
{
  
    if (I2Cx == I2C1)
    {
        /* I2C1 Reset */
        RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_I2C1);
    }
    else
    {
        /* I2C2 Reset */
        RCC_APB1_Peripheral_Reset(RCC_APB1_PERIPH_I2C2);
    }
}

/**
*\*\name    I2C_Initializes.
*\*\fun     Initializes the I2Cx peripheral according to the specified
*\*\        parameters in the I2C_InitParam
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_InitParam :
*\*\          - ClkSpeed(common speed:100000(100KHz) - 400000(400KHz) - 1000000(1MHz)):
*\*\            - between 1 to 1000000 
*\*\          - BusMode:
*\*\            - I2C_BUSMODE_I2C
*\*\            - I2C_BUSMODE_SMBDEVICE
*\*\            - I2C_BUSMODE_SMBHOST
*\*\          - DutyCycle(If the ClkSpeed does not exceed 100KHz,duty is fixed at 1:1,
*\*\                      otherwise it can be configured as 2:1 or 16:9):
*\*\            - I2C_SMDUTYCYCLE_1  
*\*\            - I2C_FMDUTYCYCLE_16_9
*\*\            - I2C_FMDUTYCYCLE_2
*\*\          - OwnAddr1:
*\*\            - between 0 to 0x3FF 
*\*\          - AckEnable:
*\*\            - I2C_ACKEN
*\*\            - I2C_ACKDIS
*\*\          - AddrMode:
*\*\            - I2C_ADDR_MODE_7BIT
*\*\            - I2C_ADDR_MODE_10BIT
*\*\return  none
**/
void I2C_Initializes(I2C_Module* I2Cx, I2C_InitType* I2C_InitParam)
{
    I2C_Clock_Speed_Config(I2Cx, I2C_InitParam->ClkSpeed, I2C_InitParam->DutyCycle);
    I2C_Bus_Mode_Config(I2Cx, I2C_InitParam->BusMode);
    I2C_Acknowledgement_Config(I2Cx, I2C_InitParam->AckEnable);
    I2C_Addressing_Mode_Config(I2Cx, I2C_InitParam->AddrMode);
    I2C_Own_Addr1_Config(I2Cx, I2C_InitParam->OwnAddr1);
}

/**
*\*\name    I2C_Clock_Speed_Config.
*\*\fun     Initializes the clock speed.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   clk_speed 
*\*\          - between 1 to 1000000
*\*\param   duty_cycle:
*\*\          - I2C_SMDUTYCYCLE_1
*\*\          - I2C_FMDUTYCYCLE_16_9
*\*\          - I2C_FMDUTYCYCLE_2
*\*\return  none
**/
void I2C_Clock_Speed_Config(I2C_Module* I2Cx, uint32_t clk_speed, uint16_t duty_cycle)
{
    uint16_t temp_value = 0, freq_value = 0, speed_value = 0x04;
    uint32_t pclk_value  = 8000000, trise_value = 0;
    RCC_ClocksType rcc_clocks;

    /* Get APB1 frequency value */
    RCC_Clocks_Frequencies_Value_Get(&rcc_clocks);

    /** I2Cx CTRL2 config **/
    /* Get the I2Cx CTRL2 value */
    temp_value = I2Cx->CTRL2;
    /* Clear frequency FREQ[5:0] bits */
    temp_value &= I2C_CLKFREQ_RESET;
    /* Get APB1 frequency value */
    pclk_value = rcc_clocks.Pclk1Freq;  
    /* Set frequency bits depending on APB1 pclk value */
    freq_value = (uint16_t)(pclk_value / 1000000);
	if (freq_value > APB1_FREQ_MAX_VALUE) 
    {
        freq_value = APB1_FREQ_MAX_VALUE;
    }
	/* Write to I2Cx CTRL2 */
    temp_value |= freq_value;
    I2Cx->CTRL2 = temp_value;
   
    /** I2Cx CLKCTRL config **/
    /* Disable the selected I2C peripheral to configure TMRISE */
    I2Cx->CTRL1 &= I2C_EN_RESET;  
    /* Get the I2Cx TMRISE value */
    trise_value = I2Cx->TMRISE;    
    /* Clear TMRISE[5:0] bits */
    trise_value &= (~I2C_TMRISE_MASK);
    /* Reset temp_value */
    /* Clear CLKCTRL:FSMODE, DUTY and CLKCTRL[11:0] bits */
    temp_value = 0;
    
    /*If the ClkSpeed does not exceed 100KHz, mode(FSMODE[bit15]) is standard, duty is fixed at 1:1,ignore DUTY[bit14] */
    /* Configure speed in SM(standard mode) */
    if (clk_speed <= CLK_SPEED_100K)
    {
        /* Standard mode speed calculate: Tlow/Thigh = 1 */
        speed_value = (uint16_t)(pclk_value / (clk_speed * 2)); 
        /* Test if CLKCTRL value is under 0x4*/
        if (speed_value < SM_CLKCTRL_LOW_LIMIT)
        {
            /* Set minimum allowed value */
            speed_value = SM_CLKCTRL_LOW_LIMIT;
        }
        /* Set speed value for standard mode */
        temp_value |= speed_value;   
        /* Set Maximum Rise Time for standard mode */
        trise_value |= ((freq_value + 1) & I2C_TMRISE_MASK);         
    }
    /*If ClkSpeed exceeds 100KHz, mode(FSMODE[bit15]) is fast, duty(DUTY[bit14]) can be configured as 2:1 or 16:9 */
    /* Configure speed in FM(fast mode) */
    else 
    {
        if (duty_cycle != I2C_FMDUTYCYCLE_16_9)
        {
            /* Fast mode speed calculate: Tlow/Thigh = 2 */
            speed_value = (uint16_t)(pclk_value / (clk_speed * 3));
        }
        else /*duty_cycle == I2C_FMDUTYCYCLE_16_9*/
        {
            /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
            speed_value = (uint16_t)(pclk_value / (clk_speed * 25));
            /* Set DUTY bit */
            speed_value |= I2C_FMDUTYCYCLE_16_9;
        }

        /* Test if CLKCTRL value is under 0x1*/
        if ((speed_value & I2C_CLKCTRL_SET) < FM_CLKCTRL_LOW_LIMIT)
        {
            /* Set minimum allowed value */
            speed_value |= (uint16_t)FM_CLKCTRL_LOW_LIMIT;
        }
        /* Set speed value and set F/S bit for fast mode */
        temp_value |= (uint16_t)(speed_value | I2C_FSMODE_SET);
        
        /* Set Maximum Rise Time for fast mode */
        /* if APB1 frequency is 32MHz,period = 1/32*1000ns,so trise_value = period/TRISE+1=32*TRISE/1000+1,See the manual for details*/
        if(clk_speed <= CLK_SPEED_400K)   /* 100KHz~400KHz */ 
        {
            trise_value |= (((uint16_t)(((freq_value * (uint16_t)FM_TRISE_400K) / (uint16_t)1000) + (uint16_t)1)) & I2C_TMRISE_MASK);
        }
        else  /* 400KHz~1MHz */ 
        {
            trise_value |= (((uint16_t)(((freq_value * (uint16_t)FM_TRISE_1M) / (uint16_t)1000) + (uint16_t)1)) & I2C_TMRISE_MASK);
        }
    }
    /* Write to I2Cx TMRISE */
    I2Cx->TMRISE = trise_value;
    /* Write to I2Cx CLKCTRL */
    I2Cx->CLKCTRL = temp_value; 
    /* Enable the selected I2C peripheral */
    I2Cx->CTRL1 |= I2C_EN_SET;
}

/**
*\*\name    I2C_Bus_Mode_Config.
*\*\fun     Initializes the bus mode.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   mode
*\*\          - I2C_BUSMODE_I2C
*\*\          - I2C_BUSMODE_SMBDEVICE
*\*\          - I2C_BUSMODE_SMBHOST
*\*\return  none
**/
void I2C_Bus_Mode_Config(I2C_Module* I2Cx, uint16_t mode)
{
    uint16_t temp_value = 0;

    /* Get the I2Cx CTRL1 value */
    temp_value = I2Cx->CTRL1;
    /* Clear SMBTYPE and SMBUS bits */
    temp_value &= I2C_BUSMODE_CLR_MASK;
    /* Set SMBTYPE and SMBUS bits according to mode value */
    temp_value |= (uint16_t)((uint32_t)mode);
    /* Set I2Cx CTRL1 */
    I2Cx->CTRL1 = temp_value;
}

/**
*\*\name    I2C_Acknowledgement_Config.
*\*\fun     Initializes the acknowledgement.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   ack
*\*\          - I2C_ACKEN
*\*\          - I2C_ACKDIS
*\*\return  none
**/
void I2C_Acknowledgement_Config(I2C_Module* I2Cx, uint16_t ack)
{
    uint16_t temp_value = 0;

    /* Get the I2Cx CTRL1 value */
    temp_value = I2Cx->CTRL1;
    /* Clear ACKEN bits */
    temp_value &= I2C_ACKEN_CLR_MASK;
    /* Set ACKEN bits according to ack value */
    temp_value |= (uint16_t)((uint32_t)ack);
    /* Set I2Cx CTRL1 */
    I2Cx->CTRL1 = temp_value;
}

/**
*\*\name    I2C_Addressing_Mode_Config.
*\*\fun     Initializes addressing mode.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   mode
*\*\          - I2C_ADDR_MODE_7BIT
*\*\          - I2C_ADDR_MODE_10BIT
*\*\return  none
**/
void I2C_Addressing_Mode_Config(I2C_Module* I2Cx, uint16_t mode)
{
    uint16_t temp_value = 0;

    /* Get the I2Cx OADDR1 value */
    temp_value = I2Cx->OADDR1;
    /* Clear ADDRMODE bits */
    temp_value &= I2C_ADDRMODE_CLR_MASK;
    /* Set ACKEN bits according to mode value */
    temp_value |= mode;
    /* Set I2Cx OADDR1 */
    I2Cx->OADDR1 = temp_value;
}

/**
*\*\name    I2C_Own_Addr1_Config.
*\*\fun     Initializes the own address.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   addr1    between 0 to 0x3FF
*\*\return  none
**/
void I2C_Own_Addr1_Config(I2C_Module* I2Cx, uint16_t addr1)
{
    uint16_t temp_value = 0;

    /* Get the I2Cx OADDR1 value */
    temp_value = I2Cx->OADDR1;
    /* Clear ADDRMODE bits */
    temp_value &= I2C_OADDR_CLR_MASK;
    /* Set ACKEN bits according to mode value */
    temp_value |= addr1;
    /* Set I2Cx OADDR1 */
    I2Cx->OADDR1 = temp_value;

}

/**
*\*\name    I2C_Initializes_Structure.
*\*\fun     Fills each I2C_InitStruct member with its default value.
*\*\param   I2C_InitStruct :
*\*\          - ClkSpeed
*\*\          - BusMode
*\*\          - DutyCycle
*\*\          - OwnAddr1
*\*\          - AckEnable
*\*\          - AddrMode
*\*\return  none
**/
void I2C_Initializes_Structure(I2C_InitType* I2C_InitStruct)
{
    /*---------------- Reset I2C init structure parameters values ----------------*/
    /* initialize the ClkSpeed member */
    I2C_InitStruct->ClkSpeed = 5000;
    /* Initialize the BusMode member */
    I2C_InitStruct->BusMode = I2C_BUSMODE_I2C;
    /* Initialize the DutyCycle member */
    I2C_InitStruct->DutyCycle = I2C_FMDUTYCYCLE_2;
    /* Initialize the OwnAddr1 member */
    I2C_InitStruct->OwnAddr1 = 0;
    /* Initialize the AckEnable member */
    I2C_InitStruct->AckEnable = I2C_ACKDIS;
    /* Initialize the AddrMode member */
    I2C_InitStruct->AddrMode = I2C_ADDR_MODE_7BIT;
}

/**
*\*\name    I2C_ON.
*\*\fun     I2Cx turn ON.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_ON(I2C_Module* I2Cx)
{
    /* Enable the selected I2C peripheral */
    I2Cx->CTRL1 |= I2C_EN_SET;  
}

/**
*\*\name    I2C_OFF.
*\*\fun     I2Cx turn OFF.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_OFF(I2C_Module* I2Cx)
{
    /* Disable the selected I2C peripheral */
    I2Cx->CTRL1 &= I2C_EN_RESET;   
}

/**
*\*\name    I2C_DMA_Transfer_Enable.
*\*\fun     Enable I2C DMA transfer.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_DMA_Transfer_Enable(I2C_Module* I2Cx)
{
    /* Set the I2C_CTRL2 DMAEN bit to enable DMA transfer */
    I2Cx->CTRL2 |= I2C_DMAEN_SET;
}

/**
*\*\name    I2C_DMA_Transfer_Disable.
*\*\fun     Disable I2C DMA transfer.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_DMA_Transfer_Disable(I2C_Module* I2Cx)
{
    /* Clean the I2C_CTRL2 DMAEN bit to disable DMA transfer */
    I2Cx->CTRL2 &= I2C_DMAEN_RESET;
}

/**
*\*\name    I2C_DMA_Last_Transfer_Enable.
*\*\fun     Enable I2C DMA last transfer.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_DMA_Last_Transfer_Enable(I2C_Module* I2Cx)
{   
    /* Next DMA transfer is the last transfer */
    I2Cx->CTRL2 |= I2C_DMALAST_SET;
}

/**
*\*\name    I2C_DMA_Last_Transfer_Disable.
*\*\fun     Disable I2C DMA last transfer.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_DMA_Last_Transfer_Disable(I2C_Module* I2Cx)
{   
    /* Next DMA transfer is not the last transfer */
    I2Cx->CTRL2 &= I2C_DMALAST_RESET;
}

/**
*\*\name    I2C_Generate_Start_Enable.
*\*\fun     Enable Generate a START condition.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Generate_Start_Enable(I2C_Module* I2Cx)
{   
    /* Generate a START condition */
    I2Cx->CTRL1 |= I2C_START_SET;
}

/**
*\*\name    I2C_Generate_Start_Disable.
*\*\fun     Disable the START condition generation.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Generate_Start_Disable(I2C_Module* I2Cx)
{   
    /* Disable the START condition generation */
    I2Cx->CTRL1 &= I2C_START_RESET;
}

/**
*\*\name    I2C_Generate_Stop_Enable.
*\*\fun     Enable Generate a STOP condition.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Generate_Stop_Enable(I2C_Module* I2Cx)
{   
    /* Generate a STOP condition */
    I2Cx->CTRL1 |= I2C_STOP_SET;
}

/**
*\*\name    I2C_Generate_Stop_Disable.
*\*\fun     Disable the STOP condition generation.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Generate_Stop_Disable(I2C_Module* I2Cx)
{   
    /* Disable the STOP condition generation */
    I2Cx->CTRL1 &= I2C_STOP_RESET;
}

/**
*\*\name    I2C_Acknowledg_Enable.
*\*\fun     Enable the acknowledgement.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Acknowledg_Enable(I2C_Module* I2Cx)
{
   /* Enable the acknowledgement */
   I2Cx->CTRL1 |= I2C_ACK_SET;
}

/**
*\*\name    I2C_Acknowledg_Disable.
*\*\fun     Disable the acknowledgement.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Acknowledg_Disable(I2C_Module* I2Cx)
{
   /* Disable the acknowledgement */
   I2Cx->CTRL1 &= I2C_ACK_RESET;
}

/**
*\*\name    I2C_Own_Addr2_Set.
*\*\fun     Set the specified I2C own address2.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   address
*\*\          - 7bit I2C own address2
*\*\return  none
**/
void I2C_Own_Addr2_Set(I2C_Module* I2Cx, uint8_t address)
{
    uint16_t temp_value = 0;

    /* Get the old register value */
    temp_value = I2Cx->OADDR2;

    /* Reset I2Cx Own address2 bit [7:1] */
    temp_value &= I2C_ADDR2_RESET;

    /* Set I2Cx Own address2 */
    temp_value |= (uint16_t)((uint16_t)address & I2C_ADDR2_SET);

    /* Store the new register value */
    I2Cx->OADDR2 = temp_value;
}

/**
*\*\name    I2C_Dual_Addr_Enable.
*\*\fun     Enables the specified I2C dual addressing mode.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Dual_Addr_Enable(I2C_Module* I2Cx)
{
    /* Enable dual addressing mode */
    I2Cx->OADDR2 |= I2C_DUALEN_SET;
}

/**
*\*\name    I2C_Dual_Addr_Disable.
*\*\fun     Disable the specified I2C dual addressing mode.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Dual_Addr_Disable(I2C_Module* I2Cx)
{
    /* Disable dual addressing mode */
    I2Cx->OADDR2 &= I2C_DUALEN_RESET;
}

/**
*\*\name    I2C_General_Call_Enable.
*\*\fun     Enables the specified I2C general call feature.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_General_Call_Enable(I2C_Module* I2Cx)
{
    /* Enable generall call */
    I2Cx->CTRL1 |= I2C_GCEN_SET;
}

/**
*\*\name    I2C_General_Call_Disable.
*\*\fun     Disable the specified I2C general call feature.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_General_Call_Disable(I2C_Module* I2Cx)
{
    /* Disable generall call */
    I2Cx->CTRL1 &= I2C_GCEN_RESET;
}

/**
*\*\name    I2C_Interrupts_Enable.
*\*\fun     Enables the specified I2C interrupts.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_IT :
*\*\          - I2C_INT_BUF Buffer interrupt mask
*\*\          - I2C_INT_EVENT Event interrupt mask
*\*\          - I2C_INT_ERR Error interrupt mask
*\*\return  none
**/
void I2C_Interrupts_Enable(I2C_Module* I2Cx, uint16_t I2C_IT)
{
    /* Enable the selected I2C interrupts */
    I2Cx->CTRL2 |= I2C_IT;
}

/**
*\*\name    I2C_Interrupts_Disable.
*\*\fun     Disables the specified I2C interrupts.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_IT :
*\*\          - I2C_INT_BUF Buffer interrupt mask
*\*\          - I2C_INT_EVENT Event interrupt mask
*\*\          - I2C_INT_ERR Error interrupt mask
*\*\return  none
**/
void I2C_Interrupts_Disable(I2C_Module* I2Cx, uint16_t I2C_IT)
{
    /* Disable the selected I2C interrupts */
    I2Cx->CTRL2 &= (uint16_t)~I2C_IT;
}

/**
*\*\name    I2C_Data_Send.
*\*\fun     Sends a data byte through the I2Cx peripheral.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   data
*\*\return  none
**/
void I2C_Data_Send(I2C_Module* I2Cx, uint8_t data)
{
    /* Write in the DAT register the data to be sent */
    I2Cx->DAT = data;
}

/**
*\*\name    I2C_Data_Recv.
*\*\fun     Returns the most recent received data by the I2Cx peripheral.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  The value of the received data
**/
uint8_t I2C_Data_Recv(I2C_Module* I2Cx)
{
    /* Return the data in the DAT register */
    return (uint8_t)I2Cx->DAT;
}

/**
*\*\name    I2C_7bit_Addr_Send.
*\*\fun     Transmits the address byte to select the slave device.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   address
*\*\param   mode :
*\*\          - I2C_DIRECTION_SEND Transmitter mode
*\*\          - I2C_DIRECTION_RECV Receiver mode
*\*\return  none
**/
void I2C_7bit_Addr_Send(I2C_Module* I2Cx, uint8_t address, uint8_t mode)
{
    /* Test on the direction to set/reset the read/write bit */
    if (mode == I2C_DIRECTION_RECV)
    {
        /* Set the address bit0 for read */
        address |= I2C_ADDR0_SET;
    }
    else
    {
        /* Reset the address bit0 for write */
        address &= I2C_ADDR0_RESET;
    }
    /* Send the address */
    I2Cx->DAT = address;
}

/**
*\*\name    I2C_Register_Value_Get.
*\*\fun     Reads the specified I2C register and returns its value.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_Register :
*\*\          - I2C_REG_CTRL1 CTRL1 register
*\*\          - I2C_REG_CTRL2 CTRL2 register
*\*\          - I2C_REG_OADDR1 OADDR1 register
*\*\          - I2C_REG_OADDR2 OADDR2 register
*\*\          - I2C_REG_DAT DAT register
*\*\          - I2C_REG_STS1 STS1 register
*\*\          - I2C_REG_STS2 STS2 register
*\*\          - I2C_REG_CLKCTRL CLKCTRL register
*\*\          - I2C_REG_TMRISE TMRISE register
*\*\return  none
**/
uint16_t I2C_Register_Value_Get(I2C_Module* I2Cx, uint8_t I2C_Register)
{
    __IO uint32_t temp_value = 0;
    temp_value = (uint32_t)I2Cx;
    temp_value += I2C_Register;

    /* Return the selected register value */
    return (*(__IO uint16_t*)temp_value);
}

/**
*\*\name    I2C_Software_Reset_Enable.
*\*\fun     Enables the specified I2C software reset.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Software_Reset_Enable(I2C_Module* I2Cx)
{
    /* Peripheral under reset */
    I2Cx->CTRL1 |= I2C_SWRESET_SET;
}

/**
*\*\name    I2C_Software_Reset_Disable.
*\*\fun     Disables the specified I2C software reset.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Software_Reset_Disable(I2C_Module* I2Cx)
{
    /* Peripheral not under reset */
    I2Cx->CTRL1 &= I2C_SWRESET_RESET;
}

/**
*\*\name    I2C_NACK_Position_Set.
*\*\fun     Selects the specified I2C NACK position in master receiver mode.
*\*\        This function is useful in I2C Master Receiver mode when the number
*\*\        of data to be received is equal to 2. In this case, this function
*\*\        should be called (with parameter I2C_NACK_POS_NEXT) before data
*\*\        reception starts,as described in the 2-byte reception procedure
*\*\        recommended in Reference Manual in Section: Master receiver.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   position :
*\*\          - I2C_NACK_POS_NEXT Indicates that the next byte will be the last received byte.
*\*\          - I2C_NACK_POS_CURRENT Indicates that current byte is the last received byte.
*\*\note    This function configures the same bit (POS) as I2C_PEC_Position_Set()
*\*\        but is intended to be used in I2C mode while I2C_PEC_Position_Set()
*\*\        is intended to used in SMBUS mode.
*\*\return  none
**/
void I2C_NACK_Position_Set(I2C_Module* I2Cx, uint16_t position)
{
    if (position == I2C_NACK_POS_NEXT)
    {
        /* Next byte in shift register is the last received byte */
        I2Cx->CTRL1 |= I2C_NACK_POS_NEXT;
    }
    else
    {
        /* Current byte in shift register is the last received byte */
        I2Cx->CTRL1 &= I2C_NACK_POS_CURRENT;
    }
}

/**
*\*\name    I2C_SMBus_Alert_Pin_Set.
*\*\fun     Set the SMBus Alert pin high or low for the specified I2C.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   polarity :
*\*\          - I2C_SMBALERT_LOW SMBAlert pin driven low
*\*\          - I2C_SMBALERT_HIGH SMBAlert pin driven high
*\*\return  none
**/
void I2C_SMBus_Alert_Pin_Set(I2C_Module* I2Cx, uint16_t polarity)
{
    if (polarity == I2C_SMBALERT_LOW)
    {
        /* Drive the SMBusAlert pin Low */
        I2Cx->CTRL1 |= I2C_SMBALERT_LOW;
    }
    else
    {
        /* Drive the SMBusAlert pin High  */
        I2Cx->CTRL1 &= I2C_SMBALERT_HIGH;
    }
}

/**
*\*\name    I2C_PEC_Send_Enable.
*\*\fun     Enables the specified I2C PEC transfer.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_PEC_Send_Enable(I2C_Module* I2Cx)
{
    /* Enable the selected I2C PEC transmission */
    I2Cx->CTRL1 |= I2C_PEC_SET;
}

/**
*\*\name    I2C_PEC_Send_Disable.
*\*\fun     Disables the specified I2C PEC transfer.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_PEC_Send_Disable(I2C_Module* I2Cx)
{
    /* Disable the selected I2C PEC transmission */
    I2Cx->CTRL1 &= I2C_PEC_RESET;
}

/**
*\*\name    I2C_NACK_Position_Set.
*\*\fun     Selects the specified I2C PEC position.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   position :
*\*\          - I2C_PEC_POS_NEXT Indicates that the next byte is PEC
*\*\          - I2C_PEC_POS_CURRENT Indicates that current byte is PEC
*\*\note    This function configures the same bit (POS) as I2C_NACK_Position_Set()
*\*\        but is intended to be used in SMBUS mode while I2C_NACK_Position_Set()
*\*\        is intended to used in I2C mode.
*\*\return  none
**/
void I2C_PEC_Position_Set(I2C_Module* I2Cx, uint16_t position)
{
    if (position == I2C_PEC_POS_NEXT)
    {
        /* Next byte in shift register is PEC */
        I2Cx->CTRL1 |= I2C_PEC_POS_NEXT;
    }
    else
    {
        /* Current byte in shift register is PEC */
        I2Cx->CTRL1 &= I2C_PEC_POS_CURRENT;
    }
}

/**
*\*\name    I2C_PEC_Compute_Enable.
*\*\fun     Enables PEC value compute.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_PEC_Compute_Enable(I2C_Module* I2Cx)
{
    /* Enable the selected I2C PEC calculation */
    I2Cx->CTRL1 |= I2C_PECEN_SET;
}

/**
*\*\name    I2C_PEC_Compute_Disable.
*\*\fun     Disables PEC value compute.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_PEC_Compute_Disable(I2C_Module* I2Cx)
{
    /* Disable the selected I2C PEC calculation */
    I2Cx->CTRL1 &= I2C_PECEN_RESET;
}

/**
*\*\name    I2C_PEC_Get.
*\*\fun     Get the PEC value for the specified I2C.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  The PEC value
**/
uint8_t I2C_PEC_Get(I2C_Module* I2Cx)
{
    /* Return the selected I2C PEC value */
    return ((I2Cx->STS2) >> 8);
}

/**
*\*\name    I2C_ARP_Enable.
*\*\fun     Enables the specified I2C ARP.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_ARP_Enable(I2C_Module* I2Cx)
{
    /* Enable the selected I2C ARP */
    I2Cx->CTRL1 |= I2C_ARPEN_SET; 
}

/**
*\*\name    I2C_ARP_Disable.
*\*\fun     Disables the specified I2C ARP.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_ARP_Disable(I2C_Module* I2Cx)
{
    /* Disable the selected I2C ARP */
    I2Cx->CTRL1 &= I2C_ARPEN_RESET;
}

/**
*\*\name    I2C_Extend_Clock_Enable.
*\*\fun     Enables the specified I2C clock extending.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Extend_Clock_Enable(I2C_Module* I2Cx)
{
    /* Enable the selected I2C Clock extending */
    I2Cx->CTRL1 &= I2C_NOEXTEND_RESET; 
}

/**
*\*\name    I2C_Extend_Clock_Disable.
*\*\fun     Disables the specified I2C clock extending.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_Extend_Clock_Disable(I2C_Module* I2Cx)
{
    /* Disable the selected I2C Clock extending */
    I2Cx->CTRL1 |= I2C_NOEXTEND_SET;
}

/**
*\*\name    I2C_Fast_Mode_Duty_Cycle_Set.
*\*\fun     Set the specified I2C fast mode duty cycle.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   duty_cycle :
*\*\          - I2C_FMDUTYCYCLE_2 I2C fast mode Tlow/Thigh = 2
*\*\          - I2C_FMDUTYCYCLE_16_9 I2C fast mode Tlow/Thigh = 16/9
*\*\return  none
**/
void I2C_Fast_Mode_Duty_Cycle_Set(I2C_Module* I2Cx, uint16_t duty_cycle)
{
    if (duty_cycle == I2C_FMDUTYCYCLE_16_9)
    {
        /* I2C fast mode Tlow/Thigh=16/9 */
        I2Cx->CLKCTRL |= I2C_FMDUTYCYCLE_16_9;
        
    }
    else
    {
        /* I2C fast mode Tlow/Thigh=2 */
        I2Cx->CLKCTRL &= I2C_FMDUTYCYCLE_2;
    }
}

/**
*\*\name    I2C_Digital_Filter_Width_Set.
*\*\fun     SDA digital filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   width :
*\*\          - 0x00 ~ 0x0F     The numbers of pclk cycles(width is 0x00: Disable the digital filter).
*\*\return  none
**/
void I2C_SDA_Digital_Filter_Width_Set(I2C_Module* I2Cx, uint8_t width)
{
    uint32_t temp_value = 0;

    temp_value = I2Cx->TMRISE;
    /* Clear SDADFW[3:0] bits */
    temp_value &= I2C_SDADFW_MASK;
    /* Set SDADFW[3:0] bits according to width value */
    temp_value |= ((uint32_t)width << RCC_TMRISE_SDADFW_OFFSET);
    /* Store the new value */
    I2Cx->TMRISE = temp_value;
    
}

/**
*\*\name    I2C_SCL_Digital_Filter_Width_Set.
*\*\fun     SCL digital filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   width :
*\*\          - 0x00            Disable the digital filter.
*\*\          - 0x01 ~ 0x0F     The numbers of pclk cycles.
*\*\return  none
**/
void I2C_SCL_Digital_Filter_Width_Set(I2C_Module* I2Cx, uint8_t width)
{
    uint32_t temp_value = 0;

    temp_value = I2Cx->TMRISE;
    /* Clear SCLDFW[3:0] bits */
    temp_value &= I2C_SCLDFW_MASK;
    /* Set SCLDFW[3:0] bits according to width value */
    temp_value |= ((uint32_t)width << RCC_TMRISE_SCLDFW_OFFSET);
    /* Store the new value */
    I2Cx->TMRISE = temp_value;
    
}

/**
*\*\name    I2C_SDA_Analog_Filter_Width_Set.
*\*\fun     SDA analog filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   width :
*\*\        - I2C_ANALOG_FILTER_WIDTH_5NS   
*\*\        - I2C_ANALOG_FILTER_WIDTH_15NS  
*\*\        - I2C_ANALOG_FILTER_WIDTH_25NS  
*\*\        - I2C_ANALOG_FILTER_WIDTH_35NS  
*\*\return  none
**/
void I2C_SDA_Analog_Filter_Width_Set(I2C_Module* I2Cx, uint32_t width)
{
    uint32_t temp_value = 0;

    temp_value = I2Cx->TMRISE;
    /* Clear SDAAFW[1:0] bits */
    temp_value &= I2C_SDAAFW_MASK;
    /* Set SDAAFW[1:0] bits according to width value */
    temp_value |= width;
    /* Store the new value */
    I2Cx->TMRISE = temp_value;
    
}

/**
*\*\name    I2C_SDA_Analog_Filter_Enable.
*\*\fun     Enables the SDA analog filter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_SDA_Analog_Filter_Enable(I2C_Module* I2Cx)
{
    /* Enable the SDA analog filter */
    I2Cx->TMRISE |= I2C_SDAAFENN_SET;
}

/**
*\*\name    I2C_SDA_Analog_Filter_Disable.
*\*\fun     Disables the SDA analog filter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_SDA_Analog_Filter_Disable(I2C_Module* I2Cx)
{
    /* Disable the SDA analog filter */
    I2Cx->TMRISE &= I2C_SDAAFENN_RESET;
}

/**
*\*\name    I2C_SCL_Analog_Filter_Width_Set.
*\*\fun     SCL analog filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   width :
*\*\        - I2C_ANALOG_FILTER_WIDTH_5NS   
*\*\        - I2C_ANALOG_FILTER_WIDTH_15NS  
*\*\        - I2C_ANALOG_FILTER_WIDTH_25NS  
*\*\        - I2C_ANALOG_FILTER_WIDTH_35NS  
*\*\return  none
**/
void I2C_SCL_Analog_Filter_Width_Set(I2C_Module* I2Cx, uint32_t width)
{
    uint32_t temp_value = 0;

    temp_value = I2Cx->TMRISE;
    /* Clear SCLAFW[1:0] bits */
    temp_value &= I2C_SCLAFW_MASK;
    /* Set SCLAFW[1:0] bits according to width value */
    temp_value |= (width << RCC_SDAAFW_SCLAFW_OFFSET);
    /* Store the new value */
    I2Cx->TMRISE = temp_value;
    
}

/**
*\*\name    I2C_SCL_Analog_Filter_Enable.
*\*\fun     Enables the SCL analog filter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_SCL_Analog_Filter_Enable(I2C_Module* I2Cx)
{
    /* Enable the SCL analog filter */
    I2Cx->TMRISE |= I2C_SCLAFENN_SET;
}

/**
*\*\name    I2C_SCL_Analog_Filter_Disable.
*\*\fun     Disables the SCL analog filter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\return  none
**/
void I2C_SCL_Analog_Filter_Disable(I2C_Module* I2Cx)
{
    /* Disable the SCL analog filter */
    I2Cx->TMRISE &= I2C_SCLAFENN_RESET;
}

/**
*\*\brief I2C State Monitoring Functions
*\*\      This I2C driver provides three different ways for I2C state monitoring
*\*\      depending on the application requirements and constraints:
*\*\
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
*\*\note
*\*\        For error management, it is advised to use the following functions:
*\*\          - I2C_ConfigInt() to configure and enable the error interrupts (I2C_INT_ERR).
*\*\          - I2Cx_ER_IRQHandler() which is called when the error interrupt occurs.
*\*\            Where x is the peripheral instance (I2C1, I2C2 ...)
*\*\          - I2C_Flag_Status_Get() or I2C_GetIntStatus() to be called into I2Cx_ER_IRQHandler()
*\*\            in order to determine which error occured.
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
*\*\         overcome the mentioned limitation of I2C_Flag_Status_Get() function.
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
*\*\  For detailed description of Events, please refer to section I2C_Events in
*\*\  n32g430_i2c.h file.
*\*\
**/


/**
*\*\name    I2C_Event_Check.
*\*\fun     Checks whether the last I2Cx Event is equal to the one passed as parameter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_event :
*\*\          - I2C_EVT_SLAVE_SEND_ADDR_MATCHED                 EV1
*\*\          - I2C_EVT_SLAVE_RECV_ADDR_MATCHED                 EV1
*\*\          - I2C_EVT_SLAVE_SEND_ADDR2_MATCHED                EV1
*\*\          - I2C_EVT_SLAVE_RECV_ADDR2_MATCHED                EV1
*\*\          - I2C_EVT_SLAVE_GCALLADDR_MATCHED                 EV1
*\*\          - I2C_EVT_SLAVE_DATA_RECVD                        EV2
*\*\          - (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_DUALFLAG)  EV2
*\*\          - (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_GCALLADDR) EV2
*\*\          - I2C_EVT_SLAVE_DATA_SENDED                       EV3
*\*\          - (I2C_EVT_SLAVE_DATA_SENDED | I2C_FLAG_DUALFLAG) EV3
*\*\          - (I2C_EVT_SLAVE_DATA_SENDED | I2C_FLAG_GCALLADDR)EV3
*\*\          - I2C_EVT_SLAVE_ACK_MISS                          EV3_2
*\*\          - I2C_EVT_SLAVE_STOP_RECVD                        EV4
*\*\          - I2C_EVT_MASTER_MODE_FLAG                        EV5
*\*\          - I2C_EVT_MASTER_TXMODE_FLAG                      EV6
*\*\          - I2C_EVT_MASTER_RXMODE_FLAG                      EV6
*\*\          - I2C_EVT_MASTER_DATA_RECVD_FLAG                  EV7
*\*\          - I2C_EVT_MASTER_DATA_SENDING                     EV8
*\*\          - I2C_EVT_MASTER_DATA_SENDED                      EV8_2
*\*\          - I2C_EVT_MASTER_MODE_ADDRESS10_FLAG              EV9
*\*\note    For detailed description of Events, please refer to section
*\*\        I2C_Events in n32g430_i2c.h file.
*\*\return  SUCCESS or ERROR
**/
ErrorStatus I2C_Event_Check(I2C_Module* I2Cx, uint32_t I2C_event)
{
    uint32_t le_value = 0;
    uint32_t flag1 = 0, flag2 = 0;

    /* Read the I2Cx status register */
    flag1 = I2Cx->STS1;
    flag2 = I2Cx->STS2;
    flag2 = flag2 << RCC_FLAG_STS2_OFFSET;

    /* Get the last event value from I2C status register */
    le_value = (flag1 | flag2) & FLAG_MASK;

    /* Check whether the last event contains the I2C_event */
    if ((le_value & I2C_event) == I2C_event)
    {
        /* Return SUCCESS: last event is equal to I2C_event */
        return SUCCESS;
    }
    else
    {
        /* Return ERROR: last event is different from I2C_event */
        return ERROR;
    }
}

/**
*\*\name    I2C_Last_Event_Get.
*\*\fun     Returns the last I2Cx Event.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\note    For detailed description of Events, please refer to section
*\*\        I2C_Events in n32g430_i2c.h file.
*\*\return  The last event
**/
uint32_t I2C_Last_Event_Get(I2C_Module* I2Cx)
{
    uint32_t flag1 = 0, flag2 = 0;

    /* Read the I2Cx status register */
    flag1 = I2Cx->STS1;
    flag2 = I2Cx->STS2;
    flag2 = flag2 << RCC_FLAG_STS2_OFFSET;

    /* Return the last event value from I2C status register */
    return (flag1 | flag2) & FLAG_MASK;
}

/**
*\*\name    I2C_Flag_Status_Get.
*\*\fun     Checks whether the specified I2C flag is set or not.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_flag :
*\*\          - I2C_FLAG_DUALFLAG     Dual flag (Slave mode)
*\*\          - I2C_FLAG_SMBHADDR     SMBus host header (Slave mode)
*\*\          - I2C_FLAG_SMBDADDR     SMBus default header (Slave mode)
*\*\          - I2C_FLAG_GCALLADDR    General call header flag (Slave mode)
*\*\          - I2C_FLAG_TRF          Transmitter/Receiver flag
*\*\          - I2C_FLAG_BUSY         Bus busy flag
*\*\          - I2C_FLAG_MSMODE       Master/Slave flag
*\*\          - I2C_FLAG_SMBALERT     SMBus Alert flag
*\*\          - I2C_FLAG_TIMOUT       Timeout or Tlow error flag
*\*\          - I2C_FLAG_PECERR       PEC error in reception flag
*\*\          - I2C_FLAG_OVERRUN      Overrun/Underrun flag (Slave mode)
*\*\          - I2C_FLAG_ACKFAIL      Acknowledge failure flag
*\*\          - I2C_FLAG_ARLOST       Arbitration lost flag (Master mode)
*\*\          - I2C_FLAG_BUSERR       Bus error flag
*\*\          - I2C_FLAG_TXDATE       Data register empty flag (Transmitter)
*\*\          - I2C_FLAG_RXDATNE      Data register not empty (Receiver) flag
*\*\          - I2C_FLAG_STOPF        Stop detection flag (Slave mode)
*\*\          - I2C_FLAG_ADDR10F      10-bit header sent flag (Master mode)
*\*\          - I2C_FLAG_BYTEF        Byte transfer finished flag
*\*\          - I2C_FLAG_ADDRF        Address sent flag (Master mode) "ADSL"
*\*\                                  Address matched flag (Slave mode)"ENDA"
*\*\          - I2C_FLAG_STARTBF      Start bit flag (Master mode)
*\*\return  SET or RESET
**/
FlagStatus I2C_Flag_Status_Get(I2C_Module* I2Cx, uint32_t I2C_flag)
{
    __IO uint32_t temp_value0 = 0, temp_value1 = 0;

    /* Get the I2Cx peripheral base address */
    temp_value0 = (uint32_t)I2Cx;

    /* Read flag register index */
    temp_value1 = I2C_flag >> RCC_FLAG_GET_OFFSET;

    /* Get bit[23:0] of the flag */
    I2C_flag &= FLAG_MASK;

    if (temp_value1 == 0)
    {
        /* Flag in I2Cx STS2 Register */
        I2C_flag = (uint32_t)(I2C_flag >> RCC_FLAG_STS2_OFFSET);
        /* Get the I2Cx STS2 register address */
        temp_value0 += 0x18;
    }
    else
    {
        /* Get the I2Cx STS1 register address */
        temp_value0 += 0x14;
    }

    if (((*(__IO uint32_t*)temp_value0) & I2C_flag) == (uint32_t)RESET)
    {
        /* I2C_flag is reset */
        return RESET;
    }
    else
    {
        /* I2C_flag is set */
        return SET;
    }
}

/**
*\*\name    I2C_Flag_Status_Clear.
*\*\fun     Clears the I2Cx's flags.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   I2C_flag :
*\*\          - I2C_FLAG_SMBALERT    SMBus Alert flag
*\*\          - I2C_FLAG_TIMOUT      Timeout or Tlow error flag
*\*\          - I2C_FLAG_PECERR      PEC error in reception flag
*\*\          - I2C_FLAG_OVERRUN     Overrun/Underrun flag (Slave mode)
*\*\          - I2C_FLAG_ACKFAIL     Acknowledge failure flag
*\*\          - I2C_FLAG_ARLOST      Arbitration lost flag (Master mode)
*\*\          - I2C_FLAG_BUSERR      Bus error flag
*\*\note    - STOPF (STOP detection) is cleared by software sequence: a read operation
*\*\          to I2C_STS1 register (I2C_Flag_Get()) followed by a write operation
*\*\          to I2C_CTRL1 register (I2C_ON() to re-enable the I2C peripheral).
*\*\        - ADD10 (10-bit header sent) is cleared by software sequence: a read
*\*\          operation to I2C_STS1 (I2C_Flag_Get()) followed by writing the
*\*\          second byte of the address in DAT register.
*\*\        - BTF (Byte Transfer Finished) is cleared by software sequence: a read
*\*\          operation to I2C_STS1 register (I2C_Flag_Get()) followed by a
*\*\          read/write to I2C_DAT register (I2C_Data_Send()).
*\*\        - ADDR (Address sent) is cleared by software sequence: a read operation to
*\*\          I2C_STS1 register (I2C_Flag_Get()) followed by a read operation to
*\*\          I2C_STS2 register ((void)(I2Cx->STS2)).
*\*\        - SB (Start Bit) is cleared software sequence: a read operation to I2C_STS1
*\*\          register (I2C_Flag_Get()) followed by a write operation to I2C_DAT
*\*\          register (I2C_Data_Send()).
*\*\return  none
**/
void I2C_Flag_Status_Clear(I2C_Module* I2Cx, uint32_t I2C_flag)
{
    uint32_t temp_value = 0;

    /* Get the I2C flag position */
    temp_value = I2C_flag & FLAG_MASK;
    /* Clear the selected I2C flag */
    I2Cx->STS1 = (uint16_t)~temp_value;
}

/**
*\*\name    I2C_Interrupt_Status_Get.
*\*\fun     Checks whether the specified I2C interrupt has occurred or not.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Interrupt :
*\*\          - I2C_INT_SMBALERT    SMBus Alert flag
*\*\          - I2C_INT_TIMOUT      Timeout or Tlow error flag
*\*\          - I2C_INT_PECERR      PEC error in reception flag
*\*\          - I2C_INT_OVERRUN     Overrun/Underrun flag (Slave mode)
*\*\          - I2C_INT_ACKFAIL     Acknowledge failure flag
*\*\          - I2C_INT_ARLOST      Arbitration lost flag (Master mode)
*\*\          - I2C_INT_BUSERR      Bus error flag
*\*\          - I2C_INT_TXDATE      Data register empty flag (Transmitter)
*\*\          - I2C_INT_RXDATNE     Data register not empty (Receiver) flag
*\*\          - I2C_INT_STOPF       Stop detection flag (Slave mode)
*\*\          - I2C_INT_ADDR10F     10-bit header sent flag (Master mode)
*\*\          - I2C_INT_BYTEF       Byte transfer finished flag
*\*\          - I2C_INT_ADDRF       Address sent flag (Master mode) "ADSL"
*\*\                                Address matched flag (Slave mode)"ENDAD"
*\*\          - I2C_INT_STARTBF     Start bit flag (Master mode)
*\*\return  SET or RESET
**/
INTStatus I2C_Interrupt_Status_Get(I2C_Module* I2Cx, uint32_t Interrupt)
{
    uint32_t temp_value = 0;

    /* Check if the interrupt source is enabled or not */
    temp_value = (uint32_t)(((Interrupt & INTEN_MASK) >> 16) & (I2Cx->CTRL2));

    /* Get bit[23:0] of the flag */
    Interrupt &= FLAG_MASK;

    /* Check the status of the specified I2C flag */
    if (((I2Cx->STS1 & Interrupt) != (uint32_t)RESET) && temp_value)
    {
        /* Interrupt is set */
        return SET;
    }
    else
    {
        /* Interrupt is reset */
        return RESET;
    }
}

/**
*\*\name    I2C_Interrupt_Statu_Clear.
*\*\fun     Clears the I2Cx's interrupt statu bits.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\param   Interrupt :
*\*\          - I2C_INT_SMBALERT    SMBus Alert flag
*\*\          - I2C_INT_TIMOUT      Timeout or Tlow error flag
*\*\          - I2C_INT_PECERR      PEC error in reception flag
*\*\          - I2C_INT_OVERRUN     Overrun/Underrun flag (Slave mode)
*\*\          - I2C_INT_ACKFAIL     Acknowledge failure flag
*\*\          - I2C_INT_ARLOST      Arbitration lost flag (Master mode)
*\*\          - I2C_INT_BUSERR      Bus error flag
*\*\note    - STOPF (STOP detection) is cleared by software sequence: a read operation
*\*\          to I2C_STS1 register (I2C_Flag_Get()) followed by a write operation
*\*\          to I2C_CTRL1 register (I2C_ON() to re-enable the I2C peripheral).
*\*\        - ADD10 (10-bit header sent) is cleared by software sequence: a read
*\*\          operation to I2C_STS1 (I2C_Flag_Get()) followed by writing the
*\*\          second byte of the address in DAT register.
*\*\        - BTF (Byte Transfer Finished) is cleared by software sequence: a read
*\*\          operation to I2C_STS1 register (I2C_Flag_Get()) followed by a
*\*\          read/write to I2C_DAT register (I2C_Data_Send()).
*\*\        - ADDR (Address sent) is cleared by software sequence: a read operation to
*\*\          I2C_STS1 register (I2C_Flag_Get()) followed by a read operation to
*\*\          I2C_STS2 register ((void)(I2Cx->STS2)).
*\*\        - SB (Start Bit) is cleared software sequence: a read operation to I2C_STS1
*\*\          register (I2C_Flag_Get()) followed by a write operation to I2C_DAT
*\*\          register (I2C_Data_Send()).
*\*\return  none
**/
void I2C_Interrupt_Statu_Clear(I2C_Module* I2Cx, uint32_t Interrupt)
{
    uint32_t temp_value = 0;

    /* Get the I2C flag position */
    temp_value = Interrupt & FLAG_MASK;
    /* Clear the selected I2C flag */
    I2Cx->STS1 = (uint16_t)~temp_value;
}


