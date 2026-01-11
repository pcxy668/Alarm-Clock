#include "Int_Mic.h"

Mic_Type Int_Mic_value(void)
{
    if (HAL_GPIO_ReadPin(MIC_GPIO_Port,MIC_Pin) == GPIO_PIN_RESET)
    {
        return MIC_ON;
    }
    return MIC_OFF;
}


