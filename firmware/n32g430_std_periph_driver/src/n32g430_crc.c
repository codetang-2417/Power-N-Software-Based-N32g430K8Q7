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
*\*\file n32g430_crc.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

#include "n32g430_crc.h"

/** CRC Private Defines **/


/** CRC Driving Functions Declaration **/

/**
*\*\name    CRC32_Reset.
*\*\fun     Resets the CRC Data register (DAT).
*\*\param   none
*\*\return  none
**/
void CRC32_Reset(void)
{
    /* Reset CRC generator */
    CRC->CRC32CTRL = CRC_CRC32_RESET;
}

/**
*\*\name    CRC32_Calculate.
*\*\fun     Computes the 32-bit CRC of a given data word(32-bit).
*\*\param   data :
*\*\          - data word(32-bit) to compute its CRC
*\*\return  32-bit CRC
**/
uint32_t CRC32_Calculate(uint32_t data)
{
    /* Write data to the CRC32DAT register */
    CRC->CRC32DAT = data;
    /* Returns the computed CRC result */
    return (CRC->CRC32DAT);
}

/**
*\*\name    CRC32_Buffer_Calculate.
*\*\fun     Computes the 32-bit CRC of a given buffer of data word(32-bit).
*\*\param   p_buf :
*\*\          - pointer to the buffer containing the data to be computed
*\*\param   buf_len :
*\*\          - length of the buffer to be computed
*\*\return  32-bit CRC
**/
uint32_t CRC32_Buffer_Calculate(uint32_t p_buf[], uint32_t buf_len)
{
    uint32_t index = 0;

    for (index = 0; index < buf_len; index++)
    {
        /* Write data to the CRC32DAT register */
        CRC->CRC32DAT = p_buf[index];
    }
    /* Returns the computed CRC result */
    return (CRC->CRC32DAT);
}

/**
*\*\name    CRC32_Get.
*\*\fun     Returns the current CRC value.
*\*\param   none
*\*\return  32-bit CRC
**/
uint32_t CRC32_Get(void)
{
    /* Returns the computed CRC result */
    return (CRC->CRC32DAT);
}

/**
*\*\name    CRC32_Independent_Data_Save.
*\*\fun     Stores a 8-bit data in the Independent Data(ID) register.
*\*\param   value :
*\*\          - 8-bit value to be stored in the ID register
*\*\return  none
**/
void CRC32_Independent_Data_Save(uint8_t value)
{
    /* storage of 8-bit data */
    CRC->CRC32IDAT = value;
}

/**
*\*\name    CRC32_Independent_Data_Get.
*\*\fun     Returns the 8-bit data stored in the Independent Data(ID) register.
*\*\param   none
*\*\return  8-bit value of the ID register
**/
uint8_t CRC32_Independent_Data_Get(void)
{
    /* Returns the 8-bit data */
    return (CRC->CRC32IDAT);
}

/**
*\*\name    CRC16_Calculate.
*\*\fun     Computes the 16-bit CRC of a given data word(8-bit).
*\*\param   data :
*\*\          - data word(8-bit) to compute its CRC
*\*\return  16-bit CRC
**/
uint16_t CRC16_Calculate(uint8_t data)
{
    /* Write data to the CRC16DAT register */
    CRC->CRC16DAT = data;
    /* Returns the computed CRC16 result */
    return (CRC->CRC16D);
}

/**
*\*\name    CRC16_Buffer_Calculate.
*\*\fun     Computes the 16-bit CRC of a given buffer of data word(8-bit).
*\*\param   p_buf :
*\*\          - pointer to the buffer containing the data to be computed
*\*\param   buf_len :
*\*\          - length of the buffer to be computed
*\*\return  16-bit CRC
**/
uint16_t CRC16_Buffer_Calculate(uint8_t p_buf[], uint32_t buf_len)
{
    uint32_t index = 0;
    CRC->CRC16D = 0x00;
    for (index = 0; index < buf_len; index++)
    {
        /* Write data to the CRC16DAT register */
        CRC->CRC16DAT = p_buf[index];
    }
    /* Returns the computed CRC16 result */
    return (CRC->CRC16D);
}

/**
*\*\name    CRC16_Set.
*\*\fun     write a 8-bit data in the 16-bit CRC Data register.
*\*\param   data :
*\*\          - 8-bit data value to be writed in the 16-bit CRC Data register
*\*\return  none
**/
void CRC16_Set(uint8_t data)
{
    /* Writes 8-bit data to the CRC16DAT register */
    CRC->CRC16DAT = data;
}

/**
*\*\name    CRC16_Get.
*\*\fun     Returns the current CRC value.
*\*\param   none
*\*\return  16-bit CRC
**/
uint16_t CRC16_Get(void)
{
    /* Returns the CRC16 calculation result */
    return (CRC->CRC16D);
}

/**
*\*\name    CRC16_Little_Endian_Format_Set.
*\*\fun     Set the calculate data to little endian format.
*\*\param   none
*\*\return  none
**/
void CRC16_Little_Endian_Format_Set(void)
{
    CRC->CRC16CTRL |= CRC_LITTLE_ENDIAN_ENABLE;
}

/**
*\*\name    CRC16_Big_Endian_Format_Set.
*\*\fun     Set the calculate data to big endian format.
*\*\param   none
*\*\return  none
**/
void CRC16_Big_Endian_Format_Set(void)
{
    CRC->CRC16CTRL &= CRC_BIG_ENDIAN_ENABLE;
}

/**
*\*\name    CRC16_Value_Clean_Enable.
*\*\fun     Enable Clean CRC16 value.
*\*\param   none
*\*\return  none
**/
void CRC16_Value_Clean_Enable(void)
{
    CRC->CRC16CTRL |= CRC_CRC16_VALUE_CLEAR;
}

/**
*\*\name    CRC16_Value_Clean_Disable.
*\*\fun     Disable Clean CRC16 value.
*\*\param   none
*\*\return  none
**/
void CRC16_Value_Clean_Disable(void)
{
    CRC->CRC16CTRL &= CRC_CRC16_VALUE_NO_CLEAR;
}

/**
*\*\name    CRC_LRC_Set.
*\*\fun     Write LRC initial value.
*\*\param   data :
*\*\          - 8-bit data
*\*\return  none
**/
void CRC_LRC_Set(uint8_t data)
{
    /* Write LRC to verify the initial value */
    CRC->LRC = data;
}

/**
*\*\name    CRC_LRC_Get.
*\*\fun     Returns the current LRC value.
*\*\param   none
*\*\return  8-bit LRC
**/
uint8_t CRC_LRC_Get(void)
{
    /* Returns the LRC check value */
    return (CRC->LRC);
}

