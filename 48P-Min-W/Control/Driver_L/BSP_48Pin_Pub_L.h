
//对外暴漏函数
#ifndef __BSP_48PIN_PUB_H__
#define __BSP_48PIN_PUB_H__

#include "stdint.h"
#include "tim.h"


#define EEPROM_ADDRESS 0xA0
#define PCA9555_ADDRESS 0x40 // PCA9555APW的I2C地址

//--------------------------整车控制记录仪-------------------------------------------
typedef struct
{
	uint16_t Type;	//汽车型号
	
	//行驶控制
	uint16_t Rpmspeed;//引擎转速 
	
	uint8_t Driving_Direction;						//行驶方向				0.空挡 1.前进 2.后退
	uint8_t Speed_Mode;										//速度模式				0.乌龟 1.兔子 2.寸进
	uint8_t High_Torque_Mode_EN;					//使能大扭矩模式
	
	uint8_t Xn;    												//旋钮
	
	uint8_t Speed;  											//行驶速度
	uint8_t Directional_Switch_Brake_EN;	//刹车是否使能使能，用于防止速度切换
	
	
	//行驶控制
	uint16_t Drive_Max_Rpm;								//现在最大转速
	uint16_t Drive_Max_Torque;						//现在最大扭矩
	
	uint16_t Feedback_Nm;									//电机反馈力矩值
	uint16_t Cruise_RPM;									//定速
	
	uint8_t Pedal_Enable;									//踏板使能	
	uint16_t Pedal_oment;									//踏板力矩
	
	//定速巡航
	uint8_t cruise_Enable;								//定速使能		//0:不使能 1:准备使能 2:使能

	uint16_t Cruise_oment;								//定速调整力矩
	uint16_t Threshold_Force;								//定速调整力矩	
	
	
	//仪表台变量
	uint8_t Forward_switch;								//前进开关 0:关   1开
	uint8_t Back_switch;									//后退开关 0:关   1开
	uint8_t Speed_switch;									//高低速 0:低速   1高速
	uint8_t record_Speed_state;						//原有高低速 0:低速   1高速
	uint8_t record_state_flag;						//原有高低速切换标志位 0:不用切 1：正在切


	//液压控制
	uint16_t Oil_Pump_Speed;							//油泵转速 
	uint8_t Third_Way_Lock;								//第三路液压锁定开关 0:非锁定   1准备锁定  2准备锁定后 3锁定  4锁定后
	uint16_t Third_Way_Lock_Value;					//第三路液压锁定值		
	uint16_t Third_hydraulic_speed;					//第三路液压电机值
	uint8_t Floa_Switch;										//浮动开关控制 
		
	//灯光 喇叭控制
	uint8_t Headlight_Ctrl;								//大灯控制
	uint8_t Tail_Light;										//尾部灯光控制 0:不亮 1:大灯量50%亮度 2:刹车亮100%亮度
	
	//电池能量 
	uint16_t oil; 												//整车燃油量
	uint16_t Vbus; 												//整车电池电压 
	uint8_t V12;													//12V电池 0-255(0.1V)
	uint16_t Bus_current; 								//电机母线电流值


	
	//辅助灯具
	uint8_t Trumpet_Ctrl;									//喇叭控制
	uint8_t Hydraulic_oil_fan; 						//液压油散热风扇
	




	

	
} Vehicle_Parameters_t;


//PWM封装结构体
typedef struct
{
	
	//以下为封装PWM函数
	uint16_t MOS0_Dynamo_Value;							//发电机励磁输出
	uint16_t MOS1_Meter_Power_Value;					//仪表电源
	uint16_t MOS2_Backup_Light_Sound_Value;				//倒车灯、喇叭
	uint16_t MOS3_Brake_Light_Value;					//刹车灯
	
	uint16_t MOS6_Grease_Pump_Value;					//黄油泵
	uint16_t MOS7_Grease_Pump_Value;					//黄油泵
	uint16_t MOS8_Float_Switch_Value;					//浮动开关（大臂减震）
	uint16_t MOS9_Float_Switch_Value;					//浮动开关（大臂减震）
	uint16_t MOS10_Switching_Mode4;						//第四路切换
	uint16_t MOS11_Switching_Mode4;						//第四路切换
	uint16_t MOS12_Honk_Out_Value;							//喇叭
	uint16_t MOS13_Hydraulic_Lock;						//液压锁阀
	uint16_t MOS14_Switching_Mode3;						//第三路换向阀2
	uint16_t MOS15_Switching_Mode3;						//第三路换向阀1
	uint16_t MOS16_Brake;											//刹车电磁阀
	uint16_t MOS17_Motor;											//变量马达
	uint16_t MOS18_retreat_Vulue;							//后退阀
	uint16_t MOS19_advance_Vulue;							//前进阀
	
}MOS_Ctrl_t;


//----------------------ADC控制区域------------------------------------

/*--------ADC-----------------*/
#define AIN_COUNT								(13)
extern uint32_t ADCValueDMA[AIN_COUNT] ;//此数组仅用于ADC_DMA使用，数据在ADC中断里用消息发给其他线程

 
/*--------PMOS----------------*/
//PMOS通道数20个0-19
#define OUT_CHANNEL_COUNT			(20)
//引脚配置
#define OUT_INDEX_12V_SSR_NUM							(11)	//12V继电器



/*各路模拟量传感器对应控制板AD接口*/ //请根据DMA循序修改此位置
//油门角度 刹车5V 旋钮


#define AIN_Brake_1_Index							(1)		//刹车
#define AIN_Knob_2_Index							(2)  	//旋钮
#define AIN_Accelerator_0_Index				(3)		//油门踏板

#define AIN_EL_MOS1_Index							(7)  	//MOS1_电流 
#define AIN_EL_MOS3_Index							(8)  	//MOS3_电流  
#define AIN_EL_MOS18_Index						(9)  	//MOS18_电流 
#define AIN_EL_MOS19_Index						(10)  //MOS19_电流 


#define AIN_Vrefint_Index							(11)  	//电池电压




//PMOS_Out TIM对应的通道
typedef struct
{
	TIM_HandleTypeDef *phtim;	//定时器
	uint32_t channel;					//定时器通道
} timChannel_t;

/*----------------开关量-------------------------------*/
#define IN_DI_COUNT			(7)

//开关量 对应的通道
typedef struct
{
	GPIO_TypeDef* GPIOx;	//GPIO号  PB
	uint16_t GPIO_Pin;		//引脚号  16
	
} DI_Channel_t;

//----------------------ADC控制区域------------------------------------
typedef struct
{
	int16_t Throttle_percent;	//Null
	int16_t Brake_angle;		//刹车角度
	int16_t Throttle_angle;		//油门角度
	int16_t Knob_position;		//旋钮
} adcPhyField1_t;

typedef struct
{
	int16_t Fuel_percent;		//燃油量百分比
	int16_t Water_temp;			//水温0.1C
	int16_t Oil_temp;			//液压油温0.1C
	int16_t MOS1_current;		//MOS1_电流
} adcPhyField2_t;

typedef struct
{
	int16_t MOS3_EL_ADC;//MOS3_电流
	int16_t MOS18_EL_ADC;//MOS18_电流
	int16_t MOS19_EL_ADC;//MOS19_电流
	int16_t VrefX100;
} adcPhyField3_t;

typedef struct
{
	adcPhyField1_t adcPhyField1;
	adcPhyField2_t adcPhyField2;
	adcPhyField3_t adcPhyField3;
} adcPhyResult_t;//源自本板ADC的输入。开发初期，定义为uint32_t，与ADC数组长度相同，后来改存换算后的物理值,于是改int16_t，与PhyValue数组相同



//--------------------------------脉冲捕获配置区域-------------------
/*转速传感器对应的通道: 0 - SPEED_CHANNEL_COUNT */
#define Engine_SPEED0_CHANNEL_INDEX	(0)
#define Engine_SPEED1_CHANNEL_INDEX	(1)

#define SPEED_CHANNEL_COUNT		(4)
#define ENGINESPEED_SENSOR_GAIN			(1)

typedef struct
{
	unsigned int SPD0_Speed;		//转速传感器0
	unsigned int SPD1_Speed;		//转速传感器1

} Pulse_Speed_t; //转速


//声明函数区
void Analytic_CAN_DATA_STD(void);
void Analytic_CAN_DATA_EXT(void);
extern timChannel_t Out_List[OUT_CHANNEL_COUNT];
void SET_PWM_PMOS(int PMOS_Num,int PMOS_Num_duty);	//控制PWM占空比
void Car_Iint(void);
unsigned int Out_DI_Switch(unsigned int DI_Num);

void MOS_Unified_OUT(void);

extern uint16_t rpms[];//各路转速输入计算为rpm值

//-----------ADC区域-------------
int16_t permille(uint16_t val, uint16_t val_from, uint16_t val_to, int8_t from_min);//数据换算为千分比的分子

extern adcPhyResult_t adcPhyResult;
extern Pulse_Speed_t Pulse_Speed;
void calcPhyValue(uint16_t VrefX100, uint32_t * adcArray, int16_t * phyArray);


void EEPROM_Write(uint16_t mem_address, uint8_t *data, uint16_t size);
void EEPROM_Read(uint16_t mem_address, uint8_t *data, uint16_t size);


void MOS_ST_State(void);
#endif

