/*
 *
 * 　　┏┓　　　┏┓+ +
 * 　┏┛┻━━━┛┻┓ + +
 * 　┃　　　　　　　┃ 　
 * 　┃　　　━　　　┃ ++ + + +
 *  ████━████ ┃+
 * 　┃　　　　　　　┃ +
 * 　┃　　　┻　　　┃
 * 　┃　　　　　　　┃ + +
 * 　┗━┓　　　┏━┛
 * 　　　┃　　　┃　　　　　　　　　　　
 * 　　　┃　　　┃ + + + +
 * 　　　┃　　　┃
 * 　　　┃　　　┃ +  神兽保佑
 * 　　　┃　　　┃    代码无bug　　
 * 　　　┃　　　┃　　+　　　　　　　　　
 * 　　　┃　 　　┗━━━┓ + +
 * 　　　┃ 　　　　　　　┣┓
 * 　　　┃ 　　　　　　　┏┛
 * 　　　┗┓┓┏━┳┓┏┛ + + + +
 * 　　　　┃┫┫　┃┫┫
 * 　　　　┗┻┛　┗┻┛+ + + +
 *
 */

#include "ad9851.h"
#include "stm32f4xx_hal.h" // 改为自己32的hal库头文件

void AD9851_Init(void)
{
	//配置串行模式 D2到D0需固定电平011, PCB 对D1,D0 已有上拉
	AD9851_Reset();
}

void AD9851_Reset(void)
{
	AD9851_WCLK_L;
	AD9851_FQUD_L;

	AD9851_RESET_L;
	AD9851_RESET_H;
	AD9851_Delay(0xffff);
	AD9851_RESET_L;

	AD9851_WCLK_L;
	AD9851_WCLK_H;
	AD9851_Delay(0xffff);
	AD9851_WCLK_L;

	AD9851_FQUD_L;
	AD9851_FQUD_H;
	AD9851_Delay(0xffff);
	AD9851_FQUD_L;
}

/**
 * @description: 设置DDS频率
 * @param {uint8_t} w0 写入 AD9851_FD 倍频开关标记即可
 * @param {double} frequence
 * @return {*}
 */
void AD9851_Write(uint8_t w0, double frequence)
{
	unsigned char i, w;
	long int y;
	double x;

#if AD9851_FD
	x = 4294967295U / 180; //适合30M晶振
#else
	x = 4294967295U / 30; //适合30M晶振
#endif
	//如果时钟频率不为30MHZ，修改该处的频率值，单位MHz  ！！！

	frequence = frequence / 1000000;
	frequence = frequence * x;
	y = frequence;

	//写w4数据
	w = (y >>= 0);
	for (i = 0; i < 8; i++)
	{
		AD9851_BIT_DATA = (w >> i) & 0x01;
		AD9851_WCLK_H;
		AD9851_WCLK_L;
	}
	//写w3数据
	w = (y >> 8);
	for (i = 0; i < 8; i++)
	{
		AD9851_BIT_DATA = (w >> i) & 0x01;
		AD9851_WCLK_H;
		AD9851_WCLK_L;
	}
	//写w2数据
	w = (y >> 16);
	for (i = 0; i < 8; i++)
	{
		AD9851_BIT_DATA = (w >> i) & 0x01;
		AD9851_WCLK_H;
		AD9851_WCLK_L;
	}
	//写w1数据
	w = (y >> 24);
	for (i = 0; i < 8; i++)
	{
		AD9851_BIT_DATA = (w >> i) & 0x01;
		AD9851_WCLK_H;
		AD9851_WCLK_L;
	}
	//写w0数据
	w = w0;
	for (i = 0; i < 8; i++)
	{
		AD9851_BIT_DATA = (w >> i) & 0x01;
		AD9851_WCLK_H;
		AD9851_WCLK_L;
	}

	AD9851_FQUD_H;
	//	AD9851_Delay(0xffff);
	AD9851_FQUD_L;
}

void AD9851_Delay(unsigned int z)
{

	for (; z > 0; z--)
	{
		;
	}
}
