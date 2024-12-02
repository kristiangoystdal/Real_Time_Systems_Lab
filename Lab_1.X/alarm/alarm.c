
#include "alarm.h"
#include "../state/state.h"

bool check_clock_alarm(clock_t clock) {
  if(get_config_alarm_flag() == false)
    return false;

  uint8_t alarm_hours = get_config_alarm_hours();
  uint8_t alarm_minutes = get_config_alarm_minutes();
  uint8_t alarm_seconds = get_config_alarm_seconds();
  if(clock.hours > alarm_hours)
    return true;
  else if(clock.hours == alarm_hours) {
    if(clock.minutes > alarm_minutes)
      return true;
    else if(clock.minutes == alarm_minutes) {
      if(clock.seconds >= alarm_seconds)
        return true;
    }
  }
  return false;
}

bool check_lum_alarm(uint8_t lum) {
  if(get_config_alarm_flag() == false)
    return false;

  uint8_t threshold_lum = get_config_threshold_luminosity();
  if(lum >= threshold_lum)
    return true;

  return false;
}

bool check_temp_alarm(uint8_t temp) {
  if(get_config_alarm_flag() == false)
    return false;

  uint8_t threshold_temp = get_config_threshold_temperature();
  if(temp >= threshold_temp)
    return true;

  return false;
}
