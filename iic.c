#include "iic.h"
// MSP430FR5994ֻ��eUSCI_B��IIC

void IICB0_Port_Init(void){
    Config_P17_UCB0SCL();
    Config_P16_UCB0SDA();
}

void IICB0_Init(void){
    UCB0CTLW0 |= UCSWRST;                // USCI_B��λ
    UCB0CTLW0 |= UCMODE_3 | UCMST | UCSSEL__SMCLK;      // I2C����ģʽ
    //UCB0BRW = 8;                        // ������=SMCLK/8 Ĭ��ʱ��Դ��SMCLK
                                        // ����AT24C02��Ƶ�ʿ��ܹ���
    //UCB0CTL1 |= UCASTP_2;               // �Զ����ֹͣ�ź�

    // UCB0TBCNT = 7;                      // ����7�ֽ�����

    // UCB0I2CSA = slave_address;          // ���д�ӻ���ַ
    IICB0_Port_Init();
    UCB0CTLW0 &= ~UCSWRST;               // USCI_B��ɿɲ���״̬

    //UCBxIE |= UXTXIE;                 // ʹ�ܷ����ж�
    //__bis_SR_register(GIE);           // ʹ��ȫ���ж�

}

void IICB0_Set_Device_Address(unsigned char devAddr){
    UCB0I2CSA = devAddr;
}

void IICB0_Write(unsigned char devAddr, unsigned char byteAddr, unsigned char *data, int len){
    int pageCount;
    int i;
    for(pageCount = 0; pageCount + 8 < len; pageCount += 8){
        // �����豸��ַ
        IICB0_Set_Device_Address(devAddr);
        //IICB0_Set_Device_Address(0X50 << 1);
        // ����Ϊ����ģʽ UCTR=1
        UCB0CTLW0 |= UCTR;
        // ����ʼ�ź� UCTXSTT=1
        UCB0CTLW0 |= UCTXSTT;
        // �ȴ�UCTXSTT��Ϊ0
        while(UCB0CTLW0 & UCTXSTT);
        // �ȴ�UCTXIFG��Ϊ1
        while(!(UCB0IFG & UCTXIFG));
        // ��UCB0TXBUF������ݣ��ֵ�ַ��
        UCB0TXBUF = byteAddr;
        // �ȴ�UCTXBUF��Ϊ1
        while(!(UCB0IFG & UCTXIFG));
        // ��UCBOTXBUF������ݣ����������ݣ�

        for(i = 0; i < 8; i++){
            UCB0TXBUF = data[pageCount + i];
            while(!(UCB0IFG & UCTXIFG));
            //printf(1,1,1,1, "Write data[%d]=%d\r\n", pageCount + i, data[pageCount + i]);
        }


        // ����ֹͣ�ź� UCTXSTP=1
        UCB0CTLW0 |= UCTXSTP;
        // �ȴ�UCTXSTP��Ϊ0
        while(UCB0CTLW0 & UCTXSTP);
        byteAddr += 8;
    }

    // �����豸��ַ
    IICB0_Set_Device_Address(devAddr);
    //IICB0_Set_Device_Address(0X50 << 1);
    // ����Ϊ����ģʽ UCTR=1
    UCB0CTLW0 |= UCTR;
    // ����ʼ�ź� UCTXSTT=1
    UCB0CTLW0 |= UCTXSTT;
    // �ȴ�UCTXSTT��Ϊ0
    while(UCB0CTLW0 & UCTXSTT);
    // �ȴ�UCTXIFG��Ϊ1
    while(!(UCB0IFG & UCTXIFG));
    // ��UCB0TXBUF������ݣ��ֵ�ַ��
    UCB0TXBUF = byteAddr;
    // �ȴ�UCTXBUF��Ϊ1
    while(!(UCB0IFG & UCTXIFG));
    // ��UCBOTXBUF������ݣ����������ݣ�
    for(i = 0; i + pageCount < len; i++){
        UCB0TXBUF = data[pageCount + i];
        while(!(UCB0IFG & UCTXIFG));
        //printf(1,1,1,1, "Write data[%d]=%d\r\n", pageCount + i, data[pageCount + i]);
    }

    // ����ֹͣ�ź� UCTXSTP=1
    UCB0CTLW0 |= UCTXSTP;
    // �ȴ�UCTXSTP��Ϊ0
    while(UCB0CTLW0 & UCTXSTP);

}

void IICB0_Read(unsigned char devAddr, unsigned char byteAddr, unsigned char* rxBuf, int len){
    unsigned int i;
    // �����豸��ַ
    IICB0_Set_Device_Address(devAddr);
    //IICB0_Set_Device_Address(0X50 << 1);
    // ����Ϊ����ģʽ UCTR=1
    UCB0CTLW0 |= UCTR;
    // ����ʼ�ź� UCTXSTT=1
    UCB0CTLW0 |= UCTXSTT;
    // �ȴ�UCTXSTT��Ϊ0
    while(UCB0CTLW0 & UCTXSTT);
    // �ȴ�UCTXIFG��Ϊ1
    while(!(UCB0IFG & UCTXIFG));
    // ��UCB0TXBUF������ݣ��ֵ�ַ��
    UCB0TXBUF = byteAddr;
    while(!(UCB0IFG & UCTXIFG));
    // ����Ϊ����ģʽ UCTR=0
    UCB0CTLW0 &= ~UCTR;

    // ���Ϳ�ʼ�ź� UCTXSTT=1
    UCB0CTLW0 |= UCTXSTT;
    // �ȴ��ֵ�ַ�������
    //while(!(UCB0IFG & UCTXIFG));

    // �ȴ�UCTXSTT=0 ��ʱ�豸��ַ�ַ�����һ��
    while(UCB0CTLW0 & UCTXSTT);

    // �ȴ�UCRXIFG��1
    for(i = 0; i < len; i++){
        while(!(UCB0IFG & UCRXIFG));
        // ��ȡUCRXBUF�Ĵ���
        rxBuf[i] = UCB0RXBUF;
    }
    // ����ֹͣ�ź� UXTCSTP=0
        UCB0CTLW0 |= UCTXSTP;
    // �ȴ�UXTCSTP=0
    while(UCB0CTLW0 & UCTXSTP);
}
