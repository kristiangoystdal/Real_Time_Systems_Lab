/*
 * File:   luminosity.c
 * Author: krisg
 *
 * Created on 27. november 2024
 */

#include "luminosity.h"

/**
 * @brief Reads the luminosity value from the ADC and converts it to a 3-bit
 * value.
 *
 * This function uses the ADC peripheral to read a 10-bit raw value from
 * the RA0 (AN0) channel, then scales it down to a 3-bit value (0–7).
 *
 * @return uint8_t The 3-bit luminosity value.
 */
uint8_t readLum(void) {
  // Select RA0 (AN0) as the ADC input channel
  ADC_ChannelSelect(0); // Channel 0 corresponds to AN0

  // Start the ADC conversion
  ADC_ConversionStart();

  // Wait for the conversion to complete
  while (!ADC_IsConversionDone())
    ;

  // Get the raw ADC result (10-bit resolution)
  uint16_t rawResult = ADC_ConversionResultGet();

  // Convert the raw ADC value to a 3-bit value (0–7)
  uint8_t result3Bit = rawResult >> 7;

  return result3Bit;
}
