#ifndef __EEPROM_H
#define __EEPROM_H

#include "../../mcc_generated_files/system/system.h"

#define MONITORING_PERIOD_ADDR 0x7000
#define ALARM_DURATION_ADDR 0x7001
#define ALARM_FLAG_ADDR 0x7002
#define ALARM_HOURS_ADDR 0x7003
#define ALARM_MINUTES_ADDR 0x7004
#define ALARM_SECONDS_ADDR 0x7005
#define THRESHOLD_TEMP_ADDR 0x7006
#define THRESHOLD_LUM_ADDR 0x7007
#define CLOCK_HOURS_ADDR 0x7008
#define CLOCK_MINUTES_ADDR 0x7009
#define MAX_TEMP_ADDR 0x700A // 0x700A -> 0x700E
#define MIN_TEMP_ADDR 0x700F // 0x700F -> 0x7013
#define MAX_LUM_ADDR 0x7014  // 0x7014 -> 0x7018
#define MIN_LUM_ADDR 0x7019  // 0x7019 -> 0x701D
#define MAGIC_WORD_ADDR 0x7042
#define CHECKSUM_ADDR 0x7043

#define MAGIC_WORD 42

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

uint8_t CalculateChecksum(Configs configs);
bool ConfigIsUsable();
Configs ReadConfigs();
void WriteConfigs(Configs configs);
void WriteMaxMin(SensorsMaxMin sensorsMaxMin);
SensorsMaxMin ReadMaxMin();

#endif