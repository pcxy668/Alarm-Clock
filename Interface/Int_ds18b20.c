#include "Int_DS18B20.h"

uint8_t data[5];

/**
 * @brief 7系数延迟3s之后的误差大概在0.3s左右
 *        8系数延迟3s之后的误差大概在0.006s左右
 * @param us
 */
void Int_Delay_us(uint32_t us)
{
    uint32_t count = us * 8;
    // 8次 1us  =>  一次是125ns   机械周期是72MHz  一次是13ns
    while (count--)
    {
        __NOP();
    }
}

void Int_DS18B20_Init(void)
{
    DS18B20_DATA_L;
    Int_Delay_us(480);
    DS18B20_DATA_H;
    Int_Delay_us(480);
}

void Int_DS18B20_WriteByte(uint8_t byte)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        DS18B20_DATA_L;
        Int_Delay_us(5);
        if (byte & 0x01)
        {
            DS18B20_DATA_H;
        }
        else
        {
            DS18B20_DATA_L;
        }
        byte >>= 1;
        Int_Delay_us(60);
        DS18B20_DATA_H;
    }
}

uint8_t Int_DS18B20_ReadByte(void)
{
    uint8_t byte = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        DS18B20_DATA_L;
        Int_Delay_us(2);
        DS18B20_DATA_H;
        Int_Delay_us(8);
        byte >>= 1;
        if (DS18B20_DATA_READ == GPIO_PIN_SET)
        {
            byte |= 0x80;
        }
        Int_Delay_us(50);
    }
    return byte;
}

void Int_DS18B20_Value(char *temperature)
{
    uint8_t lsb=0,msb=0;
    //初始化
    Int_DS18B20_Init();
    //忽略ROM指令
    Int_DS18B20_WriteByte(0xcc);
    //温度转换
    Int_DS18B20_WriteByte(0x44);

    //初始化
    Int_DS18B20_Init();
    //忽略ROM指令
    Int_DS18B20_WriteByte(0xcc);
    //温度转换
    Int_DS18B20_WriteByte(0xbe);
    lsb=Int_DS18B20_ReadByte();
    msb=Int_DS18B20_ReadByte();
    *temperature=(lsb>>4)|(msb<<4);
}
