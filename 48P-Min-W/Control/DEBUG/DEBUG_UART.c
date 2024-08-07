#include "DEBUG_UART.h"


/**
 * CMD����ϵͳ��λ��ʹ��˵����
 * 1.��������˵����
 * 		�ڡ������⡰�����һ�����У����б�����EndCmd֮ǰ��˳����Ҫ�����Խ��鰴��ʾ��˳���д
 * 		��EndCmd��������������ɾ������д
 *		ʾ���������£�
 * 		{"U8Test",	&U8Test,	D_uint8,	Cmd_DataManage},
 *		"U8Test"Ϊ������CMD����ϵͳ�е�ƥ��������U8Test������ʵ�����Ʋ�����ͬ��������ͬ���߼�д�����ڵ���
 * 		&U8TestΪ������ַ
 *		D_uint8Ϊ�������ͣ������޸�Ϊʵ�ʵı������ʹ˴�Ϊö�ٱ������Բο�D_X_enum�е�ö��
 * 		Cmd_DataManageΪִ�к������������޸�ʹ��Cmd_DataManage����
 * 2.��������˵����
 * 		�ڡ�����⡰�����һ�����У����б�����EndCmd֮ǰ��˳����Ҫ�����Խ��鰴��ʾ��˳���д
 * 		�������еı������鲻����ɾ��
 *		ʾ���������£�
 * 		{"size",	Cmd_Size},
 *		"size"Ϊ������CMD����ϵͳ�е�ƥ��������Cmd_Size������ʵ�����Ʋ�����ͬ��������ͬ���߼�д�����ڵ���
 * 		Cmd_SizeΪִ�к�������Ҫ���ⶨ�岢����
 * 3.ʹ��˵����
 * 		1.������COBEMX�п�����ش��ڵĴ��ڽ����ж�
 *		2.��DEBUG_UART_Init�����еĴ��ڽṹ��ָ���޸�Ϊ���贮��
 *		3.��DEBUG_UART_Init������main��������
 *		4.CMD����ϵͳ�����ɹ����ӡ�����Ϣ
 *
 *
 *
 *
 */



/* fifo��ر����������޸ģ� */
uint8 uart_get_data[64];                                                        // ���ڽ������ݻ�����
uint8 fifo_get_data[64];                                                        // fifo �������������

uint8  aRxBuffer = 0;                                                            // �������ݱ���
uint32 fifo_data_count = 0;                                                      // fifo ���ݸ���

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
const CMD_Data_str CMD_Data[]=/* ������ */
{
	/* U8���� */
	{"U8Test",	&U8Test,	D_uint8,	Cmd_DataManage},
	
	/* U16���� */
	{"U16Test",	&U16Test,	D_uint16,	Cmd_DataManage},
	
	/* U32���� */
	{"U32Test",	&U32Test,	D_uint32,	Cmd_DataManage},
	
	/* I8���� */
	{"I8Test",	&I8Test,	D_int8,	Cmd_DataManage},
	
	/* I16���� */
	{"I16Test",	&I16Test,	D_int16,	Cmd_DataManage},
	
	/* I32���� */
	{"I32Test",	&I32Test,	D_int32,	Cmd_DataManage},
	
	/* fTest���� */
	{"fTest",	&fTest,	D_float,	Cmd_DataManage},

//	/* ���������־ */
	
	
	
	{"EndCmd", NULL,	D_float,	IfSeachCmdData},	//���һ�����ݱ����ǽ�����־����
};





const CMD_str CMD_Order[]=/* ����� */
{
	/* �������� */
	{"help",	Cmd_help},				// �г������б�
	{"reset",	Cmd_reset},				// ����
	
	/* ������� */


	/* �������� */
	{"LED_test",	Cmd_test},				// ���Ժ���
	
	
//	/* ���������־ */
	{"EndCmd", IfSeachCmd},	//���һ�����ݱ����ǽ�����־����
};

/*�Ա�STR1��STR2�Ƿ�һ�£���ENDSTRΪ��β*/
/*�޽�β���������δд*/


/* ��ȡ����ⳤ�� */
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

/* ��ȡ���ݿⳤ�� */
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

/* �ַ����Աȣ���EndStrΪ������ */
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

/* �ַ���תΪ���� */
uint8 StrToData(const char *Str1, void *outData, D_X_enum D_X)
{
	char *endptr;
	uint32 u32buf = 0;
	int32 i32buf = 0;
	float floatbuf = 0;
	while(*Str1 != '=')Str1++;//�ҵȺ�
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


/* ��ӡCMD���� */
uint8 printf_CMD_Data(CMD_Data_str *CMD_dat, uint8_t ChangeX)
{
	uint16 i=0;

	for(i=0; i<GetSizeofCmd_Data(CMD_Data); i++)					//���������
	{
		if(ChangeX == 1)
			printf("@%s=0\n",CMD_Data[i].CMD);
		else
			printf("@%s?\n",CMD_Data[i].CMD);
	}
	return 1;
}
/* ��ӡCMD���� */
uint8 printf_CMD_Order(CMD_str *CMD_dat)
{
	uint16 i=0;
	for(i=0; i<GetSizeofCmd(CMD_Order); i++)					//���������
	{
		printf("#%s\n",CMD_Order[i].CMD);
	}
	return 1;
}

/* ������� */
uint8 CommOrder(void)
{
	uint16 i=0;
	char temp;

//	if(StrComparison((char*)(&fifo_get_data[1]),"LED",'\n') == 1)
//		HAL_GPIO_TogglePin(LED2_PE10_GPIO_Port, LED2_PE10_Pin);	//����ָʾ��
	for(i=0; i<GetSizeofCmd(CMD_Order); i++)					//���������
	{
		temp = StrComparison( (const char*)&fifo_get_data[1], CMD_Order[i].CMD, '\n');
		if( temp ) // ��ָ�����
		{
			CMD_Order[i].Program();// Ȩ�޽�����Ӧ����
			return 1;
		}
	}
	if(temp != 1)
	{
		printf("Error:ָ�����\r\n");
		printf("Cmdָ���б�����\r\n");
		printf_CMD_Order(CMD_Order);
	}
	return 1;
}

/* ���ݽ��� */
uint8 CommData(void)
{
	uint16 i=0;
	char temp1;
	char temp2;
	
	for(i=0; i<GetSizeofCmd_Data(CMD_Data); i++)
	{
		temp1 = StrComparison( (const char*)&fifo_get_data[1], CMD_Data[i].CMD, '=');
		temp2 = StrComparison( (const char*)&fifo_get_data[1], CMD_Data[i].CMD, '?');
		if( temp1 ) // ��ָ�����
		{
			Cmd_DataManage((const char*)&fifo_get_data[1], 1 , i);
			return 1;
		}
		else if( temp2 ) // ��ָ�����
		{
			Cmd_DataManage(NULL, 0 , i);
			return 1;
		}
	}
	if(temp2 != 1 && temp2!= 1)
	{
		printf("Error:����������\r\n");
		printf("Cmd�����б�����\r\n");
		printf_CMD_Data(CMD_Data, 1);
	}
	return 1;

}


/* CMDϵͳ��ʼ�� */
void DEBUG_UART_Init(void)
{
	fifo_init(&uart_data_fifo, FIFO_DATA_8BIT, uart_get_data, 64);              // ��ʼ�� fifo ���ػ�����
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer, 1);
	printf("***************Cmd����ϵͳ�����ɹ�***************\r\n");
}

/* CMDϵͳ���ڳ�ʼ�� */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	fifo_write_buffer(&uart_data_fifo, &aRxBuffer, 1);                           // ������д�� fifo ��
	if(aRxBuffer == '\n')
	{
		fifo_data_count = fifo_used(&uart_data_fifo);                           // �鿴 fifo �Ƿ�������
		printf("���ݸ���:%d\r\n",fifo_data_count);
		
		fifo_read_buffer(&uart_data_fifo, fifo_get_data, &fifo_data_count, FIFO_READ_AND_CLEAN);    // �� fifo �����ݶ�������� fifo ���صĻ���
		if(fifo_get_data[0] == '#')//����
			CommOrder();
		else if(fifo_get_data[0] == '@')
			CommData();
		else
			Cmd_help();
	}
	HAL_UART_Receive_IT(&huart2, (uint8 *)&aRxBuffer, 1);
}



/* CMD���ݴ��� */
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
			printf("*********����%s�޸�ʧ��********\r\n",CMD_Data[CMDnum].CMD);
		else if(ToDataERR == 1)
			printf("*********����%s�޸ĳɹ�********\r\n",CMD_Data[CMDnum].CMD);
	}
	return 1;
}
	

uint8 Cmd_help(void)
{
	printf("***************Cmd_help***************\r\n");
	printf("*********�޸ı�����ֵ*********\r\n");
	printf_CMD_Data(CMD_Data, 1);
	printf("*********��ѯ������ֵ*********\r\n");
	printf_CMD_Data(CMD_Data, 0);
	printf("*********ִ������ָ��*********\r\n");
	printf_CMD_Order(CMD_Order);
	printf("**************************************\r\n");
	printf("#helpִ�гɹ�\r\n");
	printf("**************************************\r\n");
	return 0;
}




uint8 Cmd_reset(void)
{
	printf("**************************************\r\n");
	printf("#resetִ�гɹ�\r\n");
	printf("**************************************\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	printf("\r\n");
	HAL_NVIC_SystemReset();          	/* ������Ƭ��		*/	
	return 0;
}



uint8 Cmd_test(void)
{
	HAL_GPIO_TogglePin(LED2_PE10_GPIO_Port, LED2_PE10_Pin);	//����ָʾ��
	printf("**************************************\r\n");
	printf("#testִ�гɹ�\r\n");
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

