#include "Computer_interface.h"
#include "stm32f4xx_hal.h"
#include "Config.h"
Upload_Flash_t Upload_Flash;		//上位机
//------上位机------

/**
 * @brief  上位机参数数据
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
int i_Num; //发送的位数
void Upper_Computer_Updates_data()
{
//	Upload_Flash.Argument_Addr=i_Num;
//	Upload_Flash.Argument_Data=	read_parameter_table[i_Num];
//	Upload_Flash.Argument_Config=1;
	

}
