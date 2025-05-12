#include "setup.h"
#include "UART.h"
#include "LCD.h"


void RCC_Config()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* cấu hình chân LCD */
    GPIO_InitStruct.GPIO_Pin = RS | RW | EN | D4 | D5 | D6 | D7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(LCD_GPIO, &GPIO_InitStruct);

    /* cấu hình chân UART */
	// RX
    GPIO_InitStruct.GPIO_Pin = RX_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(UART_GPIO, &GPIO_InitStruct);

	// TX
    GPIO_InitStruct.GPIO_Pin = TX_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(UART_GPIO, &GPIO_InitStruct);
}

void TIM_Config()
{
    TIM_TimeBaseInitTypeDef TIM_InitStruct;

    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStruct.TIM_Period = 10 - 1;         // 1ms interrupt
    TIM_InitStruct.TIM_Prescaler = 7200 - 1;    // 0.1ms tick++

    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

void UART_Config()
{
    USART_InitTypeDef UART_InitStruct;

    UART_InitStruct.USART_BaudRate = 115200;
    UART_InitStruct.USART_WordLength = USART_WordLength_8b;
    UART_InitStruct.USART_StopBits = USART_StopBits_1;
    UART_InitStruct.USART_Parity = USART_Parity_No;
    UART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    UART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &UART_InitStruct);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}

void NVIC_Config()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;

    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
}