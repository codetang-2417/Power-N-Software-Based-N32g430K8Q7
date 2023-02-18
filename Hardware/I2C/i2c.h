#ifndef __I2C_H
#define __I2C_H
#include "n32g430.h"
#include "bsp_delay.h"

#define FS2711_SCL_Clr() 						GPIO_Pins_Reset(GPIOA,GPIO_PIN_12)
#define FS2711_SCL_Set() 						GPIO_Pins_Set(GPIOA,GPIO_PIN_12)
#define FS2711_SDA_Clr() 						GPIO_Pins_Reset(GPIOA,GPIO_PIN_11)
#define FS2711_SDA_Set() 						GPIO_Pins_Set(GPIOA,GPIO_PIN_11)

#define FS2711_SDA()		GPIO_Input_Pin_Data_Get(GPIOA,GPIO_PIN_11)

void FS2711_GPIO_Init(void);
void Write_IIC(unsigned char addr, unsigned char dat);
unsigned char Read_IIC(unsigned char addr);
void PinInInitSDA(void);
void PinOutInitSDA(void);

#endif
