#ifndef __APP_FREERTOS_H__
#define __APP_FREERTOS_H__

#include "FreeRTOS.h"
#include "task.h"
#include "Com_Debug.h"
#include "Int_ds18b20.h"
#include "rtc.h"
#include "Int_buzzer.h"
#include "App_show.h"
#include "App_switch.h"

void App_freeRTOS_start(void);

#endif /* __APP_FREERTOS_H__ */
