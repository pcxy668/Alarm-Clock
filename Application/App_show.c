#include "App_show.h"

uint8_t blink = 0;
uint8_t tmp;
char str[10] = {0};

void App_show_Init(void)
{
    Int_oled_init();
}

void App_show_temperature(void)
{
    Int_oled_displayWord(14, 3, 12); // ℃
    sprintf(str, "%d", temperature);
    tmp = strlen(str);
    if (tmp == 1)
    {
        Int_oled_displayStr(13, 3, str);
    }
    else if (tmp == 2)
    {
        Int_oled_displayStr(12, 3, str);
    }
}

void App_show_time(void)
{
    sprintf(str, "%02d-%02d-%02d", date.Year, date.Month, date.Date);
    Int_oled_displayStr(0, 0, str);
    Int_oled_displayWord(9, 0, 0);                                     // 周
    Int_oled_displayWord(11, 0, date.WeekDay != 0 ? date.WeekDay : 7); // x

    if (is_24hour)
    {
        Int_oled_displayStr(0, 2, "  ");
        if (time.Hours < 10)
        {
            Int_oled_displayBigFont(2, 1, 0);
            Int_oled_displayBigFont(4, 1, time.Hours);
        }
        else
        {
            Int_oled_displayBigFont(2, 1, time.Hours / 10);
            Int_oled_displayBigFont(4, 1, time.Hours % 10);
        }
    }
    else
    {
        if (time.Hours == 0)
        {
            Int_oled_displayStr(0, 2, "AM");
            Int_oled_displayBigFont(2, 1, 1);
            Int_oled_displayBigFont(4, 1, 2);
        }
        else if (time.Hours >= 1 && time.Hours <= 9)
        {
            Int_oled_displayStr(0, 2, "AM");
            Int_oled_displayBigFont(2, 1, 0);
            Int_oled_displayBigFont(4, 1, time.Hours);
        }
        else if (time.Hours >= 10 && time.Hours <= 11)
        {
            Int_oled_displayStr(0, 2, "AM");
            Int_oled_displayBigFont(2, 1, time.Hours / 10);
            Int_oled_displayBigFont(4, 1, time.Hours % 10);
        }
        else if (time.Hours == 12)
        {
            Int_oled_displayStr(0, 2, "PM");
            Int_oled_displayBigFont(2, 1, 1);
            Int_oled_displayBigFont(4, 1, 2);
        }
        else if (time.Hours >= 13 && time.Hours <= 21)
        {
            Int_oled_displayStr(0, 2, "PM");
            Int_oled_displayBigFont(2, 1, 0);
            Int_oled_displayBigFont(4, 1, time.Hours - 12);
        }
        else if (time.Hours >= 22 && time.Hours <= 23)
        {
            Int_oled_displayStr(0, 2, "PM");
            Int_oled_displayBigFont(2, 1, (time.Hours - 12) / 10);
            Int_oled_displayBigFont(4, 1, (time.Hours - 12) % 10);
        }
    }

    if (blink == 1)
    {
        Int_oled_displayBigFont(6, 1, 10);
        blink = 0;
    }
    else if (blink == 0)
    {
        Int_oled_displayBigFont(6, 1, 11);
        blink = 1;
    }

    if (time.Minutes < 10)
    {
        Int_oled_displayBigFont(8, 1, 0);
        Int_oled_displayBigFont(10, 1, time.Minutes);
    }
    else
    {
        Int_oled_displayBigFont(8, 1, time.Minutes / 10);
        Int_oled_displayBigFont(10, 1, time.Minutes % 10);
    }
}

void App_show_charge(void)
{
    if (HAL_GPIO_ReadPin(CHRG_GPIO_Port, CHRG_Pin) == GPIO_PIN_RESET)
    {
        Int_oled_displayIcon(14, 0, 0); // charging
    }else
    {
        Int_oled_displayStr(14,0," ");
    }
    

    if (HAL_GPIO_ReadPin(CHRGT_GPIO_Port, CHRGT_Pin) == GPIO_PIN_RESET)
    {
        Int_oled_displayIcon(15, 0, 1); // chargT   
    }else
    {
        Int_oled_displayStr(15,0," ");
    }
}

void App_show_alarm(void)
{
    if (alarm_info.Alarm1_Type != ALARM_OFF)
    {
        Int_oled_displayIcon(13, 1, 2); // alarm1
        Int_oled_displayWord(14, 1, alarm_info.Alarm1_Type + 8);
    }else
    {
        Int_oled_displayStr(13,1,"   ");
    }
    
    if (alarm_info.Alarm2_Type != ALARM_OFF)
    {
        Int_oled_displayIcon(13, 2, 2); // alarm1
        Int_oled_displayWord(14, 2, alarm_info.Alarm2_Type + 8);
    }else
    {
        Int_oled_displayStr(13,2,"   ");
    }
}

void App_show_static(void)
{
    Int_oled_displayStr(0, 3, "LOVE MAO");
    Int_oled_displayWord(8, 3, 11); // ❤
}

void App_show_sleepManage(void)
{
    if (oled_en && (wake_en == 0) && (sleep_time_count < 30))
    {
        sleep_time_count++;
        if (sleep_time_count >= 30)
        {
            sleepFlag = 1;
            if (oled_is_on)
            {
                Int_oled_Off();
                oled_is_on = 0;
            }
        }
    }

    if (oled_en == 0)
    {
        sleepFlag = 0;
        if (oled_is_on)
        {
            Int_oled_Off();
            oled_is_on = 0;
            sleep_time_count = 0;
        }
    }

    if (oled_en && ((sleepFlag == 0) || wake_en))
    {
        if (oled_is_on == 0)
        {
            Int_oled_On();
            oled_is_on = 1;
            sleepFlag = 0;
            sleep_time_count = 0;
        }
    }
}

void App_show_normal(void)
{
    // 1.温度展示
    App_show_temperature();

    // 2.时间展示
    App_show_time();

    // 3.充电展示
    App_show_charge();

    // 4.闹钟展示
    App_show_alarm();

    // 5.静态展示
    App_show_static();
}

void App_show_set_time(void)
{

    if (blink == 1)
    {
        blink = 0;
        sprintf(str, "%02d-%02d-%02d", date_buffer.Year, date_buffer.Month, date_buffer.Date);
        Int_oled_displayStr(4, 1, str);
        sprintf(str, "%02d:%02d", time_buffer.Hours, time_buffer.Minutes);
        Int_oled_displayStr(5, 2, str);
    }
    else
    {
        blink = 1;
        switch (set_time_type)
        {
        case SET_TIME_YEAR:
            sprintf(str, "  -%02d-%02d", date_buffer.Month, date_buffer.Date);
            Int_oled_displayStr(4, 1, str);
            break;
        case SET_TIME_MONTH:
            sprintf(str, "%02d-  -%02d", date_buffer.Year, date_buffer.Date);
            Int_oled_displayStr(4, 1, str);
            break;
        case SET_TIME_DAY:
            sprintf(str, "%02d-%02d-  ", date_buffer.Year, date_buffer.Month);
            Int_oled_displayStr(4, 1, str);
            break;
        case SET_TIME_HOUR:
            sprintf(str, "  :%02d", time_buffer.Minutes);
            Int_oled_displayStr(5, 2, str);
            break;
        case SET_TIME_MINUTE:
            sprintf(str, "%02d:  ", time_buffer.Hours);
            Int_oled_displayStr(5, 2, str);
            break;
        default:
            break;
        }
    }
}

void App_show_set_alarm(void)
{
    Int_oled_displayIcon(3, 1, 2); // alarm1
    Int_oled_displayIcon(3, 2, 2); // alarm1
    if (blink == 1)
    {
        blink = 0;
        sprintf(str, "%02d:%02d", alarm_info.Alarm1_Time.Hours,alarm_info.Alarm1_Time.Minutes);
        Int_oled_displayStr(5, 1, str);
        sprintf(str, "%02d:%02d", alarm_info.Alarm2_Time.Hours,alarm_info.Alarm2_Time.Minutes);
        Int_oled_displayStr(5, 2, str);
        Int_oled_displayWord(11, 1, alarm_info.Alarm1_Type + 8); 
        Int_oled_displayWord(11, 2, alarm_info.Alarm2_Type + 8);
    }else
    {
        blink = 1;
        switch (set_alarm_type)
        {
        case SET_ALARM1_HOUR:
            sprintf(str, "  :%02d",alarm_info.Alarm1_Time.Minutes);
            Int_oled_displayStr(5, 1, str);
            break;
        case SET_ALARM1_MINUTE:
            sprintf(str, "%02d:  ",alarm_info.Alarm1_Time.Hours);
            Int_oled_displayStr(5, 1, str);
            break;
        case SET_ALARM1_MODE:
            Int_oled_displayStr(11, 1, "  ");
            break;    
        case SET_ALARM2_HOUR:
            sprintf(str, "  :%02d",alarm_info.Alarm2_Time.Minutes);
            Int_oled_displayStr(5, 2, str);
            break;
        case SET_ALARM2_MINUTE:
            sprintf(str, "%02d:  ",alarm_info.Alarm2_Time.Hours);
            Int_oled_displayStr(5, 2, str);
            break;
        case SET_ALARM2_MODE:
            Int_oled_displayStr(11, 2, "  ");
            break;         
        default:
            break;
        } 
    } 
}
