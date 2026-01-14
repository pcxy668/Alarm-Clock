#ifndef __INT_DHT11_H__
#define __INT_DHT11_H__

#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Com_Debug.h"

#define DHT11_DATA_H HAL_GPIO_WritePin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin,GPIO_PIN_SET) 
#define DHT11_DATA_L HAL_GPIO_WritePin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin,GPIO_PIN_RESET) 
#define DHT11_DATA_READ HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port,DHT11_DATA_Pin)

void Int_DHT11_Init(void);
void Int_DHT11_Value(uint8_t *temperature,uint8_t *humidity);

#endif /* __INT_DHT11_H__ */
