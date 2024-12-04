
#include "button.h"
#include "../../mcc_generated_files/mcc.h"

static uint8_t btn1_state = NOT_PRESSED;
static uint8_t btn2_state = NOT_PRESSED;

bool checkButtonS1(void) {
  if (btn1_state == NOT_PRESSED) {
    if (BTN_1_PORT == LOW) {
      __delay_ms(1);
      btn1_state = PRESSED;
    }
  } else if (BTN_1_PORT == HIGH) {
    btn1_state = NOT_PRESSED;
    return true;
  }
  return false;
}

bool checkButtonS2(void) {
  if (btn2_state == NOT_PRESSED) {
    if (BTN_2_PORT == LOW) {
      __delay_ms(1);
      btn2_state = PRESSED;
    }
  } else if (BTN_2_PORT == HIGH) {
    btn2_state = NOT_PRESSED;
    return true;
  }
  return false;
}
