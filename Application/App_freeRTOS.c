#include "App_freeRTOS.h"

char temperature;
RTC_TimeTypeDef time;
RTC_DateTypeDef date;

//采集类任务：获取时间、温度等
void collect_task(void *pvParameters);
#define COLLECT_TASK_STACK_DEPTH 128
#define COLLECT_TASK_PRIORITY 1
TaskHandle_t collect_task_handle;

//展示类任务：屏幕显示等
void show_task(void *pvParameters);
#define SHOW_TASK_STACK_DEPTH 128
#define SHOW_TASK_PRIORITY 2
TaskHandle_t show_task_handle;

void App_freeRTOS_start()
{
    debug_printf("task-start execute\n");
    xTaskCreate(collect_task,"collect_task",COLLECT_TASK_STACK_DEPTH,NULL,COLLECT_TASK_PRIORITY,&collect_task_handle);
    xTaskCreate(show_task,"show_task",SHOW_TASK_STACK_DEPTH,NULL,SHOW_TASK_PRIORITY,&show_task_handle);
    // xTaskCreate(task3,"task3",128,NULL,1,&task3_handle);
    // xTaskCreate(task4,"task4",128,NULL,1,&task4_handle);
    // xTaskCreate(task5,"task5",128,NULL,1,&task5_handle);
    vTaskStartScheduler();
}

void collect_task(void *pvParameters)
{
    while (1)
    {
        HAL_RTC_GetTime(&hrtc,&time,RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc,&date,RTC_FORMAT_BIN);
        Int_DS18B20_Value(&temperature);
        vTaskDelay(1000);
    }
}

void show_task(void *pvParameters)
{
    Int_oled_init();
    Int_oled_displayStr(0,0,"2026-01-15");
    Int_oled_displayBigNum(2,1,1);
    Int_oled_displayBigNum(4,1,5);
    Int_oled_displayBigNum(6,1,10);
    Int_oled_displayBigNum(8,1,3);
    Int_oled_displayBigNum(10,1,0);
    Int_oled_displayIcon(14,0,0);
    Int_oled_displayIcon(15,0,1);
    while (1)
    {
        debug_printf("oled model");
        vTaskDelay(5000);
    }
}

// void task1(void *pvParameters)
// {
//     while (1)
//     {
//         Key_Type key = Int_key_value();
//         if (key != KEY_NONE)
//         {
//             debug_printf("key %d is pressed\n",(uint8_t)key);
//             Int_buzzer_once();
//         }
//         Mic_Type mic = Int_Mic_value();
//         if (mic == MIC_ON)
//         {
//             debug_printf("mic is on\n");
//         }
//         Touch_Type touch = Int_touch_value();
//         if (touch == TOUCH_UP)
//         {
//             debug_printf("touch is up\n");
//         }
//         vTaskDelay(1);
//     }
// }

// void task2(void *pvParameters)
// {
//     while (1)
//     {
//         OLED_Type oled = Int_OLED_value();
//         debug_printf("oled is %d\n",(uint8_t)oled);
//         Light_Type light = Int_light_value();
//         debug_printf("light is %d\n",(uint8_t)light);
//         vTaskDelay(5000);
//     }
// }

// void task3(void *pvParameters)
// {
//     while (1)
//     {
//         RTC_TimeTypeDef time;
//         RTC_DateTypeDef date;
//         HAL_RTC_GetTime(&hrtc,&time,RTC_FORMAT_BIN);
//         HAL_RTC_GetDate(&hrtc,&date,RTC_FORMAT_BIN);
//         debug_printf("Current time is:20%d-%d-%d %d:%d:%d\n",date.Year,date.Month,date.Date,time.Hours,time.Minutes,time.Seconds);
//         vTaskDelay(1000);
//     }
    
// }

// void task4(void *pvParameters)
// {
//     char temperature = 0;
//     while (1)
//     {
//         Int_DS18B20_Value(&temperature);
//         debug_printf("current T=%d \n",temperature);
//         vTaskDelay(3000);
//     }
// }

// TaskHandle_t task2_handle;
// TaskHandle_t task3_handle;
// TaskHandle_t task4_handle;
// TaskHandle_t task5_handle;

