#include "pwm.h"
#include "../../mcc_generated_files/mcc.h"

void PWM_enable(void) {
    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCK = 0x00; // unlock PPS

    RA6PPS = 0x0E;

    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCK = 0x01; // lock PPS
}

void PWM_disable(void) {
    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCK = 0x00; // unlock PPS
    
    RA6PPS = 0x00;
    
    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCK = 0x01; // lock PPS
}