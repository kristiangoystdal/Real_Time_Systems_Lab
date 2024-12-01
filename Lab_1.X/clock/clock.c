
#include "clock.h"

#include <stdio.h>

static clock_t _clock;

void set_clock(uint8_t hours, uint8_t minutes, uint8_t seconds) {
  _clock.hours = hours;
  _clock.minutes = minutes;
  _clock.seconds = seconds;
}

uint8_t increment_clock() {
  _clock.seconds ++;
  if(_clock.seconds < SECONDS_MAX_VALUE)
    return ONLY_SECONDS;

  _clock.seconds = 0;
  _clock.minutes ++;
  if(_clock.minutes < MINUTES_MAX_VALUE)
    return ONLY_MINUTES_AND_SECONDS;

  _clock.minutes = 0;
  _clock.hours ++;
  if(_clock.hours >= HOURS_MAX_VALUE)
    _clock.hours = 0;
 
  return HOURS_MINUTES_AND_SECONDS;
}

uint8_t increment_seconds() {
  _clock.seconds ++;
  if(_clock.seconds >= SECONDS_MAX_VALUE)
    _clock.seconds = 0;
  return ONLY_SECONDS;
}

uint8_t increment_minutes() {
  _clock.minutes = (_clock.minutes + 1);
  if(_clock.minutes >= MINUTES_MAX_VALUE)
    _clock.minutes = 0;
  return ONLY_MINUTES;
}

uint8_t increment_hours() {
  _clock.hours ++;
  if(_clock.hours >= HOURS_MAX_VALUE)
    _clock.hours = 0;
  return ONLY_HOURS;
}

clock_t get_clock(void) {
  return _clock;
}

uint8_t get_clock_str(uint8_t precision, char clock[9]) {
  switch (precision) {
    case ONLY_SECONDS:
      sprintf(clock, "%02u", _clock.seconds);
      return SECONDS_POSITION;
    case ONLY_MINUTES:
      sprintf(clock, "%02u", _clock.minutes);
      return MINUTES_POSITION;
    case ONLY_HOURS:
      sprintf(clock, "%02u", _clock.hours);
      return HOURS_POSITION;
    case ONLY_MINUTES_AND_SECONDS:
      sprintf(clock, "%02u:%02u", _clock.seconds, _clock.minutes);
      return SECONDS_POSITION;
    default: // HOURS_MINUTES_AND_SECONDS
      sprintf(clock, "%02u:%02u:%02u", _clock.seconds, _clock.minutes, _clock.hours);
      return SECONDS_POSITION;
  }
}
