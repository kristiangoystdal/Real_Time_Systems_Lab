/**
  Generated Main Source File

  Company:
	Microchip Technology Inc.

  File Name:
	main.c

  Summary:
	This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
	This header file provides implementations for driver APIs for all modules selected in the GUI.
	Generation Information :
		Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
		Device            :  PIC16F18875
		Driver Version    :  2.00
*/

/*
	(c) 2018 Microchip Technology Inc. and its subsidiaries.

	Subject to your compliance with these terms, you may use Microchip software and any
	derivatives exclusively with Microchip products. It is your responsibility to comply with third party
	license terms applicable to your use of third party software (including open source software) that
	may accompany Microchip software.

	THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
	EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
	IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
	FOR A PARTICULAR PURPOSE.

	IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
	INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
	WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
	HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
	THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
	CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
	OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
	SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "I2C/i2c.h"
#include "LCD/lcd.h"
#include "stdio.h"

/*
						 Main application
 */
#define MAGIC_NUMBER_ADDR 0x7042

#define MONITOR_PERIOD_ADDR 0x7000
#define ALARM_DURATION_ADDR 0x7001





unsigned char c;
char buf[17];
uint8_t seconds = 40;
uint8_t minutes = 59;
uint8_t hours = 23;
char buf2[10];

void increment_time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds)
{
	if (*seconds == 59)
	{
		*seconds = 0;
		if (*minutes == 59)
		{
			*minutes = 0;
			if (*hours == 23)
			{
				*hours = 0;
			}
			else
			{
				(*hours)++;
			}
		}
		else
		{
			(*minutes)++;
		}
	}
	else
	{
		(*seconds)++;
	}
}

unsigned char readTC74(void)
{
	unsigned char value;
	do
	{
		IdleI2C();
		StartI2C();
		IdleI2C();

		WriteI2C(0x9a | 0x00);
		IdleI2C();
		WriteI2C(0x01);
		IdleI2C();
		RestartI2C();
		IdleI2C();
		WriteI2C(0x9a | 0x01);
		IdleI2C();
		value = ReadI2C();
		IdleI2C();
		NotAckI2C();
		IdleI2C();
		StopI2C();
	} while (!(value & 0x40));

	IdleI2C();
	StartI2C();
	IdleI2C();
	WriteI2C(0x9a | 0x00);
	IdleI2C();
	WriteI2C(0x00);
	IdleI2C();
	RestartI2C();
	IdleI2C();
	WriteI2C(0x9a | 0x01);
	IdleI2C();
	value = ReadI2C();
	IdleI2C();
	NotAckI2C();
	IdleI2C();
	StopI2C();

	return value;
}

t1_isr()
{
	c = readTC74();
	LCDcmd(0x80); // first line, first column
	while (LCDbusy())
		;
	LCDstr("CHECK");
	LCDpos(0, 8);
	while (LCDbusy())
		;
	LCDstr("STR-RTS");
	LCDcmd(0xc0); // second line, first column
	sprintf(buf, "%02d C", c);
	while (LCDbusy())
		;
	LCDstr(buf);

	increment_time(&hours, &minutes, &seconds);
	IO_RA7_Toggle();
	LCDpos(1, 6);
	sprintf(buf2, "%02u:%02u:%02u", hours, minutes, seconds);
	while (LCDbusy())
		;
	LCDstr(buf2);
}

void main(void)
{

	// initialize the device
	SYSTEM_Initialize();

	// When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
	// Use the following macros to:

	// Enable the Global Interrupts
	INTERRUPT_GlobalInterruptEnable();

	// Enable the Peripheral Interrupts
	INTERRUPT_PeripheralInterruptEnable();

	// Disable the Global Interrupts
	// INTERRUPT_GlobalInterruptDisable();

	// Disable the Peripheral Interrupts
	// INTERRUPT_PeripheralInterruptDisable();

	OpenI2C();
	// I2C_SCL = 1;
	// I2C_SDA = 1;
	// WPUC3 = 1;
	// WPUC4 = 1;
	LCDinit();

	TMR1_SetInterruptHandler(t1_isr);
	IO_RA7_SetHigh();

	while (1)
	{
		// Add your application code
		NOP();
	}
}
/**
 End of File
*/