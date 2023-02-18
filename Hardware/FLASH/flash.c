#include "flash.h"

/*擦除指定页*/
static void FLASH_SIM_EraseEE(u32 pageAddress)
{
    FLASH_Unlock();
    FLASH_One_Page_Erase(pageAddress);
    FLASH_Lock();
}

FlashStore_t sg_FlashSelect;
#define BASED_USERDATA_ADDRESS 0x0800F800


void Flash_Read(void)
{
    uint32_t PeogramData;
	PeogramData = (*(__IO uint32_t*)(BASED_USERDATA_ADDRESS));
    sg_FlashSelect.MenuSelect = (uint8_t)(PeogramData&0xff);
    sg_FlashSelect.IsFsReset  = (uint8_t)((PeogramData&0xff00)>>8);
    sg_FlashSelect.ProtocolInformation.protocol_mode = (uint8_t)((PeogramData&0xff0000)>>16);
    sg_FlashSelect.ProtocolInformation.req_pdo_num   = (uint8_t)((PeogramData&0xff000000)>>24);

    PeogramData = (*(__IO uint32_t*)(BASED_USERDATA_ADDRESS+4));
    sg_FlashSelect.ProtocolInformation.ptl_start_volt = (uint16_t)(PeogramData&0xffff);
    sg_FlashSelect.ScrenDeirection  = (uint8_t)((PeogramData&0xff0000)>>16);
    
	PeogramData = (*(__IO uint32_t*)(BASED_USERDATA_ADDRESS+8));
    sg_FlashSelect.ProtocolInformation.ptl_end_volt = (uint16_t)(PeogramData&0xffff);
    sg_FlashSelect.ProtocolInformation.ptl_max_curr = (uint16_t)(PeogramData>>16);

    PeogramData = (*(__IO uint32_t*)(BASED_USERDATA_ADDRESS+12));
    sg_FlashSelect.ProtocolInformation.ptl_select_volt = (uint16_t)(PeogramData&0xffff);

}

void Flash_Write(void)
{
    //擦除一页数据	一页1k字节
	FLASH_SIM_EraseEE(BASED_USERDATA_ADDRESS);
	FLASH_Unlock();
    uint32_t WriteData;
    WriteData = sg_FlashSelect.MenuSelect |(sg_FlashSelect.IsFsReset<<8) | (sg_FlashSelect.ProtocolInformation.protocol_mode<<16) | (sg_FlashSelect.ProtocolInformation.req_pdo_num<<24);
    FLASH_Word_Program(BASED_USERDATA_ADDRESS,WriteData);
    
    WriteData = sg_FlashSelect.ProtocolInformation.ptl_start_volt | (sg_FlashSelect.ScrenDeirection<<16);
    FLASH_Word_Program(BASED_USERDATA_ADDRESS+4,WriteData);

    WriteData = sg_FlashSelect.ProtocolInformation.ptl_end_volt | (sg_FlashSelect.ProtocolInformation.ptl_max_curr<<16);
    FLASH_Word_Program(BASED_USERDATA_ADDRESS+8,WriteData);

    WriteData = sg_FlashSelect.ProtocolInformation.ptl_select_volt;
    FLASH_Word_Program(BASED_USERDATA_ADDRESS+12,WriteData);
    
	FLASH_Lock();
}
