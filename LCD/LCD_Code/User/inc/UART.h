#ifndef __UART__H__
#define __UART__H__

#include "stm32f10x_usart.h"

#define TX_Pin GPIO_Pin_9
#define RX_Pin GPIO_Pin_10

#define UART_GPIO GPIOA

#define  UART_Buffer_Size  25
#define  UART_TIMEOUT_MS  100


extern volatile char uart_rx_buf[UART_Buffer_Size];  // buffer chứa data từ uart
extern volatile uint8_t uart_rx_index;                  // index của kí tự nhận từ uart
extern volatile uint8_t uart_data_ready;                // cờ báo dữ liệu sẵn sàngsàng
extern volatile uint16_t uart_timeout_counter;          // lưu thời gian để xác định kết thúc 1 string

// uint8_t UART1_ReceiveByte();
// void UART1_TransmitByte(uint8_t data);
void UART1_Task();

#endif //!__UART__H__