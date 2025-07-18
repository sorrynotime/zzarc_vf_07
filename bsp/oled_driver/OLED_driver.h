#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H

#include "main.h"

#include "stm32f4xx_hal.h"

#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdarg.h>
#include "stdio.h"

//主控型号选择
//#define SSD1306
//#define SH1106
#define SSD1309

//是否使用硬件SPI（注释该项则直接控制GPIO）
#define OLED_UI_USE_HW_SPI


//使用硬件SPI
#ifdef OLED_UI_USE_HW_SPI
#define OLED_UI_SPI_USE_DMA			//使用DMA
//#define OLED_UI_SPI_NSS_HARD_OUTPUT	//硬件CS（注释该项则使用软件控制OLED的CS pin）

#define OLED_DC_Clr()   (HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 0))  // 复位 DC (将DC引脚拉低)
#define OLED_DC_Set()   (HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 1))  // 置位 DC (将DC引脚拉高)

#define OLED_CS_Clr()  (HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, 0))  // 复位 DC (将DC引脚拉低)
#define OLED_CS_Set()  (HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, 1))  // 置位 DC (将DC引脚拉高)

#define OLED_RES_Clr()  (HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, 0))  // 复位 DC (将DC引脚拉低)
#define OLED_RES_Set()  (HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, 1))  // 置位 DC (将DC引脚拉高)

//不使用硬件SPI
#else

//使用宏定义，速度更快（寄存器方式）
#define OLED_SCL_Clr()  (GPIOB->BRR = GPIO_Pin_8)   // 复位 SCL (将 GPIOB 的 8 号引脚拉低)
#define OLED_SCL_Set()  (GPIOB->BSRR = GPIO_Pin_8)  // 置位 SCL (将 GPIOB 的 8 号引脚拉高)

#define OLED_SDA_Clr()  (GPIOB->BRR = GPIO_Pin_9)   // 复位 SDA (将 GPIOB 的 9 号引脚拉低)
#define OLED_SDA_Set()  (GPIOB->BSRR = GPIO_Pin_9)  // 置位 SDA (将 GPIOB 的 9 号引脚拉高)

#define OLED_RES_Clr()  (GPIOB->BRR = GPIO_Pin_5)   // 复位 RES (将 GPIOB 的 5 号引脚拉低)
#define OLED_RES_Set()  (GPIOB->BSRR = GPIO_Pin_5)  // 置位 RES (将 GPIOB 的 5 号引脚拉高)

#define OLED_DC_Clr()   (GPIOB->BRR = GPIO_Pin_6)   // 复位 DC (将 GPIOB 的 6 号引脚拉低)
#define OLED_DC_Set()   (GPIOB->BSRR = GPIO_Pin_6)  // 置位 DC (将 GPIOB 的 6 号引脚拉高)

#define OLED_CS_Clr()   (GPIOB->BRR = GPIO_Pin_7)   // 复位 CS (将 GPIOB 的 7 号引脚拉低)
#define OLED_CS_Set()   (GPIOB->BSRR = GPIO_Pin_7)  // 置位 CS (将 GPIOB 的 7 号引脚拉高)

#endif

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//	oled初始化函数
void OLED_Init(void);
//	oled全局刷新函数
void OLED_Update(void);
//	oled局部刷新函数
void OLED_UpdateArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height);
// 设置颜色模式
void OLED_SetColorMode(bool colormode);
// OLED 设置亮度函数
void OLED_Brightness(int16_t Brightness);





#endif







