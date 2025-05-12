#ifndef __LCD__H__
#define __LCD__H__

#include "stm32f10x_gpio.h"

#define RS GPIO_Pin_0
#define RW GPIO_Pin_1
#define EN GPIO_Pin_2

#define D4 GPIO_Pin_3
#define D5 GPIO_Pin_4
#define D6 GPIO_Pin_5
#define D7 GPIO_Pin_6

#define LCD_GPIO GPIOA

// Tạo xung Enable để giao tiếp với LCD
void LCD_Enable();

// Truyền 4bit dữ liệu xuống LCD
void LCD_Send4Bit(uint8_t data);

// Gửi 1 lệnh xuống LCD (Một lệnh thì có 8 bit dữ liệu)
void LCD_SendCommand(uint8_t command);

// Khởi tạo ban đầu cho LCD
void LCD_Init();

//  Hiển thị 1 ký tự lên LCD.
void LCD_PutChar(uint8_t data);

// Hiển thị một chuỗi lên LCD
void LCD_Puts(char *s);

// Xóa màn hình LCD
void LCD_Clear();

// hiển thị bắt đầu tại vị trí hàng row, cột col
void LCD_Gotoxy(uint8_t row, uint8_t col);

// clear từ 1 vị trí tới hết hàng 
void LCD_ClearRow(uint8_t row, uint8_t col);

#endif //!__LCD__H__
