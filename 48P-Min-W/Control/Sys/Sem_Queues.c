//Free��Ϣ��
#include "Sem_Queues.h"	//������Ϣ
#include "FreeRTOS.h"
#include "queue.h"

#include "can.h"
#include "Sys_Cofig.h"
#include "BSP_48Pin_Pub_L.h"
#include "HPMotor.h"

#include "HGLS_7_appearance.h"

/*CANЭ�����

��ʼ������
ADC��ȡ
PWM����

*/

QueueHandle_t qCanIsrToCAN1Rx;//��CAN�����жϵ�CAN1Rx�߳�
QueueHandle_t qAdcIsrToAdcTask;//��ADC-DMA�ж�����ɵ�ADCֵ���ݸ�ADC�̴߳����ַ�


canReceiveMsg_t canReceiveMsg;
	

/*
1.������Ӧ������.c .h�ļ�
2.���·���дID�Ͷ�Ӧ�ṹ��(����λ��,,)
*/

/********************************************************
 * @brief    ����CAN��չ֡����
 *
 *
 * @return   ��
 *
 * @note   
 *
 * @see      Analytic_CAN_DATA_EXT();  //����PWMͨ��0 P0_19
 *
 * @date     2023/9/9 ŵ־�� ������
**********************************************************/
void Analytic_CAN_DATA_EXT()
{
	
 switch(canReceiveMsg.Id)
 {
	 
	//-------------------HGLS�ֱ���������-------------------	 
	 case 0x18fc0080:
	 	memcpy(&hglsJoy, &(canReceiveMsg.Data.asHglsJoy), sizeof(hglsJoy));
	  HGLS_JOY_1();
	 break;
	 
	 case 0x18fc0081:
		memcpy(&hglsJoy2, &(canReceiveMsg.Data.asHglsJoy2), sizeof(hglsJoy2));
	  HGLS_JOY_2();
	 break; 
	
	 //-------------------�Ǳ��Ĵ洢-------------------
	 case 0x18fe0044: memcpy(&hgls_rec_pack, &(canReceiveMsg.Data.as_hgls_rec_pack), sizeof(hgls_rec_pack)); break;  //TODO

 }
}
/********************************************************
 * @brief    ����CAN��׼֡����
 *
 *
 * @return   ��
 *
 * @note   
 *
 * @see      Analytic_CAN_DATA_STD();  //����PWMͨ��0 P0_19
 *
 * @date     2023/9/9 ŵ־�� ������
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
 * @brief    ��Ϣ����
 *
 * @param    Establish_Queue_Create  	
 
 * @return   ��
 *
 * @note     ������Ϣ����
 *
 * @see       Establish_Queue_Create();  //������Ϣ����
 *
 * @date     2023/9/7 ŵ־�� ������
**********************************************************/
unsigned int Interval_timing=0;
void  Send_Message()
{

	//----------------------�Ǳ�-------------------------------------------------------
		if(Interval_timing % 15 == 1)
	{
		
		Send_CAN_Message_MAIN(0x14180061,(uint8_t *)&VCU_Send_to_Screen_1_pack,1,8,1);  	//
		
	}

	if(Interval_timing % 15 == 5)
	{	
		
		Send_CAN_Message_MAIN(0x14180062,(uint8_t *)&VCU_Send_to_Screen_2_pack,1,8,1); 		//
		
	}

	//ʱ���ۼ�
	if(Interval_timing==5000)
	{
		Interval_timing=0;
	}
		
		Interval_timing++;
		
	
}

//�߼�����

/*******************CAN��������***************************/


/********************************************************
 * @brief    ����CAN����
 *
 *
 * @return   ��
 *
 * @note     ������չ֡�ͱ�׼֡
 *
 * @see       Analytic_CAN();
 *
 * @date     2023/9/9 ŵ־�� ������
**********************************************************/
void Analytic_CAN()
{
	

//		//��CAN1�����̷߳����յ������ݱ�
	if(pdTRUE == xQueueReceive(qCanIsrToCAN1Rx, &canReceiveMsg, portMAX_DELAY))
	{
		//����CAN����
		if(canReceiveMsg.IDE==CAN_ID_EXT)
		{
			//��չ֡
			Analytic_CAN_DATA_EXT();


		}else{
			//��׼֡
			Analytic_CAN_DATA_STD();

			
		}
	
	}
	
}
	
/********************************************************
 * @brief    ��Ϣ���д���
 *
 * @param    Establish_Queue_Create  	
 
 * @return   ��
 *
 * @note     ������Ϣ����
 *
 * @see       Establish_Queue_Create();  //������Ϣ����
 *
 * @date     2023/9/7 ŵ־�� ������
**********************************************************/
void Establish_Queue_Create()
{
	
	//CAN��Ϣ����
	qCanIsrToCAN1Rx = xQueueCreate(5, sizeof(canReceiveMsg_t));
	if(qCanIsrToCAN1Rx == NULL)
	{
		for(;;);
	}
	
	//ADC	���ݴ���
	qAdcIsrToAdcTask = xQueueCreate(1, sizeof(ADCValueDMA[0])*AIN_COUNT);//ԭ���ź����5��xQueueSendToBackFromISR���У�CAN�����ղ�����������
	if(qAdcIsrToAdcTask == NULL)
	{
		for(;;);
	}
	
	
}
