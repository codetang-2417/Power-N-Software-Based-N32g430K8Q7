/**
 **********************************************************************************************************************
 * @file    menu.c
 * @brief   该文件提供菜单框架功能
 * @author  const_zpc  any question please send mail to const_zpc@163.com
 * @version V3.1.0
 * @date    2022-09-04
 *
 * @details  功能详细说明：
 *           + 菜单初始化函数
 *           + 返回主菜单函数
 *           + 菜单控制函数
 *           + 菜单轮询任务函数
 *
 **********************************************************************************************************************
 * 源码路径：https://gitee.com/const-zpc/menu.git 具体问题及建议可在该网址填写 Issue
 *
 * 使用方式:
 *    1、使用前初始化函数 Menu_Init, 设置主菜单内容
 *    2、周期调用函数 Menu_Task, 用来处理菜单显示和执行相关回调函数
 *    3、使用其他函数对菜单界面控制
 *
 **********************************************************************************************************************
 */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "menu.h"

#ifdef _MENU_USE_MALLOC_
#include <malloc.h>
#endif

#ifdef _MENU_USE_SHORTCUT_
#include <stdarg.h>
#endif

/* Private typedef ---------------------------------------------------------------------------------------------------*/
typedef struct MenuCtrl
{
    struct MenuCtrl *pParentMenuCtrl; /*!< 父菜单控制处理 */
    char *pszDesc;                    /*!< 当前菜单的中文字符串描述 */
    char *pszEnDesc;                  /*!< 当前菜单的英文字符串描述 */
    ShowMenuCallFun_f pfnShowMenuFun; /*!< 当前菜单显示效果函数 */
    MenuList_t *pMenuList;            /*!< 当前菜单列表 */
    MenuCallFun_f pfnLoadCallFun;     /*!< 当前菜单加载函数 */
    MenuCallFun_f pfnRunCallFun;      /*!< 当前选项的非菜单功能函数 */
    menusize_t itemsNum;              /*!< 当前菜单选项总数目 */
    menusize_t showBaseItem;          /*!< 当前菜单首个显示的选项 */
    menusize_t selectItem;            /*!< 当前菜单选中的选项 */
    bool isSelected;                  /*!< 菜单选项是否已经被选择 */
} MenuCtrl_t;

typedef struct
{
    MenuCtrl_t *pMenuCtrl; /*!< 当前菜单控制处理 */
    bool isEnglish;        /*!< 是否使能英文 */
} MenuManage_t;

/* Private define ----------------------------------------------------------------------------------------------------*/
/* Private macro -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
static MenuManage_t sg_tMenuManage;

#ifndef _MENU_USE_MALLOC_
static MenuCtrl_t sg_arrMenuCtrl[MENU_MAX_DEPTH];
#endif

static uint8_t sg_currMenuDepth = 0;

/* Private function prototypes ---------------------------------------------------------------------------------------*/
static MenuCtrl_t *NewMenu(void);
static void DeleteMenu(MenuCtrl_t *pMenu);
//static MenuCtrl_t *MianMenu(void);

/* Private function --------------------------------------------------------------------------------------------------*/
/**
 * @brief      新建菜单层级
 *
 * @return     MenuCtrl_t*
 */
static MenuCtrl_t *NewMenu(void)
{
    MenuCtrl_t *pMenuCtrl = NULL;

    if (sg_currMenuDepth < MENU_MAX_DEPTH)
    {
#ifdef _MENU_USE_MALLOC_
        pMenuCtrl = (MenuCtrl_t *)malloc(sizeof(MenuCtrl_t));
#else
        pMenuCtrl = &sg_arrMenuCtrl[sg_currMenuDepth];
#endif
        sg_currMenuDepth++;
    }

    return pMenuCtrl;
}

/**
 * @brief      销毁菜单层级
 *
 * @param      pMenu
 */
static void DeleteMenu(MenuCtrl_t *pMenu)
{
#ifdef _MENU_USE_MALLOC_
    free(pMenu);
#endif
    if (sg_currMenuDepth > 0)
    {
        sg_currMenuDepth--;
    }
}

/**
 * @brief      得到主菜单控制处理指针
 *
 * @return     MenuCtrl_t*
 *
static MenuCtrl_t *MianMenu(void)
{
    MenuCtrl_t *pMenuCtrl = sg_tMenuManage.pMenuCtrl;

    while (pMenuCtrl != NULL && pMenuCtrl->pParentMenuCtrl != NULL)
    {
        pMenuCtrl = pMenuCtrl->pParentMenuCtrl;
    }

    return pMenuCtrl;
} */

/**
 * @brief      菜单初始化
 *
 * @param[in]  pMainMenu        主菜单注册信息
 * @return     0,成功; -1,失败
 */
int Menu_Init(MainMenuCfg_t *pMainMenu)
{
    MenuCtrl_t *pNewMenuCtrl = NULL;

    if (sg_tMenuManage.pMenuCtrl != NULL) // 不为空，则已经初始化
    {
        return -1;
    }

#if MENU_MAX_DEPTH != 0
    sg_currMenuDepth = 0;
#endif

    if ((pNewMenuCtrl = NewMenu()) == NULL)
    {
        return -1;
    }

    sg_tMenuManage.isEnglish = true;

    pNewMenuCtrl->pszDesc = (char *)pMainMenu->pszDesc;
    pNewMenuCtrl->pszEnDesc = (char *)pMainMenu->pszEnDesc;
    pNewMenuCtrl->pParentMenuCtrl = NULL;
    pNewMenuCtrl->pfnLoadCallFun = pMainMenu->pfnLoadCallFun;
    pNewMenuCtrl->pfnShowMenuFun = NULL;
    pNewMenuCtrl->pfnRunCallFun = pMainMenu->pfnRunCallFun;

    pNewMenuCtrl->pMenuList = NULL;
    pNewMenuCtrl->itemsNum = 0;
    pNewMenuCtrl->selectItem = 0;
    pNewMenuCtrl->showBaseItem = 0;

    sg_tMenuManage.pMenuCtrl = pNewMenuCtrl;

    if (sg_tMenuManage.pMenuCtrl->pfnLoadCallFun != NULL)
    {
        sg_tMenuManage.pMenuCtrl->pfnLoadCallFun();
    }

    return 0;
}

/**
 * @brief  菜单反初始化
 *
 * @return 0,成功; -1,失败
 */
int Menu_DeInit(void)
{
    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return -1;
    }

    while (Menu_Exit(1) == 0)
    {
    }

    DeleteMenu(sg_tMenuManage.pMenuCtrl);
    sg_tMenuManage.pMenuCtrl = NULL;
    sg_tMenuManage.isEnglish = false;

    return 0;
}

/**
 * @brief      子菜单绑定当前菜单选项
 *
 * @param      pMenuList       新的菜单列表
 * @param      menuNum         新的菜单列表数目
 * @param      pfnShowMenuFun  新的菜单列表显示效果回调函数, 为NULL则延续上级菜单显示效果
 * @return     int
 */
int Menu_Bind(MenuList_t *pMenuList, menusize_t menuNum, ShowMenuCallFun_f pfnShowMenuFun)
{
    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return -1;
    }

    if (sg_tMenuManage.pMenuCtrl->pMenuList != NULL)
    {
        return 0;
    }

    sg_tMenuManage.pMenuCtrl->pMenuList = pMenuList;
    sg_tMenuManage.pMenuCtrl->itemsNum = menuNum;

    if (pfnShowMenuFun != NULL)
    {
        sg_tMenuManage.pMenuCtrl->pfnShowMenuFun = pfnShowMenuFun;
    }

    return 0;
}

/**
 * @brief      是否为英文显示
 *
 * @return     false,中文; true,英文
 */
bool Menu_IsEnglish(void)
{
    return sg_tMenuManage.isEnglish;
}

/**
 * @brief      使能英文显示
 *
 * @param[in]  isEnable 使能英文显示
 * @return     0,成功; -1,失败
 */
int Menu_EnableEnglish(bool isEnable)
{
    sg_tMenuManage.isEnglish = isEnable;
    return 0;
}

/**
 * @brief      复位菜单, 回到主菜单界面
 *
 * @note       该复位回到主菜单不会执行退出所需要执行的回调函数
 * @return     0,成功; -1,失败
 */
int Menu_Reset(void)
{
    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return -1;
    }

    while (sg_tMenuManage.pMenuCtrl->pParentMenuCtrl != NULL)
    {
        MenuCtrl_t *pMenuCtrl = sg_tMenuManage.pMenuCtrl;

        sg_tMenuManage.pMenuCtrl = sg_tMenuManage.pMenuCtrl->pParentMenuCtrl;
        DeleteMenu(pMenuCtrl);
    }

    sg_tMenuManage.pMenuCtrl->selectItem = 0;

    return 0;
}

/**
 * @brief      菜单功能是否正在运行
 *
 * @return     false,已停止运行; true,正在运行
 */
bool Menu_IsRun(void)
{
    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return false;
    }

    return true;
}

/**
 * @brief      进入当前菜单选项
 *
 * @return     0,成功; -1,失败
 */
int Menu_Enter(void)
{
    MenuCtrl_t *pNewMenuCtrl = NULL;
    MenuCtrl_t *pCurrMenuCtrl = sg_tMenuManage.pMenuCtrl;

    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return -1;
    }

    if ((pNewMenuCtrl = NewMenu()) == NULL)
    {
        return -1;
    }

    if (pCurrMenuCtrl->pMenuList == NULL)
    {
        return -1;
    }

    pNewMenuCtrl->pszDesc = (char *)pCurrMenuCtrl->pMenuList[pCurrMenuCtrl->selectItem].pszDesc;
    pNewMenuCtrl->pszEnDesc = (char *)pCurrMenuCtrl->pMenuList[pCurrMenuCtrl->selectItem].pszEnDesc;
    pNewMenuCtrl->pMenuList = NULL;
    pNewMenuCtrl->itemsNum = 0;
    pNewMenuCtrl->pfnShowMenuFun = pCurrMenuCtrl->pfnShowMenuFun;
    pNewMenuCtrl->pfnLoadCallFun = pCurrMenuCtrl->pMenuList[pCurrMenuCtrl->selectItem].pfnLoadCallFun;
    pNewMenuCtrl->pfnRunCallFun = pCurrMenuCtrl->pMenuList[pCurrMenuCtrl->selectItem].pfnRunCallFun;
    pNewMenuCtrl->selectItem = 0;
    pNewMenuCtrl->isSelected = true;
    pNewMenuCtrl->pParentMenuCtrl = pCurrMenuCtrl;

    sg_tMenuManage.pMenuCtrl = pNewMenuCtrl;

    if (sg_tMenuManage.pMenuCtrl->pfnLoadCallFun != NULL)
    {
        sg_tMenuManage.pMenuCtrl->pfnLoadCallFun();
    }

    return 0;
}

/**
 * @brief      退出当前选项并返回上一层菜单
 *
 * @param[in]  isReset 菜单选项是否从头选择
 * @return     0,成功; -1,失败, 即目前处于主菜单, 无法返回
 */
int Menu_Exit(bool isReset)
{
    MenuCtrl_t *pMenuCtrl = sg_tMenuManage.pMenuCtrl;


    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return -1;
    }

    if (sg_tMenuManage.pMenuCtrl->pParentMenuCtrl == NULL)
    {
        return -1;
    }

    int i = Menu_SetItemBeginLocation(0); // 读取目前的偏移
    if (i != 0)
    {
        Menu_SetItemBeginLocation(-i); // 将偏移重新置0
    }
    
    sg_tMenuManage.pMenuCtrl = sg_tMenuManage.pMenuCtrl->pParentMenuCtrl;
    DeleteMenu(pMenuCtrl);
    pMenuCtrl = NULL;

    if (sg_tMenuManage.pMenuCtrl->pMenuList[sg_tMenuManage.pMenuCtrl->selectItem].pfnExitCallFun != NULL)
    {
        sg_tMenuManage.pMenuCtrl->isSelected = false;
        sg_tMenuManage.pMenuCtrl->pMenuList[sg_tMenuManage.pMenuCtrl->selectItem].pfnExitCallFun();
    }

    
    
    if (sg_tMenuManage.pMenuCtrl->pfnLoadCallFun != NULL)
    {
        sg_tMenuManage.pMenuCtrl->pfnLoadCallFun();
    }

    if (isReset)
    {
        sg_tMenuManage.pMenuCtrl->selectItem = 0;
    }

    return 0;
}

/**
 * @brief      选择上一个菜单选项
 *
 * @param[in]  isAllowRoll 第一个选项时是否从跳转到最后一个选项
 * @return     0,成功; -1,失败
 */
int Menu_SelectPrevious(bool isAllowRoll)
{
    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return -1;
    }

    if (sg_tMenuManage.pMenuCtrl->selectItem > 0)
    {
        sg_tMenuManage.pMenuCtrl->selectItem--;
    }
    else
    {
        if (isAllowRoll)
        {
            sg_tMenuManage.pMenuCtrl->selectItem = sg_tMenuManage.pMenuCtrl->itemsNum - 1;
        }
        else
        {
            sg_tMenuManage.pMenuCtrl->selectItem = 0;
            return -1;
        }
    }

    return 0;
}

/**
 * @brief      选择下一个菜单选项
 *
 * @param[in]  isAllowRoll 最后一个选项时是否跳转到第一个选项
 * @return     0,成功; -1,失败
 */
int Menu_SelectNext(bool isAllowRoll)
{
    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return -1;
    }

    if (sg_tMenuManage.pMenuCtrl->selectItem < (sg_tMenuManage.pMenuCtrl->itemsNum - 1))
    {
        sg_tMenuManage.pMenuCtrl->selectItem++;
    }
    else
    {
        if (isAllowRoll)
        {
            sg_tMenuManage.pMenuCtrl->selectItem = 0;
        }
        else
        {
            sg_tMenuManage.pMenuCtrl->selectItem = sg_tMenuManage.pMenuCtrl->itemsNum - 1;
            return -1;
        }
    }

    return 0;
}

#ifdef _MENU_USE_SHORTCUT_

/**
 * @brief      相对主菜单或当前菜单通过下级各菜单索引快速进入指定选项
 *
 * @param[in]  isAbsolute 是否采用绝对菜单索引（从主菜单开始）
 * @param[in]  deep 菜单深度，大于 0
 * @param[in]  ...  各级菜单索引值(从0开始), 入参个数由 deep 的值决定
 * @return     0,成功; -1,失败
 */
int Menu_ShortcutEnter(bool isAbsolute, uint8_t deep, ...)
{
    uint8_t selectDeep = 0;
    va_list pItemList;
    menusize_t selectItem;

    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return -1;
    }

    if (isAbsolute)
    {
        Menu_Reset();
    }

    va_start(pItemList, deep);

    while (selectDeep < deep)
    {
        selectItem = va_arg(pItemList, menusize_t);

        if (selectItem >= sg_tMenuManage.pMenuCtrl->itemsNum)
        {
            va_end(pItemList);
            return -1;
        }

        sg_tMenuManage.pMenuCtrl->selectItem = selectItem;
        Menu_Enter();
        selectDeep++;
    }

    va_end(pItemList);

    return 0;
}

#endif

/**
 * @brief reset the number of items in the current menu
 *
 * @param itemsNum the new number of items
 * @return int 0,successful
 */
int Menu_ResetItemsNum(menusize_t itemsNum)
{
    sg_tMenuManage.pMenuCtrl->itemsNum = itemsNum;
    return 0;
}

void Menu_SetShowBaseItem(uint16_t BaseItem)
{
    sg_tMenuManage.pMenuCtrl->showBaseItem = BaseItem;
}

/**
 * @brief 重置菜单选项的起始位置
 * @note Location一定大于等于0
 * @param relativeLocation 相对位移，可正可负
 * @return int 负数表示未更改起始位置，其他值表示更改后的相对位置;-2表示超出最大选项位
 */
int Menu_SetItemBeginLocation(int relativeLocation)
{
    static int Location = 0;
    if ((relativeLocation + Location) >= 0) // 检查是否是安全地址
    {
        if (sg_tMenuManage.pMenuCtrl->itemsNum > (relativeLocation + Location))
        {
            sg_tMenuManage.pMenuCtrl->pMenuList = sg_tMenuManage.pMenuCtrl->pMenuList + relativeLocation;
            Location = Location + relativeLocation;
            return Location;
        }
        else
        {
            return -2;
        }
    }
    else
    {
        sg_tMenuManage.pMenuCtrl->pMenuList -= Location;
        Location = 0;
        return -1;
    }
}

/**
 * @brief      限制当前菜单界面最多显示的菜单数目
 *
 * @note       在菜单显示效果回调函数中使用, 使用成员变量 showBaseItem 得到显示界面的第一个选项索引
 * @param[in,out]  tMenuShow   当前菜单显示信息
 * @param[in,out]  showNum     当前菜单中需要显示的选项数目, 根据当前菜单选项的总数得到最终的显示的选项数目
 * @return     0,成功; -1,失败
 */
int Menu_LimitShowListNum(MenuShow_t *ptMenuShow, menusize_t *pShowNum)
{
    if (ptMenuShow == NULL || pShowNum == NULL)
    {
        return -1;
    }

    if (*pShowNum > ptMenuShow->itemsNum)
    {
        *pShowNum = ptMenuShow->itemsNum;
    }

    if (ptMenuShow->selectItem < ptMenuShow->showBaseItem) /*! 向上滚动菜单的效果 */
    {
        ptMenuShow->showBaseItem = ptMenuShow->selectItem;
    }
    else if ((ptMenuShow->selectItem - ptMenuShow->showBaseItem) >= *pShowNum) /*! 向下滚动菜单的效果 */
    {
        ptMenuShow->showBaseItem = ptMenuShow->selectItem - *pShowNum + 1;
    }
    else
    {
        // 保持
    }

    return 0;
}

/**
 * @brief       获取当前父菜单显示信息
 *              如获取当前菜单的二级父菜单信息，level 为2
 *
 * @param[out]  ptMenuShow 父 n 级菜单显示信息
 * @param[in]   level      n 级, 大于 0
 * @return int
 */
int Menu_QueryParentMenu(MenuShow_t *ptMenuShow, uint8_t level)
{
    int i;
    MenuList_t *pMenu;
    MenuCtrl_t *pMenuCtrl = NULL;

    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return -1;
    }

    pMenuCtrl = sg_tMenuManage.pMenuCtrl->pParentMenuCtrl;

    while (level && pMenuCtrl != NULL)
    {
        pMenu = pMenuCtrl->pMenuList;
        ptMenuShow->itemsNum = pMenuCtrl->itemsNum;
        ptMenuShow->selectItem = pMenuCtrl->selectItem;
        ptMenuShow->showBaseItem = pMenuCtrl->showBaseItem;

        if (sg_tMenuManage.isEnglish)
        {
            ptMenuShow->pszDesc = pMenuCtrl->pszEnDesc;

            for (i = 0; i < ptMenuShow->itemsNum && i < MENU_MAX_NUM; i++)
            {
                ptMenuShow->pszItemsDesc[i] = (char *)pMenu[i].pszEnDesc;
                ptMenuShow->pItemsExData[i] = pMenu[i].pExtendData;
            }
        }
        else
        {
            ptMenuShow->pszDesc = pMenuCtrl->pszDesc;

            for (i = 0; i < ptMenuShow->itemsNum && i < MENU_MAX_NUM; i++)
            {
                ptMenuShow->pszItemsDesc[i] = (char *)pMenu[i].pszDesc;
                ptMenuShow->pItemsExData[i] = pMenu[i].pExtendData;
            }
        }

        pMenuCtrl = pMenuCtrl->pParentMenuCtrl;
        level--;
    }

    if (level != 0 && pMenuCtrl == NULL)
    {
        return -1;
    }

    return 0;
}

/**
 * @brief  菜单任务
 *
 * @return 0,成功, 处于菜单模式下; -1,失败, 未处于菜单模式下
 */
int Menu_Task(void)
{
    int i;
    MenuList_t *pMenuList;
    MenuShow_t tMenuShow;

    if (sg_tMenuManage.pMenuCtrl == NULL)
    {
        return -1;
    }

    if (sg_tMenuManage.pMenuCtrl->pMenuList != NULL)
    {
        pMenuList = sg_tMenuManage.pMenuCtrl->pMenuList;
        tMenuShow.itemsNum = sg_tMenuManage.pMenuCtrl->itemsNum;
        tMenuShow.selectItem = sg_tMenuManage.pMenuCtrl->selectItem;
        tMenuShow.showBaseItem = sg_tMenuManage.pMenuCtrl->showBaseItem;

        if (sg_tMenuManage.isEnglish)
        {
            tMenuShow.pszDesc = sg_tMenuManage.pMenuCtrl->pszEnDesc;

            for (i = 0; i < tMenuShow.itemsNum && i < MENU_MAX_NUM; i++)
            {
                tMenuShow.pszItemsDesc[i] = (char *)pMenuList[i].pszEnDesc;
                tMenuShow.pItemsExData[i] = pMenuList[i].pExtendData;
            }
        }
        else
        {
            tMenuShow.pszDesc = sg_tMenuManage.pMenuCtrl->pszDesc;

            for (i = 0; i < tMenuShow.itemsNum && i < MENU_MAX_NUM; i++)
            {
                tMenuShow.pszItemsDesc[i] = (char *)pMenuList[i].pszDesc;
                tMenuShow.pItemsExData[i] = pMenuList[i].pExtendData;
            }
        }

        if (sg_tMenuManage.pMenuCtrl->pfnShowMenuFun != NULL)
        {
            sg_tMenuManage.pMenuCtrl->pfnShowMenuFun(&tMenuShow);
        }

        sg_tMenuManage.pMenuCtrl->showBaseItem = tMenuShow.showBaseItem;
    }

    if (sg_tMenuManage.pMenuCtrl->pfnRunCallFun != NULL)
    {
        sg_tMenuManage.pMenuCtrl->pfnRunCallFun();
    }

    return 0;
}
