
#include "luminosity.h"
#include "../../mcc_generated_files/adcc.h" // Ensure this includes ADC function declarations
#include "../LCD/lcd.h"                    // Include the LCD header file

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

/**
 * @brief Reads the luminosity value as a 3-bit value.
 *
 * @return uint8_t The 3-bit luminosity value (0–7).
 */
uint8_t readLum(void) {

  // Start the ADC conversion on channel 0 (RA0/AN0)
  ADCC_StartConversion(0);

  // Wait for the conversion to complete
  while (!ADCC_IsConversionDone())
    ;

  // Get the raw ADC result (10-bit resolution)
  uint16_t rawResult = (uint16_t)ADCC_GetConversionResult();

  // Convert the raw ADC value to a 3-bit value (0–7)
  uint8_t result3Bit = (uint8_t)(rawResult >> 7);

  return result3Bit;
}
