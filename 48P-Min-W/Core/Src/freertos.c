/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adc.h"
#include "usart.h"
#include "stdio.h"
#include "BSP_48Pin_Pub_L.h"		//驱动层
#include "Electric_L_Pub.h"
#include "DEBUG_Pub.h"
#include "Sem_Queues.h"	//队列消息
#include "Logic_Pub_L.h"
#include "Math.h" //算法
#include "220E_Dis_Pub_L.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern uint16_t AD_Buf[13];//两个通道采集数据存在这个数组里面
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Logical_Task_L */
osThreadId_t Logical_Task_LHandle;
const osThreadAttr_t Logical_Task_L_attributes = {
  .name = "Logical_Task_L",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal5,
};
/* Definitions for Parsing_service */
osThreadId_t Parsing_serviceHandle;
const osThreadAttr_t Parsing_service_attributes = {
  .name = "Parsing_service",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal6,
};
/* Definitions for Send_Message */
osThreadId_t Send_MessageHandle;
const osThreadAttr_t Send_Message_attributes = {
  .name = "Send_Message",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal6,
};
/* Definitions for Logical_Task_H */
osThreadId_t Logical_Task_HHandle;
const osThreadAttr_t Logical_Task_H_attributes = {
  .name = "Logical_Task_H",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal7,
};
/* Definitions for Start_Adc */
osThreadId_t Start_AdcHandle;
const osThreadAttr_t Start_Adc_attributes = {
  .name = "Start_Adc",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime6,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Logical_Processing_Low_Task(void *argument);
void Parsing_service_Task(void *argument);
void Send_Message_StartTask(void *argument);
void Logical_Processing_High_Task(void *argument);
void Start_Adc_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
 
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
	Establish_Queue_Create();
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Logical_Task_L */
  Logical_Task_LHandle = osThreadNew(Logical_Processing_Low_Task, NULL, &Logical_Task_L_attributes);

  /* creation of Parsing_service */
  Parsing_serviceHandle = osThreadNew(Parsing_service_Task, NULL, &Parsing_service_attributes);

  /* creation of Send_Message */
  Send_MessageHandle = osThreadNew(Send_Message_StartTask, NULL, &Send_Message_attributes);

  /* creation of Logical_Task_H */
  Logical_Task_HHandle = osThreadNew(Logical_Processing_High_Task, NULL, &Logical_Task_H_attributes);

  /* creation of Start_Adc */
  Start_AdcHandle = osThreadNew(Start_Adc_Task, NULL, &Start_Adc_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	DEBUG_Item();
    vTaskDelayUntil( &xLastWakeTime, 10);//绝对延时
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Logical_Processing_Low_Task */
/**
* @brief Function implementing the Logical_Task_L thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Logical_Processing_Low_Task */
void Logical_Processing_Low_Task(void *argument)
{
  /* USER CODE BEGIN Logical_Processing_Low_Task */
  /* Infinite loop */
  for(;;)
  {
	//500ms 一次
	//printf("samples:%d\n",Pulse_Speed.SPD1_Speed);
  HAL_GPIO_TogglePin(LED2_PE10_GPIO_Port, LED2_PE10_Pin);	//运行指示灯
	Off_Power();
	
  osDelay(100);
  }
  /* USER CODE END Logical_Processing_Low_Task */
}

/* USER CODE BEGIN Header_Parsing_service_Task */
/**
* @brief Function implementing the Parsing_service thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Parsing_service_Task */
void Parsing_service_Task(void *argument)
{
  /* USER CODE BEGIN Parsing_service_Task */
  /* Infinite loop */
  for(;;)
  {
//	HAL_GPIO_TogglePin(LED2_PE10_GPIO_Port, LED2_PE10_Pin);	//运行指示灯
	//CAN消息处理
	Analytic_CAN();
    osDelay(5);
  }
  /* USER CODE END Parsing_service_Task */
}

/* USER CODE BEGIN Header_Send_Message_StartTask */
/**
* @brief Function implementing the Send_Message thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Send_Message_StartTask */
void Send_Message_StartTask(void *argument)
{
  /* USER CODE BEGIN Send_Message_StartTask */
  /* Infinite loop */
  for(;;)
  {
			//CAN消息发送
	Send_Message();
    osDelay(10);
  }
  /* USER CODE END Send_Message_StartTask */
}

/* USER CODE BEGIN Header_Logical_Processing_High_Task */
/**
* @brief Function implementing the Logical_Task_H thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Logical_Processing_High_Task */
void Logical_Processing_High_Task(void *argument)
{
  /* USER CODE BEGIN Logical_Processing_High_Task */
  /* Infinite loop */
  for(;;)
  {
		
 	MOS_Unified_OUT();
	Main_Logical_Processing();

	
    osDelay(5);
  }
  /* USER CODE END Logical_Processing_High_Task */
}

/* USER CODE BEGIN Header_Start_Adc_Task */
/**
* @brief Function implementing the Start_Adc thread.
* @param argument: Not used
* @retval None
*/
#define ADC_FILTER_BUFF_SIZE			(12)
/* USER CODE END Header_Start_Adc_Task */
void Start_Adc_Task(void *argument)
{
  /* USER CODE BEGIN Start_Adc_Task */
	static uint32_t ADCValueADC[ADC_FILTER_BUFF_SIZE][AIN_COUNT];
	uint32_t ADCValueTmp[ADC_FILTER_BUFF_SIZE];
	uint32_t ADCValueAvg[AIN_COUNT];
	uint8_t i, j, buffLine = 0;
	
  /* Infinite loop */
  for(;;)
  {
    	if(pdTRUE == xQueueReceive(qAdcIsrToAdcTask, &ADCValueADC[buffLine], portMAX_DELAY))//一直等
		{ 
		//	printf("samples:%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d \n",ADCValueDMA[0],ADCValueDMA[1],ADCValueDMA[2],ADCValueDMA[3],ADCValueDMA[4],ADCValueDMA[5],ADCValueDMA[6],ADCValueDMA[7],ADCValueDMA[8],ADCValueDMA[9],ADCValueDMA[10],ADCValueDMA[11],ADCValueDMA[12]);
	
			if(buffLine == ADC_FILTER_BUFF_SIZE-1)
			{
				for(i=0; i<AIN_COUNT; i++)//逐个传感器做平均值滤波
				{
					for(j=0; j<ADC_FILTER_BUFF_SIZE; j++)
					{
						ADCValueTmp[j] = ADCValueADC[j][i];//把此传感器历次AD值转移到tmp数组, 之后排序、平均

					}
					bubble_sort(ADCValueTmp, ADC_FILTER_BUFF_SIZE);//排序
					ADCValueAvg[i] = ( ADCValueTmp[3] + ADCValueTmp[4] + ADCValueTmp[5] + ADCValueTmp[6] + ADCValueTmp[7]+ADCValueTmp[8] ) / 6;//中间6值求平均
					//0 1 2    9 10 11
				}
				calcPhyValue(0*100, ADCValueDMA, (int16_t *)&adcPhyResult);
				buffLine = 0;//重新开始一轮滤波
			}
			else buffLine++;
		}
		
		osDelay(1);
  }
  /* USER CODE END Start_Adc_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

