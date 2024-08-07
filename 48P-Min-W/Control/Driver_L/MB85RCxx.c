#include "MB85RCxx.h"


HAL_StatusTypeDef writeMB85RCxx(uint16_t startByte, uint8_t* willWriteBuf, uint16_t bufSize)
{
	if (startByte+bufSize > MB85RCXX_LEN) return HAL_ERROR;
	return HAL_I2C_Mem_Write(&hi2c1, 0xA0|((startByte>>8)<<1), startByte&0xFF, I2C_MEMADD_SIZE_8BIT, willWriteBuf, bufSize, 2);
}

HAL_StatusTypeDef readMB85RCxx(uint16_t startByte, uint8_t* buf, uint16_t bufSize)
{
	return HAL_I2C_Mem_Read(&hi2c1, 0xA0|((startByte>>8)<<1), startByte&0xFF, I2C_MEMADD_SIZE_8BIT, buf, bufSize, 2);
}




//示例
void GO_EEP()
{
	
	   uint16_t start_address = 0x00;
    uint8_t data_to_write[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    uint8_t data_to_read[sizeof(data_to_write)];

    HAL_Delay(100);

    if(HAL_I2C_IsDeviceReady(&hi2c1, 0xA0, 10, HAL_MAX_DELAY) != HAL_OK)
    {
        printf("MB85RC not found!\r\n");
        while(1);
    }

    // 写入数据到MB85RCxx芯片
    HAL_StatusTypeDef write_status = writeMB85RCxx(start_address, data_to_write, sizeof(data_to_write));
    if(write_status != HAL_OK)
    {
        printf("Error writing data to MB85RC: %d\r\n", write_status);
    }
    else
    {
        printf("Data written successfully!\r\n");
    }

    // 从MB85RCxx芯片读取数据
    HAL_StatusTypeDef read_status = readMB85RCxx(start_address, data_to_read, sizeof(data_to_read));
    if(read_status != HAL_OK)
    {
        printf("Error reading data from MB85RC: %d\r\n", read_status);
    }
    else
    {
        printf("Data read successfully: ");
        for(int i = 0; i < sizeof(data_to_read); i++)
        {
            printf("%02X ", data_to_read[i]);
        }
        printf("\r\n");
    }
}