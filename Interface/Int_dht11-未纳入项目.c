#include "Int_dht11.h"

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

void Int_DHT11_Init(void)
{
    DHT11_DATA_H;
    HAL_Delay(1500);
    
}

void Int_DHT11_Value(uint8_t *temperature, uint8_t *humidity)
{
    DHT11_DATA_L;
    HAL_Delay(20);
    DHT11_DATA_H;
    int16_t countmax = 0xfff;

    while ((DHT11_DATA_READ == GPIO_PIN_SET) && countmax--)
    {
    }

    while ((DHT11_DATA_READ == GPIO_PIN_RESET) && countmax--)
    {
    }   

    while ((DHT11_DATA_READ == GPIO_PIN_SET) && countmax--)
    {
    }

    if (countmax == 0)
    {
        printf("DHT11 timeout");
        return;
    }
    
    for (uint8_t i = 0; i < 5; i++)
    {
        uint8_t tmp = 0;   
        for (uint8_t j = 0; j < 8; j++)
        {
             while ((DHT11_DATA_READ == GPIO_PIN_RESET) && countmax--)
            {
            }
            Int_Delay_us(40);
            if ((DHT11_DATA_READ == GPIO_PIN_SET) && countmax-- )
            {
                tmp |= (0x80 >> j);
                while ((DHT11_DATA_READ == GPIO_PIN_SET) && countmax--)
                {
                }
            }
            else
            {
            }
        }
        data[i] = tmp;
    }
    uint16_t sum = data[0] + data[1] + data[2] + data[3];

    if (countmax == 0)
    {
        printf("DHT11 timeout");
        return;
    }

    if ((uint8_t)sum != data[4])
    {
        printf("data wrong!");
        return;
    }

    *temperature = data[2];
    *humidity = data[0];    
}
