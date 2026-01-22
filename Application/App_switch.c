#include "App_switch.h"

uint8_t alarm_status_change = 2;

void App_switch_key_process(void)
{
    Key_Type key = Int_key_value();
    Touch_Type touch = Int_touch_value();

    // 当有按键按下时，可唤醒屏幕
    if ((key != KEY_NONE) || (touch == TOUCH_UP))
    {
        if (oled_en && (wake_en == 0) && sleepFlag)
        {
            sleepFlag = 0;
            sleep_time_count = 0;
        }
    }

    switch (key)
    {
    // 进行24和12小时的显示切换
    case KEY_TIME:
        is_24hour = (is_24hour + 1) % 2;
        break;

    // 长按进入时间设置
    case KEY_TIME_LONG:

        taskENTER_CRITICAL();
        Int_oled_clear();
        taskEXIT_CRITICAL();

        time_buffer = time;
        date_buffer = date;
        time_buffer.Seconds = 0;
        show_type = SHOW_SET_TIME;
        break;

    // 长按进入闹钟设置
    case KEY_ALARM_SET_LONG:

        taskENTER_CRITICAL();
        Int_oled_clear();
        taskEXIT_CRITICAL();

        show_type = SHOW_SET_ALARM;
        break;

    // 一键设置闹钟模式：工作日、每天、关闭
    case KEY_5DAY:
        alarm_status_change = (alarm_status_change + 1) % 3;
        if (alarm_status_change == 0)
        {
            alarm_info.Alarm1_Type = ALARM_5DAY;
            alarm_info.Alarm2_Type = ALARM_5DAY;
        }
        else if (alarm_status_change == 1)
        {
            alarm_info.Alarm1_Type = ALARM_EVERYDAY;
            alarm_info.Alarm2_Type = ALARM_EVERYDAY;
        }
        else if (alarm_status_change == 2)
        {
            alarm_info.Alarm1_Type = ALARM_OFF;
            alarm_info.Alarm2_Type = ALARM_OFF;
        }        
        break;

    //暂停正在响的闹铃
    case KEY_ALARM_EN:
    case KEY_ALARM_SET:
        alarm_suspend = 1;
        break;
    default:
        break;
    }
}

void App_switch_toggle_process(void)
{
    OLED_Type oled = Int_OLED_value();
    switch (oled)
    {
    // OLED开启
    case OLED_ON:
        oled_en = 1;
        break;

    // OLED关闭
    case OLED_OFF:
        oled_en = 0;
        break;
    default:
        break;
    }

    Light_Type light = Int_light_value();
    switch (light)
    {
    // 常亮开启
    case LIGHT_ON:
        wake_en = 1;
        break;

    // 常亮关闭
    case LIGHT_OFF:
        wake_en = 0;
        break;
    default:
        break;
    }
}

void App_switch_set_time_process(void)
{
    Key_Type key = Int_key_value();
    switch (key)
    {
    case KEY_TIME:
        set_time_type = (Set_Time_Type)(((uint8_t)set_time_type + 1) % 5);
        break;
    case KEY_UP:
        if (set_time_type == SET_TIME_YEAR)
        {
            date_buffer.Year = (date_buffer.Year + 1) % 100;
        }
        else if (set_time_type == SET_TIME_MONTH)
        {
            date_buffer.Month = (date_buffer.Month + 1) % 13;
        }
        else if (set_time_type == SET_TIME_DAY)
        {
            date_buffer.Date = (date_buffer.Date + 1) % 32;
        }
        else if (set_time_type == SET_TIME_HOUR)
        {
            time_buffer.Hours = (time_buffer.Hours + 1) % 24;
        }
        else if (set_time_type == SET_TIME_MINUTE)
        {
            time_buffer.Minutes = (time_buffer.Minutes + 1) % 60;
        }
        break;
    case KEY_DOWN:
        if (set_time_type == SET_TIME_YEAR)
        {
            if (date_buffer.Year == 0)
            {
                date_buffer.Year = 99;
            }
            else
            {
                date_buffer.Year = date_buffer.Year - 1;
            }
        }
        else if (set_time_type == SET_TIME_MONTH)
        {
            if (date_buffer.Month == 1)
            {
                date_buffer.Month = 12;
            }
            else
            {
                date_buffer.Month = date_buffer.Month - 1;
            }
        }
        else if (set_time_type == SET_TIME_DAY)
        {
            if (date_buffer.Date == 1)
            {
                date_buffer.Date = 31;
            }
            else
            {
                date_buffer.Date = date_buffer.Date - 1;
            }
        }
        else if (set_time_type == SET_TIME_HOUR)
        {
            if (time_buffer.Hours == 0)
            {
                time_buffer.Hours = 23;
            }
            else
            {
                time_buffer.Hours = time_buffer.Hours - 1;
            }
        }
        else if (set_time_type == SET_TIME_MINUTE)
        {
            if (time_buffer.Minutes == 0)
            {
                time_buffer.Minutes = 59;
            }
            else
            {
                time_buffer.Minutes = time_buffer.Minutes - 1;
            }
        }
        break;
    case KEY_TIME_LONG:
        time = time_buffer;
        date = date_buffer;
        HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
        HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN);

        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, hrtc.DateToUpdate.Year);
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, hrtc.DateToUpdate.Month);
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, hrtc.DateToUpdate.Date);
        HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR5, hrtc.DateToUpdate.WeekDay);  
        
        taskENTER_CRITICAL();
        Int_oled_clear();
        taskEXIT_CRITICAL();

        show_type = SHOW_NORMAL;
        break;
    default:
        break;
    }
}

void App_switch_set_alarm_process(void)
{
    Key_Type key = Int_key_value();
    switch (key)
    {
    case KEY_ALARM_SET:
        set_alarm_type = (Set_Alarm_Type)(((uint8_t)set_alarm_type + 1) % 6);
        break;
    case KEY_UP:
        if (set_alarm_type == SET_ALARM1_HOUR)
        {
            alarm_info.Alarm1_Time.Hours = (alarm_info.Alarm1_Time.Hours + 1) % 24;
        }
        else if (set_alarm_type == SET_ALARM1_MINUTE)
        {
            alarm_info.Alarm1_Time.Minutes = (alarm_info.Alarm1_Time.Minutes + 1) % 60;
        }
        else if (set_alarm_type == SET_ALARM1_MODE)
        {
            alarm_info.Alarm1_Type = (Alarm_Type)(((uint8_t)alarm_info.Alarm1_Type + 1) % 3);
        }
        else if (set_alarm_type == SET_ALARM2_HOUR)
        {
            alarm_info.Alarm2_Time.Hours = (alarm_info.Alarm2_Time.Hours + 1) % 24;
        }
        else if (set_alarm_type == SET_ALARM2_MINUTE)
        {
            alarm_info.Alarm2_Time.Minutes = (alarm_info.Alarm2_Time.Minutes + 1) % 60;
        }
        else if (set_alarm_type == SET_ALARM2_MODE)
        {
            alarm_info.Alarm2_Type = (Alarm_Type)(((uint8_t)alarm_info.Alarm2_Type + 1) % 3);
        }
        break;
    case KEY_DOWN:
        if (set_alarm_type == SET_ALARM1_HOUR)
        {
            if (alarm_info.Alarm1_Time.Hours == 0)
            {
                alarm_info.Alarm1_Time.Hours = 23;
            }
            else
            {
                alarm_info.Alarm1_Time.Hours--;
            }
        }
        else if (set_alarm_type == SET_ALARM1_MINUTE)
        {
            if (alarm_info.Alarm1_Time.Minutes == 0)
            {
                alarm_info.Alarm1_Time.Minutes = 59;
            }
            else
            {
                alarm_info.Alarm1_Time.Minutes--;
            }
        }
        else if (set_alarm_type == SET_ALARM1_MODE)
        {
            if (alarm_info.Alarm1_Type == ALARM_OFF)
            {
                alarm_info.Alarm1_Type = ALARM_EVERYDAY;
            }
            else
            {
                alarm_info.Alarm1_Type = (Alarm_Type)((uint8_t)alarm_info.Alarm1_Type - 1);
            }
        }
        else if (set_alarm_type == SET_ALARM2_HOUR)
        {
            if (alarm_info.Alarm2_Time.Hours == 0)
            {
                alarm_info.Alarm2_Time.Hours = 23;
            }
            else
            {
                alarm_info.Alarm2_Time.Hours--;
            }
        }
        else if (set_alarm_type == SET_ALARM2_MINUTE)
        {
            if (alarm_info.Alarm2_Time.Minutes == 0)
            {
                alarm_info.Alarm2_Time.Minutes = 59;
            }
            else
            {
                alarm_info.Alarm2_Time.Minutes--;
            }
        }
        else if (set_alarm_type == SET_ALARM2_MODE)
        {
            if (alarm_info.Alarm2_Type == ALARM_OFF)
            {
                alarm_info.Alarm2_Type = ALARM_EVERYDAY;
            }
            else
            {
                alarm_info.Alarm2_Type = (Alarm_Type)((uint8_t)alarm_info.Alarm1_Type - 1);
            }
        }
        break;
    case KEY_ALARM_SET_LONG:

        taskENTER_CRITICAL();
        Int_oled_clear();
        taskEXIT_CRITICAL();

        show_type = SHOW_NORMAL;
        break;
    default:
        break;
    }
}
