#include "EEPROM_controller.h"

uint8_t CalculateChecksum(Configs configs, SensorsMaxMin sensorsMaxMin)
{
    uint8_t checksum = 0;
    checksum += configs.monitoringPeriod;
    checksum += configs.alarmDuration;
    checksum += configs.alarmFlag;
    checksum += configs.alarmHours;
    checksum += configs.alarmMinutes;
    checksum += configs.alarmSeconds;
    checksum += configs.thresholdTemp;
    checksum += configs.thresholdLum;
    checksum += configs.clockHours;
    checksum += configs.clockMinutes;
    checksum += sensorsMaxMin.maxLum;
    checksum += sensorsMaxMin.maxTemp;
    checksum += sensorsMaxMin.minLum;
    checksum += sensorsMaxMin.minTemp;
    return checksum;
}

bool MemIsUsable()
{
    uint8_t calculatedChecksum = CalculateChecksum(ReadConfigs(), ReadMaxMin());
    uint8_t readMagicWord = EEPROM_Read(MAGIC_WORD_ADDR);
    uint8_t readChecksum = EEPROM_Read(CHECKSUM_ADDR);
    if ((readChecksum == calculatedChecksum) && (readMagicWord == MAGIC_WORD))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Configs ReadConfigs()
{
    Configs configs;
    configs.monitoringPeriod = EEPROM_Read(MONITORING_PERIOD_ADDR);
    configs.alarmDuration = EEPROM_Read(ALARM_DURATION_ADDR);
    configs.alarmFlag = EEPROM_Read(ALARM_FLAG_ADDR);
    configs.alarmHours = EEPROM_Read(ALARM_HOURS_ADDR);
    configs.alarmMinutes = EEPROM_Read(ALARM_MINUTES_ADDR);
    configs.alarmSeconds = EEPROM_Read(ALARM_SECONDS_ADDR);
    configs.thresholdTemp = EEPROM_Read(THRESHOLD_TEMP_ADDR);
    configs.thresholdLum = EEPROM_Read(THRESHOLD_LUM_ADDR);
    configs.clockHours = EEPROM_Read(CLOCK_HOURS_ADDR);
    configs.clockMinutes = EEPROM_Read(CLOCK_MINUTES_ADDR);
    return configs;
}

void WriteConfigs(Configs configs)
{
    uint8_t calculatedChecksum = CalculateChecksum(configs);
    EEPROM_Write(MAGIC_WORD_ADDR, MAGIC_WORD);
    EEPROM_Write(CHECKSUM_ADDR, calculatedChecksum);
    EEPROM_Write(MONITORING_PERIOD_ADDR, configs.monitoringPeriod);
    EEPROM_Write(ALARM_DURATION_ADDR, configs.alarmDuration);
    EEPROM_Write(ALARM_FLAG_ADDR, configs.alarmFlag);
    EEPROM_Write(ALARM_HOURS_ADDR, configs.alarmHours);
    EEPROM_Write(ALARM_MINUTES_ADDR, configs.alarmMinutes);
    EEPROM_Write(ALARM_SECONDS_ADDR, configs.alarmSeconds);
    EEPROM_Write(THRESHOLD_TEMP_ADDR, configs.thresholdTemp);
    EEPROM_Write(THRESHOLD_LUM_ADDR, configs.thresholdLum);
    EEPROM_Write(CLOCK_HOURS_ADDR, configs.clockHours);
    EEPROM_Write(CLOCK_MINUTES_ADDR, configs.clockMinutes);
}

void WriteMaxMin(SensorsMaxMin sensorMaxMin)
{
    for (uint8_t i = 0; i < 5; i++)
    {
        EEPROM_Write(MAX_TEMP_ADDR + i, sensorMaxMin.maxTemp[i]);
        EEPROM_Write(MIN_TEMP_ADDR + i, sensorMaxMin.minTemp[i]);
        EEPROM_Write(MAX_LUM_ADDR + i, sensorMaxMin.maxLum[i]);
        EEPROM_Write(MIN_LUM_ADDR + i, sensorMaxMin.minLum[i]);
    }
}

SensorsMaxMin ReadMaxMin()
{
    SensorsMaxMin sensorMaxMin;
    for (uint8_t i = 0; i < 5; i++)
    {
        sensorMaxMin.maxTemp[i] = EEPROM_Read(MAX_TEMP_ADDR + i);
        sensorMaxMin.minTemp[i] = EEPROM_Read(MIN_TEMP_ADDR + i);
        sensorMaxMin.maxLum[i] = EEPROM_Read(MAX_LUM_ADDR + i);
        sensorMaxMin.minLum[i] = EEPROM_Read(MIN_LUM_ADDR + i);
    }
    return sensorMaxMin;
}