/**
 * @file FS2711.c
 * @author HYJ
 * @brief
 * @version 0.1
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "FS2711.h"

// PDO type
#define FS2711_PDO_FIX 0
#define FS2711_PDO_PPS 1

#define FS2711_MAX_5V 1
#define FS2711_MAX_9V 3
#define FS2711_MAX_12V 7
#define FS2711_MAX_20V 15

// Sweep mode
#define FS2711_SWEEP_SAW 0
#define FS2711_SWEEP_TRI 1
#define FS2711_SWEEP_STEP 2

/*!
华为快充协议：SCP、FCP、SSCP、HISCP
三星快充协议：AFC
OPPO快充协议：VOOC
联发科快充协议：BC、PE、MTK

*/

FS2711_Lib_t FS2711_Lib = {0};

#define FS2711_WRITE_ADDR 0x5a //<! FS2711地址
#define FS2711_READ_ADDR 0x5b  //<! FS2711地址

//<! 寄存器列表
#define FS2711_REG_SR 0x4a	   //<! 系统复位寄存器
#define FS2711_REG_MC 0xa0	   //<! 模式设置寄存器
#define FS2711_REG_PR 0x49	   //<! 端口复位寄存器
#define FS2711_REG_DPDM 0x51   //<! DPDM寄存器
#define FS2711_REG_SS 0x40	   //<! 协议扫描寄存器
#define FS2711_REG_STATE1 0xb2 //<! 状态寄存器1

void FS2711_Debug(char *file, int ln, char *msg)
{
	// printf("error file: %s\r\nerror line: %d\r\nerror message: %s\r\n", file, ln, msg);
	while (1)
		;
}

uint16_t FS2711_SCP_Calc(uint8_t val);

/**
 * @brief: FS2711写寄存器数据
 * @author: HYJ
 * @param regAddr: 寄存器地址
 * @param data: 待写入数据
 * @retval None
 */
void FS2711_Write(uint8_t regAddr, uint8_t data)
{
	/*
	uint8_t dataBuf = data;
	HAL_I2C_Mem_Write(&hi2c1, FS2711_WRITE_ADDR, regAddr, 1, &dataBuf, 1, HAL_MAX_DELAY);
	*/
	Write_IIC(regAddr, data);
}

/**
 * @brief: FS2711写寄存器数据
 * @author: HYJ
 * @param regAddr: 寄存器地址
 * @retval None
 */
uint8_t FS2711_Read(uint8_t regAddr)
{
	uint8_t data = 0;
	// HAL_I2C_Mem_Read(&hi2c1, FS2711_WRITE_ADDR, regAddr, 1, &data, 1, HAL_MAX_DELAY);
	data = Read_IIC(regAddr);
	return data;
}

/**
 * @brief: FS2711选择协议
 * @author: HYJ
 * @param protocol: 选择的协议
 * @retval None
 */
void FS2711_Select_Protocol(uint8_t protocol)
{
	if (protocol > 21)
	{
		FS2711_Debug(__FILE__, __LINE__, "protocol error");
	}
	FS2711_Write(0x42, protocol);
}

/**
 * @brief: FS2711启动协议
 * @author: HYJ
 * @param protocol: 选择的协议
 * @retval None
 */
void FS2711_Enable_Protocol(uint8_t ena)
{
	if (ena)
	{
		FS2711_Write(0x41, 0x1);
	}
	else
	{
		FS2711_Write(0x41, 0x2);
	}
}

/**
 * @brief: FS2711开启电压电流诱骗
 * @author: HYJ
 * @retval None
 */
void FS2711_Enable_Voltage_Current(void)
{
	FS2711_Write(0x43, 0x1);
}
/**
 * @brief: FS2711设置需要诱骗的电压电流
 * @author: HYJ
 * @param protocol: 选择的协议
 * @param start_volt: 开始电压
 * @param end_volt: 结束电压
 * @param max_curr: 最大电流
 * @retval None
 */
void FS2711_Select_Voltage_Current(uint8_t protocol, uint16_t start_volt, uint16_t end_volt, uint16_t max_curr)
{
	uint16_t wr_l, wr_h;

	if (protocol > 21)
	{
		FS2711_Debug(__FILE__, __LINE__, "Protocol error");
	}
	if (start_volt > end_volt)
	{
		FS2711_Debug(__FILE__, __LINE__, "Start Voltage > End Voltage");
	}

	switch (protocol)
	{
	case FS2711_PROTOCOL_QC2A:
	case FS2711_PROTOCOL_QC2B:
	case FS2711_PROTOCOL_AFC:
	case FS2711_PROTOCOL_FCP:
	{
		switch (start_volt)
		{
		case 5000:
			wr_l = 0x0;
			break;
		case 9000:
			wr_l = 0x1;
			break;
		case 12000:
			wr_l = 0x2;
			break;
		case 20000:
			wr_l = 0x3;
			break;
		default:
			FS2711_Debug(__FILE__, __LINE__, "Start Voltage error");
			break;
		}

		switch (end_volt)
		{
		case 5000:
			wr_h = 0x0;
			break;
		case 9000:
			wr_h = 0x1;
			break;
		case 12000:
			wr_h = 0x2;
			break;
		case 20000:
			wr_h = 0x3;
			break;
		default:
			FS2711_Debug(__FILE__, __LINE__, "End Voltage error");
			break;
		}

		break;
	}
	case FS2711_PROTOCOL_QC3A:
	case FS2711_PROTOCOL_QC3B:
	{
		wr_l = (start_volt - 3600) / 200;
		wr_h = (end_volt - 3600) / 200;
		break;
	}
	case FS2711_PROTOCOL_SCP:
	{
		wr_l = (start_volt - 3300) / 10;
		wr_h = (end_volt - 3300) / 10;
		break;
	}
	case FS2711_PROTOCOL_HISCP:
	{
		wr_l = (start_volt - 5500) / 10;
		wr_h = (end_volt - 5500) / 10;
		break;
	}
	case FS2711_PROTOCOL_VOOC2:
	case FS2711_PROTOCOL_VOOC3:
	case FS2711_PROTOCOL_VOOC4:
	{
		FS2711_Write(0xdc, start_volt);
		FS2711_Write(0xde, (max_curr - 3000) / 250);
		break;
	}
	case FS2711_PROTOCOL_SVOOC1:
	{
		FS2711_Write(0xdc, start_volt);
		FS2711_Write(0xde, max_curr / 100);
		break;
	}
	case FS2711_PROTOCOL_VIVO_5V4A:
	{
		wr_l = (start_volt - 4000) / 10;
		wr_h = (end_volt - 4000) / 10;
		break;
	}
	case FS2711_PROTOCOL_VIVO_10V2P25A:
	case FS2711_PROTOCOL_VIVO_11V4A:
	{
		wr_l = (start_volt - 7000) / 10;
		wr_h = (end_volt - 7000) / 10;
		break;
	}
	case FS2711_PROTOCOL_MTK:
	{
		switch (start_volt)
		{
		case 3600:
			wr_l = 0;
			break;
		case 3800:
			wr_l = 1;
			break;
		case 4000:
			wr_l = 2;
			break;
		case 4200:
			wr_l = 3;
			break;
		case 4400:
			wr_l = 4;
			break;
		case 4600:
			wr_l = 5;
			break;
		case 4800:
			wr_l = 6;
			break;
		case 5000:
			wr_l = 7;
			break;
		case 7000:
			wr_l = 8;
			break;
		case 9000:
			wr_l = 9;
			break;
		case 12000:
			wr_l = 10;
			break;
		default:
			FS2711_Debug(__FILE__, __LINE__, "Start Voltage error");
			break;
		}
		switch (end_volt)
		{
		case 3600:
			wr_h = 0;
			break;
		case 3800:
			wr_h = 1;
			break;
		case 4000:
			wr_h = 2;
			break;
		case 4200:
			wr_h = 3;
			break;
		case 4400:
			wr_h = 4;
			break;
		case 4600:
			wr_h = 5;
			break;
		case 4800:
			wr_h = 6;
			break;
		case 5000:
			wr_h = 7;
			break;
		case 7000:
			wr_h = 8;
			break;
		case 9000:
			wr_h = 9;
			break;
		case 12000:
			wr_h = 10;
			break;
		default:
			FS2711_Debug(__FILE__, __LINE__, "End Voltage error");
			break;
		}
		break;
	}
	case FS2711_PROTOCOL_PD:
	case FS2711_PROTOCOL_PPS:
	{
		FS2711_Write(0x46, FS2711_Lib.req_pdo_num + (FS2711_Lib.req_pdo_num << 4));
		wr_l = (start_volt - FS2711_Lib.pdo_min_volt[FS2711_Lib.req_pdo_num]) / 20;
		wr_h = (end_volt - FS2711_Lib.pdo_min_volt[FS2711_Lib.req_pdo_num]) / 20;
		// wr_l = (start_volt - 5000) / 20;
		// wr_h = (end_volt - 5000) / 20;
		FS2711_Write(0xde, max_curr / 50);
		break;
	}
	default:
		FS2711_Debug(__FILE__, __LINE__, "Protocol error");
		break;
	}
	FS2711_Write(0xf4, wr_l & 0xff);
	FS2711_Write(0xf5, (wr_l >> 8) & 0xff);
	FS2711_Write(0xf6, wr_h & 0xff);
	FS2711_Write(0xf7, (wr_h >> 8) & 0xff);
}
/**
 * @brief: FS2711设置需要诱骗的电压电流
 * @author: HYJ
 * @param protocol: 选择的协议
 * @param start_volt: 开始电压
 * @param end_volt: 结束电压
 * @param pdoID: PDO ID 只有PD协议时才有效
 * @retval None
 */
void FS2711_Decoy_Protocol(uint8_t protocol, uint16_t start_volt, uint16_t end_volt, uint16_t max_curr, uint8_t pdoID)
{
	static signed char nowPro = -1;

	if (protocol > 21)
	{
		FS2711_Debug(__FILE__, __LINE__, "Protocol error");
	}
	if (start_volt > end_volt)
	{
		FS2711_Debug(__FILE__, __LINE__, "Start Voltage > End Voltage");
	}

	FS2711_Lib.req_pdo_num = pdoID;

	if (nowPro != protocol)
	{
		FS2711_Enable_Protocol(0);
		nowPro = protocol;
		SysTick_Delay_Ms(500);
		if (protocol == FS2711_PROTOCOL_PPS)
		{
			FS2711_Select_Protocol(FS2711_PROTOCOL_PD);
			FS2711_Enable_Protocol(1);
			SysTick_Delay_Ms(100);
		}
		FS2711_Select_Protocol(protocol);
		FS2711_Enable_Protocol(1);
		SysTick_Delay_Ms(3000);
	}
	FS2711_Select_Voltage_Current(protocol, start_volt, end_volt, max_curr);
	FS2711_Enable_Voltage_Current();
}

/**
 * @brief: FS2711获取PD协议信息
 * @author: HYJ
 */
void FS2711_Get_PD_Information(void)
{
	uint8_t i = 0;
	uint8_t pdo_b0 = 0, pdo_b1 = 0, pdo_b2 = 0, pdo_b3 = 0;

	//<! 查询PD信息之前会先退出当前的协议，因为查询PD信息需要进入PD模式
	FS2711_Port_Reset();
	FS2711_Enable_Protocol(0);					//<! 退出当前协议
	FS2711_Select_Protocol(FS2711_PROTOCOL_PD); //<! 进入PD协议
	FS2711_Port_Reset();
	FS2711_Enable_Protocol(1);
	SysTick_Delay_Ms(500);

	FS2711_Lib.pdo_num = 0;
	FS2711_Lib.pdo_type = 0;
	memset(FS2711_Lib.pdo_max_volt, 0, sizeof(FS2711_Lib.pdo_max_volt));
	memset(FS2711_Lib.pdo_min_volt, 0, sizeof(FS2711_Lib.pdo_min_volt));
	memset(FS2711_Lib.pdo_max_curr, 0, sizeof(FS2711_Lib.pdo_max_curr));

	// SysTick_Delay_Ms(1000);
	for (i = 0; i < 7; i++)
	{
		pdo_b0 = FS2711_Read(0xc0 + i * 4);
		pdo_b1 = FS2711_Read(0xc1 + i * 4);
		pdo_b2 = FS2711_Read(0xc2 + i * 4);
		pdo_b3 = FS2711_Read(0xc3 + i * 4);
		if (pdo_b0)
		{
			if (pdo_b3 & 0xc0)
			{
				FS2711_Lib.pdo_type |= 1 << i;
				FS2711_Lib.pdo_min_volt[i] = pdo_b1 * 100;
				FS2711_Lib.pdo_max_volt[i] = ((pdo_b2 >> 1) + ((pdo_b3 & 0x1) << 7)) * 100;
				FS2711_Lib.pdo_max_curr[i] = (pdo_b0 & 0x7f) * 50;
			}
			else
			{
				FS2711_Lib.pdo_min_volt[i] = ((pdo_b1 >> 2) + ((pdo_b2 & 0xf) << 6)) * 50;
				FS2711_Lib.pdo_max_volt[i] = FS2711_Lib.pdo_min_volt[i];
				FS2711_Lib.pdo_max_curr[i] = (pdo_b0 + ((pdo_b1 & 0x3) << 8)) * 10;
			}
		}
		else
		{
			break;
		}
	}
	FS2711_Lib.pdo_num = i;

	/* //printf("PDO 0:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 1) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[0], FS2711_Lib.pdo_max_volt[0], FS2711_Lib.pdo_max_curr[0]);
	//printf("PDO 1:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 2) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[1], FS2711_Lib.pdo_max_volt[1], FS2711_Lib.pdo_max_curr[1]);
	//printf("PDO 2:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 4) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[2], FS2711_Lib.pdo_max_volt[2], FS2711_Lib.pdo_max_curr[2]);
	//printf("PDO 3:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 8) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[3], FS2711_Lib.pdo_max_volt[3], FS2711_Lib.pdo_max_curr[3]);
	//printf("PDO 4:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 16) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[4], FS2711_Lib.pdo_max_volt[4], FS2711_Lib.pdo_max_curr[4]);
	//printf("PDO 5:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 32) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[5], FS2711_Lib.pdo_max_volt[5], FS2711_Lib.pdo_max_curr[5]);
	//printf("PDO 6:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 64) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[6], FS2711_Lib.pdo_max_volt[6], FS2711_Lib.pdo_max_curr[6]); */
}

/**
 * @brief 返回固定pd协议的数量，pps协议在固定协议之后
 * 
 * @return uint8_t 
 */
uint8_t FS2711_Get_PPS_Num(void)
{
	int i;
	uint8_t pdo_type;
	for (i = 0; i < 7; i++)
	{
		pdo_type = FS2711_Lib.pdo_type>>i;
		if(pdo_type & 0x01)
			return i;
	}
	return FS2711_Lib.pdo_num;
}

/**
 * @brief: FS2711获取扫描的协议
 * @author: HYJ
 * @retval None
 */
void FS2711_Get_State(void)
{
	uint8_t data = 0, i = 0;
	uint8_t pdo_b0 = 0, pdo_b1 = 0, pdo_b2 = 0, pdo_b3 = 0;

	typedef struct
	{
		uint8_t scan : 1;
		uint8_t pd_up : 1;
		uint8_t : 6;
	} state1_reg;

	state1_reg *sr;

	data = FS2711_Read(0xb1);
	data = FS2711_Read(FS2711_REG_STATE1);

	sr = (state1_reg *)&data;

	if (sr->scan == 0)
	{
		FS2711_Lib.prot_exists = FS2711_Read(0xf8);
		FS2711_Lib.prot_exists |= FS2711_Read(0xf9) << 8;
		FS2711_Lib.prot_exists |= FS2711_Read(0xfa) << 16; //<! 扫描的协议

		FS2711_Lib.qc_max_volt = FS2711_Read(0xc0); //<! 获取QC最高电压

		if ((FS2711_Read(0xC6) & 0xf0) == 0x70) //<! 获取AFC最高电压
		{
			FS2711_Lib.afc_max_volt = FS2711_MAX_12V;
		}
		else if ((FS2711_Read(0xC5) & 0xf0) == 0x40)
		{
			FS2711_Lib.afc_max_volt = FS2711_MAX_9V;
		}
		else
		{
			FS2711_Lib.afc_max_volt = FS2711_MAX_5V;
		}

		if (FS2711_Read(0xCA) == 0x78) //<! 获取FCP最高电压
		{
			FS2711_Lib.fcp_max_volt = FS2711_MAX_12V;
		}
		else if (FS2711_Read(0xC9) == 0x5A)
		{
			FS2711_Lib.fcp_max_volt = FS2711_MAX_9V;
		}
		else
		{
			FS2711_Lib.fcp_max_volt = FS2711_MAX_5V;
		}
		// // SCP Max/Min Volt/Curr
		FS2711_Lib.scp_min_volt = FS2711_SCP_Calc(FS2711_Read(0xd0));
		FS2711_Lib.scp_max_volt = FS2711_SCP_Calc(FS2711_Read(0xd1));
		FS2711_Lib.scp_min_curr = FS2711_SCP_Calc(FS2711_Read(0xd2));
		FS2711_Lib.scp_max_curr = FS2711_SCP_Calc(FS2711_Read(0xd3));
		FS2711_Lib.vivo_max_power = FS2711_Read(0xd4); //<! 获取VIVO最高电压

		// while (i++ < 24)
		// {
		// 	if ((FS2711_Lib.prot_exists >> i) & 0x00000001)
		// 		//printf("%s ", protocol[i]);
		// }
		// printf("\r\n");
		// printf("QC   MAX V: 0x%x\r\n", FS2711_Lib.qc_max_volt);
		// printf("AFC  MAX V: %d\r\n", FS2711_Lib.afc_max_volt);
		// printf("FCP  MAX V: %d\r\n", FS2711_Lib.fcp_max_volt);
		// printf("SCP  MAX V: %d | MIN V: %d | MAX C: %d | MIN C: %d\r\n", FS2711_Lib.scp_max_volt, FS2711_Lib.scp_min_volt, FS2711_Lib.scp_max_curr, FS2711_Lib.scp_min_curr);
		// printf("VIVO MAX V: %d\r\n", FS2711_Lib.vivo_max_power);
	}
	if (sr->pd_up == 0)
	{

		FS2711_Lib.pdo_num = 0;
		FS2711_Lib.pdo_type = 0;
		memset(FS2711_Lib.pdo_max_volt, 0, sizeof(FS2711_Lib.pdo_max_volt));
		memset(FS2711_Lib.pdo_min_volt, 0, sizeof(FS2711_Lib.pdo_min_volt));
		memset(FS2711_Lib.pdo_max_curr, 0, sizeof(FS2711_Lib.pdo_max_curr));

		for (i = 0; i < 7; i++)
		{
			pdo_b0 = FS2711_Read(0xc0 + i * 4);
			pdo_b1 = FS2711_Read(0xc1 + i * 4);
			pdo_b2 = FS2711_Read(0xc2 + i * 4);
			pdo_b3 = FS2711_Read(0xc3 + i * 4);
			if (pdo_b0)
			{
				if (pdo_b3 & 0xc0)
				{
					FS2711_Lib.pdo_type |= 1 << i;
					FS2711_Lib.pdo_min_volt[i] = pdo_b1 * 100;
					FS2711_Lib.pdo_max_volt[i] = ((pdo_b2 >> 1) + ((pdo_b3 & 0x1) << 7)) * 100;
					FS2711_Lib.pdo_max_curr[i] = (pdo_b0 & 0x7f) * 50;
				}
				else
				{
					FS2711_Lib.pdo_min_volt[i] = ((pdo_b1 >> 2) + ((pdo_b2 & 0xf) << 6)) * 50;
					FS2711_Lib.pdo_max_volt[i] = FS2711_Lib.pdo_min_volt[i];
					FS2711_Lib.pdo_max_curr[i] = (pdo_b0 + ((pdo_b1 & 0x3) << 8)) * 10;
				}
			}
			else
			{
				break;
			}
		}
		FS2711_Lib.pdo_num = i;

		// //printf("PDO 0:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 1) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[0], FS2711_Lib.pdo_max_volt[0], FS2711_Lib.pdo_max_curr[0]);
		// //printf("PDO 1:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 2) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[1], FS2711_Lib.pdo_max_volt[1], FS2711_Lib.pdo_max_curr[1]);
		// //printf("PDO 2:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 4) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[2], FS2711_Lib.pdo_max_volt[2], FS2711_Lib.pdo_max_curr[2]);
		// //printf("PDO 3:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 8) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[3], FS2711_Lib.pdo_max_volt[3], FS2711_Lib.pdo_max_curr[3]);
		// //printf("PDO 4:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 16) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[4], FS2711_Lib.pdo_max_volt[4], FS2711_Lib.pdo_max_curr[4]);
		// //printf("PDO 5:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 32) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[5], FS2711_Lib.pdo_max_volt[5], FS2711_Lib.pdo_max_curr[5]);
		// //printf("PDO 6:\t%s\tminV: %d\tmaxV: %d\tmaxC: %d\r\n", (FS2711_Lib.pdo_type & 64) ? "PPS" : "FIXED", FS2711_Lib.pdo_min_volt[6], FS2711_Lib.pdo_max_volt[6], FS2711_Lib.pdo_max_curr[6]);
	}
}
/**
 * @brief: FS2711中断处理
 * @author: HYJ
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	FS2711_Get_State();
	/* if (GPIO_Pin == FS2711_INT_Pin)
	{
		FS2711_Get_State();
	} */
}

/**
 * @brief: FS2711开始扫描协议
 * @author: HYJ
 */
void FS2711_Scan_Start(void)
{
	FS2711_Write(FS2711_REG_SS, 0x1);
}

void FS2711_Set_Sweep_Mode(uint8_t mode)
{
	FS2711_Write(0x47, mode);
}

/**
 *
 */
void FS2711_TEST(uint8_t data)
{
}

/**
 * @brief: FS2711 拉高DP & DM
 */
void FS2711_DPDM_Set(void)
{
	FS2711_Write(FS2711_REG_DPDM, 0xFF); //<! 拉高DP & DM
}

/**
 * @brief: FS2711 复位DP & DM
 */
void FS2711_DPDM_Reset(void)
{
	FS2711_Write(FS2711_REG_DPDM, 0x00); //<! 拉低DP & DM
}

/**
 * @brief: FS2711系统复位
 * @author: HYJ
 */
void FS2711_System_Reset(void)
{
	FS2711_Write(FS2711_REG_SR, 0x1);
}

/**
 * @brief: FS2711端口复位
 * @author: HYJ
 */
void FS2711_Port_Reset(void)
{
	FS2711_Write(FS2711_REG_MC, 0x02); //<! 断开Rd
	FS2711_Write(FS2711_REG_PR, 0x00); //<! 端口复位
	SysTick_Delay_Ms(1);
	FS2711_Write(FS2711_REG_MC, 0x00);
	FS2711_Write(FS2711_REG_PR, 0x01);
}

void FS2711_Port_Disconnect(void)
{
	FS2711_Write(FS2711_REG_MC, 0x02); //<! 断开Rd
	FS2711_Write(FS2711_REG_PR, 0x00); //<! 端口复位
}

void FS2711_Port_Connect(void)
{
	FS2711_Write(FS2711_REG_MC, 0x00);
	FS2711_Write(FS2711_REG_PR, 0x01);
}

uint16_t FS2711_SCP_Calc(uint8_t val) //<! SCP值计算
{
	uint16_t result;
	if ((val & 0xc0) == 0xc0)
	{
		result = (val & 0x3f) * 1000;
	}
	else if ((val & 0xc0) == 0x80)
	{
		result = (val & 0x3f) * 100;
	}
	else if ((val & 0xc0) == 0x40)
	{
		result = (val & 0x3f) * 10;
	}
	return result;
}
