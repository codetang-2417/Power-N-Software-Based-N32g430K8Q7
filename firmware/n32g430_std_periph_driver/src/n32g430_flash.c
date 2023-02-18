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
*\*\file n32g430_flash.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/
#include "n32g430_flash.h"

/** FLASH Driving Functions Declaration **/

/**
*\*\name    FLASH_Latency_Set
*\*\fun     Sets the code latency value.
*\*\note    This function can be used for N32G430 devices.
*\*\param   flash_latency :
*\*\            - FLASH_LATENCY_0    FLASH Zero Latency cycle
*\*\            - FLASH_LATENCY_1    FLASH One Latency cycle
*\*\            - FLASH_LATENCY_2    FLASH Two Latency cycles
*\*\            - FLASH_LATENCY_3    FLASH Three Latency cycles
*\*\return  none
**/
void FLASH_Latency_Set(uint32_t flash_latency)
{
    uint32_t temp_value = 0;

    /* Read the AC register */
    temp_value = FLASH->AC;

    /* Sets the Latency value */
    temp_value &= (~FLASH_LATENCY_MASK);
    temp_value |= flash_latency;

    /* Write the AC register */
    FLASH->AC = temp_value;
}

/**
*\*\name    FLASH_Latency_Get
*\*\fun     Get the code latency value.
*\*\note    This function can be used for N32G430 devices.
*\*\param   none
*\*\return  FLASH_LATENCY :
*\*\            - FLASH_LATENCY_0    FLASH Zero Latency cycle
*\*\            - FLASH_LATENCY_1    FLASH One Latency cycle
*\*\            - FLASH_LATENCY_2    FLASH Two Latency cycles
*\*\            - FLASH_LATENCY_3    FLASH Three Latency cycles
**/
uint8_t FLASH_Latency_Get(void)
{
    /* Read the AC register */
    return (uint8_t)(FLASH->AC & FLASH_LATENCY_MASK);
}

/**
*\*\name    FLASH_Prefetch_Buffer_Enable
*\*\fun     Enables the Prefetch Buffer.
*\*\note    This function can be used for N32G430 devices. 
*\*\param   none 
*\*\return  none
**/
void FLASH_Prefetch_Buffer_Enable(void)
{
    /* Enable the Prefetch Buffer */
    FLASH->AC |= FLASH_PREFETCHBUF_EN;
}

/**
*\*\name    FLASH_Prefetch_Buffer_Set
*\*\fun     Disables the Prefetch Buffer.
*\*\note    This function can be used for N32G430 devices.
*\*\param   none
*\*\return  none
**/
void FLASH_Prefetch_Buffer_Disable(void)
{
    /* Disable the Prefetch Buffer */
    FLASH->AC &= FLASH_PREFETCHBUF_DIS;
}

/**
*\*\name    FLASH_ICache_Reset
*\*\fun     ICache Reset.
*\*\note    This function can be used for N32G430 devices.
*\*\param   none
*\*\return  none
**/
void FLASH_ICache_Reset(void)
{
    /* ICache Reset */
    FLASH->AC |= FLASH_ICAHRST_MSK;
}

/**
*\*\name    FLASH_ICache_Enable
*\*\fun     Enables the iCache.
*\*\note    This function can be used for N32G430 devices.
*\*\param   none
*\*\return  none
**/
void FLASH_ICache_Enable(void)
{
    /* Enable the iCache */
    FLASH->AC |= FLASH_ICACHE_EN;
}

/**
*\*\name    FLASH_ICache_Disable
*\*\fun     Disables the iCache.
*\*\note    This function can be used for N32G430 devices.
*\*\param   none
*\*\return  none
**/
void FLASH_ICache_Disable(void)
{
    /* Disable the iCache */
    FLASH->AC &= FLASH_ICACHE_DIS;
}


/**
*\*\name    FLASH_ICache_Status_Get
*\*\fun     Get the iCache status.
*\*\note    This function can be used for N32G430 devices.
*\*\param   none
*\*\return  FlagStatus :
*\*\            - SET
*\*\            - RESET
**/
FlagStatus FLASH_ICache_Status_Get(void)
{
    if ((FLASH->AC & FLASH_AC_ICAHEN) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}



/**
*\*\name   FLASH_Cache_LOCK_Start
*\*\fun    Start cache lock.
*\*\note   This function can be used for N32G430 devices.
*\*\param  lock_start_way :
*\*\            - FLASH_CAHR_LOCKSTRT_WAY0
*\*\            - FLASH_CAHR_LOCKSTRT_WAY1
*\*\            - FLASH_CAHR_LOCKSTRT_WAY2
*\*\            - FLASH_CAHR_LOCKSTRT_WAY3
*\*\return none
**/
void FLASH_Cache_LOCK_Start(uint32_t lock_start_way)
{
    FLASH->CAHR &= (~(lock_start_way << FLASH_CAHR_LOCK_OFFSET));
    FLASH->CAHR |= lock_start_way;
}

/**
*\*\name   FLASH_Cache_LOCK_Stop
*\*\fun    Start cache lock.
*\*\note   This function can be used for N32G430 devices.
*\*\param  lock_stop_way :
*\*\            - FLASH_CAHR_LOCKSTOP_WAY0
*\*\            - FLASH_CAHR_LOCKSTOP_WAY1
*\*\            - FLASH_CAHR_LOCKSTOP_WAY2
*\*\            - FLASH_CAHR_LOCKSTOP_WAY3
*\*\return none
**/
void FLASH_Cache_LOCK_Stop(uint32_t lock_stop_way)
{
    FLASH->CAHR |= lock_stop_way;
}


/**
*\*\name   FLASH_Cache_LOCK_Cancel
*\*\fun    Start cache lock.
*\*\note   This function can be used for N32G430 devices.
*\*\param  lock_stop_way :
*\*\            - FLASH_CAHR_LOCKSTOP_WAY0
*\*\            - FLASH_CAHR_LOCKSTOP_WAY1
*\*\            - FLASH_CAHR_LOCKSTOP_WAY2
*\*\            - FLASH_CAHR_LOCKSTOP_WAY3
*\*\return none
**/
void FLASH_Cache_LOCK_Cancel(uint32_t lock_stop_way)
{
    FLASH->CAHR |= lock_stop_way;
    FLASH->CAHR &= (~lock_stop_way);
}

/**
*\*\name   FLASH_Cache_LOCK_Status_Get
*\*\fun    Get cache lock status.
*\*\note   This function can be used for N32G430 devices.
*\*\param  lock_way :
*\*\            - FLASH_CAHR_LOCKSTRT_WAY0
*\*\            - FLASH_CAHR_LOCKSTRT_WAY1
*\*\            - FLASH_CAHR_LOCKSTRT_WAY2
*\*\            - FLASH_CAHR_LOCKSTRT_WAY3
*\*\            - FLASH_CAHR_LOCKSTOP_WAY0
*\*\            - FLASH_CAHR_LOCKSTOP_WAY1
*\*\            - FLASH_CAHR_LOCKSTOP_WAY2
*\*\            - FLASH_CAHR_LOCKSTOP_WAY3
*\*\return  FlagStatus :
*\*\            - SET
*\*\            - RESET
**/
FlagStatus FLASH_Cache_LOCK_Status_Get(uint32_t lock_way)
{
    if ((FLASH->CAHR & lock_way) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}



/**
*\*\name   FLASH_Unlock
*\*\fun    Unlocks the FLASH Program Erase Controller.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return none
**/
void FLASH_Unlock(void)
{
    FLASH->KEY = FLASH_KEY1;
    FLASH->KEY = FLASH_KEY2;
}

/**
*\*\name   FLASH_Lock
*\*\fun    Locks the FLASH Program Erase Controller.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return none
**/
void FLASH_Lock(void)
{
    FLASH->CTRL |= FLASH_CTRL_SET_LOCK;
}


/**
*\*\name   Option_Bytes_Unlock
*\*\fun    Unlocks the Option_Bytes Program Erase Controller.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return none
**/
void Option_Bytes_Unlock(void)
{
    FLASH->OPTKEY = FLASH_KEY1;
    FLASH->OPTKEY = FLASH_KEY2;
}


/**
*\*\name   Option_Bytes_Lock
*\*\fun    Locks the Option_Bytes Program Erase Controller.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return none
**/
void Option_Bytes_Lock(void)
{
    /* Set the FLASH_CTRL_SET_OPTWE Bit to lock */
    FLASH->CTRL &= (~FLASH_CTRL_SET_OPTWE);
}


/**
*\*\name   Option_Bytes_Lock_Status_Get
*\*\fun    Get the Option_Bytes status.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return FlagStatus :
*\*\            - SET
*\*\            - RESET
**/
FlagStatus Option_Bytes_Lock_Status_Get(void)
{
    if ((FLASH->CTRL & FLASH_CTRL_SET_OPTWE) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}


/**
*\*\name   FLASH_One_Page_Erase
*\*\fun    Erases a specified FLASH page.
*\*\note   This function can be used for N32G430 devices.
*\*\param  page_address :
*\*\            - It ranges from 0x08000000 to 0x0800FFFF
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY
*\*\            - FLASH_ERR_PG 
*\*\            - FLASH_ERR_WRP
*\*\            - FLASH_EOP
*\*\            - FLASH_TIMEOUT
**/
FLASH_STS FLASH_One_Page_Erase(uint32_t page_address)
{
    FLASH_STS status_value = FLASH_EOP;

   /* Clears the FLASH's pending flags */
    FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

    if (status_value == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CTRL |= FLASH_CTRL_SET_PER;
        FLASH->ADD = page_address;
        FLASH->CTRL |= FLASH_CTRL_SET_START;

        /* Wait for last operation to be completed */
        status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

        /* Disable the PER Bit */
        FLASH->CTRL &= FLASH_CTRL_RESET_PER;
    }
    else
    {
        /*No process*/
    }

    /* Return the Erase status_value */
    return status_value;
}

/**
*\*\name   FLASH_Mass_Erase
*\*\fun    Erases all FLASH pages.
*\*\note   This function can be used for all N32G430 devices.
*\*\param  none
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY
*\*\            - FLASH_ERR_PG 
*\*\            - FLASH_ERR_WRP
*\*\            - FLASH_EOP
*\*\            - FLASH_TIMEOUT
**/
FLASH_STS FLASH_Mass_Erase(void)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Clears the FLASH's pending flags */
    FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

    if (status_value == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to erase all pages */
        FLASH->CTRL |= FLASH_CTRL_SET_MER;
        FLASH->CTRL |= FLASH_CTRL_SET_START;

        /* Wait for last operation to be completed */
        status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

        /* Disable the MER Bit */
        FLASH->CTRL &= FLASH_CTRL_RESET_MER;
    }
    else
    {
        /*No process*/
    }

    /* Return the Erase status_value */
    return status_value;
}

/**
*\*\name   FLASH_Word_Program
*\*\fun    Programs a word at a specified address.
*\*\note   This function can be used for N32G430 devices.
*\*\param  address :
*\*\            - It ranges from 0x08000000 to 0x0800FFFF
*\*\param  data :
*\*\            - It ranges from 0x00000000 to 0xFFFFFFFF
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY
*\*\            - FLASH_ERR_PG
*\*\            - FLASH_ERR_WRP
*\*\            - FLASH_EOP
*\*\            - FLASH_ERR_ADD
*\*\            - FLASH_TIMEOUT
**/
FLASH_STS FLASH_Word_Program(uint32_t address, uint32_t data)
{
    FLASH_STS status_value  = FLASH_EOP;

    if((address & FLASH_WORD_LENGTH) != RESET)
    {
        /* The programming address is not a multiple of 4 */
        return FLASH_ERR_ADD;
    }
    else
    {
        /*No process*/
    }

    /* Clears the FLASH's pending flags */
    FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_Last_Operation_Wait(PROGRAM_TIMEOUT);

    if (status_value == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to program the new word */
        FLASH->CTRL |= FLASH_CTRL_SET_PG;

        *(__IO uint32_t*)address = (uint32_t)data;
        /* Wait for last operation to be completed */
        status_value = FLASH_Last_Operation_Wait(PROGRAM_TIMEOUT);

        /* Disable the PG Bit */
        FLASH->CTRL &= FLASH_CTRL_RESET_PG;
    }
    else
    {
        /*No process*/
    }

    /* Return the Program status_value */
    return status_value;
}


/**
*\*\name   FLASH_Option_Bytes_Erase
*\*\fun    Erases the FLASH option bytes.
*\*\note   This functions erases all option bytes except the Read protection (RDP).
*\*\       This function can be used for N32G430 devices.
*\*\param  none
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY
*\*\            - FLASH_ERR_PG 
*\*\            - FLASH_ERR_WRP
*\*\            - FLASH_EOP
*\*\            - FLASH_ERR_RDP2
*\*\            - FLASH_ERR_ADD
*\*\            - FLASH_TIMEOUT
**/
FLASH_STS FLASH_Option_Bytes_Erase(void)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_Read_Out_Protection_L2_Status_Get() != RESET)
    {
        return FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    /* Clears the FLASH's pending flags */
    FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

    if (status_value == FLASH_EOP)
    {
        Option_Bytes_Unlock();

        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CTRL |= FLASH_CTRL_SET_OPTER;
        FLASH->CTRL |= FLASH_CTRL_SET_START;
        /* Wait for last operation to be completed */
        status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

        if (status_value == FLASH_EOP)
        {
            /* Clears the FLASH's pending flags */
            FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= FLASH_CTRL_RESET_OPTER;
        }
        else
        {
            if (status_value != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= FLASH_CTRL_RESET_OPTER;
            }
            else
            {
                /*No process*/
            }
        }
    }
    else
    {
        /*No process*/
    }
    /* Return the erase status_value */
    return status_value;
}


/**
*\*\name   FLASH_Option_Bytes_User_RDP1_Program
*\*\fun    Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY / 
*\*\       IWDG_STOP0_FRZ / IWDG_STOP2_FRZ / IWDG_STDBY_FRZ / IWDG_SLEEP_FRZ / RDP1.
*\*\note   This function can be used for N32G430 devices.
*\*\param  option_byte_rpd1 :
*\*\        - FLASH_OB_RDP1_ENABLE
*\*\        - FLASH_OB_RDP1_DISABLE
*\*\param  option_byte_iwdg :
*\*\        - FLASH_OB_IWDG_SW Software IWDG selected
*\*\        - FLASH_OB_IWDG_HW Hardware IWDG selected
*\*\param  option_byte_stop :
*\*\        - FLASH_OB_STOP_NORST No reset generated when entering in STOP
*\*\        - FLASH_OB_STOP_RST Reset generated when entering in STOP
*\*\param  option_byte_stdby :
*\*\        - FLASH_OB_STDBY_NORST No reset generated when entering in STANDBY
*\*\        - FLASH_OB_STDBY_RST Reset generated when entering in STANDBY
*\*\param  option_byte_iwdg_stop0 :
*\*\        - FLASH_OB_IWDG_STOP0_FRZ IWDG freeze in stop0
*\*\        - FLASH_OB_IWDG_STOP0_NOFRZ Default no freeze
*\*\param  option_byte_iwdg_stop2 :
*\*\        - FLASH_OB_IWDG_STOP2_FRZ IWDG freeze in stop2
*\*\        - FLASH_OB_IWDG_STOP2_NOFRZ Default no freeze
*\*\param  option_byte_iwdg_stdby :
*\*\        - FLASH_OB_IWDG_STDBY_FRZ IWDG freeze in standby
*\*\        - FLASH_OB_IWDG_STDBY_NOFRZ Default no freeze
*\*\param  option_byte_iwdg_sleep :
*\*\        - FLASH_OB_IWDG_SLEEP_FRZ IWDG freeze in sleep
*\*\        - FLASH_OB_IWDG_SLEEP_NOFRZ Default no freeze
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY
*\*\        - FLASH_ERR_PG 
*\*\        - FLASH_ERR_WRP
*\*\        - FLASH_EOP
*\*\        - FLASH_ERR_RDP2
*\*\        - FLASH_TIMEOUT
**/
FLASH_STS FLASH_Option_Bytes_User_RDP1_Program(uint8_t option_byte_rpd1, uint16_t option_byte_iwdg, \
                                               uint16_t option_byte_stop, uint16_t option_byte_stdby, \
                                               uint16_t option_byte_iwdg_stop0, uint16_t option_byte_iwdg_stop2, \
                                               uint16_t option_byte_iwdg_stdby, uint16_t option_byte_iwdg_sleep)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_Read_Out_Protection_L2_Status_Get() != RESET)
    {
        return FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    Option_Bytes_Unlock();

    /* Clears the FLASH's pending flags */
    FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= FLASH_CTRL_SET_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER_RDP =
            (uint32_t)option_byte_rpd1
            | (((uint32_t)(option_byte_iwdg | option_byte_stop | option_byte_stdby | option_byte_iwdg_stop0 
            | option_byte_iwdg_stop2 | option_byte_iwdg_stdby | option_byte_iwdg_sleep)) << FLASH_USER_RPD_OFFSET);
        
        /* Wait for last operation to be completed */
        status_value = FLASH_Last_Operation_Wait(PROGRAM_TIMEOUT);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= FLASH_CTRL_RESET_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}


/**
*\*\name   FLASH_Option_Bytes_DATA_Program
*\*\fun    Programs a half word at a specified Option Byte Data address.
*\*\note   This function can be used for N32G430 devices.
*\*\param  option_byte_data0:
*\*\                - 0x00 to 0xFF
*\*\param  option_byte_data1:
*\*\                - 0x00 to 0xFF
*\*\return FLASH_STS: The returned value can be: 
*\*\                - FLASH_BUSY
*\*\            - FLASH_ERR_PG
*\*\            - FLASH_ERR_WRP
*\*\            - FLASH_EOP
*\*\            - FLASH_ERR_RDP2
*\*\            - FLASH_TIMEOUT
**/
FLASH_STS FLASH_Option_Bytes_DATA_Program(uint8_t option_byte_data0,uint8_t option_byte_data1)
{
    FLASH_STS status_value = FLASH_EOP;
 
    /* Clears the FLASH's pending flags */
    FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_Last_Operation_Wait(PROGRAM_TIMEOUT);

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_Read_Out_Protection_L2_Status_Get() != RESET)
    {
        return FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    if (status_value == FLASH_EOP)
    {
        Option_Bytes_Unlock();
        /* Enables the Option Bytes Programming operation */
        FLASH->CTRL |= FLASH_CTRL_SET_OPTPG;
        OBT->Data1_Data0 = (((uint32_t)option_byte_data0) << FLASH_DATA0_DATA1_OFFSET) \
                          | ((uint32_t)option_byte_data1);

        /* Wait for last operation to be completed */
        status_value = FLASH_Last_Operation_Wait(PROGRAM_TIMEOUT);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= FLASH_CTRL_RESET_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }
    /* Return the Option Byte Data Program status_value */
    return status_value;
}

/**
*\*\name   FLASH_Write_Protection_Enable
*\*\fun    Write protects the desired pages
*\*\note   This function can be used for N32G430 devices.
*\*\param  flash_pages :
*\*\        - FLASH_WRP_Pages0to1
*\*\        - FLASH_WRP_Pages2to3
*\*\        - FLASH_WRP_Pages4to5
*\*\        - FLASH_WRP_Pages6to7
*\*\        - FLASH_WRP_Pages8to9
*\*\        - FLASH_WRP_Pages10to11
*\*\        - FLASH_WRP_Pages12to13
*\*\        - FLASH_WRP_Pages14to15
*\*\        - FLASH_WRP_Pages16to17
*\*\        - FLASH_WRP_Pages18to19
*\*\        - FLASH_WRP_Pages20to21
*\*\        - FLASH_WRP_Pages22to23
*\*\        - FLASH_WRP_Pages24to25
*\*\        - FLASH_WRP_Pages26to27
*\*\        - FLASH_WRP_Pages28to29
*\*\        - FLASH_WRP_Pages30to31
*\*\        - FLASH_WRP_AllPages
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY
*\*\        - FLASH_ERR_PG 
*\*\        - FLASH_ERR_WRP
*\*\        - FLASH_EOP
*\*\        - FLASH_ERR_RDP2
*\*\        - FLASH_TIMEOUT
**/
FLASH_STS FLASH_Write_Protection_Enable(uint32_t flash_pages)
{
    uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF;

    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_Read_Out_Protection_L2_Status_Get() != RESET)
    {
        return FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    flash_pages = (uint32_t)(~flash_pages);
    WRP0_Data   = (uint16_t)( flash_pages & FLASH_WRP0_MSK);
    WRP1_Data   = (uint16_t)((flash_pages & FLASH_WRP1_MSK) >> FLASH_WRP_WRP1_OFFSET);

    /* Clears the FLASH's pending flags */
    FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_Last_Operation_Wait(PROGRAM_TIMEOUT);

    if (status_value == FLASH_EOP)
    {
        Option_Bytes_Unlock();
        FLASH->CTRL |= FLASH_CTRL_SET_OPTPG;

        if ((WRP0_Data != 0xFF) || (WRP1_Data != 0xFF))
        {
            OBT->WRP1_WRP0 = (((uint32_t)WRP0_Data) | (((uint32_t)WRP1_Data) << FLASH_WRP1_DATA_OFFSET));

            /* Wait for last operation to be completed */
            status_value = FLASH_Last_Operation_Wait(PROGRAM_TIMEOUT);
        }
        else
        {
            /*No process*/
        }

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= FLASH_CTRL_RESET_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }
    /* Return the write protection operation status_value */
    return status_value;
}


/**
*\*\name    FLASH_Option_Bytes_User2_RDP2_Program
*\*\fun     Programs the FLASH User2_RDP2 Option Byte: nBOOT0 / nBOOT1 / nSWBOOT0 / RDP2 .
*\*\note    This function can be used for N32G430 devices.
*\*\param  option_byte_rpd2 :
*\*\            - FLASH_OB_RDP2_ENABLE
*\*\            - FLASH_OB_RDP2_DISABLE
*\*\param   option_byte2_nBOOT0 :
*\*\            - FLASH_OB2_NBOOT0_SET Set nBOOT0
*\*\            - FLASH_OB2_NBOOT0_CLR Clear nBOOT0
*\*\param   option_byte2_nBOOT1 :
*\*\            - FLASH_OB2_NBOOT1_SET Set nBOOT1
*\*\            - FLASH_OB2_NBOOT1_CLR Clear nBOOT1
*\*\param   option_byte2_nSWBOOT0 :
*\*\            - FLASH_OB2_NSWBOOT0_SET Set nSWBOOT0
*\*\            - FLASH_OB2_NSWBOOT0_CLR Clear nSWBOOT0
*\*\return  FLASH_STS : 
*\*\            - FLASH_BUSY
*\*\            - FLASH_ERR_PG 
*\*\            - FLASH_ERR_WRP
*\*\            - FLASH_EOP
*\*\            - FLASH_ERR_RDP2
*\*\            - FLASH_TIMEOUT
**/
FLASH_STS FLASH_Option_Bytes_User2_RDP2_Program(uint8_t option_byte_rpd2,uint8_t option_byte2_nBOOT0, \
                                                uint8_t option_byte2_nBOOT1, uint8_t option_byte2_nSWBOOT0)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_Read_Out_Protection_L2_Status_Get() != RESET)
    {
        return FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    Option_Bytes_Unlock();

    /* Clears the FLASH's pending flags */
    FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

    if (status_value == FLASH_EOP)
    {
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= FLASH_CTRL_SET_OPTPG;
        /* Restore the last read protection Option Byte value */
        OBT->USER2_RDP2 = (((uint32_t)option_byte_rpd2) | \
        (((uint32_t)(option_byte2_nBOOT0 | option_byte2_nBOOT1 | option_byte2_nSWBOOT0)) << FLASH_OB2_USER2_OFFSET));
        
        /* Wait for last operation to be completed */
        status_value = FLASH_Last_Operation_Wait(PROGRAM_TIMEOUT);
        if (status_value != FLASH_TIMEOUT)
        {
            /* If the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= FLASH_CTRL_RESET_OPTPG;
        }
        else
        {
            /*No process*/
        }
    }
    else
    {
        /*No process*/
    }

    /* Return the Option Byte program status_value */
    return status_value;
}

/**
*\*\name   FLASH_Read_Out_Protection_L1_Enable
*\*\fun    Enables the read out protection.
*\*\note   If the user has already programmed the other option bytes before calling
*\*\       this function, he must re-program them since this function erases all option bytes.
*\*\       This function can be used for N32G430 devices.
*\*\param  none
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY
*\*\        - FLASH_ERR_PG
*\*\        - FLASH_ERR_WRP
*\*\        - FLASH_EOP
*\*\        - FLASH_ERR_RDP2
*\*\        - FLASH_TIMEOUT
**/
FLASH_STS FLASH_Read_Out_Protection_L1_Enable(void)
{
    uint32_t user_temp;
    FLASH_STS status_value = FLASH_EOP;

    user_temp = ((FLASH_OB_USER_MSK & FLASH->OB) << FLASH_OB_TO_USER_OFFSET);

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_Read_Out_Protection_L2_Status_Get() != RESET)
    {
        return FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    /* Clears the FLASH's pending flags */
    FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

    if (status_value == FLASH_EOP)
    {
        Option_Bytes_Unlock();
        FLASH->CTRL |= FLASH_CTRL_SET_OPTER;
        FLASH->CTRL |= FLASH_CTRL_SET_START;
        /* Wait for last operation to be completed */
        status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);
        if (status_value == FLASH_EOP)
        {
            /* Clears the FLASH's pending flags */
            FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= FLASH_CTRL_RESET_OPTER;
            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= FLASH_CTRL_SET_OPTPG;
            /*enable new state of the ReadOut Protection*/
            OBT->USER_RDP = (FLASH_USER_MASK & user_temp);
            /* Wait for last operation to be completed */
            status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

            if (status_value != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= FLASH_CTRL_RESET_OPTPG;
            }
            else
            {
                /*No process*/
            }
        }
        else
        {
            if (status_value != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= FLASH_CTRL_RESET_OPTER;
            }
            else
            {
                /*No process*/
            }
        }
    }
    else
    {
        /*No process*/
    }
    /* Return the protection operation status_value */
    return status_value;
}


/**
*\*\name   FLASH_Read_Out_Protection_L1_Disable
*\*\fun    Disables the read out protection.
*\*\note   If the user has already programmed the other option bytes before calling
*\*\       this function, he must re-program them since this function erases all option bytes.
*\*\       This function can be used for N32G430 devices.
*\*\param  none
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY
*\*\        - FLASH_ERR_PG
*\*\        - FLASH_ERR_WRP
*\*\        - FLASH_EOP
*\*\        - FLASH_ERR_RDP2
*\*\        - FLASH_TIMEOUT
**/
FLASH_STS FLASH_Read_Out_Protection_L1_Disable(void)
{
    uint32_t user_temp;
    FLASH_STS status_value = FLASH_EOP;

    user_temp = ((FLASH_OB_USER_MSK & FLASH->OB) << FLASH_OB_TO_USER_OFFSET);

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_Read_Out_Protection_L2_Status_Get() != RESET)
    {
        return FLASH_ERR_RDP2;        
    }
    else
    {
        /*No process*/
    }

    /* Clears the FLASH's pending flags */
    FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

    if (status_value == FLASH_EOP)
    {
        Option_Bytes_Unlock();
        FLASH->CTRL |= FLASH_CTRL_SET_OPTER;
        FLASH->CTRL |= FLASH_CTRL_SET_START;
        /* Wait for last operation to be completed */
        status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);
        if (status_value == FLASH_EOP)
        {
            /* Clears the FLASH's pending flags */
            FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= FLASH_CTRL_RESET_OPTER;
            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= FLASH_CTRL_SET_OPTPG;
            /* Disables the read out protection */
            OBT->USER_RDP = ((FLASH_L1_RDP_KEY & FLASH_RDP1_MASK) | user_temp);
            /* Wait for last operation to be completed */
            status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

            if (status_value != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= FLASH_CTRL_RESET_OPTPG;
            }
            else
            {
                /*No process*/
            }
        }
        else
        {
            if (status_value != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= FLASH_CTRL_RESET_OPTER;
            }
            else
            {
                /*No process*/
            }
        }
    }
    else
    {
        /*No process*/
    }
    /* Return the protection operation status_value */
    return status_value;
}

/**
*\*\name   FLASH_Read_Out_Protection_L2_Enable
*\*\fun    Enables or disables the read out protection L2.
*\*\note   If the user has already programmed the other option bytes before calling
*\*\       this function, he must re-program them since this function erases all option bytes.
*\*\       This function can be used for N32G430 devices.
*\*\param  none
*\*\return FLASH_STS : 
*\*\        - FLASH_BUSY
*\*\        - FLASH_ERR_PG 
*\*\        - FLASH_ERR_PV 
*\*\        - FLASH_ERR_WRP
*\*\        - FLASH_EOP
*\*\        - FLASH_ERR_EV
*\*\        - FLASH_ERR_RDP2
*\*\        - FLASH_TIMEOUT
**/
FLASH_STS FLASH_Read_Out_Protection_L2_Enable(void)
{
    uint32_t user_temp;
    FLASH_STS status_value = FLASH_EOP;

    user_temp = ((FLASH_OB_USER_MSK & FLASH->OB) << FLASH_OB_TO_USER_OFFSET);
  
    /* Get the actual read protection L1 Option Byte value */
    if (FLASH_Read_Out_Protection_Status_Get() == RESET)
    {
        user_temp |= (FLASH_L1_RDP_KEY & FLASH_RDP1_MASK);
    }
    else
    {
        /*No process*/
    }
    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_Read_Out_Protection_L2_Status_Get() != RESET)
    {
        return FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    /* Clears the FLASH's pending flags */
    FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

    if (status_value == FLASH_EOP)
    {
        Option_Bytes_Unlock();
        FLASH->CTRL |= FLASH_CTRL_SET_OPTER;
        FLASH->CTRL |= FLASH_CTRL_SET_START;
        /* Wait for last operation to be completed */
        status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);
        if (status_value == FLASH_EOP)
        {
            /* Clears the FLASH's pending flags */
            FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG); 

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= FLASH_CTRL_RESET_OPTER;
            /* Enable the Option Bytes Programming operation */
            FLASH->CTRL |= FLASH_CTRL_SET_OPTPG;

            OBT->USER_RDP = user_temp;
            /* Wait for last operation to be completed */
            status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);

            if (status_value == FLASH_EOP)
            {
                /* Clears the FLASH's pending flags */
                FLASH_Flag_Status_Clear(FLASH_STS_CLRFLAG);

                /* Enables the read out protection L2 */
                OBT->USER2_RDP2 = FLASH_L2_RDP_KEY;

                /* Wait for last operation to be completed */
                status_value = FLASH_Last_Operation_Wait(ERASE_TIMEOUT);
            }
            else
            {
                /*No process*/
            }

            if (status_value != FLASH_TIMEOUT)
            {
                /* if the program operation is completed, disable the OPTPG Bit */
                FLASH->CTRL &= FLASH_CTRL_RESET_OPTPG;
            }
            else
            {
                /*No process*/
            }
        }
        else
        {
            if (status_value != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= FLASH_CTRL_RESET_OPTER;
            }
            else
            {
                /*No process*/
            }
        }
    }
    else
    {
        /*No process*/
    }
    /* Return the protection operation status_value */
    return status_value;
}

/**
*\*\name   FLASH_Option_Bytes_User_Get
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return The FLASH User Option Bytes values :
*\*\            - Bit0    IWDG_SW
*\*\            - Bit1    RST_STOP
*\*\            - Bit2    RST_STDBY
*\*\            - Bit3    IWDG_STOP0_FRZ
*\*\            - Bit4    IWDG_STOP2_FRZ
*\*\            - Bit5    IWDG_STDBY_FRZ
*\*\            - Bit6    IWDG_SLEEP_FRZ
**/
uint32_t FLASH_Option_Bytes_User_Get(void)
{
    /* Return the User Option Byte */
    return (uint32_t)(FLASH->OB >> FLASH_OB_OFFSET);
}


/**
*\*\name   FLASH_Option_Bytes2_User_Get
*\*\fun    Returns the FLASH User Option Bytes2 values.
*\*\note   This function can be used for N32G430 devices.
*\*\param  boot_bit :
*\*\            - FLASH_OB2_nBOOT1_MASK
*\*\            - FLASH_OB2_nSWBOOT0_MASK
*\*\            - FLASH_OB2_nBOOT0_MASK
*\*\return FlagStatus :
*\*\            - SET
*\*\            - RESET
**/
FlagStatus FLASH_Option_Bytes2_User_Get(uint32_t boot_bit)
{
    if ((FLASH->OB2 & boot_bit) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name   FLASH_Option_Bytes_Data0_Get
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return data0:
*\*\            - 0x00 to 0xFF.
**/
uint32_t FLASH_Option_Bytes_Data0_Get(void)
{
    /* Return the User Option Byte2 */
    return (uint32_t)((FLASH->OB & FLASH_OB_DATA0_MASK) >> FLASH_OB_DATA0_OFFSET);
}

/**
*\*\name   FLASH_Option_Bytes_Data1_Get
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return data1:
*\*\            - 0x00 to 0xFF.
**/
uint32_t FLASH_Option_Bytes_Data1_Get(void)
{
    /* Return the User Option Byte2 */
    return (uint32_t)((FLASH->OB & FLASH_OB_DATA1_MASK) >> FLASH_OB_DATA1_OFFSET);
}

/**
*\*\name   FLASH_Option_Bytes_Write_Protection_Get
*\*\fun    Returns the FLASH Write Protection Option Bytes Register value.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return The FLASH Write Protection  Option Bytes Register value :
*\*\            - Bit15 - Bit0 write-protects pages (32,31) - page (0,1) 
**/
uint32_t FLASH_Option_Bytes_Write_Protection_Get(void)
{
    /* Return the Flash write protection Register value */
    return (uint32_t)(FLASH->WRP);
}

/**
*\*\name   FLASH_Read_Out_Protection_Status_Get
*\*\fun    Checks whether the FLASH Read Out Protection status_value is set or not.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET
*\*\        - RESET
**/
FlagStatus FLASH_Read_Out_Protection_Status_Get(void)
{
    if ((FLASH->OB & FLASH_RDPRTL1_MSK) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name   FLASH_Read_Out_Protection_L2_Status_Get
*\*\fun    Checks whether the FLASH Read Out Protection L2 status_value is set or not.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET
*\*\        - RESET
**/
FlagStatus FLASH_Read_Out_Protection_L2_Status_Get(void)
{
    if ((FLASH->OB & FLASH_RDPRTL2_MSK) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name   FLASH_Prefetch_Buffer_Status_Get
*\*\fun    Checks whether the FLASH Prefetch Buffer status_value is set or not.
*\*\note   This function can be used for N32G430 devices.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET
*\*\        - RESET
**/
FlagStatus FLASH_Prefetch_Buffer_Status_Get(void)
{
    if ((FLASH->AC & FLASH_PRFTBS_MSK) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name   FLASH_Interrupt_Enable
*\*\fun    Enables the specified FLASH interrupts.
*\*\note   This function can be used for N32G430 devices.
*\*\param  flash_interrupts :
*\*\        - FLASH_INT_ERROR    FLASH Error Interrupt
*\*\        - FLASH_INT_EOP      FLASH end of operation Interrupt
*\*\return none
**/
void FLASH_Interrupt_Enable(uint32_t flash_interrupts)
{
    /* Enable the interrupt sources */
    FLASH->CTRL |= flash_interrupts;
}

/**
*\*\name   FLASH_Interrupt_Disable
*\*\fun    Disables the specified FLASH interrupts.
*\*\note   This function can be used for N32G430 devices.
*\*\param  flash_interrupts :
*\*\        - FLASH_INT_ERROR    FLASH Error Interrupt
*\*\        - FLASH_INT_EOP      FLASH end of operation Interrupt
*\*\return none
**/
void FLASH_Interrupt_Disable(uint32_t flash_interrupts)
{
    /* Disable the interrupt sources */
    FLASH->CTRL &= ~(uint32_t)flash_interrupts;
}

/**
*\*\name   FLASH_Flag_Status_Get
*\*\fun    Checks whether the specified FLASH flag is set or not.
*\*\note   This function can be used for N32G430 devices.
*\*\param  flash_flag :
*\*\        - FLASH_FLAG_BUSY      FLASH Busy flag
*\*\        - FLASH_FLAG_PGERR     FLASH Program error flag
*\*\        - FLASH_FLAG_WRPERR    FLASH Write protected error flag
*\*\        - FLASH_FLAG_EOP       FLASH End of Operation flag
*\*\return FlagStatus :
*\*\        - SET
*\*\        - RESET
**/
FlagStatus FLASH_Flag_Status_Get(uint32_t flash_flag)
{
    if ((FLASH->STS & flash_flag) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name   FLASH_Option_Bytes_Flag_Get
*\*\fun    Checks whether the specified FLASH flag is set or not.
*\*\note   This function can be used for N32G430 devices.
*\*\param  flash_flag :
*\*\        - FLASH_FLAG_OBERR FLASH Option Byte error flag
*\*\return FlagStatus :
*\*\        - SET
*\*\        - RESET
**/
FlagStatus FLASH_Option_Bytes_Flag_Get(uint32_t flash_flag)
{
    if ((FLASH->OB & flash_flag) != (uint32_t)RESET)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/**
*\*\name   FLASH_Flag_Status_Clear
*\*\fun    Clears the FLASH's status flags.
*\*\note   This function can be used for N32G430 devices.
*\*\param  flash_flag :
*\*\        - FLASH_FLAG_PGERR     FLASH Program error flag
*\*\        - FLASH_FLAG_WRPERR    FLASH Write protected error flag
*\*\        - FLASH_FLAG_EOP       FLASH End of Operation flag
*\*\return none
**/
void FLASH_Flag_Status_Clear(uint32_t flash_flag)
{
    /* Clear the flags */
    FLASH->STS |= flash_flag;
}

/**
*\*\name   FLASH_Status_Get
*\*\fun    Returns the FLASH_STS.
*\*\note   This function can be used for N32G430 devices, it is equivalent
*\*\       to FLASH_GetBank1Status function.
*\*\param  none
*\*\return FLASH_STS :
*\*\        - FLASH_BUSY
*\*\        - FLASH_ERR_PG 
*\*\        - FLASH_ERR_WRP
*\*\        - FLASH_EOP
**/
FLASH_STS FLASH_Status_Get(void)
{
    FLASH_STS status_value = FLASH_EOP;

    if ((FLASH->STS & FLASH_FLAG_BUSY) == FLASH_FLAG_BUSY)
    {
        status_value = FLASH_BUSY;
    }
    else
    {
        if ((FLASH->STS & FLASH_FLAG_PGERR) != RESET)
        {
            status_value = FLASH_ERR_PG;
        }
        else
        {
            if ((FLASH->STS & FLASH_FLAG_WRPERR) != RESET)
            {
                status_value = FLASH_ERR_WRP;
            }
            else
            {
                status_value = FLASH_EOP;
            }
        }
    }

    /* Return the FLASH_STS */
    return status_value;
}

/**
*\*\name   FLASH_Last_Operation_Wait
*\*\fun    Waits for a Flash operation to complete or a timeout to occur.
*\*\note   This function can be used for N32G430 devices,
*\*\       it is equivalent to FLASH_WaitForLastBank1Operation..
*\*\param  timeout :
*\*\            - ERASE_TIMEOUT
*\*\            - PROGRAM_TIMEOUT
*\*\return FLASH_STS: The returned value can be: 
*\*\            - FLASH_BUSY
*\*\            - FLASH_ERR_PG 
*\*\            - FLASH_ERR_PV 
*\*\            - FLASH_ERR_WRP
*\*\            - FLASH_EOP
*\*\            - FLASH_ERR_EV
*\*\            - FLASH_TIMEOUT
**/
FLASH_STS FLASH_Last_Operation_Wait(uint32_t timeout)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Check for the Flash status_value */
    status_value = FLASH_Status_Get();
    /* Wait for a Flash operation to complete or a timeout to occur */
    while ((status_value == FLASH_BUSY) && (timeout != 0x00))
    {
        status_value = FLASH_Status_Get();
        timeout--;
    }
    if (timeout == 0x00)
    {
        status_value = FLASH_TIMEOUT;
    }
    /* Return the operation status_value */
    return status_value;
}


