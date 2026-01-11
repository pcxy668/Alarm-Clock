#include "App_freeRTOS.h"

void App_freeRTOS_start()
{
    //xTaskCreate();
    vTaskStartScheduler();
}
