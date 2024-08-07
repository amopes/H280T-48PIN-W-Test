//�߼���
#include "BSP_48Pin_Pub_L.h"
#include <stdlib.h>
#include "Logic_Pub_L.h"
#include "adc.h"
#include "can.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "Sem_Queues.h"			//������Ϣ
#include "BSP_48Pin_Pub_L.h"

#include "HGLS_Joy_Ped.h"
#include "220E_Dis_Pub_L.h"

/*CANЭ�����

��ʼ������
ADC��ȡ
PWM����

*/


uint16_t AD_Buf[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};//����ͨ���ɼ����ݴ��������������

Vehicle_Parameters_t Vehicle_Parameters;	//�������ƽṹ��
MOS_Ctrl_t MOS_Ctrl;	//MOS���ƽṹ��

/********************************************************
 * @brief    ��ʼ������
 *
 * @param    Car_Iint    	
 
 * @return   ��
 *
 * @note     ��ʼ������,PWM��ʼ��,ADC��ʼ��,CAN��ʼ��
 *
 * @see      SET_PWM_PMOS(0,999);  //����PWMͨ��0 P0_19
 *
 * @date     2023/9/5 ŵ־�� ���ڶ�
**********************************************************/
void Car_Iint()
{
	
		//��ʼת�ټ��
	HAL_TIM_IC_Start_IT(&htim13, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	/********************�޸ĵ�1***************************/

	//��ʼ��PWMͨ��,PWMȫ��ͨ������
	
	for(int i=0; i<OUT_CHANNEL_COUNT; i++)
	{
		//����ȫ����PWMռ�ձ�Ϊ0,������PWM
		__HAL_TIM_SetCompare(Out_List[i].phtim, Out_List[i].channel, 0);//����ռ�ձ�ȫ��Ϊ0
		HAL_TIM_PWM_Start(Out_List[i].phtim, Out_List[i].channel);
	}

}


/**
 * @brief  ��������ϵͳ����Ҫ�߼���������
 * 
 * �ú�����������߼����̣�����Һѹ���ơ�Կ��״̬�жϡ����ʹ�ܡ�״̬���ݴ�����ֱ����봦��
 * 
 * @author ŵ־��
 * @param  ��
 * @since  v1.0
 * @return NULL
 * @date   2023/09/09
 * @usage
 *      Main_Logical_Processing(); // ���ú����Ը��³����Ŀ���״̬
 * @notice
 *      ע��! �ú���Ӧ���ڵ�����ȷ����������ϵͳ���������С�
 */



//------------------------Һѹ����-----------------------
void Main_Logical_Processing()
{

//Կ���ж�
//���ݰ���
//�Ǳ�
//�ֱ�
//Һѹ
//Կ��״̬�ж�
//adcPhyResult.adcPhyField1.Throttle_angle

//�����ջ�
	
	
	
}
