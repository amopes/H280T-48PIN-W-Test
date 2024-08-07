#ifndef __LOGIC_PUB_H__
#define __LOGIC_PUB_H__


#include "stdint.h"







//声明函数

void Car_Iint(void);
void Analytic_CAN(void);


void Analytic_CAN_DATA_STD(void);
void Analytic_CAN_DATA_EXT(void);

void Main_Logical_Processing(void); //逻辑
void Basic_Data_Handling(void);
void Sys_Gamepad_Middleware(void); //手柄系统中间传递
void  Ctrl_Sys_L_Processing(void);
#endif
