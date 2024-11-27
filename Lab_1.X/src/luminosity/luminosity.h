/*
 * File:   luminosity.h
 * Author: krisg
 *
 * Created on 27. november 2024, 10:46
 */

#ifndef LUMINOSITY_H
#define LUMINOSITY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mcc_generated_files/system/system.h"
#include <xc.h>


// Function Prototypes
/**
 * @brief Reads the luminosity value from the ADC.
 *
 * This function starts an ADC conversion on channel RA0 (AN0),
 * waits for the conversion to complete, and returns the converted
 * 3-bit luminosity value (range 0–7).
 *
 * @return uint8_t The 3-bit luminosity value.
 */
uint8_t readLum(void);

#ifdef __cplusplus
}
#endif

#endif /* LUMINOSITY_H */
