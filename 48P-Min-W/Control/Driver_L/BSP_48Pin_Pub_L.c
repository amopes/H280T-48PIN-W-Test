//������
#include "BSP_48Pin_Pub_L.h"
#include "220E_Dis_Pub_L.h"
#include "i2c.h"
#include "Diagnose.h"
#include "string.h"

//uint32_t ADCValueDMA[AIN_COUNT] = {0};//�����������ADC_DMAʹ�ã�������ADC�ж�������Ϣ���������߳�


//-------------------------------ADC�˲�����---------------------------
uint32_t ADCValueDMA[AIN_COUNT] = {0};//�����������ADC_DMAʹ�ã�������ADC�ж�������Ϣ���������߳�
adcPhyResult_t adcPhyResult;
Pulse_Speed_t Pulse_Speed;

uint16_t rpms[SPEED_CHANNEL_COUNT] = {0};//��·ת���������Ϊrpmֵ

extern Vehicle_Parameters_t Vehicle_Parameters;	//�������ƽṹ��
extern  MOS_Ctrl_t MOS_Ctrl;	//�������ƽṹ��
//PMOS_Out TIM��Ӧ��ͨ��

timChannel_t Out_List[OUT_CHANNEL_COUNT] = {
	{&htim10, TIM_CHANNEL_1},
	{&htim2, TIM_CHANNEL_1},
	{&htim2, TIM_CHANNEL_2},
	{&htim8, TIM_CHANNEL_4},
	{&htim8, TIM_CHANNEL_3},
	{&htim8, TIM_CHANNEL_2},
	{&htim8, TIM_CHANNEL_1},
	{&htim4, TIM_CHANNEL_4},
	{&htim4, TIM_CHANNEL_3},
	{&htim4, TIM_CHANNEL_2},
	{&htim4, TIM_CHANNEL_1},
	{&htim12, TIM_CHANNEL_2},
	{&htim12, TIM_CHANNEL_1},
	{&htim2, TIM_CHANNEL_4},
	{&htim2, TIM_CHANNEL_3},
	{&htim1, TIM_CHANNEL_4},
	{&htim1, TIM_CHANNEL_3},
	{&htim1, TIM_CHANNEL_2},
	{&htim1, TIM_CHANNEL_1},
	{&htim14, TIM_CHANNEL_1}
};


//---------------------------������-----------------------------------
DI_Channel_t In_Di[IN_DI_COUNT] = {
	
	{DI0_PD11_GPIO_Port,	DI0_PD11_Pin},
	{DI1_PD10_GPIO_Port	,	DI1_PD10_Pin},
	{DI2_T9CH2_GPIO_Port,	DI2_T9CH2_Pin},
	{DI3_T9CH1_GPIO_Port,	DI3_T9CH1_Pin},
	{DI4_PD3_GPIO_Port,		DI4_PD3_Pin},
	{DI5_PD4_GPIO_Port,		DI5_PD4_Pin}
	
	
	
};


//-------------------������--------------------------
/********************************************************
 * @brief    ����������
 *
 * @param    DI_Num    		��  ���������
 *
 * @return   ��
 *
 * @note     �ɼ�������
 *
 * @see      Out_DI_Switch(0);
 *
 * @date     2024/3/15 ŵ־�� ������
**********************************************************/
unsigned int Out_DI_Switch(unsigned int DI_Num)
{
	if(DI_Num<=IN_DI_COUNT &&  DI_Num>=0)
	{

		return HAL_GPIO_ReadPin(In_Di[DI_Num].GPIOx,In_Di[DI_Num].GPIO_Pin);		//��������
		
	}else{
	
		return 0;			//��������
	}
}

/********************************************************
 * @brief    PWM����
 *
 * @param    PMOS_Num    		��  PWMͨ���� 0-19
 * @param    PMOS_Num_duty  ��  PWMռ�ձ� 0-999  
 *
 * @return   ��
 *
 * @note     ���ڿ���PWM���蹤��
 *
 * @see      SET_PWM_PMOS(0,999);  //����PWMͨ��0 P0_19
 *
 * @date     2023/9/1 ŵ־�� ������
**********************************************************/
void SET_PWM_PMOS(int PMOS_Num,int PMOS_Num_duty )
{
	
	//�ж�һ�������Ƿ���ȷ
	if(PMOS_Num<OUT_CHANNEL_COUNT &&  PMOS_Num>=0)
	{
		
		
		__HAL_TIM_SetCompare(Out_List[PMOS_Num].phtim, Out_List[PMOS_Num].channel, PMOS_Num_duty );    //ͨ���޸ıȽ�ֵ���ı�ռ�ձ�
	
	}
	
	
}

/********************************************************
 * @brief    PWM�˿�����ͳһ���
 *
 * @param    ��
 *
 * @return   ��
 *
 * @note     �ɼ�������
 *
 * @see      Out_DI_Switch(0);
 *
 * @date     2024/3/15 ŵ־�� ������
**********************************************************/
void MOS_Unified_OUT()
{
	//����ΪMOS���������"BSP_48Pin_Pub_L.h" �޸Ķ�Ӧ�˿�
	SET_PWM_PMOS(0,999);//������������
	SET_PWM_PMOS(1,MOS_Ctrl.MOS1_Meter_Power_Value);
	SET_PWM_PMOS(2,MOS_Ctrl.MOS2_Backup_Light_Sound_Value);
	SET_PWM_PMOS(3,MOS_Ctrl.MOS3_Brake_Light_Value);
	
	
//	SET_PWM_PMOS(6,MOS_ctrl.MOS6_Grease_Pump_Value);
//	SET_PWM_PMOS(7,MOS_ctrl.MOS7_Grease_Pump_Value);
	
	
	SET_PWM_PMOS(8,MOS_Ctrl.MOS8_Float_Switch_Value);
	SET_PWM_PMOS(9,MOS_Ctrl.MOS9_Float_Switch_Value);
	
	SET_PWM_PMOS(10,MOS_Ctrl.MOS10_Switching_Mode4);
	SET_PWM_PMOS(11,MOS_Ctrl.MOS11_Switching_Mode4);
	
	SET_PWM_PMOS(12,MOS_Ctrl.MOS12_Honk_Out_Value);
	
	SET_PWM_PMOS(13,MOS_Ctrl.MOS13_Hydraulic_Lock);
	
	SET_PWM_PMOS(14,MOS_Ctrl.MOS14_Switching_Mode3);
	SET_PWM_PMOS(15,MOS_Ctrl.MOS15_Switching_Mode3);
	
	SET_PWM_PMOS(16,MOS_Ctrl.MOS16_Brake);
	SET_PWM_PMOS(17,MOS_Ctrl.MOS17_Motor);//400 - 800mA;	PWM:210 - 420
	
	SET_PWM_PMOS(18,MOS_Ctrl.MOS19_advance_Vulue);//175��380mA�� - 550(1250) | 610(1310mA)
	SET_PWM_PMOS(19,MOS_Ctrl.MOS18_retreat_Vulue);//���� 135��300mA�� -  600��1300mA��| 550(1220mA)
	
}





void calcPhyValue(uint16_t VrefX100, uint32_t * adcArray, int16_t * phyArray)
{
	//14->13.83
	if(VrefX100 == 0)//����ò�������Ĳο���ѹΪ0��������stm32f407�ڲ�V12������ʵ��VDDAֵ������, ��λ:0.01V
	{
		*(phyArray+AIN_Vrefint_Index) = (uint16_t)(1.1854 * 4096 / (*(adcArray+AIN_Vrefint_Index)) * 100);
	}
	

		*(phyArray+AIN_Brake_1_Index) = *(adcArray+AIN_Brake_1_Index);								//ɲ��
		*(phyArray+AIN_Knob_2_Index) = *(adcArray+AIN_Knob_2_Index);									//��ť
		*(phyArray+AIN_Accelerator_0_Index) = permille((*(adcArray+AIN_Accelerator_0_Index)), 850, 3600, 1); //����
	
		*(phyArray+AIN_EL_MOS1_Index) = *(adcArray+AIN_EL_MOS1_Index);								//��ť
		*(phyArray+AIN_EL_MOS3_Index) = *(adcArray+AIN_EL_MOS3_Index);								//��ť
		*(phyArray+AIN_EL_MOS18_Index) = *(adcArray+AIN_EL_MOS18_Index);								//��ť
		*(phyArray+AIN_EL_MOS19_Index) = *(adcArray+AIN_EL_MOS19_Index);								//��ť
}




//���ݻ���Ϊǧ�ֱȵķ���
//val_from == �������
//val_to   == �����յ�
//from_min : 1 == �������ΪСֵ; else == �������Ϊ��ֵ
//����ֵΪ0-999����ֵ�����󷵻�-1
int16_t permille(uint16_t val, uint16_t val_from, uint16_t val_to, int8_t from_min)
{
	if(from_min)
	{
		if(val_to < val_from) return -1;
		if(val < val_from) val = val_from;
		if(val > val_to) val = val_to;
		return (val - val_from) * 999 / (val_to - val_from);
	}
	else
	{
		if(val_to > val_from) return -1;
		if(val < val_to) val = val_to;
		if(val > val_from) val = val_from;
		return (val_from - val) * 999 / (val_from - val_to);
	}
}



//--------------------------------------IO��չ��EEPROOM------------------------------------------------
void EEPROM_Write(uint16_t mem_address, uint8_t *data, uint16_t size)
{ 
  HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDRESS, mem_address, I2C_MEMADD_SIZE_16BIT, data, size, HAL_MAX_DELAY);
}

void EEPROM_Read(uint16_t mem_address, uint8_t *data, uint16_t size)
{
  HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDRESS, mem_address, I2C_MEMADD_SIZE_16BIT, data, size, HAL_MAX_DELAY);
}

//IO
uint16_t value=0;
void MOS_ST_State()
{
   uint8_t data[2];  // ���ڴ洢��ȡ��16λIO״̬
   HAL_I2C_Master_Receive(&hi2c1, PCA9555_ADDRESS, data, 2, HAL_MAX_DELAY);  // ��PCA9555��ȡ16λIO״̬
   uint16_t value = (data[0] << 8) | data[1];  // ����ȡ�������ֽ���ϳ�һ��16λ��
	
	MOS_ST_PCA.MOS0_ST = (value >> 8) & 0x1;
    MOS_ST_PCA.MOS2_ST = (value >> 9) & 0x1;
    MOS_ST_PCA.MOS4_ST = (value >> 10) & 0x1;
    MOS_ST_PCA.MOS5_ST = (value >> 11) & 0x1;
    MOS_ST_PCA.MOS6_ST = (value >> 12) & 0x1;
    MOS_ST_PCA.MOS7_ST = (value >> 13) & 0x1;
    MOS_ST_PCA.MOS8_ST = (value >> 14) & 0x1;
    MOS_ST_PCA.MOS9_ST = (value >> 15) & 0x1;
    MOS_ST_PCA.MOS17_ST = (value >> 0) & 0x1;
    MOS_ST_PCA.MOS16_ST = (value >> 1) & 0x1;
    MOS_ST_PCA.MOS15_ST = (value >> 2) & 0x1;
    MOS_ST_PCA.MOS14_ST = (value >> 3) & 0x1;
    MOS_ST_PCA.MOS13_ST = (value >> 4) & 0x1;
    MOS_ST_PCA.MOS12_ST = (value >> 5) & 0x1;
    MOS_ST_PCA.MOS11_ST = (value >> 6) & 0x1;
    MOS_ST_PCA.MOS10_ST = (value >> 7) & 0x1;


//printf("Data: %04X\r\n", value);  // ��ӡIO״̬��%04X��ʾ��ӡΪ4λʮ��������
}
