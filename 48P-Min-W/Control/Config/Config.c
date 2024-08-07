#include "Config.h"
#include "stm32f4xx_hal.h"


//Ĭ������
const int Default_parameter_table[MEAU_NUM] =
{     
	 128,      		// 0���룬�Զ����֣�0~255
	 SOFTWARE_REV,  // 1����汾����1��ʼ
	 18,        	// 2�ͺţ���0��ʼ
	 0,     	// 3
	 0,      	// 4
	 0,      	// 5
	 0,        	// 6
	 0,        	// 7
	 0,        	// 8
	 0,     	// 9
	 0,     	// 10
	 0,        	// 11
	 0,        	// 12
	 0,        	// 13
	 0,        	// 14
	 0,        	// 15
	 0,        	// 16
	 0,        	// 17
	 0,        	// 18
	 0,        // 19
	 0,        // 20
	 0,        // 21
	 0,        // 22
	 0,        // 23
	 0,        // 24
	 0,        // 25
	 0,        // 26
	 0,        // 27
	 0,        // 28
	 0,        // 29
	 0,        // 30
	 0,        // 31
	 0,        // 32
	 0,        // 33
	 0,        // 34
	 0,        // 35
	 0,        // 36
	 0,        // 37
	 0,        // 38
	 0,        // 39
	 0,        // 40
	 0,        // 41
	 0,        // 42
	 0,        // 43
	 0,        // 44
	 0,        // 45
	 0,        // 46
	 0,        // 47
	 0,        // 48
	 0,        // 49
	 0,        // 50
	 0,        // 51
	 0,        // 52
	 0,        // 53
	 0,        // 54
	 0,        // 55
	 0,        // 56
	 0,        // 57
	 0,        // 58
	 0,        // 59
	 0,        // 60
	 0,        // 61
	 0,        // 62
	 0,        // 63
	 0,        // 64
	 0,        // 65
	 0,        // 66
	 0,        // 67
	 0,        // 68
	 0,        // 69
	 0,        // 70
	 0,        // 71
	 0,        // 72
	 0,        // 73
	 0,        // 74
	 0,        // 75
	 0,        // 76
	 0,        // 77
	 0,        // 78
	 0         // 79

};


//ʵʱ����
//const

int read_parameter_table[MEAU_NUM]; 	// �������ȡ���ݵ�����
void read_and_print_parameters_SW(void);
void modify_array_element(uint32_t index, int value);
void Default_Parameter_array_element();	// Ĭ�ϲ�������Ԫ��д������
void read_from_flash_to_array(void);// ���ú����������ȡ���ݵ�����	


void Car_Soft_Parameter_config()
{
	
	printf("Hercules System Starts����\r\n");	//ϵͳ����
	
	//���ݸ��°�������
	read_from_flash_to_array();// ���ú����������ȡ���ݵ�����
	
	if(read_parameter_table[Table_Password] != 128)
	{
		//д�����,���¶���дһ��
		printf("д���������д�����\r\n");

		read_from_flash_to_array();// ���ú����������ȡ���ݵ�����
	}
	
	
	
}
/**
 * @brief  �������ȡ���ݵ�����
 * 
 * �ú�����ָ����������ʼ��ַ��ȡ���ݣ�������洢��ȫ������ `read_parameter_table` �С�
 * �����ȡ���İ汾��С�ڵ�ǰ����汾�ţ���������ݸ��²�������Ƭ����
 * 
 * @author ŵ־��
 * @param  ��
 * @since  v1.0
 * @return NULL
 * @date   2024/07/30
 * @usage
 *      read_from_flash_to_array(); // ���ú����������ȡ���ݵ�����
 * @notice
 *      ע��! ����汾��С�ڵ�ǰ����汾�ţ��������Flash���ݸ��²�������Ƭ����
 */
void read_from_flash_to_array(void) {
	
	//���±�������
    volatile uint32_t *flash_ptr = (volatile uint32_t *)FLASH_START_ADDR;
    for (uint32_t i = 0; i < MEAU_NUM; i++) {
        read_parameter_table[i] = *flash_ptr++;
    }
	
	//У��汾(Flash�洢�汾��<����汾�� ���� ���ÿ�����ģʽ ���� Flash����У����ȷ)
	if( (read_parameter_table[Table_SoftwareVersion] < SOFTWARE_REV  || DEVELOPER_MODEL ==1) )		
	{
		HAL_Delay(100);
		printf("\n�°汾!! Old:%d New:%d �����С��� ����ģʽ:%s\n",read_parameter_table[Table_SoftwareVersion],SOFTWARE_REV,(DEVELOPER_MODEL?"����":"�ر�"));
		printf("Ը������һ�ɣ�ϵͳ������ʯ����Ŀ�Դ�ɡ�\r\n");
		
		
		//���ݸ���
		Default_Parameter_array_element();	//����ͬ������
		

		//���±�������
		volatile uint32_t *flash_ptr = (volatile uint32_t *)FLASH_START_ADDR;
		for (uint32_t i = 0; i < MEAU_NUM; i++) {
			read_parameter_table[i] = *flash_ptr++;
		}
	
		if(DEVELOPER_MODEL !=1)
		{
			HAL_NVIC_SystemReset();          	/* ������Ƭ��		*/	
		}
		
	}
}


/**
 * @brief  Ĭ�ϲ�������Ԫ��д������
 * 
 * �ú����������棬����ָ������������Ĭ�ϲ��������Ԫ��д�����档
 * 
 * @author ŵ־��
 * @param  ��
 * @since  v1.0
 * @return NULL
 * @date   2024/07/30
 * @usage
 *      Default_Parameter_array_element(); // ���ú�����Ĭ�ϲ�������Ԫ��д������
 * @notice
 *      ע��! �ڵ��ô˺���ǰ����ȷ�������ѽ��������Ҳ��������ɹ���
 */
void Default_Parameter_array_element() {
	
    HAL_FLASH_Unlock(); // ����FLASH

    // ����Ҫд�������
    FLASH_EraseInitTypeDef eraseInitStruct;
    eraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInitStruct.Sector = FLASH_SECTOR_11;
    eraseInitStruct.NbSectors = 1;
    eraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    uint32_t sectorError = 0;
    HAL_FLASHEx_Erase(&eraseInitStruct, &sectorError);

    // д������
    for (uint32_t i = 0; i < MEAU_NUM; i++) {
			
      HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_START_ADDR + i * sizeof(int), (uint64_t)Default_parameter_table[i]);
      
    }

    HAL_FLASH_Lock(); // ����FLASH
}

void Flash_Test()
{

	
	// ���ö�ȡ����ӡ�����ĺ���
	//read_and_print_parameters_SW();
	
}

/**
 * @brief  ��ȡ����ӡ�������
 * 
 * �ú����������ж�ȡ�������������ӡ������̨��
 * 
 * @author  ŵ־��
 * @param  ��
 * @return NULL
 * @since  v1.0
 * @date   2024/07/30
 * @usage
 *      read_and_print_parameters_SW(); // ���ú�����ȡ����ӡ�������
 * @notice
 *      ע��! ��ȷ�������ַ�������С��ȷ����
 */
void read_and_print_parameters_SW()
{
    //��ȡFlash�еĲ�����
    const int *flash_parameters = (int *)0x080E0000;

    // ��ӡ������
    printf("Default Parameter Table:\n");
    for (int i = 0; i < MEAU_NUM; i++)
    {
        printf("Parameter %d: %d\n", i, read_parameter_table[i]);
    }
}

/**
 * @brief  ����Flash�Ĳ�������
 * 
 * �ú����������棬����ָ������������ `read_parameter_table` ������ָ��������Ԫ��ֵ�޸�Ϊ��ֵ��
 * 
 * @author  ŵ־��
 * @param  index Ҫ�޸ĵ�����Ԫ�ص�����
 * @param  value Ҫ���õ���ֵ
 * @return NULL
 * @since  v1.0
 * @date   2024/07/30
 * @usage
 *      modify_array_element(0, 100); // �������һ��Ԫ�ص�ֵ�޸�Ϊ100
 * @notice
 *      ע��! �ڵ��ô˺���ǰ����ȷ�������ѽ��������Ҳ��������ɹ���
 */
void modify_array_element(uint32_t index, int value) {
	
    HAL_FLASH_Unlock(); // ����FLASH

    // ����Ҫд�������
    FLASH_EraseInitTypeDef eraseInitStruct;
    eraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInitStruct.Sector = FLASH_SECTOR_11;
    eraseInitStruct.NbSectors = 1;
    eraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    uint32_t sectorError = 0;
    HAL_FLASHEx_Erase(&eraseInitStruct, &sectorError);

    // д������
    for (uint32_t i = 0; i < MEAU_NUM; i++) {
        if (i == index) {
            HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_START_ADDR + i * sizeof(int), (uint64_t)value);
        } else {
           HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_START_ADDR + i * sizeof(int), (uint64_t)read_parameter_table[i]);
        }
    }

    HAL_FLASH_Lock(); // ����FLASH
}

