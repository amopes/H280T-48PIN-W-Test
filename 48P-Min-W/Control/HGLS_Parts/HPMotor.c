#include "HPMotor.h"

//用于存放从模块发来的最新CAN报文数据
motor_pump_state1_t			motor_pump_state1;
motor_drive_state1_t		motor_drive_state1;
motor_drive2_ctrl_t		motor_drive2_ctrl;
motor_pump_state2_t			motor_pump_state2;
motor_drive_state2_t		motor_drive_state2;
x14188480_t x14188480;
x14188400_t x14188400;

//即将发往模块的CAN报文
motor_pump_ctrl_t			motor_pump_ctrl;
motor_drive_ctrl_t		motor_drive_ctrl;

