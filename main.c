#include "msp430fr5994.h"
#include "clock.h"
#include "pin.h"
#include "uart.h"
#include "printf.h"
#include "iic.h"
#define SIZE 134

int main(void){
    volatile unsigned char a[256], b[256];
    int t;
    WDTCTL = WDTPW | WDTHOLD;   // 关闭看门狗
    Clock_System_Init();        // MCLK=SMCLK=8M ACLK=32768(有误差)
                                // 修改时钟频率要修改和delay相关的CPU_F宏
    UARTA0_Init();              // 用于printf的串口 波特率9600
    AT24C02_Init();
    for(t = 0; t < 256; t++){
        a[t] = t % 57;
    }

    puts("\r\nGO\r\n");
    AT24C02_Write(0, a, SIZE);
    puts("Write OK\r\n");
    AT24C02_Read(0, b, SIZE);
    puts("Read OK\r\n");
    for(t = 0; t < SIZE; t++){
        printf(1,1,1,1, "%3d ", a[t]);
        if((t + 1) % 16 == 0)
            puts("\r\n");

    }
    puts("\r\n");
    for(t = 0; t < SIZE + 6; t++){
        printf(1,1,1,1, "%3d ", b[t]);
        if((t + 1) % 16 == 0)
            puts("\r\n");
    }
    while(1);
}




