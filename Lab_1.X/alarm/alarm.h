#ifndef __ALARM_H
#define __ALARM_H

#include "../clock/clock.h"
#include "stdbool.h"

bool check_clock_alarm(clock_t clock);

bool check_lum_alarm(uint8_t lum);

bool check_temp_alarm(uint8_t temp);

void set_alarm_triggered(bool value);

bool get_alarm_triggered(void);

void clear_alarm();

#endif
