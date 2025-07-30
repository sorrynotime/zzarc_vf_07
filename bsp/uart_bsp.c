#include "uart_bsp.h"
#include "string.h"

void uart_transmit(t_uart_raw *xuart, volatile uint8_t *str, uint8_t length)
{

    if (xuart == NULL || str == NULL || length == 0)
    {
        return;
    }

    if (xuart->config.dma_is_en)
    {
        HAL_USART_Transmit_DMA(xuart->config.huart, (uint8_t *)str, length);
    }
    else
    {
        HAL_USART_Transmit(xuart->config.huart, (uint8_t *)str, length, 1000);
    }

    // uint8_t i;
    // for (i = 0; i < length; i++)
    // {
    //     xuart->tx_buffer[xuart->tx_buff_wr] = *str;
    //     xuart->tx_buff_wr++;
    //     str++;
    //     if (xuart->tx_buff_wr >= 200)
    //     {
    //         xuart->tx_buff_wr = 0;
    //     }
    // }

    // if (xuart->tx_buff_wr != xuart->tx_buff_rd)
    // {
    //     for (i = 0; i < length; i++)
    //     {
    //         usart_data_transmit(xuart->config.huart, xuart->tx_buffer[xuart->tx_buff_rd]);
    //         while (!usart_flag_get(xuart->config.huart, USART_TDC_FLAG))
    //             ;

    //         xuart->tx_buff_rd++;
    //         if (xuart->tx_buff_rd >= 200)
    //         {
    //             xuart->tx_buff_rd = 0;
    //         }
    //     }
    // }
}

void UsartReceiveData(t_uart_raw *xuart) // ¿ÕÏÐÖÐ¶Ï
{
    // xuart->received_data_length = DMA1_CHANNEL3_BUFFER_SIZE - dma_data_number_get(DMA1_CHANNEL3); //
    // memcpy(xuart->received_currently_data, xuart->rx_buffer, xuart->received_data_length);
    // xuart->received_data_ok = 1;

    if (xuart->ops.uart_analysis_fun == NULL)
        return;
    xuart->ops.uart_analysis_fun(xuart->received_currently_data, &xuart->received_data_ok, xuart->received_data_length);
}

void UartFunInit(t_uart_raw *xuart)
{
    // xuart->conflg.dma_is_en = 1;
    // xuart->config.huart = USART1;

    // xuart->ops.uart_analysis_fun = NULL;
    // xuart->tx_buff_wr = 0;
    // xuart->tx_buff_rd = 0;
    // memset(xuart->tx_buffer, 0, sizeof(xuart->tx_buffer));
    // memset(xuart->rx_buffer, 0, sizeof(xuart->rx_buffer));
    // memset(xuart->received_currently_data, 0, sizeof(xuart->received_currently_data));
    // xuart->received_data_ok = 0;
    // xuart->received_data_length = 0;
}

t_uart_raw a_uart1_debug = {
    .conflg = {
        .dma_is_en = 1,
        .huart = USART1,
    },
    .ops = {
        .uart_analysis_fun = NULL,
    },
};
