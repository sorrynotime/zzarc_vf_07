#ifndef __OLED_UI_DRIVER_H
#define __OLED_UI_DRIVER_H

#include "main.h"

/*【如果您需要移植此项目，则需要更改以下函数的实现方式。】 */
#include "stm32f4xx_hal.h"                  // Device header
#include "stm32f4xx.h"

extern t_vf07 zzarc_vf07;

//获取确认，取消，上，下按键状态的函数
#define Key_GetEnterStatus()	(zzarc_vf07.oled_enter_key)//(!BTN_stat.isDebouncedPressing)
#define Key_GetBackStatus()		(zzarc_vf07.oled_back_key)
#define Key_GetUpStatus()		(zzarc_vf07.oled_up_key)
#define Key_GetDownStatus()		(zzarc_vf07.oled_down_key)

//按键初始化函数
//void Key_Init(void);

//编码器初始化函数
void Encoder_Init(void);

// 编码器使能函数
void Encoder_Enable(void);

//编码器失能函数
void Encoder_Disable(void);

//读取编码器的增量值
int16_t Encoder_Get(void);

//延时函数
//void Delay_us(uint32_t xus);
void Delay_ms(uint32_t xms);
void Delay_s(uint32_t xs);

#endif
