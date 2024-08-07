#include "Config.h"
#include "stm32f4xx_hal.h"


//默认配置
const int Default_parameter_table[MEAU_NUM] =
{     
	 128,      		// 0密码，自定数字，0~255
	 SOFTWARE_REV,  // 1软件版本，从1开始
	 18,        	// 2型号，从0开始
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


//实时配置
//const

int read_parameter_table[MEAU_NUM]; 	// 从闪存读取数据到数组
void read_and_print_parameters_SW(void);
void modify_array_element(uint32_t index, int value);
void Default_Parameter_array_element();	// 默认参数数组元素写入闪存
void read_from_flash_to_array(void);// 调用函数从闪存读取数据到数组	


void Car_Soft_Parameter_config()
{
	
	printf("Hercules System Starts……\r\n");	//系统启动
	
	//数据更新搬运数组
	read_from_flash_to_array();// 调用函数从闪存读取数据到数组
	
	if(read_parameter_table[Table_Password] != 128)
	{
		//写入错误,重新二次写一下
		printf("写入错误，重新写入参数\r\n");

		read_from_flash_to_array();// 调用函数从闪存读取数据到数组
	}
	
	
	
}
/**
 * @brief  从闪存读取数据到数组
 * 
 * 该函数从指定的闪存起始地址读取数据，并将其存储到全局数组 `read_parameter_table` 中。
 * 如果读取到的版本号小于当前软件版本号，则进行数据更新并重启单片机。
 * 
 * @author 诺志辉
 * @param  无
 * @since  v1.0
 * @return NULL
 * @date   2024/07/30
 * @usage
 *      read_from_flash_to_array(); // 调用函数从闪存读取数据到数组
 * @notice
 *      注意! 如果版本号小于当前软件版本号，将会进行Flash数据更新并重启单片机。
 */
void read_from_flash_to_array(void) {
	
	//更新本地数据
    volatile uint32_t *flash_ptr = (volatile uint32_t *)FLASH_START_ADDR;
    for (uint32_t i = 0; i < MEAU_NUM; i++) {
        read_parameter_table[i] = *flash_ptr++;
    }
	
	//校验版本(Flash存储版本号<程序版本号 或者 启用开发者模式 并且 Flash密码校验正确)
	if( (read_parameter_table[Table_SoftwareVersion] < SOFTWARE_REV  || DEVELOPER_MODEL ==1) )		
	{
		HAL_Delay(100);
		printf("\n新版本!! Old:%d New:%d 更新中…… 调试模式:%s\n",read_parameter_table[Table_SoftwareVersion],SOFTWARE_REV,(DEVELOPER_MODEL?"开启":"关闭"));
		printf("愿君代码一成，系统稳如磐石，项目皆大成。\r\n");
		
		
		//数据更新
		Default_Parameter_array_element();	//数据同步更新
		

		//更新本地数据
		volatile uint32_t *flash_ptr = (volatile uint32_t *)FLASH_START_ADDR;
		for (uint32_t i = 0; i < MEAU_NUM; i++) {
			read_parameter_table[i] = *flash_ptr++;
		}
	
		if(DEVELOPER_MODEL !=1)
		{
			HAL_NVIC_SystemReset();          	/* 重启单片机		*/	
		}
		
	}
}


/**
 * @brief  默认参数数组元素写入闪存
 * 
 * 该函数解锁闪存，擦除指定扇区，并将默认参数数组的元素写入闪存。
 * 
 * @author 诺志辉
 * @param  无
 * @since  v1.0
 * @return NULL
 * @date   2024/07/30
 * @usage
 *      Default_Parameter_array_element(); // 调用函数将默认参数数组元素写入闪存
 * @notice
 *      注意! 在调用此函数前，请确保闪存已解锁，并且擦除操作成功。
 */
void Default_Parameter_array_element() {
	
    HAL_FLASH_Unlock(); // 解锁FLASH

    // 擦除要写入的扇区
    FLASH_EraseInitTypeDef eraseInitStruct;
    eraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInitStruct.Sector = FLASH_SECTOR_11;
    eraseInitStruct.NbSectors = 1;
    eraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    uint32_t sectorError = 0;
    HAL_FLASHEx_Erase(&eraseInitStruct, &sectorError);

    // 写入数据
    for (uint32_t i = 0; i < MEAU_NUM; i++) {
			
      HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_START_ADDR + i * sizeof(int), (uint64_t)Default_parameter_table[i]);
      
    }

    HAL_FLASH_Lock(); // 锁定FLASH
}

void Flash_Test()
{

	
	// 调用读取并打印参数的函数
	//read_and_print_parameters_SW();
	
}

/**
 * @brief  读取并打印软件参数
 * 
 * 该函数从闪存中读取参数表，并将其打印到控制台。
 * 
 * @author  诺志辉
 * @param  无
 * @return NULL
 * @since  v1.0
 * @date   2024/07/30
 * @usage
 *      read_and_print_parameters_SW(); // 调用函数读取并打印软件参数
 * @notice
 *      注意! 请确保闪存地址和数组大小正确无误。
 */
void read_and_print_parameters_SW()
{
    //读取Flash中的参数表
    const int *flash_parameters = (int *)0x080E0000;

    // 打印参数表
    printf("Default Parameter Table:\n");
    for (int i = 0; i < MEAU_NUM; i++)
    {
        printf("Parameter %d: %d\n", i, read_parameter_table[i]);
    }
}

/**
 * @brief  更新Flash的参数数据
 * 
 * 该函数解锁闪存，擦除指定扇区，并将 `read_parameter_table` 数组中指定索引的元素值修改为新值。
 * 
 * @author  诺志辉
 * @param  index 要修改的数组元素的索引
 * @param  value 要设置的新值
 * @return NULL
 * @since  v1.0
 * @date   2024/07/30
 * @usage
 *      modify_array_element(0, 100); // 将数组第一个元素的值修改为100
 * @notice
 *      注意! 在调用此函数前，请确保闪存已解锁，并且擦除操作成功。
 */
void modify_array_element(uint32_t index, int value) {
	
    HAL_FLASH_Unlock(); // 解锁FLASH

    // 擦除要写入的扇区
    FLASH_EraseInitTypeDef eraseInitStruct;
    eraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
    eraseInitStruct.Sector = FLASH_SECTOR_11;
    eraseInitStruct.NbSectors = 1;
    eraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    uint32_t sectorError = 0;
    HAL_FLASHEx_Erase(&eraseInitStruct, &sectorError);

    // 写入数据
    for (uint32_t i = 0; i < MEAU_NUM; i++) {
        if (i == index) {
            HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_START_ADDR + i * sizeof(int), (uint64_t)value);
        } else {
           HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_START_ADDR + i * sizeof(int), (uint64_t)read_parameter_table[i]);
        }
    }

    HAL_FLASH_Lock(); // 锁定FLASH
}

