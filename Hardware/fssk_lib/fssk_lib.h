#ifndef _FS2711_LIB_H_
#define _FS2711_LIB_H_

#include "n32g430.h"

// Protocol type
#define FS2711_APPLE_2P4A 	0
#define FS2711_SAMSUNG_2A 	1
#define FS2711_BC1P2 			2
#define FS2711_TYPEC 			3
#define FS2711_QC2A 			4
#define FS2711_QC2B 			5
#define FS2711_QC3A 			6
#define FS2711_QC3B 			7
#define FS2711_AFC 			8
#define FS2711_FCP 			9
#define FS2711_SCP 			10
#define FS2711_HISCP 			11
#define FS2711_VOOC2 			12
#define FS2711_SVOOC1 		13
#define FS2711_VOOC3 			14
#define FS2711_VOOC4 			15
#define FS2711_VIVO_5V4A 		16
#define FS2711_VIVO_10V2P25A 	17
#define FS2711_VIVO_11V4A 	18
#define FS2711_MTK 			19
#define FS2711_PPS 			20
#define FS2711_PD 			21

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

// FS2711 Struct
typedef struct
{
	// SCAN Result
	u32 prot_exists;
	u8 qc_max_volt;
	u8 afc_max_volt;
	u8 fcp_max_volt;
	u16 scp_max_volt;
	u16 scp_min_volt;
	u16 scp_max_curr;
	u16 scp_min_curr;
	u8 vivo_max_power;
	// PD PDO
	u8 pdo_num;
	u8 pdo_type;
	u8 req_pdo_num;
	u16 pdo_max_volt[7];
	u16 pdo_min_volt[7];
	u16 pdo_max_curr[7];
	u8 data_c0[32];
} FS2711_LIB_t;

void FS2711_Debug(void);
void FS2711_System_Reset(void);
void FS2711_Port_Reset(void);
void FS2711_Scan_Start(void);
void FS2711_Enable_Monitor(void);
void FS2711_Select_Protocol(u8 protocol);
void FS2711_Enable_Protocol(u8 ena);
void FS2711_Select_Voltage_Current(u8 protocol, u16 start_volt, u16 end_volt, u16 max_curr);
void FS2711_Enable_Voltage_Current(void);
void FS2711_Set_Sweep_Mode(u8 mode);
void FS2711_IRQHandler(void);
u16 FS2711_SCP_Calc(u8 val);

extern FS2711_LIB_t FS2711_lib;

#endif
