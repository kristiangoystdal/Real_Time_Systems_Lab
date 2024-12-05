#ifndef __MAX_MIN_H
#define __MAX_MIN_H

#include "../clock/clock.h"
#include <stdint.h>
#include <stdbool.h>


void update_max_min_temperature(clock_t clock, uint8_t lum, uint8_t temp);

void update_max_min_luminosity(clock_t clock, uint8_t lum, uint8_t temp);

bool check_lum_zeros();

#endif
