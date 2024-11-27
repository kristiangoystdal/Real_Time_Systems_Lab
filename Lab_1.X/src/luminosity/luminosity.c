/*
 * File:   luminosity.c
 * Author: krisg
 *
 * Created on 27. november 2024, 10:39
 */

#include "mcc_generated_files/system/system.h"
#include <xc.h>

/**
 * @brief Reads the luminosity value from the ADC and converts it to 3 bits.
 *
 * @return uint8_t The 3-bit luminosity value (0–7).
 */
uint8_t readLum(void) {
  // Start ADC conversion on RA0
  ADC_ChannelSelect(ADC_CHANNEL_ANA0); // Select RA0 (AN0) as input channel
  ADC_ConversionStart();               // Start ADC conversion

  // Wait for the conversion to complete
  while (!ADC_IsConversionDone())
    ;

  // Get the raw ADC result (10-bit resolution)
  adc_result_t rawResult = ADC_ConversionResultGet();

  // Convert the raw ADC value to 3 bits (0–7)
  uint8_t result3Bit = rawResult >> 7;

  return result3Bit;
}
