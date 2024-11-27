
#include "normal_mode.h"
#include "configuration_mode.h"
#include "../clock/clock.h"
#include "../controller/LCD/lcd.h"

static uint8_t s2_state; 

void normal_mode_initialization() {
  char clock [9];
  get_clock(HOURS_MINUTES_AND_SECONDS, clock);
  s2_state = S2_NORMAL_MODE;
}

void normal_mode_timer_handler() {

}

void normal_mode_s1_handler() {
  configuration_mode_initialization();
}

void normal_mode_s2_handler() {
  s2_state = (s2_state + 1)%(S2_LUM_MODE+1);
  switch (s2_state) {
    case S2_TEMP_MODE:
      break;
    case S2_LUM_MODE:
      break;
    default: // S2_NORMAL_MODE
      break;
  }
}
