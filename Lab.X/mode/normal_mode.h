#ifndef __NORMAL_MODE_H
#define __NORMAL_MODE_H

#include "stdbool.h"

#define S2_NORMAL_MODE 0
#define S2_TEMP_MODE 1
#define S2_LUM_MODE 2

void normal_mode_initialization(void);
void normal_mode_timer_handler(void);
void normal_mode_s1_handler(void);
void normal_mode_s2_handler(void);
bool get_pwm_en(void);

#endif
