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
#include "../LCD/I2C/i2c.h"

uint8_t readTemperature() {
    unsigned char value;
    do
    {
        IdleI2C();
        StartI2C();
        IdleI2C();

        WriteI2C(0x9a | 0x00);
        IdleI2C();
        WriteI2C(0x01);
        IdleI2C();
        RestartI2C();
        IdleI2C();
        WriteI2C(0x9a | 0x01);
        IdleI2C();
        value = ReadI2C();
        IdleI2C();
        NotAckI2C();
        IdleI2C();
        StopI2C();
    } while (!(value & 0x40));

    IdleI2C();
    StartI2C();
    IdleI2C();
    WriteI2C(0x9a | 0x00);
    IdleI2C();
    WriteI2C(0x00);
    IdleI2C();
    RestartI2C();
    IdleI2C();
    WriteI2C(0x9a | 0x01);
    IdleI2C();
    value = ReadI2C();
    IdleI2C();
    NotAckI2C();
    IdleI2C();
    StopI2C();

    uint8_t temp = value;
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