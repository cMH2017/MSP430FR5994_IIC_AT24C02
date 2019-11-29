#include "uart.h"

void UARTA0_Port_Init(void){
    Config_P20_UCA0TXD();
    Config_P21_UCA0RXD();
}

void UARTA0_Init(void){
    UCA0CTLW0 |= UCSWRST;

    UCA0CTLW0 |= UCSSEL__SMCLK;

    // ²¨ÌØÂÊ9600
    UCA0BRW = 52;
    UCA0MCTLW |= (0x49 << 8) | (1 << 4) | UCOS16;

    UARTA0_Port_Init();
    UCA0CTLW0 &= ~UCSWRST;
}

int UARTA0_Putchar(char c){
    UCA0TXBUF = c;
    while( (UCA0IFG & UCTXIFG) == 0);
    return 0;
}

int UARTA0_Puts(const char *str){
  while(*str!='\0'){
      UARTA0_Putchar(*str++);
  }
  return 0;
}

