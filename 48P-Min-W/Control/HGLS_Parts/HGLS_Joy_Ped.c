#include "HGLS_Joy_Ped.h"

//用于存放从模块发来的最新CAN报文数据
hglsJoy_t hglsJoy;//来自手柄0x18fc0080
hglsJoy2_t hglsJoy2;//来自手柄0x18fc0081

hglsJoyXYZ_t hglsJoyXYZ;



/********************************************************
 * @brief    解析手柄CAN 高低位
 *
 * @param    Analysis_hglsJoy()； 	
 
 * @return   无
 *
 * @note     解析手柄CAN 高低位
 *
 * @see      Analysis_hglsJoy();
 *
 * @date     2023/9/12 于世壮 星期二
**********************************************************/
void HGLS_JOY_1()
{
	//0-1000-2000
	if (hglsJoy.updown1H > 0x04)
	{
		hglsJoy.updown1H = (0xffff - (hglsJoy.updown1H << 8 | hglsJoy.updown1L) + 1001) >> 8;
		hglsJoy.updown1L = (0xffff - (hglsJoy.updown1H << 8 | hglsJoy.updown1L) + 1001) & 0xff;
		hglsJoyXYZ.updown1 = (hglsJoy.updown1H << 8) | hglsJoy.updown1L;
	}
	else
	{
		hglsJoy.updown1H = (0x03e8 - (hglsJoy.updown1H << 8 | hglsJoy.updown1L)) >> 8;
		hglsJoy.updown1L = (0x03e8 - (hglsJoy.updown1H << 8 | hglsJoy.updown1L)) & 0xff;
		hglsJoyXYZ.updown1 = (hglsJoy.updown1H << 8) | hglsJoy.updown1L;
	}

	if (hglsJoy.updown2H > 0x04)
	{
		hglsJoy.updown2H = (0xffff - (hglsJoy.updown2H << 8 | hglsJoy.updown2L) + 1001) >> 8;
		hglsJoy.updown2L = (0xffff - (hglsJoy.updown2H << 8 | hglsJoy.updown2L) + 1001) & 0xff;
		hglsJoyXYZ.updown2 = (hglsJoy.updown2H << 8) | hglsJoy.updown2L;
	}
	else
	{
		hglsJoy.updown2H = (0x03e8 - (hglsJoy.updown2H << 8 | hglsJoy.updown2L)) >> 8;
		hglsJoy.updown2L = (0x03e8 - (hglsJoy.updown2H << 8 | hglsJoy.updown2L)) & 0xff;
		hglsJoyXYZ.updown2 = (hglsJoy.updown2H << 8) | hglsJoy.updown2L;
	}

	if (hglsJoy.updown3H > 0x04)
	{
		hglsJoy.updown3H = (0xffff - (hglsJoy.updown3H << 8 | hglsJoy.updown3L) + 1001) >> 8;
		hglsJoy.updown3L = (0xffff - (hglsJoy.updown3H << 8 | hglsJoy.updown3L) + 1001) & 0xff;
		hglsJoyXYZ.updown3 = (hglsJoy.updown3H << 8) | hglsJoy.updown3L;
	}
	else
	{
		hglsJoy.updown3H = (0x03e8 - (hglsJoy.updown3H << 8 | hglsJoy.updown3L)) >> 8;
		hglsJoy.updown3L = (0x03e8 - (hglsJoy.updown3H << 8 | hglsJoy.updown3L)) & 0xff;
		hglsJoyXYZ.updown3 = (hglsJoy.updown3H << 8) | hglsJoy.updown3L;
	}
}
void HGLS_JOY_2()
{
	if (hglsJoy2.XaxisH > 0x04)
	{
		hglsJoy2.XaxisH = (0xffff - (hglsJoy2.XaxisH << 8 | hglsJoy2.XaxisL) + 1001) >> 8;
		hglsJoy2.XaxisL = (0xffff - (hglsJoy2.XaxisH << 8 | hglsJoy2.XaxisL) + 1001) & 0xff;
		hglsJoyXYZ.Xaxis = (hglsJoy2.XaxisH << 8) | hglsJoy2.XaxisL;
	}
	else
	{
		hglsJoy2.XaxisH = (0x03e8 - (hglsJoy2.XaxisH << 8 | hglsJoy2.XaxisL)) >> 8;
		hglsJoy2.XaxisL = (0x03e8 - (hglsJoy2.XaxisH << 8 | hglsJoy2.XaxisL)) & 0xff;
		hglsJoyXYZ.Xaxis = (hglsJoy2.XaxisH << 8) | hglsJoy2.XaxisL;
	}

	if (hglsJoy2.YaxisH > 0x04|hglsJoy2.YaxisH==0x00)
	{
		hglsJoy2.YaxisH = (0xffff - (hglsJoy2.YaxisH << 8 | hglsJoy2.YaxisL) + 1001) >> 8;
		hglsJoy2.YaxisL = (0xffff - (hglsJoy2.YaxisH << 8 | hglsJoy2.YaxisL) + 1001) & 0xff;
		hglsJoyXYZ.Yaxis = 2000-((hglsJoy2.YaxisH << 8) | hglsJoy2.YaxisL);
	}
	else
	{
		hglsJoy2.YaxisH = (0x03e8 - (hglsJoy2.YaxisH << 8 | hglsJoy2.YaxisL)) >> 8;
		hglsJoy2.YaxisL = (0x03e8 - (hglsJoy2.YaxisH << 8 | hglsJoy2.YaxisL)) & 0xff;
		hglsJoyXYZ.Yaxis = 2000-((hglsJoy2.YaxisH << 8) | hglsJoy2.YaxisL);
	}
}
/********************************************************
 * @brief    手柄CAN逻辑控制
 *
 * @param    Analysis_hglsJoy()； 	
 
 * @return   无
 *
 * @note     解析手柄CAN 高低位
 *
 * @see      Analysis_hglsJoy();
 *
 * @date     2023/9/12 于世壮 星期二
**********************************************************/
void Handle_Logic_Ctrl()
{
	
	
	
}