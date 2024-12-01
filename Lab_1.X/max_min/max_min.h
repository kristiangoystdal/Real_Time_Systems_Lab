#ifndef __MAX_MIN_H
#define __MAX_MIN_H

#include <stdint.h>
#include "../clock/clock.h"

void update_max_min_temperature(clock_t clock, uint8_t lum, uint8_t temp);

void update_max_min_luminosity(clock_t clock, uint8_t lum, uint8_t temp);

#endif
