
#include "led.h"
#include "../../mcc_generated_files/mcc.h"

void turn_on(uint8_t n) {
  if (n == 0) {
    IO_RA4_SetHigh();
  } else if (n == 1) {
    IO_RA5_SetHigh();
  } else if (n == 2) {
    IO_RA6_SetHigh();
  } else if (n == 3) {
    IO_RA7_SetHigh();
  }
}

void turn_off(uint8_t n) {
  if (n == 0) {
    IO_RA4_SetLow();
  } else if (n == 1) {
    IO_RA5_SetLow();
  } else if (n == 2) {
    IO_RA6_SetLow();
  } else if (n == 3) {
    IO_RA7_SetLow();
  }
}

void turn_off_all(void) {
  IO_RA4_SetLow();
  IO_RA5_SetLow();
  IO_RA6_SetLow();
  IO_RA7_SetLow();
}

void toggle(uint8_t n) {
  if (n == 0) {
    IO_RA4_Toggle();
  } else if (n == 1) {
    IO_RA5_Toggle();
  } else if (n == 2) {
    IO_RA6_Toggle();
  } else if (n == 3) {
    IO_RA7_Toggle();
  }
}
