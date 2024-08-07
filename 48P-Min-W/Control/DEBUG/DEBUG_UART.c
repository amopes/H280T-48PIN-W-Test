#include "DEBUG_UART.h"


/**
 * CMD调试系统下位机使用说明：
 * 1.变量增改说明：
 * 		在”变量库“中添加一个新行，新行必须在EndCmd之前，顺序不重要，但仍建议按照示例顺序编写
 * 		除EndCmd其他变量都可以删除或重写
 *		示例新行如下：
 * 		{"U8Test",	&U8Test,	D_uint8,	Cmd_DataManage},
 *		"U8Test"为变量在CMD调试系统中的匹配名，与U8Test变量的实际名称不必相同，建议相同或者简写，便于调试
 * 		&U8Test为变量地址
 *		D_uint8为变量类型，必须修改为实际的变量类型此处为枚举变量可以参考D_X_enum中的枚举
 * 		Cmd_DataManage为执行函数，不建议修改使用Cmd_DataManage即可
 * 2.命令增改说明：
 * 		在”命令库“中添加一个新行，新行必须在EndCmd之前，顺序不重要，但仍建议按照示例顺序编写
 * 		库中已有的变量建议不进行删改
 *		示例新行如下：
 * 		{"size",	Cmd_Size},
 *		"size"为命令在CMD调试系统中的匹配名，与Cmd_Size函数的实际名称不必相同，建议相同或者简写，便于调试
 * 		Cmd_Size为执行函数，需要另外定义并声明
 * 3.使用说明：
 * 		1.首先在COBEMX中开启相关串口的串口接收中断
 *		2.将DEBUG_UART_Init函数中的串口结构体指针修改为所需串口
 *		3.将DEBUG_UART_Init函数在main函数调用
 *		4.CMD调试系统启动成功会打印相关信息
 *
 *
 *
 *
 */



/* fifo相关变量，不可修改！ */
uint8 uart_get_data[64];                                                        // 串口接收数据缓冲区
uint8 fifo_get_data[64];                                                        // fifo 输出读出缓冲区

uint8  aRxBuffer = 0;                                                            // 接收数据变量
uint32 fifo_data_count = 0;                                                      // fifo 数据个数

fifo_struct uart_data_fifo;




/*************************************************************/
uint8 U8Test = 123;
uint16 U16Test = 1234;
uint32 U32Test = 65531;

int8 I8Test = -123;
int16 I16Test = -1234;
int32 I32Test = -65536;

float fTest = 3.1415926;

/*************************************************************/
const CMD_Data_str CMD_Data[]=/* 变量库 */
{
	/* U8变量 */
	{"U8Test",	&U8Test,	D_uint8,	Cmd_DataManage},
	
	/* U16变量 */
	{"U16Test",	&U16Test,	D_uint16,	Cmd_DataManage},
	
	/* U32变量 */
	{"U32Test",	&U32Test,	D_uint32,	Cmd_DataManage},
	
	/* I8变量 */
	{"I8Test",	&I8Test,	D_int8,	Cmd_DataManage},
	
	/* I16变量 */
	{"I16Test",	&I16Test,	D_int16,	Cmd_DataManage},
	
	/* I32变量 */
	{"I32Test",	&I32Test,	D_int32,	Cmd_DataManage},
	
	/* fTest变量 */
	{"fTest",	&fTest,	D_float,	Cmd_DataManage},

//	/* 命令结束标志 */
	
	
	
	{"EndCmd", NULL,	D_float,	IfSeachCmdData},	//最后一组数据必须是结束标志命令
};





const CMD_str CMD_Order[]=/* 命令库 */
{
	/* 基本命令 */
	{"help",	Cmd_help},				// 列出命令列表
	{"reset",	Cmd_reset},				// 重启
	
	/* 保存变量 */


	/* 测试命令 */
	{"LED_test",	Cmd_test},				// 测试函数
	
	
//	/* 命令结束标志 */
	{"EndCmd", IfSeachCmd},	//最后一组数据必须是结束标志命令
};

/*对比STR1与STR2是否一致，以ENDSTR为结尾*/
/*无结尾的命令错误未写*/


/* 获取命令库长度 */
uint16 GetSizeofCmd(CMD_str *CMD_dat)
{
	uint16 i = 0;
	char *temp1;
	
	while(1)
	{
		temp1 = strstr( CMD_dat[i].CMD, "EndCmd");
		if(temp1)	return i;
		else 		i++;
	}
}

/* 获取数据库长度 */
uint16 GetSizeofCmd_Data(CMD_Data_str *CMD_dat)
{
	uint16 i = 0;
	char *temp1;
	
	while(1)
	{
		temp1 = strstr( CMD_dat[i].CMD, "EndCmd");
		if(temp1)	return i;
		else 		i++;
	}
}

/* 字符串对比，以EndStr为结束符 */
uint8 StrComparison(const char *Str1, const char *Str2 , char EndStr)
{
  while (*Str1 != EndStr && *Str2 != EndStr)
  {
    if (*Str1 != *Str2)
    {
			 return 0;
    }
    Str1++;
    Str2++;
  }
  return 1;
}

/* 字符串转为数据 */
uint8 StrToData(const char *Str1, void *outData, D_X_enum D_X)
{
	char *endptr;
	uint32 u32buf = 0;
	int32 i32buf = 0;
	float floatbuf = 0;
	while(*Str1 != '=')Str1++;//找等号
  Str1++;
	switch(D_X)
	{
		case D_uint8:
			u32buf = strtoul(Str1, &endptr, 10);
//			if (errno == ERANGE || val > UCHAR_MAX) return -1;
			if (*endptr != '\n' && *endptr != '.') return 0;
			*(uint8 *)outData = (uint8)u32buf;
			break;
		case D_uint16:
			u32buf = strtoul(Str1, &endptr, 10);
//			if (errno == ERANGE || val > UCHAR_MAX) return -1;
			if (*endptr != '\n' && *endptr != '.') return 0;
			*(uint16 *)outData = (uint16)u32buf;
			break;
		case D_uint32:
			u32buf = strtoul(Str1, &endptr, 10);
//			if (errno == ERANGE || val > UCHAR_MAX) return -1;
			if (*endptr != '\n' && *endptr != '.') return 0;
			*(uint32 *)outData = (uint32)u32buf;
			break;
		case D_int8:
			i32buf = strtol(Str1, &endptr, 10);
//			if (errno == ERANGE || val > UCHAR_MAX) return -1;
			if (*endptr != '\n' && *endptr != '.') return 0;
			*(int8 *)outData = (int8)i32buf;
			break;
		case D_int16:
			i32buf = strtol(Str1, &endptr, 10);
//			if (errno == ERANGE || val > UCHAR_MAX) return -1;
			if (*endptr != '\n' && *endptr != '.') return 0;
			*(int16 *)outData = (int16)i32buf;
			break;
		case D_int32:	
			i32buf = strtol(Str1, &endptr, 10);
//			if (errno == ERANGE || val > UCHAR_MAX) return -1;
			if (*endptr != '\n' && *endptr != '.') return 0;
			*(int32 *)outData = (int32)i32buf;
			break;
		case D_float:
			floatbuf = strtof(Str1, &endptr);
//			if (errno == ERANGE || val > UCHAR_MAX) return -1;
			if (*endptr != '\n' && *endptr != '.') return 0;
			*(float *)outData = floatbuf;
			break;
	}
	return 1;
}


/* 打印CMD数据 */
uint8 printf_CMD_Data(CMD_Data_str *CMD_dat, uint8_t ChangeX)
{
	uint16 i=0;

	for(i=0; i<GetSizeofCmd_Data(CMD_Data); i++)					//遍历命令表
	{
		if(ChangeX == 1)
			printf("@%s=0\n",CMD_Data[i].CMD);
		else
			printf("@%s?\n",CMD_Data[i].CMD);
	}
	return 1;
}
/* 打印CMD命令 */
uint8 printf_CMD_Order(CMD_str *CMD_dat)
{
	uint16 i=0;
	for(i=0; i<GetSizeofCmd(CMD_Order); i++)					//遍历命令表
	{
		printf("#%s\n",CMD_Order[i].CMD);
	}
	return 1;
}

/* 命令解算 */
uint8 CommOrder(void)
{
	uint16 i=0;
	char temp;

//	if(StrComparison((char*)(&fifo_get_data[1]),"LED",'\n') == 1)
//		HAL_GPIO_TogglePin(LED2_PE10_GPIO_Port, LED2_PE10_Pin);	//运行指示灯
	for(i=0; i<GetSizeofCmd(CMD_Order); i++)					//遍历命令表
	{
		temp = StrComparison( (const char*)&fifo_get_data[1], CMD_Order[i].CMD, '\n');
		if( temp ) // 该指令存在
		{
			CMD_Order[i].Program();// 权限交给对应函数
			return 1;
		}
	}
	if(temp != 1)
	{
		printf("Error:指令不存在\r\n");
		printf("Cmd指令列表如下\r\n");
		printf_CMD_Order(CMD_Order);
	}
	return 1;
}

/* 数据解算 */
uint8 CommData(void)
{
	uint16 i=0;
	char temp1;
	char temp2;
	
	for(i=0; i<GetSizeofCmd_Data(CMD_Data); i++)
	{
		temp1 = StrComparison( (const char*)&fifo_get_data[1], CMD_Data[i].CMD, '=');
		temp2 = StrComparison( (const char*)&fifo_get_data[1], CMD_Data[i].CMD, '?');
		if( temp1 ) // 该指令存在
		{
			Cmd_DataManage((const char*)&fifo_get_data[1], 1 , i);
			return 1;
		}
		else if( temp2 ) // 该指令存在
		{
			Cmd_DataManage(NULL, 0 , i);
			return 1;
		}
	}
	if(temp2 != 1 && temp2!= 1)
	{
		printf("Error:变量不存在\r\n");
		printf("Cmd变量列表如下\r\n");
		printf_CMD_Data(CMD_Data, 1);
	}
	return 1;

}


/* CMD系统初始化 */
void DEBUG_UART_Init(void)
{
	fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // 初始化 fifo 挂载缓冲区
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1);
	printf("***************Cmd调试系统启动成功***************\r\n");
}

/* CMD系统串口初始化 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	fifo_write_buffer(&uart_data_fifo, &aRxBuffer, 1);                           // 将数据写入 fifo 中
	if(aRxBuffer == '\n')
	{
		fifo_data_count = fifo_used(&uart_data_fifo);                           // 查看 fifo 是否有数据
		printf("数据个数:%d\r\n",fifo_data_count);
		
		fifo_read_buffer(&uart_data_fifo, fifo_get_data, &fifo_data_count, FIFO_READ_AND_CLEAN);    // 将 fifo 中数据读出并清空 fifo 挂载的缓冲
		if(fifo_get_data[0] == '#')//命令
			CommOrder();
		else if(fifo_get_data[0] == '@')
			CommData();
		else
			Cmd_help();
	}
	HAL_UART_Receive_IT(&huart2, (uint8 *)&aRxBuffer, 1);
}



/* CMD数据处理 */
uint8 Cmd_DataManage(const char *Str1, uint8 ChangeX, uint16 CMDnum)
{
	uint8 ToDataERR;
	if(ChangeX == 0)
	{
		switch(CMD_Data[CMDnum].D_X)
		{
			case D_uint8:
				printf("re:@%s=%d\n", CMD_Data[CMDnum].CMD,*(uint8*)CMD_Data[CMDnum].data_p);
				break;
			case D_uint16:
				printf("re:@%s=%d\n", CMD_Data[CMDnum].CMD,*(uint16*)CMD_Data[CMDnum].data_p);
				break;
			case D_uint32:
				printf("re:@%s=%d\n", CMD_Data[CMDnum].CMD,*(uint32*)CMD_Data[CMDnum].data_p);
				break;
			case D_int8:
				printf("re:@%s=%d\n", CMD_Data[CMDnum].CMD,*(int8*)CMD_Data[CMDnum].data_p);
				break;
			case D_int16:
				printf("re:@%s=%d\n", CMD_Data[CMDnum].CMD,*(int16*)CMD_Data[CMDnum].data_p);
				break;
			case D_int32:	
				printf("re:@%s=%d\n", CMD_Data[CMDnum].CMD,*(int32*)CMD_Data[CMDnum].data_p);
				break;
			case D_float:
				printf("re:@%s=%f\n", CMD_Data[CMDnum].CMD,*(float*)CMD_Data[CMDnum].data_p);
				break;
		}
	}
	else if(ChangeX == 1)
	{
		switch(CMD_Data[CMDnum].D_X)
		{
			case D_uint8:
				printf("re:@%s:%d", CMD_Data[CMDnum].CMD,*(uint8*)CMD_Data[CMDnum].data_p);
				break;
			case D_uint16:
				printf("re:@%s:%d", CMD_Data[CMDnum].CMD,*(uint16*)CMD_Data[CMDnum].data_p);
				break;
			case D_uint32:
				printf("re:@%s:%d", CMD_Data[CMDnum].CMD,*(uint32*)CMD_Data[CMDnum].data_p);
				break;
			case D_int8:
				printf("re:@%s:%d", CMD_Data[CMDnum].CMD,*(int8*)CMD_Data[CMDnum].data_p);
				break;
			case D_int16:
				printf("re:@%s:%d", CMD_Data[CMDnum].CMD,*(int16*)CMD_Data[CMDnum].data_p);
				break;
			case D_int32:	
				printf("re:@%s:%d", CMD_Data[CMDnum].CMD,*(int32*)CMD_Data[CMDnum].data_p);
				break;
			case D_float:
				printf("re:@%s:%f", CMD_Data[CMDnum].CMD,*(float*)CMD_Data[CMDnum].data_p);
				break;
		}
		ToDataERR = StrToData(Str1, CMD_Data[CMDnum].data_p, CMD_Data[CMDnum].D_X);
		switch(CMD_Data[CMDnum].D_X)
		{
			case D_uint8:
				printf("->%d\n", *(uint8*)CMD_Data[CMDnum].data_p);
				break;
			case D_uint16:
				printf("->%d\n", *(uint16*)CMD_Data[CMDnum].data_p);
				break;
			case D_uint32:
				printf("->%d\n", *(uint32*)CMD_Data[CMDnum].data_p);
				break;
			case D_int8:
				printf("->%d\n", *(int8*)CMD_Data[CMDnum].data_p);
				break;
			case D_int16:
				printf("->%d\n", *(int16*)CMD_Data[CMDnum].data_p);
				break;
			case D_int32:	
				printf("->%d\n", *(int32*)CMD_Data[CMDnum].data_p);
				break;
			case D_float:
				printf("->%f\n", *(float*)CMD_Data[CMDnum].data_p);
				break;
		}
		if(ToDataERR == 0)
			printf("*********变量%s修改失败********\r\n",CMD_Data[CMDnum].CMD);
		else if(ToDataERR == 1)
			printf("*********变量%s修改成功********\r\n",CMD_Data[CMDnum].CMD);
	}
	return 1;
}
	

uint8 Cmd_help(void)
{
	printf("***************Cmd_help***************\r\n");
	printf("*********修改变量数值*********\r\n");
	printf_CMD_Data(CMD_Data, 1);
	printf("*********查询变量数值*********\r\n");
	printf_CMD_Data(CMD_Data, 0);
	printf("*********执行命令指令*********\r\n");
	printf_CMD_Order(CMD_Order);
	printf("**************************************\r\n");
	printf("#help执行成功\r\n");
	printf("**************************************\r\n");
	return 0;
}




uint8 Cmd_reset(void)
{
	printf("**************************************\r\n");
	printf("#reset执行成功\r\n");
	printf("**************************************\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	HAL_NVIC_SystemReset();          	/* 重启单片机		*/	
	return 0;
}



uint8 Cmd_test(void)
{
	HAL_GPIO_TogglePin(LED2_PE10_GPIO_Port, LED2_PE10_Pin);	//运行指示灯
	printf("**************************************\r\n");
	printf("#test执行成功\r\n");
	printf("**************************************\r\n");
	return 0;
}

uint8 IfSeachCmd(void)
{

	return 1;
}

uint8 IfSeachCmdData(const char *Str1, uint8 ChangeX, uint16 CMDnum)
{

	return 1;
}

