
#include "normal_mode.h"
#include "../alarm/alarm.h"
#include "../clock/clock.h"
#include "../controller/LCD/lcd.h"
#include "../controller/LED/led.h"
#include "../controller/Luminosity/luminosity.h"
#include "../controller/Temperature/temperature.h"
#include "../controller/PWM/pwm.h"
#include "../mcc_generated_files/tmr2.h"
#include "../max_min/max_min.h"
#include "../mcc_generated_files/tmr0.h"
#include "../state/state.h"
#include <stdio.h>
#include <string.h>

static uint8_t _s2_state;
static uint8_t _sensor_cnt;
static uint8_t _pwm_cnt;
static bool _pwm_en;
static char _ctl[4];

void init_lcd_normal_mode() {
  char clock[9];
  uint8_t clock_column = get_clock_str(HOURS_MINUTES_AND_SECONDS, clock);
  LCDWriteStr(clock, LINE_CLOCK_HOURS, clock_column);

  LCDWriteStr(_ctl, LINE_ALARM_C, COLUMN_ALARM_C);

  if (get_config_alarm_flag() == true) {
    LCDWriteChar('A', LINE_ALARM_ENABLE, COLUMN_ALARM_ENABLE);
  } else {
    LCDWriteChar('a', LINE_ALARM_ENABLE, COLUMN_ALARM_ENABLE);
  }

  char temperature[3];
  get_temperature(temperature);
  LCDWriteStr(temperature, LINE_TEMP, COLUMN_TEMP0);
  LCDWriteChar('C', LINE_TEMP_C, COLUMN_TEMP_C);

  char luminosity[2];
  get_luminosity(luminosity);
  LCDWriteChar('L', LINE_LUM_L, COLUMN_LUM_L);
  LCDWriteChar(luminosity[0], LINE_LUM, COLUMN_LUM);
}

void normal_mode_initialization() {
  // TODO: Set Interrupts
  // TODO: Enable Timer IRQ
  TMR0_StartTimer();
  set_clock(get_config_clock_hours(), get_config_clock_minutes(), 0);
  printf("Setting clock");
  char clock[9];
  get_clock_str(HOURS_MINUTES_AND_SECONDS, clock);

  _s2_state = S2_NORMAL_MODE;
  _sensor_cnt = get_config_monitoring_period();
  _pwm_cnt = get_config_alarm_duration();
  _pwm_en = false;
  strcpy(_ctl, "   ");

  turn_off_all();
  turn_on(2);

  init_lcd_normal_mode();
}

void update_clock(void) {
  uint8_t precision = increment_clock();
  char clock[9];
  uint8_t clock_column = get_clock_str(precision, clock);
  LCDWriteStr(clock, LINE_CLOCK_HOURS, clock_column);

  if (check_clock_alarm(get_clock())) {
      if(_pwm_en == false){
          turn_off(2);
          set_PWM(true);
          TMR2_StartTimer();
      }
    _pwm_en = true;
    _pwm_cnt = get_config_alarm_duration();
    _ctl[0] = 'C';
    LCDWriteChar('C', LINE_ALARM_C, COLUMN_ALARM_C);
  }
}

void update_sensors(void) {
  uint8_t lum = readLum();
  uint8_t temp = readTemperature();
  clock_t clock = get_clock();
  update_max_min_luminosity(clock, lum, temp);
  update_max_min_temperature(clock, lum, temp);

  char luminosity[2];
  luminosity_to_string(luminosity, lum);
  char temperature[3];
  temperature_to_string(temperature, temp);
  LCDWriteStr(temperature, LINE_TEMP, COLUMN_TEMP0);
  LCDWriteChar(luminosity[0], LINE_LUM, COLUMN_LUM);

  if (check_lum_alarm(lum)) {
      if(_pwm_en == false){
          turn_off(2);
          set_PWM(true);
          TMR2_StartTimer();
      }
    _pwm_en = true;
    _pwm_cnt = get_config_alarm_duration();
    turn_on(0);
    _ctl[2] = 'L';
    LCDWriteChar('L', LINE_ALARM_T, COLUMN_ALARM_L);
  } else {
    turn_off(0);
  }

  if (check_temp_alarm(temp)) {
    if(_pwm_en == false){
        turn_off(2);
        set_PWM(true);
        TMR2_StartTimer();
    }
    _pwm_en = true;
    _pwm_cnt = get_config_alarm_duration();
    turn_on(1);
    _ctl[1] = 'T';
    LCDWriteChar('T', LINE_ALARM_T, COLUMN_ALARM_T);
  } else {
    turn_off(1);
  }
}

void normal_mode_timer_handler() {
  toggle(3);
  update_clock();
  _sensor_cnt--;
  if (_pwm_en)
      _pwm_cnt--;
  if (_sensor_cnt == 0) {
    _sensor_cnt = get_config_monitoring_period();
    update_sensors();
  }
  if (_pwm_cnt == 0) {
    _pwm_cnt = get_config_alarm_duration();
    _pwm_en = false;
    TMR2_StopTimer();
    set_PWM(false);
    turn_on(2);
  }
}

void normal_mode_s1_handler() { set_mode(CONFIGURATION_MODE); }

void normal_mode_s2_handler() {
  // TODO: LEDs?
  char line0[17], line1[17];
  _s2_state = (_s2_state + 1) % (S2_LUM_MODE + 1);
  switch (_s2_state) {
  case S2_TEMP_MODE:
    // TODO: Disable Timer
    TMR0_StopTimer();
    get_measure(MAX_TEMPERATURE, line0);
    get_measure(MIN_TEMPERATURE, line1);
    LCDWriteStr(line0, 0, 0);
    LCDWriteStr(line1, 1, 0);
    break;
  case S2_LUM_MODE:
    get_measure(MAX_LUMINOSITY, line0);
    get_measure(MIN_LUMINOSITY, line1);
    LCDWriteStr(line0, 0, 0);
    LCDWriteStr(line1, 1, 0);
    break;
  default: // S2_NORMAL_MODE
    // TODO: Enable Timer
      TMR0_StartTimer();
      init_lcd_normal_mode();
    break;
  }
}

bool get_pwm_en(void){
    return _pwm_en;
}