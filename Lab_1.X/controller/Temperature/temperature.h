/*
 * File: temperature.h
 * Author: Your Name
 * Description: This file contains the declarations for temperature control
 * functions. Created on: Date
 */

#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <stdint.h>

// Function to read the temperature value
uint8_t readTemperature(void);

// Function to get the temperature as a string
void get_temperature(char *temperature);

#endif /* TEMPERATURE_H */