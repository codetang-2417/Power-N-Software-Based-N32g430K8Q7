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
*\*\file n32g430_gpio.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32G430_GPIO_H__
#define __N32G430_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"


#define GPIOA_MODE_POSITION             (12U)
#define GPIOB_MODE_POSITION1            (3U)
#define GPIOB_MODE_POSITION2            (4U)
#define GPIOD_MODE_POSITION             (0U)

#define GPIOA_PUPD_POSITION1            (15U) 
#define GPIOA_PUPD_POSITION2            (13U)
#define GPIOA_PUPD_POSITION3            (14U)
#define GPIOB_PUPD_POSITION1            (4U)
#define GPIOD_PUPD_POSITION1            (0U)
#define GPIOD_PUPD_POSITION2            (12U)


#define GPIO_AF_MODE                    ((uint32_t)GPIO_PMODE0_2)
#define GPIO_ANALOG_MODE                ((uint32_t)GPIO_PMODE0_Msk)
#define GPIO_INPUT_MODE                 ((uint32_t)GPIO_PMODE0_0)
#define GPIO_PU_MODE                    ((uint32_t)GPIO_PUPD0_1)
#define GPIO_PD_MODE                    ((uint32_t)GPIO_PUPD0_2)
#define GPIO_DRIVER_8MA                 ((uint32_t)GPIO_DS1_1)
#define GPIO_SR_SLOW                    (GPIO_SR_SR0)

#define GPIO_OUTPUT_TYPE_MASK           ((uint32_t)0x00000010)
#define GPIO_SET_PMODE_MASK             ((uint32_t)0x00000003)
#define GPIO_AF_MASK                    ((uint32_t)0x0000000F)
#define AFIO_EXTI_CFG_MASK              ((uint32_t)0x0000003F)
#define AFIO_RMP_CFG_MASK               ((uint32_t)0x00000FFF)
#define GPIO_PMODE_MASK                 ((uint32_t)GPIO_PMODE0_Msk)
#define GPIO_PUPD_MASK                  ((uint32_t)GPIO_PUPD0_Msk)
#define GPIO_DRIVER_MASK                ((uint32_t)GPIO_DS0_Msk)
#define GPIO_POTYPE_MASK                (GPIO_POTYPE_POT0)
#define GPIO_SR_MASK                    (GPIO_SR_SR0)
#define GPIO_PLOCKK_MASK                (GPIO_PLOCK_PLOCKK)
#define AFIO_EXTI_POSITION_MASK         (0x03)
#define AFIO_EFT_SELECTION_MASK         ((uint8_t)0x02)
#define AFIO_RMPCFG_ADC_MASK            (0x01U)
#define AF_SELECTION_MASK               (0x08)
#define AF_WRITE_POSITION_MASK          (0x07U)
#define AFIO_EXTICFG_MASK               (0xFFUL)
#define AFIO_RMPCFG_EXTI_MASK           (0x0FU)
#define IO_POSITION_MASK                (1U)

#define MULTIPLIER_FACTOR_2             (2U)
#define MULTIPLIER_FACTOR_4             (4U)
#define MULTIPLIER_FACTOR_8             (8U)

#define SHIFT_EXTI                      (REG_BIT2_OFFSET)
#define SHIFT_POTYPE                    (REG_BIT4_OFFSET)
#define SHIFT_EXTI_ETRI                 (REG_BIT4_OFFSET)
#define SHIFT_PBSC_HIGH16               (REG_BIT16_OFFSET)

#define GPIO_GET_INDEX(PERIPH)          (((PERIPH) == (GPIOA))? 0 :\
                                         ((PERIPH) == (GPIOB))? 1 :\
                                         ((PERIPH) == (GPIOC))? 2 :3)

#define GPIO_GET_PERIPH(INDEX)          (((INDEX)==((uint8_t)0x00))? GPIOA :\
                                         ((INDEX)==((uint8_t)0x01))? GPIOB :\
                                         ((INDEX)==((uint8_t)0x02))? GPIOC : GPIOD )

/**
 *\*\name   GPIO_ModeType. 
 *\*\fun    GPIO mode definition.
 *\*\       Values convention: 0x00YZ
 *\*\          - Y  : Output type (Push Pull or Open Drain)
 *\*\          - Z  : IO Direction mode (Input, Output, Alternate or Analog)      
 */
#define GPIO_MODE_INPUT     ((uint32_t)0x00000000U)  /* Input Floating Mode */
#define GPIO_MODE_OUT_PP    ((uint32_t)0x00000001U)  /* Output Push Pull Mode */
#define GPIO_MODE_OUT_OD    ((uint32_t)0x00000011U)  /* Output Open Drain Mode */
#define GPIO_MODE_AF_PP     ((uint32_t)0x00000002U)  /* Alternate Function Push Pull Mode  */
#define GPIO_MODE_AF_OD     ((uint32_t)0x00000012U)  /* Alternate Function Open Drain Mode */
#define GPIO_MODE_ANALOG    ((uint32_t)0x00000003U)  /* Analog Mode */

/** GPIO Pull-Up or Pull-Down Activation **/
#define GPIO_NO_PULL         ((uint32_t)GPIO_PUPD0_0) /* No Pull-up or Pull-down activation */
#define GPIO_PULL_UP         ((uint32_t)GPIO_PUPD0_1) /* Pull-up activation */
#define GPIO_PULL_DOWN       ((uint32_t)GPIO_PUPD0_2) /* Pull-down activation */

/** slew rate config **/
#define GPIO_SLEW_RATE_FAST  ((uint32_t)0x00000000U)
#define GPIO_SLEW_RATE_SLOW  ((uint32_t)0x00000001U)

/** driver strength config **/
#define GPIO_DS_2MA          ((uint32_t)GPIO_DS0_0)
#define GPIO_DS_8MA          ((uint32_t)GPIO_DS0_1)
#define GPIO_DS_4MA          ((uint32_t)GPIO_DS0_2)
#define GPIO_DS_12MA         ((uint32_t)GPIO_DS0_3)

/** GPIO Init Structure Definition **/
typedef struct
{
    uint32_t         Pin;            /* Specifies the GPIO pins to be configured. */

    uint32_t         GPIO_Mode;      /* Specifies the operating mode for the selected pins. */

    uint32_t         GPIO_Pull;      /* Specifies the Pull-up or Pull-Down activation for the selected pins. */

    uint32_t         GPIO_Slew_Rate; /* Specify the reverse speed for the selected pins. */

    uint32_t         GPIO_Current;   /* Driving current of the select pins. */

    uint32_t         GPIO_Alternate; /* Peripheral to be connected to the selected pins. */ 
}GPIO_InitType;

/** Bit_SET and Bit_RESET enumeration **/
typedef enum
{
    PIN_RESET = 0,
    PIN_SET
}Bit_CommandType;

/** GPIO_pins_define **/
#define GPIO_PIN_0           ((uint16_t)0x0001U) /* Pin 0 selected    */
#define GPIO_PIN_1           ((uint16_t)0x0002U) /* Pin 1 selected    */
#define GPIO_PIN_2           ((uint16_t)0x0004U) /* Pin 2 selected    */
#define GPIO_PIN_3           ((uint16_t)0x0008U) /* Pin 3 selected    */
#define GPIO_PIN_4           ((uint16_t)0x0010U) /* Pin 4 selected    */
#define GPIO_PIN_5           ((uint16_t)0x0020U) /* Pin 5 selected    */
#define GPIO_PIN_6           ((uint16_t)0x0040U) /* Pin 6 selected    */
#define GPIO_PIN_7           ((uint16_t)0x0080U) /* Pin 7 selected    */
#define GPIO_PIN_8           ((uint16_t)0x0100U) /* Pin 8 selected    */
#define GPIO_PIN_9           ((uint16_t)0x0200U) /* Pin 9 selected    */
#define GPIO_PIN_10          ((uint16_t)0x0400U) /* Pin 10 selected   */
#define GPIO_PIN_11          ((uint16_t)0x0800U) /* Pin 11 selected   */
#define GPIO_PIN_12          ((uint16_t)0x1000U) /* Pin 12 selected   */
#define GPIO_PIN_13          ((uint16_t)0x2000U) /* Pin 13 selected   */
#define GPIO_PIN_14          ((uint16_t)0x4000U) /* Pin 14 selected   */
#define GPIO_PIN_15          ((uint16_t)0x8000U) /* Pin 15 selected   */
#define GPIO_PIN_ALL         ((uint16_t)0xFFFFU) /* All pins selected */

/** GPIO Port Sources **/
#define GPIOA_PORT_SOURCE    ((uint8_t)0x00)
#define GPIOB_PORT_SOURCE    ((uint8_t)0x01)
#define GPIOC_PORT_SOURCE    ((uint8_t)0x02)
#define GPIOD_PORT_SOURCE    ((uint8_t)0x03)

/** GPIO Pin Sources **/
#define GPIO_PIN_SOURCE0     ((uint8_t)0x00)
#define GPIO_PIN_SOURCE1     ((uint8_t)0x01)
#define GPIO_PIN_SOURCE2     ((uint8_t)0x02)
#define GPIO_PIN_SOURCE3     ((uint8_t)0x03)
#define GPIO_PIN_SOURCE4     ((uint8_t)0x04)
#define GPIO_PIN_SOURCE5     ((uint8_t)0x05)
#define GPIO_PIN_SOURCE6     ((uint8_t)0x06)
#define GPIO_PIN_SOURCE7     ((uint8_t)0x07)
#define GPIO_PIN_SOURCE8     ((uint8_t)0x08)
#define GPIO_PIN_SOURCE9     ((uint8_t)0x09)
#define GPIO_PIN_SOURCE10    ((uint8_t)0x0A)
#define GPIO_PIN_SOURCE11    ((uint8_t)0x0B)
#define GPIO_PIN_SOURCE12    ((uint8_t)0x0C)
#define GPIO_PIN_SOURCE13    ((uint8_t)0x0D)
#define GPIO_PIN_SOURCE14    ((uint8_t)0x0E)
#define GPIO_PIN_SOURCE15    ((uint8_t)0x0F)

/** EXTI external interrupt input source **/
#define AFIO_EXTI_PA0        (AFIO_EXTI_CFG1_EXTI0_PA0)
#define AFIO_EXTI_PB0        (AFIO_EXTI_CFG1_EXTI0_PB0)
#define AFIO_EXTI_PD0        (AFIO_EXTI_CFG1_EXTI0_PD0)
#define AFIO_EXTI_PA1        (AFIO_EXTI_CFG1_EXTI0_PA1)
#define AFIO_EXTI_PB1        (AFIO_EXTI_CFG1_EXTI0_PB1)
#define AFIO_EXTI_PA2        (AFIO_EXTI_CFG1_EXTI0_PA2)
#define AFIO_EXTI_PB2        (AFIO_EXTI_CFG1_EXTI0_PB2)
#define AFIO_EXTI_PA3        (AFIO_EXTI_CFG1_EXTI0_PA3)
#define AFIO_EXTI_PB3        (AFIO_EXTI_CFG1_EXTI0_PB3)

#define AFIO_EXTI_PA4        (AFIO_EXTI_CFG1_EXTI0_PA4)
#define AFIO_EXTI_PB4        (AFIO_EXTI_CFG1_EXTI0_PB4)
#define AFIO_EXTI_PA5        (AFIO_EXTI_CFG1_EXTI0_PA5)
#define AFIO_EXTI_PB5        (AFIO_EXTI_CFG1_EXTI0_PB5)
#define AFIO_EXTI_PA6        (AFIO_EXTI_CFG1_EXTI0_PA6)
#define AFIO_EXTI_PB6        (AFIO_EXTI_CFG1_EXTI0_PB6)
#define AFIO_EXTI_PA7        (AFIO_EXTI_CFG1_EXTI0_PA7)
#define AFIO_EXTI_PB7        (AFIO_EXTI_CFG1_EXTI0_PB7)

#define AFIO_EXTI_PA8        (AFIO_EXTI_CFG1_EXTI0_PA8)
#define AFIO_EXTI_PB8        (AFIO_EXTI_CFG1_EXTI0_PB8)
#define AFIO_EXTI_PA9        (AFIO_EXTI_CFG1_EXTI0_PA9)
#define AFIO_EXTI_PB9        (AFIO_EXTI_CFG1_EXTI0_PB9)
#define AFIO_EXTI_PA10       (AFIO_EXTI_CFG1_EXTI0_PA10)
#define AFIO_EXTI_PB10       (AFIO_EXTI_CFG1_EXTI0_PB10)
#define AFIO_EXTI_PA11       (AFIO_EXTI_CFG1_EXTI0_PA11)
#define AFIO_EXTI_PB11       (AFIO_EXTI_CFG1_EXTI0_PB11)

#define AFIO_EXTI_PA12       (AFIO_EXTI_CFG1_EXTI0_PA12)
#define AFIO_EXTI_PB12       (AFIO_EXTI_CFG1_EXTI0_PB12)
#define AFIO_EXTI_PD12       (AFIO_EXTI_CFG1_EXTI0_PD12)
#define AFIO_EXTI_PA13       (AFIO_EXTI_CFG1_EXTI0_PA13)
#define AFIO_EXTI_PB13       (AFIO_EXTI_CFG1_EXTI0_PB13)
#define AFIO_EXTI_PC13       (AFIO_EXTI_CFG1_EXTI0_PC13)
#define AFIO_EXTI_PD13       (AFIO_EXTI_CFG1_EXTI0_PD13)
#define AFIO_EXTI_PA14       (AFIO_EXTI_CFG1_EXTI0_PA14)
#define AFIO_EXTI_PB14       (AFIO_EXTI_CFG1_EXTI0_PB14)
#define AFIO_EXTI_PC14       (AFIO_EXTI_CFG1_EXTI0_PC14)
#define AFIO_EXTI_PD14       (AFIO_EXTI_CFG1_EXTI0_PD14)
#define AFIO_EXTI_PA15       (AFIO_EXTI_CFG1_EXTI0_PA15)
#define AFIO_EXTI_PB15       (AFIO_EXTI_CFG1_EXTI0_PB15)
#define AFIO_EXTI_PC15       (AFIO_EXTI_CFG1_EXTI0_PC15)
#define AFIO_EXTI_PD15       (AFIO_EXTI_CFG1_EXTI0_PD15)

/** EXTI line define **/
#define EXTI_LINE_0   ((uint16_t)0x0001U) /* EXTI0  */
#define EXTI_LINE_1   ((uint16_t)0x0002U) /* EXTI1  */
#define EXTI_LINE_2   ((uint16_t)0x0004U) /* EXTI2  */
#define EXTI_LINE_3   ((uint16_t)0x0008U) /* EXTI3  */
#define EXTI_LINE_4   ((uint16_t)0x0010U) /* EXTI4  */
#define EXTI_LINE_5   ((uint16_t)0x0020U) /* EXTI5  */
#define EXTI_LINE_6   ((uint16_t)0x0040U) /* EXTI6  */
#define EXTI_LINE_7   ((uint16_t)0x0080U) /* EXTI7  */
#define EXTI_LINE_8   ((uint16_t)0x0100U) /* EXTI8  */
#define EXTI_LINE_9   ((uint16_t)0x0200U) /* EXTI9  */
#define EXTI_LINE_10  ((uint16_t)0x0400U) /* EXTI10 */
#define EXTI_LINE_11  ((uint16_t)0x0800U) /* EXTI11 */
#define EXTI_LINE_12  ((uint16_t)0x1000U) /* EXTI12 */
#define EXTI_LINE_13  ((uint16_t)0x2000U) /* EXTI13 */
#define EXTI_LINE_14  ((uint16_t)0x4000U) /* EXTI14 */
#define EXTI_LINE_15  ((uint16_t)0x8000U) /* EXTI15 */
#define EXTI_LINE_ALL ((uint16_t)0xFFFFU) /* All EXTI line */

/** EXTI line sources **/
#define EXTI_LINE_SOURCE0    ((uint8_t)0x00) /* EXTI_line_0  */
#define EXTI_LINE_SOURCE1    ((uint8_t)0x01) /* EXTI_line_1  */
#define EXTI_LINE_SOURCE2    ((uint8_t)0x02) /* EXTI_line_2  */
#define EXTI_LINE_SOURCE3    ((uint8_t)0x03) /* EXTI_line_3  */
#define EXTI_LINE_SOURCE4    ((uint8_t)0x04) /* EXTI_line_4  */
#define EXTI_LINE_SOURCE5    ((uint8_t)0x05) /* EXTI_line_5  */
#define EXTI_LINE_SOURCE6    ((uint8_t)0x06) /* EXTI_line_6  */
#define EXTI_LINE_SOURCE7    ((uint8_t)0x07) /* EXTI_line_7  */
#define EXTI_LINE_SOURCE8    ((uint8_t)0x08) /* EXTI_line_8  */
#define EXTI_LINE_SOURCE9    ((uint8_t)0x09) /* EXTI_line_9  */
#define EXTI_LINE_SOURCE10   ((uint8_t)0x0A) /* EXTI_line_10 */
#define EXTI_LINE_SOURCE11   ((uint8_t)0x0B) /* EXTI_line_11 */
#define EXTI_LINE_SOURCE12   ((uint8_t)0x0C) /* EXTI_line_12 */
#define EXTI_LINE_SOURCE13   ((uint8_t)0x0D) /* EXTI_line_13 */
#define EXTI_LINE_SOURCE14   ((uint8_t)0x0E) /* EXTI_line_14 */
#define EXTI_LINE_SOURCE15   ((uint8_t)0x0F) /* EXTI_line_15 */

/** Filter stage control define **/
#define AFIO_IOFITCFG        ((uint8_t)0x00)

/** AFIO EFT sources **/
#define AFIO_PA0_EFT         (AFIO_EFT_CFG1_PA0EFTEN)      
#define AFIO_PA1_EFT         (AFIO_EFT_CFG1_PA1EFTEN)   
#define AFIO_PA2_EFT         (AFIO_EFT_CFG1_PA2EFTEN)   
#define AFIO_PA3_EFT         (AFIO_EFT_CFG1_PA3EFTEN)    
#define AFIO_PA4_EFT         (AFIO_EFT_CFG1_PA4EFTEN)    
#define AFIO_PA5_EFT         (AFIO_EFT_CFG1_PA5EFTEN)    
#define AFIO_PA6_EFT         (AFIO_EFT_CFG1_PA6EFTEN)    
#define AFIO_PA7_EFT         (AFIO_EFT_CFG1_PA7EFTEN)    
#define AFIO_PA8_EFT         (AFIO_EFT_CFG1_PA8EFTEN)    
#define AFIO_PA9_EFT         (AFIO_EFT_CFG1_PA9EFTEN)      
#define AFIO_PA10_EFT        (AFIO_EFT_CFG1_PA10EFTEN)    
#define AFIO_PA11_EFT        (AFIO_EFT_CFG1_PA11EFTEN)    
#define AFIO_PA12_EFT        (AFIO_EFT_CFG1_PA12EFTEN)    
#define AFIO_PA13_EFT        (AFIO_EFT_CFG1_PA13EFTEN)    
#define AFIO_PA14_EFT        (AFIO_EFT_CFG1_PA14EFTEN)   
#define AFIO_PA15_EFT        (AFIO_EFT_CFG1_PA15EFTEN) 
#define AFIO_PB0_EFT         (AFIO_EFT_CFG1_PB0EFTEN)     
#define AFIO_PB1_EFT         (AFIO_EFT_CFG1_PB1EFTEN)   
#define AFIO_PB2_EFT         (AFIO_EFT_CFG1_PB2EFTEN)   
#define AFIO_PB3_EFT         (AFIO_EFT_CFG1_PB3EFTEN)   
#define AFIO_PB4_EFT         (AFIO_EFT_CFG1_PB4EFTEN)   
#define AFIO_PB5_EFT         (AFIO_EFT_CFG1_PB5EFTEN)    
#define AFIO_PB6_EFT         (AFIO_EFT_CFG1_PB6EFTEN)    
#define AFIO_PB7_EFT         (AFIO_EFT_CFG1_PB7EFTEN)   
#define AFIO_PB8_EFT         (AFIO_EFT_CFG1_PB8EFTEN)    
#define AFIO_PB9_EFT         (AFIO_EFT_CFG1_PB9EFTEN)   
#define AFIO_PB10_EFT        (AFIO_EFT_CFG1_PB10EFTEN)    
#define AFIO_PB11_EFT        (AFIO_EFT_CFG1_PB11EFTEN)   
#define AFIO_PB12_EFT        (AFIO_EFT_CFG1_PB12EFTEN)    
#define AFIO_PB13_EFT        (AFIO_EFT_CFG1_PB13EFTEN)   
#define AFIO_PB14_EFT        (AFIO_EFT_CFG1_PB14EFTEN)    
#define AFIO_PB15_EFT        (AFIO_EFT_CFG1_PB15EFTEN)  
#define AFIO_PC13_EFT        (AFIO_EFT_CFG2_PC13EFTEN)    
#define AFIO_PC14_EFT        (AFIO_EFT_CFG2_PC14EFTEN)    
#define AFIO_PC15_EFT        (AFIO_EFT_CFG2_PC15EFTEN)    
#define AFIO_PD0_EFT         (AFIO_EFT_CFG2_PD0EFTEN)    
#define AFIO_PD12_EFT        (AFIO_EFT_CFG2_PD12EFTEN)   
#define AFIO_PD13_EFT        (AFIO_EFT_CFG2_PD13EFTEN)    
#define AFIO_PD14_EFT        (AFIO_EFT_CFG2_PD14EFTEN)    
#define AFIO_PD15_EFT        (AFIO_EFT_CFG2_PD15EFTEN)  

/** AFIO DIGEFT sources **/
#define AFIO_PA0_DIGEFT      (AFIO_DIGEFT_CFG1_PA0EFTEN)       
#define AFIO_PA1_DIGEFT      (AFIO_DIGEFT_CFG1_PA1EFTEN)    
#define AFIO_PA2_DIGEFT      (AFIO_DIGEFT_CFG1_PA2EFTEN)    
#define AFIO_PA3_DIGEFT      (AFIO_DIGEFT_CFG1_PA3EFTEN)     
#define AFIO_PA4_DIGEFT      (AFIO_DIGEFT_CFG1_PA4EFTEN)     
#define AFIO_PA5_DIGEFT      (AFIO_DIGEFT_CFG1_PA5EFTEN)     
#define AFIO_PA6_DIGEFT      (AFIO_DIGEFT_CFG1_PA6EFTEN)     
#define AFIO_PA7_DIGEFT      (AFIO_DIGEFT_CFG1_PA7EFTEN)     
#define AFIO_PA8_DIGEFT      (AFIO_DIGEFT_CFG1_PA8EFTEN)     
#define AFIO_PA9_DIGEFT      (AFIO_DIGEFT_CFG1_PA9EFTEN)       
#define AFIO_PA10_DIGEFT     (AFIO_DIGEFT_CFG1_PA10EFTEN)    
#define AFIO_PA11_DIGEFT     (AFIO_DIGEFT_CFG1_PA11EFTEN)    
#define AFIO_PA12_DIGEFT     (AFIO_DIGEFT_CFG1_PA12EFTEN)    
#define AFIO_PA13_DIGEFT     (AFIO_DIGEFT_CFG1_PA13EFTEN)    
#define AFIO_PA14_DIGEFT     (AFIO_DIGEFT_CFG1_PA14EFTEN)   
#define AFIO_PA15_DIGEFT     (AFIO_DIGEFT_CFG1_PA15EFTEN) 
#define AFIO_PB0_DIGEFT      (AFIO_DIGEFT_CFG1_PB0EFTEN)      
#define AFIO_PB1_DIGEFT      (AFIO_DIGEFT_CFG1_PB1EFTEN)    
#define AFIO_PB2_DIGEFT      (AFIO_DIGEFT_CFG1_PB2EFTEN)    
#define AFIO_PB3_DIGEFT      (AFIO_DIGEFT_CFG1_PB3EFTEN)    
#define AFIO_PB4_DIGEFT      (AFIO_DIGEFT_CFG1_PB4EFTEN)    
#define AFIO_PB5_DIGEFT      (AFIO_DIGEFT_CFG1_PB5EFTEN)     
#define AFIO_PB6_DIGEFT      (AFIO_DIGEFT_CFG1_PB6EFTEN)     
#define AFIO_PB7_DIGEFT      (AFIO_DIGEFT_CFG1_PB7EFTEN)    
#define AFIO_PB8_DIGEFT      (AFIO_DIGEFT_CFG1_PB8EFTEN)     
#define AFIO_PB9_DIGEFT      (AFIO_DIGEFT_CFG1_PB9EFTEN)    
#define AFIO_PB10_DIGEFT     (AFIO_DIGEFT_CFG1_PB10EFTEN)    
#define AFIO_PB11_DIGEFT     (AFIO_DIGEFT_CFG1_PB11EFTEN)   
#define AFIO_PB12_DIGEFT     (AFIO_DIGEFT_CFG1_PB12EFTEN)    
#define AFIO_PB13_DIGEFT     (AFIO_DIGEFT_CFG1_PB13EFTEN)   
#define AFIO_PB14_DIGEFT     (AFIO_DIGEFT_CFG1_PB14EFTEN)    
#define AFIO_PB15_DIGEFT     (AFIO_DIGEFT_CFG1_PB15EFTEN)  
#define AFIO_PC13_DIGEFT     (AFIO_DIGEFT_CFG2_PC13EFTEN)    
#define AFIO_PC14_DIGEFT     (AFIO_DIGEFT_CFG2_PC14EFTEN)    
#define AFIO_PC15_DIGEFT     (AFIO_DIGEFT_CFG2_PC15EFTEN)    
#define AFIO_PD0_DIGEFT      (AFIO_DIGEFT_CFG2_PD0EFTEN)     
#define AFIO_PD12_DIGEFT     (AFIO_DIGEFT_CFG2_PD12EFTEN)   
#define AFIO_PD13_DIGEFT     (AFIO_DIGEFT_CFG2_PD13EFTEN)    
#define AFIO_PD14_DIGEFT     (AFIO_DIGEFT_CFG2_PD14EFTEN)    
#define AFIO_PD15_DIGEFT     (AFIO_DIGEFT_CFG2_PD15EFTEN)  


/** Port pin 5V tolerance enable mask **/
#define PA0_5V_TOLERANCE     (AFIO_5VTOL_CFG_PA0TOLENN)
#define PA1_5V_TOLERANCE     (AFIO_5VTOL_CFG_PA1TOLENN)
#define PA2_5V_TOLERANCE     (AFIO_5VTOL_CFG_PA2TOLENN)
#define PA3_5V_TOLERANCE     (AFIO_5VTOL_CFG_PA3TOLENN)
#define PA4_5V_TOLERANCE     (AFIO_5VTOL_CFG_PA4TOLENN)
#define PA5_5V_TOLERANCE     (AFIO_5VTOL_CFG_PA5TOLENN)
#define PA6_5V_TOLERANCE     (AFIO_5VTOL_CFG_PA6TOLENN)
#define PA7_5V_TOLERANCE     (AFIO_5VTOL_CFG_PA7TOLENN)
#define PA8_5V_TOLERANCE     (AFIO_5VTOL_CFG_PA8TOLENN)
#define PA11_5V_TOLERANCE    (AFIO_5VTOL_CFG_PA11TOLENN)
#define PA12_5V_TOLERANCE    (AFIO_5VTOL_CFG_PA12TOLENN)
#define PA15_5V_TOLERANCE    (AFIO_5VTOL_CFG_PA15TOLENN)
#define PB0_5V_TOLERANCE     (AFIO_5VTOL_CFG_PB0TOLENN)
#define PB1_5V_TOLERANCE     (AFIO_5VTOL_CFG_PB1TOLENN)
#define PB2_5V_TOLERANCE     (AFIO_5VTOL_CFG_PB2TOLENN)
#define PB3_5V_TOLERANCE     (AFIO_5VTOL_CFG_PB3TOLENN)
#define PB4_5V_TOLERANCE     (AFIO_5VTOL_CFG_PB4TOLENN)
#define PB5_5V_TOLERANCE     (AFIO_5VTOL_CFG_PB5TOLENN)
#define PB7_5V_TOLERANCE     (AFIO_5VTOL_CFG_PB7TOLENN)
#define PB10_5V_TOLERANCE    (AFIO_5VTOL_CFG_PB10TOLENN)
#define PB11_5V_TOLERANCE    (AFIO_5VTOL_CFG_PB11TOLENN)
#define PB12_5V_TOLERANCE    (AFIO_5VTOL_CFG_PB12TOLENN)
#define PB13_5V_TOLERANCE    (AFIO_5VTOL_CFG_PB13TOLENN)
#define PB14_5V_TOLERANCE    (AFIO_5VTOL_CFG_PB14TOLENN)
#define PB15_5V_TOLERANCE    (AFIO_5VTOL_CFG_PB15TOLENN)

/** GPIOx_Alternate_function_selection Alternate function selection **/

/** Alternate function AF0 **/
#define ALTERNATE_FUN_0      ((uint8_t)0x00U)
#define GPIO_AF0_SWDIO_JTMS  (ALTERNATE_FUN_0) /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK_JTCK  (ALTERNATE_FUN_0) /* SWCLK Alternate Function mapping    */
#define GPIO_AF0_JTDI        (ALTERNATE_FUN_0) /* JTDI  Alternate Function mapping    */
#define GPIO_AF0_JTDO        (ALTERNATE_FUN_0) /* JTDO  Alternate Function mapping    */
#define GPIO_AF0_NJRST       (ALTERNATE_FUN_0) /* NJRST Alternate Function mapping    */

/** Alternate function AF1 **/
#define ALTERNATE_FUN_1      ((uint8_t)0x01U)
#define GPIO_AF1_SPI1        (ALTERNATE_FUN_1) /* SPI1 Alternate Function mapping     */
#define GPIO_AF1_SPI2        (ALTERNATE_FUN_1) /* SPI2 Alternate Function mapping     */
#define GPIO_AF1_TIM8        (ALTERNATE_FUN_1) /* TIM8 Alternate Function mapping     */
#define GPIO_AF1_USART1      (ALTERNATE_FUN_1) /* USART1 Alternate Function mapping   */

/** Alternate function AF2 **/
#define ALTERNATE_FUN_2      ((uint8_t)0x02U)
#define GPIO_AF2_TIM5        (ALTERNATE_FUN_2) /* TIM5 Alternate Function mapping     */
#define GPIO_AF2_TIM1        (ALTERNATE_FUN_2) /* TIM1 Alternate Function mapping     */
#define GPIO_AF2_USART1      (ALTERNATE_FUN_2) /* USART1 Alternate Function mapping   */
#define GPIO_AF2_I2C2        (ALTERNATE_FUN_2) /* I2C2 Alternate Function mapping     */
#define GPIO_AF2_CAN         (ALTERNATE_FUN_2) /* CAN Alternate Function mapping      */
#define GPIO_AF2_SPI2        (ALTERNATE_FUN_2) /* SPI2 Alternate Function mapping     */
#define GPIO_AF2_SPI1        (ALTERNATE_FUN_2) /* SPI1 Alternate Function mapping     */
#define GPIO_AF2_I2C1        (ALTERNATE_FUN_2) /* I2C1 Alternate Function mapping     */

/** Alternate function AF3 **/
#define ALTERNATE_FUN_3      ((uint8_t)0x03U)
#define GPIO_AF3_TIM2        (ALTERNATE_FUN_3) /* TIM2 Alternate Function mapping     */
#define GPIO_AF3_SPI2        (ALTERNATE_FUN_3) /* SPI2 Alternate Function mapping     */
#define GPIO_AF3_TIM3        (ALTERNATE_FUN_3) /* TIM3 Alternate Function mapping     */
#define GPIO_AF3_TIM1        (ALTERNATE_FUN_3) /* TIM1 Alternate Function mapping     */
#define GPIO_AF3_LPTIM       (ALTERNATE_FUN_3) /* LPTIM Alternate Function mapping    */
#define GPIO_AF3_TIM4        (ALTERNATE_FUN_3) /* TIM4 Alternate Function mapping     */

/** Alternate function AF4 **/
#define ALTERNATE_FUN_4      ((uint8_t)0x04U)
#define GPIO_AF4_EVENTOUT    (ALTERNATE_FUN_4) /* EVENTOUT Alternate Function mapping */
#define GPIO_AF4_USART2      (ALTERNATE_FUN_4) /* USART2 Alternate Function mapping   */

/** Alternate function AF5 **/
#define ALTERNATE_FUN_5      ((uint8_t)0x05U)
#define GPIO_AF5_USART2      (ALTERNATE_FUN_5) /* USART2 Alternate Function mapping   */
#define GPIO_AF5_USART1      (ALTERNATE_FUN_5) /* USART1 Alternate Function mapping   */
#define GPIO_AF5_SPI1        (ALTERNATE_FUN_5) /* SPI1 Alternate Function mapping     */
#define GPIO_AF5_TIM3        (ALTERNATE_FUN_5) /* TIM3 Alternate Function mapping     */
#define GPIO_AF5_SPI2        (ALTERNATE_FUN_5) /* SPI2 Alternate Function mapping     */
#define GPIO_AF5_I2C1        (ALTERNATE_FUN_5) /* I2C1 Alternate Function mapping     */

/** Alternate function AF6 **/
#define ALTERNATE_FUN_6      ((uint8_t)0x06U)
#define GPIO_AF6_TIM2        (ALTERNATE_FUN_6) /* TIM2 Alternate Function mapping     */
#define GPIO_AF6_I2C2        (ALTERNATE_FUN_6) /* I2C2 Alternate Function mapping     */
#define GPIO_AF6_TIM4        (ALTERNATE_FUN_6) /* TIM4 Alternate Function mapping     */
#define GPIO_AF6_TIM1        (ALTERNATE_FUN_6) /* TIM1 Alternate Function mapping     */
#define GPIO_AF6_SPI1        (ALTERNATE_FUN_6) /* SPI1 Alternate Function mapping     */
#define GPIO_AF6_SPI2        (ALTERNATE_FUN_6) /* SPI2 Alternate Function mapping     */
#define GPIO_AF6_LPTIM       (ALTERNATE_FUN_6) /* LPTIM Alternate Function mapping    */
#define GPIO_AF6_CAN         (ALTERNATE_FUN_6) /* CAN Alternate Function mapping      */
#define GPIO_AF6_UART4       (ALTERNATE_FUN_6) /* UART4 Alternate Function mapping    */

/** Alternate function AF7 **/
#define ALTERNATE_FUN_7      ((uint8_t)0x07U)
#define GPIO_AF7_TIM5        (ALTERNATE_FUN_7) /* TIM5 Alternate Function mapping     */
#define GPIO_AF7_TIM8        (ALTERNATE_FUN_7) /* TIM8 Alternate Function mapping     */
#define GPIO_AF7_I2C2        (ALTERNATE_FUN_7) /* I2C2 Alternate Function mapping     */
#define GPIO_AF7_USART2      (ALTERNATE_FUN_7) /* USART2 Alternate Function mapping   */
#define GPIO_AF7_UART4       (ALTERNATE_FUN_7) /* UART4 Alternate Function mapping    */
#define GPIO_AF7_UART3       (ALTERNATE_FUN_7) /* UART3 Alternate Function mapping    */
#define GPIO_AF7_TIM1        (ALTERNATE_FUN_7) /* TIM1 Alternate Function mapping     */
#define GPIO_AF7_I2C1        (ALTERNATE_FUN_7) /* I2C1 Alternate Function mapping     */

/** Alternate function AF8 **/
#define ALTERNATE_FUN_8      ((uint8_t)0x08U)
#define GPIO_AF8_TIM8        (ALTERNATE_FUN_8) /* TIM8 Alternate Function mapping     */
#define GPIO_AF8_TIM5        (ALTERNATE_FUN_8) /* TIM5 Alternate Function mapping     */
#define GPIO_AF8_COMP2       (ALTERNATE_FUN_8) /* COMP2 Alternate Function mapping    */
#define GPIO_AF8_I2C1        (ALTERNATE_FUN_8) /* I2C1 Alternate Function mapping     */
#define GPIO_AF8_TIM1        (ALTERNATE_FUN_8) /* TIM1 Alternate Function mapping     */
#define GPIO_AF8_COMP1       (ALTERNATE_FUN_8) /* COMP1 Alternate Function mapping    */
#define GPIO_AF8_UART3       (ALTERNATE_FUN_8) /* UART3 Alternate Function mapping    */

/** Alternate function AF9 **/
#define ALTERNATE_FUN_9      ((uint8_t)0x09U)
#define GPIO_AF9_COMP1       (ALTERNATE_FUN_9) /* COMP1 Alternate Function mapping    */
#define GPIO_AF9_TIM8        (ALTERNATE_FUN_9) /* TIM8 Alternate Function mapping     */
#define GPIO_AF9_TIM4        (ALTERNATE_FUN_9) /* TIM4 Alternate Function mapping     */
#define GPIO_AF9_MCO         (ALTERNATE_FUN_9) /* MCO Alternate Function mapping      */
#define GPIO_AF9_RTC         (ALTERNATE_FUN_9) /* RTC Alternate Function mapping      */
#define GPIO_AF9_COMP2       (ALTERNATE_FUN_9) /* COMP2 Alternate Function mapping    */
#define GPIO_AF9_LPTIM       (ALTERNATE_FUN_9) /* LPTIM Alternate Function mapping    */
#define GPIO_AF9_I2C2        (ALTERNATE_FUN_9) /* I2C2 Alternate Function mapping     */
#define GPIO_AF9_TIMESTAMP   (ALTERNATE_FUN_9) /* TIMESTAMP Alternate Function mapping */

/** Alternate function AF10 **/
#define ALTERNATE_FUN_10     ((uint8_t)0x0AU)
#define GPIO_AF10_TIM1       (ALTERNATE_FUN_10) /* TIM1 Alternate Function mapping     */
#define GPIO_AF10_TIM8       (ALTERNATE_FUN_10) /* TIM8 Alternate Function mapping     */
#define GPIO_AF10_COMP3      (ALTERNATE_FUN_10) /* COMP3 Alternate Function mapping    */
#define GPIO_AF10_TIM4       (ALTERNATE_FUN_10) /* TIM4 Alternate Function mapping     */
#define GPIO_AF10_COMP1      (ALTERNATE_FUN_10) /* COMP1 Alternate Function mapping    */
#define GPIO_AF10_UART3      (ALTERNATE_FUN_10) /* UART3 Alternate Function mapping    */

/** Alternate function AF11 **/
#define ALTERNATE_FUN_11     ((uint8_t)0x0BU)
#define GPIO_AF11_UART4      (ALTERNATE_FUN_11) /* UART4 Alternate Function mapping    */
#define GPIO_AF11_CAN        (ALTERNATE_FUN_11) /* CAN Alternate Function mapping      */
#define GPIO_AF11_USART2     (ALTERNATE_FUN_11) /* USART2 Alternate Function mapping   */
#define GPIO_AF11_TIM8       (ALTERNATE_FUN_11) /* TIM8 Alternate Function mapping     */
#define GPIO_AF11_COMP3      (ALTERNATE_FUN_11) /* COMP3 Alternate Function mapping    */

/** Alternate function AF12 **/
#define ALTERNATE_FUN_12     ((uint8_t)0x0CU)
#define GPIO_AF12_LPTIM      (ALTERNATE_FUN_12) /* LPTIM Alternate Function mapping    */
#define GPIO_AF12_BEEPER     (ALTERNATE_FUN_12) /* BEEPER Alternate Function mapping   */

/** Alternate function AF13 **/
#define ALTERNATE_FUN_13     ((uint8_t)0x0DU)
#define GPIO_AF13_TIM3       (ALTERNATE_FUN_13) /* TIM3 Alternate Function mapping     */
#define GPIO_AF13_TIM8       (ALTERNATE_FUN_13) /* TIM8 Alternate Function mapping     */
#define GPIO_AF13_TIM4       (ALTERNATE_FUN_13) /* TIM4 Alternate Function mapping     */
#define GPIO_AF13_TIM5       (ALTERNATE_FUN_13) /* TIM5 Alternate Function mapping     */

/** Alternate function AF15 **/
#define ALTERNATE_FUN_15     ((uint8_t)0x0FU)  /* NON Alternate Function mapping     */

#define GPIO_NO_AF           (ALTERNATE_FUN_15)

/** SPI mode definition in AFIO register  **/
#define AFIO_SPI1_NSS        ((uint32_t)AFIO_RMP_CFG_SPI1_NSS)
#define AFIO_SPI2_NSS        ((uint32_t)AFIO_RMP_CFG_SPI2_NSS)

#define AFIO_SPI_NSS_HIGH_IMPEDANCE  (0x0UL)
#define AFIO_SPI_NSS_High_LEVEL      (0x1UL)

/** ADC mode definition in AFIO register  **/
typedef enum
{
    AFIO_ADC_ETRI = 9U,
    AFIO_ADC_ETRR = 8U
}AFIO_ADC_ETRType;

typedef enum
{
    AFIO_ADC_TRIG_EXTI_0 = 0x00U,
    AFIO_ADC_TRIG_EXTI_1 = 0x01U,
    AFIO_ADC_TRIG_EXTI_2,
    AFIO_ADC_TRIG_EXTI_3,
    AFIO_ADC_TRIG_EXTI_4,
    AFIO_ADC_TRIG_EXTI_5,
    AFIO_ADC_TRIG_EXTI_6,
    AFIO_ADC_TRIG_EXTI_7,
    AFIO_ADC_TRIG_EXTI_8,
    AFIO_ADC_TRIG_EXTI_9,
    AFIO_ADC_TRIG_EXTI_10,
    AFIO_ADC_TRIG_EXTI_11,
    AFIO_ADC_TRIG_EXTI_12,
    AFIO_ADC_TRIG_EXTI_13,
    AFIO_ADC_TRIG_EXTI_14,
    AFIO_ADC_TRIG_EXTI_15,
    AFIO_ADC_TRIG_TIM8_TRGO,
    AFIO_ADC_TRIG_TIM8_CH4
}AFIO_ADC_Trig_RemapType;



/** GPIO_Exported_Functions **/
void GPIOA_Pin_Reset(uint16_t pin);
void GPIOB_Pin_Reset(uint16_t pin);
void GPIOC_Pin_Reset(uint16_t pin);
void GPIOD_Pin_Reset(uint16_t pin);
void AFIO_EXTI_Reset(uint16_t EXTI_line);
void GPIO_ALLPin_Reset(void);

void GPIO_Reset(GPIO_Module* GPIOx);
void GPIO_Alternate_Function_Reset(void);

void GPIO_Alternate_Set(GPIO_Module* GPIOx, uint32_t alternate, uint32_t position);
void GPIO_Mode_Set(GPIO_Module* GPIOx, uint32_t mode, uint32_t position);
void GPIO_Pull_Set(GPIO_Module* GPIOx, uint32_t pull, uint32_t position);
void GPIO_SlewRate_Set(GPIO_Module* GPIOx, uint32_t slew_rate, uint32_t position);
void GPIO_Driver_Set(GPIO_Module* GPIOx, uint32_t current, uint32_t position);
void GPIO_Peripheral_Initialize(GPIO_Module* GPIOx, GPIO_InitType* GPIO_InitStructure);
void GPIO_Structure_Initialize(GPIO_InitType* GPIO_InitStruct);

uint8_t GPIO_Input_Pin_Data_Get(GPIO_Module* GPIOx, uint16_t pin);
uint16_t GPIO_Input_Data_Get(GPIO_Module* GPIOx);
uint8_t GPIO_Output_Pin_Data_Get(GPIO_Module* GPIOx, uint16_t pin);
uint16_t GPIO_Output_Data_Get(GPIO_Module* GPIOx);
void GPIO_Pins_Set(GPIO_Module* GPIOx, uint16_t pin);
void GPIO_Pins_Reset(GPIO_Module* GPIOx, uint16_t pin);
void GPIO_PBSC_Pins_Reset(GPIO_Module* GPIOx, uint16_t pin);
void GPIO_PBC_Pins_Reset(GPIO_Module* GPIOx, uint16_t pin);
void GPIO_Write(GPIO_Module* GPIOx, uint16_t data_value);
void GPIO_Pin_Toggle(GPIO_Module* GPIOx, uint16_t pin);
void GPIO_Pin_Lock_Set(GPIO_Module* GPIOx, uint16_t pin);

void GPIO_Pin_Remap_Set(uint8_t port_source, uint8_t pin_source, uint32_t alternate_function);
void GPIO_EXTI_Line_Set(uint8_t EXTI_line, uint32_t pin_source);
void AFIO_SPI_NSS_Mode_Set(uint32_t AFIO_SPIx_NSS, uint32_t SPI_nss_mode);
void AFIO_ADC_External_Trigger_Remap_Set(AFIO_ADC_ETRType ADC_ET_type, AFIO_ADC_Trig_RemapType ADC_trigger_remap);

void AFIO_5V_Tolerance_Enable(uint32_t tol_pin);
void AFIO_5V_Tolerance_Disable(uint32_t tol_pin);
void AFIO_Filter_Stage_Ctrl(uint8_t filter);
void AFIO_EFT_Enable(GPIO_Module* GPIOx, uint32_t EFT_pin_source);
void AFIO_EFT_Disable(GPIO_Module* GPIOx, uint32_t EFT_pin_source);
void AFIO_Digital_EFT_Enable(GPIO_Module* GPIOx, uint32_t digital_EFT_pin);
void AFIO_Digital_EFT_Disable(GPIO_Module* GPIOx, uint32_t digital_EFT_pin);


#ifdef __cplusplus
}
#endif

#endif /* __N32G430_GPIO_H__ */

