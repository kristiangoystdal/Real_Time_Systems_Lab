
#include "state.h"
#include "../controller/EEPROM/EEPROM_controller.h"
#include <string.h>
#include <stdio.h>

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

void get_config_alarm_hours_str(char* s) {
  sprintf(s, "%02u", _configs.alarmHours);
}

void get_config_alarm_minutes_str(char* s) {
  sprintf(s, "%02u", _configs.alarmMinutes);
}

void get_config_alarm_seconds_str(char* s) {
  sprintf(s, "%02u", _configs.alarmSeconds);
}

void get_config_alarm_time_str(char* s) {
  sprintf(s, "%02u:%02u:%02u", _configs.alarmHours, _configs.alarmMinutes, _configs.alarmSeconds);
}

void get_config_threshold_temperature_str(char* s) {
  sprintf(s, "%02u", _configs.thresholdTemp);
}

void get_config_threshold_luminosity_str(char* s) {
  sprintf(s, "%u", _configs.thresholdLum);
}

void increment_config_alarm_hours(void) {
  _configs.alarmHours = (_configs.alarmHours + 1) % HOURS_MAX_VALUE;
}

void increment_config_alarm_minutes(void) {
  _configs.alarmMinutes = (_configs.alarmMinutes + 1) % MINUTES_MAX_VALUE;
}

void increment_config_alarm_seconds(void) {
  _configs.alarmSeconds = (_configs.alarmSeconds + 1) % SECONDS_MAX_VALUE;
}

void increment_config_threshold_temperature(void) {
  _configs.thresholdTemp = (_configs.thresholdTemp + 1) % TEMP_MAX_VALUE;
}

void increment_config_threshold_luminosity(void) {
  _configs.thresholdLum = (_configs.thresholdLum + 1) % LUM_MAX_VALUE;
}

void toggle_config_alarm_flag(void) {
  _configs.alarmFlag = ~_configs.alarmFlag;
}

void reset_sensors_max_min(void) {
  memset(&_sensorsMaxMin, 0, sizeof(_sensorsMaxMin));
  _sensorsMaxMin.minTemp[MAX_MIN_TEMP_BYTE] = 0xFF;
  _sensorsMaxMin.minLum[MAX_MIN_LUM_BYTE] = 0xFF;
}

void flush_configs(uint8_t hours, uint8_t minutes) {
  WriteMaxMin(_sensorsMaxMin);
  _configs.clockHours = hours;
  _configs.clockMinutes = minutes;
  WriteConfigs(_configs);
  WriteChecksum(_configs, _sensorsMaxMin);
}

void measure_to_string(uint8_t measure [5], char string [17]) {
  uint8_t seconds = measure[MAX_MIN_SECONDS_BYTE];
  uint8_t minutes = measure[MAX_MIN_MINUTES_BYTE];
  uint8_t hours = measure[MAX_MIN_HOURS_BYTE];
  uint8_t lum = measure[MAX_MIN_LUM_BYTE];
  uint8_t temp = measure[MAX_MIN_TEMP_BYTE];
  sprintf(string, "%02u:%02u:%02u  %02uC L%02u", hours, minutes, seconds, lum, temp);
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
