//逻辑层
#include "BSP_48Pin_Pub_L.h"
#include <stdlib.h>
#include "Logic_Pub_L.h"
#include "adc.h"
#include "can.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "Sem_Queues.h"			//队列消息
#include "BSP_48Pin_Pub_L.h"

#include "HGLS_Joy_Ped.h"
#include "220E_Dis_Pub_L.h"

/*CAN协议解析

初始化整车
ADC读取
PWM驱动

*/


uint16_t AD_Buf[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};//两个通道采集数据存在这个数组里面

Vehicle_Parameters_t Vehicle_Parameters;	//整车控制结构体
MOS_Ctrl_t MOS_Ctrl;	//MOS控制结构体

/********************************************************
 * @brief    初始化整车
 *
 * @param    Car_Iint    	
 
 * @return   无
 *
 * @note     初始化整车,PWM初始化,ADC初始化,CAN初始化
 *
 * @see      SET_PWM_PMOS(0,999);  //配置PWM通道0 P0_19
 *
 * @date     2023/9/5 诺志辉 星期二
**********************************************************/
void Car_Iint()
{
	
		//开始转速检测
	HAL_TIM_IC_Start_IT(&htim13, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	/********************修改点1***************************/

	//初始化PWM通道,PWM全部通道归零
	
	for(int i=0; i<OUT_CHANNEL_COUNT; i++)
	{
		//配置全部的PWM占空比为0,并启动PWM
		__HAL_TIM_SetCompare(Out_List[i].phtim, Out_List[i].channel, 0);//其余占空比全部为0
		HAL_TIM_PWM_Start(Out_List[i].phtim, Out_List[i].channel);
	}

}


/**
 * @brief  车辆控制系统的主要逻辑处理函数。
 * 
 * 该函数处理各种逻辑过程，包括液压控制、钥匙状态判断、电机使能、状态数据处理和手柄输入处理。
 * 
 * @author 诺志辉
 * @param  无
 * @since  v1.0
 * @return NULL
 * @date   2023/09/09
 * @usage
 *      Main_Logical_Processing(); // 调用函数以更新车辆的控制状态
 * @notice
 *      注意! 该函数应定期调用以确保车辆控制系统的正常运行。
 */



//------------------------液压变量-----------------------
void Main_Logical_Processing()
{

//钥匙判断
//数据搬运
//仪表
//手柄
//液压
//钥匙状态判断
//adcPhyResult.adcPhyField1.Throttle_angle

//电流闭环
	
	
	
}
