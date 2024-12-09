
#include "max_min.h"
#include "../state/state.h"
#include <stdbool.h>

bool check_is_zero(uint8_t v[5]) {
  bool is_zero = true;
  for(uint8_t i = 0; i < 5; i++) {
    is_zero &= (v[i] == 0);
  }
  return is_zero;
}

void update_max_min_temperature(clock_t clock, uint8_t lum, uint8_t temp) {
  SensorsMaxMin sensorsMaxMin = get_max_min();
  if (temp > sensorsMaxMin.maxTemp[MAX_MIN_TEMP_BYTE] || check_is_zero(sensorsMaxMin.maxTemp)) {
    sensorsMaxMin.maxTemp[MAX_MIN_SECONDS_BYTE] = clock.seconds;
    sensorsMaxMin.maxTemp[MAX_MIN_MINUTES_BYTE] = clock.minutes;
    sensorsMaxMin.maxTemp[MAX_MIN_HOURS_BYTE] = clock.hours;
    sensorsMaxMin.maxTemp[MAX_MIN_TEMP_BYTE] = temp;
    sensorsMaxMin.maxTemp[MAX_MIN_LUM_BYTE] = lum;
    set_max_min(sensorsMaxMin, true);
  }

  if (temp < sensorsMaxMin.minTemp[MAX_MIN_TEMP_BYTE]) {
    sensorsMaxMin.minTemp[MAX_MIN_SECONDS_BYTE] = clock.seconds;
    sensorsMaxMin.minTemp[MAX_MIN_MINUTES_BYTE] = clock.minutes;
    sensorsMaxMin.minTemp[MAX_MIN_HOURS_BYTE] = clock.hours;
    sensorsMaxMin.minTemp[MAX_MIN_TEMP_BYTE] = temp;
    sensorsMaxMin.minTemp[MAX_MIN_LUM_BYTE] = lum;
    set_max_min(sensorsMaxMin, true);
  }
}

void update_max_min_luminosity(clock_t clock, uint8_t lum, uint8_t temp) {
  SensorsMaxMin sensorsMaxMin = get_max_min();
  if (lum > sensorsMaxMin.maxLum[MAX_MIN_LUM_BYTE] || check_is_zero(sensorsMaxMin.maxLum)) {
    sensorsMaxMin.maxLum[MAX_MIN_SECONDS_BYTE] = clock.seconds;
    sensorsMaxMin.maxLum[MAX_MIN_MINUTES_BYTE] = clock.minutes;
    sensorsMaxMin.maxLum[MAX_MIN_HOURS_BYTE] = clock.hours;
    sensorsMaxMin.maxLum[MAX_MIN_TEMP_BYTE] = temp;
    sensorsMaxMin.maxLum[MAX_MIN_LUM_BYTE] = lum;
    set_max_min(sensorsMaxMin, true);
  }

  if (lum < sensorsMaxMin.minLum[MAX_MIN_LUM_BYTE]) {
    sensorsMaxMin.minLum[MAX_MIN_SECONDS_BYTE] = clock.seconds;
    sensorsMaxMin.minLum[MAX_MIN_MINUTES_BYTE] = clock.minutes;
    sensorsMaxMin.minLum[MAX_MIN_HOURS_BYTE] = clock.hours;
    sensorsMaxMin.minLum[MAX_MIN_TEMP_BYTE] = temp;
    sensorsMaxMin.minLum[MAX_MIN_LUM_BYTE] = lum;
    set_max_min(sensorsMaxMin, true);
  }
}
