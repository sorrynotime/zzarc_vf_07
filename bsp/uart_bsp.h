#ifndef __UART_BSP__
#define __UART_BSP__

#include "at32f421_wk_config.h"
#include "wk_system.h"

// typedef void *(*xUartAnalysis_t)(uint8_t *, uint8_t *, uint8_t);

// void Uart1_Transmit(volatile unsigned char *str, unsigned char length);
// void UsartReceiveData(void);

// extern uint8_t Uart1_DRx_Buff[];

// void UartAnalysisFunInit(xUartAnalysis_t pFun);

typedef __packed struct
{
    struct
    {
        USART_HandleTypeDef *huart; // 串口句柄
        uint8_t dma_is_en;          // 串口是否使用DMA
    } config;

    struct
    {
        void (*uart_analysis_fun)(uint8_t *data, uint8_t *status, uint8_t length); // 串口数据分析函数
    } ops;

    uint16_t tx_buff_wr;
    uint16_t tx_buff_rd;
    uint8_t tx_buffer[200];
    uint8_t rx_buffer[200];

    uint8_t received_currently_data[100];
    uint8_t received_data_ok;
    uint8_t received_data_length;

} t_uart_raw;

#endif
