
//对外暴漏函数
#ifndef __220E_DIS_PUB_H__
#define __220E_DIS_PUB_H__

#include "stdint.h"
#include "tim.h"


//--------------------行走配置----------------------
//模式下最大转数和 模式下最大扭矩

//寸进
#define DRIVE_MODE1_MAX_RPM 1200
#define DRIVE_MODE1_MAX_TORQUE 1500

//乌龟
#define DRIVE_MODE2_MAX_RPM 4000
#define DRIVE_MODE2_MAX_TORQUE 1200

//兔子
#define DRIVE_MODE3_MAX_RPM 7500
#define DRIVE_MODE3_MAX_TORQUE 600


//--------------------油泵配置----------------------

//怠速和最大速度
#define PUMP_MIN_RPM 					600		//待机转速
#define PUMP_BUCKET_MAX_RPM 	1000	//手柄控制收斗最大转速
#define PUMP_SHANK_MAX_RPM 		1500	//手柄控制大臂最大转速
#define PUMP_MAX_RPM 					2000	//波轮控制第三路最大转速

//--------------------油泵配置----------------------
//供电电压 线圈电阻 最大电流 最小电流 加速时间 减速时间

#define HYDRAULIC_MINIMUM_PWM 		280		//最小电流

//--------------------液压配置----------------------
#define HYDRAULIC_ACCELERATION_INTERVENTION 		850		//液压提速介入,电机接入最小值 x-1000  0-1000
#define THIRD_ACCELERATED_INTERVENTION 					700		//第三路液压提速介入,电机接入最小值   0-400
#endif
