#ifndef __LCD_H
#define __LCD_H

#include <xc.h>

#define LCD_ADDR 0x4e   // 0x27 << 1
#define LCD_BL 0x08
#define LCD_EN 0x04
#define LCD_RW 0x02
#define LCD_RS 0x01

void LCDsend(unsigned char c);

unsigned char LCDrecv(unsigned char mode);

void LCDsend2x4(unsigned char c, unsigned char mode);

void LCDinit(void);

void LCDcmd(unsigned char c);

void LCDchar(unsigned char c);

void LCDstr(char *p);

int LCDbusy(void);

void LCDpos(unsigned char l, unsigned char c);

#endif
