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
*\*\file      n32g430_spi.h
*\*\author    Nations
*\*\version   v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved. 
**/
#ifndef __N32G430_SPI_H__
#define __N32G430_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

/** SPI Init structure definition **/
typedef struct
{
    uint16_t DataDirection; /* Specifies the SPI unidirectional or bidirectional data mode */

    uint16_t SpiMode;       /* Specifies the SPI operating mode */
                            
    uint16_t DataLen;       /* Specifies the SPI data size */

    uint16_t CLKPOL;        /* Specifies the serial clock steady state */
                             
    uint16_t CLKPHA;        /* Specifies the clock active edge for the bit capture */


    uint16_t NSS;           /* Specifies whether the NSS signal is managed by
                               hardware (NSS pin) or by software using the SSI bit */


    uint16_t BaudRatePres;  /* Specifies the Baud Rate prescaler value which will be
                               used to configure the transmit and receive SCK clock */

    uint16_t FirstBit;      /* Specifies whether data transfers start from MSB or LSB bit */

    uint16_t CRCPoly;       /* Specifies the polynomial used for the CRC calculation */
} SPI_InitType;

/** I2S Init structure definition **/
typedef struct
{
    uint16_t I2sMode;        /* Specifies the I2S operating mode */                           

    uint16_t Standard;       /* Specifies the standard used for the I2S communication */                         

    uint16_t DataFormat;     /* Specifies the data format for the I2S communication */

    uint16_t MCLKEnable;     /* Specifies whether the I2S MCLK output is enabled or not */                              

    uint32_t AudioFrequency; /* Specifies the frequency selected for the I2S communication */                                

    uint16_t CLKPOL;         /* Specifies the idle state of the I2S clock */
} I2S_InitType;

/** SPI_data_direction **/
#define SPI_DATADIRECTION_MASK        (~(SPI_CTRL1_RONLY | SPI_CTRL1_BIDIROEN | SPI_CTRL1_BIDIRMODE)) /* direction [15:14] and [10] bits Mask */
#define SPI_DIR_DOUBLELINE_FULLDUPLEX ((uint16_t)0x0000)
#define SPI_DIR_DOUBLELINE_RONLY      (SPI_CTRL1_RONLY)
#define SPI_DIR_SINGLELINE_RX         (SPI_CTRL1_BIDIRMODE)
#define SPI_DIR_SINGLELINE_TX         (SPI_CTRL1_BIDIRMODE | SPI_CTRL1_BIDIROEN)

/** SPI mode **/
#define SPI_MODE_MASK                 (~SPI_CTRL1_MSEL) /* MSEL bits Mask */
#define SPI_MODE_MASTER               (SPI_CTRL1_MSEL)
#define SPI_MODE_SLAVE                ((uint16_t)0x0000)

/** SPI_data_size **/
#define SPI_DATALEN_MASK              (~SPI_CTRL1_DATFF) /* DATFF bits Mask */
#define SPI_DATA_SIZE_16BITS          (SPI_CTRL1_DATFF)
#define SPI_DATA_SIZE_8BITS           ((uint16_t)0x0000)

#define SPI_CRCNEXT_ENABLE            (SPI_CTRL1_CRCNEXT)
#define CTRL1_CRCEN_ENABLE            (SPI_CTRL1_CRCEN)
#define CTRL1_CRCEN_DISABLE           (~SPI_CTRL1_CRCEN)

/** SPI_Clock_Polarity **/
#define SPI_CLKPOL_MASK               (~SPI_CTRL1_CLKPOL) /* CLKPOL bits Mask */
#define SPI_CLKPOL_LOW                ((uint16_t)0x0000)
#define SPI_CLKPOL_HIGH               (SPI_CTRL1_CLKPOL)

/** SPI_Clock_Phase **/
#define SPI_CLKPHA_MASK               (~SPI_CTRL1_CLKPHA) /* CLKPHA bits Mask */
#define SPI_CLKPHA_FIRST_EDGE         ((uint16_t)0x0000)
#define SPI_CLKPHA_SECOND_EDGE        (SPI_CTRL1_CLKPHA)

/** SPI_Slave_Select_management **/
#define SPI_NSS_MASK                  (~SPI_CTRL1_SSMEN) /* SSMEN bits Mask */
#define SPI_NSS_SOFT                  (SPI_CTRL1_SSMEN)
#define SPI_NSS_HARD                  ((uint16_t)0x0000)

#define SPI_SS_OUTPUT_ENABLE          SPI_CTRL2_SSOEN
#define SPI_SS_OUTPUT_DISABLE         (~SPI_CTRL2_SSOEN)

/** SPI_BaudRate_Prescaler **/
#define SPI_BAUDRATEPRES_MASK         (~SPI_CTRL1_BR) /* BR[2:0] bits Mask */
#define SPI_BR_PRESCALER_2            ((uint16_t)0x0000)
#define SPI_BR_PRESCALER_4            (SPI_CTRL1_BR0)
#define SPI_BR_PRESCALER_8            (SPI_CTRL1_BR1)
#define SPI_BR_PRESCALER_16           (SPI_CTRL1_BR1 | SPI_CTRL1_BR0)
#define SPI_BR_PRESCALER_32           (SPI_CTRL1_BR2)
#define SPI_BR_PRESCALER_64           (SPI_CTRL1_BR2 | SPI_CTRL1_BR0)
#define SPI_BR_PRESCALER_128          (SPI_CTRL1_BR2 | SPI_CTRL1_BR1)
#define SPI_BR_PRESCALER_256          (SPI_CTRL1_BR2 | SPI_CTRL1_BR1 | SPI_CTRL1_BR0)

/** SPI_MSB_LSB_transmission **/
#define SPI_FIRSTBIT_MASK             (~SPI_CTRL1_LSBFF) /* LSBFF bits Mask */
#define SPI_FB_MSB                    ((uint16_t)0x0000)
#define SPI_FB_LSB                    (SPI_CTRL1_LSBFF)

/** SPI CRCPOLY **/
#define SPI_CRCPOLY_MASK              (~SPI_CRCPOLY_CRCPOLY) /* SPI_CRCPOLY register Mask */  

/** SPI Converter **/
#define SPI_TURN_ON                   (SPI_CTRL1_SPIEN) /* SPIEN ON bit */
#define SPI_TURN_OFF                  (~SPI_CTRL1_SPIEN) /* SPIEN ON bit Mask */

/** I2s Mode **/
#define I2S_MODE_SEL_MASK             (~SPI_I2SCFG_MODSEL)/* selet spi/I2S mode bit */
#define SEL_SPI_Mode                  ((uint16_t)0x0000) 
#define SEL_I2S_Mode                  (SPI_I2SCFG_MODSEL)

#define I2S_MODE_MASK                 (~SPI_I2SCFG_MODCFG) /* MODCFG bit Mask */ 
#define I2S_MODE_SlAVE_TX             ((uint16_t)0x0000)
#define I2S_MODE_SlAVE_RX             (SPI_I2SCFG_MODCFG0)
#define I2S_MODE_MASTER_TX            (SPI_I2SCFG_MODCFG1)
#define I2S_MODE_MASTER_RX            (SPI_I2SCFG_MODCFG0 | SPI_I2SCFG_MODCFG1)

/** Standard **/
#define I2S_STANDARD_MASK             (~(SPI_I2SCFG_STDSEL | SPI_I2SCFG_PCMFSYNC)) /* STDSEL and PCMFSYNC bit Mask */
#define I2S_STD_PHILLIPS              ((uint16_t)0x0000)
#define I2S_STD_MSB_ALIGN             (SPI_I2SCFG_STDSEL0)
#define I2S_STD_LSB_ALIGN             (SPI_I2SCFG_STDSEL1)
#define I2S_STD_PCM_SHORTFRAME        (SPI_I2SCFG_STDSEL1 | SPI_I2SCFG_STDSEL0)
#define I2S_STD_PCM_LONGFRAME         (SPI_I2SCFG_STDSEL1 | SPI_I2SCFG_STDSEL0 | SPI_I2SCFG_PCMFSYNC)
                                                                                     

/** I2S_Data_Format **/
#define I2S_DATA_FORMAT_MASK          (~(SPI_I2SCFG_CHBITS | SPI_I2SCFG_TDATLEN)) /* CHBITS and TDATLEN bit Mask */
#define I2S_DATA_FMT_16BITS           ((uint16_t)0x0000)
#define I2S_DATA_FMT_16BITS_EXTENDED  (SPI_I2SCFG_CHBITS)
#define I2S_DATA_FMT_24BITS           (SPI_I2SCFG_TDATLEN0 | SPI_I2SCFG_CHBITS)
#define I2S_DATA_FMT_32BITS           (SPI_I2SCFG_TDATLEN1 | SPI_I2SCFG_CHBITS)

/** I2S_MCLK_Output **/
#define I2S_MCLK_ENABLE               (SPI_I2SPREDIV_MCLKOEN)
#define I2S_MCLK_DISABLE              (~SPI_I2SPREDIV_MCLKOEN)

/** I2S_Audio_Frequency **/
#define I2S_AUDIO_FREQ_192K           ((uint32_t)192000)
#define I2S_AUDIO_FREQ_96K            ((uint32_t)96000)
#define I2S_AUDIO_FREQ_48K            ((uint32_t)48000)
#define I2S_AUDIO_FREQ_44K            ((uint32_t)44100)
#define I2S_AUDIO_FREQ_32K            ((uint32_t)32000)
#define I2S_AUDIO_FREQ_22K            ((uint32_t)22050)
#define I2S_AUDIO_FREQ_16K            ((uint32_t)16000)
#define I2S_AUDIO_FREQ_11K            ((uint32_t)11025)
#define I2S_AUDIO_FREQ_8K             ((uint32_t)8000)
#define I2S_AUDIO_FREQ_DEFAULT        ((uint32_t)2)
    
/** I2S_Clock_Polarity **/
#define I2S_CLKPOL_MASK               (~SPI_I2SCFG_CLKPOL) /* MCLKOEN bit Mask */
#define I2S_CLKPOL_LOW                ((uint16_t)0x0000)
#define I2S_CLKPOL_HIGH               (SPI_I2SCFG_CLKPOL)

/** I2S Converter **/
#define I2S_TURN_ON                   (SPI_I2SCFG_I2SEN | SPI_I2SCFG_MODSEL) /* I2SEN and MODSEL bit */
#define I2S_TURN_OFF                  (~(SPI_I2SCFG_I2SEN | SPI_I2SCFG_MODSEL)) /* I2SEN  bit Mask */

/** SPI_I2S_DMA_transfer_requests **/
#define SPI_I2S_DMA_TX                (SPI_CTRL2_TDMAEN)
#define SPI_I2S_DMA_RX                (SPI_CTRL2_RDMAEN)

/** SPI_NSS_internal_software_management **/
#define SPI_NSS_HIGH                  (SPI_CTRL1_SSEL)
#define SPI_NSS_LOW                   (~SPI_CTRL1_SSEL)

/** SPI_CRC_Transmit_Receive **/
#define SPI_CRC_TX                    ((uint8_t)0x00)
#define SPI_CRC_RX                    ((uint8_t)0x01)

/** SPI_I2S_flags_definition **/

#define SPI_I2S_FLAG_RNE              (SPI_STS_RNE)
#define SPI_I2S_FLAG_TE               (SPI_STS_TE)
#define I2S_FLAG_CHSIDE               (SPI_STS_CHSIDE)
#define I2S_FLAG_UNDER                (SPI_STS_UNDER)
#define SPI_FLAG_CRCERR               (SPI_STS_CRCERR)
#define SPI_FLAG_MODERR               (SPI_STS_MODERR)
#define SPI_I2S_FLAG_OVER             (SPI_STS_OVER)
#define SPI_I2S_FLAG_BUSY             (SPI_STS_BUSY)

#define SPI_I2S_INT_RNE               (SPI_CTRL2_RNEINTEN)
#define SPI_I2S_INT_TE                (SPI_CTRL2_TEINTEN)
#define SPI_I2S_INT_ERR               (SPI_CTRL2_ERRINTEN)


#define SPI_I2S_INT_FLAG_RNE          (SPI_STS_RNE)
#define SPI_I2S_INT_FLAG_TE           (SPI_STS_TE)
#define I2S_INT_FLAG_UNDER            (SPI_STS_UNDER)
#define SPI_INT_FLAG_CRCERR           (SPI_STS_CRCERR)
#define SPI_INT_FLAG_MODERR           (SPI_STS_MODERR)
#define SPI_I2S_INT_FLAG_OVER         (SPI_STS_OVER)
#define SPI_I2S_INT_FLAG_ERR          (SPI_STS_UNDER | SPI_STS_CRCERR | SPI_STS_MODERR | SPI_STS_OVER)

/** SPI Macro Definition End **/

/** SPI Driving Functions Declaration **/

void SPI_I2S_Reset(SPI_Module* SPIx);

void SPI_ON(SPI_Module* SPIx);
void SPI_OFF(SPI_Module* SPIx);
void SPI_Initializes_Structure(SPI_InitType* SPI_InitStruct);
void SPI_Initializes(SPI_Module* SPIx, SPI_InitType* SPI_InitStruct);

void SPI_DataDirection_Config(SPI_Module* SPIx, uint16_t DataDirection);
void SPI_SpiMode_Config(SPI_Module* SPIx, uint16_t SpiMode);
void SPI_DataLen_Config(SPI_Module* SPIx, uint16_t DataLen);
void SPI_CLKPOL_Config(SPI_Module* SPIx, uint16_t CLKPOL);
void SPI_CLKPHA_Config(SPI_Module* SPIx, uint16_t CLKPHA);
void SPI_NSS_Config(SPI_Module* SPIx, uint16_t NSS);
void SPI_BaudRatePres_Config(SPI_Module* SPIx, uint16_t BaudRatePres);
void SPI_FirstBit_Config(SPI_Module* SPIx, uint16_t FirstBit);
void SPI_CRC_Polynomial_Set(SPI_Module* SPIx, uint16_t polynomial);
uint16_t SPI_CRC_Polynomial_Get(SPI_Module* SPIx);
void SPI_Set_Nss_Level(SPI_Module* SPIx, uint16_t SPI_NSS_Internal_Soft);
void SPI_SS_Output_Enable(SPI_Module* SPIx);
void SPI_SS_Output_Disable(SPI_Module* SPIx);
void SPI_Next_Transmit_CRC(SPI_Module* SPIx);
void SPI_CRC_Enable(SPI_Module* SPIx);
void SPI_CRC_Disable(SPI_Module* SPIx);
uint16_t SPI_CRC_Data_Get(SPI_Module* SPIx, uint8_t SPI_CRC);


void SPI_I2S_Mode_Select(SPI_Module* SPIx, uint16_t Mode);
void I2S_ON(SPI_Module* SPIx);
void I2S_OFF(SPI_Module* SPIx);
void I2S_Initializes_Structure(I2S_InitType* I2S_InitStruct);
void I2S_Initializes(SPI_Module* SPIx, I2S_InitType* I2S_InitStruct);
void I2S_Mode_Config(SPI_Module* SPIx, uint16_t I2sMode);
void I2S_Standard_Config(SPI_Module* SPIx, uint16_t Standard);
void I2S_DataFormat_Config(SPI_Module* SPIx, uint16_t DataFormat);
void I2S_MCLK_Enable(SPI_Module* SPIx);
void I2S_MCLK_Disable(SPI_Module* SPIx);
void I2S_AudioFrequency_Config(SPI_Module* SPIx, uint32_t AudioFrequency);
void I2S_CLKPOL_Config(SPI_Module* SPIx, uint16_t CLKPOL);

void SPI_I2S_Interrupts_Enable(SPI_Module* SPIx, uint8_t spi_interrupt);
void SPI_I2S_Interrupts_Disable(SPI_Module* SPIx, uint8_t spi_interrupt);

void SPI_I2S_DMA_Transfer_Enable(SPI_Module* SPIx, uint16_t SPI_I2S_DMARequest);
void SPI_I2S_DMA_Transfer_Disable(SPI_Module* SPIx, uint16_t SPI_I2S_DMARequest);

void SPI_I2S_Data_Transmit(SPI_Module* SPIx, uint16_t Data);
uint16_t SPI_I2S_Data_Get(SPI_Module* SPIx);

FlagStatus SPI_I2S_Flag_Status_Get(SPI_Module* SPIx, uint8_t spi_i2s_flag);
FlagStatus SPI_I2S_Interrupt_Flag_Status_Get(SPI_Module* SPIx, uint16_t spi_i2s_flag);
void SPI_I2S_Clear_Flag_Status(SPI_Module* SPIx, uint16_t spi_i2s_flag);
#ifdef __cplusplus
}
#endif

#endif /*__N32G430_SPI_H__ */

