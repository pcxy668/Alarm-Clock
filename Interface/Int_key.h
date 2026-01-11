#ifndef __INT_KEY_H__
#define __INT_KEY_H__

#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"

typedef enum
{
    KEY_NONE = 0,
    KEY_TIME,
    KEY_TIME_LONG,
    KEY_UP,
    KEY_DOWN,
    KEY_ALARM_SET,
    KEY_ALARM_SET_LONG,
    KEY_ALARM_EN,
    KEY_5DAY
} Key_Type;

typedef enum
{
    OLED_ON = 0,
    OLED_OFF
} OLED_Type;

typedef enum
{
    LIGHT_ON = 0,
    LIGHT_OFF
} Light_Type;

/* 检测是否有轻触开关被短按 */
uint8_t Int_key_isPressed(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/* 检测轻触开关值 */
Key_Type Int_key_value(void);

/* 检测OLED拨动开关值 */
OLED_Type Int_OLED_value(void);

/* 检测常亮拨动开关值 */
Light_Type Int_light_value(void);

#endif /* __INT_KEY_H__ */
