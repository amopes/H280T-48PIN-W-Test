
//���Ⱪ©����
#ifndef __BSP_48PIN_PUB_H__
#define __BSP_48PIN_PUB_H__

#include "stdint.h"
#include "tim.h"


#define EEPROM_ADDRESS 0xA0
#define PCA9555_ADDRESS 0x40 // PCA9555APW��I2C��ַ

//--------------------------�������Ƽ�¼��-------------------------------------------
typedef struct
{
	uint16_t Type;	//�����ͺ�
	
	//��ʻ����
	uint16_t Rpmspeed;//����ת�� 
	
	uint8_t Driving_Direction;						//��ʻ����				0.�յ� 1.ǰ�� 2.����
	uint8_t Speed_Mode;										//�ٶ�ģʽ				0.�ڹ� 1.���� 2.���
	uint8_t High_Torque_Mode_EN;					//ʹ�ܴ�Ť��ģʽ
	
	uint8_t Xn;    												//��ť
	
	uint8_t Speed;  											//��ʻ�ٶ�
	uint8_t Directional_Switch_Brake_EN;	//ɲ���Ƿ�ʹ��ʹ�ܣ����ڷ�ֹ�ٶ��л�
	
	
	//��ʻ����
	uint16_t Drive_Max_Rpm;								//�������ת��
	uint16_t Drive_Max_Torque;						//�������Ť��
	
	uint16_t Feedback_Nm;									//�����������ֵ
	uint16_t Cruise_RPM;									//����
	
	uint8_t Pedal_Enable;									//̤��ʹ��	
	uint16_t Pedal_oment;									//̤������
	
	//����Ѳ��
	uint8_t cruise_Enable;								//����ʹ��		//0:��ʹ�� 1:׼��ʹ�� 2:ʹ��

	uint16_t Cruise_oment;								//���ٵ�������
	uint16_t Threshold_Force;								//���ٵ�������	
	
	
	//�Ǳ�̨����
	uint8_t Forward_switch;								//ǰ������ 0:��   1��
	uint8_t Back_switch;									//���˿��� 0:��   1��
	uint8_t Speed_switch;									//�ߵ��� 0:����   1����
	uint8_t record_Speed_state;						//ԭ�иߵ��� 0:����   1����
	uint8_t record_state_flag;						//ԭ�иߵ����л���־λ 0:������ 1��������


	//Һѹ����
	uint16_t Oil_Pump_Speed;							//�ͱ�ת�� 
	uint8_t Third_Way_Lock;								//����·Һѹ�������� 0:������   1׼������  2׼�������� 3����  4������
	uint16_t Third_Way_Lock_Value;					//����·Һѹ����ֵ		
	uint16_t Third_hydraulic_speed;					//����·Һѹ���ֵ
	uint8_t Floa_Switch;										//�������ؿ��� 
		
	//�ƹ� ���ȿ���
	uint8_t Headlight_Ctrl;								//��ƿ���
	uint8_t Tail_Light;										//β���ƹ���� 0:���� 1:�����50%���� 2:ɲ����100%����
	
	//������� 
	uint16_t oil; 												//����ȼ����
	uint16_t Vbus; 												//������ص�ѹ 
	uint8_t V12;													//12V��� 0-255(0.1V)
	uint16_t Bus_current; 								//���ĸ�ߵ���ֵ


	
	//�����ƾ�
	uint8_t Trumpet_Ctrl;									//���ȿ���
	uint8_t Hydraulic_oil_fan; 						//Һѹ��ɢ�ȷ���
	




	

	
} Vehicle_Parameters_t;


//PWM��װ�ṹ��
typedef struct
{
	
	//����Ϊ��װPWM����
	uint16_t MOS0_Dynamo_Value;							//������������
	uint16_t MOS1_Meter_Power_Value;					//�Ǳ��Դ
	uint16_t MOS2_Backup_Light_Sound_Value;				//�����ơ�����
	uint16_t MOS3_Brake_Light_Value;					//ɲ����
	
	uint16_t MOS6_Grease_Pump_Value;					//���ͱ�
	uint16_t MOS7_Grease_Pump_Value;					//���ͱ�
	uint16_t MOS8_Float_Switch_Value;					//�������أ���ۼ���
	uint16_t MOS9_Float_Switch_Value;					//�������أ���ۼ���
	uint16_t MOS10_Switching_Mode4;						//����·�л�
	uint16_t MOS11_Switching_Mode4;						//����·�л�
	uint16_t MOS12_Honk_Out_Value;							//����
	uint16_t MOS13_Hydraulic_Lock;						//Һѹ����
	uint16_t MOS14_Switching_Mode3;						//����·����2
	uint16_t MOS15_Switching_Mode3;						//����·����1
	uint16_t MOS16_Brake;											//ɲ����ŷ�
	uint16_t MOS17_Motor;											//�������
	uint16_t MOS18_retreat_Vulue;							//���˷�
	uint16_t MOS19_advance_Vulue;							//ǰ����
	
}MOS_Ctrl_t;


//----------------------ADC��������------------------------------------

/*--------ADC-----------------*/
#define AIN_COUNT								(13)
extern uint32_t ADCValueDMA[AIN_COUNT] ;//�����������ADC_DMAʹ�ã�������ADC�ж�������Ϣ���������߳�

 
/*--------PMOS----------------*/
//PMOSͨ����20��0-19
#define OUT_CHANNEL_COUNT			(20)
//��������
#define OUT_INDEX_12V_SSR_NUM							(11)	//12V�̵���



/*��·ģ������������Ӧ���ư�AD�ӿ�*/ //�����DMAѭ���޸Ĵ�λ��
//���ŽǶ� ɲ��5V ��ť


#define AIN_Brake_1_Index							(1)		//ɲ��
#define AIN_Knob_2_Index							(2)  	//��ť
#define AIN_Accelerator_0_Index				(3)		//����̤��

#define AIN_EL_MOS1_Index							(7)  	//MOS1_���� 
#define AIN_EL_MOS3_Index							(8)  	//MOS3_����  
#define AIN_EL_MOS18_Index						(9)  	//MOS18_���� 
#define AIN_EL_MOS19_Index						(10)  //MOS19_���� 


#define AIN_Vrefint_Index							(11)  	//��ص�ѹ




//PMOS_Out TIM��Ӧ��ͨ��
typedef struct
{
	TIM_HandleTypeDef *phtim;	//��ʱ��
	uint32_t channel;					//��ʱ��ͨ��
} timChannel_t;

/*----------------������-------------------------------*/
#define IN_DI_COUNT			(7)

//������ ��Ӧ��ͨ��
typedef struct
{
	GPIO_TypeDef* GPIOx;	//GPIO��  PB
	uint16_t GPIO_Pin;		//���ź�  16
	
} DI_Channel_t;

//----------------------ADC��������------------------------------------
typedef struct
{
	int16_t Throttle_percent;	//Null
	int16_t Brake_angle;		//ɲ���Ƕ�
	int16_t Throttle_angle;		//���ŽǶ�
	int16_t Knob_position;		//��ť
} adcPhyField1_t;

typedef struct
{
	int16_t Fuel_percent;		//ȼ�����ٷֱ�
	int16_t Water_temp;			//ˮ��0.1C
	int16_t Oil_temp;			//Һѹ����0.1C
	int16_t MOS1_current;		//MOS1_����
} adcPhyField2_t;

typedef struct
{
	int16_t MOS3_EL_ADC;//MOS3_����
	int16_t MOS18_EL_ADC;//MOS18_����
	int16_t MOS19_EL_ADC;//MOS19_����
	int16_t VrefX100;
} adcPhyField3_t;

typedef struct
{
	adcPhyField1_t adcPhyField1;
	adcPhyField2_t adcPhyField2;
	adcPhyField3_t adcPhyField3;
} adcPhyResult_t;//Դ�Ա���ADC�����롣�������ڣ�����Ϊuint32_t����ADC���鳤����ͬ�������Ĵ滻��������ֵ,���Ǹ�int16_t����PhyValue������ͬ



//--------------------------------���岶����������-------------------
/*ת�ٴ�������Ӧ��ͨ��: 0 - SPEED_CHANNEL_COUNT */
#define Engine_SPEED0_CHANNEL_INDEX	(0)
#define Engine_SPEED1_CHANNEL_INDEX	(1)

#define SPEED_CHANNEL_COUNT		(4)
#define ENGINESPEED_SENSOR_GAIN			(1)

typedef struct
{
	unsigned int SPD0_Speed;		//ת�ٴ�����0
	unsigned int SPD1_Speed;		//ת�ٴ�����1

} Pulse_Speed_t; //ת��


//����������
void Analytic_CAN_DATA_STD(void);
void Analytic_CAN_DATA_EXT(void);
extern timChannel_t Out_List[OUT_CHANNEL_COUNT];
void SET_PWM_PMOS(int PMOS_Num,int PMOS_Num_duty);	//����PWMռ�ձ�
void Car_Iint(void);
unsigned int Out_DI_Switch(unsigned int DI_Num);

void MOS_Unified_OUT(void);

extern uint16_t rpms[];//��·ת���������Ϊrpmֵ

//-----------ADC����-------------
int16_t permille(uint16_t val, uint16_t val_from, uint16_t val_to, int8_t from_min);//���ݻ���Ϊǧ�ֱȵķ���

extern adcPhyResult_t adcPhyResult;
extern Pulse_Speed_t Pulse_Speed;
void calcPhyValue(uint16_t VrefX100, uint32_t * adcArray, int16_t * phyArray);


void EEPROM_Write(uint16_t mem_address, uint8_t *data, uint16_t size);
void EEPROM_Read(uint16_t mem_address, uint8_t *data, uint16_t size);


void MOS_ST_State(void);
#endif

