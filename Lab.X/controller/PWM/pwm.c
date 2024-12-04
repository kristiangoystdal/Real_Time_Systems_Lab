#include "pwm.h"
#include "../../mcc_generated_files/mcc.h"

void set_PWM(bool on){
    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCK = 0x00; // unlock PPS
    
    if(on){
    RA6PPS = 0x0E;
    } else{
        RA6PPS = 0x00;
    }

    PPSLOCK = 0x55; 
    PPSLOCK = 0xAA; 
    PPSLOCK = 0x01; // lock PPS
}