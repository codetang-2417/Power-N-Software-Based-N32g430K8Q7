#ifndef _FS2711_EXAMPLE_H_
#define _FS2711_EXAMPLE_H_

#include "n32g430.h"

#define FS2711_SCL_Clr() 						GPIO_Pins_Reset(GPIOA,GPIO_PIN_12)
#define FS2711_SCL_Set() 						GPIO_Pins_Set(GPIOA,GPIO_PIN_12)
#define FS2711_SDA_Clr() 						GPIO_Pins_Reset(GPIOA,GPIO_PIN_11)
#define FS2711_SDA_Set() 						GPIO_Pins_Set(GPIOA,GPIO_PIN_11)

#define FS2711_SDA()		GPIO_Input_Pin_Data_Get(GPIOA,GPIO_PIN_11)

void delay(unsigned int num);
//void delay_ms(unsigned int num);
void I2C_Start(void);
void I2C_ReStart(void);
void I2C_Stop(void);
void I2C_Wait_Ack(void);
void Write_I2C_Byte(unsigned char I2C_Byte);
unsigned char Read_I2C_Byte(void);
void Write_IIC(unsigned char addr, unsigned dat);
unsigned char Read_IIC(unsigned char addr);
void FS2711_GPIO_Init(void);
void PinOutInitSDA(void);
void PinInInitSDA(void);
void main_app(u8 mode,u8 pdo_num,u16 max_v,u16 max_c);	



#endif
