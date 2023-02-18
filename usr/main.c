#include "sysclk.h"
#include "lcd.h"
#include "adc.h"
#include "key.h"
#include "ui.h"
#include <stdio.h>
#include "i2c.h"
#include "decoy.h"
#include "flash.h"

void OnKeyActionProess(IoKeyType_e eKey, KeyAction_e eAction);


/**
 * @brief ��ʼ��������ʱ��6����ʼ���Ķ�ʱƵ��Ϊ��64MHz/(prescaler+1)/(period+1) MHz
 * 
 * @param period ��ʱ���ļ����Ĵ�����ֵ
 * @param prescaler Ԥ��Ƶ�Ĵ�����ֵ
 */
void Tim6_Init(uint16_t period, uint16_t prescaler)
{
	TIM_TimeBaseInitType TIM_TimeBaseStructure;

	RCC_APB1_Peripheral_Clock_Enable(RCC_APB1_PERIPH_TIM6);

	NVIC_InitType NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Initializes(&NVIC_InitStructure);

	TIM_Base_Struct_Initialize(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.Period = period;
	TIM_TimeBaseStructure.Prescaler = prescaler;
	TIM_TimeBaseStructure.ClkDiv = 0;
	TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;

	TIM_Base_Initialize(TIM6, &TIM_TimeBaseStructure);

	TIM_Base_Reload_Mode_Set(TIM6, TIM_PSC_RELOAD_MODE_IMMEDIATE);

	TIM_Interrupt_Enable(TIM6, TIM_INT_UPDATE);//���������磬�����ֶ���λʱ�������

	TIM_On(TIM6);
}

/**
 * @brief  ��ʱ��6�жϷ������
 * @retval None
 */
static uint32_t cnt = 0;
void TIM6_IRQHandler(void)
{
	
	if (TIM_Interrupt_Status_Get(TIM6, TIM_INT_UPDATE) != RESET)
	{
		TIM_Interrupt_Status_Clear(TIM6, TIM_INT_UPDATE);
		cnt++;
		if (0 == cnt%10)
		{
			KEY_Scan(10);//10ms ɨ��һ�ΰ���
		}
		if(100 == cnt)
		{
			Menu_Task();//100msˢ��һ����Ļ
			cnt = 0;
		}
	}
}

//char strbuf[256];
bool IsReset = false;
int main(void)
{
	Set_SysClock_To_PLL128MHz();
	ADC_Configuration();
	LCD_Init();
	KEY_Init();
	Key_Start_Task();
	FS2711_GPIO_Init();
	FS2711_Enable_Protocol(0);/* ֹͣоƬ����Э�飬����оƬ�ᷢ��Ĭ�ϵ�Э�� */
	Flash_Read();
	
	MainMenuCfg_t tMainMenu;
	
	tMainMenu.pszDesc = "���˵�";
	tMainMenu.pszEnDesc = "Main Menu";
	tMainMenu.pfnLoadCallFun = UI_Main_Load;
	tMainMenu.pfnRunCallFun = UI_Main_Task;

	Menu_Init(&tMainMenu);

	Init_FS2711();
	Tim6_Init(63, 1000);
	while (1)
	{		
		
	}
}


