#ifndef __CONFIGURATION_MODE_H
#define __CONFIGURATION_MODE_H

#define CURSOR_CLOCK_HOURS 0
#define CURSOR_CLOCK_MINUTES 1
#define CURSOR_CLOCK_SECONDS 2
#define CURSOR_ALARM_C 3
#define CURSOR_ALARM_HOURS 4
#define CURSOR_ALARM_MINUTES 5
#define CURSOR_ALARM_SECONDS 6
#define CURSOR_ALARM_T 7
#define CURSOR_ALARM_TEMP 8
#define CURSOR_ALARM_L 9
#define CURSOR_ALARM_LUM 10
#define CURSOR_ALARM_ENABLE 11
#define CURSOR_RESET_MAX_MIN 12
#define CURSOR_NORMAL_MODE 13

void configuration_mode_initialization(void);
void configuration_mode_timer_handler(void);
void configuration_mode_s1_handler(void);
void configuration_mode_s2_handler(void);

#endif
