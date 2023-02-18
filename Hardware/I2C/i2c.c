#include "i2c.h"

void delay(unsigned int num)
{
	SysTick_Delay_Us(num);
}

void FS2711_GPIO_Init(void)
{
	GPIO_InitType GPIO_InitStructure;

	RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_GPIOA);

	GPIO_Structure_Initialize(&GPIO_InitStructure);

	/* Select the GPIO pin to control */
	GPIO_InitStructure.Pin = GPIO_PIN_11 | GPIO_PIN_12;
	/* Set pin mode to general push-pull output */
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT_PP;
	/* Set the pin drive current to 4MA*/
	//	GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
	/* Initialize GPIO */
	GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);

	FS2711_SCL_Set();
	FS2711_SDA_Set();
}

void I2C_Start()
{
	PinOutInitSDA();
	FS2711_SCL_Set();
	delay(2);
	FS2711_SDA_Set();
	delay(2);
	FS2711_SDA_Clr();
	delay(2);
	FS2711_SCL_Clr();
}

void I2C_ReStart()
{
	PinOutInitSDA();
	FS2711_SCL_Set();
	delay(1);
	FS2711_SCL_Clr();
	delay(1);
	FS2711_SDA_Set();
	delay(1);
	FS2711_SCL_Set();
	delay(1);
	FS2711_SDA_Clr();
}

void I2C_Stop()
{
	PinOutInitSDA();
	FS2711_SDA_Clr();
	delay(1);
	FS2711_SCL_Set();
	delay(1);
	FS2711_SDA_Set();
}

void I2C_Wait_Ack()
{
	PinInInitSDA();
	FS2711_SCL_Set();
	delay(2);
	FS2711_SCL_Clr();
}

void Write_I2C_Byte(unsigned char I2C_Byte)
{
	unsigned char i;
	unsigned char da;
	PinOutInitSDA();
	da = I2C_Byte;
	FS2711_SCL_Clr();
	delay(1);
	for (i = 0; i < 8; i++)
	{
		if (0x80 == (da & 0x80))
		{
			FS2711_SDA_Set();
		}
		else
		{
			FS2711_SDA_Clr();
		}
		da = da << 1;
		FS2711_SCL_Set();
		delay(1);
		FS2711_SCL_Clr();
	}
	delay(1);
}

unsigned char Read_I2C_Byte(void)
{
	unsigned char i, da;
	PinInInitSDA();
	da = 0;
	FS2711_SCL_Clr();
	delay(1);
	for (i = 0; i < 8; i++)
	{
		if (FS2711_SDA())
		{
			da |= 1 << (7 - i);
		}
		FS2711_SCL_Set();
		delay(1);
		FS2711_SCL_Clr();
	}
	return da;
}

void Write_IIC(unsigned char addr, unsigned char dat)
{
	I2C_Start();
	Write_I2C_Byte(0x5A);
	I2C_Wait_Ack();
	Write_I2C_Byte(addr);
	I2C_Wait_Ack();
	Write_I2C_Byte(dat);
	I2C_Wait_Ack();
	I2C_Stop();
}

unsigned char Read_IIC(unsigned char addr)
{
	unsigned char dat;
	I2C_Start();
	Write_I2C_Byte(0x5A);
	I2C_Wait_Ack();
	Write_I2C_Byte(addr);
	I2C_ReStart();
	Write_I2C_Byte(0x5B);
	I2C_Wait_Ack();
	dat = Read_I2C_Byte();
	I2C_Wait_Ack();
	I2C_Stop();
	return dat;
}

void PinOutInitSDA(void)
{
	GPIO_InitType GPIO_InitStructure;

	RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_GPIOA);

	GPIO_Structure_Initialize(&GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_11;

	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT_PP;

	GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);
}

void PinInInitSDA(void)
{
	GPIO_InitType GPIO_InitStructure;

	RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_GPIOA);

	GPIO_Structure_Initialize(&GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_11;

	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;

	GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);
}
