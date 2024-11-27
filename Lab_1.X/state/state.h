#ifndef __STATE_H
#define __STATE_H

#include "stdint.h"
#include "stdbool.h"

#define INITIAL_MONITORING_PERIOD 3
#define INITIAL_ALARM_DURATION 5
#define INITIAL_ALARM_FLAG 0
#define INITIAL_ALARM_HOURS 12
#define INITIAL_ALARM_MINUTES 0
#define INITIAL_ALARM_SECONDS 0
#define INITIAL_THRESHOLD_TEMP 25
#define INITIAL_THRESHOLD_LUM 5
#define INITIAL_CLOCK_HOURS 0
#define INITIAL_CLOCK_MINUTES 0

#define MAX_TEMPERATURE 0
#define MIN_TEMPERATURE 1
#define MAX_LUMINOSITY 2
#define MIN_LUMINOSITY 3

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

void set_default(void);
void set_configs(Configs configs, bool write_eeprom);
Configs get_configs(void);
void set_max_min(SensorsMaxMin sensorsMaxMin, bool write_eeprom);
SensorsMaxMin get_max_min(void);
uint8_t get_config_clock_hours(void);
uint8_t get_config_clock_minutes(void);
void get_measure(uint8_t index, char measure [17]);

#endif
