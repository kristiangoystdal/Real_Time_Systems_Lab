/*
 * File:   luminosity.h
 * Author: krisg
 *
 * Created on 27. november 2024
 */

#ifndef LUMINOSITY_H
#define LUMINOSITY_H

#include <stdint.h>
#include <xc.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reads the luminosity value from the ADC and converts it to a 3-bit
 * value.
 *
 * This function performs an ADC conversion, waits for the conversion to
 * complete, and returns a 3-bit value (range 0–7) corresponding to the
 * luminosity.
 *
 * @return uint8_t The 3-bit luminosity value.
 */
uint8_t readLum(void);
void get_luminosity(char *luminosity);
void luminosity_to_string(char *s, uint8_t luminosity);

#ifdef __cplusplus
}
#endif

#endif /* LUMINOSITY_H */
