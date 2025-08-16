#include "uart_bsp.h"
#include "dma.h"
#include "string.h"
#include "usart.h"

// 串口发送
void uart_transmit(t_uart_raw *xuart, volatile uint8_t *str, uint8_t length)
{
    if (xuart == NULL || str == NULL || length == 0)
    {
        return;
    }

    if (xuart->config.dma_is_en)
    {
        HAL_UART_Transmit_DMA(xuart->config.huart, (uint8_t *)str, length);
    }
    else
    {
        HAL_UART_Transmit(xuart->config.huart, (uint8_t *)str, length, 1000);
    }
}

// 串口接收
void uart_receive_data(t_uart_raw *xuart) // 空闲中断
{
    //	通过DMA函数获取当前接收到的数据长度
    xuart->received_data_length = xuart->config.uart_rx_len_max - __HAL_DMA_GET_COUNTER(xuart->config.huart->hdmarx);

    memcpy(xuart->received_currently_data, xuart->rx_buffer, xuart->received_data_length);

    xuart->received_data_ok = 1;

    HAL_UART_Receive_DMA(xuart->config.huart, xuart->rx_buffer, 100);

    if (xuart->ops.uart_analysis_fun == NULL)
        return;

    xuart->ops.uart_analysis_fun(xuart->received_currently_data, &xuart->received_data_ok, xuart->received_data_length);
}

void uart_init(t_uart_raw *xuart)
{
    // if(xuart->config.huart->Instance == USART1){
    // 	ZG_DMA_SetConfig(
    // 		&hdma_usart1_rx,
    // 		(uint32_t)&USART1->DR,
    // 		*(uint32_t *)xuart->rx_buffer,
    // 		xuart->config.uart_rx_len_max);
    // }
}

uint8_t b_uart_log_rx_buffer[200] = {0};
uint8_t b_uart_log_tx_buffer[200] = {0};
uint8_t b_uart_log_rxdata[200] = {0};

t_uart_raw a_uart1_debug = {
    .config = {
        .dma_is_en = 1,
        .huart = &huart1,
        .uart_rx_len_max = 200,
        .uart_tx_len_max = 200,
        .rx_buffer = b_uart_log_rx_buffer,
        .tx_buffer = b_uart_log_tx_buffer,
        .received_data = b_uart_log_rxdata,
    },
    .ops = {
        .uart_analysis_fun = NULL,
    },

};
