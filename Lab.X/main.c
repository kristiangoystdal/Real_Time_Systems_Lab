/*
 * MAIN Generated Driver File
 *
 * @file main.c
 *
 * @defgroup main MAIN
 *
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
 */

/*
� [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip
    software and any derivatives exclusively with Microchip products.
    You are responsible for complying with 3rd party license terms
    applicable to your use of 3rd party software (including open source
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.?
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR
    THIS SOFTWARE.
*/
#include "alarm/alarm.h"
#include "clock/clock.h"
#include "controller/Button/button.h"
#include "controller/EEPROM/EEPROM_controller.h"
#include "controller/LCD/I2C/i2c.h"
#include "controller/LCD/lcd.h"
#include "controller/PWM/pwm.h"
#include "mcc_generated_files/mcc.h"
#include "mode/configuration_mode.h"
#include "mode/normal_mode.h"
#include "state/state.h"


/*
    Main application
*/

#define NO_INTERRUPT 0
#define HAS_INTERRUPT 1

void global_initialization() {
  if (MemIsUsable()) {
    set_configs(ReadConfigs(), false);
    set_max_min(ReadMaxMin(), false);
  } else {
    set_default();
  }
  set_mode(NORMAL_MODE);
}

volatile uint8_t normal_interrupt = NO_INTERRUPT;
void normal_mode_isr() { normal_interrupt = HAS_INTERRUPT; }

volatile uint8_t btn1_interrupt = NO_INTERRUPT;
void checkButtonS1_isr(void) { btn1_interrupt = HAS_INTERRUPT; }

volatile uint8_t btn2_interrupt = NO_INTERRUPT;
void checkButtonS2_isr(void) { btn2_interrupt = HAS_INTERRUPT; }

int main(void) {
  SYSTEM_Initialize();
  // If using interrupts in PIC18 High/Low Priority Mode you need to enable the
  // Global High and Low Interrupts If using interrupts in PIC Mid-Range
  // Compatibility Mode you need to enable the Global and Peripheral Interrupts
  // Use the following macros to:

  TMR0_SetInterruptHandler(normal_mode_isr);

  IOCBF4_SetInterruptHandler(checkButtonS1_isr);
  IOCCF5_SetInterruptHandler(checkButtonS2_isr);

  // Enable the Global Interrupts
  INTERRUPT_GlobalInterruptEnable();

  // Disable the Global Interrupts
  // INTERRUPT_GlobalInterruptDisable();

  // Enable the Peripheral Interrupts
  INTERRUPT_PeripheralInterruptEnable();

  // Disable the Peripheral Interrupts
  // INTERRUPT_PeripheralInterruptDisable();

  OpenI2C();
  LCDinit();

  global_initialization();

  while (1) {

    if (normal_interrupt == HAS_INTERRUPT) {
      normal_interrupt = NO_INTERRUPT;
      if (get_mode() == NORMAL_MODE) {
        normal_mode_timer_handler();
      }
    }

    if (btn1_interrupt == HAS_INTERRUPT) {
      btn1_interrupt = NO_INTERRUPT;
      if (checkButtonS1()) {
        if (get_alarm_triggered()) {
          set_alarm_triggered(false);
          clear_alarm();
        } else if (get_mode() == NORMAL_MODE) {
          normal_mode_s1_handler();
        } else {
          configuration_mode_s1_handler();
        }
      }
    }

    if (btn2_interrupt == HAS_INTERRUPT) {
      btn2_interrupt = NO_INTERRUPT;
      if (checkButtonS2()) {
        if (get_mode() == NORMAL_MODE) {
          normal_mode_s2_handler();
        } else {
          configuration_mode_s2_handler();
        }
      }
    }

    if (mode_has_changed()) {
      LCDClear();
      if (get_mode() == NORMAL_MODE) {
        normal_mode_initialization();
      } else {
        configuration_mode_initialization();
      }
    }
    if (!get_pwm_en())
      SLEEP();
  }
}