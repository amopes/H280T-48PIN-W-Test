#ifndef __SEM_QUEUES1_PUB_H__
#define __SEM_QUEUES1_PUB_H__
#include "FreeRTOS.h"
#include "queue.h"	//消息队列
#include "BSP_48Pin_Pub_L.h"

#include "HPMotor.h"  		//合普电机
#include "HGLS_Joy_Ped.h" //海格力斯手柄
#include "HGLS_7_appearance.h"

//CAN消息
//---------------------------------CAN处理-------------------
//CAN报文数据字段解析联合体
typedef union
{
	uint8_t asData[8];
	hglsJoy_t asHglsJoy; //手柄报文
	hglsJoy2_t asHglsJoy2;//手柄报文2
	
	//--------------合普------------------------------------
	motor_pump_state1_t as14188080;		//合普泵(电压温度方向)
	motor_pump_state2_t as14188180;		//合普泵(转速电压电流扭矩)
	
	motor_drive_state1_t as14188000;	//合普
	motor_drive_state2_t as14188100;	//合普
	
//	x14188480_t as14188480;		//合普
//	x14188400_t as14188400;		//合普
	
	//--------------7寸仪表------------------------------------
	
	hgls_rec_pack_t as_hgls_rec_pack;		//7寸仪表
	
} canFrameData_union;


//CAN报文
typedef struct
{
	uint32_t Id;
	uint32_t IDE;
	canFrameData_union Data;
} canReceiveMsg_t;




//队列结构体
extern QueueHandle_t qCanIsrToCAN1Rx;//从CAN接收中断到CAN1Rx线程
extern QueueHandle_t qAdcIsrToAdcTask;//把ADC-DMA中断里完成的ADC值传递给ADC线程处理、分发

//声明函数
void Establish_Queue_Create(void);//创建队列
void  Send_Message(void); //消息发送








extern Vehicle_Parameters_t Vehicle_Parameters;	//整车控制结构体

#endif
