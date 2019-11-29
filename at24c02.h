#ifndef _AT24C02_H
#define _AT24C02_H
#include "iic.h"
#define  DEVEICE_ADDR 0X50   // AT24C02的设备地址
void AT24C02_Init(void);
void AT24C02_Write(unsigned char byteAddr, unsigned char *data, int len);
void AT24C02_Read(unsigned char byteAddr, unsigned char* rxBuf, int len);
#endif
