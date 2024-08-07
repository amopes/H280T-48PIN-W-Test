
//���Ⱪ©����
#ifndef __220E_DIS_PUB_H__
#define __220E_DIS_PUB_H__

#include "stdint.h"
#include "tim.h"


//--------------------��������----------------------
//ģʽ�����ת���� ģʽ�����Ť��

//���
#define DRIVE_MODE1_MAX_RPM 1200
#define DRIVE_MODE1_MAX_TORQUE 1500

//�ڹ�
#define DRIVE_MODE2_MAX_RPM 4000
#define DRIVE_MODE2_MAX_TORQUE 1200

//����
#define DRIVE_MODE3_MAX_RPM 7500
#define DRIVE_MODE3_MAX_TORQUE 600


//--------------------�ͱ�����----------------------

//���ٺ�����ٶ�
#define PUMP_MIN_RPM 					600		//����ת��
#define PUMP_BUCKET_MAX_RPM 	1000	//�ֱ������ն����ת��
#define PUMP_SHANK_MAX_RPM 		1500	//�ֱ����ƴ�����ת��
#define PUMP_MAX_RPM 					2000	//���ֿ��Ƶ���·���ת��

//--------------------�ͱ�����----------------------
//�����ѹ ��Ȧ���� ������ ��С���� ����ʱ�� ����ʱ��

#define HYDRAULIC_MINIMUM_PWM 		280		//��С����

//--------------------Һѹ����----------------------
#define HYDRAULIC_ACCELERATION_INTERVENTION 		850		//Һѹ���ٽ���,���������Сֵ x-1000  0-1000
#define THIRD_ACCELERATED_INTERVENTION 					700		//����·Һѹ���ٽ���,���������Сֵ   0-400
#endif
