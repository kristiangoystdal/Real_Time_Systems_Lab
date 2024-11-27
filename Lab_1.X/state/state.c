
#include "state.h"
#include "../controller/EEPROM/EEPROM_controller.h"
#include <string.h>

static Configs _configs;
static SensorsMaxMin _sensorsMaxMin;

void set_configs(Configs configs, bool write_eeprom) {
  _configs = configs;
  if(write_eeprom) {
    WriteConfigs(configs);
    WriteChecksum(configs, _sensorsMaxMin);
  }
}

Configs get_configs(){
  return _configs;
}

void set_max_min(SensorsMaxMin sensorsMaxMin, bool write_eeprom) {
  _sensorsMaxMin = sensorsMaxMin;
  if(write_eeprom) {
    WriteMaxMin(sensorsMaxMin);
    WriteChecksum(_configs, sensorsMaxMin);
  }
}

void set_default() {
  memset(&_sensorsMaxMin, 0, sizeof(_sensorsMaxMin));
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

SensorsMaxMin get_max_min() {
  return _sensorsMaxMin;
}

uint8_t get_config_clock_hours() {
  return _configs.clockHours;
}

uint8_t get_config_clock_minutes() {
  return _configs.clockMinutes;
}
