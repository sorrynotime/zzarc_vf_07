#ifndef __OLED_UI_DRIVER_H
#define __OLED_UI_DRIVER_H

#include "main.h"

/*����������?��ֲ����Ŀ������Ҫ�������º�����ʵ�ַ�ʽ���� */
#include "stm32f4xx_hal.h"                  // Device header
#include "stm32f4xx.h"

extern t_vf07 zzarc_vf07;

//��ȡȷ�ϣ�ȡ�����ϣ��°���״̬�ĺ���
#define Key_GetEnterStatus()	(zzarc_vf07.oled_enter_key)//(!BTN_stat.isDebouncedPressing)
#define Key_GetBackStatus()		(zzarc_vf07.oled_back_key)
#define Key_GetUpStatus()		HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_7)
#define Key_GetDownStatus()		HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8)

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
