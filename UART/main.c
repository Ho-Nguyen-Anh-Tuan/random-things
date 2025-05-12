#include "stm32f10x.h"       // Device header
#include "stm32f10x_rcc.h"   // Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"  // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_tim.h"   // Device:StdPeriph Drivers:TIM
#include "stm32f10x_usart.h" // Device:StdPeriph Drivers:USART
#include "stm32f10x_exti.h"  // Device:StdPeriph Drivers:EXTI
#include "misc.h"

uint16_t count = 0;

#define TX_Pin GPIO_Pin_9
#define RX_Pin GPIO_Pin_10

#define UART_GPIO GPIOA

void RCC_Config()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 |
                            RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
    
    // Pin 13
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOC, &GPIO_InitStruct);
//---------------------------------------------------------- 
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
//---------------------------------------------------------

    // EXTI
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);    
}

void TIM_Config()
{
    TIM_TimeBaseInitTypeDef TIM_InitStruct;

    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_Prescaler = 7200 - 1;
    TIM_InitStruct.TIM_Period = 10 - 1;
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

void delay_ms(uint16_t time)
{
    count = 0;
    while(count < time);
    // wait
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

void EXTI_Config()
{
    EXTI_InitTypeDef EXTI_Initstruct;

    EXTI_Initstruct.EXTI_Line = EXTI_Line0;
    EXTI_Initstruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_Initstruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Initstruct.EXTI_LineCmd = ENABLE;

    EXTI_Init(&EXTI_Initstruct);
}

void NVIC_Config()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;

    // NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    // NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    // NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    // NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    // NVIC_Init(&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
}

void TIM2_IRQHandler()
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        count++;

        // clears the TIM2 interrput pending bit
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

void USART1_IRQHandler()
{
    uint8_t data = 0x00;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        data = USART_ReceiveData(USART1);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, data);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }

	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

uint8_t USART1_ReceiveByte()
{
		uint8_t data = 0xFF;

    // wait DR has data
		while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET){}

    data = (uint8_t)USART_ReceiveData(USART1);

    return data;
}

void USART1_TransmitByte(uint8_t data)
{
    // wait until DR resgister is empty
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    USART_SendData(USART1, data);

    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

// char data[] = {'t', 'u', 'a', 'n', 'd', 'z', '@'};
// char buffer[100];

int main()
{
    RCC_Config();
    GPIO_Config();
    TIM_Config();
    UART_Config();
    EXTI_Config();
    NVIC_Config();

    while(1)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
        delay_ms(1000);
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        delay_ms(1000);
    }
}
