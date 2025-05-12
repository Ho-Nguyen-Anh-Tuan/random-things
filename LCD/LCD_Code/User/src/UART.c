#include "UART.h"

volatile char uart_rx_buf[UART_Buffer_Size];
volatile uint8_t uart_rx_index = 0;
volatile uint8_t uart_data_ready = 0;
volatile uint16_t uart_timeout_counter = 0;

// /* hàm nhận 1 byte uart */
// uint8_t UART1_ReceiveByte()
// {
//     uint8_t data = 0xFF;

//     // wait DR has data
//     while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

//     data = (uint8_t)USART_ReceiveData(USART1);

//     return data;
// }

// /* hàm truyền 1 byte uart */
// void UART1_TransmitByte(uint8_t data)
// {
//     // wait until DR resgister is empty
//     while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

//     USART_SendData(USART1, data);

//     while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
// }

// uint8_t UART1_Task()
// {
// 	uint8_t data = 0x00;
//     if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//     {
//         data = USART_ReceiveData(USART1);
//         while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
// 		USART_SendData(USART1, data);
// 		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
//     }

// 	USART_ClearITPendingBit(USART1, USART_IT_RXNE);

//     return data;
// }

void UART1_Task()
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        // Nhận 1 ký tự từ UART
        char c = USART_ReceiveData(USART1);

        // send to PC
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, c);

        // xóa chuỗi cũ
        if(uart_rx_index == 0)
        {
            for (int i = 0; i < UART_Buffer_Size; i++)
            {
                uart_rx_buf[i] = 0;
            }
            
        }

        if (uart_rx_index >= UART_Buffer_Size - 1) // giới hạn 16 kí tự - 0->15
        {
            uart_rx_index = 0; // Đặt lại index nếu buffer đầy
        }

        uart_rx_buf[uart_rx_index++] = c;   // ghi char c vào buffer

        uart_timeout_counter = 0; // nhận 1 kí tự thì reset thời gian kết thúc chuỗi

        // Xóa cờ ngắt
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}