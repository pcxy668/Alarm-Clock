#include "Int_buzzer.h"

void Int_buzzer_once(void)
{
    HAL_GPIO_WritePin(BUZZER_EN_GPIO_Port,BUZZER_EN_Pin,GPIO_PIN_SET);
    vTaskDelay(200);
    HAL_GPIO_WritePin(BUZZER_EN_GPIO_Port,BUZZER_EN_Pin,GPIO_PIN_RESET);
}
