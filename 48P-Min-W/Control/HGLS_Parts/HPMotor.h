#ifndef __HPMOTOR_H__
#define __HPMOTOR_H__

#include "stm32f4xx_hal.h"
#include "string.h"
#include "Sys_Cofig.h"


/*****************�����Ǻ��յ�������ı���**********************/
//���յ����������0x14188080
typedef struct 
{
	ULL Vbus: 16;//ĸ�ߵ�ѹ, ��λ0.1
	ULL motorTemp: 8;//����¶� ��λ1  ƫ����-50
	ULL mcuTemp: 8;//�������¶� ��λ1  ƫ����-50
	ULL motorDir: 1;//������� 0�� 1��
	ULL unUsed: 31;
} motor_pump_state1_t;

//���յ����������0x14188000
typedef struct 
{
	ULL Vbus: 16;//ĸ�ߵ�ѹ, ��λ0.1
	ULL motorTemp: 8;//����¶� ��λ1  ƫ����-50
	ULL mcuTemp: 8;//�������¶� ��λ1  ƫ����-50
	ULL motorDir: 1;//������� 0�� 1��
	ULL unUsed: 31;
} motor_drive_state1_t;

//���յ����������0x14188180
typedef struct 
{
	ULL rpm: 16;//ת��rpm
	ULL Vphase: 16;//���ѹ ��λ0.1V
	ULL Iphase: 16;//����� ��λ0.1A
	ULL torque: 16;//Ť�� ��λ0.1nM -500
} motor_pump_state2_t;

//���յ����������0x14188100
typedef struct 
{
	ULL rpm: 16;//ת��rpm
	ULL Vphase: 16;//���ѹ ��λ0.1V
	ULL Iphase: 16;//����� ��λ0.1A
	ULL torque: 16;//Ť�� ��λ0.1nM -500
} motor_drive_state2_t;

//���յ����������0x14188480
typedef struct 
{
	ULL seconds: 32;//Сʱ�� s
	ULL unUsed: 32;
} x14188480_t;

//���յ����������0x14188400
typedef struct 
{
	ULL seconds: 32;//Сʱ�� s
	ULL unUsed: 32;
} x14188400_t;

/*****************�����Ǻ��յ�����յı���**********************/
//Сʱ�ƹ��� 0x1418fe80
typedef struct 
{
	ULL zero1: 32;//0x55AA55AA
	ULL zero2: 32;//0x55AA55AA
} x1418fe80_t;

//Сʱ�ƹ��� 0x1418fe00
typedef struct 
{
	ULL zero1: 32;//0x55AA55AA
	ULL zero2: 32;//0x55AA55AA
} x1418fe00_t;

//ģʽ���� 0x14180080
typedef struct 
{
	ULL onDir: 2;//0=ͣת  1=��ת  2=��ת
	ULL mode: 2;//0=�ٶȻ�  1=ת�ػ�  2/3=����
	ULL clrErrs: 1;//0=���������  1=�������
	ULL unUsed: 11;
	ULL targetRpm: 16;//0-65535 * 1rpm
	ULL targetNm: 16;//0-65535 * 0.1 - 500 Nm
	ULL maxRpm: 16;//0-65535 * 1rpm
} motor_pump_ctrl_t; 


//��Э��
//ģʽ���� 0x14180000
typedef struct 
{
	ULL onDir: 2;//0=ͣת  1=��ת  2=��ת
	ULL mode: 2;//0=�ٶȻ�  1=ת�ػ�  2/3=����
	ULL clrErrs: 1;//0=���������  1=�������
	ULL unUsed: 11;
	ULL targetRpm: 16;//0-65535 * 1rpm
	ULL targetNm: 16;//0-65535 * 0.1 - 500 Nm
	ULL maxRpm: 16;//0-65535 * 1rpm	
	
} motor_drive_ctrl_t;




////��Э��
////ģʽ���� 0x14180000
//typedef struct 
//{
//	ULL onDir: 2;					//0=ͣת  1=��ת  2=��ת
//	ULL mode: 2;					//0=�ٶȻ�  1=ת�ػ�  2/3=����
//	ULL clrErrs: 1;				//0=���������  1=�������
//	ULL brake: 1;					//0=��ɲ��  1=ɲ��
//	ULL unUsed: 2;
//	ULL targetRpm: 16;		//ת������0-65535 * 1rpm
//	ULL targetNm: 16;			//��������0-65535 * 0.1 - 500 Nm
//	ULL maxNm: 8;					//ת�ٿ����µ���������0-65535 * 1rpm
//	ULL maxRpm: 16;				//���ؿ�����ת������0-65535 * 1rpm			
//} motor_drive_ctrl_t;




//��������
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
