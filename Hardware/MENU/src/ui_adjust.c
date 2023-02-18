#include "ui_adjust.h"
#include "lcd.h"
#include "FS2711.h"
#include "menu.h"
#include "key.h"
#include <stdio.h>
#include <string.h>
#include "adc.h"

/* ��ƭ�˵� */
MenuList_t sg_AdjMenuTable[] =
    {
        {"1.PD��ƭ ", "1.PD ", OnPDFunctionLoad, OnPDFunctionExit, OnPDFunction, NULL},
        {"2.QC��ƭ ", "2.QC ", OnQCFunctionLoad, OnQCFunctionExit, OnQCFunction, NULL},
        //{"3.PDO��ȡ ", "3.PDO read", OnPDOFunctionLoad, OnPDOFunctionExit, OnPDOFunction, NULL},

};

void ShowAdjMainMenu(MenuShow_t *ptShowInfo)
{
    menusize_t ShowNum = 3;
    menusize_t tmpselect;
    Menu_LimitShowListNum(ptShowInfo, &ShowNum);
    int i;
    LCD_ShowString(48, 0, (u8 *)(ptShowInfo->pszDesc), LIGHTBLUE, BLACK, 24, 0);
    for (i = 0; i < ShowNum; i++)
    {
        tmpselect = i + ptShowInfo->showBaseItem;
        if (tmpselect == ptShowInfo->selectItem)
        {
            LCD_ShowString(16, 24 + i * 16, (u8 *)(ptShowInfo->pszItemsDesc[tmpselect]), BLACK, LBBLUE, 16, 0);
        }
        else
        {
            LCD_ShowString(16, 24 + i * 16, (u8 *)(ptShowInfo->pszItemsDesc[tmpselect]), BRRED, BLACK, 16, 0);
        }
    }
}

void UI_Adjust_Load(void)
{
    LCD_Fill(0, 0, 160, 80, BLACK); /*! 160*80 ��ʼ�� */
    Menu_Bind(sg_AdjMenuTable, GET_MENU_NUM(sg_AdjMenuTable), ShowAdjMainMenu);
}

void UI_Adjust_Exit(void)
{
    LCD_Fill(0, 0, 160, 80, BLACK); /*! 160*80 ��ʼ�� */
    Key_Start_Task();
}

void UI_Adjust_Task(void)
{
}

extern char Key_Ok_Func;
extern bool Screen_Roll;
uint8_t pps_sel = 0;
uint8_t temp_mode = 0;

void OnKeyOkPDProess(IoKeyType_e eKey, KeyAction_e eAction)
{
    static uint8_t cnt = 0;

    if (KEY_ACTION_PRESS == eAction)
    {
        KEY_SetNotifyTime(eKey, 800); // 2��󣬰������ܱ�Ϊ����
        if (KEY_GetPressTime(eKey) >= 800)
        {
            KEY_SetNotifyTime(eKey, 0); // ��ʵҲ�������ã���������ã���Ч��Ϊÿ3�룬�ͷ���һ�Σ����ú�ֻ����һ��
            Key_Ok_Func = 'N';
            Menu_Exit(false); // ������һ���˵�����
        }
    }

    uint8_t click = KEY_GetClickCnt(eKey, 200);
    if (2 == click)
    {
        if ('N' != Key_Ok_Func)
        {
            if (cnt % 2 == 1)
            {
                Screen_Roll = !Screen_Roll;
                LCD_Roll(Screen_Roll);
            }
            else
            {
                Screen_Roll = !Screen_Roll;
                LCD_Roll(Screen_Roll);
            }
            cnt++;
            sg_FlashSelect.ScrenDeirection = Screen_Roll;
        }
        else
            Key_Ok_Func = 'B';
    }
    else if (1 == click)
    {
        if ('N' == Key_Ok_Func)
        {
            Key_Ok_Func = 'B';
        }
        else
        {
            Key_Ok_Func = 'O'; // ȷ�ϼ�������˵�����ִ�й���
            PD_Ok();           // Menu_Enter();
        }
    }
}

void Set_PD_Protocol(void)
{
    EnableNewProtocol(temp_mode);
}

void PD_Ok(void)
{
    if (pps_sel == 0)
    {
        if (temp_mode == FS2711_PROTOCOL_PD)
        {
            sg_FlashSelect.ProtocolInformation.ptl_select_volt = sg_FlashSelect.ProtocolInformation.ptl_start_volt;
        }
        else
        {
            if (sg_FlashSelect.ProtocolInformation.ptl_select_volt > FS2711_Lib.pdo_max_volt[sg_FlashSelect.ProtocolInformation.req_pdo_num])
                sg_FlashSelect.ProtocolInformation.ptl_select_volt = FS2711_Lib.pdo_max_volt[sg_FlashSelect.ProtocolInformation.req_pdo_num];
            sg_FlashSelect.ProtocolInformation.ptl_max_curr = FS2711_Lib.pdo_max_curr[sg_FlashSelect.ProtocolInformation.req_pdo_num];
        }
        Set_PD_Protocol();
    }
    else
    {
        if (pps_sel == 1)
        {
            if (temp_mode == FS2711_PROTOCOL_PPS)
            {
                // int pps_mode = FS2711_Get_PPS_Num();
                /* if (FS2711_Lib.req_pdo_num < pps_mode)
                    FS2711_Lib.req_pdo_num = pps_mode; */
                sg_FlashSelect.ProtocolInformation.ptl_select_volt += 20;
                if (sg_FlashSelect.ProtocolInformation.ptl_select_volt > FS2711_Lib.pdo_max_volt[sg_FlashSelect.ProtocolInformation.req_pdo_num])
                    sg_FlashSelect.ProtocolInformation.ptl_select_volt = FS2711_Lib.pdo_max_volt[sg_FlashSelect.ProtocolInformation.req_pdo_num];
                sg_FlashSelect.ProtocolInformation.ptl_end_volt = sg_FlashSelect.ProtocolInformation.ptl_select_volt;
                sg_FlashSelect.ProtocolInformation.ptl_start_volt = sg_FlashSelect.ProtocolInformation.ptl_select_volt;
                sg_FlashSelect.ProtocolInformation.ptl_max_curr = FS2711_Lib.pdo_max_curr[sg_FlashSelect.ProtocolInformation.req_pdo_num];
                EnableNewProtocol(FS2711_PROTOCOL_PPS);
            }
        }
        else if (pps_sel == 2)
        {
            if (temp_mode == FS2711_PROTOCOL_PPS)
            {
                // int pps_mode = FS2711_Get_PPS_Num();
                /* if (FS2711_Lib.req_pdo_num < pps_mode)
                    FS2711_Lib.req_pdo_num = pps_mode; */
                sg_FlashSelect.ProtocolInformation.ptl_select_volt -= 20;
                if (sg_FlashSelect.ProtocolInformation.ptl_select_volt < FS2711_Lib.pdo_min_volt[sg_FlashSelect.ProtocolInformation.req_pdo_num])
                    sg_FlashSelect.ProtocolInformation.ptl_select_volt = FS2711_Lib.pdo_min_volt[sg_FlashSelect.ProtocolInformation.req_pdo_num];
                sg_FlashSelect.ProtocolInformation.ptl_end_volt = sg_FlashSelect.ProtocolInformation.ptl_select_volt;
                sg_FlashSelect.ProtocolInformation.ptl_start_volt = sg_FlashSelect.ProtocolInformation.ptl_select_volt;
                sg_FlashSelect.ProtocolInformation.ptl_max_curr = FS2711_Lib.pdo_max_curr[sg_FlashSelect.ProtocolInformation.req_pdo_num];
                EnableNewProtocol(FS2711_PROTOCOL_PPS);
            }
        }
    }
};

void Key_Register_PD(void)
{
    // KEY_Register(IO_KEY_UP, OnKeyActionPDProess);
    // KEY_Register(IO_KEY_DOWN, OnKeyActionPDProess);
    KEY_Register(IO_KEY_OK, OnKeyOkPDProess);
}

/* PD��ƭ�˵� */
char PdMenuVolt[7][16] = {0};
MenuList_t sg_PDMenuTable[] =
    {
        {"+20mV", "+20mV", NULL, NULL, NULL, NULL},
        {"-20mV", "-20mV", NULL, NULL, NULL, NULL},
        {PdMenuVolt[0], PdMenuVolt[0], NULL, NULL, NULL, NULL},
        {PdMenuVolt[1], PdMenuVolt[1], NULL, NULL, NULL, NULL},
        {PdMenuVolt[2], PdMenuVolt[2], NULL, NULL, NULL, NULL},
        {PdMenuVolt[3], PdMenuVolt[3], NULL, NULL, NULL, NULL},
        {PdMenuVolt[4], PdMenuVolt[4], NULL, NULL, NULL, NULL},
        {PdMenuVolt[5], PdMenuVolt[5], NULL, NULL, NULL, NULL},
        {PdMenuVolt[6], PdMenuVolt[6], NULL, NULL, NULL, NULL},
};

void ShowPdMainMenu(MenuShow_t *ptShowInfo)
{
    menusize_t ShowNum;
    menusize_t tmpselect;
    uint8_t pps_mode = FS2711_Get_PPS_Num();
    if (pps_mode == 0)
    {
        LCD_ShowString(40, 8, "no pd protocol.", WHITE, BLACK, 16, 0);
        return;
    }
    if (pps_mode == FS2711_Lib.pdo_num) // ˵��û��ppsģʽ
    {
        // ����ʾ+-20mv�İ�ť,����+-20mvѡ��
        int i = Menu_SetItemBeginLocation(0);
        if (i != 2)
        {
            Menu_SetItemBeginLocation(2 - i); //
        }
        ShowNum = FS2711_Lib.pdo_num;
        Menu_ResetItemsNum(ShowNum); // �ֶ������б�����
        ShowNum = ShowNum > 5 ? 5 : ShowNum;
    }
    else // ˵����ppsģʽ
    {
        int i = Menu_SetItemBeginLocation(0); // ��ȡĿǰ��ƫ��
        if (i != 0)
        {
            Menu_SetItemBeginLocation(-i); // ��ƫ��������0
        }
        ShowNum = FS2711_Lib.pdo_num + 2;
        Menu_ResetItemsNum(ShowNum); // �ֶ������б�����
        ShowNum = ShowNum > 5 ? 5 : ShowNum;
        ShowNum += 2;
    }
    Menu_LimitShowListNum(ptShowInfo, &ShowNum);
    ShowNum = ShowNum > 5 ? 5 : ShowNum;
    int i;
    /* for(i=0;i<FS2711_Lib.pdo_num;i++)
        if((FS2711_Lib.pdo_type & (1<<i)))//PPS else PD Fixed
            LCD_ShowString(0, 0, (u8 *)("PPS "), LGRAY, BLACK, 24, 0);
        else */

    if (sg_FlashSelect.ProtocolInformation.protocol_mode == FS2711_PROTOCOL_PD)
        LCD_ShowString(0, 0, "PD ", LGRAY, BLACK, 24, 0);
    else
        LCD_ShowString(0, 0, "PPS", LGRAY, BLACK, 24, 0);

    for (i = 0; i < FS2711_Lib.pdo_num; i++)
    {
        if (FS2711_Lib.pdo_max_volt[i] != 0)
        {
            sprintf(PdMenuVolt[i], "%.1fV ", FS2711_Lib.pdo_min_volt[i] * 1.0 / 1000.0); //
            int sizeofstr = strlen(PdMenuVolt[i]);
            if (sizeofstr < 6)
            {
                PdMenuVolt[i][sizeofstr] = ' ';
                PdMenuVolt[i][sizeofstr + 1] = 0;
            }
        }
        else
            sprintf(PdMenuVolt[i], "0V ");
    }

    if (pps_mode != FS2711_Lib.pdo_num) // ˵����ppsģʽ
    {
        if (ptShowInfo->selectItem == 0)
        {
            pps_sel = 1; //+20mV
            LCD_ShowString(44, 0, (u8 *)(ptShowInfo->pszItemsDesc[0]), BLACK, GREEN, 16, 0);
        }
        else
        {
            LCD_ShowString(44, 0, (u8 *)(ptShowInfo->pszItemsDesc[0]), GREEN, BLACK, 16, 0);
        }
        if (ptShowInfo->selectItem == 1)
        {
            pps_sel = 2; //-20mV
            LCD_ShowString(44, 16, (u8 *)(ptShowInfo->pszItemsDesc[1]), BLACK, GREEN, 16, 0);
        }
        else
            LCD_ShowString(44, 16, (u8 *)(ptShowInfo->pszItemsDesc[1]), GREEN, BLACK, 16, 0);
    }

    for (i = 0; i < ShowNum; i++)
    {
        if (i == 0 && ptShowInfo->selectItem > 1 && (ptShowInfo->selectItem - ptShowInfo->showBaseItem < 2))
        {
            Menu_SetShowBaseItem(ptShowInfo->showBaseItem - 1);
            ptShowInfo->showBaseItem -= 1;
        }

        if (pps_mode != FS2711_Lib.pdo_num)
            tmpselect = i + ptShowInfo->showBaseItem + 2; // ȥ��+-20mvѡ���Ӱ��
        else
            tmpselect = i + ptShowInfo->showBaseItem;

        if (pps_mode > tmpselect - 2 && i > 2)
        {
            LCD_ShowString(64, 0 + (i)*16, "      ", BLACK, BLACK, 16, 0);
        }

        if (strcmp(ptShowInfo->pszItemsDesc[tmpselect], "") != 0) // ������ǿգ�����ʾ
        {
            if (tmpselect == ptShowInfo->selectItem) // ѡ��
            {
                if (pps_mode <= tmpselect - 2) // pps mode
                {
                    FS2711_Lib.req_pdo_num = tmpselect - 2;
                    temp_mode = FS2711_PROTOCOL_PPS; // ѡ��ppsЭ��󣬲��ܰ�+-20mV
                    sg_FlashSelect.ProtocolInformation.req_pdo_num = FS2711_Lib.req_pdo_num;
                    sg_FlashSelect.ProtocolInformation.ptl_start_volt = FS2711_Lib.pdo_min_volt[FS2711_Lib.req_pdo_num];
                    sg_FlashSelect.ProtocolInformation.ptl_end_volt = FS2711_Lib.pdo_min_volt[FS2711_Lib.req_pdo_num];
                    sg_FlashSelect.ProtocolInformation.ptl_max_curr = FS2711_Lib.pdo_max_curr[FS2711_Lib.req_pdo_num];
                    pps_sel = 0;
                    sprintf(PdMenuVolt[tmpselect - 2], "%.1fV-", FS2711_Lib.pdo_min_volt[tmpselect - 2] * 1.0 / 1000.0); //
                    LCD_ShowString(72, 0 + (i)*16, (u8 *)(ptShowInfo->pszItemsDesc[tmpselect]), BLACK, LBBLUE, 16, 0);
                    sprintf(PdMenuVolt[tmpselect - 2], "%.1fV ", FS2711_Lib.pdo_max_volt[tmpselect - 2] * 1.0 / 1000.0); //
                    LCD_ShowString(112, 0 + (i)*16, (u8 *)(ptShowInfo->pszItemsDesc[tmpselect]), BLACK, LBBLUE, 16, 0);
                }
                else
                {
                    LCD_ShowString(112, 0 + (i)*16, (u8 *)(ptShowInfo->pszItemsDesc[tmpselect]), BLACK, LBBLUE, 16, 0);
                    if (pps_mode != FS2711_Lib.pdo_num)
                        FS2711_Lib.req_pdo_num = tmpselect - 2;
                    else
                        FS2711_Lib.req_pdo_num = tmpselect;
                    pps_sel = 0;
                    temp_mode = FS2711_PROTOCOL_PD;
                    sg_FlashSelect.ProtocolInformation.req_pdo_num = FS2711_Lib.req_pdo_num;
                    sg_FlashSelect.ProtocolInformation.ptl_start_volt = FS2711_Lib.pdo_min_volt[FS2711_Lib.req_pdo_num];
                    sg_FlashSelect.ProtocolInformation.ptl_end_volt = FS2711_Lib.pdo_max_volt[FS2711_Lib.req_pdo_num];
                    sg_FlashSelect.ProtocolInformation.ptl_max_curr = FS2711_Lib.pdo_max_curr[FS2711_Lib.req_pdo_num];
                }
            }
            else
            {
                if (pps_mode <= tmpselect - 2) // pps mode
                {
                    sprintf(PdMenuVolt[tmpselect - 2], "%.1fV-", FS2711_Lib.pdo_min_volt[tmpselect - 2] * 1.0 / 1000.0); //
                    LCD_ShowString(72, 0 + (i)*16, (u8 *)(ptShowInfo->pszItemsDesc[tmpselect]), BRRED, BLACK, 16, 0);
                    sprintf(PdMenuVolt[tmpselect - 2], "%.1fV ", FS2711_Lib.pdo_max_volt[tmpselect - 2] * 1.0 / 1000.0); //
                    LCD_ShowString(112, 0 + (i)*16, (u8 *)(ptShowInfo->pszItemsDesc[tmpselect]), BRRED, BLACK, 16, 0);
                }
                else
                    LCD_ShowString(112, 0 + (i)*16, (u8 *)(ptShowInfo->pszItemsDesc[tmpselect]), BRRED, BLACK, 16, 0);
            }
        }
        else
            LCD_ShowString(100, 0 + (i)*16, "      ", BLACK, BLACK, 16, 0);
    }
    char strbuf[20] = {0};
    sprintf(strbuf, "%.2fV ", sg_FlashSelect.ProtocolInformation.ptl_select_volt / 1000.0);
    LCD_ShowString(56, 32, (u8 *)strbuf, MAGENTA, BLACK, 16, 0); //
}

void OnPDFunctionLoad(void)
{
    LCD_Fill(0, 0, 160, 80, BLACK); /*! 160*80 ��ʼ�� */
    LCD_Roll(sg_FlashSelect.ScrenDeirection);
    Menu_Bind(sg_PDMenuTable, GET_MENU_NUM(sg_PDMenuTable), ShowPdMainMenu);
    Key_Register_PD();

    sg_FlashSelect.MenuSelect = 0;
    sg_FlashSelect.IsFsReset = true;
    if (sg_FlashSelect.ProtocolInformation.protocol_mode != FS2711_PROTOCOL_PD)// && sg_FlashSelect.ProtocolInformation.protocol_mode != FS2711_PROTOCOL_PPS
    {
        sg_FlashSelect.ProtocolInformation.protocol_mode = FS2711_PROTOCOL_PD;
        Flash_Write();
    }
    else
        Flash_Write();

    FS2711_System_Reset();
    SysTick_Delay_Ms(500);

    //<! ��ѯPD��Ϣ֮ǰ�����˳���ǰ��Э�飬��Ϊ��ѯPD��Ϣ��Ҫ����PD,����PPSģʽ
    FS2711_Enable_Protocol(0); //<! �˳���ǰЭ��
    FS2711_Port_Reset();
    FS2711_Select_Protocol(sg_FlashSelect.ProtocolInformation.protocol_mode); //<! ����Э��
    FS2711_Enable_Protocol(1);
    /*! ���д��������Ч��PDЭ���л�����ȫ�Ͽ���Դ�������д�����Ч */
    SysTick_Delay_Ms(500);

    FS2711_Get_State();
}

void OnPDFunctionExit(void)
{
    LCD_Fill(0, 0, 160, 80, BLACK); /*! 160*80 ��ʼ�� */
    Key_Start_Task();
    sg_FlashSelect.IsFsReset = false;
    Flash_Write();
    FS2711_Lib.req_pdo_num = 0;
   /*  FS2711_System_Reset();
    SysTick_Delay_Ms(500);
    FS2711_Enable_Protocol(0); //<! �˳���ǰЭ��
    SysTick_Delay_Ms(500);
    FS2711_Port_Reset();
    SysTick_Delay_Ms(500); */
    
    sg_FlashSelect.ProtocolInformation.ptl_select_volt = 5000;
    EnableNewProtocol(FS2711_PROTOCOL_PD); // ���ĳ����һ����Э�飬��ֹ���ֻ�
}

void OnPDFunction(void)
{
    char strbuf[256];
    Get_Average_ADC_Converted_Value();

    sprintf(strbuf, "%.2fV ", ADC_Calculation_Value.SampleVoltage);
    LCD_ShowString(0, 32, (u8 *)strbuf, LIGHTGREEN, BLACK, 16, 0); //

    sprintf(strbuf, "%.2fA ", ADC_Calculation_Value.SampleCurrent);
    LCD_ShowString(0, 48, (u8 *)strbuf, LGRAY, BLACK, 16, 0); //

    sprintf(strbuf, "%.2fw ", ADC_Calculation_Value.SampleCurrent * ADC_Calculation_Value.SampleVoltage);
    LCD_ShowString(0, 64, (u8 *)strbuf, BRRED, BLACK, 16, 0); //
}

const uint16_t QC_Value[]={
5000,9000,12000,20000
};
MenuList_t sg_QCMenuTable[] =
{
    {"+200mV", "+200mV", NULL, NULL, NULL, NULL},
    {"-200mV", "-200mV", NULL, NULL, NULL, NULL},
    {"5V", "5V", NULL, NULL, NULL, NULL},
    {"9V", "9V", NULL, NULL, NULL, NULL},
    {"12V", "12V", NULL, NULL, NULL, NULL},
    {"20V", "20V", NULL, NULL, NULL, NULL},
};


void Set_QC_Protocol(void)
{
    EnableNewProtocol(temp_mode);
}
void QC_Ok(void)
{
    if (pps_sel == 0)
    {
         if (temp_mode == FS2711_PROTOCOL_QC2B)
        {
            sg_FlashSelect.ProtocolInformation.ptl_select_volt = sg_FlashSelect.ProtocolInformation.ptl_start_volt;
        }
        if (sg_FlashSelect.ProtocolInformation.ptl_select_volt == 20000)
            temp_mode = FS2711_PROTOCOL_QC3B;
        Set_QC_Protocol();
    }
    else
    {
        if (pps_sel == 1)
        {
            if (temp_mode == FS2711_PROTOCOL_QC3B)
            {
                sg_FlashSelect.ProtocolInformation.ptl_select_volt += 200;
                if (sg_FlashSelect.ProtocolInformation.ptl_select_volt > 20000)
                    sg_FlashSelect.ProtocolInformation.ptl_select_volt = 20000;
                sg_FlashSelect.ProtocolInformation.ptl_end_volt = sg_FlashSelect.ProtocolInformation.ptl_select_volt;
                EnableNewProtocol(FS2711_PROTOCOL_QC3B);
            }
        }
        else if (pps_sel == 2)
        {
            if (temp_mode == FS2711_PROTOCOL_QC3B)
            {
                sg_FlashSelect.ProtocolInformation.ptl_select_volt -= 200;
                if (sg_FlashSelect.ProtocolInformation.ptl_select_volt < 3600)
                    sg_FlashSelect.ProtocolInformation.ptl_select_volt = 3600;
                sg_FlashSelect.ProtocolInformation.ptl_end_volt = sg_FlashSelect.ProtocolInformation.ptl_select_volt;
                EnableNewProtocol(FS2711_PROTOCOL_QC3B);
            }
        }
    }
}

void OnKeyOkQCProess(IoKeyType_e eKey, KeyAction_e eAction)
{
    static uint8_t cnt = 0;

    if (KEY_ACTION_PRESS == eAction)
    {
        KEY_SetNotifyTime(eKey, 800); // 2��󣬰������ܱ�Ϊ����
        if (KEY_GetPressTime(eKey) >= 800)
        {
            KEY_SetNotifyTime(eKey, 0); // ��ʵҲ�������ã���������ã���Ч��Ϊÿ3�룬�ͷ���һ�Σ����ú�ֻ����һ��
            Key_Ok_Func = 'N';
            Menu_Exit(false); // ������һ���˵�����
        }
    }

    uint8_t click = KEY_GetClickCnt(eKey, 200);
    if (2 == click)
    {
        if ('N' != Key_Ok_Func)
        {
            if (cnt % 2 == 1)
            {
                Screen_Roll = !Screen_Roll;
                LCD_Roll(Screen_Roll);
            }
            else
            {
                Screen_Roll = !Screen_Roll;
                LCD_Roll(Screen_Roll);
            }
            cnt++;
            sg_FlashSelect.ScrenDeirection = Screen_Roll;
        }
        else
            Key_Ok_Func = 'B';
    }
    else if (1 == click)
    {
        if ('N' == Key_Ok_Func)
        {
            Key_Ok_Func = 'B';
        }
        else
        {
            Key_Ok_Func = 'O'; // ȷ�ϼ�������˵�����ִ�й���
            QC_Ok();           // Menu_Enter();
        }
    }
}
void Key_Register_QC(void)
{
    // KEY_Register(IO_KEY_UP, OnKeyActionPDProess);
    // KEY_Register(IO_KEY_DOWN, OnKeyActionPDProess);
    KEY_Register(IO_KEY_OK, OnKeyOkQCProess);
}

void ShowQCMainMenu(MenuShow_t *ptShowInfo)
{
    menusize_t ShowNum;
    menusize_t tmpselect;
    ShowNum = 7;
    Menu_LimitShowListNum(ptShowInfo, &ShowNum);
    int i;

    if (sg_FlashSelect.ProtocolInformation.protocol_mode == FS2711_PROTOCOL_QC2B)
        LCD_ShowString(0, 0, "QC2 ", LGRAY, BLACK, 24, 0);
    else
        LCD_ShowString(0, 0, "QC3 ", LGRAY, BLACK, 24, 0);

    if (ptShowInfo->selectItem == 0)
    {
        pps_sel = 1; //ѡ��+200mV
        temp_mode = FS2711_PROTOCOL_QC3B;
        LCD_ShowString(44, 0, (u8 *)(ptShowInfo->pszItemsDesc[0]), BLACK, GREEN, 16, 0);
    }
    else
    {
        LCD_ShowString(44, 0, (u8 *)(ptShowInfo->pszItemsDesc[0]), GREEN, BLACK, 16, 0);
    }
    if (ptShowInfo->selectItem == 1)
    {
        pps_sel = 2; //ѡ��-200mV
        temp_mode = FS2711_PROTOCOL_QC3B;
        LCD_ShowString(44, 16, (u8 *)(ptShowInfo->pszItemsDesc[1]), BLACK, GREEN, 16, 0);
    }
    else
        LCD_ShowString(44, 16, (u8 *)(ptShowInfo->pszItemsDesc[1]), GREEN, BLACK, 16, 0);


    for (i = 2; i < ShowNum; i++)
    {
        tmpselect = i + ptShowInfo->showBaseItem;//�ó�ѡ�����б����λ��

        if (strcmp(ptShowInfo->pszItemsDesc[tmpselect], "") != 0) // ������ǿգ�����ʾ
        {
            if (tmpselect == ptShowInfo->selectItem) // ѡ��
            {
                temp_mode = FS2711_PROTOCOL_QC2B;
                sg_FlashSelect.ProtocolInformation.ptl_start_volt = QC_Value[i-2];
                sg_FlashSelect.ProtocolInformation.ptl_end_volt = QC_Value[i-2];
                sg_FlashSelect.ProtocolInformation.ptl_max_curr = 0;
                pps_sel = 0;//�̶�ģʽ
                LCD_ShowString(112, 0 + (i-2)*16, (u8 *)(ptShowInfo->pszItemsDesc[tmpselect]), BLACK, LBBLUE, 16, 0);
            }
            else
            {
                LCD_ShowString(112, 0 + (i-2)*16, (u8 *)(ptShowInfo->pszItemsDesc[tmpselect]), BRRED, BLACK, 16, 0);
            }
        }
        else
            LCD_ShowString(100, 0 + (i)*16, "      ", BLACK, BLACK, 16, 0);
    }
    char strbuf[20] = {0};
    sprintf(strbuf, "%.2fV ", sg_FlashSelect.ProtocolInformation.ptl_select_volt / 1000.0);
    LCD_ShowString(56, 32, (u8 *)strbuf, MAGENTA, BLACK, 16, 0); //
}

void OnQCFunctionLoad(void)
{
    LCD_Fill(0, 0, 160, 80, BLACK); /*! 160*80 ��ʼ�� */
    LCD_Roll(sg_FlashSelect.ScrenDeirection);
    Menu_Bind(sg_QCMenuTable, GET_MENU_NUM(sg_QCMenuTable), ShowQCMainMenu);
    Key_Register_QC();

    sg_FlashSelect.MenuSelect = 1;
    sg_FlashSelect.IsFsReset = true;
    //sg_FlashSelect.ProtocolInformation.protocol_mode = FS2711_PROTOCOL_QC2B;
    sg_FlashSelect.ProtocolInformation.ptl_select_volt = 5000;
    sg_FlashSelect.ProtocolInformation.ptl_start_volt = 5000;
    sg_FlashSelect.ProtocolInformation.ptl_end_volt = 5000;
    sg_FlashSelect.ProtocolInformation.ptl_max_curr = 0;
    if(sg_FlashSelect.ProtocolInformation.protocol_mode != 0)
    {
        sg_FlashSelect.ProtocolInformation.protocol_mode = 0;
        Flash_Write();
        FS2711_Port_Disconnect();		// ͨ���Ͽ��˿ڵ��裬ʹ���ֻ�����ͨ���Լ���Э�飻ֻ�ڲ���������ʹ��
        mcuRestart();
    }
    else
    {
        sg_FlashSelect.ProtocolInformation.protocol_mode = FS2711_PROTOCOL_QC2B;
    }
    Flash_Write();
    FS2711_System_Reset();
    SysTick_Delay_Ms(500);
    FS2711_Enable_Protocol(0); //<! �˳���ǰЭ��
    FS2711_Port_Reset();
    FS2711_Select_Protocol(FS2711_PROTOCOL_QC2B);
    //SysTick_Delay_Ms(500);
    //SysTick_Delay_Ms(500);
    LCD_ShowString(16, 36, "wait a moment", BLACK, LBBLUE, 16, 0);
    FS2711_Enable_Protocol(1);
    SysTick_Delay_Ms(2500);
    LCD_Fill(0, 0, 160, 80, BLACK); /*! 160*80 ��ʼ�� */
    FS2711_Select_Voltage_Current(FS2711_PROTOCOL_QC2B, 5000, 5000, 0);
    FS2711_Enable_Voltage_Current();

    //<! ��ѯPD��Ϣ֮ǰ�����˳���ǰ��Э�飬��Ϊ��ѯPD��Ϣ��Ҫ����PD,����PPSģʽ
    FS2711_Select_Protocol(sg_FlashSelect.ProtocolInformation.protocol_mode); //<! ����Э��
    FS2711_Enable_Protocol(1); 
    
    //EnableNewProtocol(FS2711_PROTOCOL_QC2B);

}

void OnQCFunctionExit(void)
{
    LCD_Fill(0, 0, 160, 80, BLACK); /*! 160*80 ��ʼ�� */
    Key_Start_Task();
    sg_FlashSelect.IsFsReset = false;
    sg_FlashSelect.ProtocolInformation.ptl_select_volt = 5000;
    Flash_Write();
    /* FS2711_Select_Voltage_Current(sg_FlashSelect.ProtocolInformation.protocol_mode, 5000, 5000, 0);        
    FS2711_Enable_Voltage_Current();
    SysTick_Delay_Ms(500);
    FS2711_System_Reset();
    SysTick_Delay_Ms(500);
    FS2711_Enable_Protocol(0); //<! �˳���ǰЭ��
    FS2711_Port_Reset(); */
    EnableNewProtocol(FS2711_PROTOCOL_QC2B); // ���ĳ����һ����Э�飬��ֹ���ֻ�
}

void OnQCFunction(void)
{
    char strbuf[256];
    Get_Average_ADC_Converted_Value();

    sprintf(strbuf, "%.2fV ", ADC_Calculation_Value.SampleVoltage);
    LCD_ShowString(0, 32, (u8 *)strbuf, LIGHTGREEN, BLACK, 16, 0); //

    sprintf(strbuf, "%.2fA ", ADC_Calculation_Value.SampleCurrent);
    LCD_ShowString(0, 48, (u8 *)strbuf, LGRAY, BLACK, 16, 0); //

    sprintf(strbuf, "%.2fw ", ADC_Calculation_Value.SampleCurrent * ADC_Calculation_Value.SampleVoltage);
    LCD_ShowString(0, 64, (u8 *)strbuf, BRRED, BLACK, 16, 0); //
}
