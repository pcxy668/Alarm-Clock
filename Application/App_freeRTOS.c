#include "App_freeRTOS.h"

void task1(void *pvParameters)
{
    while (1)
    {
        Key_Type key = Int_key_value();
        if (key != KEY_NONE)
        {
            debug_printf("key %d is pressed\n",(uint8_t)key);
            Int_buzzer_once();
        }
        Mic_Type mic = Int_Mic_value();
        if (mic == MIC_ON)
        {
            debug_printf("mic is on\n");
        }
        Touch_Type touch = Int_touch_value();
        if (touch == TOUCH_UP)
        {
            debug_printf("touch is up\n");
        }
        vTaskDelay(1);
    }
}

void task2(void *pvParameters)
{
    while (1)
    {
        OLED_Type oled = Int_OLED_value();
        debug_printf("oled is %d\n",(uint8_t)oled);
        Light_Type light = Int_light_value();
        debug_printf("light is %d\n",(uint8_t)light);
        vTaskDelay(5000);
    }
}

void task3(void *pvParameters)
{
    while (1)
    {
        RTC_TimeTypeDef time;
        RTC_DateTypeDef date;
        HAL_RTC_GetTime(&hrtc,&time,RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc,&date,RTC_FORMAT_BIN);
        debug_printf("Current time is:20%d-%d-%d %d:%d:%d\n",date.Year,date.Month,date.Date,time.Hours,time.Minutes,time.Seconds);
        vTaskDelay(1000);
    }
    
}

void task4(void *pvParameters)
{
    char temperature = 0;
    while (1)
    {
        Int_DS18B20_Value(&temperature);
        debug_printf("current T=%d \n",temperature);
        vTaskDelay(3000);
    }
}

void task5(void *pvParameters)
{
    Int_oled_init();
    Int_oled_displayStr(0,0,"2026-01-14");
    Int_oled_displayStr(0,1,"21:50");
    while (1)
    {
        debug_printf("oled model");
        vTaskDelay(3000);
    }
}

TaskHandle_t task1_handle;
TaskHandle_t task2_handle;
TaskHandle_t task3_handle;
TaskHandle_t task4_handle;
TaskHandle_t task5_handle;

void App_freeRTOS_start()
{
    debug_printf("task-start execute\n");
    xTaskCreate(task1,"task1",128,NULL,1,&task1_handle);
    xTaskCreate(task2,"task2",128,NULL,1,&task2_handle);
    xTaskCreate(task3,"task3",128,NULL,1,&task3_handle);
    xTaskCreate(task4,"task4",128,NULL,1,&task4_handle);
    xTaskCreate(task5,"task5",128,NULL,1,&task5_handle);
    vTaskStartScheduler();
}
