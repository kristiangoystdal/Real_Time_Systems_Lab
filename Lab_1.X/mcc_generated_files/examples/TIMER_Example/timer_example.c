/**
 * TIMER Toggle LED - Callback Example Driver File
 * 
 * @file timer_example.c
 * 
 * @addtogroup timer_example
 * 
 * @brief This is the generated example implementation for TIMER Toggle LED - Callback driver.
 *
 * @version TIMER Toggle LED - Callback Example Version 1.0.0
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

/* Use Case 1 - Callback implementation. Copy this code to your project source, e.g., to main.c  */
/* ------------------------------------------------------------------

#include "mcc_generated_files/system/system.h"

static void Timer_Callback(void);

static const struct TMR_INTERFACE *Timer = &Timer0; // TODO: Replace Timer0 with name of const struct TMR_INTERFACE, from MCC Generated Files > timer > tmrx.c

static void Timer_Callback(void)
{
    IO_LED_Toggle();
    IO_Debug_Toggle();
}

int main(void)
{
    SYSTEM_Initialize();
    Timer->TimeoutCallbackRegister(Timer_Callback);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    while (1) 
    {
    }
}
------------------------------------------------------------------ */
/**
 End of File
*/