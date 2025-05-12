#include "LCD.h"
#include "Delay.h"

void LCD_Enable()
{
    GPIO_SetBits(LCD_GPIO, EN);
    delay_ms(1);
    GPIO_ResetBits(LCD_GPIO, EN);
    delay_ms(1);
}

void LCD_Send4Bit(uint8_t data)
{
    GPIO_WriteBit(LCD_GPIO, D4, data & 0x01);
    GPIO_WriteBit(LCD_GPIO, D5, data & 0x02);
    GPIO_WriteBit(LCD_GPIO, D6, data & 0x04);
    GPIO_WriteBit(LCD_GPIO, D7, data & 0x08);
}

void LCD_SendCommand(uint8_t command)
{
    LCD_Send4Bit(command >> 4); // guiử 4 bit cao
    LCD_Enable();
    LCD_Send4Bit(command); // gửi 4 bit thấp
    LCD_Enable();
}

void LCD_Init()
{
    GPIO_ResetBits(LCD_GPIO, RS);
    GPIO_ResetBits(LCD_GPIO, RW);
    delay_ms(20);

    LCD_Send4Bit(0x03);
    LCD_Enable();
    delay_ms(10);
    LCD_Send4Bit(0x03);
    LCD_Enable();
    delay_ms(10);
    LCD_Send4Bit(0x03);
    LCD_Enable();
    delay_ms(10);
    LCD_Send4Bit(0x02);
    LCD_Enable();
    delay_ms(10);

    LCD_SendCommand(0x28);
    LCD_SendCommand(0x0C);
    LCD_SendCommand(0x06);
    LCD_SendCommand(0x01);
}

void LCD_PutChar(uint8_t data)
{
    GPIO_SetBits(LCD_GPIO, RS);
    LCD_SendCommand(data);
    GPIO_ResetBits(LCD_GPIO, RS);
}

void LCD_Puts(char *s)
{
    while (*s)
    {
        LCD_PutChar(*s);
        s++;
    }
}

void LCD_Clear()
{
    LCD_SendCommand(0x01);
    delay_ms(10);
}

void LCD_Gotoxy(uint8_t row, uint8_t col)
{
    uint8_t address;

    if (!row)
        address = (0x80 + col);
    else
        address = (0xC0 + col);
    delay_ms(1);
    LCD_SendCommand(address);
    delay_ms(1);
}

void LCD_ClearRow(uint8_t row, uint8_t col)
{
    // Đặt con trỏ tại đầu hàng cần xóa
    LCD_Gotoxy(row, col);

    // Ghi đè các ký tự trống lên toàn bộ hàng
    for (int i = col; i < 16; i++)
    {    
        LCD_PutChar(' ');
    }
    // Đặt lại con trỏ về vị trí xóa
    LCD_Gotoxy(row, col);
}
