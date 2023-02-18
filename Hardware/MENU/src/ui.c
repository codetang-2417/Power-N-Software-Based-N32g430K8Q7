#include "ui.h"
#include "key.h"
#include "ui_measure.h"
#include "ui_adjust.h"
#include "picture.h"
#include "lcd.h"

char Key_Ok_Func = 'B';
bool Screen_Roll = false;
extern bool MeasureFlag;
extern bool ConnectFlag;

void OnKeyActionProessUp(IoKeyType_e eKey, KeyAction_e eAction)
{
	if (IO_KEY_UP == eKey)
	{
		if (KEY_ACTION_LOSSEN == eAction)
		{
			if (!Screen_Roll)
				Menu_SelectPrevious(true);
			else
				Menu_SelectNext(true);
		}
	}
}

void OnKeyActionProessDown(IoKeyType_e eKey, KeyAction_e eAction)
{
	if (IO_KEY_DOWN == eKey)
	{
		if (KEY_ACTION_LOSSEN == eAction)
		{
			if (Screen_Roll)
				Menu_SelectPrevious(true);
			else
				Menu_SelectNext(true);
		}
	}
}
void OnKeyActionProess(IoKeyType_e eKey, KeyAction_e eAction)
{
	static uint8_t cnt = 0;
	
	if (IO_KEY_OK == eKey)
	{
		if (KEY_ACTION_PRESS == eAction)
		{
			KEY_SetNotifyTime(eKey, 800); // 2��󣬰������ܱ�Ϊ����
			if (KEY_GetPressTime(eKey) >= 800)
			{
				KEY_SetNotifyTime(eKey, 0); // ��ʵҲ�������ã���������ã���Ч��Ϊÿ3�룬�ͷ���һ�Σ����ú�ֻ����һ��
				Key_Ok_Func = 'N';
				if (MeasureFlag)
				{
					ConnectFlag = false;
					FS2711_Port_Reset(); // �ָ��˿ڵ�������
				}
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
				if (MeasureFlag)
				{
					ConnectFlag = true;
					LCD_Fill(0, 0, 160, 80, BLACK); /*! 160*80 ��ʼ�� */
					FS2711_Port_Disconnect();		// ͨ���Ͽ��˿ڵ��裬ʹ���ֻ�����ͨ���Լ���Э�飻ֻ�ڲ���������ʹ��
				}
				Menu_Enter();
			}
		}
	}
}

void Key_Start_Task(void)
{
	KEY_Register(IO_KEY_UP, OnKeyActionProessUp);
	KEY_Register(IO_KEY_DOWN, OnKeyActionProessDown);
	KEY_Register(IO_KEY_OK, OnKeyActionProess);
}

/* ���˵� */
MenuList_t sg_MainMenuTable[] =
{
	{"����", "Measure", UI_Measure_Load, UI_Measure_Exit, UI_Measure_Task, NULL},
	{"��ƭ", "Decoy", UI_Adjust_Load, UI_Adjust_Exit, UI_Adjust_Task, NULL},
};

void ShowMainMenu(MenuShow_t *ptShowInfo)
{
	if (0 == ptShowInfo->selectItem)
	{
		LCD_ShowString(10, 40 - 12, "Measure", GL_RGB_32_to_16(0XFAD40C), BLACK, 24, 0);
		LCD_ShowPicture(100, 20, 40, 40, gImage_measu); // ����
	}
	else if (1 == ptShowInfo->selectItem)
	{
		LCD_ShowString(10, 40 - 12, "Decoy  ", GL_RGB_32_to_16(0XBD8ED6), BLACK, 24, 0);
		LCD_ShowPicture(100, 20, 40, 40, gImage_Adj); // ��ƭ
	}
}

void UI_Main_Load(void)
{
	Screen_Roll = sg_FlashSelect.ScrenDeirection;
	LCD_Roll(Screen_Roll);
	LCD_Fill(0, 0, 160, 80, BLACK); /*! 160*80 ��ʼ�� */
	Menu_Bind(sg_MainMenuTable, GET_MENU_NUM(sg_MainMenuTable), ShowMainMenu);
}

void UI_Main_Task(void)
{
}
