
//���Ⱪ©����
#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "main.h"
#include "Sys_Cofig.h"

//��λ��
typedef struct 
{
	ULL Argument_Addr: 16;//��ǰ��������λ
	ULL Argument_Data: 32;//��ǰ��������
	ULL Argument_Config: 16;//��ǰ������������λ

} Upload_Flash_t; 


extern Upload_Flash_t Upload_Flash;		//��λ��
#endif

