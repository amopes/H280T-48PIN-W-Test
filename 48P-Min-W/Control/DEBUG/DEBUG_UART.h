#ifndef __DEBUG_UART_H__
#define __DEBUG_UART_H__

#include "stdio.h"
#include "usart.h"
#include "freertos.h"
#include "common_fifo.h"
/* 变量类型枚举，不可修改！ */
typedef enum
{
	D_uint8 = 1,
	D_uint16 = 2,
	D_uint32 = 3,
	D_int8 = 4,
	D_int16 = 5,
	D_int32 = 6,
	D_float = 7,
}D_X_enum;


/* CMD命令结构体，不可修改！ */
typedef const struct CMD_str	//共32字节
{
	char CMD[24];					//识别库
	uint8	(*Program)(void);	//函数执行
}CMD_str;

/* CMD数据结构体，不可修改！ */
typedef const struct CMD_Data_str
{
	char CMD[24];					//识别库
	void *data_p;	//数据指针
	D_X_enum D_X; //数据类型枚举
	uint8	(*Program)(const char *Str1, uint8 ChangeX, uint16 CMDnum);	//函数执行，原数据，输入数据，数据类型
}CMD_Data_str;





//全局变量声明区


extern float desired_current;
extern float Kp_A ;
extern float Ki_A ;
extern float Kd_A ;


void DEBUG_UART_Init(void);
uint8 Cmd_DataManage(const char *Str1, uint8 ChangeX, uint16 CMDnum);
uint8 Cmd_Size(void);
uint8 Cmd_help(void);
uint8 Cmd_Time(void);
uint8 Cmd_cpuid(void);
uint8 Cmd_reset(void);
uint8 Cmd_save(void);
uint8 Cmd_Fifo(void);
uint8 Cmd_test(void);
uint8 IfSeachCmd(void);
uint8 IfSeachCmdData(const char *Str1, uint8 ChangeX, uint16 CMDnum);


void DEBUG_Item(void);
void pwm_control_loop(unsigned int target_current);
#endif /*__DEBUG_UART_H__*/

