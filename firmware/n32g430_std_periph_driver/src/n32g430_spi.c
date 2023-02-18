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
*\*\file      n32g430_spi.c
*\*\author    Nations
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved. 
**/

#include "n32g430_spi.h"
#include "n32g430_rcc.h"

/* SPI Driving Functions Declaration */

/**
*\*\name    SPI_I2S_Reset.
*\*\fun     Reset the SPIx registers.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\return  none
**/
void SPI_I2S_Reset(SPI_Module* SPIx)
{
    if (SPIx == SPI1)
    {
        /* SPI1 Reset */
        RCC_APB2_Peripheral_Reset(RCC_APB2_PERIPH_SPI1);
    }
    else if (SPIx == SPI2)
    {
        /* SPI2 Reset */
        RCC_APB2_Peripheral_Reset(RCC_APB2_PERIPH_SPI2);
    }
    else
    {
        /* none */
    }
}


/**
*\*\name    SPI_ON.
*\*\fun     SPIx turn ON.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\return  none
**/
void SPI_ON(SPI_Module* SPIx)
{
    /* Set the SPI_CTRL1 ON bit to wake up the SPI from power down mode */
    SPIx->CTRL1 |= SPI_TURN_ON;
}


/**
*\*\name    SPI_OFF.
*\*\fun     SPIx turn OFF.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\return  none
**/
void SPI_OFF(SPI_Module* SPIx)
{
    /* Clear the SPI_CTRL1 ON bit, The SPI go to power down mode */
    SPIx->CTRL1 &= SPI_TURN_OFF;
}


/**
*\*\name    SPI_Initializes_Structure.
*\*\fun     Fills each SPI_InitStruct member with its default value.
*\*\param   SPI_InitStruct :
*\*\          - DataDirection
*\*\          - SpiMode
*\*\          - DataLen
*\*\          - CLKPOL
*\*\          - CLKPHA
*\*\          - NSS      
*\*\          - BaudRatePres     
*\*\          - FirstBit      
*\*\          - CRCPoly
*\*\return  none
**/
void SPI_Initializes_Structure(SPI_InitType* SPI_InitStruct)
{
    /*--------------- Reset SPI init structure parameters values -----------------*/
    /* Initialize the DataDirection member */
    SPI_InitStruct->DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    /* initialize the SpiMode member */
    SPI_InitStruct->SpiMode = SPI_MODE_SLAVE;
    /* initialize the DataLen member */
    SPI_InitStruct->DataLen = SPI_DATA_SIZE_8BITS;
    /* Initialize the CLKPOL member */
    SPI_InitStruct->CLKPOL = SPI_CLKPOL_LOW;
    /* Initialize the CLKPHA member */
    SPI_InitStruct->CLKPHA = SPI_CLKPHA_FIRST_EDGE;
    /* Initialize the NSS member */
    SPI_InitStruct->NSS = SPI_NSS_HARD;
    /* Initialize the BaudRatePres member */
    SPI_InitStruct->BaudRatePres = SPI_BR_PRESCALER_2;
    /* Initialize the FirstBit member */
    SPI_InitStruct->FirstBit = SPI_FB_MSB;
    /* Initialize the CRCPoly member */
    SPI_InitStruct->CRCPoly = 7;
}


/**
*\*\name    SPI_Initializes.
*\*\fun     Initializes the SPIx according to SPI_InitStruct.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   SPI_InitStruct :
*\*\          - DataDirection
*\*\            - SPI_DIR_DOUBLELINE_FULLDUPLEX
*\*\            - SPI_DIR_DOUBLELINE_RONLY     
*\*\            - SPI_DIR_SINGLELINE_RX        
*\*\            - SPI_DIR_SINGLELINE_TX        
*\*\          - SpiMode
*\*\            - SPI_MODE_MASTER
*\*\            - SPI_MODE_SLAVE 
*\*\          - DataLen
*\*\            - SPI_DATA_SIZE_16BITS
*\*\            - SPI_DATA_SIZE_8BITS     
*\*\          - CLKPOL
*\*\            - SPI_CLKPOL_LOW 
*\*\            - SPI_CLKPOL_HIGH
*\*\          - CLKPHA
*\*\            - SPI_CLKPHA_FIRST_EDGE 
*\*\            - SPI_CLKPHA_SECOND_EDGE
*\*\          - NSS
*\*\            - SPI_NSS_SOFT
*\*\            - SPI_NSS_HARD
*\*\          - BaudRatePres
*\*\            - SPI_BR_PRESCALER_2  
*\*\            - SPI_BR_PRESCALER_4  
*\*\            - SPI_BR_PRESCALER_8  
*\*\            - SPI_BR_PRESCALER_16 
*\*\            - SPI_BR_PRESCALER_32 
*\*\            - SPI_BR_PRESCALER_64 
*\*\            - SPI_BR_PRESCALER_128
*\*\            - SPI_BR_PRESCALER_256
*\*\          - FirstBit
*\*\            - SPI_FB_MSB
*\*\            - SPI_FB_LSB
*\*\          - CRCPoly      default 0x0007, max 0xffff 
*\*\return  none
**/
void SPI_Initializes(SPI_Module* SPIx, SPI_InitType* SPI_InitStruct)
{
    SPI_DataDirection_Config(SPIx, SPI_InitStruct->DataDirection);
    SPI_SpiMode_Config(SPIx, SPI_InitStruct->SpiMode);
    SPI_DataLen_Config(SPIx, SPI_InitStruct->DataLen);
	SPI_CLKPHA_Config(SPIx, SPI_InitStruct->CLKPHA);
    SPI_CLKPOL_Config(SPIx, SPI_InitStruct->CLKPOL);
    SPI_NSS_Config(SPIx, SPI_InitStruct->NSS);
    SPI_BaudRatePres_Config(SPIx, SPI_InitStruct->BaudRatePres);
    SPI_FirstBit_Config(SPIx, SPI_InitStruct->FirstBit);
    SPI_CRC_Polynomial_Set(SPIx, SPI_InitStruct->CRCPoly);
}


/**
*\*\name     SPI_DataDirection_Config.
*\*\fun     Config the SPIx DataDirection.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   DataDirection :
*\*\          - SPI_DIR_DOUBLELINE_FULLDUPLEX
*\*\          - SPI_DIR_DOUBLELINE_RONLY     
*\*\          - SPI_DIR_SINGLELINE_RX        
*\*\          - SPI_DIR_SINGLELINE_TX
*\*\return  none
**/
void SPI_DataDirection_Config(SPI_Module* SPIx, uint16_t DataDirection)
{  
    /* Clear SPI_CTRL1[15:14] and [10] bits */
    SPIx->CTRL1 &= SPI_DATADIRECTION_MASK;
    /* Set SPI_CTRL1[15:14] and [10] bits */
    SPIx->CTRL1 |= DataDirection;
}


/**
*\*\name    SPI_SpiMode_Config.
*\*\fun     Config the SPIx mode.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   SpiMode :
*\*\          - SPI_MODE_MASTER
*\*\          - SPI_MODE_SLAVE
*\*\return  none
**/
void SPI_SpiMode_Config(SPI_Module* SPIx, uint16_t SpiMode)
{
    /* Clear SPI_CTRL1 MSEL bits */
    SPIx->CTRL1 &= SPI_MODE_MASK;
    /* Set SPI_CTRL1 MSEL bits */
    SPIx->CTRL1 |= SpiMode;
}


/**
*\*\name    SPI_DataLen_Config.
*\*\fun     Config the SPIx DataLen.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   DataLen :
*\*\          - SPI_DATA_SIZE_16BITS
*\*\          - SPI_DATA_SIZE_8BITS
*\*\return  none
*\*\note    Must be used with SPI OFF.
**/
void SPI_DataLen_Config(SPI_Module* SPIx, uint16_t DataLen)
{
    /* Clear SPI_CTRL1 DATFF bits */
    SPIx->CTRL1 &= SPI_DATALEN_MASK;
    /* Set SPI_CTRL1 DATFF bits */
    SPIx->CTRL1 |= DataLen;
}


/**
*\*\name    SPI_CLKPOL_Config.
*\*\fun     Config the SPIx CLKPOL.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   CLKPOL :
*\*\          - SPI_CLKPOL_LOW
*\*\          - SPI_CLKPOL_HIGH
*\*\return  none
**/
void SPI_CLKPOL_Config(SPI_Module* SPIx, uint16_t CLKPOL)
{
    /* Clear SPI_CTRL1 CLKPOL bits */
    SPIx->CTRL1 &= SPI_CLKPOL_MASK;
    /* Set SPI_CTRL1 CLKPOL bits */
    SPIx->CTRL1 |= CLKPOL;
}


/**
*\*\name    SPI_CLKPHA_Config.
*\*\fun     Config the SPIx CLKPHA.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   CLKPHA :
*\*\          - SPI_CLKPHA_FIRST_EDGE
*\*\          - SPI_CLKPHA_SECOND_EDGE
*\*\return  none
**/
void SPI_CLKPHA_Config(SPI_Module* SPIx, uint16_t CLKPHA)
{
    /* Clear SPI_CTRL1 CLKPHA bits */
    SPIx->CTRL1 &= SPI_CLKPHA_MASK;
    /* Set SPI_CTRL1 CLKPHA bits */
    SPIx->CTRL1 |= CLKPHA;
}


/**
*\*\name    SPI_NSS_Config.
*\*\fun     Config the SPIx NSS.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   NSS :
*\*\          - SPI_NSS_SOFT
*\*\          - SPI_NSS_HARD
*\*\return  none
**/
void SPI_NSS_Config(SPI_Module* SPIx, uint16_t NSS)
{
    /* Clear SPI_CTRL1 SSMEN bits */
    SPIx->CTRL1 &= SPI_NSS_MASK;
    /* Set SPI_CTRL1 SSMEN bits */
    SPIx->CTRL1 |= NSS;
}


/**
*\*\name    SPI_BaudRatePres_Config.
*\*\fun     Config the SPIx BaudRatePres.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   BaudRatePres :
*\*\          - SPI_BR_PRESCALER_2
*\*\          - SPI_BR_PRESCALER_4
*\*\          - SPI_BR_PRESCALER_8
*\*\          - SPI_BR_PRESCALER_16
*\*\          - SPI_BR_PRESCALER_32
*\*\          - SPI_BR_PRESCALER_64
*\*\          - SPI_BR_PRESCALER_128
*\*\          - SPI_BR_PRESCALER_256
*\*\return  none
**/
void SPI_BaudRatePres_Config(SPI_Module* SPIx, uint16_t BaudRatePres)
{
    /* Clear SPI_CTRL1 BR[2:0] bits */
    SPIx->CTRL1 &= SPI_BAUDRATEPRES_MASK;
    /* Set SPI_CTRL1 BR[2:0] bits */
    SPIx->CTRL1 |= BaudRatePres;
}


/**
*\*\name    SPI_FirstBit_Config.
*\*\fun     Config the SPIx FirstBit.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   FirstBit :
*\*\          - SPI_FB_MSB
*\*\          - SPI_FB_LSB
*\*\return  none
**/
void SPI_FirstBit_Config(SPI_Module* SPIx, uint16_t FirstBit)
{
    /* Clear SPI_CTRL1 LSBFF bits */
    SPIx->CTRL1 &= SPI_FIRSTBIT_MASK;
    /* Set SPI_CTRL1 LSBFF bits */
    SPIx->CTRL1 |= FirstBit;
}


/**
*\*\name    SPI_Set_Nss_Level.
*\*\fun     Configures internally by software the NSS pin for the selected SPI.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   SPI_NSS_Internal_Soft :
*\*\          - SPI_NSS_HIGH
*\*\          - SPI_NSS_LOW
*\*\return  none
**/
void SPI_Set_Nss_Level(SPI_Module* SPIx, uint16_t SPI_NSS_Internal_Soft)
{
    if(SPI_NSS_Internal_Soft == SPI_NSS_HIGH)
    {
        /* Set NSS pin internally by software */
        SPIx->CTRL1 |= SPI_NSS_HIGH;
    }
    else
    {
        /* Reset NSS pin internally by software */
        SPIx->CTRL1 &= SPI_NSS_LOW;
    }
}

/**
*\*\name    SPI_SS_Output_Enable.
*\*\fun     Enables the SS output for the selected SPI.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\return  none
**/
void SPI_SS_Output_Enable(SPI_Module* SPIx)
{
    /* Set the SPI_CTRL2 SSOEN bit to enable SS output */
    SPIx->CTRL2 |= SPI_SS_OUTPUT_ENABLE;
}

/**
*\*\name    SPI_SS_Output_Disable.
*\*\fun     Disable the SS output for the selected SPI.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\return  none
**/
void SPI_SS_Output_Disable(SPI_Module* SPIx)
{
    /* Clean the SPI_CTRL2 SSOEN bit to disable SS output */
    SPIx->CTRL2 &= SPI_SS_OUTPUT_DISABLE;
}

/**
*\*\name    SPI_Next_Transmit_Crc.
*\*\fun     Transmit the SPIx CRC value.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\return  none
**/
void SPI_Next_Transmit_CRC(SPI_Module* SPIx)
{
    /* Set the SPI_CTRL1 CRCNEXT bit */
    SPIx->CTRL1 |= SPI_CRCNEXT_ENABLE;
}

/**
*\*\name    SPI_Crc_ENABLE.
*\*\fun     Enables the CRC value calculation of the transferred bytes.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\return  none
*\*\note    Must be used with SPI OFF.
**/
void SPI_CRC_Enable(SPI_Module* SPIx)
{
    /* Set the SPI_CTRL1 CRCEN bit to enable CRC calculation */
    SPIx->CTRL1 |= CTRL1_CRCEN_ENABLE;
}

/**
*\*\name    SPI_Crc_Disable.
*\*\fun     Disable the CRC value calculation of the transferred bytes.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\return  none
**/
void SPI_CRC_Disable(SPI_Module* SPIx)
{
    /* Clean the SPI_CTRL1 CRCEN bit to Disable CRC calculation */
    SPIx->CTRL1 &= CTRL1_CRCEN_DISABLE; 
}

/**
*\*\name    SPI_CRC_Data_Get.
*\*\fun     Get SPI CRC data from SPI_CRCTDAT/SPI_CRCRDAT register.
*\*\param   SPIx :
*\*\          - SPI1       
*\*\          - SPI2       
*\*\param   SPI_CRC :
*\*\          - SPI_CRC_TX       
*\*\          - SPI_CRC_RX        
*\*\return  Tx/Rx CRC register value.
**/
uint16_t SPI_CRC_Data_Get(SPI_Module* SPIx, uint8_t SPI_CRC)
{
    if (SPI_CRC != SPI_CRC_RX)
    {
        /* return Tx CRC register value */
        return SPIx->CRCTDAT;
    }
    else
    {
        /* return Rx CRC register value */
        return SPIx->CRCRDAT;
    }
}


/**
*\*\name    SPI_CRC_Polynomial_Set.
*\*\fun     Set CRC Polynomial from SPI_CRC_POLY register.
*\*\param   SPIx :
*\*\          - SPI1       
*\*\          - SPI2  
*\*\param   polynomial      max 0xffff           
*\*\return  none.
**/
void SPI_CRC_Polynomial_Set(SPI_Module* SPIx, uint16_t polynomial)
{
    /* Return the CRC polynomial register value */
    SPIx->CRCPOLY = polynomial;
}


/**
*\*\name    SPI_CRC_Polynomial_Get.
*\*\fun     Get CRC Polynomial from SPI_CRC_POLY register.
*\*\param   SPIx :
*\*\          - SPI1       
*\*\          - SPI2               
*\*\return  The CRC Polynomial register value.
**/
uint16_t SPI_CRC_Polynomial_Get(SPI_Module* SPIx)
{
    /* Return the CRC polynomial register value */
    return SPIx->CRCPOLY;
}


/**
*\*\name    SPI_I2S_Mode_Select.
*\*\fun     Select working on SPI mode or I2S mode.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   Mode :
*\*\          - SEL_SPI_Mode
*\*\          - SEL_I2S_Mode
*\*\return  none
*\*\note    Must be used with I2S or SPI OFF.
**/
void SPI_I2S_Mode_Select(SPI_Module* SPIx, uint16_t Mode)
{
    /* Clear MODSEL bit */
    SPIx->I2SCFG &= I2S_MODE_MASK;
    /* Select the mode */
    SPIx->I2SCFG |= Mode;  
}


/**
*\*\name    I2S_ON.
*\*\fun     I2S turn ON.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\return  none
**/
void I2S_ON(SPI_Module* SPIx)
{
    /* Set the SPI_I2SCFG ON bit to wake up the I2S from power down mode */
    SPIx->I2SCFG |= I2S_TURN_ON;
}


/**
*\*\name    I2S_OFF.
*\*\fun     I2S turn OFF.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\return  none
**/
void I2S_OFF(SPI_Module* SPIx)
{
    /* Clear the SPI_I2SCFG ON bit, The I2S go to power down mode */
    SPIx->I2SCFG &= I2S_TURN_OFF;
}


/**
*\*\name    I2S_Initializes_Structure.
*\*\fun     Fills each I2S_InitStruct member with its default value.
*\*\param   I2S_InitStruct :
*\*\          - I2sMode
*\*\          - Standard
*\*\          - DataFormat
*\*\          - MCLKEnable
*\*\          - AudioFrequency
*\*\          - CLKPOL      
*\*\return  none
**/
void I2S_Initializes_Structure(I2S_InitType* I2S_InitStruct)
{
    /*--------------- Reset I2S init structure parameters values -----------------*/
    /* Initialize the I2sMode member */
    I2S_InitStruct->I2sMode = I2S_MODE_SlAVE_TX;

    /* Initialize the Standard member */
    I2S_InitStruct->Standard = I2S_STD_PHILLIPS;

    /* Initialize the DataFormat member */
    I2S_InitStruct->DataFormat = I2S_DATA_FMT_16BITS;

    /* Initialize the MCLKEnable member */
    I2S_InitStruct->MCLKEnable = DISABLE;

    /* Initialize the AudioFrequency member */
    I2S_InitStruct->AudioFrequency = I2S_AUDIO_FREQ_DEFAULT;

    /* Initialize the CLKPOL member */
    I2S_InitStruct->CLKPOL = I2S_CLKPOL_LOW;
}


/**
*\*\name    I2S_Initializes.
*\*\fun     Initializes the SPIx according to I2S_InitStruct.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   I2S_InitType :
*\*\          - I2sMode
*\*\           - I2S_MODE_SlAVE_TX 
*\*\           - I2S_MODE_SlAVE_RX 
*\*\           - I2S_MODE_MASTER_TX
*\*\           - I2S_MODE_MASTER_RX
*\*\          - Standard
*\*\           - I2S_STD_PHILLIPS      
*\*\           - I2S_STD_MSB_ALIGN     
*\*\           - I2S_STD_LSB_ALIGN     
*\*\           - I2S_STD_PCM_SHORTFRAME
*\*\           - I2S_STD_PCM_LONGFRAME 
*\*\          - DataFormat
*\*\           - I2S_DATA_FMT_16BITS          
*\*\           - I2S_DATA_FMT_16BITS_EXTENDED 
*\*\           - I2S_DATA_FMT_24BITS          
*\*\           - I2S_DATA_FMT_32BITS          
*\*\          - MCLKEnable
*\*\           - ENABLE 
*\*\           - DISABLE
*\*\          - AudioFrequency
*\*\           - I2S_AUDIO_FREQ_192K   
*\*\           - I2S_AUDIO_FREQ_96K    
*\*\           - I2S_AUDIO_FREQ_48K    
*\*\           - I2S_AUDIO_FREQ_44K    
*\*\           - I2S_AUDIO_FREQ_32K    
*\*\           - I2S_AUDIO_FREQ_22K    
*\*\           - I2S_AUDIO_FREQ_16K    
*\*\           - I2S_AUDIO_FREQ_11K    
*\*\           - I2S_AUDIO_FREQ_8K     
*\*\           - I2S_AUDIO_FREQ_DEFAULT
*\*\          - CLKPOL
*\*\           - I2S_CLKPOL_LOW 
*\*\           - I2S_CLKPOL_HIGH
*\*\return  none
**/
void I2S_Initializes(SPI_Module* SPIx, I2S_InitType* I2S_InitStruct)
{
    I2S_Mode_Config(SPIx, I2S_InitStruct->I2sMode);
    I2S_Standard_Config(SPIx, I2S_InitStruct->Standard);
    I2S_DataFormat_Config(SPIx, I2S_InitStruct->DataFormat);
    if(I2S_InitStruct->MCLKEnable == ENABLE)
    {
        I2S_MCLK_Enable(SPIx);
    }
    else
    {
        I2S_MCLK_Disable(SPIx);
    }
    I2S_AudioFrequency_Config(SPIx,I2S_InitStruct->AudioFrequency);
    I2S_CLKPOL_Config(SPIx, I2S_InitStruct->CLKPOL);
}


/**
*\*\name    I2S_Mode_Config.
*\*\fun     Config the I2s I2sMode.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   I2sMode :
*\*\          - I2S_MODE_SlAVE_TX 
*\*\          - I2S_MODE_SlAVE_RX 
*\*\          - I2S_MODE_MASTER_TX
*\*\          - I2S_MODE_MASTER_RX
*\*\return  none
*\*\note    Must be used with I2S OFF.
**/
void I2S_Mode_Config(SPI_Module* SPIx, uint16_t I2sMode)
{
    /* Clear SPI_I2SCFG MODCFG bits */
    SPIx->I2SCFG &= I2S_MODE_MASK;
    /* Set SPI_I2SCFG MODCFG bits */
    SPIx->I2SCFG |= I2sMode;
}


/**
*\*\name    I2S_Standard_Config.
*\*\fun     Config the I2s Standard.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   I2sMode :
*\*\          - I2S_STD_PHILLIPS      
*\*\          - I2S_STD_MSB_ALIGN     
*\*\          - I2S_STD_LSB_ALIGN     
*\*\          - I2S_STD_PCM_SHORTFRAME
*\*\          - I2S_STD_PCM_LONGFRAME 
*\*\return  none
**/
void I2S_Standard_Config(SPI_Module* SPIx, uint16_t Standard)
{
    /* Clear SPI_I2SCFG STDSEL and PCMFSYNC bit */
    SPIx->I2SCFG &= I2S_STANDARD_MASK;
    /* Set SPI_I2SCFG STDSEL and PCMFSYNC bit */
    SPIx->I2SCFG |= Standard;
}


/**
*\*\name    I2S_DataFormat_Config.
*\*\fun     Config the I2s DataFormat.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   DataFormat :
*\*\          - I2S_DATA_FMT_16BITS          
*\*\          - I2S_DATA_FMT_16BITS_EXTENDED 
*\*\          - I2S_DATA_FMT_24BITS          
*\*\          - I2S_DATA_FMT_32BITS  
*\*\return  none
**/
void I2S_DataFormat_Config(SPI_Module* SPIx, uint16_t DataFormat)
{
    /* Clear SPI_I2SCFG CHBITS and TDATLEN bit */
    SPIx->I2SCFG &= I2S_DATA_FORMAT_MASK;
    /* Set SPI_I2SCFG CHBITS and TDATLEN bit */
    SPIx->I2SCFG |= DataFormat;
}


/**
*\*\name    I2S_MCLK_Enable.
*\*\fun     Enable the I2s MCLK.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\return  none
**/
void I2S_MCLK_Enable(SPI_Module* SPIx)
{
    /* Set SPI_I2SPREDIV MCLKOEN bit */
    SPIx->I2SPREDIV |= I2S_MCLK_ENABLE;
}


/**
*\*\name    I2S_MCLK_Disable.
*\*\fun     Disable the I2s MCLK.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   MCLKEnable :
*\*\return  none
**/
void I2S_MCLK_Disable(SPI_Module* SPIx)
{
    /* Clear SPI_I2SPREDIV MCLKOEN bit */
    SPIx->I2SPREDIV &= I2S_MCLK_DISABLE;
}


/**
*\*\name    I2S_Config_MCLKEnable_And_AudioFrequency.
*\*\fun     Config the I2s MCLKEnable and AudioFrequency.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   AudioFrequency :
*\*\          - I2S_AUDIO_FREQ_192K   
*\*\          - I2S_AUDIO_FREQ_96K    
*\*\          - I2S_AUDIO_FREQ_48K    
*\*\          - I2S_AUDIO_FREQ_44K    
*\*\          - I2S_AUDIO_FREQ_32K    
*\*\          - I2S_AUDIO_FREQ_22K    
*\*\          - I2S_AUDIO_FREQ_16K    
*\*\          - I2S_AUDIO_FREQ_11K    
*\*\          - I2S_AUDIO_FREQ_8K     
*\*\          - I2S_AUDIO_FREQ_DEFAULT
*\*\return  none
**/
void I2S_AudioFrequency_Config(SPI_Module* SPIx, uint32_t AudioFrequency)
{
    uint16_t i2sdiv = 2, i2sodd = 0, packetlength = 1;
    uint32_t tmp = 0;///
    RCC_ClocksType RCC_Clocks;
    uint32_t sourceclock = 0;

    /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
    if (AudioFrequency == I2S_AUDIO_FREQ_DEFAULT)
    {
        i2sodd = (uint16_t)0;
        i2sdiv = (uint16_t)2;
    }
    else
    {
        /* Check the frame length (For the SPI_I2SCFG CHBITSbit) */
        if (SPIx->I2SCFG & SPI_I2SCFG_CHBITS)
        {
            /* Packet length is 32 bits */
            packetlength = 2;
        }
        else
        {
            /* Packet length is 16 bits */
            packetlength = 1;
        }
        
        /* I2S Clock source is System clock: Get System Clock frequency */
        RCC_Clocks_Frequencies_Value_Get(&RCC_Clocks); 

        /* Get the source clock value: based on System Clock value */
        sourceclock = RCC_Clocks.SysclkFreq;

        /* Compute the Real divider depending on the MCLK output state with a floating point */
        /* Get the SPIx->I2SPREDIV MCLKOEN bit state */
        if ( SPIx->I2SPREDIV & I2S_MCLK_ENABLE)
        {
            /* MCLK output is enabled */
            tmp = (uint16_t)(((((sourceclock / 256) * 10) / AudioFrequency)) + 5);
        }
        else
        {
            /* MCLK output is disabled */
            tmp = (uint16_t)(((((sourceclock / (32 * packetlength)) * 10) / AudioFrequency)) + 5);
        }

        /* Remove the floating point */
        tmp = tmp / 10;

        /* Check the parity of the divider */
        i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);

        /* Compute the i2sdiv prescaler */
        i2sdiv = (uint16_t)((tmp - i2sodd) / 2);

        /* Get the Mask for the Odd bit (SPI_I2SPREDIV[8]) register */
        i2sodd = (uint16_t)(i2sodd << 8);
    }
        /* Test if the divider is 1 or 0 or greater than 0xFF */
    if ((i2sdiv < 2) || (i2sdiv > 0xFF))
    {
        /* Set the default values */
        i2sdiv = 2;
        i2sodd = 0;
    }

    /* Write to SPIx I2SPREDIV register the computed value */
    SPIx->I2SPREDIV = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (SPIx->I2SPREDIV & I2S_MCLK_ENABLE)));
}


/**
*\*\name    I2S_CLKPOL_Config.
*\*\fun     Config the I2s CLKPOL.
*\*\param   SPIx :
*\*\          - SPI1
*\*\          - SPI2
*\*\param   CLKPOL :
*\*\          - I2S_CLKPOL_LOW 
*\*\          - I2S_CLKPOL_HIGH
*\*\return  none
**/
void I2S_CLKPOL_Config(SPI_Module* SPIx, uint16_t CLKPOL)
{
    /* Clear SPI_I2SPREDIV CLKPOL bit */
    SPIx->I2SCFG &= I2S_CLKPOL_MASK;
    /* Set SPI_I2SPREDIV CLKPOL bit */
    SPIx->I2SCFG |= CLKPOL;
}


/**
*\*\name    SPI_I2S_Interrupts_Enable.
*\*\fun     Enable SPI interrupts.
*\*\param   SPIx :
*\*\          - SPI1    
*\*\          - SPI2       
*\*\param   spi_interrupt :
*\*\          - SPI_I2S_INT_TE    SPI_CTRL2
*\*\          - SPI_I2S_INT_RNE   SPI_CTRL2
*\*\          - SPI_I2S_INT_ERR   SPI_CTRL2
*\*\return  none
**/
void SPI_I2S_Interrupts_Enable(SPI_Module* SPIx, uint8_t spi_interrupt)
{
    /* Set the SPI_CTRL2 TEINTEN/RNEINTEN/ERRINTEN bit to enable SPI or I2S interrupts */
    SPIx->CTRL2 |= spi_interrupt;
}

/**
*\*\name    SPI_I2S_Interrupts_Disable.
*\*\fun     Disable SPI interrupts.
*\*\param   SPIx :
*\*\          - SPI1       
*\*\          - SPI2             
*\*\param   spi_interrupt :
*\*\          - SPI_I2S_INT_TE    SPI_CTRL2
*\*\          - SPI_I2S_INT_RNE   SPI_CTRL2
*\*\          - SPI_I2S_INT_ERR   SPI_CTRL2
*\*\return  none
**/
void SPI_I2S_Interrupts_Disable(SPI_Module* SPIx, uint8_t spi_interrupt)
{
    /* Clean the SPI_CTRL2 TEINTEN/RNEINTEN/ERRINTEN bit to disable SPI or I2S interrupts */
    SPIx->CTRL2 &= (~spi_interrupt);
}


/**
*\*\name    SPI_I2S_DMA_Transfer_Enable.
*\*\fun     Enable SPI or I2S DMA transfer.
*\*\param   SPIx :
*\*\          - SPI1      
*\*\          - SPI2           
*\*\param   SPI_I2S_DMARequest :
*\*\          - SPI_I2S_DMA_TX
*\*\          - SPI_I2S_DMA_RX
*\*\return  none
**/
void SPI_I2S_DMA_Transfer_Enable(SPI_Module* SPIx, uint16_t SPI_I2S_DMARequest)
{
    /* Set the SPI_CTRL2 TDMAEN/RDMAEN bit to enable TX/RX DMA transfer */
    SPIx->CTRL2 |= SPI_I2S_DMARequest;
}


/**
*\*\name    SPI_I2S_DMA_Transfer_Disable.
*\*\fun     Disable SPI or I2S DMA transfer.
*\*\param   SPIx :
*\*\          - SPI1       
*\*\          - SPI2          
*\*\param   SPI_I2S_DMARequest :
*\*\          - SPI_I2S_DMA_TX
*\*\          - SPI_I2S_DMA_RX
*\*\return  none
**/
void SPI_I2S_DMA_Transfer_Disable(SPI_Module* SPIx, uint16_t SPI_I2S_DMARequest)
{
    /* Clean the SPI_CTRL2 TDMAEN/RDMAEN bit to disable TX/RX DMA transfer */
    SPIx->CTRL2 &= (uint16_t)~SPI_I2S_DMARequest;
}


/**
*\*\name    SPI_I2S_Data_Transmit.
*\*\fun     Transmits a Data through the SPIx/I2Sx peripheral.
*\*\param   SPIx :
*\*\          - SPI1       
*\*\          - SPI2             
*\*\param   Data           \* Data to be transmitted *\
*\*\return  none
**/
void SPI_I2S_Data_Transmit(SPI_Module* SPIx, uint16_t Data)
{
    /* Write in the SPI_DAT register the data to be sent */
    SPIx->DAT = Data;
}


/**
*\*\name    SPI_I2S_Data_Get.
*\*\fun     Get SPI/I2S data from SPI_DAT register.
*\*\param   SPIx :
*\*\          - SPI1       
*\*\          - SPI2             
*\*\return  The data in the SPI_DAT register
**/
uint16_t SPI_I2S_Data_Get(SPI_Module* SPIx)
{
    /* Return the data in the SPI_DAT register */
    return SPIx->DAT;
}


/**
*\*\name    SPI_I2S_Flag_Status_Get.
*\*\fun     Get SPI/I2S flag status.
*\*\param   SPIx :
*\*\          - SPI1       
*\*\          - SPI2             
*\*\param   spi_i2s_flag :
*\*\          - SPI_I2S_FLAG_TE
*\*\          - SPI_I2S_FLAG_RNE
*\*\          - SPI_I2S_FLAG_BUSY
*\*\          - SPI_I2S_FLAG_OVER
*\*\          - SPI_FLAG_MODERR
*\*\          - SPI_FLAG_CRCERR
*\*\          - I2S_FLAG_UNDER
*\*\          - I2S_FLAG_CHSIDE 
*\*\return  SET or RESET
**/
FlagStatus SPI_I2S_Flag_Status_Get(SPI_Module* SPIx, uint8_t spi_i2s_flag)
{
    return (((SPIx->STS & spi_i2s_flag) == spi_i2s_flag) ? SET : RESET);  
}

/**
*\*\name    SPI_I2S_Get_Flag_Status.
*\*\fun     Get SPI/I2S flag status.
*\*\param   SPIx :
*\*\          - SPI1       
*\*\          - SPI2             
*\*\param   spi_i2s_flag :
*\*\          - SPI_I2S_INT_FLAG_RNE 
*\*\          - SPI_I2S_INT_FLAG_TE  
*\*\          - I2S_INT_FLAG_UNDER   
*\*\          - SPI_INT_FLAG_CRCERR  
*\*\          - SPI_INT_FLAG_MODERR  
*\*\          - SPI_I2S_INT_FLAG_OVER
*\*\          - SPI_I2S_INT_FLAG_ERR 
*\*\return  SET or RESET
**/

FlagStatus SPI_I2S_Interrupt_Flag_Status_Get(SPI_Module* SPIx, uint16_t spi_i2s_flag)
{
    /* Interrupt flag */
    switch (spi_i2s_flag)
    {
        case SPI_I2S_INT_FLAG_TE:
            if((SPIx->CTRL2 & SPI_I2S_INT_TE) == SPI_I2S_INT_TE && (SPIx->STS & SPI_I2S_INT_FLAG_TE) == SPI_I2S_INT_FLAG_TE)
            {
                return SET;
            }
            else
            {
                return RESET;
            }
        case SPI_I2S_INT_FLAG_RNE:
            if((SPIx->CTRL2 & SPI_I2S_INT_RNE) && (SPIx->STS & SPI_I2S_INT_FLAG_RNE))
            {
                return SET;
            }
            else
            {
                return RESET;
            }
        case SPI_I2S_INT_FLAG_ERR:
        case I2S_INT_FLAG_UNDER:    
        case SPI_INT_FLAG_CRCERR:   
        case SPI_INT_FLAG_MODERR:   
        case SPI_I2S_INT_FLAG_OVER:
            if((SPIx->CTRL2 & SPI_I2S_INT_ERR) && (SPIx->STS & spi_i2s_flag))
            {
                return SET;
            }
            else
            {
                return RESET;
            }
        default:
           return RESET;
    }
}


/**
*\*\name    SPI_I2S_Get_Flag_Status.
*\*\fun     Get SPI/I2S flag status.
*\*\param   SPIx :
*\*\          - SPI1       
*\*\          - SPI2            
*\*\param   spi_i2s_flag :
*\*\          - SPI_I2S_FLAG_OVER
*\*\          - SPI_FLAG_CRCERR
*\*\          - I2S_FLAG_UNDER     
*\*\return  none
**/
void SPI_I2S_Clear_Flag_Status(SPI_Module* SPIx, uint16_t spi_i2s_flag)
{
    volatile u8 temp_vlue;
    switch (spi_i2s_flag)
    {
      case SPI_FLAG_CRCERR:
            SPIx->STS &= (uint16_t)(~spi_i2s_flag);
        break;
      case I2S_FLAG_UNDER:
           temp_vlue = SPIx->STS;
        break;
      default:
        break;
    }
    if((spi_i2s_flag == SPI_FLAG_CRCERR) || (spi_i2s_flag == SPI_INT_FLAG_CRCERR))
    {
        /* Clear the selected SPI CRC Error (CRCERR) flag */
        SPIx->STS &= (uint16_t)(~spi_i2s_flag);
    }
    else if((spi_i2s_flag == I2S_FLAG_UNDER) || (spi_i2s_flag == I2S_INT_FLAG_UNDER))
    {
      temp_vlue = SPIx->STS;
    }
    else
    {
        /* read SPI_DAT and SPI_STS to Clear the Flag*/
        temp_vlue = SPIx->DAT;
        temp_vlue = SPIx->STS;
    }
}


