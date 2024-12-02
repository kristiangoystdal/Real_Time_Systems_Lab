#include "pwm.h"
#include "../../mcc_generated_files/system/system.h"
#include "../../mcc_generated_files/pwm/pwm6.h"

void PWM_Output_D4_Enable(void)
{
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x00; // unlock PPS

    // Set D5 as the output of PWM6
    RA6PPS = 0x0E;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x01; // lock PPS
}

void PWM_Output_D4_Disable(void)
{
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x00; // unlock PPS
    // Set D5 as GPIO pin
    RA6PPS = 0x00;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCK = 0x01; // lock PPS
}