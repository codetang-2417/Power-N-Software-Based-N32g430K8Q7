#ifndef __FS2711_H
#define __FS2711_H

#include "stdio.h"
#include "i2c.h"
#include "string.h"

typedef struct
{
	// SCAN Result
	uint32_t prot_exists;
	uint8_t qc_max_volt;
	uint8_t afc_max_volt;
	uint8_t fcp_max_volt;
	uint16_t scp_max_volt;
	uint16_t scp_min_volt;
	uint16_t scp_max_curr;
	uint16_t scp_min_curr;
	uint8_t vivo_max_power;
	// PD PDO
	uint8_t pdo_num;
	uint8_t pdo_type;
	uint8_t req_pdo_num;
	uint16_t pdo_max_volt[7];
	uint16_t pdo_min_volt[7];
	uint16_t pdo_max_curr[7];
	uint8_t data_c0[32];
} FS2711_Lib_t;

extern FS2711_Lib_t FS2711_Lib;
//<! 协议列表
#define FS2711_PROTOCOL_APPLE_2P4A 0
#define FS2711_PROTOCOL_SAMSUNG_2A 1
#define FS2711_PROTOCOL_BC1P2 2
#define FS2711_PROTOCOL_TYPEC 3
#define FS2711_PROTOCOL_QC2A 4
#define FS2711_PROTOCOL_QC2B 5
#define FS2711_PROTOCOL_QC3A 6
#define FS2711_PROTOCOL_QC3B 7
#define FS2711_PROTOCOL_AFC 8
#define FS2711_PROTOCOL_FCP 9
#define FS2711_PROTOCOL_SCP 10
#define FS2711_PROTOCOL_HISCP 11
#define FS2711_PROTOCOL_VOOC2 12
#define FS2711_PROTOCOL_SVOOC1 13
#define FS2711_PROTOCOL_VOOC3 14
#define FS2711_PROTOCOL_VOOC4 15
#define FS2711_PROTOCOL_VIVO_5V4A 16
#define FS2711_PROTOCOL_VIVO_10V2P25A 17
#define FS2711_PROTOCOL_VIVO_11V4A 18
#define FS2711_PROTOCOL_MTK 19
#define FS2711_PROTOCOL_PPS 20
#define FS2711_PROTOCOL_PD 21

void FS2711_TEST(uint8_t data);

void FS2711_Scan_Start(void);
void FS2711_System_Reset(void);
void FS2711_Port_Reset(void);
void FS2711_Port_Disconnect(void);
void FS2711_Port_Connect(void);
void FS2711_DPDM_Set(void);
void FS2711_DPDM_Reset(void);

void FS2711_Get_State(void);
uint8_t FS2711_Get_PPS_Num(void);

void FS2711_Get_PD_Information(void);
void FS2711_Select_Voltage_Current(uint8_t protocol, uint16_t start_volt, uint16_t end_volt, uint16_t max_curr);
void FS2711_Enable_Voltage_Current(void);
void FS2711_Select_Protocol(uint8_t protocol);
void FS2711_Enable_Protocol(uint8_t ena);
void FS2711_Decoy_Protocol(uint8_t protocol, uint16_t start_volt, uint16_t end_volt, uint16_t max_curr, uint8_t pdoID);
#endif
