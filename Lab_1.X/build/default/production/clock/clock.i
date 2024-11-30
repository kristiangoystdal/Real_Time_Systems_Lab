# 1 "clock/clock.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "clock/clock.c" 2

# 1 "clock/clock.h" 1



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdint.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\musl_xc8.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdint.h" 2 3
# 26 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 133 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned short uintptr_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef short intptr_t;
# 164 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 194 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 235 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 27 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "C:\\Program Files\\Microchip\\xc8\\v2.50\\pic\\include\\c99\\stdint.h" 2 3
# 4 "clock/clock.h" 2
# 20 "clock/clock.h"
void set_clock(uint8_t hours, uint8_t minutes, uint8_t seconds);

uint8_t increment_clock(void);

uint8_t increment_seconds(void);

uint8_t increment_minutes(void);

uint8_t increment_hours(void);

uint8_t get_clock(uint8_t precision, char clock[9]);
# 2 "clock/clock.c" 2


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
  if(_seconds < 60)
    return 0;

  _seconds = 0;
  _minutes ++;
  if(_minutes < 60)
    return 3;

  _minutes = 0;
  _hours ++;
  if(_hours >= 24)
    _hours = 0;

  return 4;
}

uint8_t increment_seconds() {
  _seconds ++;
  if(_seconds >= 60)
    _seconds = 0;
  return 0;
}

uint8_t increment_minutes() {
  _minutes = (_minutes + 1);
  if(_minutes >= 60)
    _minutes = 0;
  return 1;
}

uint8_t increment_hours() {
  _hours ++;
  if(_hours >= 24)
    _hours = 0;
  return 2;
}

uint8_t get_clock(uint8_t precision, char clock[9]) {
  switch (precision) {
    case 0:
      clock[0] = 0x30 + _seconds/10;
      clock[1] = 0x30 + (_seconds%10);
      clock[2] = '\0';
      return 0;
    case 1:
      clock[0] = 0x30 + _minutes/10;
      clock[1] = 0x30 + (_minutes%10);
      clock[2] = '\0';
      return 3;
    case 2:
      clock[0] = 0x30 + _hours/10;
      clock[1] = 0x30 + (_hours%10);
      clock[2] = '\0';
      return 6;
    case 3:
      clock[0] = 0x30 + _seconds/10;
      clock[1] = 0x30 + (_seconds%10);
      clock[2] = ':';
      clock[3] = 0x30 + _minutes/10;
      clock[4] = 0x30 + (_minutes%10);
      clock[5] = '\0';
      return 0;
    default:
      clock[0] = 0x30 + _seconds/10;
      clock[1] = 0x30 + (_seconds%10);
      clock[2] = ':';
      clock[3] = 0x30 + _minutes/10;
      clock[4] = 0x30 + (_minutes%10);
      clock[5] = ':';
      clock[6] = 0x30 + _hours/10;
      clock[7] = 0x30 + (_hours%10);
      clock[8] = '\0';
      return 0;
  }
}
