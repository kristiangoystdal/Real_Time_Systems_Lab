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
#include "clock/clock.h"
#include "controller/EEPROM/EEPROM_controller.h"
#include "controller/LCD/I2C/i2c.h"
#include "controller/LCD/lcd.h"
#include "controller/LED/led.h"
#include "mcc_generated_files/mcc.h"
#include "mode/configuration_mode.h"
#include "mode/normal_mode.h"
#include "state/state.h"
#include <stdio.h>

/*
    Main application
*/

void global_initialization() {
  if (MemIsUsable()) {
    set_configs(ReadConfigs(), false);
    set_max_min(ReadMaxMin(), false);
  } else {
    set_default();
  }
  set_mode(NORMAL_MODE);
}

int main(void) {
  SYSTEM_Initialize();
  // If using interrupts in PIC18 High/Low Priority Mode you need to enable the
  // Global High and Low Interrupts If using interrupts in PIC Mid-Range
  // Compatibility Mode you need to enable the Global and Peripheral Interrupts
  // Use the following macros to:

  TMR0_SetInterruptHandler(normal_mode_timer_handler);

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
  ADCC_Initialize(); // Initialize ADC

  global_initialization();

  while (1) {
    if (mode_has_changed()) {
      uint8_t mode = get_mode();
      if (mode == NORMAL_MODE) {
        normal_mode_initialization();
      } else {
        configuration_mode_initialization();
      }
    } // Add a delay for readability
    SLEEP();
  }
}