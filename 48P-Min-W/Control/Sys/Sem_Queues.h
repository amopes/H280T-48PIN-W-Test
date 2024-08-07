#ifndef __SEM_QUEUES1_PUB_H__
#define __SEM_QUEUES1_PUB_H__
#include "FreeRTOS.h"
#include "queue.h"	//��Ϣ����
#include "BSP_48Pin_Pub_L.h"

#include "HPMotor.h"  		//���յ��
#include "HGLS_Joy_Ped.h" //������˹�ֱ�
#include "HGLS_7_appearance.h"

//CAN��Ϣ
//---------------------------------CAN����-------------------
//CAN���������ֶν���������
typedef union
{
	uint8_t asData[8];
	hglsJoy_t asHglsJoy; //�ֱ�����
	hglsJoy2_t asHglsJoy2;//�ֱ�����2
	
	//--------------����------------------------------------
	motor_pump_state1_t as14188080;		//���ձ�(��ѹ�¶ȷ���)
	motor_pump_state2_t as14188180;		//���ձ�(ת�ٵ�ѹ����Ť��)
	
	motor_drive_state1_t as14188000;	//����
	motor_drive_state2_t as14188100;	//����
	
//	x14188480_t as14188480;		//����
//	x14188400_t as14188400;		//����
	
	//--------------7���Ǳ�------------------------------------
	
	hgls_rec_pack_t as_hgls_rec_pack;		//7���Ǳ�
	
} canFrameData_union;


//CAN����
typedef struct
{
	uint32_t Id;
	uint32_t IDE;
	canFrameData_union Data;
} canReceiveMsg_t;




//���нṹ��
extern QueueHandle_t qCanIsrToCAN1Rx;//��CAN�����жϵ�CAN1Rx�߳�
extern QueueHandle_t qAdcIsrToAdcTask;//��ADC-DMA�ж�����ɵ�ADCֵ���ݸ�ADC�̴߳����ַ�

//��������
void Establish_Queue_Create(void);//��������
void  Send_Message(void); //��Ϣ����








extern Vehicle_Parameters_t Vehicle_Parameters;	//�������ƽṹ��

#endif
