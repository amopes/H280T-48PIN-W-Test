#include "Electric_L_Pub.h"
#include "BSP_48Pin_Pub_L.h"
#include "220E_Dis_Pub_L.h"
extern  MOS_Ctrl_t MOS_Ctrl;	//�������ƽṹ��
//����������(�˲�ADC����)





#define OUT_INDEX_12V_SSR_NUM							(11)	//12V�̵���

//-------------------������Դ����--------------------------

//������Դ��
void Open_Power()
{
	
		//����PWM���ȫ������
	for (int i = 11; i <= OUT_CHANNEL_COUNT; i++)
	{
		switch(i)
		{
//			case OUT_INDEX_12V_SSR_NUM:			
//				HAL_Delay(50);
//				__HAL_TIM_SetCompare(Out_List[i].phtim, Out_List[i].channel, 999);//12V
//			break;	
		}
	}

	
	

	
}


//������Դ��
void Off_Power()
{
	
	//Կ�׵�λΪ0
	if(!HAL_GPIO_ReadPin(DI5_PD4_GPIO_Port,DI5_PD4_Pin))
	{
			
		
	}

}

