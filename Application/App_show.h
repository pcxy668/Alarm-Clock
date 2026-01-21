#ifndef __APP_SHOW_H__
#define __APP_SHOW_H__

#include "Int_oled.h"
#include "stdio.h"
#include "Com_Debug.h"

typedef enum
{
    SHOW_NORMAL = 0,
    SHOW_SET_TIME,
    SHOW_SET_ALARM
} Show_Type;

typedef enum
{
    SET_TIME_YEAR,
    SET_TIME_MONTH,
    SET_TIME_DAY,
    SET_TIME_HOUR,
    SET_TIME_MINUTE
} Set_Time_Type;

typedef enum
{
    SET_ALARM1_HOUR,
    SET_ALARM1_MINUTE,
    SET_ALARM1_MODE,
    SET_ALARM2_HOUR,
    SET_ALARM2_MINUTE,
    SET_ALARM2_MODE
} Set_Alarm_Type;

typedef enum
{
    ALARM_OFF,
    ALARM_5DAY,
    ALARM_EVERYDAY
} Alarm_Type;

typedef struct
{
    RTC_TimeTypeDef Alarm1_Time;
    RTC_TimeTypeDef Alarm2_Time;
    Alarm_Type Alarm1_Type;
    Alarm_Type Alarm2_Type;
} Alarm_Info;

extern char temperature;
extern RTC_TimeTypeDef time;
extern RTC_DateTypeDef date;
extern uint8_t is_24hour;
extern uint8_t oled_en;
extern uint8_t wake_en;
extern uint16_t sleep_time_count;
extern uint8_t sleepFlag;
extern uint8_t oled_is_on;
extern RTC_TimeTypeDef time_buffer;
extern RTC_DateTypeDef date_buffer;
extern Set_Time_Type set_time_type;
extern Set_Alarm_Type set_alarm_type;
extern Alarm_Info alarm_info;

void App_show_Init(void);
void App_show_temperature(void);
void App_show_time(void);
void App_show_charge(void);
void App_show_alarm(void);
void App_show_static(void);
void App_show_sleepManage(void);
void App_show_normal(void);
void App_show_set_time(void);
void App_show_set_alarm(void);

#endif /* __APP_SHOW_H__ */
