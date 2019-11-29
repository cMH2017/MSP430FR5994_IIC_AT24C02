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
    WDTCTL = WDTPW | WDTHOLD;   // �رտ��Ź�
    Clock_System_Init();        // MCLK=SMCLK=8M ACLK=32768(�����)
                                // �޸�ʱ��Ƶ��Ҫ�޸ĺ�delay��ص�CPU_F��
    UARTA0_Init();              // ����printf�Ĵ��� ������9600
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




