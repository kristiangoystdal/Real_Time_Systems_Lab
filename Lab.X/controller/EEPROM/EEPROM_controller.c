#include "EEPROM_controller.h"

uint8_t CalculateChecksum(Configs configs, SensorsMaxMin sensorsMaxMin) {
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
  for (uint8_t i = 0; i < 5; i++) {
    checksum += sensorsMaxMin.maxLum[i];
    checksum += sensorsMaxMin.maxTemp[i];
    checksum += sensorsMaxMin.minLum[i];
    checksum += sensorsMaxMin.minTemp[i];
  }
  return checksum;
}

void WriteChecksum(Configs configs, SensorsMaxMin sensorsMaxMin) {
  uint8_t calculatedChecksum = CalculateChecksum(configs, sensorsMaxMin);
  DATAEE_WriteByte(CHECKSUM_ADDR, calculatedChecksum);
}

bool MemIsUsable() {
  uint8_t calculatedChecksum = CalculateChecksum(ReadConfigs(), ReadMaxMin());
  uint8_t readMagicWord = DATAEE_ReadByte(MAGIC_WORD_ADDR);
  uint8_t readChecksum = DATAEE_ReadByte(CHECKSUM_ADDR);
  if ((readChecksum == calculatedChecksum) && (readMagicWord == MAGIC_WORD)) {
    return true;
  } else {
    return false;
  }
}

Configs ReadConfigs() {
  Configs configs;
  configs.monitoringPeriod = DATAEE_ReadByte(MONITORING_PERIOD_ADDR);
  configs.alarmDuration = DATAEE_ReadByte(ALARM_DURATION_ADDR);
  configs.alarmFlag = DATAEE_ReadByte(ALARM_FLAG_ADDR);
  configs.alarmHours = DATAEE_ReadByte(ALARM_HOURS_ADDR);
  configs.alarmMinutes = DATAEE_ReadByte(ALARM_MINUTES_ADDR);
  configs.alarmSeconds = DATAEE_ReadByte(ALARM_SECONDS_ADDR);
  configs.thresholdTemp = DATAEE_ReadByte(THRESHOLD_TEMP_ADDR);
  configs.thresholdLum = DATAEE_ReadByte(THRESHOLD_LUM_ADDR);
  configs.clockHours = DATAEE_ReadByte(CLOCK_HOURS_ADDR);
  configs.clockMinutes = DATAEE_ReadByte(CLOCK_MINUTES_ADDR);
  return configs;
}

void WriteConfigs(Configs configs) {
  DATAEE_WriteByte(MAGIC_WORD_ADDR, MAGIC_WORD);
  DATAEE_WriteByte(MONITORING_PERIOD_ADDR, configs.monitoringPeriod);
  DATAEE_WriteByte(ALARM_DURATION_ADDR, configs.alarmDuration);
  DATAEE_WriteByte(ALARM_FLAG_ADDR, configs.alarmFlag);
  DATAEE_WriteByte(ALARM_HOURS_ADDR, configs.alarmHours);
  DATAEE_WriteByte(ALARM_MINUTES_ADDR, configs.alarmMinutes);
  DATAEE_WriteByte(ALARM_SECONDS_ADDR, configs.alarmSeconds);
  DATAEE_WriteByte(THRESHOLD_TEMP_ADDR, configs.thresholdTemp);
  DATAEE_WriteByte(THRESHOLD_LUM_ADDR, configs.thresholdLum);
  DATAEE_WriteByte(CLOCK_HOURS_ADDR, configs.clockHours);
  DATAEE_WriteByte(CLOCK_MINUTES_ADDR, configs.clockMinutes);
}

void WriteMaxMin(SensorsMaxMin sensorMaxMin) {
  for (uint8_t i = 0; i < 5; i++) {
    DATAEE_WriteByte(MAX_TEMP_ADDR + i, sensorMaxMin.maxTemp[i]);
    DATAEE_WriteByte(MIN_TEMP_ADDR + i, sensorMaxMin.minTemp[i]);
    DATAEE_WriteByte(MAX_LUM_ADDR + i, sensorMaxMin.maxLum[i]);
    DATAEE_WriteByte(MIN_LUM_ADDR + i, sensorMaxMin.minLum[i]);
  }
}

SensorsMaxMin ReadMaxMin() {
  SensorsMaxMin sensorMaxMin;
  for (uint8_t i = 0; i < 5; i++) {
    sensorMaxMin.maxTemp[i] = DATAEE_ReadByte(MAX_TEMP_ADDR + i);
    sensorMaxMin.minTemp[i] = DATAEE_ReadByte(MIN_TEMP_ADDR + i);
    sensorMaxMin.maxLum[i] = DATAEE_ReadByte(MAX_LUM_ADDR + i);
    sensorMaxMin.minLum[i] = DATAEE_ReadByte(MIN_LUM_ADDR + i);
  }
  return sensorMaxMin;
}