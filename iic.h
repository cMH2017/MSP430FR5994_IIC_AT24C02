#ifndef _IIC_H
#define _IIC_H
// MSP430FR5994Ö»ÓÐeUSCI_BÓÐIIC
#include "msp430fr5994.h"
#include "pin.h"
#include "delay.h"
#include "printf.h"
void IICB0_Port_Init(void);
void IICB0_Init(void);
void IICB0_Set_Device_Address(unsigned char devAddr);
void IICB0_Write(unsigned char devAddr, unsigned char byteAddr, unsigned char *data, int len);
void IICB0_Read(unsigned char devAddr, unsigned char byteAddr, unsigned char* rxBuf, int len);


#endif

