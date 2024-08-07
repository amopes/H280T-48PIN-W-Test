#ifndef __HPMOTOR_H__
#define __HPMOTOR_H__

#include "stm32f4xx_hal.h"
#include "string.h"
#include "Sys_Cofig.h"


/*****************以下是合普电机发出的报文**********************/
//合普电机发出报文0x14188080
typedef struct 
{
	ULL Vbus: 16;//母线电压, 单位0.1
	ULL motorTemp: 8;//电机温度 单位1  偏移量-50
	ULL mcuTemp: 8;//控制器温度 单位1  偏移量-50
	ULL motorDir: 1;//电机方向 0正 1反
	ULL unUsed: 31;
} motor_pump_state1_t;

//合普电机发出报文0x14188000
typedef struct 
{
	ULL Vbus: 16;//母线电压, 单位0.1
	ULL motorTemp: 8;//电机温度 单位1  偏移量-50
	ULL mcuTemp: 8;//控制器温度 单位1  偏移量-50
	ULL motorDir: 1;//电机方向 0正 1反
	ULL unUsed: 31;
} motor_drive_state1_t;

//合普电机发出报文0x14188180
typedef struct 
{
	ULL rpm: 16;//转速rpm
	ULL Vphase: 16;//相电压 单位0.1V
	ULL Iphase: 16;//相电流 单位0.1A
	ULL torque: 16;//扭矩 单位0.1nM -500
} motor_pump_state2_t;

//合普电机发出报文0x14188100
typedef struct 
{
	ULL rpm: 16;//转速rpm
	ULL Vphase: 16;//相电压 单位0.1V
	ULL Iphase: 16;//相电流 单位0.1A
	ULL torque: 16;//扭矩 单位0.1nM -500
} motor_drive_state2_t;

//合普电机发出报文0x14188480
typedef struct 
{
	ULL seconds: 32;//小时计 s
	ULL unUsed: 32;
} x14188480_t;

//合普电机发出报文0x14188400
typedef struct 
{
	ULL seconds: 32;//小时计 s
	ULL unUsed: 32;
} x14188400_t;

/*****************以下是合普电机接收的报文**********************/
//小时计归零 0x1418fe80
typedef struct 
{
	ULL zero1: 32;//0x55AA55AA
	ULL zero2: 32;//0x55AA55AA
} x1418fe80_t;

//小时计归零 0x1418fe00
typedef struct 
{
	ULL zero1: 32;//0x55AA55AA
	ULL zero2: 32;//0x55AA55AA
} x1418fe00_t;

//模式控制 0x14180080
typedef struct 
{
	ULL onDir: 2;//0=停转  1=正转  2=反转
	ULL mode: 2;//0=速度环  1=转矩环  2/3=保留
	ULL clrErrs: 1;//0=不清除故障  1=清除故障
	ULL unUsed: 11;
	ULL targetRpm: 16;//0-65535 * 1rpm
	ULL targetNm: 16;//0-65535 * 0.1 - 500 Nm
	ULL maxRpm: 16;//0-65535 * 1rpm
} motor_pump_ctrl_t; 


//老协议
//模式控制 0x14180000
typedef struct 
{
	ULL onDir: 2;//0=停转  1=正转  2=反转
	ULL mode: 2;//0=速度环  1=转矩环  2/3=保留
	ULL clrErrs: 1;//0=不清除故障  1=清除故障
	ULL unUsed: 11;
	ULL targetRpm: 16;//0-65535 * 1rpm
	ULL targetNm: 16;//0-65535 * 0.1 - 500 Nm
	ULL maxRpm: 16;//0-65535 * 1rpm	
	
} motor_drive_ctrl_t;




////新协议
////模式控制 0x14180000
//typedef struct 
//{
//	ULL onDir: 2;					//0=停转  1=正转  2=反转
//	ULL mode: 2;					//0=速度环  1=转矩环  2/3=保留
//	ULL clrErrs: 1;				//0=不清除故障  1=清除故障
//	ULL brake: 1;					//0=不刹车  1=刹车
//	ULL unUsed: 2;
//	ULL targetRpm: 16;		//转速命令0-65535 * 1rpm
//	ULL targetNm: 16;			//力矩命令0-65535 * 0.1 - 500 Nm
//	ULL maxNm: 8;					//转速控制下的力矩限制0-65535 * 1rpm
//	ULL maxRpm: 16;				//力矩控制下转速限制0-65535 * 1rpm			
//} motor_drive_ctrl_t;




//电流反馈
typedef struct 
{
	ULL Motor_Reverse_Current: 16; //0-65535A
	ULL unUsed: 48;
} motor_drive2_ctrl_t;

extern motor_pump_state1_t		motor_pump_state1;
extern motor_drive_state1_t		motor_drive_state1;
extern motor_pump_state2_t		motor_pump_state2;
extern motor_drive_state2_t		motor_drive_state2;
extern x14188480_t x14188480;
extern x14188400_t x14188400;

extern motor_pump_ctrl_t		motor_pump_ctrl;
extern motor_drive_ctrl_t		motor_drive_ctrl;
extern motor_drive2_ctrl_t		motor_drive2_ctrl;

#endif
