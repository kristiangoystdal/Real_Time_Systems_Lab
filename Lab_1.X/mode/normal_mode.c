
#include "normal_mode.h"
#include "../clock/clock.h"
#include "../controller/LCD/lcd.h"
#include "../controller/LED/led.h"
#include "../controller/Luminosity/luminosity.h"
#include "../controller/Temperature/temperature.h"
#include "../state/state.h"
#include <stdio.h>

static uint8_t _s2_state;
static uint8_t _sensor_cnt;

void normal_mode_initialization() {
  // TODO: Create and Initializa Max/Min and Alarm Modules
  set_clock(get_config_clock_hours(), get_config_clock_minutes(), 0);

  char clock[9];
  get_clock(HOURS_MINUTES_AND_SECONDS, clock);
  _s2_state = S2_NORMAL_MODE;
  _sensor_cnt = 3;
  turn_on(1);

  char luminosity[4];
  get_luminosity(luminosity);

  char temperature[4];
  get_temperature(temperature);

  LCDWriteStr("clock", 0, 0);
  // LCDWriteStr("CTL AR", 0, 10);
  // LCDWriteStr(temperature, 1, 0);
  // LCDWriteStr(luminosity, 1, 13);
}

void normal_mode_timer_handler() {
  toggle(0);
  uint8_t precision = increment_clock();
  char clock [9];
  uint8_t clock_pos = get_clock(precision, clock);
  LCDWriteStr(clock, 0, clock_pos);
  _sensor_cnt --;
  if(_sensor_cnt == 0) {
    _sensor_cnt = 3;
    uint8_t lum = readLum();
    uint8_t temp = readTemperature();
    char luminosity[4];
    luminosity_to_string(luminosity, lum);
    char temperature[4];
    temperature_to_string(temperature, temp);
    // LCDWriteStr(temperature, 1, 0);
    // LCDWriteStr(luminosity, 1, 13);
  }
  toggle(1);
  toggle(2);
  printf("Timer1 interrupt triggered!\n");
}

void normal_mode_s1_handler() { set_mode(CONFIGURATION_MODE); }

void normal_mode_s2_handler() {
  _s2_state = (_s2_state + 1) % (S2_LUM_MODE + 1);
  switch (_s2_state) {
  case S2_TEMP_MODE:
    break;
  case S2_LUM_MODE:
    break;
  default: // S2_NORMAL_MODE
    break;
  }
}
