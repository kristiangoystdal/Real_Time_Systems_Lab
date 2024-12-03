/*
 * File: temperature.c
 * Author: Your Name
 * Description: This file contains the implementation of temperature control
 * functions. Created on: Date
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "temperature.h"

uint8_t readTemperature() {
  // Read the temperature value
  uint8_t temp = 25;

  return temp;
}

void get_temperature(char *temperature) {
  // Read the temperature value
  uint8_t temp = readTemperature();

  // Convert the temperature to a string with Celsius sign
  temperature_to_string(temperature, temp);
}

void temperature_to_string(char *s, uint8_t temperature) {
  sprintf(s, "%02u", temperature);
}