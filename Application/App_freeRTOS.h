#ifndef __APP_FREERTOS_H__
#define __APP_FREERTOS_H__

#include "FreeRTOS.h"
#include "task.h"
#include "Com_Debug.h"
#include "Int_key.h"
#include "Int_touch.h"
#include "Int_Mic.h"
#include "Int_ds18b20.h"
#include "Int_buzzer.h"
#include "Int_oled.h"
#include "rtc.h"

void App_freeRTOS_start(void);

#endif /* __APP_FREERTOS_H__ */
