
#include "configuration_mode.h"
#include "../clock/clock.h"
#include "../controller/LCD/lcd.h"
#include "../controller/LED/led.h"
#include "../mcc_generated_files/tmr0.h"
#include "../state/state.h"

static uint8_t _cursor;
static uint8_t _cursor_pos_l;
static uint8_t _cursor_pos_c;

void init_lcd_configuration_mode() {
  char clock_alarm[9];
  get_config_alarm_time_str(clock_alarm);
  LCDWriteStr(clock_alarm, LINE_CLOCK_HOURS, COLUMN_CLOCK_HOURS0);

  if (get_config_alarm_flag() == true) {
    LCDWriteStr("CTL AR", LINE_ALARM_C, COLUMN_ALARM_C);
  } else {
    LCDWriteStr("CTL aR", LINE_ALARM_C, COLUMN_ALARM_C);
  }

  char temperature[3];
  get_config_threshold_temperature_str(temperature);
  LCDWriteStr(temperature, LINE_TEMP, COLUMN_TEMP0);
  LCDWriteChar('C', LINE_TEMP_C, COLUMN_TEMP_C);

  char luminosity[2];
  get_config_threshold_luminosity_str(luminosity);
  LCDWriteChar('L', LINE_LUM_L, COLUMN_LUM_L);
  LCDWriteChar(luminosity[0], LINE_LUM, COLUMN_LUM);

  LCDpos(_cursor_pos_l, _cursor_pos_c);
}

void configuration_mode_initialization() {
  // TODO: Disable Timer IRQ
  TMR0_StopTimer();
  // TODO: Set Interrupts
  turn_off_all();
  // toggle(2)
  _cursor = CURSOR_CLOCK_HOURS;
  _cursor_pos_l = LINE_CLOCK_HOURS;
  _cursor_pos_c = COLUMN_CLOCK_HOURS1;
  init_lcd_configuration_mode();
}

void configuration_mode_s1_handler() {
  char buf[9];
  switch (_cursor) {
  case CURSOR_CLOCK_HOURS:
    _cursor = CURSOR_CLOCK_MINUTES;
    _cursor_pos_l = LINE_CLOCK_MINUTES;
    _cursor_pos_c = COLUMN_CLOCK_MINUTES1;
    break;
  case CURSOR_CLOCK_MINUTES:
    _cursor = CURSOR_CLOCK_SECONDS;
    _cursor_pos_l = LINE_CLOCK_SECONDS;
    _cursor_pos_c = COLUMN_CLOCK_SECONDS1;
    break;
  case CURSOR_CLOCK_SECONDS:
    _cursor = CURSOR_ALARM_C;
    _cursor_pos_l = LINE_ALARM_C;
    _cursor_pos_c = COLUMN_ALARM_C;
    break;
  case CURSOR_ALARM_C:
    _cursor = CURSOR_ALARM_T;
    _cursor_pos_l = LINE_ALARM_T;
    _cursor_pos_c = COLUMN_ALARM_T;
    break;
  case CURSOR_ALARM_HOURS:
    _cursor = CURSOR_CLOCK_MINUTES;
    _cursor_pos_l = LINE_CLOCK_MINUTES;
    _cursor_pos_c = COLUMN_CLOCK_MINUTES1;
    break;
  case CURSOR_ALARM_MINUTES:
    _cursor = CURSOR_ALARM_SECONDS;
    _cursor_pos_l = LINE_CLOCK_SECONDS;
    _cursor_pos_c = COLUMN_CLOCK_SECONDS1;
    break;
  case CURSOR_ALARM_SECONDS:
    get_clock_str(HOURS_MINUTES_AND_SECONDS, buf);
    LCDWriteStr(buf, LINE_CLOCK_HOURS, COLUMN_CLOCK_HOURS0);
    _cursor = CURSOR_ALARM_T;
    _cursor_pos_l = LINE_ALARM_T;
    _cursor_pos_c = COLUMN_ALARM_T;
    break;
  case CURSOR_ALARM_T:
    _cursor = CURSOR_ALARM_L;
    _cursor_pos_l = LINE_ALARM_L;
    _cursor_pos_c = COLUMN_ALARM_L;
    break;
  case CURSOR_ALARM_TEMP:
    _cursor = CURSOR_ALARM_L;
    _cursor_pos_l = LINE_ALARM_L;
    _cursor_pos_c = COLUMN_ALARM_L;
    break;
  case CURSOR_ALARM_L:
    _cursor = CURSOR_ALARM_ENABLE;
    _cursor_pos_l = LINE_ALARM_ENABLE;
    _cursor_pos_c = COLUMN_ALARM_ENABLE;
    break;
  case CURSOR_ALARM_LUM:
    _cursor = CURSOR_ALARM_ENABLE;
    _cursor_pos_l = LINE_ALARM_ENABLE;
    _cursor_pos_c = COLUMN_ALARM_ENABLE;
    break;
  case CURSOR_ALARM_ENABLE:
    _cursor = CURSOR_RESET_MAX_MIN;
    _cursor_pos_l = LINE_RESET_MAX_MIN;
    _cursor_pos_c = COLUMN_RESET_MAX_MIN;
    break;
  case CURSOR_RESET_MAX_MIN:
    _cursor = CURSOR_NORMAL_MODE;
    _cursor_pos_l = LINE_RESET_MAX_MIN;
    _cursor_pos_c = COLUMN_RESET_MAX_MIN;
    break;
  default: // CURSOR_NORMAL_MODE
    flush_configs(get_clock_hours(), get_clock_minutes());
    set_mode(NORMAL_MODE);
    break;
  }
  LCDpos(_cursor_pos_l, _cursor_pos_c);
}

void configuration_mode_s2_handler() {
  char buf[9];
  uint8_t column;
  switch (_cursor) {
  case CURSOR_CLOCK_HOURS:
    column = get_clock_str(increment_hours(), buf);
    LCDWriteStr(buf, LINE_CLOCK_HOURS, column);
    break;
  case CURSOR_CLOCK_MINUTES:
    column = get_clock_str(increment_minutes(), buf);
    LCDWriteStr(buf, LINE_CLOCK_HOURS, column);
    break;
  case CURSOR_CLOCK_SECONDS:
    column = get_clock_str(increment_seconds(), buf);
    LCDWriteStr(buf, LINE_CLOCK_HOURS, column);
    break;
  case CURSOR_ALARM_C:
    get_config_alarm_time_str(buf);
    LCDWriteStr(buf, LINE_CLOCK_HOURS, COLUMN_CLOCK_HOURS0);
    _cursor = CURSOR_CLOCK_HOURS;
    _cursor_pos_l = LINE_CLOCK_HOURS;
    _cursor_pos_c = COLUMN_CLOCK_HOURS1;
    LCDpos(_cursor_pos_l, _cursor_pos_c);
    break;
  case CURSOR_ALARM_HOURS:
    increment_config_alarm_hours();
    get_config_alarm_hours_str(buf);
    LCDWriteStr(buf, LINE_CLOCK_HOURS, COLUMN_CLOCK_HOURS0);
    break;
  case CURSOR_ALARM_MINUTES:
    increment_config_alarm_minutes();
    get_config_alarm_minutes_str(buf);
    LCDWriteStr(buf, LINE_CLOCK_MINUTES, COLUMN_CLOCK_MINUTES0);
    break;
  case CURSOR_ALARM_SECONDS:
    increment_config_alarm_seconds();
    get_config_alarm_seconds_str(buf);
    LCDWriteStr(buf, LINE_CLOCK_SECONDS, COLUMN_CLOCK_SECONDS0);
    break;
  case CURSOR_ALARM_T:
    _cursor = CURSOR_ALARM_TEMP;
    _cursor_pos_l = LINE_TEMP;
    _cursor_pos_c = COLUMN_TEMP1;
    LCDpos(_cursor_pos_l, _cursor_pos_c);
    break;
  case CURSOR_ALARM_TEMP:
    increment_config_threshold_temperature();
    get_config_threshold_temperature_str(buf);
    LCDWriteStr(buf, LINE_TEMP, COLUMN_TEMP0);
    break;
  case CURSOR_ALARM_L:
    _cursor = CURSOR_ALARM_LUM;
    _cursor_pos_l = LINE_ALARM_L;
    _cursor_pos_c = COLUMN_ALARM_L;
    LCDpos(_cursor_pos_l, _cursor_pos_c);
    break;
  case CURSOR_ALARM_LUM:
    increment_config_threshold_luminosity();
    get_config_threshold_luminosity_str(buf);
    LCDWriteStr(buf, LINE_LUM, COLUMN_LUM);
    break;
  case CURSOR_ALARM_ENABLE:
    toggle_config_alarm_flag();
    buf[0] = get_config_alarm_flag() ? 'A' : 'a';
    LCDWriteChar(buf[0], LINE_ALARM_ENABLE, COLUMN_ALARM_ENABLE);
    break;
  case CURSOR_RESET_MAX_MIN:
    reset_sensors_max_min();
    break;
  default: // CURSOR_NORMAL_MODE
    break;
  }
}
