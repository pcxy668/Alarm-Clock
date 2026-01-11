#ifndef __INT_TOUCH_H__
#define __INT_TOUCH_H__

#include "gpio.h"

typedef enum
{
    TOUCH_NONE = 0,
    TOUCH_UP
} Touch_Type;

Touch_Type Int_touch_value(void);

#endif /* __INT_TOUCH_H__ */
