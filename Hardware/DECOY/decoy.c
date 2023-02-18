#include "decoy.h"
#include "menu.h"

extern bool IsReset;
extern bool ConnectFlag;
/**
 * @brief 根据flash中的信息，初始化FS2711；使用前必须先通过函数Flash_Read读取flash中的信息sg_FlashSelect
 *
 */
void Init_FS2711(void)
{
    FS2711_System_Reset();
    FS2711_Port_Reset();
    FS2711_Enable_Protocol(0);
    if (sg_FlashSelect.IsFsReset)//通过写入flash重启标志，判断开机后是否需要重启，并进入到要求重启子菜单
    {
        sg_FlashSelect.IsFsReset = false;
        Flash_Write();
        if (sg_FlashSelect.MenuSelect != 0xFF)
        {
            Menu_ShortcutEnter(true, 2, 1, sg_FlashSelect.MenuSelect);//
        }
    }
}

void Decoy(uint16_t start_volt, uint16_t end_volt, uint16_t max_curr)
{
    FS2711_Select_Voltage_Current(sg_FlashSelect.ProtocolInformation.protocol_mode, start_volt, end_volt, max_curr);
    FS2711_Enable_Voltage_Current();
}

void Start_FS2711_With(void)
{
}

void mcuRestart(void)
{
    __set_FAULTMASK(1); // 关闭所有中断
    NVIC_SystemReset(); // 复位
}

/**
 * @brief 如果是QC协议转其他协议，不需要重启；如果不是qc，则需要重启；
 *
 * @param protocol 想要更改的最新的协议
 */
void EnableNewProtocol(uint8_t Protocol)
{
    bool Reset = false;
    uint8_t t_Protocol = sg_FlashSelect.ProtocolInformation.protocol_mode;
    sg_FlashSelect.ProtocolInformation.protocol_mode = Protocol;
    Flash_Write();

    if (Protocol != t_Protocol)
    {
        if (t_Protocol >= FS2711_PROTOCOL_QC2A && t_Protocol <= FS2711_PROTOCOL_QC3B)
        {
            Reset = false;

            FS2711_Enable_Protocol(0);
            FS2711_Port_Reset();
            FS2711_Select_Protocol(Protocol);
            FS2711_Enable_Protocol(1);
            SysTick_Delay_Ms(1000);
            FS2711_Select_Voltage_Current(Protocol, sg_FlashSelect.ProtocolInformation.ptl_select_volt, sg_FlashSelect.ProtocolInformation.ptl_select_volt, sg_FlashSelect.ProtocolInformation.ptl_max_curr);
            FS2711_Enable_Voltage_Current();

            SysTick_Delay_Ms(2000);
            FS2711_Select_Voltage_Current(Protocol, sg_FlashSelect.ProtocolInformation.ptl_select_volt, sg_FlashSelect.ProtocolInformation.ptl_select_volt, sg_FlashSelect.ProtocolInformation.ptl_max_curr);
            FS2711_Enable_Voltage_Current();
        }
        else
        {
            //Reset = true;
            //FS2711_Enable_Protocol(0);
            FS2711_Select_Protocol(Protocol);
            //FS2711_Port_Reset();
            FS2711_Enable_Protocol(1);
            FS2711_Select_Voltage_Current(Protocol, sg_FlashSelect.ProtocolInformation.ptl_select_volt, sg_FlashSelect.ProtocolInformation.ptl_select_volt, sg_FlashSelect.ProtocolInformation.ptl_max_curr);
        }

        if (Reset)
            mcuRestart();
    }
    else
    {
        if (Protocol == FS2711_PROTOCOL_PD)
        {
            FS2711_Select_Voltage_Current(Protocol, 0, 0, sg_FlashSelect.ProtocolInformation.ptl_max_curr);
            FS2711_Enable_Voltage_Current();
        }
        else if (Protocol == FS2711_PROTOCOL_PPS)
        {
            FS2711_Lib.req_pdo_num = sg_FlashSelect.ProtocolInformation.req_pdo_num;
            FS2711_Select_Voltage_Current(Protocol, sg_FlashSelect.ProtocolInformation.ptl_select_volt, sg_FlashSelect.ProtocolInformation.ptl_select_volt, sg_FlashSelect.ProtocolInformation.ptl_max_curr);
            FS2711_Enable_Voltage_Current(); // FS2711_Enable_Protocol(1);
        }
        else
        {
            FS2711_Select_Voltage_Current(sg_FlashSelect.ProtocolInformation.protocol_mode, sg_FlashSelect.ProtocolInformation.ptl_select_volt,
                                          sg_FlashSelect.ProtocolInformation.ptl_select_volt, sg_FlashSelect.ProtocolInformation.ptl_max_curr);
            FS2711_Enable_Voltage_Current();
        }
    }
}
