
#include "normal_mode.h"
#include "../state/state.h"
#include "../clock/clock.h"
#include "../controller/LCD/lcd.h"
#include "../controller/LED/led.h"

static uint8_t _s2_state; 

void normal_mode_initialization() {
  char clock [9];
  get_clock(HOURS_MINUTES_AND_SECONDS, clock);
  _s2_state = S2_NORMAL_MODE;
  turn_on(2);
}

void normal_mode_timer_handler() {

}

void normal_mode_s1_handler() {
  set_mode(CONFIGURATION_MODE);
}

void normal_mode_s2_handler() {
  _s2_state = (_s2_state + 1)%(S2_LUM_MODE+1);
  switch (_s2_state) {
    case S2_TEMP_MODE:
      break;
    case S2_LUM_MODE:
      break;
    default: // S2_NORMAL_MODE
      break;
  }
}
