//Free消息区
#include "Sem_Queues.h"	//队列消息
#include "FreeRTOS.h"
#include "queue.h"

#include "can.h"
#include "Sys_Cofig.h"
#include "BSP_48Pin_Pub_L.h"
#include "HPMotor.h"

#include "HGLS_7_appearance.h"

/*CAN协议解析

初始化整车
ADC读取
PWM驱动

*/

QueueHandle_t qCanIsrToCAN1Rx;//从CAN接收中断到CAN1Rx线程
QueueHandle_t qAdcIsrToAdcTask;//把ADC-DMA中断里完成的ADC值传递给ADC线程处理、分发


canReceiveMsg_t canReceiveMsg;
	

/*
1.创建对应部件的.c .h文件
2.在下方填写ID和对应结构体(缓存位段,,)
*/

/********************************************************
 * @brief    解析CAN扩展帧数据
 *
 *
 * @return   无
 *
 * @note   
 *
 * @see      Analytic_CAN_DATA_EXT();  //配置PWM通道0 P0_19
 *
 * @date     2023/9/9 诺志辉 星期六
**********************************************************/
void Analytic_CAN_DATA_EXT()
{
	
 switch(canReceiveMsg.Id)
 {
	 
	//-------------------HGLS手柄报文两个-------------------	 
	 case 0x18fc0080:
	 	memcpy(&hglsJoy, &(canReceiveMsg.Data.asHglsJoy), sizeof(hglsJoy));
	  HGLS_JOY_1();
	 break;
	 
	 case 0x18fc0081:
		memcpy(&hglsJoy2, &(canReceiveMsg.Data.asHglsJoy2), sizeof(hglsJoy2));
	  HGLS_JOY_2();
	 break; 
	
	 //-------------------仪表报文存储-------------------
	 case 0x18fe0044: memcpy(&hgls_rec_pack, &(canReceiveMsg.Data.as_hgls_rec_pack), sizeof(hgls_rec_pack)); break;  //TODO

 }
}
/********************************************************
 * @brief    解析CAN标准帧数据
 *
 *
 * @return   无
 *
 * @note   
 *
 * @see      Analytic_CAN_DATA_STD();  //配置PWM通道0 P0_19
 *
 * @date     2023/9/9 诺志辉 星期六
**********************************************************/
void Analytic_CAN_DATA_STD()
{
 switch(canReceiveMsg.Id)
 {
	 case 0x1:
		 			HAL_GPIO_TogglePin(LED0_PE7_GPIO_Port, LED0_PE7_Pin);
	 break;
	 
	 case 0x2:
		 			HAL_GPIO_TogglePin(LED0_PE7_GPIO_Port, LED0_PE7_Pin);
	 break; 
	 
	 
	 
 }

	
}

/********************************************************
 * @brief    消息发送
 *
 * @param    Establish_Queue_Create  	
 
 * @return   无
 *
 * @note     创建消息队列
 *
 * @see       Establish_Queue_Create();  //创建消息队列
 *
 * @date     2023/9/7 诺志辉 星期四
**********************************************************/
unsigned int Interval_timing=0;
void  Send_Message()
{

	//----------------------仪表-------------------------------------------------------
		if(Interval_timing % 15 == 1)
	{
		
		Send_CAN_Message_MAIN(0x14180061,(uint8_t *)&VCU_Send_to_Screen_1_pack,1,8,1);  	//
		
	}

	if(Interval_timing % 15 == 5)
	{	
		
		Send_CAN_Message_MAIN(0x14180062,(uint8_t *)&VCU_Send_to_Screen_2_pack,1,8,1); 		//
		
	}

	//时间累计
	if(Interval_timing==5000)
	{
		Interval_timing=0;
	}
		
		Interval_timing++;
		
	
}

//逻辑控制

/*******************CAN解析区域***************************/


/********************************************************
 * @brief    解析CAN类型
 *
 *
 * @return   无
 *
 * @note     区分扩展帧和标准帧
 *
 * @see       Analytic_CAN();
 *
 * @date     2023/9/9 诺志辉 星期六
**********************************************************/
void Analytic_CAN()
{
	

//		//当CAN1接收线程发来收到的数据报
	if(pdTRUE == xQueueReceive(qCanIsrToCAN1Rx, &canReceiveMsg, portMAX_DELAY))
	{
		//解析CAN类型
		if(canReceiveMsg.IDE==CAN_ID_EXT)
		{
			//扩展帧
			Analytic_CAN_DATA_EXT();


		}else{
			//标准帧
			Analytic_CAN_DATA_STD();

			
		}
	
	}
	
}
	
/********************************************************
 * @brief    消息队列创建
 *
 * @param    Establish_Queue_Create  	
 
 * @return   无
 *
 * @note     创建消息队列
 *
 * @see       Establish_Queue_Create();  //创建消息队列
 *
 * @date     2023/9/7 诺志辉 星期四
**********************************************************/
void Establish_Queue_Create()
{
	
	//CAN消息队列
	qCanIsrToCAN1Rx = xQueueCreate(5, sizeof(canReceiveMsg_t));
	if(qCanIsrToCAN1Rx == NULL)
	{
		for(;;);
	}
	
	//ADC	数据处理
	qAdcIsrToAdcTask = xQueueCreate(1, sizeof(ADCValueDMA[0])*AIN_COUNT);//原用信号深度5，xQueueSendToBackFromISR不行，CAN任务收不到最新数据
	if(qAdcIsrToAdcTask == NULL)
	{
		for(;;);
	}
	
	
}
