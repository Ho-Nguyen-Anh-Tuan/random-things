#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Device:StdPeriph Drivers:GPIO
#include "stm32f10x_tim.h"              // Device:StdPeriph Drivers:TIM

#define Led7Seg_A	GPIO_Pin_0
#define Led7Seg_B	GPIO_Pin_1
#define Led7Seg_C	GPIO_Pin_2
#define Led7Seg_D	GPIO_Pin_3
#define Led7Seg_E	GPIO_Pin_4
#define Led7Seg_F	GPIO_Pin_5
#define Led7Seg_G	GPIO_Pin_6
#define Led7Seg_H	GPIO_Pin_7
#define Led7Seg_K	GPIO_Pin_8
#define Led7Seg_M	GPIO_Pin_9
#define Led7Seg_N	GPIO_Pin_10
#define Led7Seg_P	GPIO_Pin_11
#define Led7Seg_R	GPIO_Pin_12
#define Led7Seg_S	GPIO_Pin_13
#define Led7Seg_T	GPIO_Pin_14
#define Led7Seg_U	GPIO_Pin_15



#define LED1	GPIO_Pin_0
#define LED2	GPIO_Pin_1
#define LED3	GPIO_Pin_2
#define LED4	GPIO_Pin_3
#define LED5	GPIO_Pin_4
#define LED6	GPIO_Pin_5

/* 7 seg RCC */
#define RCC_Led7Seg_Signal	RCC_APB2Periph_GPIOA
#define RCC_Led7Seg_Power		RCC_APB2Periph_GPIOB

/* 7 seg GPIO */
#define Led7Seg_Signal_GPIO	GPIOA
#define Led7Seg_Power_GPIO	GPIOB


void RCC_Config(){
	RCC_APB2PeriphClockCmd(RCC_Led7Seg_Signal | RCC_Led7Seg_Power, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config(){
	GPIO_InitTypeDef GPIO_Initstruct;
	
	/* Initalize GPIO A */ 
	GPIO_Initstruct.GPIO_Pin = Led7Seg_A | Led7Seg_B | Led7Seg_C | Led7Seg_D 
														| Led7Seg_E | Led7Seg_F | Led7Seg_G | Led7Seg_H
														|	Led7Seg_K | Led7Seg_M | Led7Seg_N | Led7Seg_P 
														|	Led7Seg_R | Led7Seg_S | Led7Seg_T | Led7Seg_U;
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(Led7Seg_Signal_GPIO, &GPIO_Initstruct);
	
	/* Initalize GPIO B */
	GPIO_Initstruct.GPIO_Pin = LED1 | LED2 | LED3 | LED4 | LED5 | LED6;
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(Led7Seg_Power_GPIO, &GPIO_Initstruct);
}

void TIM_Config(){
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	
	// Goal: count up 1 every 0.1ms
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // xung clock mcu : 1 = 72MHz
	TIM_InitStruct.TIM_Prescaler = 7200 - 1;	// 0,1ms count++
	TIM_InitStruct.TIM_Period = 0xFFFF;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);
	TIM_Cmd(TIM2, ENABLE);
}	

void delay_ms(uint32_t TimeDelay){
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < TimeDelay * 10);
}


/* mang chu cai hien thi */
uint16_t display_chars[] = {
	0xDDFC,	// T
	0xFF03,	// U
	0x7730,	// A
	0xEE33,	// N
	0xDDC0, // D
	0xBBCC	// Z
};


int main(){
	RCC_Config();
	GPIO_Config();
	TIM_Config();
	
	/* Tat het led luc dau */
	GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);	
	GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);	
	GPIO_ResetBits(Led7Seg_Power_GPIO, LED3);	
	GPIO_ResetBits(Led7Seg_Power_GPIO, LED4);	
	GPIO_ResetBits(Led7Seg_Power_GPIO, LED5);	
	GPIO_ResetBits(Led7Seg_Power_GPIO, LED6);	
	
	while(1){
		
		// hien thi chu T
		GPIO_Write(Led7Seg_Signal_GPIO, display_chars[0]);
		GPIO_SetBits(Led7Seg_Power_GPIO, LED1);
		delay_ms(5);
		GPIO_ResetBits(Led7Seg_Power_GPIO, LED1);
		
		// hien thi chu U
		GPIO_Write(Led7Seg_Signal_GPIO, display_chars[1]);
		GPIO_SetBits(Led7Seg_Power_GPIO, LED2);
		delay_ms(5);
		GPIO_ResetBits(Led7Seg_Power_GPIO, LED2);
		
		// hien thi chu A
		GPIO_Write(Led7Seg_Signal_GPIO, display_chars[2]);
		GPIO_SetBits(Led7Seg_Power_GPIO, LED3);
		delay_ms(5);
		GPIO_ResetBits(Led7Seg_Power_GPIO, LED3);
		
		// hien thi chu N
		GPIO_Write(Led7Seg_Signal_GPIO, display_chars[3]);
		GPIO_SetBits(Led7Seg_Power_GPIO, LED4);
		delay_ms(5);
		GPIO_ResetBits(Led7Seg_Power_GPIO, LED4);
		
		// hien thi chu D
		GPIO_Write(Led7Seg_Signal_GPIO, display_chars[4]);
		GPIO_SetBits(Led7Seg_Power_GPIO, LED5);
		delay_ms(5);
		GPIO_ResetBits(Led7Seg_Power_GPIO, LED5);
		
		// hien thi chu Z
		GPIO_Write(Led7Seg_Signal_GPIO, display_chars[5]);
		GPIO_SetBits(Led7Seg_Power_GPIO, LED6);
		delay_ms(5);
		GPIO_ResetBits(Led7Seg_Power_GPIO, LED6);
	}
}