
//���Ⱪ©����
#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "main.h"


#define Table_Password 0                               /* 0����*/
#define Table_SoftwareVersion 1                       /* 1����汾*/


//������ģʽ
#define DEVELOPER_MODEL 0			//1Ϊ���� 0Ϊ�ر�

//���ڵ��� 
#define SERIAL_TUNING 	1			//1Ϊ���� 0Ϊ�ر�


//�����ÿ����汾���޸İ汾��
#define SOFTWARE_REV 2024072923		//������������

//����ģʽ
#define MODEL_SELECTION 1 			//0���ͳ� 1�ǵ糵


// FLASH��ʼ��ַ
#define FLASH_START_ADDR 	0x080E0000
#define MEAU_NUM    		80   		// ������Ŀ����


void Flash_Test(void);
void Car_Soft_Parameter_config(void);	//����ϵͳ��������

#endif

