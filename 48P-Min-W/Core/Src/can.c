/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */
#include "FreeRTOS.h"
#include "queue.h"
#include "adc.h"
#include "Sem_Queues.h"			//������Ϣ
#include "Logic_Pub_L.h" //CAN����ṹ
#include "BSP_48Pin_Pub_L.h"
#include "220E_Dis_Pub_L.h"
//�������ݽṹ��
CAN_RxHeaderTypeDef  CAN1RxHeader;
CAN_RxHeaderTypeDef  CAN2RxHeader;
	
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */
  CAN_FilterTypeDef  sFilterConfig;//����һ���������ṹ��
  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 6;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_6TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
  //����
  /* Configure the CAN Filter */
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 14;

  if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }


  /* USER CODE END CAN1_Init 2 */

}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */
 CAN_FilterTypeDef  sFilterConfig;//����һ���������ṹ��
  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 12;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_6TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */
 /* Configure the CAN Filter */
  sFilterConfig.FilterBank = 14;//���ù�����,˫·CANʱ,CAN1=[0..13] CAN2=[14..28]
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO1;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 14;

  if (HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }
  /* USER CODE END CAN2_Init 2 */

}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN1 GPIO Configuration
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/*
0-255 	1
0-65535 2
*/

void Car_Can_Iint()
{
		

	
	
//��ʼ��CAN
	//����CAN1��ע�ⲻ������ʱ֮ǰ�������ᵼ��CAN�жϳ����ܷ�
  /* Start the CAN peripheral */
  if (HAL_CAN_Start(&hcan1) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }
  /* Activate CAN RX notification */
  if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }
	//����CAN2��ע�ⲻ������ʱ֮ǰ�������ᵼ��CAN�жϳ����ܷ�
  /* Start the CAN peripheral */
  if (HAL_CAN_Start(&hcan2) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }

  /* Activate CAN RX notification */
  if (HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }


		//��ʼ��ADC
		if(HAL_ADC_Start_DMA(&hadc1,ADCValueDMA, AIN_COUNT) != HAL_OK)//����ADC��DMA���ɼ�������ֱ�ӷ���
  {
    /* Start Conversation Error */
    Error_Handler(); 
  } 
	
}

//CAN�����жϻص�����

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
//	canReceiveMsg_t CAN1RxMsg; 

	canReceiveMsg_t CAN1RxMsg; 
	
//	CAN_TxHeaderTypeDef	TxHeader;
//	uint32_t TxMailbox;
	

	
	if(CAN1 == hcan->Instance)
	{
		if(HAL_OK == HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN1RxHeader, (uint8_t *)&(CAN1RxMsg.Data)))
		{
			
			if(CAN1RxHeader.IDE == CAN_ID_STD)
			{
				//��׼֡
				CAN1RxMsg.Id = CAN1RxHeader.StdId;
				CAN1RxMsg.IDE=CAN_ID_STD;
				
			}else{
				//��չ֡
				CAN1RxMsg.Id = CAN1RxHeader.ExtId;
				CAN1RxMsg.IDE=CAN_ID_EXT;
			}
			xQueueSendToBackFromISR(qCanIsrToCAN1Rx, &CAN1RxMsg, 0);
		
		}

	}
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	
	canReceiveMsg_t CAN2RxMsg; 

	if(CAN2 == hcan->Instance)
	{
		if(HAL_OK == HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &CAN2RxHeader, (uint8_t *)&(CAN2RxMsg.Data)))
		{
			if(CAN2RxHeader.IDE == CAN_ID_STD)
			{
				//��׼֡
				CAN2RxMsg.Id = CAN2RxHeader.StdId;
				CAN2RxMsg.IDE=CAN_ID_STD;
			}else{
				//��չ֡
				CAN2RxMsg.Id = CAN2RxHeader.ExtId;
				CAN2RxMsg.IDE=CAN_ID_EXT;
			}
			
			xQueueSendToBackFromISR(qCanIsrToCAN1Rx, &CAN2RxMsg, 0);
		}
		
	}
}

/********************************************************
 * @brief    CAN���ⷢ����Ϣ
 * @param    Send_CAN_Message_MAIN(uint32_t canId,uint8_t canData[8],uint8_t CAN_CH,uint8_t What_DLC,uint8_t What_IDE)	
 *
 * @param    canId    ��  ���͵�CAN��ID��
 * @param    canData  ��  CAN������
 * @param    CAN_CH   ��  CAN��ͨ��	
																				CAN1:1
																				CAN2:2

 * @param    What_DLC ��  CAN���ݳ���		����:8
 * @param    What_IDE ��  CAN����֡��ʽ	��׼֡��0 		��չ֡:1
 *
 * @return   ��
 *
 * @note     ������Ϣ����
 *
 * @see      Send_CAN_Message_MAIN(0x123456,canData[8],0,8,1);  //������Ϣ����
 *
 * @date     2023/9/9 ŵ־�� ������
 *
 * @verify   δУ��
**********************************************************/
void Send_CAN_Message_MAIN(uint32_t canId,uint8_t canData[8],uint8_t CAN_CH,uint8_t What_DLC,uint8_t What_IDE)
{


	CAN_TxHeaderTypeDef	TxHeader;
	uint32_t TxMailbox;

	
	TxHeader.DLC = What_DLC;
	TxHeader.StdId = 0x000;
	TxHeader.RTR = CAN_RTR_DATA;//����֡
	
	
	TxHeader.ExtId = canId;
	//ѡ��֡��ʽ
	if(What_IDE==0)
	{
		//��׼֡
		TxHeader.IDE = CAN_ID_STD;//��չ֡��ʽ
	}else{
		
		//��չ֡
		TxHeader.IDE = CAN_ID_EXT;//��չ֡��ʽ
	}

	
	//ѡ��ͨ��
	if(CAN_CH==1)
	{
		//ͨ��1
		if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, canData, &TxMailbox) == HAL_OK) {
		//
		}
	}else{
		//ͨ��2
		if(HAL_CAN_AddTxMessage(&hcan2, &TxHeader, canData, &TxMailbox) == HAL_OK) {
		//
		}
	}


		
}

/* USER CODE END 1 */
