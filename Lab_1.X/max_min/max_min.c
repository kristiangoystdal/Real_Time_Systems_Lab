
#include "max_min.h"
#include "../state/state.h"

void update_max_min_temperature(uint8_t temp) {
  SensorsMaxMin sensorsMaxMin = get_max_min();
  if(temp > sensorsMaxMin.maxTemp[MAX_MIN_TEMP_BYTE]) {
    sensorsMaxMin.maxTemp[MAX_MIN_TEMP_BYTE] = temp;
    set_max_min(sensorsMaxMin, true);
  } else if (temp < sensorsMaxMin.minTemp[MAX_MIN_TEMP_BYTE]) {
    sensorsMaxMin.minTemp[MAX_MIN_TEMP_BYTE] = temp;
    set_max_min(sensorsMaxMin, true);
  }
}

void update_max_min_luminosity(uint8_t lum) {
  SensorsMaxMin sensorsMaxMin = get_max_min();
  if(lum > sensorsMaxMin.maxLum[MAX_MIN_LUM_BYTE]) {
    sensorsMaxMin.maxLum[MAX_MIN_LUM_BYTE] = lum;
    set_max_min(sensorsMaxMin, true);
  } else if (lum < sensorsMaxMin.minLum[MAX_MIN_LUM_BYTE]) {
    sensorsMaxMin.minLum[MAX_MIN_LUM_BYTE] = lum;
    set_max_min(sensorsMaxMin, true);
  }
}