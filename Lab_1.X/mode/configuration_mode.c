
#include "configuration_mode.h"
#include "../controller/LED/led.h"
#include "../controller/LCD/lcd.h"
#include "../state/state.h"

void init_lcd_configuration_mode() {
  char clock_alarm [9];
  get_config_alarm_time_str(clock_alarm);
  LCDWriteStr(clock_alarm, 0, 0);

  if(get_config_alarm_flag() == true)
    LCDWriteStr("CTL AR", 0, 10);
  else
    LCDWriteStr("CTL aR", 0, 10);

  char temperature[3];
  get_config_threshold_temperature_str(temperature);
  LCDWriteStr(temperature, 1, 0);
  LCDWriteChar('C', 1, 3);

  char luminosity[2];
  get_config_threshold_luminosity_str(luminosity);
  LCDWriteChar('L', 1, 13);
  LCDWriteChar(luminosity[0], 1, 15);
}

void configuration_mode_initialization() {
  // TODO: Disable Timer IRQ
  turn_off_all();
  // toggle(2)
  init_lcd_configuration_mode();
}

void configuration_mode_s1_handler() {}

void configuration_mode_s2_handler() {}
