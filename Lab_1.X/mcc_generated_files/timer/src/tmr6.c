/**
 * TMR6 Generated Timer Driver File
 *
 * @file tmr6.c
 * 
 * @ingroup  timerdriver
 * 
 * @brief Driver implementation for the TMR6 Timer driver.
 *
 * @version Driver Version 4.0.0
 *
 * @version Package Version 5.0.0
 */

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "../tmr6.h"

const struct TIMER_INTERFACE Timer6 = {
    .Initialize = TMR6_Initialize,
    .Deinitialize = TMR6_Deinitialize,
    .Start = TMR6_Start,
    .Stop = TMR6_Stop,
    .PeriodSet = TMR6_PeriodSet,
    .PeriodGet = TMR6_PeriodGet,
    .CounterGet = TMR6_CounterGet,
    .CounterSet = TMR6_CounterSet,
    .MaxCountGet = TMR6_MaxCountGet,
    .TimeoutCallbackRegister = TMR6_PeriodMatchCallbackRegister,
    .Tasks = NULL
};

static void (*TMR6_PeriodMatchCallback)(void);
static void TMR6_DefaultPeriodMatchCallback(void);

/**
  Section: TMR6 APIs
*/

void TMR6_Initialize(void)
{
    T6CLKCON = (4 << _T6CLKCON_T6CS_POSN);  // T6CS LFINTOSC

    T6HLT = (0 << _T6HLT_T6MODE_POSN)   // T6MODE Software control
        | (0 << _T6HLT_T6CKSYNC_POSN)   // T6CKSYNC Not Synchronized
        | (0 << _T6HLT_T6CKPOL_POSN)   // T6CKPOL Rising Edge
        | (0 << _T6HLT_T6PSYNC_POSN);  // T6PSYNC Not Synchronized

    T6RST = (0 << _T6RST_T6RSEL_POSN);  // T6RSEL T6CKIPPS pin

    T6PR = 0xF2;            // Period 1.00335s; Frequency 242Hz; Count 242

    T6TMR = 0x0;

    TMR6_PeriodMatchCallback = TMR6_DefaultPeriodMatchCallback;
    
    PIR4bits.TMR6IF = 0;   
    PIE4bits.TMR6IE = 1;

    T6CON = (7 << _T6CON_T6CKPS_POSN)   // T6CKPS 1:128
        | (1 << _T6CON_TMR6ON_POSN)   // TMR6ON on
        | (0 << _T6CON_T6OUTPS_POSN);  // T6OUTPS 1:1
}

void TMR6_Deinitialize(void)
{
    T6CONbits.TMR6ON = 0;
    
    PIR4bits.TMR6IF = 0;	   
    PIE4bits.TMR6IE = 0;		
    
    T6CON = 0x0;
    T6CLKCON = 0x0;
    T6HLT = 0x0;
    T6RST = 0x0;
    T6PR = 0xFF;
    T6TMR =0x0;
}

void TMR6_Start(void)
{   
   T6CONbits.TMR6ON = 1;
}

void TMR6_Stop(void)
{   
    T6CONbits.TMR6ON = 0;
}

uint32_t TMR6_CounterGet(void)
{
    return (uint32_t)T6TMR;
}

void TMR6_CounterSet(uint32_t count)
{  
    T6TMR = (uint8_t)count;
}

void TMR6_PeriodSet(uint32_t periodVal)
{
    T6PR = (uint8_t)periodVal;
}

uint32_t TMR6_PeriodGet(void)
{
    return (uint32_t)T6PR;
}

uint32_t TMR6_MaxCountGet(void)
{
    return (uint32_t)TMR6_MAX_COUNT;
}

void TMR6_ISR(void)
{
    // The ticker is set to 1 -> The callback function gets called every time this ISR executes.
    if(NULL != TMR6_PeriodMatchCallback)
    {
        TMR6_PeriodMatchCallback();
    }
   PIR4bits.TMR6IF = 0;
}

void TMR6_PeriodMatchCallbackRegister(void (* callbackHandler)(void))
{
   TMR6_PeriodMatchCallback = callbackHandler;
}

static void TMR6_DefaultPeriodMatchCallback(void)
{
    // Default callback function
}
