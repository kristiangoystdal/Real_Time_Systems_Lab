#ifndef __I2C_H
#define __I2C_H
/******************************************************************************
 // *                   I2C PERIPHERAL LIBRARY HEADER FILE
 ******************************************************************************
 * FileName:        		i2c.h
 * Dependencies:    	See include below
 * Processor:       		PIC18
 * Compiler:        		MCC18
 * Company:         		Microchip Technology, Inc.
 *
 * Software License Agreement
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *****************************************************************************/
 
#include <xc.h>

/* SSPCON1 REGISTER */
#define   SSPENB    			0b00100000  	/* Enable serial port and configures SCK, SDO, SDI*/
#define   SLAVE_7   			0b00000110     	/* I2C Slave mode, 7-bit address*/
#define   SLAVE_10  			0b00000111    	/* I2C Slave mode, 10-bit address*/
#define   MASTER    			0b00001000     	/* I2C Master mode */
#define   MASTER_FIRMW			0b00001011		//I2C Firmware Controlled Master mode (slave Idle)
#define   SLAVE_7_STSP_INT 		0b00001110		//I2C Slave mode, 7-bit address with Start and Stop bit interrupts enabled
#define   SLAVE_10_STSP_INT 	0b00001111		//I2C Slave mode, 10-bit address with Start and Stop bit interrupts enabled

/* SSPSTAT REGISTER */
#define   SLEW_OFF  			0b10000000  	/* Slew rate disabled for 100kHz mode */
#define   SLEW_ON   			0b00000000  	/* Slew rate enabled for 400kHz mode  */


//******** I2C **********

/***********************************************************************************
Macro       : EnableIntI2C

Include     : i2c.h

Description : Macro enables I2C  Interrupt 
 
Arguments   : None
 
Remarks     : None 
***********************************************************************************/
//#define EnableIntI2C                   (PIE1bits.SSPIE = 1)
#define EnableIntI2C()                   do { PIE3bits.SSP1IE = 1; } while (0)

#define EnableIntI2C1	EnableIntI2C

/***********************************************************************************
Macro       : DisableIntI2C

Include     : i2c.h

Description : Macro disables I2C  Interrupt 
 
Arguments   : None
 
Remarks     : None 
***********************************************************************************/
//#define DisableIntI2C                   (PIE1bits.SSPIE = 0)
#define DisableIntI2C()                   do { PIE3bits.SSP1IE = 0; } while (0)

#define DisableIntI2C1	DisableIntI2C

/***********************************************************************************
Macro       : SetPriorityIntI2C(priority)
 
Include     : i2c.h
 
Description : Macro sets the priority level for I2C interrupt.
 
Arguments   : priority - This input parameter is the level of interrupt priority.
		* 0 -- Low priority (Default Value)
		* 1 -- High Priority
 Remarks     : None
***********************************************************************************/
//#define SetPriorityIntI2C(priority)     (IPR1bits.SSPIP = priority)

//#define SetPriorityIntI2C1	SetPriorityIntI2C

/*******************************************************************
Macro       : I2C_Clear_Intr_Status_Bit

Include     : i2c.h 

Description : Macro to Clear I2C  Interrupt Status bit 

Arguments   : None 

Remarks     : None 
*******************************************************************/
//#define I2C_Clear_Intr_Status_Bit     (PIR1bits.SSPIF = 0)
#define I2C_Clear_Intr_Status_Bit     do { PIR3bits.SSP1IF = 0; } while (0)

#define I2C1_Clear_Intr_Status_Bit	I2C_Clear_Intr_Status_Bit

/*******************************************************************
Macro       : I2C_Intr_Status

Include     : i2c.h 

Description : Macro to return I2C Interrupt Status  

Arguments   : None 

Remarks     : None 
*******************************************************************/
//#define I2C_Intr_Status		PIR1bits.SSPIF
#define I2C_Intr_Status		PIR3bits.SSP1IF

#define I2C1_Intr_Status	I2C_Intr_Status

/**************************************************************************
Macro       : getcI2C

Description : macro is identical to ReadI2C,#define to ReadI2C in i2c.h
 
Arguments   : None
 
Remarks     : None 
***************************************************************************/
#define  getcI2C  ReadI2C

/**************************************************************************
Macro       : putcI2C

Description : macro is identical to WriteI2C,#define to WriteI2C in i2c.h
 
Arguments   : None
 
Remarks     : None 
***************************************************************************/
#define  putcI2C  WriteI2C

//void IdleI2C( void );

//void OpenI2C( unsigned char sync_mode,  unsigned char slew );
void OpenI2C( void );

signed char WriteI2C( unsigned char data_out );

signed char putsI2C( unsigned char *wrptr );

unsigned char ReadI2C( void );

//void CloseI2C( void );


/* CloseI2C
 * Disable SPI module
 */
//#define CloseI2C()  SSPCON1 &=0xDF
#define CloseI2C()  do { SSP1CON1bits.SSPEN = 0; } while (0)

/* Idle I2C
 * Test if I2C module is idle
 */
//#define IdleI2C()    while ((SSPCON2 & 0x1F) | (SSPSTATbits.R_W))
#define IdleI2C()    while ((SSP1CON2 & 0x1F) | (SSP1STATbits.R_W))

/*******************************************************************
Macro       : StopI2C()

Include     : i2c.h

Description : Macro to initiate stop condition

Arguments   : None

Remarks     : This macro initiates stop condition and waits till the stop signal
		sequence is terminated.This macro is applicable only to master
*******************************************************************/
//#define StopI2C()  SSPCON2bits.PEN=1;while(SSPCON2bits.PEN)
#define StopI2C()  do { SSP1CON2bits.PEN = 1;while(SSP1CON2bits.PEN); } while (0)

/*******************************************************************
Macro       : StartI2C()

Include     : i2c.h

Description : Macro to initiate start condition

Arguments   : None

Remarks     : This macro initiates start condition and waits till the start signal
		sequence is terminated. This macro is applicable only to master
*******************************************************************/
//#define StartI2C()  SSPCON2bits.SEN=1;while(SSPCON2bits.SEN)
#define StartI2C()  do { SSP1CON2bits.SEN=1;while(SSP1CON2bits.SEN); } while (0)

/*******************************************************************
Macro       : RestartI2C()

Include     : i2c.h

Description : Macro to initiate Restart condition

Arguments   : None

Remarks     : This macro initiates Restart condition and waits till the Restart signal
		sequence is terminated. This macro is applicable only to master
*******************************************************************/
//#define RestartI2C()  SSPCON2bits.RSEN=1;while(SSPCON2bits.RSEN)
#define RestartI2C()  do { SSP1CON2bits.RSEN=1;while(SSP1CON2bits.RSEN); } while (0)

/*******************************************************************
Macro       : NotAckI2C()

Include     : i2c.h

Description : Macro to initiate negetive acknowledgement sequence

Arguments   : None

Remarks     : This macro initiates negetive acknowledgement condition and 
		waits till the acknowledgement sequence is terminated.
		This macro is applicable only to master
*******************************************************************/
//#define NotAckI2C()     SSPCON2bits.ACKDT=1;SSPCON2bits.ACKEN=1;while(SSPCON2bits.ACKEN)
#define NotAckI2C()     do { SSP1CON2bits.ACKDT=1;SSP1CON2bits.ACKEN=1;while(SSP1CON2bits.ACKEN); } while (0)

/*******************************************************************
Macro       : AckI2C()

Include     : i2c.h

Description : Macro to initiate positive acknowledgement sequence

Arguments   : None

Remarks     : This macro initiates positive acknowledgement condition and 
		waits till the acknowledgement sequence is terminated.
		This macro is applicable only to master
*******************************************************************/
//#define AckI2C()        SSPCON2bits.ACKDT=0;SSPCON2bits.ACKEN=1;while(SSPCON2bits.ACKEN)
#define AckI2C()        do { SSP1CON2bits.ACKDT=0;SSP1CON2bits.ACKEN=1;while(SSP1CON2bits.ACKEN); } while (0)

/************************************************************************
Macro :  DataRdyI2C() 

Include            : i2c.h 

Description        : This Macro provides status back to user if SSPxBUF
			register contain data. 
                     
Arguments          : None 

Remarks            : This Macro determines if there is any byte to read from
			SSPxBUF register.
*************************************************************************/
//#define DataRdyI2C()    (SSPSTATbits.BF)
#define DataRdyI2C()    (SSP1STATbits.BF)


#define I2C_SCL	TRISCbits.TRISC3
#define I2C_SDA	TRISCbits.TRISC4

#endif
