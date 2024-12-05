#ifndef __STATE_H
#define __STATE_H

#include "stdbool.h"
#include "stdint.h"
#include <stdio.h>

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

#define MAX_MIN_SECONDS_BYTE 0
#define MAX_MIN_MINUTES_BYTE 1
#define MAX_MIN_HOURS_BYTE 2
#define MAX_MIN_TEMP_BYTE 3
#define MAX_MIN_LUM_BYTE 4

#define NORMAL_MODE 0
#define CONFIGURATION_MODE 1

#define SECONDS_MAX_VALUE 60
#define MINUTES_MAX_VALUE 60
#define HOURS_MAX_VALUE 24
#define TEMP_MAX_VALUE 51
#define LUM_MAX_VALUE 8

typedef struct {
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

typedef struct {
  uint8_t maxTemp[5];
  uint8_t minTemp[5];
  uint8_t maxLum[5];
  uint8_t minLum[5];
} SensorsMaxMin;

Configs _configs;
SensorsMaxMin _sensorsMaxMin;
uint8_t _mode;
bool _mode_has_changed;

void set_default(void);
void set_configs(Configs configs, bool write_eeprom);

static inline Configs get_configs(void) { return _configs; }

void set_max_min(SensorsMaxMin sensorsMaxMin, bool write_eeprom);

static inline SensorsMaxMin get_max_min(void) { return _sensorsMaxMin; }

static inline uint8_t get_config_monitoring_period(void) {
  return _configs.monitoringPeriod;
}

static inline uint8_t get_config_alarm_duration(void) {
  return _configs.alarmDuration;
}

static inline uint8_t get_config_alarm_flag(void) {
  return _configs.alarmFlag != 0;
}

static inline uint8_t get_config_alarm_hours(void) {
  return _configs.alarmHours;
}

static inline uint8_t get_config_alarm_minutes(void) {
  return _configs.alarmMinutes;
}

static inline uint8_t get_config_alarm_seconds(void) {
  return _configs.alarmSeconds;
}

static inline uint8_t get_config_threshold_temperature(void) {
  return _configs.thresholdTemp;
}

static inline uint8_t get_config_threshold_luminosity(void) {
  return _configs.thresholdLum;
}

static inline uint8_t get_config_clock_hours() { return _configs.clockHours; }

static inline uint8_t get_config_clock_minutes() {
  return _configs.clockMinutes;
}

static inline void get_config_alarm_hours_str(char *s) {
  sprintf(s, "%02u", _configs.alarmHours);
}

static inline void get_config_alarm_minutes_str(char *s) {
  sprintf(s, "%02u", _configs.alarmMinutes);
}

static inline void get_config_alarm_seconds_str(char *s) {
  sprintf(s, "%02u", _configs.alarmSeconds);
}

static inline void get_config_alarm_time_str(char *s) {
  sprintf(s, "%02u:%02u:%02u", _configs.alarmHours, _configs.alarmMinutes,
          _configs.alarmSeconds);
}

static inline void get_config_threshold_temperature_str(char *s) {
  sprintf(s, "%02u", _configs.thresholdTemp);
}

static inline void get_config_threshold_luminosity_str(char *s) {
  sprintf(s, "%u", _configs.thresholdLum);
}

static inline void increment_config_alarm_hours(void) {
  _configs.alarmHours = (_configs.alarmHours + 1) % HOURS_MAX_VALUE;
}

static inline void increment_config_alarm_minutes(void) {
  _configs.alarmMinutes = (_configs.alarmMinutes + 1) % MINUTES_MAX_VALUE;
}

static inline void increment_config_alarm_seconds(void) {
  _configs.alarmSeconds = (_configs.alarmSeconds + 1) % SECONDS_MAX_VALUE;
}

static inline void increment_config_threshold_temperature(void) {
  _configs.thresholdTemp = (_configs.thresholdTemp + 1) % TEMP_MAX_VALUE;
}

static inline void increment_config_threshold_luminosity(void) {
  _configs.thresholdLum = (_configs.thresholdLum + 1) % LUM_MAX_VALUE;
}

static inline void toggle_config_alarm_flag(void) {
  _configs.alarmFlag = !_configs.alarmFlag;
}

void reset_sensors_max_min(void);

void flush_configs(uint8_t hours, uint8_t minutes);

void get_measure(uint8_t index, char measure[17]);

static inline void set_mode(uint8_t mode) {
  _mode = mode;
  _mode_has_changed = true;
}

static inline uint8_t get_mode(void) {
  _mode_has_changed = false;
  return _mode;
}

static inline bool mode_has_changed(void) { return _mode_has_changed; }

#endif
