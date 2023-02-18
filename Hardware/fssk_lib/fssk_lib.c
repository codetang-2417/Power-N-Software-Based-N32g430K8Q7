#include "chip.h"
#include "bsp_delay.h"

FS2711_LIB_t FS2711_lib;
/*
Check if Parameter is Valid
*/
void FS2711_Debug()
{
	while (1)
		;
}

/*
Reset FS2711
*/
void FS2711_System_Reset()
{
	Write_IIC(0x4a, 0x1);
}
/*
Reset C&A Port
*/
void FS2711_Port_Reset()
{
	Write_IIC(0xa0, 0x2);
	Write_IIC(0x49, 0x0);
	SysTick_Delay_Ms(1);
	Write_IIC(0xa0, 0x0);
	Write_IIC(0x49, 0x1);
}

/*
Scan Charger Capabilities
*/
void FS2711_Scan_Start()
{
	Write_IIC(0x40, 0x1);
}

void FS2711_Enable_Monitor()
{
	Write_IIC(0xa0, 0x3);
}

/*
Enter or Exit a Protocol
*/
void FS2711_Select_Protocol(u8 protocol)
{
	if (protocol > 21)
	{
		FS2711_Debug();
	}
	Write_IIC(0x42, protocol);
}

void FS2711_Enable_Protocol(u8 ena)
{
	if (ena)
	{
		Write_IIC(0x41, 0x1);
	}
	else
	{
		Write_IIC(0x41, 0x2);
	}
}
/*
Request Voltage & Current of a protocol
*/
void FS2711_Select_Voltage_Current(u8 protocol, u16 start_volt, u16 end_volt, u16 max_curr)
{
	u16 wr_l, wr_h;
	if (protocol > 21)
	{
		FS2711_Debug();
	}
	if (start_volt > end_volt)
	{
		FS2711_Debug();
	}
	switch (protocol)
	{
	case FS2711_QC2A:
	case FS2711_QC2B:
	case FS2711_AFC:
	case FS2711_FCP:
	{
		if (start_volt == 5000)
		{
			wr_l = 0x0;
		}
		else if (start_volt == 9000)
		{
			wr_l = 0x1;
		}
		else if (start_volt == 12000)
		{
			wr_l = 0x2;
		}
		else if (start_volt == 20000)
		{
			wr_l = 0x3;
		}
		else
		{
			FS2711_Debug();
		}
		if (end_volt == 5000)
		{
			wr_h = 0x0;
		}
		else if (end_volt == 9000)
		{
			wr_h = 0x1;
		}
		else if (end_volt == 12000)
		{
			wr_h = 0x2;
		}
		else if (end_volt == 20000)
		{
			wr_h = 0x3;
		}
		else
		{
			FS2711_Debug();
		}
		break;
	}
	case FS2711_QC3A:
	case FS2711_QC3B:
	{
		wr_l = (start_volt - 3600) / 200;
		wr_h = (end_volt - 3600) / 200;
		break;
	}
	case FS2711_SCP:
	{
		wr_l = (start_volt - 3300) / 10;
		wr_h = (end_volt - 3300) / 10;
		break;
	}
	case FS2711_HISCP:
	{
		wr_l = (start_volt - 5500) / 10;
		wr_h = (end_volt - 5500) / 10;
		break;
	}
	case FS2711_VOOC2:
	case FS2711_VOOC3:
	case FS2711_VOOC4:
	{
		Write_IIC(0xdc, start_volt);
		Write_IIC(0xde, (max_curr - 3000) / 250);
		break;
	}
	case FS2711_SVOOC1:
	{
		Write_IIC(0xdc, start_volt);
		Write_IIC(0xde, max_curr / 100);
		break;
	}
	case FS2711_VIVO_5V4A:
	{
		wr_l = (start_volt - 4000) / 10;
		wr_h = (end_volt - 4000) / 10;
		break;
	}
	case FS2711_VIVO_10V2P25A:
	case FS2711_VIVO_11V4A:
	{
		wr_l = (start_volt - 7000) / 10;
		wr_h = (end_volt - 7000) / 10;
		break;
	}
	case FS2711_MTK:
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
			FS2711_Debug();
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
			FS2711_Debug();
		}
		break;
	}
	case FS2711_PD:
	case FS2711_PPS:
	{
		Write_IIC(0x46, FS2711_lib.req_pdo_num + (FS2711_lib.req_pdo_num << 4));
		wr_l = (start_volt - FS2711_lib.pdo_min_volt[FS2711_lib.req_pdo_num]) / 20;
		wr_h = (end_volt - FS2711_lib.pdo_min_volt[FS2711_lib.req_pdo_num]) / 20;
		Write_IIC(0xde, max_curr / 50);
		break;
	}
	default:
		FS2711_Debug();
	}
	Write_IIC(0xf4, wr_l & 0xff);
	Write_IIC(0xf5, (wr_l >> 8) & 0xff);
	Write_IIC(0xf6, wr_h & 0xff);
	Write_IIC(0xf7, (wr_h >> 8) & 0xff);
}

void FS2711_Enable_Voltage_Current()
{
	Write_IIC(0x43, 0x1);
}

/*
Set Sweep Mode
*/
void FS2711_Set_Sweep_Mode(u8 mode)
{
	Write_IIC(0x47, mode);
}

/*
FS2711 IRQ Handler
*/
void FS2711_IRQHandler()
{
	u8 i2c_rdata;
	u8 pdo_b0, pdo_b1, pdo_b2, pdo_b3;
	u8 i;
	i2c_rdata = ~Read_IIC(0xb1);
	i2c_rdata = ~Read_IIC(0xb2);
	if (i2c_rdata & 0x1)
	{ // Scan Done
		FS2711_lib.prot_exists = Read_IIC(0xf8);
		FS2711_lib.prot_exists |= Read_IIC(0xf9) << 8;
		FS2711_lib.prot_exists |= Read_IIC(0xfa) << 16;
		// QC Max Volt
		FS2711_lib.qc_max_volt = Read_IIC(0xc0);
		// AFC Max Volt
		if ((Read_IIC(0xC6) & 0xf0) == 0x70)
		{
			FS2711_lib.afc_max_volt = FS2711_MAX_12V;
		}
		else if ((Read_IIC(0xC5) & 0xf0) == 0x40)
		{
			FS2711_lib.afc_max_volt = FS2711_MAX_9V;
		}
		else
		{
			FS2711_lib.afc_max_volt = FS2711_MAX_5V;
		}
		// FCP Max Volt
		if (Read_IIC(0xCA) == 0x78)
		{
			FS2711_lib.fcp_max_volt = FS2711_MAX_12V;
		}
		else if (Read_IIC(0xC9) == 0x5A)
		{
			FS2711_lib.fcp_max_volt = FS2711_MAX_9V;
		}
		else
		{
			FS2711_lib.fcp_max_volt = FS2711_MAX_5V;
		}
		// SCP Max/Min Volt/Curr
		FS2711_lib.scp_min_volt = FS2711_SCP_Calc(Read_IIC(0xd0));
		FS2711_lib.scp_max_volt = FS2711_SCP_Calc(Read_IIC(0xd1));
		FS2711_lib.scp_min_curr = FS2711_SCP_Calc(Read_IIC(0xd2));
		FS2711_lib.scp_max_curr = FS2711_SCP_Calc(Read_IIC(0xd3));
		// VIVO Max Power
		FS2711_lib.vivo_max_power = Read_IIC(0xd4);
	}
	if (i2c_rdata & 0x2)
	{ // PDO Update
		FS2711_lib.pdo_num = 0;
		FS2711_lib.pdo_type = 0;
		for (i = 0; i < 7; i++)
		{
			pdo_b0 = Read_IIC(0xc0 + i * 4);
			pdo_b1 = Read_IIC(0xc1 + i * 4);
			pdo_b2 = Read_IIC(0xc2 + i * 4);
			pdo_b3 = Read_IIC(0xc3 + i * 4);
			if (pdo_b0)
			{
				if (pdo_b3 & 0xc0)
				{
					FS2711_lib.pdo_type |= 1 << i;
					FS2711_lib.pdo_min_volt[i] = pdo_b1 * 100;
					FS2711_lib.pdo_max_volt[i] = ((pdo_b2 >> 1) + ((pdo_b3 & 0x1) << 7)) * 100;
					FS2711_lib.pdo_max_curr[i] = (pdo_b0 & 0x7f) * 50;
				}
				else
				{
					FS2711_lib.pdo_min_volt[i] = ((pdo_b1 >> 2) + ((pdo_b2 & 0xf) << 6)) * 50;
					FS2711_lib.pdo_max_volt[i] = FS2711_lib.pdo_min_volt[i];
					FS2711_lib.pdo_max_curr[i] = (pdo_b0 + ((pdo_b1 & 0x3) << 8)) * 10;
				}
			}
			else
			{
				continue;
			}
		}
		FS2711_lib.pdo_num = i;
	}
}

u16 FS2711_SCP_Calc(u8 val)
{
	u16 result;
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
