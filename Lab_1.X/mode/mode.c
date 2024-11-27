
#include "mode.h"
#include "normal_mode.h"
#include "configuration_mode.h"

void mode_initialization(uint8_t mode) {
  if(mode == NORMAL_MODE) {
    normal_mode_initialization();
    return;
  }
  configuration_mode_initialization();
}

void set_interrupts_handler(uint8_t mode) {
  if(mode == NORMAL_MODE) {
    return;
  }
}