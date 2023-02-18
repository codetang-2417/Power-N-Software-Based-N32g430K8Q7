#ifndef __SPI_H
#define __SPI_H

#include "n32g430.h"


#define TFT_SCK GPIO_PIN_5
#define TFT_SDA GPIO_PIN_7
#define TFT_RES GPIO_PIN_9
#define TFT_DC  GPIO_PIN_8
#define TFT_CS  GPIO_PIN_6
#define TFT_BLK GPIO_PIN_10

#define TFT_CS_Clr()   GPIO_Pins_Reset(GPIOA,TFT_CS)//CS
#define TFT_CS_Set()   GPIO_Pins_Set(GPIOA,TFT_CS)

void SPI_TFT_Init(void);
void SPI_GPIO_Init(void);
void SPI_Send_Data8(uint8_t data);
void SPI_Send_Data16(uint16_t data);

#endif /* __SPI_H */
