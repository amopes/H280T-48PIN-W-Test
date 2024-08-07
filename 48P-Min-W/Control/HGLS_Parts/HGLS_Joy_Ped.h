#ifndef __HGLSJOY_H__
#define __HGLSJOY_H__

#include "stm32f4xx_hal.h"
#include "string.h"
#include "Sys_Cofig.h"

//HGLS手柄发出报文0x18fc0080
typedef struct 
{
	ULL button1: 1;//180: 喇叭     460-button1: 喇叭
	ULL button2: 1;//180: 3RD锁定  460-button2: 大臂安全阀
	ULL button3: 1;//180: 液压锁   460-button3: 料斗切换挡板
	ULL button4: 1;//180: 空挡
	ULL button5: 1;//180: 高低速
	ULL button6: 1;//180: 定速
	ULL unUsed: 2;
	ULL updown1H: 8;//180: 前进后退
	ULL updown1L: 8;//180: 前进后退
	ULL updown2H: 8;//180:
	ULL updown2L: 8;//180:
	ULL updown3H: 8;//180:
	ULL updown3L: 8;//180:
	ULL unUsed2: 8;
} hglsJoy_t;

//HGLS手柄发出报文0x18fc0081
typedef struct 
{
	ULL XaxisH: 8;//
	ULL XaxisL: 8;//
	ULL YaxisH: 8;//
	ULL YaxisL: 8;//
	ULL unUsed: 32;
} hglsJoy2_t;

//用于记录手柄底座和右拨轮的实际值，以实现控制
typedef struct
{
	int16_t Xaxis;
	int16_t Yaxis;
	int16_t Zaxis;
	int16_t updown1;
	int16_t updown2;
	int16_t updown3;
} hglsJoyXYZ_t;


extern hglsJoy_t hglsJoy;
extern hglsJoy2_t hglsJoy2;
extern hglsJoyXYZ_t hglsJoyXYZ;

void HGLS_JOY_1(void);
void HGLS_JOY_2(void);
#endif
