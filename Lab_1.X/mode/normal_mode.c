
#include "normal_mode.h"
#include "../clock/clock.h"
#include "../controller/LCD/lcd.h"
#include "../controller/LED/led.h"
#include "../controller/Luminosity/luminosity.h"
#include "../controller/Temperature/temperature.h"
#include "../state/state.h"
#include <stdio.h>

static uint8_t _s2_state;

void normal_mode_initialization() {
  LCDinit();

  char clock[9];
  get_clock(HOURS_MINUTES_AND_SECONDS, clock);
  _s2_state = S2_NORMAL_MODE;
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
