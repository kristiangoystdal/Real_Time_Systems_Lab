
#include "normal_mode.h"
#include "../clock/clock.h"
#include "../controller/LCD/lcd.h"
#include "../controller/LED/led.h"
#include "../controller/Luminosity/luminosity.h"
#include "../controller/Temperature/temperature.h"
#include "../max_min/max_min.h"
#include "../state/state.h"
#include "../alarm/alarm.h"
#include <stdio.h>

static uint8_t _s2_state;
static uint8_t _sensor_cnt;
static uint8_t _pwm_cnt;
static bool _pwm_en;

void normal_mode_initialization() {
  set_clock(get_config_clock_hours(), get_config_clock_minutes(), 0);

  char clock[9];
  get_clock_str(HOURS_MINUTES_AND_SECONDS, clock);

  _s2_state = S2_NORMAL_MODE;
  _sensor_cnt = get_config_monitoring_period();
  _pwm_cnt = get_config_alarm_duration();
  _pwm_en = false;

  turn_off_all();
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

void update_clock(void) {
  uint8_t precision = increment_clock();
  char clock [9];
  uint8_t clock_pos = get_clock_str(precision, clock);
  LCDWriteStr(clock, 0, clock_pos);
  if(check_clock_alarm(get_clock())) {
    // TODO: Turn on PWM
    _pwm_en = true;
    // LCDWriteStr("C", 0, 10);
  }
}

void update_sensors(void) {
  uint8_t lum = readLum();
  uint8_t temp = readTemperature();
  update_max_min_luminosity(lum);
  update_max_min_temperature(temp);
  char luminosity[4];
  luminosity_to_string(luminosity, lum);
  char temperature[4];
  temperature_to_string(temperature, temp);
  // LCDWriteStr(temperature, 1, 0);
  // LCDWriteStr(luminosity, 1, 13);
  if(check_lum_alarm(lum)) {
    // TODO: Turn on PWM
    _pwm_en = true;
    turn_on(3);
    // LCDWriteStr("L", 0, 12);
  }
  if(check_temp_alarm(temp)) {
    // TODO: Turn on PWM
    _pwm_en = true;
    turn_on(2);
    // LCDWriteStr("T", 0, 11);
  }
}

void normal_mode_timer_handler() {
  toggle(0);
  update_clock();
  _sensor_cnt --;
  if(_sensor_cnt == 0) {
    _sensor_cnt = 3;
    update_sensors();
  }
  if(_pwm_en) {
    _pwm_cnt --;
  }
  if(_pwm_cnt == 0) {
    _pwm_cnt = 5;
    _pwm_en = false;
    // TODO: Disable PWM
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
