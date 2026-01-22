#include "App_freeRTOS.h"

char temperature;
RTC_TimeTypeDef time;
RTC_TimeTypeDef time_buffer;
RTC_DateTypeDef date;
RTC_DateTypeDef date_buffer;
uint8_t is_24hour = 1;
uint8_t oled_en = 1; //屏幕开关使能
uint8_t wake_en = 1; //屏幕唤醒使能
uint16_t sleep_time_count = 0; //进入睡眠计时
uint8_t sleepFlag = 0; //睡眠状态
uint8_t oled_is_on = 0; //屏幕是否已经开启
uint8_t alarm_suspend = 0; //闹钟暂停
Show_Type show_type = SHOW_NORMAL; //默认正常展示模式 
Set_Time_Type set_time_type = SET_TIME_YEAR;
Set_Alarm_Type set_alarm_type = SET_ALARM1_HOUR;

Alarm_Info alarm_info = 
{
    {7,0,0},
    {7,30,0},
    ALARM_OFF,
    ALARM_OFF
};

// 采集类任务：获取时间、温度等
void collect_task(void *pvParameters);
#define COLLECT_TASK_STACK_DEPTH 128
#define COLLECT_TASK_PRIORITY 1
TaskHandle_t collect_task_handle;

// 展示类任务：屏幕显示等
void show_task(void *pvParameters);
#define SHOW_TASK_STACK_DEPTH 128
#define SHOW_TASK_PRIORITY 2
TaskHandle_t show_task_handle;

// 触发类任务：按键开关、触摸等
void switch_task(void *pvParameters);
#define SWITCH_TASK_STACK_DEPTH 128
#define SWITCH_TASK_PRIORITY 3
TaskHandle_t switch_task_handle;

// 声音类任务：闹铃播放等
void alarm_task(void *pvParameters);
#define ALARM_TASK_STACK_DEPTH 128
#define ALARM_TASK_PRIORITY 2
TaskHandle_t alarm_task_handle;

void App_freeRTOS_start()
{
    debug_printf("task-start execute\n");

    xTaskCreate(collect_task, "collect_task", COLLECT_TASK_STACK_DEPTH, NULL, COLLECT_TASK_PRIORITY, &collect_task_handle);
    xTaskCreate(show_task, "show_task", SHOW_TASK_STACK_DEPTH, NULL, SHOW_TASK_PRIORITY, &show_task_handle);
    xTaskCreate(switch_task, "switch_task", SWITCH_TASK_STACK_DEPTH, NULL, SWITCH_TASK_PRIORITY, &switch_task_handle);
    xTaskCreate(alarm_task, "alarm_task", ALARM_TASK_STACK_DEPTH, NULL, ALARM_TASK_PRIORITY, &alarm_task_handle);

    vTaskStartScheduler();
}

void collect_task(void *pvParameters)
{
    while (1)
    {

        hrtc.DateToUpdate.Year = HAL_RTCEx_BKUPRead(&hrtc,RTC_BKP_DR2);
        hrtc.DateToUpdate.Month = HAL_RTCEx_BKUPRead(&hrtc,RTC_BKP_DR3);
        hrtc.DateToUpdate.Date = HAL_RTCEx_BKUPRead(&hrtc,RTC_BKP_DR4);
        hrtc.DateToUpdate.WeekDay = HAL_RTCEx_BKUPRead(&hrtc,RTC_BKP_DR5);

        HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);

        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, hrtc.DateToUpdate.Year);
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, hrtc.DateToUpdate.Month);
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, hrtc.DateToUpdate.Date);
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR5, hrtc.DateToUpdate.WeekDay);  

        Int_DS18B20_Value(&temperature);
        vTaskDelay(1000);
    }
}

void show_task(void *pvParameters)
{
    App_show_Init();
    while (1)
    {
        if (oled_en && (sleepFlag == 0))
        {
            if (show_type == SHOW_NORMAL)
            {
                taskENTER_CRITICAL();
                App_show_normal();
                taskEXIT_CRITICAL();
            }
            else if (show_type == SHOW_SET_TIME)
            {
                taskENTER_CRITICAL();
                App_show_set_time();
                taskEXIT_CRITICAL();
            }
            else if (show_type == SHOW_SET_ALARM)
            {
                taskENTER_CRITICAL();
                App_show_set_alarm();
                taskEXIT_CRITICAL();
            }            
        }

        //睡眠管理
        App_show_sleepManage();

        vTaskDelay(500);
    }
}

void switch_task(void *pvParameters)
{
    while (1)
    {
        if (show_type == SHOW_NORMAL)
        {
            App_switch_key_process();
        }
        else if (show_type == SHOW_SET_TIME)
        {
            App_switch_set_time_process();
        }
        else if (show_type == SHOW_SET_ALARM)
        {
            App_switch_set_alarm_process();
        }
        App_switch_toggle_process();
        vTaskDelay(20);
    }
    
}

void alarm_task(void *pvParameters)
{
    while (1)
    {
        if ((alarm_info.Alarm1_Type == ALARM_EVERYDAY) && (alarm_suspend == 0))
        {
            if((alarm_info.Alarm1_Time.Hours == time.Hours) && (alarm_info.Alarm1_Time.Minutes == time.Minutes))
            {
                Int_buzzer_once();
            }
        }

        if ((alarm_info.Alarm2_Type == ALARM_EVERYDAY) && (alarm_suspend == 0))
        {
            if((alarm_info.Alarm2_Time.Hours == time.Hours) && (alarm_info.Alarm2_Time.Minutes == time.Minutes))
            {
                Int_buzzer_once();
            }
        }  

        if ((alarm_info.Alarm1_Type == ALARM_5DAY) && (alarm_suspend == 0) && (date.WeekDay >= 1) && (date.WeekDay <= 5))
        {
            if((alarm_info.Alarm1_Time.Hours == time.Hours) && (alarm_info.Alarm1_Time.Minutes == time.Minutes))
            {
                Int_buzzer_once();
            }
        }

        if ((alarm_info.Alarm2_Type == ALARM_5DAY) && (alarm_suspend == 0) && (date.WeekDay >= 1) && (date.WeekDay <= 5))
        {
            if((alarm_info.Alarm2_Time.Hours == time.Hours) && (alarm_info.Alarm2_Time.Minutes == time.Minutes))
            {
                Int_buzzer_once();
            }
        }

        if((alarm_info.Alarm1_Time.Minutes != time.Minutes) && (alarm_info.Alarm2_Time.Minutes != time.Minutes))
        {
            alarm_suspend = 0;
        }
        vTaskDelay(800);
    }
}
