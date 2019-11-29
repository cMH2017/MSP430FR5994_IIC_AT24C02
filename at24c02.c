#include "at24c02.h"
void AT24C02_Init(void){
    IICB0_Init();
}

void AT24C02_Write(unsigned char byteAddr, unsigned char *txBuf, int len){
    IICB0_Write(DEVEICE_ADDR, byteAddr, txBuf, len);
}

void AT24C02_Read(unsigned char byteAddr, unsigned char* rxBuf, int len){
    IICB0_Read(DEVEICE_ADDR, byteAddr, rxBuf, len);
}
