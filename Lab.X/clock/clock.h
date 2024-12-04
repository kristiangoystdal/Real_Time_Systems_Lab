#ifndef __CLOCK_H
#define __CLOCK_H

#include <stdint.h>
#include <stdio.h>

#define SECONDS_MAX_VALUE 60
#define MINUTES_MAX_VALUE 60
#define HOURS_MAX_VALUE 24

typedef struct {
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} clock_t;

clock_t _clock;

void set_clock(uint8_t hours, uint8_t minutes, uint8_t seconds);

void increment_clock(void);

static inline void increment_seconds() {
  _clock.seconds = (_clock.seconds + 1)%SECONDS_MAX_VALUE;
}

static inline void increment_minutes() {
  _clock.minutes = (_clock.minutes + 1)%MINUTES_MAX_VALUE;
}

static inline void increment_hours() {
  _clock.hours = (_clock.hours + 1)%HOURS_MAX_VALUE;
}

static inline clock_t get_clock(void) { return _clock; }

static inline uint8_t get_clock_hours(void) { return _clock.hours; }

static inline uint8_t get_clock_minutes(void) { return _clock.minutes; }

static inline void get_clock_str(char clock[9]) {
  sprintf(clock, "%02u:%02u:%02u", _clock.hours, _clock.minutes, _clock.seconds);
}

#endif
