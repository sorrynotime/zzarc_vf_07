#ifndef __OLED_UI_DRIVER_H
#define __OLED_UI_DRIVER_H

/*���������Ҫ��ֲ����Ŀ������Ҫ�������º�����ʵ�ַ�ʽ���� */
#include "stm32f4xx_hal.h"                  // Device header
#include "stm32f4xx.h"
//#include "misc.h"

//��ȡȷ�ϣ�ȡ�����ϣ��°���״̬�ĺ���
#define Key_GetEnterStatus()	(1)//(!BTN_stat.isDebouncedPressing)
#define Key_GetBackStatus()		(1)
#define Key_GetUpStatus()		(1)
#define Key_GetDownStatus()		(1)



//��ʱ���жϳ�ʼ������
//void Timer_Init(void);

//������ʼ������
//void Key_Init(void);

//��������ʼ������
void Encoder_Init(void);

// ������ʹ�ܺ���
void Encoder_Enable(void);

//������ʧ�ܺ���
void Encoder_Disable(void);

//��ȡ������������ֵ
int16_t Encoder_Get(void);

//��ʱ����
//void Delay_us(uint32_t xus);
void Delay_ms(uint32_t xms);
void Delay_s(uint32_t xs);

#endif
