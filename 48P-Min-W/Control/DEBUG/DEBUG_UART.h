#ifndef __DEBUG_UART_H__
#define __DEBUG_UART_H__

#include "stdio.h"
#include "usart.h"
#include "freertos.h"
#include "common_fifo.h"
/* ��������ö�٣������޸ģ� */
typedef enum
{
	D_uint8 = 1,
	D_uint16 = 2,
	D_uint32 = 3,
	D_int8 = 4,
	D_int16 = 5,
	D_int32 = 6,
	D_float = 7,
}D_X_enum;


/* CMD����ṹ�壬�����޸ģ� */
typedef const struct CMD_str	//��32�ֽ�
{
	char CMD[24];					//ʶ���
	uint8	(*Program)(void);	//����ִ��
}CMD_str;

/* CMD���ݽṹ�壬�����޸ģ� */
typedef const struct CMD_Data_str
{
	char CMD[24];					//ʶ���
	void *data_p;	//����ָ��
	D_X_enum D_X; //��������ö��
	uint8	(*Program)(const char *Str1, uint8 ChangeX, uint16 CMDnum);	//����ִ�У�ԭ���ݣ��������ݣ���������
}CMD_Data_str;





//ȫ�ֱ���������


extern float desired_current;
extern float Kp_A ;
extern float Ki_A ;
extern float Kd_A ;


void DEBUG_UART_Init(void);
uint8 Cmd_DataManage(const char *Str1, uint8 ChangeX, uint16 CMDnum);
uint8 Cmd_Size(void);
uint8 Cmd_help(void);
uint8 Cmd_Time(void);
uint8 Cmd_cpuid(void);
uint8 Cmd_reset(void);
uint8 Cmd_save(void);
uint8 Cmd_Fifo(void);
uint8 Cmd_test(void);
uint8 IfSeachCmd(void);
uint8 IfSeachCmdData(const char *Str1, uint8 ChangeX, uint16 CMDnum);


void DEBUG_Item(void);
void pwm_control_loop(unsigned int target_current);
#endif /*__DEBUG_UART_H__*/

