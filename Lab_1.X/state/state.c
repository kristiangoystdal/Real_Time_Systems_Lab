
#include "state.h"
#include "EEPROM_controller.h"

static Configs _configs;
static SensorsMaxMin _sensorsMaxMin;

void set_configs(Configs configs) {
  _configs = configs;
  WriteConfigs(configs);
}

void set_default_configs() {
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

Configs get_configs(){
  return _configs;
}

void set_max_min(SensorsMaxMin sensorsMaxMin) {
  _sensorsMaxMin = sensorsMaxMin;
  WriteMaxMin(sensorsMaxMin);
}

void set_default_max_min() {
  memset(&_sensorsMaxMin, 0, 20);
  WriteMaxMin(_sensorsMaxMin);
}

SensorsMaxMin get_max_min() {
  return _sensorsMaxMin;
}
