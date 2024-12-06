
#include "state.h"
#include "../controller/EEPROM/EEPROM_controller.h"
#include "../controller/Temperature/temperature.h"
#include <string.h>

void set_configs(Configs configs, bool write_eeprom) {
  _configs = configs;
  if (write_eeprom) {
    WriteConfigs(configs);
    WriteChecksum(configs, _sensorsMaxMin);
  }
}

void set_max_min(SensorsMaxMin sensorsMaxMin, bool write_eeprom) {
  _sensorsMaxMin = sensorsMaxMin;
  if (write_eeprom) {
    _sensorsMaxMin = sensorsMaxMin;
    WriteMaxMin(sensorsMaxMin);
    WriteChecksum(_configs, sensorsMaxMin);
  }
}

void set_default() {
  reset_sensors_max_min();
  WriteMaxMin(_sensorsMaxMin);
  _configs.monitoringPeriod = INITIAL_MONITORING_PERIOD;
  _configs.alarmDuration = INITIAL_ALARM_DURATION;
  _configs.alarmFlag = INITIAL_ALARM_FLAG;
  _configs.alarmHours = INITIAL_ALARM_HOURS;
  _configs.alarmMinutes = INITIAL_ALARM_MINUTES;
  _configs.alarmSeconds = INITIAL_ALARM_SECONDS;
  _configs.thresholdTemp = INITIAL_THRESHOLD_TEMP;
  _configs.thresholdLum = INITIAL_THRESHOLD_LUM;
  _configs.clockHours = INITIAL_CLOCK_HOURS;
  _configs.clockMinutes = INITIAL_CLOCK_MINUTES;
  WriteConfigs(_configs);
}

void reset_sensors_max_min(void) {
  memset(&_sensorsMaxMin, 0, sizeof(_sensorsMaxMin));
  _sensorsMaxMin.minTemp[MAX_MIN_TEMP_BYTE] = 99;
  _sensorsMaxMin.minLum[MAX_MIN_LUM_BYTE] = 7;
}

void flush_configs(uint8_t hours, uint8_t minutes) {
  WriteMaxMin(_sensorsMaxMin);
  _configs.clockHours = hours;
  _configs.clockMinutes = minutes;
  WriteConfigs(_configs);
  WriteChecksum(_configs, _sensorsMaxMin);
}

void measure_to_string(uint8_t measure[5], char string[17]) {
  uint8_t seconds = measure[MAX_MIN_SECONDS_BYTE];
  uint8_t minutes = measure[MAX_MIN_MINUTES_BYTE];
  uint8_t hours = measure[MAX_MIN_HOURS_BYTE];
  uint8_t lum = measure[MAX_MIN_LUM_BYTE];
  uint8_t temp = measure[MAX_MIN_TEMP_BYTE];
  if(temp > MAX_TEMPERATURE_VALUE) {
    sprintf(string, "%02u:%02u:%02u  ERC L%u", hours, minutes, seconds, lum);
  } else {
    sprintf(string, "%02u:%02u:%02u  %02uC L%u", hours, minutes, seconds, temp,
      lum);
  }
}

void get_measure(uint8_t index, char measure[17]) {
  switch (index) {
  case MAX_TEMPERATURE:
    measure_to_string(_sensorsMaxMin.maxTemp, measure);
    return;
  case MIN_TEMPERATURE:
    measure_to_string(_sensorsMaxMin.minTemp, measure);
    return;
  case MAX_LUMINOSITY:
    measure_to_string(_sensorsMaxMin.maxLum, measure);
    return;
  default: // MIN_LUMINOSITY
    measure_to_string(_sensorsMaxMin.minLum, measure);
    return;
  }
}
