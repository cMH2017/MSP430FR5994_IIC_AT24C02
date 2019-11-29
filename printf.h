#ifndef _PRINTF_H
#define _PRINTF_H
#include "msp430fr5994.h"
#include "uart.h"

#define putchar     UARTA0_Putchar
#define puts        UARTA0_Puts
#define  MAX_NUMBER_BYTES  64

int printf(char unused1,char unused2,char unused3,char unused4, const char *fmt, ...);

#endif /* _PRINTF_H_ */

