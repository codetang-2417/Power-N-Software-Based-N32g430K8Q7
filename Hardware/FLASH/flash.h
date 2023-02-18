#ifndef _FLASH_H
#define _FLASH_H

#include "n32g430.h"

typedef struct
{
    uint8_t  protocol_mode;  /*! protocol */
    uint8_t  req_pdo_num;
    uint16_t ptl_start_volt;
    uint16_t ptl_end_volt;
    uint16_t ptl_max_curr;
    uint16_t ptl_select_volt;
}PtlSelect_t;

typedef struct
{
    uint8_t MenuSelect; //菜单快捷选项
    bool IsFsReset;     //是否是诱骗芯片切换协议，或者断开端口引起的重启
    bool ScrenDeirection; //
    PtlSelect_t ProtocolInformation;
}FlashStore_t;

extern FlashStore_t sg_FlashSelect;

void Flash_Read(void);
void Flash_Write(void);

#endif /* _FLASH_H */
