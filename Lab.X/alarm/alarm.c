
#include "alarm.h"
#include "../controller/LCD/lcd.h"
#include "../state/state.h"
#include <stdbool.h>

bool alarm_triggered = false;

bool check_clock_alarm(clock_t clock) {
  if (get_config_alarm_flag() == false)
    return false;

  uint8_t alarm_hours = get_config_alarm_hours();
  uint8_t alarm_minutes = get_config_alarm_minutes();
  uint8_t alarm_seconds = get_config_alarm_seconds();
  if (clock.hours == alarm_hours && clock.minutes == alarm_minutes &&
      clock.seconds == alarm_seconds) {
    return true;
  }
  return false;
}

bool check_lum_alarm(uint8_t lum) {
  if (get_config_alarm_flag() == false)
    return false;

  uint8_t threshold_lum = get_config_threshold_luminosity();
  if (lum > threshold_lum)
    return true;

  return false;
}

bool check_temp_alarm(uint8_t temp) {
  if (get_config_alarm_flag() == false)
    return false;

  uint8_t threshold_temp = get_config_threshold_temperature();
  if (temp > threshold_temp)
    return true;

  return false;
}

void set_alarm_triggered(bool value) { alarm_triggered = value; }

bool get_alarm_triggered(void) { return alarm_triggered; }

void clear_alarm() { LCDWriteStr("   ", LINE_ALARM_C, COLUMN_ALARM_C); }