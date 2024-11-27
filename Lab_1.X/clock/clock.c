
#include "clock.h"

static uint8_t _hours = 0;
static uint8_t _minutes = 0;
static uint8_t _seconds = 0;

void set_clock(uint8_t hours, uint8_t minutes, uint8_t seconds) {
  _hours = hours;
  _minutes = minutes;
  _seconds = seconds;
}

uint8_t increment_clock() {
  _seconds ++;
  if(_seconds < SECONDS_MAX_VALUE)
    return ONLY_SECONDS;

  _seconds = 0;
  _minutes ++;
  if(_minutes < MINUTES_MAX_VALUE)
    return ONLY_MINUTES_AND_SECONDS;

  _minutes = 0;
  _hours ++;
  if(_hours >= HOURS_MAX_VALUE)
    _hours = 0;
 
  return HOURS_MINUTES_AND_SECONDS;
}

uint8_t increment_seconds() {
  _seconds ++;
  if(_seconds >= SECONDS_MAX_VALUE)
    _seconds = 0;
  return ONLY_SECONDS;
}

uint8_t increment_minutes() {
  _minutes = (_minutes + 1);
  if(_minutes >= MINUTES_MAX_VALUE)
    _minutes = 0;
  return ONLY_MINUTES;
}

uint8_t increment_hours() {
  _hours ++;
  if(_hours >= HOURS_MAX_VALUE)
    _hours = 0;
  return ONLY_HOURS;
}

uint8_t get_clock(uint8_t precision, char clock[9]) {
  switch (precision) {
    case ONLY_SECONDS:
      clock[0] = 0x30 + _seconds/10;
      clock[1] = 0x30 + (_seconds%10);
      clock[2] = '\0';
      return SECONDS_POSITION;
    case ONLY_MINUTES:
      clock[0] = 0x30 + _minutes/10;
      clock[1] = 0x30 + (_minutes%10);
      clock[2] = '\0';
      return MINUTES_POSITION;
    case ONLY_HOURS:
      clock[0] = 0x30 + _hours/10;
      clock[1] = 0x30 + (_hours%10);
      clock[2] = '\0';
      return HOURS_POSITION;
    case ONLY_MINUTES_AND_SECONDS:
      clock[0] = 0x30 + _seconds/10;
      clock[1] = 0x30 + (_seconds%10);
      clock[2] = ':';
      clock[3] = 0x30 + _minutes/10;
      clock[4] = 0x30 + (_minutes%10);
      clock[5] = '\0';
      return SECONDS_POSITION;
    default: // HOURS_MINUTES_AND_SECONDS
      clock[0] = 0x30 + _seconds/10;
      clock[1] = 0x30 + (_seconds%10);
      clock[2] = ':';
      clock[3] = 0x30 + _minutes/10;
      clock[4] = 0x30 + (_minutes%10);
      clock[5] = ':';
      clock[6] = 0x30 + _hours/10;
      clock[7] = 0x30 + (_hours%10);
      clock[8] = '\0';
      return SECONDS_POSITION;
  }
}
