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
*\*\file n32g430_gpio.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#include "n32g430_gpio.h"


/**
 *\*\name   GPIO_Reset.
 *\*\fun    Reset the GPIOx peripheral registers to their default reset values.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\return none
 */
void GPIO_Reset(GPIO_Module* GPIOx)
{
    if (GPIOx == GPIOA)
    {
        RCC_AHB_Peripheral_Reset(RCC_AHB_PERIPH_GPIOA);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_AHB_Peripheral_Reset(RCC_AHB_PERIPH_GPIOB);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_AHB_Peripheral_Reset(RCC_AHB_PERIPH_GPIOC);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_AHB_Peripheral_Reset(RCC_AHB_PERIPH_GPIOD);
    }
    else
    {
        return;
    }
}


/**
 *\*\name   GPIOA_Pin_Reset.
 *\*\fun    Reset the GPIOA peripheral registers to it's default reset values.
 *\*\param  pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\          - GPIO_PIN_ALL
 *\*\return none
 */
void GPIOA_Pin_Reset(uint16_t pin)
{
    uint32_t position = 0x00U;
    uint32_t current_pin = 0x00U;

    while((pin >> position) != 0)
    {
        /* Get the IO position */
        current_pin = (pin) & (IO_POSITION_MASK << position);

        if(current_pin)
        {
            if(position > GPIOA_MODE_POSITION)
            {
                /* Configure IO Direction in alternate Mode */
                GPIOA->PMODE |= (GPIO_AF_MODE << (position * MULTIPLIER_FACTOR_2));
            }
            else
            {
                /* Configure IO Direction in analog Mode */
                GPIOA->PMODE |= (GPIO_ANALOG_MODE << (position * MULTIPLIER_FACTOR_2));
            }

            /* Configure the default Alternate Function in current IO */
            if(position & AF_SELECTION_MASK)
            {
                GPIOA->AFH &= ~(GPIO_AF_MASK << ((position & (uint32_t)AF_WRITE_POSITION_MASK) * MULTIPLIER_FACTOR_4));
            }
            else
            {
                GPIOA->AFL &= ~(GPIO_AF_MASK << ((position & (uint32_t)AF_WRITE_POSITION_MASK) * MULTIPLIER_FACTOR_4));
            }

            /* Reset GPIO output type to push-pull output */
            GPIOA->POTYPE &= ~(GPIO_POTYPE_MASK << position);

            
            if(position == GPIOA_PUPD_POSITION1 || position == GPIOA_PUPD_POSITION2)
            {
                /* Reset the GPIO pull mode to pull-up */
                GPIOA->PUPD |= (GPIO_PU_MODE << (position * MULTIPLIER_FACTOR_2));  
            }
            else if(position == GPIOA_PUPD_POSITION3)
            {
                /* Reset the GPIO pull mode to pull-down */
                GPIOA->PUPD |= (GPIO_PD_MODE << (position * MULTIPLIER_FACTOR_2));  
            }
            else
            {
                /* Reset the GPIO pull mode to no-pull */
                GPIOA->PUPD &= ~(GPIO_PUPD_MASK << (position * MULTIPLIER_FACTOR_2));  
            }

            /* Reset the GPIO slew rate to slow */
            GPIOA->SR |= (GPIO_SR_SLOW << position);  

            /* Reset the GPIO driver strength to 8 mA */
            GPIOA->DS |= (GPIO_DRIVER_8MA << (position * MULTIPLIER_FACTOR_2));  
        }
        position++;
    }
}

/**
 *\*\name   GPIOB_Pin_Reset.
 *\*\fun    Reset the GPIOB peripheral registers to it's default reset values.
 *\*\param  pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\          - GPIO_PIN_ALL
 *\*\return none
 */
void GPIOB_Pin_Reset(uint16_t pin)
{
    uint32_t position = 0x00U;
    uint32_t current_pin = 0x00U;

    while((pin >> position) != 0)
    {
        /* Get the IO position */
        current_pin = (pin) & (IO_POSITION_MASK << position);

        if(current_pin)
        {
            /** Reset GPIO pin mode **/
            if((position == GPIOB_MODE_POSITION1) || (position == GPIOB_MODE_POSITION2))
            {
                /* Configure IO Direction in alternate Mode */
                GPIOB->PMODE |= (GPIO_AF_MODE << (position * MULTIPLIER_FACTOR_2));
            }
            else
            {
                /* Configure IO Direction in analog Mode */
                GPIOB->PMODE |= (GPIO_ANALOG_MODE << (position * MULTIPLIER_FACTOR_2));
            }

            /** Configure the default Alternate Function in current IO **/
            if(position & AF_SELECTION_MASK)
            {
                GPIOB->AFH &= ~(GPIO_AF_MASK << ((position & (uint32_t)AF_WRITE_POSITION_MASK) * MULTIPLIER_FACTOR_4));
            }
            else
            {
                GPIOB->AFL &= ~(GPIO_AF_MASK << ((position & (uint32_t)AF_WRITE_POSITION_MASK) * MULTIPLIER_FACTOR_4));
            }
            
            /* Reset GPIO output type to push-pull output */
            GPIOB->POTYPE &= ~(GPIO_POTYPE_MASK << position);

            if(position == GPIOB_PUPD_POSITION1)
            {
                /* Reset the GPIO pull mode to pull-up */
                GPIOB->PUPD |= (GPIO_PU_MODE << (position * MULTIPLIER_FACTOR_2));  
            }
            else
            {
                /* Reset the GPIO pull mode to no-pull */
                GPIOB->PUPD &= ~(GPIO_PUPD_MASK << (position * MULTIPLIER_FACTOR_2));  
            }

            /* Reset the GPIO slew rate to slow */
            GPIOB->SR |= (GPIO_SR_SLOW << position);  

            /* Reset the GPIO driver strength to 8 mA */
            GPIOB->DS |= (GPIO_DRIVER_8MA << (position * MULTIPLIER_FACTOR_2));  
        }
        position++;
    }
}

/**
 *\*\name   GPIOC_Pin_Reset.
 *\*\fun    Reset the GPIOC peripheral registers to it's default reset values.
 *\*\param  pin :
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\          - GPIO_PIN_ALL
 *\*\return none
 */
void GPIOC_Pin_Reset(uint16_t pin)
{
    uint32_t position = 0x00U;
    uint32_t current_pin = 0x00U;

    while((pin >> position) != 0)
    {
        /* Get the IO position */
        current_pin = (pin) & (IO_POSITION_MASK << position);

        if(current_pin)
        {
            /* Configure IO Direction in analog Mode */
            GPIOC->PMODE |= (GPIO_ANALOG_MODE << (position * MULTIPLIER_FACTOR_2));

            /* Configure the default Alternate Function in current IO */
            GPIOC->AFH &= ~(GPIO_AF_MASK << ((position & (uint32_t)AF_WRITE_POSITION_MASK) * MULTIPLIER_FACTOR_4));

            /* Reset GPIO output type to push-pull output */
            GPIOC->POTYPE &= ~(GPIO_POTYPE_MASK << position);

            /* Reset the GPIO pull mode to no-pull */
            GPIOC->PUPD &= ~(GPIO_PUPD_MASK << (position * MULTIPLIER_FACTOR_2));  

            /* Reset the GPIO slew rate to slow */
            GPIOC->SR |= (GPIO_SR_SLOW << position);  

            /* Reset the GPIO driver strength to 8 mA */
            GPIOC->DS |= (GPIO_DRIVER_8MA << (position * MULTIPLIER_FACTOR_2));  
        }
        position++;
    }
}


/**
 *\*\name   GPIOD_Pin_Reset.
 *\*\fun    Reset the GPIOD peripheral registers to it's default reset values.
 *\*\param  pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\          - GPIO_PIN_ALL
 *\*\return none
 */
void GPIOD_Pin_Reset(uint16_t pin)
{
    uint32_t position = 0x00U;
    uint32_t current_pin = 0x00U;

    while((pin >> position) != 0)
    {
        /* Get the IO position */
        current_pin = (pin) & (IO_POSITION_MASK << position);

        if(current_pin)
        {
            if(position == GPIOD_MODE_POSITION)
            {
                /* Configure IO Direction in analog Mode */
                GPIOD->PMODE |= (GPIO_INPUT_MODE << (position * MULTIPLIER_FACTOR_2));
            }
            else
            {
                /* Configure IO Direction in analog Mode */
                GPIOD->PMODE |= (GPIO_ANALOG_MODE << (position * MULTIPLIER_FACTOR_2));
            }

            /* Configure the default Alternate Function in current IO */
            if(position & AF_SELECTION_MASK)
            {
                GPIOD->AFH &= ~(GPIO_AF_MASK << ((position & (uint32_t)AF_WRITE_POSITION_MASK) * MULTIPLIER_FACTOR_4));
            }
            else
            {
                GPIOD->AFL &= ~(GPIO_AF_MASK << ((position & (uint32_t)AF_WRITE_POSITION_MASK) * MULTIPLIER_FACTOR_4));
            }

            /* Reset GPIO output type to push-pull output */
            GPIOD->POTYPE &= ~(GPIO_POTYPE_MASK << position);

            if(position == GPIOD_PUPD_POSITION1)
            {
                /* Reset the GPIO pull mode to pull-down */
                GPIOD->PUPD |= (GPIO_PD_MODE << (position * MULTIPLIER_FACTOR_2));  
            }
            else if(position >= GPIOD_PUPD_POSITION2)
            {
                /* Reset the GPIO pull mode to no-pull */
                GPIOD->PUPD &= ~(GPIO_PUPD_MASK << (position * MULTIPLIER_FACTOR_2));  
            }
            
            /* Reset the GPIO slew rate to slow */
            GPIOD->SR |= (GPIO_SR_SLOW << position);  

            /* Reset the GPIO driver strength to 8 mA */
            GPIOD->DS |= (GPIO_DRIVER_8MA << (position * MULTIPLIER_FACTOR_2)); 
        }
        position++;
    } 
}

/**
 *\*\name   AFIO_Mode_Reset.
 *\*\fun    Reset the AFIO mode.
 *\*\param  EXTI_line :
 *\*\          - EXTI_LINE_0   
 *\*\          - EXTI_LINE_1   
 *\*\          - EXTI_LINE_2   
 *\*\          - EXTI_LINE_3   
 *\*\          - EXTI_LINE_4   
 *\*\          - EXTI_LINE_5   
 *\*\          - EXTI_LINE_6   
 *\*\          - EXTI_LINE_7   
 *\*\          - EXTI_LINE_8   
 *\*\          - EXTI_LINE_9   
 *\*\          - EXTI_LINE_10  
 *\*\          - EXTI_LINE_11  
 *\*\          - EXTI_LINE_12  
 *\*\          - EXTI_LINE_13  
 *\*\          - EXTI_LINE_14  
 *\*\          - EXTI_LINE_15  
 *\*\          - EXTI_LINE_ALL 
 *\*\return none
 */
void AFIO_EXTI_Reset(uint16_t EXTI_line)
{
    uint32_t temp_value = 0x00U;
    uint32_t position = 0x00U;
    uint32_t current_line = 0x00U;

    while((EXTI_line >> position) != 0)
    {
        /* Get the IO position */
        current_line = (EXTI_line) & (IO_POSITION_MASK << position);

        if(current_line)
        {
            temp_value = (AFIO_EXTICFG_MASK << ((position & (uint32_t)AFIO_EXTI_POSITION_MASK) * MULTIPLIER_FACTOR_8));
            AFIO->EXTI_CFG[position >> SHIFT_EXTI] &= ~temp_value;
        }
        position++;
    }
}



/**
 *\*\name   GPIO_ALLPin_Reset.
 *\*\fun    Reset the GPIOx peripheral registers to their default reset values.
 *\*\param  none
 *\*\return none
 */
void GPIO_ALLPin_Reset(void) 
{
    /* Reset all pins on the GPIOA peripheral */
    GPIOA_Pin_Reset(GPIO_PIN_ALL);

    /* Reset all pins on the GPIOB peripheral */
    GPIOB_Pin_Reset(GPIO_PIN_ALL);

    /* Reset all pins on the GPIOC peripheral */
    GPIOC_Pin_Reset(GPIO_PIN_ALL);

    /* Reset all pins on the GPIOD peripheral */
    GPIOD_Pin_Reset(GPIO_PIN_ALL);
}


/**
 *\*\name   GPIO_Alternate_Set.
 *\*\fun    Configure GPIO alternate function.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  alternate
 *\*\          - Refer to the "alternate_function" parameter 
 *\*\            list of the GPIO_Pin_Remap_Set() function
 *\*\param  position
 *\*\          - 0x00 ~ 0x0F    0x00 represents GPIO_PIN_0, 
 *\*\                           0x01 represents GPIO_PIN_1
 *\*\                           ...
 *\*\                           0x0F represents GPIO_PIN_15
 *\*\return none
 */
void GPIO_Alternate_Set(GPIO_Module* GPIOx, uint32_t alternate, uint32_t position)
{
    uint32_t temp_value = 0x00U;
    
    /* Configure Alternate function mapped with the current IO */ 
    if(position & AF_SELECTION_MASK)
    {
        temp_value = GPIOx->AFH;
        temp_value &= ~(GPIO_AF_MASK << ((uint32_t)(position & (uint32_t)AF_WRITE_POSITION_MASK) * MULTIPLIER_FACTOR_4));
        temp_value |= ((uint32_t)alternate << ((uint32_t)(position & (uint32_t)AF_WRITE_POSITION_MASK) * MULTIPLIER_FACTOR_4));
        GPIOx->AFH = temp_value;
    }
    else
    {
        temp_value = GPIOx->AFL;
        temp_value &= ~(GPIO_AF_MASK << ((uint32_t)(position & (uint32_t)AF_WRITE_POSITION_MASK) * MULTIPLIER_FACTOR_4));
        temp_value |= ((uint32_t)alternate << ((uint32_t)(position & (uint32_t)AF_WRITE_POSITION_MASK) * MULTIPLIER_FACTOR_4));
        GPIOx->AFL = temp_value;
    }
}


/**
 *\*\name   GPIO_Mode_Set.
 *\*\fun    Configure GPIO mode.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  mode 
 *\*\          - GPIO_MODE_INPUT
 *\*\          - GPIO_MODE_OUT_PP
 *\*\          - GPIO_MODE_OUT_OD
 *\*\          - GPIO_MODE_AF_PP
 *\*\          - GPIO_MODE_AF_OD
 *\*\          - GPIO_MODE_ANALOG
 *\*\param  position
 *\*\          - 0x00 ~ 0x0F    0x00 represents GPIO_PIN_0, 
 *\*\                           0x01 represents GPIO_PIN_1
 *\*\                           ...
 *\*\                           0x0F represents GPIO_PIN_15
 *\*\return none
 */
void GPIO_Mode_Set(GPIO_Module* GPIOx, uint32_t mode, uint32_t position)
{
    uint32_t temp_value = 0x00U;
    uint32_t temp = 0x00U;

    /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
    temp_value = GPIOx->PMODE;
    temp = (mode & GPIO_SET_PMODE_MASK);
    temp_value &= ~(GPIO_PMODE_MASK << (position * MULTIPLIER_FACTOR_2));
    temp_value |= (temp << (position * MULTIPLIER_FACTOR_2));
    GPIOx->PMODE = temp_value;

    /* In case of Output or Alternate function mode selection */
    if((mode == GPIO_MODE_OUT_PP) || (mode == GPIO_MODE_OUT_OD) ||
       (mode == GPIO_MODE_AF_PP) || (mode == GPIO_MODE_AF_OD))
    {
        /* Configure the IO Output Type */
        temp_value = GPIOx->POTYPE;
        temp_value &= ~(GPIO_POTYPE_MASK << position);
        temp_value |= (((mode & GPIO_OUTPUT_TYPE_MASK) >> SHIFT_POTYPE) << position);
        GPIOx->POTYPE = temp_value;
    }
}


/**
 *\*\name   GPIO_Pull_Set.
 *\*\fun    Configure pull mode.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  pull 
 *\*\          - GPIO_NO_PULL
 *\*\          - GPIO_PULL_UP
 *\*\          - GPIO_PULL_DOWN
 *\*\param  position
 *\*\          - 0x00 ~ 0x0F    0x00 represents GPIO_PIN_0, 
 *\*\                           0x01 represents GPIO_PIN_1
 *\*\                           ...
 *\*\                           0x0F represents GPIO_PIN_15
 *\*\return none
 */
void GPIO_Pull_Set(GPIO_Module* GPIOx, uint32_t pull, uint32_t position)
{
    uint32_t temp_value = 0x00U;

    /* Configure pull-down mode */
    temp_value = GPIOx->PUPD;
    temp_value &= ~(GPIO_PUPD_MASK << (position * MULTIPLIER_FACTOR_2));
    temp_value |= (pull << (position * MULTIPLIER_FACTOR_2));
    GPIOx->PUPD = temp_value;
}


/**
 *\*\name   GPIO_SlewRate_Set.
 *\*\fun    GPIO slew rate configuration.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  slew_rate
 *\*\          - GPIO_SLEW_RATE_FAST
 *\*\          - GPIO_SLEW_RATE_SLOW
 *\*\param  position
 *\*\          - 0x00 ~ 0x0F    0x00 represents GPIO_PIN_0, 
 *\*\                           0x01 represents GPIO_PIN_1
 *\*\                           ...
 *\*\                           0x0F represents GPIO_PIN_15
 *\*\return none
 */
void GPIO_SlewRate_Set(GPIO_Module* GPIOx, uint32_t slew_rate, uint32_t position)
{
    uint32_t temp_value = 0x00U;

    /* Configure slew rate */
    temp_value = GPIOx->SR;
    temp_value &= ~(GPIO_SR_MASK << position);
    temp_value |= (slew_rate << position);
    GPIOx->SR = temp_value;
}


/**
 *\*\name   GPIO_Driver_Set.
 *\*\fun    GPIO driver configuration.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  current 
 *\*\          - GPIO_DS_2MA
 *\*\          - GPIO_DS_8MA
 *\*\          - GPIO_DS_4MA
 *\*\          - GPIO_DS_12MA
 *\*\param  position
 *\*\          - 0x00 ~ 0x0F    0x00 represents GPIO_PIN_0, 
 *\*\                           0x01 represents GPIO_PIN_1
 *\*\                           ...
 *\*\                           0x0F represents GPIO_PIN_15
 *\*\return none
 */ 
void GPIO_Driver_Set(GPIO_Module* GPIOx, uint32_t current, uint32_t position)
{
    uint32_t temp_value = 0x00U;
    
    temp_value = GPIOx->DS;
    temp_value &= ~(GPIO_DRIVER_MASK << (position * MULTIPLIER_FACTOR_2));
    temp_value |= (current << (position * MULTIPLIER_FACTOR_2));
    GPIOx->DS = temp_value;
}



/**
 *\*\name   GPIO_Peripheral_Initialization.
 *\*\fun    Initialize the GPIOx peripheral with the value of the GPIO_InitStruct structure.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  GPIO_InitStructure :
 *\*\           pointer to GPIO_InitType structure.
 *\*\return none
 */
void GPIO_Peripheral_Initialize(GPIO_Module* GPIOx, GPIO_InitType* GPIO_InitStructure)
{
    uint32_t position = 0x00U;
    uint32_t current_pin = 0x00U;

    while(((GPIO_InitStructure->Pin) >> position) != 0)
    {
        /* Get the IO position */
        current_pin = (GPIO_InitStructure->Pin) & (IO_POSITION_MASK << position);
        if(current_pin)
        {
            /* Configure GPIO alternate function */
            GPIO_Alternate_Set(GPIOx, GPIO_InitStructure->GPIO_Alternate, position);

            /* Configure GPIO mode */
            GPIO_Mode_Set(GPIOx, GPIO_InitStructure->GPIO_Mode, position);

            /* Configure pull-down or pull-up mode */
            GPIO_Pull_Set(GPIOx, GPIO_InitStructure->GPIO_Pull, position);

            /* Configure slew rate */
            GPIO_SlewRate_Set(GPIOx, GPIO_InitStructure->GPIO_Slew_Rate, position);

            /* Configuration drive capability */
            GPIO_Driver_Set(GPIOx, GPIO_InitStructure->GPIO_Current, position);
        }
        position++;
    }
}


/**
 *\*\name   GPIO_Alternate_Function_Reset.
 *\*\fun    Reset the Alternate Function (remapping, event control, and EXTI configuration) 
 *\*\       registers to their default reset values.
 *\*\param  none
 *\*\return none
 */
void GPIO_Alternate_Function_Reset(void)
{
    RCC_APB2_Peripheral_Reset(RCC_APB2_PERIPH_AFIO);
}


/**
 *\*\name   GPIO_Struct_Initialization.
 *\*\fun    Assign default values to each GPIO_InitStruct member.
 *\*\param  GPIO_InitStructure :
 *\*\           pointer to GPIO_InitType structure.
 *\*\return none
 */
void GPIO_Structure_Initialize(GPIO_InitType* GPIO_InitStruct)
{
    /* Reset GPIO structure member */
    GPIO_InitStruct->Pin            = GPIO_PIN_ALL;
    GPIO_InitStruct->GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStruct->GPIO_Mode      = GPIO_MODE_INPUT;
    GPIO_InitStruct->GPIO_Alternate = GPIO_NO_AF;
    GPIO_InitStruct->GPIO_Pull      = GPIO_NO_PULL;
    GPIO_InitStruct->GPIO_Current   = GPIO_DS_2MA;
}


/**
 *\*\name   GPIO_Input_Pin_Data_Get.
 *\*\fun    Get the pin status on the specified input port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the pin state on the input port.
 */
uint8_t GPIO_Input_Pin_Data_Get(GPIO_Module* GPIOx, uint16_t pin)
{
    if ((GPIOx->PID & pin) != (uint32_t)PIN_RESET)
    {
        return (uint8_t)PIN_SET;
    }
    else
    {
        return (uint8_t)PIN_RESET;
    }
}


/**
 *\*\name   GPIO_Input_Data_Get.
 *\*\fun    Get the input data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\return the data value on the GPIO input port.
 */
uint16_t GPIO_Input_Data_Get(GPIO_Module* GPIOx)
{
    return ((uint16_t)GPIOx->PID);
}


/**
 *\*\name   GPIO_Output_Pin_Data_Get.
 *\*\fun    Get the pin status on the specified output port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the pin state on the output port.
 */
uint8_t GPIO_Output_Pin_Data_Get(GPIO_Module* GPIOx, uint16_t pin)
{
    if ((GPIOx->POD & pin) != (uint32_t)PIN_RESET)
    {
        return (uint8_t)PIN_SET;
    }
    else
    {
        return (uint8_t)PIN_RESET;
    }
}


/**
 *\*\name   GPIO_Output_Data_Get.
 *\*\fun    Get the output data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\return the data value on the GPIO output port.
 */
uint16_t GPIO_Output_Data_Get(GPIO_Module* GPIOx)
{
    return ((uint16_t)GPIOx->POD);
}


/**
 *\*\name   GPIO_Pins_Set.
 *\*\fun    Sets the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_Pins_Set(GPIO_Module* GPIOx, uint16_t pin)
{
    GPIOx->PBSC = pin;
}

/**
 *\*\name   GPIO_Pins_Reset.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_Pins_Reset(GPIO_Module* GPIOx, uint16_t pin)
{
    GPIOx->PBC = pin;
}

/**
 *\*\name   GPIO_PBSC_Pins_Reset.
 *\*\fun    Sets the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_PBSC_Pins_Reset(GPIO_Module* GPIOx, uint16_t pin)
{
    uint32_t Pin = pin;
    GPIOx->PBSC = (Pin << SHIFT_PBSC_HIGH16);
}


/**
 *\*\name   GPIO_PBC_Pins_Reset.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_PBC_Pins_Reset(GPIO_Module* GPIOx, uint16_t pin)
{
    GPIOx->PBC = pin;
}


/**
 *\*\name   GPIO_Write_Data.
 *\*\fun    Write data on the designated GPIO data port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  data_value :
 *\*\          the value to be written to the port output data register.
 *\*\return none
 */
void GPIO_Write(GPIO_Module* GPIOx, uint16_t data_value)
{
    GPIOx->POD = data_value;
}


/**
 *\*\name   GPIO_Pin_Toggle.
 *\*\fun    Toggle the specified port pin level.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_Pin_Toggle(GPIO_Module* GPIOx, uint16_t pin)
{
    GPIOx->POD ^= pin;
}


/**
 *\*\name   GPIO_Pin_Lock_Set.
 *\*\fun    GPIO port lock register configuration.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\param  pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_Pin_Lock_Set(GPIO_Module* GPIOx, uint16_t pin)
{
    uint32_t temp_value = 0x00U;
	
	temp_value = (GPIO_PLOCKK_MASK | pin);

    /* PLOCKK and PLOCKx write 1 */
    GPIOx->PLOCK = temp_value;
    
    /* PLOCKK write 0 */
    GPIOx->PLOCK = pin; 
    
    /* PLOCKK and PLOCKx write 1 */
    GPIOx->PLOCK = temp_value; 

    /* PLOCKK read 0 */
    temp_value = GPIOx->PLOCK;
    
    /* PLOCKK read 1 */
    temp_value = GPIOx->PLOCK;
}


/**
 *\*\name   GPIO_Pin_Remap_Set.
 *\*\fun    Pin remapping configuration.
 *\*\param  port_source :
 *\*\          - GPIOA_PORT_SOURCE
 *\*\          - GPIOB_PORT_SOURCE
 *\*\          - GPIOC_PORT_SOURCE
 *\*\          - GPIOD_PORT_SOURCE
 *\*\param  pin_source :
 *\*\          - GPIO_PIN_SOURCE0
 *\*\          - GPIO_PIN_SOURCE1
 *\*\          - GPIO_PIN_SOURCE2
 *\*\          - GPIO_PIN_SOURCE3
 *\*\          - GPIO_PIN_SOURCE4
 *\*\          - GPIO_PIN_SOURCE5
 *\*\          - GPIO_PIN_SOURCE6
 *\*\          - GPIO_PIN_SOURCE7
 *\*\          - GPIO_PIN_SOURCE8
 *\*\          - GPIO_PIN_SOURCE9
 *\*\          - GPIO_PIN_SOURCE10
 *\*\          - GPIO_PIN_SOURCE11
 *\*\          - GPIO_PIN_SOURCE12
 *\*\          - GPIO_PIN_SOURCE13
 *\*\          - GPIO_PIN_SOURCE14
 *\*\          - GPIO_PIN_SOURCE15
 *\*\param  alternate_function :
 *\*\          - GPIO_AF0_SWDIO_JTMS   SWDIO Alternate Function mapping   
 *\*\          - GPIO_AF0_SWCLK_JTCK   SWCLK Alternate Function mapping   
 *\*\          - GPIO_AF0_JTDI         JTDI  Alternate Function mapping   
 *\*\          - GPIO_AF0_JTDO         JTDO  Alternate Function mapping   
 *\*\          - GPIO_AF0_NJRST        NJRST Alternate Function mapping   
 *\*\
 *\*\          - GPIO_AF1_SPI1         SPI1 Alternate Function mapping    
 *\*\          - GPIO_AF1_SPI2         SPI2 Alternate Function mapping    
 *\*\          - GPIO_AF1_TIM8         TIM8 Alternate Function mapping    
 *\*\          - GPIO_AF1_USART1       USART1 Alternate Function mapping  
 *\*\
 *\*\          - GPIO_AF2_TIM5         TIM5 Alternate Function mapping    
 *\*\          - GPIO_AF2_TIM1         TIM1 Alternate Function mapping    
 *\*\          - GPIO_AF2_USART1       USART1 Alternate Function mapping  
 *\*\          - GPIO_AF2_I2C2         I2C2 Alternate Function mapping    
 *\*\          - GPIO_AF2_CAN          CAN Alternate Function mapping     
 *\*\          - GPIO_AF2_CAN1         CAN1 Alternate Function mapping    
 *\*\          - GPIO_AF2_SPI2         SPI2 Alternate Function mapping    
 *\*\          - GPIO_AF2_SPI1         SPI1 Alternate Function mapping    
 *\*\          - GPIO_AF2_I2C1         I2C1 Alternate Function mapping    
 *\*\
 *\*\          - GPIO_AF3_TIM2         TIM2 Alternate Function mapping    
 *\*\          - GPIO_AF3_SPI2         SPI2 Alternate Function mapping    
 *\*\          - GPIO_AF3_TIM3         TIM3 Alternate Function mapping    
 *\*\          - GPIO_AF3_TIM1         TIM1 Alternate Function mapping    
 *\*\          - GPIO_AF3_LPTIM        LPTIM Alternate Function mapping   
 *\*\          - GPIO_AF3_TIM4         TIM4 Alternate Function mapping    
 *\*\
 *\*\          - GPIO_AF4_EVENTOUT     EVENTOUT Alternate Function mapping
 *\*\          - GPIO_AF4_USART2       USART2 Alternate Function mapping  
 *\*\
 *\*\          - GPIO_AF5_USART2       USART2 Alternate Function mapping  
 *\*\          - GPIO_AF5_USART1       USART1 Alternate Function mapping  
 *\*\          - GPIO_AF5_SPI1         SPI1 Alternate Function mapping    
 *\*\          - GPIO_AF5_TIM3         TIM3 Alternate Function mapping    
 *\*\          - GPIO_AF5_SPI2         SPI2 Alternate Function mapping    
 *\*\          - GPIO_AF5_I2C1         I2C1 Alternate Function mapping    
 *\*\
 *\*\          - GPIO_AF6_TIM2         TIM2 Alternate Function mapping    
 *\*\          - GPIO_AF6_I2C2         I2C2 Alternate Function mapping    
 *\*\          - GPIO_AF6_TIM4         TIM4 Alternate Function mapping    
 *\*\          - GPIO_AF6_TIM1         TIM1 Alternate Function mapping    
 *\*\          - GPIO_AF6_SPI1         SPI1 Alternate Function mapping    
 *\*\          - GPIO_AF6_SPI2         SPI2 Alternate Function mapping    
 *\*\          - GPIO_AF6_LPTIM        LPTIM Alternate Function mapping   
 *\*\          - GPIO_AF6_CAN          CAN Alternate Function mapping     
 *\*\          - GPIO_AF6_UART4        UART4 Alternate Function mapping     
 *\*\
 *\*\          - GPIO_AF7_TIM5         TIM5 Alternate Function mapping     
 *\*\          - GPIO_AF7_TIM8         TIM8 Alternate Function mapping     
 *\*\          - GPIO_AF7_I2C2         I2C2 Alternate Function mapping     
 *\*\          - GPIO_AF7_USART2       USART2 Alternate Function mapping   
 *\*\          - GPIO_AF7_UART4        UART4 Alternate Function mapping    
 *\*\          - GPIO_AF7_UART3        UART3 Alternate Function mapping    
 *\*\          - GPIO_AF7_TIM1         TIM1 Alternate Function mapping     
 *\*\          - GPIO_AF7_I2C1         I2C1 Alternate Function mapping     
 *\*\
 *\*\          - GPIO_AF8_TIM8         TIM8 Alternate Function mapping     
 *\*\          - GPIO_AF8_TIM5         TIM5 Alternate Function mapping     
 *\*\          - GPIO_AF8_COMP2        COMP2 Alternate Function mapping    
 *\*\          - GPIO_AF8_I2C1         I2C1 Alternate Function mapping     
 *\*\          - GPIO_AF8_TIM1         TIM1 Alternate Function mapping     
 *\*\          - GPIO_AF8_COMP1        COMP1 Alternate Function mapping    
 *\*\          - GPIO_AF8_UART3        UART3 Alternate Function mapping    
 *\*\
 *\*\          - GPIO_AF9_COMP1        COMP1 Alternate Function mapping    
 *\*\          - GPIO_AF9_TIM8         TIM8 Alternate Function mapping     
 *\*\          - GPIO_AF9_TIM4         TIM4 Alternate Function mapping     
 *\*\          - GPIO_AF9_MCO          MCO Alternate Function mapping      
 *\*\          - GPIO_AF9_RTC          RTC Alternate Function mapping      
 *\*\          - GPIO_AF9_COMP2        COMP2 Alternate Function mapping    
 *\*\          - GPIO_AF9_LPTIM        LPTIM Alternate Function mapping    
 *\*\          - GPIO_AF9_I2C2         I2C2 Alternate Function mapping     
 *\*\          - GPIO_AF9_TIMESTAMP    TIMESTAMP Alternate Function mapping 
 *\*\
 *\*\          - GPIO_AF10_TIM1        TIM1 Alternate Function mapping     
 *\*\          - GPIO_AF10_TIM8        TIM8 Alternate Function mapping     
 *\*\          - GPIO_AF10_COMP3       COMP3 Alternate Function mapping    
 *\*\          - GPIO_AF10_TIM4        TIM4 Alternate Function mapping     
 *\*\          - GPIO_AF10_COMP1       COMP1 Alternate Function mapping    
 *\*\          - GPIO_AF10_UART3       UART3 Alternate Function mapping    
 *\*\
 *\*\          - GPIO_AF11_UART4       UART4 Alternate Function mapping    
 *\*\          - GPIO_AF11_CAN         CAN Alternate Function mapping      
 *\*\          - GPIO_AF11_USART2      USART2 Alternate Function mapping   
 *\*\          - GPIO_AF11_TIM8        TIM8 Alternate Function mapping     
 *\*\          - GPIO_AF11_COMP3       COMP3 Alternate Function mapping    
 *\*\
 *\*\          - GPIO_AF12_LPTIM       LPTIM Alternate Function mapping    
 *\*\          - GPIO_AF12_BEEPER      BEEPER Alternate Function mapping   
 *\*\
 *\*\          - GPIO_AF13_TIM3        TIM3 Alternate Function mapping     
 *\*\          - GPIO_AF13_TIM8        TIM8 Alternate Function mapping     
 *\*\          - GPIO_AF13_TIM4        TIM4 Alternate Function mapping     
 *\*\          - GPIO_AF13_TIM5        TIM5 Alternate Function mapping     
 *\*\return none
 */
void GPIO_Pin_Remap_Set(uint8_t port_source, uint8_t pin_source, uint32_t alternate_function)
{
    uint32_t position = 0x00, temp_value = 0x00;
    GPIO_Module *GPIOx;

    /* Get Peripheral index */
    GPIOx = GPIO_GET_PERIPH(port_source);

    if(pin_source & (uint8_t)AF_SELECTION_MASK)
    {
        position = (uint32_t)(pin_source & (uint8_t)AF_WRITE_POSITION_MASK);

        /* Read GPIO_AFH register */
        temp_value = GPIOx->AFH;

        /* Reset corresponding bits */
        temp_value &= ~(GPIO_AF_MASK << (position * MULTIPLIER_FACTOR_4));

        /* Set corresponding bits */
        temp_value |= (alternate_function << (position * MULTIPLIER_FACTOR_4));

        /* Write to the GPIO_AFH register */
        GPIOx->AFH = temp_value;
    }
    else
    {
        position = (uint32_t)(pin_source & (uint8_t)AF_WRITE_POSITION_MASK);

        /* Read GPIO_AFL register */
        temp_value  = GPIOx->AFL;

        /* Reset corresponding bits */
        temp_value &= ~(GPIO_AF_MASK << (position * MULTIPLIER_FACTOR_4)); 

        /* Set corresponding bits */
        temp_value |= (alternate_function << (position * MULTIPLIER_FACTOR_4));

        /* Write to the GPIO_AFL register */
        GPIOx->AFL = temp_value;
    }
}

/**
 *\*\name   GPIO_EXTI_Line_Set.
 *\*\fun    Selects the GPIO pin used as EXTI Line.
 *\*\param  EXTI_line :
 *\*\          - EXTI_LINE_SOURCE0
 *\*\          - EXTI_LINE_SOURCE1
 *\*\          - EXTI_LINE_SOURCE2
 *\*\          - EXTI_LINE_SOURCE3
 *\*\          - EXTI_LINE_SOURCE4
 *\*\          - EXTI_LINE_SOURCE5
 *\*\          - EXTI_LINE_SOURCE6
 *\*\          - EXTI_LINE_SOURCE7
 *\*\          - EXTI_LINE_SOURCE8
 *\*\          - EXTI_LINE_SOURCE9
 *\*\          - EXTI_LINE_SOURCE10
 *\*\          - EXTI_LINE_SOURCE11
 *\*\          - EXTI_LINE_SOURCE12
 *\*\          - EXTI_LINE_SOURCE13
 *\*\          - EXTI_LINE_SOURCE14
 *\*\          - EXTI_LINE_SOURCE15
 *\*\param  pin_source :
 *\*\          - AFIO_EXTI_PA0
 *\*\          - AFIO_EXTI_PB0
 *\*\          - AFIO_EXTI_PD0
 *\*\          - AFIO_EXTI_PA1
 *\*\          - AFIO_EXTI_PB1
 *\*\          - AFIO_EXTI_PA2
 *\*\          - AFIO_EXTI_PB2
 *\*\          - AFIO_EXTI_PA3
 *\*\          - AFIO_EXTI_PB3
 *\*\          - AFIO_EXTI_PA4
 *\*\          - AFIO_EXTI_PB4
 *\*\          - AFIO_EXTI_PA5
 *\*\          - AFIO_EXTI_PB5
 *\*\          - AFIO_EXTI_PA6
 *\*\          - AFIO_EXTI_PB6
 *\*\          - AFIO_EXTI_PA7
 *\*\          - AFIO_EXTI_PB7
 *\*\          - AFIO_EXTI_PA8
 *\*\          - AFIO_EXTI_PB8
 *\*\          - AFIO_EXTI_PA9
 *\*\          - AFIO_EXTI_PB9
 *\*\          - AFIO_EXTI_PA10
 *\*\          - AFIO_EXTI_PB10
 *\*\          - AFIO_EXTI_PA11
 *\*\          - AFIO_EXTI_PB11
 *\*\          - AFIO_EXTI_PA12
 *\*\          - AFIO_EXTI_PB12
 *\*\          - AFIO_EXTI_PD12
 *\*\          - AFIO_EXTI_PA13
 *\*\          - AFIO_EXTI_PB13
 *\*\          - AFIO_EXTI_PC13
 *\*\          - AFIO_EXTI_PD13
 *\*\          - AFIO_EXTI_PA14
 *\*\          - AFIO_EXTI_PB14
 *\*\          - AFIO_EXTI_PC14
 *\*\          - AFIO_EXTI_PD14
 *\*\          - AFIO_EXTI_PA15
 *\*\          - AFIO_EXTI_PB15
 *\*\          - AFIO_EXTI_PC15
 *\*\          - AFIO_EXTI_PD15
 *\*\return none
 */
void GPIO_EXTI_Line_Set(uint8_t EXTI_line, uint32_t pin_source)
{
    AFIO->EXTI_CFG[(EXTI_line >> SHIFT_EXTI)] &= ~(AFIO_EXTI_CFG_MASK << ((uint32_t)((EXTI_line & (uint8_t)AFIO_EXTI_POSITION_MASK) * MULTIPLIER_FACTOR_8)));
    AFIO->EXTI_CFG[(EXTI_line >> SHIFT_EXTI)] |=  (pin_source << ((uint32_t)((EXTI_line & (uint8_t)AFIO_EXTI_POSITION_MASK) * MULTIPLIER_FACTOR_8)));
}


/**
 *\*\name   AFIO_SPI_NSS_Mode_Set.
 *\*\fun    Selects the alternate function SPIx NSS mode.
 *\*\param  AFIO_SPIx_NSS : 
 *\*\          choose which SPI configuration.
 *\*\          - AFIO_SPI1_NSS
 *\*\          - AFIO_SPI2_NSS
 *\*\param  SPI_nss_mode : 
 *\*\          specifies the SPI_NSS mode to be configured.
 *\*\          - AFIO_SPI_NSS_HIGH_IMPEDANCE
 *\*\          - AFIO_SPI_NSS_High_LEVEL
 *\*\return none
 */
void AFIO_SPI_NSS_Mode_Set(uint32_t AFIO_SPIx_NSS, uint32_t SPI_NSS_mode)
{
    uint32_t temp_value = 0x00U;

    temp_value = (AFIO->RMP_CFG & AFIO_RMP_CFG_MASK);

    if(SPI_NSS_mode != AFIO_SPI_NSS_HIGH_IMPEDANCE)
    {
        temp_value |= AFIO_SPIx_NSS;
    }
    else
    {
        temp_value &= ~AFIO_SPIx_NSS;
    }

    AFIO->RMP_CFG = temp_value;
}


/**
 *\*\name   AFIO_ADC_External_Trigger_Remap_Set.
 *\*\fun    Configurate ADC external trigger.
 *\*\param  ADC_ETR_type : 
 *\*\          choose whether to configure rule conversion or injection conversion.
 *\*\          - AFIO_ADC_ETRI
 *\*\          - AFIO_ADC_ETRR
 *\*\param  ADC_trigger_remap : 
 *\*\          specifies the external trigger line be configured.
 *\*\          - AFIO_ADC_TRIG_EXTI_0
 *\*\          - AFIO_ADC_TRIG_EXTI_1
 *\*\          - AFIO_ADC_TRIG_EXTI_2
 *\*\          - AFIO_ADC_TRIG_EXTI_3
 *\*\          - AFIO_ADC_TRIG_EXTI_4
 *\*\          - AFIO_ADC_TRIG_EXTI_5
 *\*\          - AFIO_ADC_TRIG_EXTI_6
 *\*\          - AFIO_ADC_TRIG_EXTI_7
 *\*\          - AFIO_ADC_TRIG_EXTI_8
 *\*\          - AFIO_ADC_TRIG_EXTI_9
 *\*\          - AFIO_ADC_TRIG_EXTI_10
 *\*\          - AFIO_ADC_TRIG_EXTI_11
 *\*\          - AFIO_ADC_TRIG_EXTI_12
 *\*\          - AFIO_ADC_TRIG_EXTI_13
 *\*\          - AFIO_ADC_TRIG_EXTI_14
 *\*\          - AFIO_ADC_TRIG_EXTI_15
 *\*\          - AFIO_ADC_TRIG_TIM8_TRGO
 *\*\          - AFIO_ADC_TRIG_TIM8_CH4
 *\*\return none
 */
void AFIO_ADC_External_Trigger_Remap_Set(AFIO_ADC_ETRType ADC_ETR_type, AFIO_ADC_Trig_RemapType ADC_trigger_remap)
{
    uint32_t temp_value = 0x00U;

    if(ADC_ETR_type == AFIO_ADC_ETRI)
    {
        temp_value = AFIO->RMP_CFG;

        /* clear AFIO_RMP_CFG register ETRI bit */
        temp_value &= (~(AFIO_RMPCFG_ADC_MASK << AFIO_ADC_ETRI));

        /* if ADC_ETR_type is AFIO_ADC_ETRI then ADC_trigger_remap cannot be AFIO_ADC_TRIG_TIM8_TRGO */
        if(ADC_trigger_remap == AFIO_ADC_TRIG_TIM8_CH4)
        {
            /* select TIM8_CH4 line to connect */
            temp_value |= (AFIO_RMPCFG_ADC_MASK << AFIO_ADC_ETRI);
        }
        else
        {
            /* select which external line is connected */
            temp_value &= (~(AFIO_RMPCFG_EXTI_MASK << SHIFT_EXTI_ETRI));
            temp_value |= (ADC_trigger_remap << SHIFT_EXTI_ETRI);
        }
        AFIO->RMP_CFG = temp_value;
    }
    else if(ADC_ETR_type == AFIO_ADC_ETRR)
    {
        temp_value  = AFIO->RMP_CFG;

        /* clear AFIO_RMP_CFG register ETRR bit */
        temp_value &= (~(AFIO_RMPCFG_ADC_MASK << AFIO_ADC_ETRR));

        /* if ADC_ETR_type is AFIO_ADC_ETRR then ADC_trigger_remap cannot be AFIO_ADC_TRIG_TIM8_CH4 */
        if(ADC_trigger_remap == AFIO_ADC_TRIG_TIM8_TRGO)
        {
            /* select TIM8_TRGO line to connect */
            temp_value |= (AFIO_RMPCFG_ADC_MASK << AFIO_ADC_ETRR);
        }
        else
        {
            /* select which external line is connected */
            temp_value &= ~AFIO_RMPCFG_EXTI_MASK;
            temp_value |= ADC_trigger_remap;
        }
        AFIO->RMP_CFG = temp_value;
    }
}


/**
 *\*\name   AFIO_5V_Tolerance_Enable.
 *\*\fun    Enables 5V tolerance of GPIOA and GPIOB.
 *\*\param  tolerance_pin : 
 *\*\          - PA0_5V_TOLERANCE         
 *\*\          - PA1_5V_TOLERANCE         
 *\*\          - PA2_5V_TOLERANCE        
 *\*\          - PA3_5V_TOLERANCE         
 *\*\          - PA4_5V_TOLERANCE         
 *\*\          - PA5_5V_TOLERANCE         
 *\*\          - PA6_5V_TOLERANCE         
 *\*\          - PA7_5V_TOLERANCE        
 *\*\          - PA8_5V_TOLERANCE         
 *\*\          - PA11_5V_TOLERANCE        
 *\*\          - PA12_5V_TOLERANCE        
 *\*\          - PA15_5V_TOLERANCE        
 *\*\          - PB0_5V_TOLERANCE         
 *\*\          - PB1_5V_TOLERANCE         
 *\*\          - PB2_5V_TOLERANCE         
 *\*\          - PB3_5V_TOLERANCE        
 *\*\          - PB4_5V_TOLERANCE         
 *\*\          - PB5_5V_TOLERANCE         
 *\*\          - PB7_5V_TOLERANCE         
 *\*\          - PB10_5V_TOLERANCE       
 *\*\          - PB11_5V_TOLERANCE      
 *\*\          - PB12_5V_TOLERANCE        
 *\*\          - PB13_5V_TOLERANCE        
 *\*\          - PB14_5V_TOLERANCE        
 *\*\          - PB15_5V_TOLERANCE
 *\*\return none
 */
void AFIO_5V_Tolerance_Enable(uint32_t tolerance_pin)
{
    AFIO->TOL5V_CFG &= ~tolerance_pin;
}

/**
 *\*\name   AFIO_5V_Tolerance_Disable.
 *\*\fun    Disables 5V tolerance of GPIOA and GPIOB.
 *\*\param  tolerance_pin : 
 *\*\          - PA0_5V_TOLERANCE         
 *\*\          - PA1_5V_TOLERANCE         
 *\*\          - PA2_5V_TOLERANCE        
 *\*\          - PA3_5V_TOLERANCE         
 *\*\          - PA4_5V_TOLERANCE         
 *\*\          - PA5_5V_TOLERANCE         
 *\*\          - PA6_5V_TOLERANCE         
 *\*\          - PA7_5V_TOLERANCE        
 *\*\          - PA8_5V_TOLERANCE         
 *\*\          - PA11_5V_TOLERANCE        
 *\*\          - PA12_5V_TOLERANCE        
 *\*\          - PA15_5V_TOLERANCE        
 *\*\          - PB0_5V_TOLERANCE         
 *\*\          - PB1_5V_TOLERANCE         
 *\*\          - PB2_5V_TOLERANCE         
 *\*\          - PB3_5V_TOLERANCE        
 *\*\          - PB4_5V_TOLERANCE         
 *\*\          - PB5_5V_TOLERANCE         
 *\*\          - PB7_5V_TOLERANCE         
 *\*\          - PB10_5V_TOLERANCE       
 *\*\          - PB11_5V_TOLERANCE      
 *\*\          - PB12_5V_TOLERANCE        
 *\*\          - PB13_5V_TOLERANCE        
 *\*\          - PB14_5V_TOLERANCE        
 *\*\          - PB15_5V_TOLERANCE
 *\*\return none
 */
void AFIO_5V_Tolerance_Disable(uint32_t tolerance_pin)
{
    AFIO->TOL5V_CFG |= tolerance_pin;
}


/**
 *\*\name   AFIO_Filter_Stage_Ctrl.
 *\*\fun    Filtr stage control.
 *\*\param  filter : 
 *\*\          - AFIO_IOFITCFG     filter bypass       
 *\*\return none
 */
void AFIO_Filter_Stage_Ctrl(uint8_t filter)
{
    AFIO->FILT_CFG = (uint32_t)filter;
}


/**
 *\*\name   AFIO_EFT_Enable.
 *\*\fun    Enables EFT IE of port pins.
 *\*\param  GPIOx : 
 *\*\          - GPIOA         
 *\*\          - GPIOB         
 *\*\          - GPIOC         
 *\*\          - GPIOD  
 *\*\param  EFT_pin :       
 *\*\          - AFIO_PA0_EFT                 
 *\*\          - AFIO_PA1_EFT             
 *\*\          - AFIO_PA2_EFT              
 *\*\          - AFIO_PA3_EFT              
 *\*\          - AFIO_PA4_EFT               
 *\*\          - AFIO_PA5_EFT              
 *\*\          - AFIO_PA6_EFT               
 *\*\          - AFIO_PA7_EFT                
 *\*\          - AFIO_PA8_EFT              
 *\*\          - AFIO_PA9_EFT                
 *\*\          - AFIO_PA10_EFT             
 *\*\          - AFIO_PA11_EFT              
 *\*\          - AFIO_PA12_EFT             
 *\*\          - AFIO_PA13_EFT             
 *\*\          - AFIO_PA14_EFT             
 *\*\          - AFIO_PA15_EFT          
 *\*\          - AFIO_PB0_EFT                 
 *\*\          - AFIO_PB1_EFT               
 *\*\          - AFIO_PB2_EFT              
 *\*\          - AFIO_PB3_EFT             
 *\*\          - AFIO_PB4_EFT              
 *\*\          - AFIO_PB5_EFT                
 *\*\          - AFIO_PB6_EFT                
 *\*\          - AFIO_PB7_EFT             
 *\*\          - AFIO_PB8_EFT             
 *\*\          - AFIO_PB9_EFT           
 *\*\          - AFIO_PB10_EFT           
 *\*\          - AFIO_PB11_EFT            
 *\*\          - AFIO_PB12_EFT              
 *\*\          - AFIO_PB13_EFT             
 *\*\          - AFIO_PB14_EFT             
 *\*\          - AFIO_PB15_EFT            
 *\*\          - AFIO_PC13_EFT             
 *\*\          - AFIO_PC14_EFT             
 *\*\          - AFIO_PC15_EFT            
 *\*\          - AFIO_PD0_EFT               
 *\*\          - AFIO_PD12_EFT            
 *\*\          - AFIO_PD13_EFT             
 *\*\          - AFIO_PD14_EFT              
 *\*\          - AFIO_PD15_EFT 
 *\*\return none
 */
void AFIO_EFT_Enable(GPIO_Module* GPIOx, uint32_t EFT_pin)
{
    uint32_t port;

    /* Get port index */
    port = ((uint32_t)GPIO_GET_INDEX(GPIOx));

    if(!(port & AFIO_EFT_SELECTION_MASK))
    {
        if(GPIOx == GPIOA)
        {
            AFIO->EFT_CFG1 |= EFT_pin;
        }
        else if(GPIOx == GPIOB)
        {
            AFIO->EFT_CFG1 |= EFT_pin;
        }
    }
    else
    {
        if(GPIOx == GPIOC)
        {
            AFIO->EFT_CFG2 |= EFT_pin;
        }
        else if(GPIOx == GPIOD)
        {
            AFIO->EFT_CFG2 |= EFT_pin;
        }
    }     
}


/**
 *\*\name   AFIO_EFT_Disable.
 *\*\fun    Disables EFT IE of port pins.
 *\*\param  GPIOx : 
 *\*\          - GPIOA         
 *\*\          - GPIOB         
 *\*\          - GPIOC         
 *\*\          - GPIOD  
 *\*\param  EFT_pin :       
 *\*\          - AFIO_PA0_EFT                 
 *\*\          - AFIO_PA1_EFT             
 *\*\          - AFIO_PA2_EFT              
 *\*\          - AFIO_PA3_EFT              
 *\*\          - AFIO_PA4_EFT               
 *\*\          - AFIO_PA5_EFT              
 *\*\          - AFIO_PA6_EFT               
 *\*\          - AFIO_PA7_EFT                
 *\*\          - AFIO_PA8_EFT              
 *\*\          - AFIO_PA9_EFT                
 *\*\          - AFIO_PA10_EFT             
 *\*\          - AFIO_PA11_EFT              
 *\*\          - AFIO_PA12_EFT             
 *\*\          - AFIO_PA13_EFT             
 *\*\          - AFIO_PA14_EFT             
 *\*\          - AFIO_PA15_EFT          
 *\*\          - AFIO_PB0_EFT                 
 *\*\          - AFIO_PB1_EFT               
 *\*\          - AFIO_PB2_EFT              
 *\*\          - AFIO_PB3_EFT             
 *\*\          - AFIO_PB4_EFT              
 *\*\          - AFIO_PB5_EFT                
 *\*\          - AFIO_PB6_EFT                
 *\*\          - AFIO_PB7_EFT             
 *\*\          - AFIO_PB8_EFT             
 *\*\          - AFIO_PB9_EFT           
 *\*\          - AFIO_PB10_EFT           
 *\*\          - AFIO_PB11_EFT            
 *\*\          - AFIO_PB12_EFT              
 *\*\          - AFIO_PB13_EFT             
 *\*\          - AFIO_PB14_EFT             
 *\*\          - AFIO_PB15_EFT            
 *\*\          - AFIO_PC13_EFT             
 *\*\          - AFIO_PC14_EFT             
 *\*\          - AFIO_PC15_EFT            
 *\*\          - AFIO_PD0_EFT               
 *\*\          - AFIO_PD12_EFT            
 *\*\          - AFIO_PD13_EFT             
 *\*\          - AFIO_PD14_EFT              
 *\*\          - AFIO_PD15_EFT 
 *\*\return none
 */
void AFIO_EFT_Disable(GPIO_Module* GPIOx, uint32_t EFT_pin)
{
    uint32_t port;

    /* Get port index */
    port = ((uint32_t)GPIO_GET_INDEX(GPIOx));

    if(!(port & AFIO_EFT_SELECTION_MASK))
    {
        if(GPIOx == GPIOA)
        {    
            AFIO->EFT_CFG1 &= ~EFT_pin; 
        }
        else if(GPIOx == GPIOB)
        {
            AFIO->EFT_CFG1 &= ~EFT_pin;
        }
    }
    else
    {
        if(GPIOx == GPIOC)
        {
            AFIO->EFT_CFG2 &= ~EFT_pin; 
        }
        else if(GPIOx == GPIOD)
        {
            AFIO->EFT_CFG2 &= ~EFT_pin;
        }
    }
}



/**
 *\*\name   AFIO_Digital_EFT_Enable.
 *\*\fun    Enables digital EFT IE of port pins.
 *\*\param  GPIOx : 
 *\*\          - GPIOA         
 *\*\          - GPIOB         
 *\*\          - GPIOC         
 *\*\          - GPIOD  
 *\*\param  digital_EFT_pin :       
 *\*\          - AFIO_PA0_DIGEFT                 
 *\*\          - AFIO_PA1_DIGEFT             
 *\*\          - AFIO_PA2_DIGEFT              
 *\*\          - AFIO_PA3_DIGEFT              
 *\*\          - AFIO_PA4_DIGEFT               
 *\*\          - AFIO_PA5_DIGEFT              
 *\*\          - AFIO_PA6_DIGEFT               
 *\*\          - AFIO_PA7_DIGEFT                
 *\*\          - AFIO_PA8_DIGEFT              
 *\*\          - AFIO_PA9_DIGEFT                
 *\*\          - AFIO_PA10_DIGEFT             
 *\*\          - AFIO_PA11_DIGEFT              
 *\*\          - AFIO_PA12_DIGEFT             
 *\*\          - AFIO_PA13_DIGEFT             
 *\*\          - AFIO_PA14_DIGEFT             
 *\*\          - AFIO_PA15_DIGEFT          
 *\*\          - AFIO_PB0_DIGEFT                 
 *\*\          - AFIO_PB1_DIGEFT               
 *\*\          - AFIO_PB2_DIGEFT              
 *\*\          - AFIO_PB3_DIGEFT             
 *\*\          - AFIO_PB4_DIGEFT              
 *\*\          - AFIO_PB5_DIGEFT                
 *\*\          - AFIO_PB6_DIGEFT                
 *\*\          - AFIO_PB7_DIGEFT             
 *\*\          - AFIO_PB8_DIGEFT             
 *\*\          - AFIO_PB9_DIGEFT           
 *\*\          - AFIO_PB10_DIGEFT           
 *\*\          - AFIO_PB11_DIGEFT            
 *\*\          - AFIO_PB12_DIGEFT              
 *\*\          - AFIO_PB13_DIGEFT             
 *\*\          - AFIO_PB14_DIGEFT             
 *\*\          - AFIO_PB15_DIGEFT            
 *\*\          - AFIO_PC13_DIGEFT             
 *\*\          - AFIO_PC14_DIGEFT             
 *\*\          - AFIO_PC15_DIGEFT            
 *\*\          - AFIO_PD0_DIGEFT               
 *\*\          - AFIO_PD12_DIGEFT            
 *\*\          - AFIO_PD13_DIGEFT             
 *\*\          - AFIO_PD14_DIGEFT              
 *\*\          - AFIO_PD15_DIGEFT  
 *\*\return none
 */
void AFIO_Digital_EFT_Enable(GPIO_Module* GPIOx, uint32_t digital_EFT_pin)
{
    uint32_t port;

    /* Get port index */
    port = ((uint32_t)GPIO_GET_INDEX(GPIOx));

    if(!(port & AFIO_EFT_SELECTION_MASK))
    {
        if(GPIOx == GPIOA)
        {
            AFIO->DIGEFT_CFG1 |= digital_EFT_pin;
        }
        else if(GPIOx == GPIOB)
        {
            AFIO->DIGEFT_CFG1 |= digital_EFT_pin;  
        }  
    }
    else
    {
        if(GPIOx == GPIOC)
        {    
            AFIO->DIGEFT_CFG2 |= digital_EFT_pin;
        }
        else if(GPIOx == GPIOD)
        {
            AFIO->DIGEFT_CFG2 |= digital_EFT_pin;
        }
    }     
}


/**
 *\*\name   AFIO_Digital_EFT_Disable.
 *\*\fun    Disables digital EFT IE of port pins.
 *\*\param  GPIOx : 
 *\*\          - GPIOA         
 *\*\          - GPIOB         
 *\*\          - GPIOC         
 *\*\          - GPIOD  
 *\*\param  digital_EFT_pin :       
 *\*\          - AFIO_PA0_DIGEFT                 
 *\*\          - AFIO_PA1_DIGEFT             
 *\*\          - AFIO_PA2_DIGEFT              
 *\*\          - AFIO_PA3_DIGEFT              
 *\*\          - AFIO_PA4_DIGEFT               
 *\*\          - AFIO_PA5_DIGEFT              
 *\*\          - AFIO_PA6_DIGEFT               
 *\*\          - AFIO_PA7_DIGEFT                
 *\*\          - AFIO_PA8_DIGEFT              
 *\*\          - AFIO_PA9_DIGEFT                
 *\*\          - AFIO_PA10_DIGEFT             
 *\*\          - AFIO_PA11_DIGEFT              
 *\*\          - AFIO_PA12_DIGEFT             
 *\*\          - AFIO_PA13_DIGEFT             
 *\*\          - AFIO_PA14_DIGEFT             
 *\*\          - AFIO_PA15_DIGEFT          
 *\*\          - AFIO_PB0_DIGEFT                 
 *\*\          - AFIO_PB1_DIGEFT               
 *\*\          - AFIO_PB2_DIGEFT              
 *\*\          - AFIO_PB3_DIGEFT             
 *\*\          - AFIO_PB4_DIGEFT              
 *\*\          - AFIO_PB5_DIGEFT                
 *\*\          - AFIO_PB6_DIGEFT                
 *\*\          - AFIO_PB7_DIGEFT             
 *\*\          - AFIO_PB8_DIGEFT             
 *\*\          - AFIO_PB9_DIGEFT           
 *\*\          - AFIO_PB10_DIGEFT           
 *\*\          - AFIO_PB11_DIGEFT            
 *\*\          - AFIO_PB12_DIGEFT              
 *\*\          - AFIO_PB13_DIGEFT             
 *\*\          - AFIO_PB14_DIGEFT             
 *\*\          - AFIO_PB15_DIGEFT            
 *\*\          - AFIO_PC13_DIGEFT             
 *\*\          - AFIO_PC14_DIGEFT             
 *\*\          - AFIO_PC15_DIGEFT            
 *\*\          - AFIO_PD0_DIGEFT               
 *\*\          - AFIO_PD12_DIGEFT            
 *\*\          - AFIO_PD13_DIGEFT             
 *\*\          - AFIO_PD14_DIGEFT              
 *\*\          - AFIO_PD15_DIGEFT  
 *\*\return none
 */
void AFIO_Digital_EFT_Disable(GPIO_Module* GPIOx, uint32_t digital_EFT_pin)
{
    uint32_t port;

    /* Get port index */
    port = ((uint32_t)GPIO_GET_INDEX(GPIOx));

    if(!(port & AFIO_EFT_SELECTION_MASK))
    {
        if(GPIOx == GPIOA)
        {
            AFIO->DIGEFT_CFG1 &= ~digital_EFT_pin; 
        }
        else if(GPIOx == GPIOB)
        {
            AFIO->DIGEFT_CFG1 &= ~digital_EFT_pin;
        }
    }
    else
    {
        if(GPIOx == GPIOC)
        {
            AFIO->DIGEFT_CFG2 &= ~digital_EFT_pin; 
        }
        else if(GPIOx == GPIOD)
        {
            AFIO->DIGEFT_CFG2 &= ~digital_EFT_pin;
        }
    }
}

