#ifndef __LCD_H
#define __LCD_H

#define LINE_CLOCK_HOURS 0
#define LINE_CLOCK_MINUTES 0
#define LINE_CLOCK_SECONDS 0
#define LINE_ALARM_C 0
#define LINE_ALARM_T 0
#define LINE_ALARM_L 0
#define LINE_ALARM_ENABLE 0
#define LINE_RESET_MAX_MIN 0
#define LINE_TEMP 1
#define LINE_TEMP_C 1
#define LINE_LUM_L 1
#define LINE_LUM 1

#define COLUMN_CLOCK_HOURS0 0
#define COLUMN_CLOCK_HOURS1 1
#define COLUMN_CLOCK_MINUTES0 3
#define COLUMN_CLOCK_MINUTES1 4
#define COLUMN_CLOCK_SECONDS0 6
#define COLUMN_CLOCK_SECONDS1 7
#define COLUMN_ALARM_C 10
#define COLUMN_ALARM_T 11
#define COLUMN_ALARM_L 12
#define COLUMN_ALARM_ENABLE 14
#define COLUMN_RESET_MAX_MIN 15
#define COLUMN_TEMP0 0
#define COLUMN_TEMP1 1
#define COLUMN_TEMP_C 3
#define COLUMN_LUM_L 13
#define COLUMN_LUM 15

void LCDinit(void);

void LCDpos(unsigned char l, unsigned char c);

void LCDWriteChar(unsigned char s, unsigned char l, unsigned char c);

void LCDWriteStr(char *s, unsigned char l, unsigned char c);

void LCDClear(void);

#endif
