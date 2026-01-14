#ifndef __INT_DS18B20_H__
#define __INT_DS18B20_H__

#include "gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Com_Debug.h"

#define DS18B20_DATA_H HAL_GPIO_WritePin(DS18B20_DATA_GPIO_Port,DS18B20_DATA_Pin,GPIO_PIN_SET) 
#define DS18B20_DATA_L HAL_GPIO_WritePin(DS18B20_DATA_GPIO_Port,DS18B20_DATA_Pin,GPIO_PIN_RESET) 
#define DS18B20_DATA_READ HAL_GPIO_ReadPin(DS18B20_DATA_GPIO_Port,DS18B20_DATA_Pin)

void Int_DS18B20_Init(void);
void Int_DS18B20_WriteByte(uint8_t byte);
uint8_t Int_DS18B20_ReadByte(void);
void Int_DS18B20_Value(char *temperature);

#endif /* __INT_DS18B20_H__ */
