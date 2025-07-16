#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H

#include "main.h"

#include "stm32f4xx_hal.h"

#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdarg.h>
#include "stdio.h"

//�����ͺ�ѡ��
//#define SSD1306
//#define SH1106
#define SSD1309

//�Ƿ�ʹ��Ӳ��SPI��ע�͸�����ֱ�ӿ���GPIO��
#define OLED_UI_USE_HW_SPI


//ʹ��Ӳ��SPI
#ifdef OLED_UI_USE_HW_SPI
#define OLED_UI_SPI_USE_DMA			//ʹ��DMA
//#define OLED_UI_SPI_NSS_HARD_OUTPUT	//Ӳ��CS��ע�͸�����ʹ���������OLED��CS pin��

#define OLED_DC_Clr()   (HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 0))  // ��λ DC (��DC��������)
#define OLED_DC_Set()   (HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 1))  // ��λ DC (��DC��������)

#define OLED_CS_Clr()  (HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, 0))  // ��λ DC (��DC��������)
#define OLED_CS_Set()  (HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, 1))  // ��λ DC (��DC��������)

#define OLED_RES_Clr()  (HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, 0))  // ��λ DC (��DC��������)
#define OLED_RES_Set()  (HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, 1))  // ��λ DC (��DC��������)

//��ʹ��Ӳ��SPI
#else

//ʹ�ú궨�壬�ٶȸ��죨�Ĵ�����ʽ��
#define OLED_SCL_Clr()  (GPIOB->BRR = GPIO_Pin_8)   // ��λ SCL (�� GPIOB �� 8 ����������)
#define OLED_SCL_Set()  (GPIOB->BSRR = GPIO_Pin_8)  // ��λ SCL (�� GPIOB �� 8 ����������)

#define OLED_SDA_Clr()  (GPIOB->BRR = GPIO_Pin_9)   // ��λ SDA (�� GPIOB �� 9 ����������)
#define OLED_SDA_Set()  (GPIOB->BSRR = GPIO_Pin_9)  // ��λ SDA (�� GPIOB �� 9 ����������)

#define OLED_RES_Clr()  (GPIOB->BRR = GPIO_Pin_5)   // ��λ RES (�� GPIOB �� 5 ����������)
#define OLED_RES_Set()  (GPIOB->BSRR = GPIO_Pin_5)  // ��λ RES (�� GPIOB �� 5 ����������)

#define OLED_DC_Clr()   (GPIOB->BRR = GPIO_Pin_6)   // ��λ DC (�� GPIOB �� 6 ����������)
#define OLED_DC_Set()   (GPIOB->BSRR = GPIO_Pin_6)  // ��λ DC (�� GPIOB �� 6 ����������)

#define OLED_CS_Clr()   (GPIOB->BRR = GPIO_Pin_7)   // ��λ CS (�� GPIOB �� 7 ����������)
#define OLED_CS_Set()   (GPIOB->BSRR = GPIO_Pin_7)  // ��λ CS (�� GPIOB �� 7 ����������)

#endif

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//	oled��ʼ������
void OLED_Init(void);
//	oledȫ��ˢ�º���
void OLED_Update(void);
//	oled�ֲ�ˢ�º���
void OLED_UpdateArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
// ������ɫģʽ
void OLED_SetColorMode(bool colormode);
// OLED �������Ⱥ���
void OLED_Brightness(int16_t Brightness);





#endif







