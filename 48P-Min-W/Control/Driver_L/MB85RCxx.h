#ifndef __MB85RCXX_H__
#define __MB85RCXX_H__

#include "stm32f4xx_hal.h"
#include "i2c.h"

#define MB85RCXX_LEN			(2048)

void GO_EEP(void);
HAL_StatusTypeDef writeMB85RCxx(uint16_t startByte, uint8_t* willWriteBuf, uint16_t bufSize);
HAL_StatusTypeDef readMB85RCxx(uint16_t startByte, uint8_t* buf, uint16_t bufSize);


#endif
