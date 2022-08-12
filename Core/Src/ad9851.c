/*
 *
 * ������������������+ +
 * �������ߩ��������ߩ� + +
 * �������������������� ��
 * �������������������� ++ + + +
 *  ������������������ ��+
 * �������������������� +
 * �����������ߡ�������
 * �������������������� + +
 * ��������������������
 * ��������������������������������������
 * ���������������� + + + +
 * ����������������
 * ���������������� +  ���ޱ���
 * ����������������    ������bug����
 * ��������������������+������������������
 * ���������� �������������� + +
 * �������� ���������������ǩ�
 * �������� ������������������
 * �����������������ש����� + + + +
 * �����������ϩϡ����ϩ�
 * �����������ߩ������ߩ�+ + + +
 *
 */

#include "ad9851.h"
#include "stm32f4xx_hal.h" // ��Ϊ�Լ�32��hal��ͷ�ļ�

void AD9851_Init(void)
{
	//���ô���ģʽ D2��D0��̶���ƽ011, PCB ��D1,D0 ��������
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
 * @description: ����DDSƵ��
 * @param {uint8_t} w0 д�� AD9851_FD ��Ƶ���ر�Ǽ���
 * @param {double} frequence
 * @return {*}
 */
void AD9851_Write(uint8_t w0, double frequence)
{
	unsigned char i, w;
	long int y;
	double x;

#if AD9851_FD
	x = 4294967295U / 180; //�ʺ�30M����
#else
	x = 4294967295U / 30; //�ʺ�30M����
#endif
	//���ʱ��Ƶ�ʲ�Ϊ30MHZ���޸ĸô���Ƶ��ֵ����λMHz  ������

	frequence = frequence / 1000000;
	frequence = frequence * x;
	y = frequence;

	//дw4����
	w = (y >>= 0);
	for (i = 0; i < 8; i++)
	{
		AD9851_BIT_DATA = (w >> i) & 0x01;
		AD9851_WCLK_H;
		AD9851_WCLK_L;
	}
	//дw3����
	w = (y >> 8);
	for (i = 0; i < 8; i++)
	{
		AD9851_BIT_DATA = (w >> i) & 0x01;
		AD9851_WCLK_H;
		AD9851_WCLK_L;
	}
	//дw2����
	w = (y >> 16);
	for (i = 0; i < 8; i++)
	{
		AD9851_BIT_DATA = (w >> i) & 0x01;
		AD9851_WCLK_H;
		AD9851_WCLK_L;
	}
	//дw1����
	w = (y >> 24);
	for (i = 0; i < 8; i++)
	{
		AD9851_BIT_DATA = (w >> i) & 0x01;
		AD9851_WCLK_H;
		AD9851_WCLK_L;
	}
	//дw0����
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
