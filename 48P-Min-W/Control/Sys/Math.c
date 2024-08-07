#include "Math.h"
#include "stdint.h"



/**
* 冒泡排序数组
* @param int a[] 要排序的数组
* @param int n 数组元素的个数
**/
void bubble_sort(uint32_t a[],int n)
{
    for(int i=0; i<n-1; i++){
        int isSorted = 1;
        for(int j=0; j<n-1-i; j++){
            if(a[j] > a[j+1]){
                isSorted = 0;
                uint32_t temp = a[j];
                a[j] = a[j+1];
                a[j+1]=temp;
            }  
        }
        if(isSorted) break;
    }
}

//冒泡排序取中间值算平均----此函数仅用于Drive任务中的发动机转速采集
#define FILTER_ENGINESPEED_BUFFER_SIZE		(10)
uint16_t filter_engineSpeed(uint16_t newRpm)
{
	static uint16_t buff[FILTER_ENGINESPEED_BUFFER_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	static uint8_t index = 0;
	static uint16_t rst = 0;
	
	buff[index] = newRpm;
	index++;
	if(index == FILTER_ENGINESPEED_BUFFER_SIZE)
	{
    for(int i=0; i<FILTER_ENGINESPEED_BUFFER_SIZE-1; i++){
        int isSorted = 1;
        for(int j=0; j<FILTER_ENGINESPEED_BUFFER_SIZE-1-i; j++){
            if(buff[j] > buff[j+1]){
                isSorted = 0;
                uint32_t temp = buff[j];
                buff[j] = buff[j+1];
                buff[j+1]=temp;
            }  
        }
        if(isSorted) break;
    }
		index = 0;
		rst = (buff[3]+buff[4]+buff[5]+buff[6])/4;
	}
	return rst;
}
