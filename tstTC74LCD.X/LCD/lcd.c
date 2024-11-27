/**
LCD
*/

#include <xc.h>
#define _XTAL_FREQ 4000000

#include "../I2C/i2c.h"
#include "lcd.h"

#define LCD_ADDR 0x4e   // 0x27 << 1
#define LCD_BL 0x08
#define LCD_EN 0x04
#define LCD_RW 0x02
#define LCD_RS 0x01

void LCDsend(unsigned char c)
{
  IdleI2C();
  StartI2C(); IdleI2C();
  WriteI2C(LCD_ADDR | 0x00); IdleI2C();
  WriteI2C(c); IdleI2C();
  StopI2C();    
}
unsigned char LCDrecv(unsigned char mode)
{
  unsigned char hc;
  unsigned char lc;
  
  IdleI2C();
  StartI2C(); IdleI2C();
  WriteI2C(LCD_ADDR | 0x00); IdleI2C();
  WriteI2C(0xf0 | LCD_BL | LCD_RW | mode); IdleI2C();
  WriteI2C(0xf0 | LCD_BL | LCD_EN | LCD_RW | mode); IdleI2C();
  __delay_us(1);
  RestartI2C(); IdleI2C();
  WriteI2C(LCD_ADDR | 0x01); IdleI2C();
  hc = ReadI2C(); IdleI2C();
  NotAckI2C();
  RestartI2C(); IdleI2C();
  WriteI2C(LCD_ADDR | 0x00); IdleI2C();
  WriteI2C(0xf0 | LCD_BL | LCD_RW | mode); IdleI2C();
  WriteI2C(0xf0 | LCD_BL | LCD_EN | LCD_RW | mode); IdleI2C();
  __delay_us(1);
  RestartI2C(); IdleI2C();
  WriteI2C(LCD_ADDR | 0x01); IdleI2C();
  lc = ReadI2C(); IdleI2C();
  NotAckI2C();
  RestartI2C(); IdleI2C();
  WriteI2C(LCD_ADDR | 0x00); IdleI2C();
  WriteI2C(0xf0 | LCD_BL | LCD_RW | mode); IdleI2C();
  StopI2C();
  return ((hc&0xf0) | ((lc>>4)&0x0f));
}

void LCDsend2x4(unsigned char c, unsigned char mode)
{
  unsigned char hc;
  unsigned char lc;
  
  hc = c & 0xf0;
  lc = (c << 4) & 0xf0;
    
  IdleI2C();
  StartI2C(); IdleI2C();
  WriteI2C(LCD_ADDR | 0x00); IdleI2C();
  WriteI2C(hc | LCD_BL | mode); IdleI2C();
  WriteI2C(hc | LCD_BL | LCD_EN | mode); IdleI2C();
  __delay_us(1);
  WriteI2C(hc | LCD_BL | mode); IdleI2C();
  WriteI2C(lc | LCD_BL | mode); IdleI2C();
  WriteI2C(lc | LCD_BL | LCD_EN | mode); IdleI2C();
  __delay_us(1);
  WriteI2C(lc | LCD_BL | mode); IdleI2C();
  StopI2C();    
  __delay_us(50);
}

void LCDinit(void)
{
  __delay_ms(50);
  LCDsend(0x30);
  LCDsend(0x34); __delay_us(500); LCDsend(0x30);
  __delay_ms(5);
  LCDsend(0x30);
  LCDsend(0x34); __delay_us(500); LCDsend(0x30);
  __delay_us(100);
  LCDsend(0x30);
  LCDsend(0x34); __delay_us(500); LCDsend(0x30);
  __delay_us(100);
  LCDsend(0x20);
  LCDsend(0x24); __delay_us(500); LCDsend(0x20);
  __delay_ms(5);

  LCDsend2x4(0x28, 0);
  LCDsend2x4(0x06, 0);
  LCDsend2x4(0x0f, 0);
  LCDsend2x4(0x01, 0);
  __delay_ms(2);
}

void LCDcmd(unsigned char c)
{
  LCDsend2x4(c, 0);
}

void LCDchar(unsigned char c)
{
  LCDsend2x4(c, LCD_RS);
}

void LCDstr(char *p)
{
  unsigned char c;
  
  while((c = *p++)) LCDchar(c);
}

int LCDbusy()
{
  if(LCDrecv(0) & 0x80) return 1;
  return 0;
}

void LCDpos(unsigned char l, unsigned char c)
{
  unsigned char p;

// 0x80 - first line, first column; 
// 0xc0 - second line, first column
  if (l>=1) p = 0xc0; else p=0x80; 
  p = p | (c&0x0f);
  LCDcmd(p);
}
