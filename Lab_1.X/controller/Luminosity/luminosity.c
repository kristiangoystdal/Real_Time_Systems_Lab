#include "luminosity.h"
#include "../../mcc_generated_files/adc/adc.h" // Ensure this includes ADC function declarations
#include "../LCD/lcd.h"                        // Include the LCD header file
#include <stdio.h>

/**
 * @brief Reads the luminosity value from the ADC and converts it to a 3-bit
 * value.
 *
 * This function uses the ADC peripheral to read a 10-bit raw value from
 * the RA0 (AN0) channel, then scales it down to a 3-bit value (0–7).
 *
 * @param luminosity A character array to store the luminosity value as a
 * string.
 */
void get_luminosity(char *luminosity) {
  // Read the 3-bit luminosity value using the readLum() function
  uint8_t lumValue = readLum();

  // Convert the luminosity value to a string
  luminosity_to_string(luminosity, lumValue);
}

void luminosity_to_string(char *s, uint8_t luminosity) {
  sprintf(s, "L %u", luminosity);
}

/**
 * @brief Reads the luminosity value as a 3-bit value.
 *
 * @return uint8_t The 3-bit luminosity value (0–7).
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
  uint16_t rawResult = (uint16_t)ADC_ConversionResultGet();

  // Convert the raw ADC value to a 3-bit value (0–7)
  uint8_t result3Bit = (uint8_t)(rawResult >> 7);

  return result3Bit;
}
