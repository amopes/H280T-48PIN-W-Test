#ifndef __HGLS_7_appearance_H__
#define __HGLS_7_appearance_H__

#include "stdint.h"
#include "Sys_Cofig.h"

////控制器屏幕合集
//typedef struct 
//{
//	uint16_t Rpmspeed;//引擎转速 
//	uint16_t Vbus; //整车电池电压 
//	uint8_t Xn;    //旋钮
//	uint8_t Speed;  //行驶速度
//	uint8_t Brake;//刹车
//	uint8_t Oil; //燃油量
//	
//	uint8_t Arm_shock;//大臂减震 0:关   1开
//	uint8_t Hydraulic_lock;//液压锁 0:关   1开
//	uint8_t Low_light;//近光灯 0:关   1开
//	uint8_t Hight_light;//远光灯 0:关   1开
//	uint8_t Hood_lock;//机罩锁 0:关   1开
//	uint8_t Parking_switch;//驻车开关 0:关   1开
//	uint8_t Left_turn;//左转灯 0:关   1开
//	uint8_t Right_turn;//右转灯 0:关   1开
//	uint8_t V12;//12V电池 0-255(0.1V)
//	uint8_t oil_temperature;//液压油温
//	uint8_t water_temperature;//引擎水温
//	uint32_t time;//小时计 0-4294967295(s)
//	
//	uint8_t Forward_switch;//前进开关 0:关   1开
//	uint8_t Back_switch;//后退开关 0:关   1开
//	uint8_t Speed_switch;//高低速 0:低速   1高速
//	uint8_t Constant_speed_switch;//定速开关 0:关   1开
//	uint8_t Working_switch;//工作开关 0:关   1开
//	uint8_t Pressure_relief_switch;//泄压开关 0:关   1开
//	uint8_t Air_filter_switch;//空滤开关 0:关   1开
//	uint8_t Grease_pump;//黄油泵 0:关   1开
//	uint8_t Megaphone;//喇叭 0:关   1开
//	uint8_t Warning_light;//警示灯 0:关   1开
//	uint8_t Oil_return_pressure; //回油压力 
//	uint8_t Filling_pressure; //补油压力 
//	uint8_t Main_valve_pressure; //主阀压力
//	uint8_t Oil_pressure; //机油压力 
//	uint8_t Pilot_pressure;//先导压力 
//	
//}hgls_appearance_all_t;
////控制器发送1
//typedef struct 
//{
//	ULL Rpmspeed:16; //引擎转速 
//	ULL Vbus: 16; //整车电池电压 
//	ULL Xn: 8;    //旋钮
//	ULL Speed: 8;  //行驶速度
//	ULL brake: 8;//刹车
//	ULL Oil: 8; //燃油量
//} hgls_send_pack1_t;
////控制器发送2
//typedef struct 
//{
//	ULL PFNR: 2; //档位 0:空档  1前进  2:后退   3预留
//	ULL Speed_switch: 1; //高低速 0:关   1开
//	ULL Megaphone: 1;    //喇叭 0:关   1开
//	ULL Working_switch: 1;  //工作开关 0:关   1开
//	ULL Hour_count_zero: 1;  //小时计清零  0:不清零  1清零
//	ULL unUsed1: 2; //预留
//	ULL V12: 8;  //12V电池 0-255(0.1V)
//	ULL Bus_current: 16; //电机母线电流值
//	ULL Hydraulic_oil_fan: 8; //液压油散热风扇
//	ULL Feedback_Nm: 16; //电机反馈力矩值
//	ULL unUsed2: 8; //预留

//} hgls_send_pack2_t;
////控制器发送3
//typedef struct 
//{
//	ULL bit0: 1; //泄压开关 0:关   1开
//	ULL bit1: 1; //空滤 0:关   1开
//	ULL bit2: 1; //黄油泵 0:关   1开
//	ULL bit3: 1; //定速开关 0:关   1开
//	ULL unUsed1: 4; //预留
//	ULL Oil_return_pressure: 8; //回油压力 
//	ULL Filling_pressure: 8; //补油压力 
//	ULL Main_valve_pressure: 8; //主阀压力
//	ULL Oil_pressure: 8; //机油压力 
//	ULL Pilot_pressure: 8;//先导压力 
//	ULL oil_temperature: 8; //液压油温
//	ULL water_temperature: 8; //引擎水温

//} hgls_send_pack3_t;

//控制器发送1
typedef struct
{
	int Motor_Speed: 16;			//发动机转速	 0-65535(Rpm)
	int Car_Energy: 16;				//整车能源量	 0-65535(0.1V)
	int Battery_12V: 8;				//12V电池			 0-255(0.1V)
	
	int Car_Move_Mode: 2;			//档位 				0:空档  1前进  2:后退   3驻车
	int High_Or_Low_Speed: 1; //高低速 			0:低速   1高速
	int Work_Switch: 1;	 			//工作开关 		0:关   1开
	int Keep_Speed: 1;				//定速开关 		0:关   1开
	int Add_Electricity: 1;		//充电状态		0:不充电  1充电
	int Brake_Speed: 1;				//刹车 				0:关   1开
	int Reserved: 1;					//预留
	
	int Reserved_Bit6: 8;			//预留
	int Reserved_Bit7: 8;			//预留
	
}VCU_Send_to_Screen_1;

//控制器发送2
typedef struct
{
	int bit0: 1;//图标左1 	0:关   1开
	int bit1: 1;//图标左2	 	0:关   1开
	int bit2: 1;//图标左3 	0:关   1开
	int bit3: 1;//图标左4 	0:关   1开
	int bit4: 1;//图标右1 	0:关   1开
	int bit5: 1;//图标右2	  0:关   1开
	int bit6: 1;//图标右3	  0:关   1开
	int bit7: 1;//图标右4	  0:关   1开
	 
	int byte_1: 8;//显示条左上	0-255
	int byte_2: 8;//显示条左下 	0-255
	int byte_3: 8;//显示条右上 	0-255
	int byte_4: 8;//显示条右下  0-255
	int byte_5: 8;//预留
	int byte_6: 8;//预留
	int byte_7: 8;//预留
	
}VCU_Send_to_Screen_2;

//控制器发送3
typedef struct
{
	int byte_0_bit0: 1;//远光灯	  	0:关   1开
	int byte_0_bit1: 1;//左转灯 		0:关   1开
	int byte_0_bit2: 1;//右转灯 		0:关   1开
	int byte_0_bit3: 1;//驻车开关 	0:关   1开
	int byte_0_bit4: 1;//警示灯 		0:关   1开
	int byte_0_bit5: 1;//高低速 		0:关   1开
	int byte_0_bit6: 1;//快换锁 		0:关   1开
	int byte_0_bit7: 1;//大臂减震 	0:关   1开
	
	int byte_1_bit0: 1;//预热		 	  0:关   1开
	int byte_1_bit1: 1;//喇叭		  	0:关   1开
	int byte_1_bit2: 1;//变速箱1档  0:关   1开
	int byte_1_bit3: 1;//变速箱2档  0:关   1开
	int byte_1_bit4: 1;//后窗雨刷器 0:关   1开
	int byte_1_bit5: 1;//双闪开关   0:关   1开
	int byte_1_bit6: 1;//近光灯     0:关   1开
	int byte_1_bit7: 1;//大臂浮动   0:关   1开
	
	int byte_2_bit0: 1;//喷水器		  0:关   1开
	int byte_2_bit1_2: 2;//雨刷器 	0:空档  1一档  2:二挡   3自动
	int byte_2_bit3: 1;//雾灯 		  0:关   1开
	int byte_2_bit4: 1;//
	int byte_2_bit5: 1;//
	int byte_2_bit6: 1;//
	int byte_2_bit7: 1;//
	
	int byte_3_bit0: 1;//水暖开关		0:关   1开
	int byte_3_bit1: 2;//压缩机 		0:关   1开
	int byte_3_bit2_3: 1;//暖风机 	0:关   1一档2二档 3三档
	int byte_3_bit4: 1;//
	int byte_3_bit5: 1;//
	int byte_3_bit6: 1;//
	int byte_3_bit7: 1;//
	
	int byte_4_bit0: 1;//前进阀
	int byte_4_bit1: 1;//后退阀
	int byte_4_bit2: 1;//变速箱1档
	int byte_4_bit3: 1;//变速箱2档
	int byte_4_bit4: 1;//马达阀
	int byte_4_bit5: 1;//大臂减震阀
	int byte_4_bit6: 1;//大臂浮动阀
	int byte_4_bit7: 1;//快换阀
	
	int byte_5_bit0: 1;//一二路切换阀
	int byte_5_bit1: 1;//三四路切换阀
	int byte_5_bit2: 1;//液压一阀
	int byte_5_bit3: 1;//液压二阀
	int byte_5_bit4: 1;//液压三阀
	int byte_5_bit5: 1;//液压四阀
	int byte_5_bit6: 1;//
	int byte_5_bit7: 1;//
	
	int byte_6_bit0: 1;//泄压开关	  0:关   1开
	int byte_6_bit1: 1;//空滤		 	  0:关   1开
	int byte_6_bit2: 1;//黄油泵   	0:关   1开
	int byte_6_bit3: 1;//小时计清零 0:关   1清零

	
}VCU_Send_to_Screen_3;



//控制器接收

//与油车不一致,留意甄别
typedef struct 
{

	ULL bit2: 1; //右转向 	0:关   1开
	ULL bit1: 1; //左转向		0:关   1开
	ULL bit5: 1; //高低速 	接收仪表：0高速，1低速；取反后0:关   1开
	ULL bit0: 1; //大灯  		0:关   1开
	ULL bit6: 1; //液压锁 	0:关   1开
	ULL bit7: 1; //大臂减震 0:关   1开
	ULL bit16: 1;//转速输入0
	ULL bit17: 1;//转速输入1
	
	ULL bit21: 8;	//蜂鸣器
	ULL bit22: 8;	//主阀压力
	ULL bit23: 8;	//补油泵压力
	ULL bit9: 8;	//喇叭
	ULL bit25: 8;	//回油压力
	ULL bit26: 8;	//机罩锁
	ULL bit3: 8;	//驻车
	

} hgls_rec_pack_t;

//控制器发送给灯光模块
typedef struct
{
	uint8_t bit0: 1;
	uint8_t	bit1: 1;
	uint8_t in_Lamp_Near_bit2: 1;	// 近光灯
	uint8_t in_Lamp_Far_bit3: 1;	// 远光灯
	uint8_t bit4: 1;	
	uint8_t in_Lamp_Left_bit5: 1;	// 左转向
	uint8_t in_Lamp_Right_bit6: 1;// 右转向
	uint8_t bit8: 1;
	
	uint8_t bit1_6: 7;
	uint8_t bit1_7: 1;//转向灯闪烁状态
	
}CAN_H180_Meter_7_str;

//extern hgls_appearance_all_t		hgls_appearance_all;
//extern hgls_send_pack1_t			hgls_send_pack1;
//extern hgls_send_pack2_t			hgls_send_pack2;
//extern hgls_send_pack3_t			hgls_send_pack3;
extern VCU_Send_to_Screen_1  VCU_Send_to_Screen_1_pack;
extern VCU_Send_to_Screen_2  VCU_Send_to_Screen_2_pack;
extern VCU_Send_to_Screen_3  VCU_Send_to_Screen_3_pack;
extern hgls_rec_pack_t				hgls_rec_pack;
extern CAN_H180_Meter_7_str CAN_H180_Meter_7_pack;
#endif
