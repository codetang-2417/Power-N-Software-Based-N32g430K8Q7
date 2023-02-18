/**
 **********************************************************************************************************************
 * @file    keyio.c
 * @brief   ���ļ��ṩ����Ӳ���ӿ�ʵ�ֹ���
 * @author  const_zpc  any question please send mail to const_zpc@163.com
 * @version V3.0.0
 * @date    2022-03-27
 *
 *
 **********************************************************************************************************************
 *
 *  ��ֲʱ�ں��� InitKeyIo ��ʵ�� IO �ĳ�ʼ������, ͬʱ����ö�� @reg IoKeyType_e, Ϊÿ��ʵ�尴�������ⰴ������Щ����
 *  ��һ����һ�� IO ��Ӧ����, ����ΰ���������ң�ذ����ȣ�����һ��ö��ֵ���� 0 ��ʼ����Ȼ���ں��� IoKey_Scan �еõ�ÿ
 *  ��ʵ�尴�������ⰴ������ʱ��״̬������ IO_KEY_ON ��
 *
 **********************************************************************************************************************
 */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "keyio.h"

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------------------------------------------*/
/* Private macro -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/

static IoKeyState_e sg_arrKeyState[IO_KEY_MAX_NUM];

/* Private function prototypes ---------------------------------------------------------------------------------------*/
static void InitKeyIo(void);
/* Private function --------------------------------------------------------------------------------------------------*/

static void InitKeyIo(void)
{
	// ʵ�� IO ����س�ʼ��
	GPIO_InitType GPIO_InitStructure;

	RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_GPIOA | RCC_AHB_PERIPH_GPIOB);
	GPIO_Structure_Initialize(&GPIO_InitStructure);

	/* Select the GPIO pin to control */
	GPIO_InitStructure.Pin = GPIO_PIN_2 | GPIO_PIN_15;
	/* Set pin mode to general push-pull output */
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
	/* Initialize GPIO */
	GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_7;
	/* Set pin mode to general push-pull output */
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;

	/* Initialize GPIO */
	GPIO_Peripheral_Initialize(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief      ����������ʼ��
 *
 */
void IoKey_Init(void)
{
	uint8_t i;

	for (i = 0; i < IO_KEY_MAX_NUM; i++)
	{
		sg_arrKeyState[i] = IO_KEY_OFF;
	}

	InitKeyIo();
}

/**
 * @brief      ��ȡ���� IO ״̬
 *
 * @param[in]  eKey ָ������, ȡֵΪ @reg IoKeyType_e
 * @retval     ���� IO ״̬, ȡֵΪ @reg IoKeyState_e.
 */
IoKeyState_e IoKey_Read(IoKeyType_e eKey)
{
	if (eKey < IO_KEY_MAX_NUM)
	{
		return sg_arrKeyState[eKey];
	}

	return IO_KEY_OFF;
}

/**
 * @brief      ���� IO ɨ������
 *
 */
void IoKey_Scan(void)
{
	// ʵ�� IO �����״̬
	sg_arrKeyState[IO_KEY_UP] = (IoKeyState_e)!GPIO_Input_Pin_Data_Get(GPIOA, GPIO_PIN_15);	 // ��ȡ����0
	sg_arrKeyState[IO_KEY_DOWN] = (IoKeyState_e)!GPIO_Input_Pin_Data_Get(GPIOA, GPIO_PIN_2); // ��ȡ����1
	sg_arrKeyState[IO_KEY_OK] = (IoKeyState_e)!GPIO_Input_Pin_Data_Get(GPIOB, GPIO_PIN_7);	 // ��ȡ����2
}
