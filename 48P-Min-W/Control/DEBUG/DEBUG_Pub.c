
#include "DEBUG_Pub.h"
#include "stdio.h"
#include "usart.h"
#include "can.h"
#include "freertos.h"
#include "Logic_Pub_L.h"
#include "BSP_48Pin_Pub_L.h"

//���Եƹ�
void Test_li()
{
//	SET_PWM_PMOS(7,999);//��ת��
//	vTaskDelay(2000);
//	SET_PWM_PMOS(7,0);
//	SET_PWM_PMOS(6,999);//��ת��
//	vTaskDelay(2000);
//	SET_PWM_PMOS(6,0);
//	SET_PWM_PMOS(0,999);//���
//	vTaskDelay(2000);
//	SET_PWM_PMOS(0,0);
//	SET_PWM_PMOS(2,999);//β��
//	vTaskDelay(2000);
//	SET_PWM_PMOS(2,0);
	
	
//	if(AD_Buf[1]>200)
// {
//	 SET_PWM_PMOS(10,999);//������
// }else{
//	 SET_PWM_PMOS(10,0);//����
//	 
// }

}
//�����ڷ��ؼ���λ��
void FT_printf(int D1,int D2,int D3,int D4,int D5,int D6)
{
	//���ؼ���λ������
	printf("samples:%d, %d, %d, %d, %d, %d\n",D1,D2,D3,D4,D5,D6);
	
//	printf("samples");
	
}



void TEst_Can()
{
	uint8_t data[9] = {0x01, 0x02, 0x03, 0x04,0x05,0x06,0x07,0x08}; //��Ҫ���͵�����
	
	 Send_CAN_Message_MAIN(0x1234,data,1,8,1);
	Send_CAN_Message_MAIN(0x1234,data,2,8,0);
}

//MOS_PWM_Test
void MOS_PWM_Test()
{
		 
// SET_PWM_PMOS(0,999);

// SET_PWM_PMOS(2,999);
// 
// SET_PWM_PMOS(6,999);
// SET_PWM_PMOS(7,999);
// 

// HAL_Delay(500);
// 
// SET_PWM_PMOS(0,0);

// SET_PWM_PMOS(2,0);
// 
// SET_PWM_PMOS(6,0);
// SET_PWM_PMOS(7,0);
	 

	
//	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	
//	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	
//	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_4, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	
//	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	
//	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_4, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	
//	__HAL_TIM_SetCompare(&htim10, TIM_CHANNEL_1, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//		
//	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_2, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	
//	__HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, 500);    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
//	
//	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);  //����PWMͨ��1

//	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);  //����PWMͨ��1
//	
//	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);  //����PWMͨ��1
//	
//	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);  //����PWMͨ��1
//	
//	HAL_TIM_PWM_Start(&htim10,TIM_CHANNEL_1);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);  //����PWMͨ��1
//	HAL_TIM_PWM_Start(&htim14,TIM_CHANNEL_1);  //����PWMͨ��1
	
	
}

//ADC+DMA����
void ADC_DMA_Test()
{
	
//		printf("-------------------------------------\r\n\r");
//		printf("AD1=%f\r\n\r",AD_Buf[0]/1241.2);
//    printf("AD2=%f\r\n\r",AD_Buf[1]/1241.2);
//		printf("AD3=%f\r\n\r",AD_Buf[2]/1241.2);
//    printf("AD4=%f\r\n\r",AD_Buf[3]/1241.2);
//		printf("AD5=%f\r\n\r",AD_Buf[4]/1241.2);
//    printf("AD6=%f\r\n\r",AD_Buf[5]/1241.2);
//		printf("AD7=%f\r\n\r",AD_Buf[6]/1241.2);
//		printf("AD8=%f\r\n\r",AD_Buf[7]/1241.2);
//    printf("AD9=%f\r\n\r",AD_Buf[8]/1241.2);
//		printf("AD10=%f\r\n\r",AD_Buf[9]/1241.2);
//    printf("AD11=%f\r\n\r",AD_Buf[10]/1241.2);
//		printf("AD12=%f\r\n\r",AD_Buf[11]/1241.2);
//    printf("AD11=%f\r\n\r",AD_Buf[12]/1241.2);
//	
	
}

//GPIO����������
void GPIO_INPUT()
{
	
	
//FT_printf(HAL_GPIO_ReadPin(DI0_PD11_GPIO_Port,DI0_PD11_Pin),HAL_GPIO_ReadPin(DI1_PD10_GPIO_Port,DI1_PD10_Pin),HAL_GPIO_ReadPin(DI2_T9CH2_GPIO_Port,DI2_T9CH2_Pin),HAL_GPIO_ReadPin(DI3_T9CH1_GPIO_Port,DI3_T9CH1_Pin),HAL_GPIO_ReadPin(DI4_PD3_GPIO_Port,DI4_PD3_Pin),HAL_GPIO_ReadPin(DI5_PD4_GPIO_Port,DI5_PD4_Pin));
		
}



void EEPROM_Test(void)
{
    uint8_t data_to_write[2] = {0x00, 0x16}; // Data to write to EEPROM
    uint8_t data_to_read[2];                  // Data read from EEPROM

    // Write data to EEPROM
	// EEPROM_Write(0x0000, data_to_write, sizeof(data_to_write));

    // Read data from EEPROM
    EEPROM_Read(0x0000, data_to_read, sizeof(data_to_read));

    // Print the read data (for testing purpose)
    printf("Data read from EEPROM: %02X %02X\n", data_to_read[0], data_to_read[1]);
}

//IO
void PCA_Test(void)
{
	    MOS_ST_State();
  
}



//�����Ե��� ֻ��ϵͳǰ����һ��
void Functional_Debug() //�����Ե��� TEST
{
	
	
	Flash_Test();
	
}

//void System_Printing()
//{
//	//ϵͳ����
//	 printf("Hercules system is activating\r\n\n");
//	//ϵͳ��ǰ�汾��
//	printf("Program version Number:%d\r\n\n",SOFTWARE_REV);
//	//Ŀ��汾��
//	printf("Original program version number:%d\r\n\n",SOFTWARE_REV);
//	
//}
