#ifndef __UART_BSP__
#define __UART_BSP__

#include "main.h"
#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal_usart.h"
#include "system_bsp.h"
#include "usart.h"

typedef struct
{
    struct
    {
        UART_HandleTypeDef *huart; // 串口句柄
        uint8_t dma_is_en;         // 串口是否使用DMA
        uint16_t uart_rx_len_max;
        uint16_t uart_tx_len_max;

        uint8_t *tx_buffer; // 发送缓冲区
        uint8_t *rx_buffer; // 接收缓冲区

        uint8_t *received_data; // 拼接后的数据
    } config;

    struct
    {
        void (*uart_analysis_fun)(uint8_t *data, uint8_t *status, uint8_t length); // 串口数据分析函数
    } ops;

    // 过程量
    // 发送缓冲区管理
    uint16_t tx_buff_wr;
    uint16_t tx_buff_rd;

    uint8_t received_data_ok;
    uint16_t received_data_length;

} t_uart_raw;

void uart_transmit(t_uart_raw *xuart, volatile uint8_t *str, uint8_t length);
void uart_receive_data(t_uart_raw *xuart);

extern t_uart_raw a_uart1_debug;

#endif
