#include <xc.h>
#include "i2c.h"

/********************************************************************
*   Function Name:  OpenI2C                                         *
*   Return Value:   void                                            *
*   Parameters:     SSP peripheral setup bytes                      *
*   Description:    This function sets up the SSP module on a       * 
*                   PIC18CXXX device for use with a Microchip I2C   *
*                   EEPROM device or I2C bus device.                *
********************************************************************/
//void OpenI2C( unsigned char sync_mode, unsigned char slew )
//{
//  SSPSTAT &= 0x3F;                // power on state 
//  SSPCON1 = 0x00;                 // power on state
//  SSPCON2 = 0x00;                 // power on state
//  SSPCON1 |= sync_mode;           // select serial mode 
//  SSPSTAT |= slew;                // slew rate on/off 

//  I2C_SCL = 1;
//  I2C_SDA = 1;
//  SSPCON1 |= SSPENB;              // enable synchronous serial port 

//}

void OpenI2C( void  )
{
  SSP1STAT = 0x80;
  SSP1CON1 = 0x08;
  SSP1CON2 = 0x00;
  SSP1ADD = 0x03;
  SSP1CON1bits.SSPEN = 1;

  I2C_SCL = 1;
  I2C_SDA = 1;
}

/********************************************************************
*     Function Name:    ReadI2C                                     *
*     Return Value:     contents of SSPBUF register                 *
*     Parameters:       void                                        *
*     Description:      Read single byte from I2C bus.              *
********************************************************************/
unsigned char ReadI2C( void )
{
if( ((SSP1CON1&0x0F)==0x08) || ((SSP1CON1&0x0F)==0x0B) )	//master mode only
  SSP1CON2bits.RCEN = 1;           // enable master for 1 byte reception
  while ( !SSP1STATbits.BF );      // wait until byte received  
  return ( SSP1BUF );              // return with read byte 
}

/********************************************************************
*     Function Name:    WriteI2C                                    *
*     Return Value:     Status byte for WCOL detection.             *
*     Parameters:       Single data byte for I2C bus.               *
*     Description:      This routine writes a single byte to the    * 
*                       I2C bus.                                    *
********************************************************************/
signed char WriteI2C( unsigned char data_out )
{
  SSP1BUF = data_out;           // write single byte to SSPBUF
  if ( SSP1CON1bits.WCOL )      // test if write collision occurred
   return ( -1 );              // if WCOL bit is set return negative #
  else
  {
	if( ((SSP1CON1&0x0F)!=0x08) && ((SSP1CON1&0x0F)!=0x0B) )	//Slave mode only
	{
	      SSP1CON1bits.CKP = 1;        // release clock line 
	      while ( !PIR3bits.SSP1IF );  // wait until ninth clock pulse received

	      if ( ( !SSP1STATbits.R_W ) && ( !SSP1STATbits.BF ) )// if R/W=0 and BF=0, NOT ACK was received
	      {
	        return ( -2 );           //return NACK
	      }
		  else
		  {
			return ( 0 );				//return ACK
		  }	
	}
	else if( ((SSP1CON1&0x0F)==0x08) || ((SSP1CON1&0x0F)==0x0B) )	//master mode only
	{ 
	    while( SSP1STATbits.BF );   // wait until write cycle is complete   
	    IdleI2C();                 // ensure module is idle
	    if ( SSP1CON2bits.ACKSTAT ) // test for ACK condition received
	    	 return ( -2 );			// return NACK
		else return ( 0 );              //return ACK
	}
	return ( 0 );
  }
}

