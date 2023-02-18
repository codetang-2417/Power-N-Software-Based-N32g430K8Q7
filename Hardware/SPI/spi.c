#include "spi.h"

#define SPI_TFT             SPI1
#define GPIO_AF1_SPI_TFT    GPIO_AF1_SPI1


void SPI_GPIO_Init(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Configure master pins: NSS, SCK, MISO and MOSI */
    /* Confugure SPI pins as Alternate Function Push Pull */
    GPIO_Structure_Initialize(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = TFT_SCK | TFT_SDA;
    GPIO_InitStructure.GPIO_Mode  = GPIO_MODE_AF_PP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_SPI_TFT;
    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);
    
    //;
}

SPI_InitType SPI_InitStructure;
void SPI_TFT_Init(void)
{
	/* spi clock enable */
    RCC_APB2_Peripheral_Clock_Enable(RCC_APB2_PERIPH_SPI1);
	
    SPI_I2S_Reset(SPI_TFT);

    /* SPI_MASTER configuration */
    SPI_Initializes_Structure(&SPI_InitStructure);
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;//只发送，不接收
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;      //主机
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;  //8bit模式
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_HIGH;       //时钟空闲时的状态，高电平
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;//串行同步时钟空第二个时钟沿捕获
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;          //片选信号由软件控制
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_8;    //8MHz
    SPI_InitStructure.FirstBit      = SPI_FB_MSB;            //高位先行
    //SPI_InitStructure.CRCPoly       = 7;                     //CRC计算多项式
    SPI_Initializes(SPI_TFT, &SPI_InitStructure);         //初始化SPI_TFT
	SPI_Set_Nss_Level(SPI_TFT, SPI_NSS_HIGH);					//内部将NSS拉高，才能保持SPI的主机模式

  //SPI_CRC_Enable(SPI_TFT);  
	SPI_ON(SPI_TFT);
}

void SPI_Send_Data8(uint8_t data)
{
	  TFT_CS_Clr();
    /* Wait for SPI_MASTER Tx buffer empty */
    while (SPI_I2S_Flag_Status_Get(SPI_TFT, SPI_I2S_FLAG_TE) == RESET)
        ;
    SPI_I2S_Data_Transmit(SPI_TFT, data);
    while(SPI_I2S_Flag_Status_Get(SPI_TFT, SPI_I2S_FLAG_BUSY) != RESET)     // 等待SPI输完成
    ;
    TFT_CS_Set();
}

void SPI_Send_Data16(uint16_t data)
{
    SPI_Send_Data8(data>>8);
    SPI_Send_Data8(data);
}

