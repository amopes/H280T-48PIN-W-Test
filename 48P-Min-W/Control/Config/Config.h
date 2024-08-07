
//对外暴漏函数
#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "main.h"


#define Table_Password 0                               /* 0密码*/
#define Table_SoftwareVersion 1                       /* 1软件版本*/


//开发者模式
#define DEVELOPER_MODEL 0			//1为开启 0为关闭

//串口调参 
#define SERIAL_TUNING 	1			//1为开启 0为关闭


//不启用开发版本请修改版本号
#define SOFTWARE_REV 2024072923		//量产发送日期

//配置模式
#define MODEL_SELECTION 1 			//0是油车 1是电车


// FLASH起始地址
#define FLASH_START_ADDR 	0x080E0000
#define MEAU_NUM    		80   		// 数据条目数量


void Flash_Test(void);
void Car_Soft_Parameter_config(void);	//整车系统参数配置

#endif

