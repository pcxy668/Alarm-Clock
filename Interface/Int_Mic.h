#ifndef __INT_MIC_H__
#define __INT_MIC_H__

#include "gpio.h"

typedef enum
{
    MIC_ON = 0,
    MIC_OFF
} Mic_Type;

Mic_Type Int_Mic_value(void);

#endif /* __INT_MIC_H__ */
