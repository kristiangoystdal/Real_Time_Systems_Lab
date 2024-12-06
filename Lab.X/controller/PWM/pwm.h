#ifndef __PWM_H
#define __PWM_H

#include "stdbool.h"

void activate_pwm(void);
void deactivate_pwm(void);
void decrement_pwm_cnt(void);
bool get_pwm_en(void);

#endif