#ifndef _DELAY_H
#define _DELAY_H
#include "msp430fr5994.h"
// 改变CPU工作频率时要更改宏CPU_F
#define CPU_F           ((double)8000000)
#define delay_us(x)     __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x)     __delay_cycles((long)(CPU_F*(double)x/1000.0))


#endif
