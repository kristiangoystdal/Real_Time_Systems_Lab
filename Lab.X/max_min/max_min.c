
#include "max_min.h"
#include "../state/state.h"

void update_max_min_temperature(clock_t clock, uint8_t lum, uint8_t temp) {
  SensorsMaxMin sensorsMaxMin = get_max_min();
  if(temp > sensorsMaxMin.maxTemp[MAX_MIN_TEMP_BYTE]) {
    sensorsMaxMin.maxTemp[MAX_MIN_SECONDS_BYTE] = clock.seconds;
    sensorsMaxMin.maxTemp[MAX_MIN_MINUTES_BYTE] = clock.minutes;
    sensorsMaxMin.maxTemp[MAX_MIN_HOURS_BYTE] = clock.hours;
    sensorsMaxMin.maxTemp[MAX_MIN_TEMP_BYTE] = temp;
    sensorsMaxMin.maxTemp[MAX_MIN_LUM_BYTE] = lum;
    set_max_min(sensorsMaxMin, true);
  } else if (temp < sensorsMaxMin.minTemp[MAX_MIN_TEMP_BYTE]) {
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
  if(lum > sensorsMaxMin.maxLum[MAX_MIN_LUM_BYTE]) {
    sensorsMaxMin.maxLum[MAX_MIN_SECONDS_BYTE] = clock.seconds;
    sensorsMaxMin.maxLum[MAX_MIN_MINUTES_BYTE] = clock.minutes;
    sensorsMaxMin.maxLum[MAX_MIN_HOURS_BYTE] = clock.hours;
    sensorsMaxMin.maxLum[MAX_MIN_TEMP_BYTE] = temp;
    sensorsMaxMin.maxLum[MAX_MIN_LUM_BYTE] = lum;
    set_max_min(sensorsMaxMin, true);
  } else if (lum < sensorsMaxMin.minLum[MAX_MIN_LUM_BYTE]) {
    sensorsMaxMin.minLum[MAX_MIN_SECONDS_BYTE] = clock.seconds;
    sensorsMaxMin.minLum[MAX_MIN_MINUTES_BYTE] = clock.minutes;
    sensorsMaxMin.minLum[MAX_MIN_HOURS_BYTE] = clock.hours;
    sensorsMaxMin.minLum[MAX_MIN_TEMP_BYTE] = temp;
    sensorsMaxMin.minLum[MAX_MIN_LUM_BYTE] = lum;
    set_max_min(sensorsMaxMin, true);
  }
}