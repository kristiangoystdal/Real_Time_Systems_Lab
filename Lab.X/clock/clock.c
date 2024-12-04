
#include "clock.h"
#include "../state/state.h"

void set_clock(uint8_t hours, uint8_t minutes, uint8_t seconds) {
  _clock.hours = hours;
  _clock.minutes = minutes;
  _clock.seconds = seconds;
}

void increment_clock() {
  _clock.seconds++;
  if (_clock.seconds < SECONDS_MAX_VALUE)
    return;

  _clock.seconds = 0;
  _clock.minutes++;
  if (_clock.minutes < MINUTES_MAX_VALUE){
      Configs configs = get_configs();
      configs.clockMinutes = _clock.minutes;
      set_configs(configs, true);
      return;
  }

  _clock.minutes = 0;
  _clock.hours++;
  if (_clock.hours >= HOURS_MAX_VALUE)
      _clock.hours = 0;
  Configs configs = get_configs();
  configs.clockMinutes = _clock.minutes;
  configs.clockHours = _clock.hours;
  set_configs(configs, true);
  return;
}
