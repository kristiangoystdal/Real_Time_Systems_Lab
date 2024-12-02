#ifndef __CLOCK_H
#define __CLOCK_H

#include <stdint.h>

#define ONLY_SECONDS 0
#define ONLY_MINUTES 1
#define ONLY_HOURS 2
#define ONLY_MINUTES_AND_SECONDS 3
#define HOURS_MINUTES_AND_SECONDS 4

#define SECONDS_MAX_VALUE 60
#define MINUTES_MAX_VALUE 60
#define HOURS_MAX_VALUE 24

#define SECONDS_POSITION 0
#define MINUTES_POSITION 3
#define HOURS_POSITION 6

void set_clock(uint8_t hours, uint8_t minutes, uint8_t seconds);

uint8_t increment_clock();

uint8_t increment_seconds();

uint8_t increment_minutes();

uint8_t increment_hours();

uint8_t get_clock(uint8_t precision, char* clock);

#endif
