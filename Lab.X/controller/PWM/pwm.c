
#include "pwm.h"
#include "../../mcc_generated_files/mcc.h"
#include "../../mcc_generated_files/tmr2.h"
#include "../../state/state.h"
#include "../LED/led.h"


static uint8_t _pwm_cnt;
static bool _pwm_en;

void set_PWM(bool on) {
  PPSLOCK = 0x55;
  PPSLOCK = 0xAA;
  PPSLOCK = 0x00; // unlock PPS

  if (on) {
    RA6PPS = 0x0E;
  } else {
    RA6PPS = 0x00;
  }

  PPSLOCK = 0x55;
  PPSLOCK = 0xAA;
  PPSLOCK = 0x01; // lock PPS
}

void activate_pwm() {
  if (_pwm_en == false) {
    turn_off(2);
    set_PWM(true);
    TMR2_StartTimer();
  }
  _pwm_en = true;
  _pwm_cnt = get_config_alarm_duration();
}

void deactivate_pwm() {
  _pwm_en = false;
  _pwm_cnt = get_config_alarm_duration();
  TMR2_StopTimer();
}

void decrement_pwm_cnt() {
  if (_pwm_cnt == 0) {
    _pwm_cnt = get_config_alarm_duration();
    _pwm_en = false;
    TMR2_StopTimer();
    set_PWM(false);
    turn_on(2);
  }
  if (_pwm_en)
    _pwm_cnt--;
}

bool get_pwm_en(void) { return _pwm_en; }