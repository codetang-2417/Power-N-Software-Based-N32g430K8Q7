
#include "chip.h"
#include "bsp_delay.h"

extern FS2711_LIB_t FS2711_lib;

void delay(unsigned int num)
{
	//		unsigned int i;
	//		for(i=0;i<num;i++){
	//		}
	SysTick_Delay_Us(num);
}

// void SysTick_Delay_Ms(unsigned int num){
//		unsigned int i;
//		for(i=0;i<num;i++){
//				delay(2000);
//		}
// }

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
	unsigned char m, da;
	PinOutInitSDA();
	da = I2C_Byte;
	FS2711_SCL_Clr();
	delay(1);
	for (i = 0; i < 8; i++)
	{
		m = da;
		m = m & 0x80;
		if (m == 0x80)
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

void Write_IIC(unsigned char addr, unsigned dat)
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

void FS2711_GPIO_Init()
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
	
	FS2711_Enable_Protocol(0);/* 停止芯片发送协议，否则芯片会发送默认的协议 */
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

void main_app(u8 mode, u8 pdo_num, u16 max_v, u16 max_c)
{

	switch (mode)
	{
	case FS2711_APPLE_2P4A:
		break;
	case FS2711_SAMSUNG_2A:
		break;
	case FS2711_BC1P2:
		break;
	case FS2711_TYPEC:
		break;
	case FS2711_QC2A:
		break;
	case FS2711_QC2B:
		break;
	case FS2711_QC3A:
		break;
	case FS2711_QC3B:
		break;
	case FS2711_AFC:
		break;
	case FS2711_FCP:
		break;
	case FS2711_SCP:
		break;
	case FS2711_HISCP:
		break;
	case FS2711_VOOC2:
		break;
	case FS2711_SVOOC1:
		break;
	case FS2711_VOOC3:
		break;
	case FS2711_VOOC4:
		break;
	case FS2711_VIVO_5V4A:
		break;
	case FS2711_VIVO_10V2P25A:
		break;
	case FS2711_VIVO_11V4A:
		break;
	case FS2711_MTK:
		break;
	case FS2711_PPS:
		SysTick_Delay_Ms(500);
		FS2711_lib.req_pdo_num = 0;
		FS2711_Select_Protocol(FS2711_PD);
		FS2711_Enable_Protocol(1);
		SysTick_Delay_Ms(2000);
		FS2711_lib.req_pdo_num = 5;
		FS2711_Select_Voltage_Current(FS2711_PPS, 5000, 5000, 1000);
		FS2711_Enable_Protocol(1);
		SysTick_Delay_Ms(2000);
		FS2711_Select_Voltage_Current(FS2711_PPS, 6000, 6000, 1000);
		FS2711_Enable_Voltage_Current();
		break;
	case FS2711_PD:
		SysTick_Delay_Ms(500);
		FS2711_lib.req_pdo_num = 0;
		FS2711_Select_Protocol(FS2711_PD);
		FS2711_Enable_Protocol(1);
		SysTick_Delay_Ms(500);
		FS2711_lib.req_pdo_num = pdo_num;
		FS2711_Select_Voltage_Current(FS2711_PD, max_v, max_v, max_c);
		FS2711_Enable_Voltage_Current();
		break;

	default:
		FS2711_System_Reset();
		break;
	}
	//	  SysTick_Delay_Ms(500);
	//	  FS2711_lib.req_pdo_num = 0;
	//		FS2711_Select_Protocol(FS2711_PPS);
	//		FS2711_Enable_Protocol(1);
	//		SysTick_Delay_Ms(500);
	//		FS2711_lib.req_pdo_num = 1;
	//	  FS2711_Select_Voltage_Current(FS2711_PD, 0, 0, 1500);
	//	  FS2711_Enable_Voltage_Current();

	//		  SysTick_Delay_Ms(500);
	//	  FS2711_lib.req_pdo_num = 0;
	//		FS2711_Select_Protocol(FS2711_PPS);
	//		FS2711_Enable_Protocol(1);
	//		SysTick_Delay_Ms(500);
	////		FS2711_lib.req_pdo_num = 4; // select 3.3~12V1.5A
	////		FS2711_Select_Voltage_Current(FS2711_PPS,11000, 11000, 1500); //apply 11V1.5A
	////		FS2711_Enable_Voltage_Current();
	//		FS2711_lib.req_pdo_num = 2; // select 3.3~12V1.5A
	//		FS2711_Select_Voltage_Current(FS2711_PPS,12000, 12000, 1500); //apply 11V1.5A
	//		FS2711_Enable_Voltage_Current();

	//		  SysTick_Delay_Ms(500);
	//	  FS2711_lib.req_pdo_num = 0;
	//		FS2711_Select_Protocol(FS2711_PPS);
	//		FS2711_Enable_Protocol(1);
	//		SysTick_Delay_Ms(500);
	//		FS2711_lib.req_pdo_num = 1; //
	////		FS2711_lib.pdo_type = FS2711_PDO_PPS; //
	//		FS2711_Select_Voltage_Current(FS2711_PPS,5500, 5500, 1500); //apply 11V1.5A
	//		FS2711_Enable_Voltage_Current();
	//
	/**/
	//	SysTick_Delay_Ms(500);
	//		FS2711_Select_Protocol(FS2711_QC2A);
	//		FS2711_Enable_Protocol(1);
	//		SysTick_Delay_Ms(2000);
	//		FS2711_Select_Voltage_Current(FS2711_QC2A, 9000, 9000, 1000);
	//		FS2711_Enable_Voltage_Current();
}
