#include "Int_key.h"

uint8_t Int_key_isPressed(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == GPIO_PIN_RESET)
    {
        vTaskDelay(15);
        if (HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == GPIO_PIN_RESET)
        {
            while (HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == GPIO_PIN_RESET)
            {
                vTaskDelay(1);
            }
            return 1;
        }
    }
    return 0;
}

Key_Type Int_key_value(void)
{
    /* 短按逻辑 */
    if (Int_key_isPressed(UP_GPIO_Port,UP_Pin) == 1)
    {
        return KEY_UP;
    }else if (Int_key_isPressed(DOWN_GPIO_Port,DOWN_Pin) == 1)
    {
        return KEY_DOWN;
    }else if (Int_key_isPressed(ALARM_EN_GPIO_Port,ALARM_EN_Pin) == 1)
    {
        return KEY_ALARM_EN;
    }else if (Int_key_isPressed(ALARM_5DAY_GPIO_Port,ALARM_5DAY_Pin) == 1)
    {
        return KEY_5DAY;
    }
    
    /* 长按逻辑 */
    if (HAL_GPIO_ReadPin(TIME_SET_GPIO_Port,TIME_SET_Pin) == GPIO_PIN_RESET)
    {
        vTaskDelay(15);
        if (HAL_GPIO_ReadPin(TIME_SET_GPIO_Port,TIME_SET_Pin) == GPIO_PIN_RESET)
        {
            TickType_t start = xTaskGetTickCount();
            while (HAL_GPIO_ReadPin(TIME_SET_GPIO_Port,TIME_SET_Pin) == GPIO_PIN_RESET)
            {
                vTaskDelay(1);
            }
            TickType_t end = xTaskGetTickCount();
            if (end - start > 3000)
            {
                return KEY_TIME_LONG;
            }else
            {
                return KEY_TIME;
            }
            
        }
    }
    
    if (HAL_GPIO_ReadPin(ALARM_SET_GPIO_Port,ALARM_SET_Pin) == GPIO_PIN_RESET)
    {
        vTaskDelay(15);
        if (HAL_GPIO_ReadPin(ALARM_SET_GPIO_Port,ALARM_SET_Pin) == GPIO_PIN_RESET)
        {
            TickType_t start = xTaskGetTickCount();
            while (HAL_GPIO_ReadPin(ALARM_SET_GPIO_Port,ALARM_SET_Pin) == GPIO_PIN_RESET)
            {
                vTaskDelay(1);
            }
            TickType_t end = xTaskGetTickCount();
            if (end - start > 3000)
            {
                return KEY_ALARM_SET_LONG;
            }else
            {
                return KEY_ALARM_SET;
            }
            
        }
    }

    return KEY_NONE;
}

OLED_Type Int_OLED_value(void)
{
    if (HAL_GPIO_ReadPin(OLED_ON_GPIO_Port,OLED_ON_Pin) == GPIO_PIN_RESET)
    {
        return OLED_ON;
    }else
    {
        return OLED_OFF;
    }
}

Light_Type Int_light_value(void)
{
    if (HAL_GPIO_ReadPin(LIGHT_GPIO_Port,LIGHT_Pin) == GPIO_PIN_RESET)
    {
        return LIGHT_ON;
    }else
    {
        return LIGHT_OFF;
    }
}

