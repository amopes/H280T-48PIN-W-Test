#include "Electric_L_Pub.h"
#include "BSP_48Pin_Pub_L.h"
#include "220E_Dis_Pub_L.h"
extern  MOS_Ctrl_t MOS_Ctrl;	//整车控制结构体
//电气驱动层(滤波ADC处理)





#define OUT_INDEX_12V_SSR_NUM							(11)	//12V继电器

//-------------------整车电源控制--------------------------

//整车电源开
void Open_Power()
{
	
		//板载PWM输出全部开启
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


//整车电源关
void Off_Power()
{
	
	//钥匙挡位为0
	if(!HAL_GPIO_ReadPin(DI5_PD4_GPIO_Port,DI5_PD4_Pin))
	{
			
		
	}

}

