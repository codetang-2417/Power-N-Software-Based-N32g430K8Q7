#ifndef __DECOY_H
#define __DECOY_H

#include "FS2711.h"

#include "flash.h"

void Init_FS2711(void);
void Decoy(uint16_t start_volt, uint16_t end_volt, uint16_t max_curr);
//void EnableNewProtocol(void);
void EnableNewProtocol(uint8_t Protocol);
void mcuRestart(void);
#endif // __DECOY_H
