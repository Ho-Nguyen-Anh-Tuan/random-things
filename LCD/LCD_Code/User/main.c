#include "stm32f10x.h"		// Device header
#include "stm32f10x_rcc.h"	// Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h" // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_tim.h"	// Device:StdPeriph Drivers:TIM
#include "stm32f10x_usart.h" // Device:StdPeriph Drivers:USART

#include "setup.h"
#include "LCD.h"
#include "UART.h"
#include "Delay.h"

#define  SYSTICK_Config_1ms  SysTick_Config(SystemCoreClock / 1000) // 1ms

// void SysTick_Handler()
// {
//   if (uart_rx_index > 0)
//   {
//     // khi có data thì ++tick
//     uart_timeout_counter++;

//     if (uart_timeout_counter >= UART_TIMEOUT_MS)
//     {
//       uart_rx_buf[uart_rx_index] = '\0';  // timeout, kết thúc chuỗi

//       uart_data_ready = 1;  // bật cờ RDY_Data
//       // uart_timeout_counter = 0;
//     }
//   }
// }

void TIM2_IRQHandler()
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
  {
    TIM2_Counter++; // 1ms tick++

    if (uart_rx_index > 0)
    {
      // khi có data thì ++tick
      uart_timeout_counter++;

      if (uart_timeout_counter >= UART_TIMEOUT_MS)
      {
        uart_rx_buf[uart_rx_index] = '\0';  // timeout, kết thúc chuỗi

        uart_data_ready = 1;  // bật cờ RDY_Data
        // uart_timeout_counter = 0;
      }
    }

    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }
}

void USART1_IRQHandler()
{
  UART1_Task();
}

int main()
{
  // Cấu hình hệ thống
  RCC_Config();
  GPIO_Config();
  TIM_Config();
  UART_Config();
  NVIC_Config();
  // SYSTICK_Config_1ms;

  // Khởi tạo LCD
  LCD_Init(); 

  // Hiển thị chuỗi "Hello, World!!" ở dòng 1
  LCD_Clear();
  LCD_Gotoxy(0, 0); // Đặt con trỏ tại hàng 0, cột 0
  LCD_Puts("Hello World!!");

  while(1)
  {
    if (uart_data_ready)
    {
      LCD_ClearRow(1, 0);
      LCD_Puts(uart_rx_buf);

      // reset cờ và index
      uart_rx_index = 0;
			uart_data_ready = 0;
    }
  }
}