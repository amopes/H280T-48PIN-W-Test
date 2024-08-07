
//对外暴漏函数
#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "main.h"
#include "Sys_Cofig.h"

//上位机
typedef struct 
{
	ULL Argument_Addr: 16;//当前发送数据位
	ULL Argument_Data: 32;//当前发送数据
	ULL Argument_Config: 16;//当前发送数据配置位

} Upload_Flash_t; 


extern Upload_Flash_t Upload_Flash;		//上位机
#endif

