#ifndef _UART_H
#define _UART_H
#include "msp430fr5994.h"
#include "delay.h"
#include "pin.h"

void UARTA0_Port_Init(void);
void UARTA0_Init(void);
int UARTA0_Putchar(char c);
int UARTA0_Puts(const char *str);

#endif /* _UART_H */
