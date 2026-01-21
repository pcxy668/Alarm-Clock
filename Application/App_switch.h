#ifndef __APP_SWITCH_H__
#define __APP_SWITCH_H__

#include "Int_key.h"
#include "Int_oled.h"
#include "Int_touch.h"
#include "Com_Debug.h"
#include "App_show.h"
#include "rtc.h"

extern uint8_t is_24hour;
extern uint8_t oled_en;
extern uint8_t wake_en;
extern uint16_t sleep_time_count;
extern uint8_t sleepFlag;
extern uint8_t alarm_suspend;
extern Show_Type show_type;
extern Set_Time_Type set_time_type;
extern Set_Alarm_Type set_alarm_type;
extern RTC_TimeTypeDef time;
extern RTC_TimeTypeDef time_buffer;
extern RTC_DateTypeDef date;
extern RTC_DateTypeDef date_buffer;


void App_switch_key_process(void);
void App_switch_toggle_process(void);
void App_switch_set_time_process(void);
void App_switch_set_alarm_process(void);

#endif /* __APP_SWITCH_H__ */
