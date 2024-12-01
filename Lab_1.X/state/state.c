
#include "state.h"
#include "../controller/EEPROM/EEPROM_controller.h"
#include <string.h>

static Configs _configs;
static SensorsMaxMin _sensorsMaxMin;
static uint8_t _mode;
static bool _mode_has_changed;

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

uint8_t get_config_monitoring_period(void) {
  return _configs.monitoringPeriod;
}

uint8_t get_config_alarm_duration(void) {
  return _configs.alarmDuration;
}

uint8_t get_config_alarm_flag(void) {
  return _configs.alarmFlag;
}

uint8_t get_config_alarm_hours(void) {
  return _configs.alarmHours;
}

uint8_t get_config_alarm_minutes(void) {
  return _configs.alarmMinutes;
}

uint8_t get_config_alarm_seconds(void) {
  return _configs.alarmSeconds;
}

uint8_t get_config_threshold_temperature(void) {
  return _configs.thresholdTemp;
}

uint8_t get_config_threshold_luminosity(void) {
  return _configs.thresholdLum;
}

uint8_t get_config_clock_hours() {
  return _configs.clockHours;
}

uint8_t get_config_clock_minutes() {
  return _configs.clockMinutes;
}

void measure_to_string(uint8_t measure [5], char string [17]) {
  string[0] = 0x30 + measure[0]/10;
  string[1] = 0x30 + (measure[0]%10);
  string[2] = ':';
  string[3] = 0x30 + measure[1]/10;
  string[4] = 0x30 + (measure[1]%10);
  string[5] = ':';
  string[6] = 0x30 + measure[2]/10;
  string[7] = 0x30 + (measure[2]%10);
  string[8] = ' ';
  string[9] = ' ';
  string[10] = 0x30 + measure[3]/10;
  string[11] = 0x30 + (measure[3]%10);
  string[12] = 'C';
  string[13] = ' ';
  string[14] = 'L';
  string[15] = 0x30 + measure[4];
  string[16] = '\0';
}

void get_measure(uint8_t index, char measure [17] ) {
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

void set_mode(uint8_t mode) {
  _mode = mode;
  _mode_has_changed = true;
}

uint8_t get_mode(void) {
  _mode_has_changed = false;
  return _mode;
}

bool mode_has_changed(void) {
  return _mode_has_changed;
}
