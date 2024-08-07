#include "HGLS_7_appearance.h"
//控制器屏幕合集
//hgls_appearance_all_t		hgls_appearance_all;
//控制器发送
//hgls_send_pack1_t			hgls_send_pack1;
//hgls_send_pack2_t			hgls_send_pack2;
//hgls_send_pack3_t			hgls_send_pack3;

//控制器 发送给仪表
VCU_Send_to_Screen_1  VCU_Send_to_Screen_1_pack;
VCU_Send_to_Screen_2  VCU_Send_to_Screen_2_pack;
VCU_Send_to_Screen_3  VCU_Send_to_Screen_3_pack;
//控制器 接收 接收仪表数据
hgls_rec_pack_t				hgls_rec_pack;

//控制器 发送给 灯光模块
CAN_H180_Meter_7_str CAN_H180_Meter_7_pack;
