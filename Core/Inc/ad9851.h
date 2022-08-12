#ifndef _AD9851_H
#define _AD9851_H

#include "stm32f4xx_hal.h" //�ĳ��Լ�32��hal��ͷ�ļ�
#include "sys.h"

#define AD9851_FD 0x01 // 6��Ƶ����

#define AD9851_CONTROL_PORT GPIOD
#define AD9851_FQUD GPIO_PIN_3 //�ĳ��Լ����ӵ�����
#define AD9851_WCLK GPIO_PIN_4 //�ĳ��Լ����ӵ�����
#define AD9851_DATA GPIO_PIN_2 //�ĳ��Լ����ӵ�����  Ӧ���ǽ� D7
#define AD9851_RST GPIO_PIN_5  //�ĳ��Լ����ӵ�����

#define AD9851_BIT_DATA PDout(2)  // �������������ݽ�

#define AD9851_WCLK_H HAL_GPIO_WritePin(AD9851_CONTROL_PORT, 1, GPIO_PIN_SET)
#define AD9851_WCLK_L HAL_GPIO_WritePin(AD9851_CONTROL_PORT, 1, GPIO_PIN_RESET)
#define AD9851_FQUD_H HAL_GPIO_WritePin(AD9851_CONTROL_PORT, 1, GPIO_PIN_SET)
#define AD9851_FQUD_L HAL_GPIO_WritePin(AD9851_CONTROL_PORT, 1, GPIO_PIN_RESET)
#define AD9851_DATA_H HAL_GPIO_WritePin(AD9851_CONTROL_PORT, 1, GPIO_PIN_SET)
#define AD9851_DATA_L HAL_GPIO_WritePin(AD9851_CONTROL_PORT, 1, GPIO_PIN_RESET)
#define AD9851_RESET_H HAL_GPIO_WritePin(AD9851_CONTROL_PORT, 1, GPIO_PIN_SET)
#define AD9851_RESET_L HAL_GPIO_WritePin(AD9851_CONTROL_PORT, 1, GPIO_PIN_RESET)

void AD9851_Init(void);
void AD9851_Reset(void);
void AD9851_Delay(unsigned int z);
void AD9851_Write(unsigned char w0, double frequence);

#endif
