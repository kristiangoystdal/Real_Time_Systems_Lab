#ifndef __STATE_H
#define __STATE_H

#include "stdint.h"

typedef struct
{
    uint8_t monitoringPeriod;
    uint8_t alarmDuration;
    uint8_t alarmFlag;
    uint8_t alarmHours;
    uint8_t alarmMinutes;
    uint8_t alarmSeconds;
    uint8_t thresholdTemp;
    uint8_t thresholdLum;
    uint8_t clockHours;
    uint8_t clockMinutes;
} Configs;

typedef struct
{
    uint8_t maxTemp[5];
    uint8_t minTemp[5];
    uint8_t maxLum[5];
    uint8_t minLum[5];
} SensorsMaxMin;

void set_configs(Configs configs);
void set_default_configs();
Configs get_configs();
void set_max_min(SensorsMaxMin sensorsMaxMin);
SensorsMaxMin get_max_min();

#endif
