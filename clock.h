#ifndef _CLOCK_H
#define _CLOCK_H
#include "msp430fr5994.h"
#include "delay.h"
#include "pin.h"

#define DCOFRE_1MHz     DCOFSEL_0
#define DCOFRE_4MHz     DCOFSEL_3
#define DCOFRE_7MHz     DCOFSEL_5
#define DCOFRE_8MHz     DCOFSEL_6

void Clock_System_Init(void);
#endif
