/**
  **********************************************************************************************************************
  * @file    key.c
  * @brief   ���ļ��ṩ��������ʶ����
  * @author  const_zpc  any question please send mail to const_zpc@163.com
  * @version V3.0.0
  * @date    2022-03-27
  *
  * @details  ������ϸ˵����
  *           + ������ʼ��
  *           + ������������
  *           + ����������Ϣ��ȡ
  *           + ������ѯ����
  *
  **********************************************************************************************************************
  * Դ��·����https://gitee.com/const-zpc/key.git �������⼰������ڸ���ַ��д Issue
  *
  * ʹ�÷�ʽ:
  *    1��ʹ��ǰ��ʼ������ KEY_Init
  *    2�����ڵ��ú��� KEY_Scan, ��������������ʶ��ʹ���
  *    3��ʹ�����������Ի�ȡ��������������Ϣ
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "key.h"
#include "keyio.h"

/* Private typedef ---------------------------------------------------------------------------------------------------*/

/**
  * @brief ����������Ϣ�ṹ�嶨��
  */
typedef struct
{
    KeyAction_e eKeyAction;                     /*!< ָ����ѡ�����Ķ���״̬ */

    KeyAction_e eKeyActionBak;                  /*!< ָ����ѡ�����Ķ���״̬���� */

    uint8_t clickCnt;                           /*!< ָ����ѡ�����ĵ������� */

    uint16_t uiPressTic;                        /*!< ָ����ѡ�����İ����ۼ�ʱ��, �ò�����λΪ1ms,��ֵ��ֵΪ0 */

    uint16_t uiLossenTic;                       /*!< ָ����ѡ�������ɿ��ۼ�ʱ��, �ò�����λΪ1ms,��ֵ��ֵΪ0 */

    uint16_t uiAntiShakeTime;                   /*!< ָ����ѡ�����ķ���ʱ��, �ò�����λΪ1ms */
    
    uint16_t refreshNotifyTic;					/*!< ָ����ѡ�����Ĵ����ص�֪ͨ�����Ķ�ʱ��ʱ, ��λΪ1ms */

    KeyFunCB pfnKeyNotifyFun;                   /*!< ָ����ѡ�����Ķ����ı�ص�֪ͨ���� */
} KeyManage_t;

/* Private define ----------------------------------------------------------------------------------------------------*/

/** ��������ʱ�� */
#define KEY_ANTI_SHAKE_TIME      20

/* Private macro -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/

static KeyManage_t sg_tKeyManage[IO_KEY_MAX_NUM];

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/* Private function --------------------------------------------------------------------------------------------------*/

/**
  * @brief ������ʼ��
  *
  */
void KEY_Init(void)
{
    uint8_t key;

    for (key = 0; key < IO_KEY_MAX_NUM; key++)
    {
        sg_tKeyManage[key].eKeyAction = KEY_ACTION_NO_PRESS;
        sg_tKeyManage[key].eKeyActionBak = KEY_ACTION_NO_PRESS;
        sg_tKeyManage[key].clickCnt = 0;
        sg_tKeyManage[key].uiPressTic = 0;
        sg_tKeyManage[key].uiLossenTic = 0;
        sg_tKeyManage[key].uiAntiShakeTime = KEY_ANTI_SHAKE_TIME;
        sg_tKeyManage[key].refreshNotifyTic = 0;
        sg_tKeyManage[key].pfnKeyNotifyFun = NULL;
    }

    IoKey_Init();
}

/**
  * @brief      ע�ᰴ�������ı�ʱ��֪ͨ�ص�����
  *
  * @param[in]  eKey ָ������, ȡֵΪ @reg IoKeyType_e
  * @param[in]  pKeyFun ֪ͨ�ص�����
  */
void KEY_Register(IoKeyType_e eKey, KeyFunCB pKeyFun)
{
    if (eKey < IO_KEY_MAX_NUM)
    {
        sg_tKeyManage[eKey].pfnKeyNotifyFun = pKeyFun;
    }
}

/**
  * @brief      ע�����������ı�ʱ��֪ͨ�ص�����
  *
  * @param[in]  eKey ָ������, ȡֵΪ @reg IoKeyType_e
  */
void KEY_UnRegister(IoKeyType_e eKey)
{
    if (eKey < IO_KEY_MAX_NUM)
    {
        sg_tKeyManage[eKey].pfnKeyNotifyFun = NULL;
    }
}

/**
  * @brief      ���ð�������ʱ��
  * 
  * @param[in]  eKey ָ������, ȡֵΪ @reg IoKeyType_e
  * @param[in]  time �´δ��������¼��ص�������ʱ��
  */
void KEY_SetNotifyTime(IoKeyType_e eKey, uint16_t time)
{
    if (eKey < IO_KEY_MAX_NUM)
    {
        sg_tKeyManage[eKey].refreshNotifyTic = time;
    }
}

/**
  * @brief      ��ȡ������������
  * 
  * @note       ���øú���ʱ�����й��ڰ�����������������
  * @param[in]  eKey ָ������, ȡֵΪ @reg IoKeyType_e
  * @param[in]  time ÿ�ε����ļ��ʱ��
  * @retval     ��������.
  */
uint8_t KEY_GetClickCnt(IoKeyType_e eKey, uint16_t time)
{
    if (eKey >= IO_KEY_MAX_NUM)
    {
        return 0;
    }

    /* ���������󣬻�ȼ��ʱ���ٽ��лص�֪ͨ, Ŀ������ȫ�ɿ������󣬿����ٴδ������ص��������������¼��ɺ����ڶ����任�ڼ��ʱ���ڣ�������÷������ */
    if (sg_tKeyManage[eKey].eKeyAction == KEY_ACTION_LOSSEN)
    {
        sg_tKeyManage[eKey].refreshNotifyTic = time;
    }
    
    if (sg_tKeyManage[eKey].eKeyAction == KEY_ACTION_PRESS)
    {
        if (sg_tKeyManage[eKey].clickCnt < 0xFF)
        {
            sg_tKeyManage[eKey].clickCnt++;
        }
    }
		
		//�ر�LOSSEN���NO_PRESS״̬���Ӷ��ﵽ����������Ŀ��
    if (sg_tKeyManage[eKey].eKeyAction == KEY_ACTION_NO_PRESS && sg_tKeyManage[eKey].uiLossenTic >= time)
    {
        uint8_t cnt = sg_tKeyManage[eKey].clickCnt;
        
        sg_tKeyManage[eKey].clickCnt = 0;
        return cnt;
    }
    
    return 0;
}

/**
  * @brief      ��ȡ��������ʱ��
  *
  * @param[in]  eKey ָ������, ȡֵΪ @reg IoKeyType_e
  * @retval     ��������ʱ��, ��λms.
  */
uint16_t KEY_GetPressTime(IoKeyType_e eKey)
{
    if (eKey >= IO_KEY_MAX_NUM)
    {
        return 0;
    }

    return sg_tKeyManage[eKey].uiPressTic;
}

/**
  * @brief      ��ȡ�����ɿ�ʱ��
  *
  * @param[in]  eKey ָ������, ȡֵΪ @reg IoKeyType_e
  * @retval     �����ɿ�ʱ��, ��λms.
  */
uint16_t KEY_GetLossenTime(IoKeyType_e eKey)
{
    if (eKey >= IO_KEY_MAX_NUM)
    {
        return 0;
    }

    return sg_tKeyManage[eKey].uiLossenTic;
}

/**
  * @brief      ����ɨ����������Action״̬�����Ⱥ�˳��NO_PRESS -> PRESS -> LOSSEN -> NO_PRESS
  *
  * @param[in]  cycleTime ����ʱ��, ��λms.
  */
void KEY_Scan(uint16_t cycleTime)
{
    uint8_t key;
    IoKeyState_e eKeyState;

    IoKey_Scan();//����IO��״̬

    for (key = 0; key < IO_KEY_MAX_NUM; key++)
    {
        eKeyState = IoKey_Read((IoKeyType_e)key);

        if (eKeyState == IO_KEY_OFF)//��
        {
            if (sg_tKeyManage[key].eKeyAction == KEY_ACTION_PRESS)//����״̬
            {
                if (sg_tKeyManage[key].uiLossenTic < (0xFFFF - cycleTime))
                {
                    sg_tKeyManage[key].uiLossenTic += cycleTime;
                }

                if (sg_tKeyManage[key].uiLossenTic >= sg_tKeyManage[key].uiAntiShakeTime)
                {
                    sg_tKeyManage[key].eKeyAction = KEY_ACTION_LOSSEN;
                }
            }
            else//�����ɿ���δ���¡�����LOSSEN״ֻ̬����������PRESS֮�󣬲���ֻ��ά��һ��cycle������LOSSEN֮��ת��ΪNO_PRESS
            {
                sg_tKeyManage[key].eKeyAction = KEY_ACTION_NO_PRESS;
                sg_tKeyManage[key].uiPressTic = 0;

                if (sg_tKeyManage[key].uiLossenTic < (0xFFFF - cycleTime))
                {
                    sg_tKeyManage[key].uiLossenTic += cycleTime;
                }
            }
        }
        else//��
        {
            if (sg_tKeyManage[key].eKeyAction != KEY_ACTION_LOSSEN)//����������δ���� ״̬
            {
                if (sg_tKeyManage[key].eKeyAction == KEY_ACTION_PRESS)//����
                {
                    sg_tKeyManage[key].uiLossenTic = 0;
                }

                if (sg_tKeyManage[key].uiPressTic < (0xFFFF - cycleTime))
                {
                    sg_tKeyManage[key].uiPressTic += cycleTime;
                }

                if (sg_tKeyManage[key].uiPressTic >= sg_tKeyManage[key].uiAntiShakeTime)
                {
                    sg_tKeyManage[key].eKeyAction = KEY_ACTION_PRESS;
                }
            }
            else//�����ɿ�״̬������ɨ��ģʽ�£�������ְ����ɿ��Ժ������ְ��µ��������Ϊʱ��Ƭ10ms������ǰ����ɿ������ְ��£���Զ����10ms��������֣����Ƕ���
            {
                sg_tKeyManage[key].eKeyAction = KEY_ACTION_NO_PRESS;
                sg_tKeyManage[key].uiPressTic = 0;
                sg_tKeyManage[key].uiLossenTic = 1;
            }
        }
        
        //�ж��갴��״̬�Ժ󣬿�ʼ����ص�����
        if (sg_tKeyManage[key].pfnKeyNotifyFun != NULL)
        {
            if (sg_tKeyManage[key].refreshNotifyTic > 0)//�ӳٻص��������ڳ����̶�ʱ�䣬�����̰�����������Ч�ر�״̬������ת������ĳһ��״̬�ٳ�
            {
                if (sg_tKeyManage[key].refreshNotifyTic >= cycleTime)
                {
                    sg_tKeyManage[key].refreshNotifyTic -= cycleTime;
                }
                else
                {
                    sg_tKeyManage[key].refreshNotifyTic = 0;
                }
                
                if (sg_tKeyManage[key].refreshNotifyTic == 0)
                {
                    sg_tKeyManage[key].pfnKeyNotifyFun((IoKeyType_e)key, sg_tKeyManage[key].eKeyAction);
                }
            }
            
            if (sg_tKeyManage[key].eKeyAction != sg_tKeyManage[key].eKeyActionBak)//״̬�ı䣬�����������������Ƚ���ص��������ڻص��������޸��ӳٴ���tick��ʹ֮����0�������ص�����ͻᴦ����ʱ�ص�����
            {
                sg_tKeyManage[key].pfnKeyNotifyFun((IoKeyType_e)key, sg_tKeyManage[key].eKeyAction);
            }
        }

        sg_tKeyManage[key].eKeyActionBak = sg_tKeyManage[key].eKeyAction;
    }
}
