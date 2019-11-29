#include "iic.h"
// MSP430FR5994只有eUSCI_B有IIC

void IICB0_Port_Init(void){
    Config_P17_UCB0SCL();
    Config_P16_UCB0SDA();
}

void IICB0_Init(void){
    UCB0CTLW0 |= UCSWRST;                // USCI_B复位
    UCB0CTLW0 |= UCMODE_3 | UCMST | UCSSEL__SMCLK;      // I2C主机模式
    //UCB0BRW = 8;                        // 波特率=SMCLK/8 默认时钟源是SMCLK
                                        // 对于AT24C02该频率可能过快
    //UCB0CTL1 |= UCASTP_2;               // 自动诊断停止信号

    // UCB0TBCNT = 7;                      // 发送7字节数据

    // UCB0I2CSA = slave_address;          // 填充写从机地址
    IICB0_Port_Init();
    UCB0CTLW0 &= ~UCSWRST;               // USCI_B变成可操作状态

    //UCBxIE |= UXTXIE;                 // 使能发送中断
    //__bis_SR_register(GIE);           // 使能全局中断

}

void IICB0_Set_Device_Address(unsigned char devAddr){
    UCB0I2CSA = devAddr;
}

void IICB0_Write(unsigned char devAddr, unsigned char byteAddr, unsigned char *data, int len){
    int pageCount;
    int i;
    for(pageCount = 0; pageCount + 8 < len; pageCount += 8){
        // 设置设备地址
        IICB0_Set_Device_Address(devAddr);
        //IICB0_Set_Device_Address(0X50 << 1);
        // 设置为发送模式 UCTR=1
        UCB0CTLW0 |= UCTR;
        // 发起开始信号 UCTXSTT=1
        UCB0CTLW0 |= UCTXSTT;
        // 等待UCTXSTT变为0
        while(UCB0CTLW0 & UCTXSTT);
        // 等待UCTXIFG变为1
        while(!(UCB0IFG & UCTXIFG));
        // 向UCB0TXBUF填充数据（字地址）
        UCB0TXBUF = byteAddr;
        // 等待UCTXBUF变为1
        while(!(UCB0IFG & UCTXIFG));
        // 向UCBOTXBUF填充数据（真正的数据）

        for(i = 0; i < 8; i++){
            UCB0TXBUF = data[pageCount + i];
            while(!(UCB0IFG & UCTXIFG));
            //printf(1,1,1,1, "Write data[%d]=%d\r\n", pageCount + i, data[pageCount + i]);
        }


        // 发起停止信号 UCTXSTP=1
        UCB0CTLW0 |= UCTXSTP;
        // 等待UCTXSTP变为0
        while(UCB0CTLW0 & UCTXSTP);
        byteAddr += 8;
    }

    // 设置设备地址
    IICB0_Set_Device_Address(devAddr);
    //IICB0_Set_Device_Address(0X50 << 1);
    // 设置为发送模式 UCTR=1
    UCB0CTLW0 |= UCTR;
    // 发起开始信号 UCTXSTT=1
    UCB0CTLW0 |= UCTXSTT;
    // 等待UCTXSTT变为0
    while(UCB0CTLW0 & UCTXSTT);
    // 等待UCTXIFG变为1
    while(!(UCB0IFG & UCTXIFG));
    // 向UCB0TXBUF填充数据（字地址）
    UCB0TXBUF = byteAddr;
    // 等待UCTXBUF变为1
    while(!(UCB0IFG & UCTXIFG));
    // 向UCBOTXBUF填充数据（真正的数据）
    for(i = 0; i + pageCount < len; i++){
        UCB0TXBUF = data[pageCount + i];
        while(!(UCB0IFG & UCTXIFG));
        //printf(1,1,1,1, "Write data[%d]=%d\r\n", pageCount + i, data[pageCount + i]);
    }

    // 发起停止信号 UCTXSTP=1
    UCB0CTLW0 |= UCTXSTP;
    // 等待UCTXSTP变为0
    while(UCB0CTLW0 & UCTXSTP);

}

void IICB0_Read(unsigned char devAddr, unsigned char byteAddr, unsigned char* rxBuf, int len){
    unsigned int i;
    // 设置设备地址
    IICB0_Set_Device_Address(devAddr);
    //IICB0_Set_Device_Address(0X50 << 1);
    // 设置为发送模式 UCTR=1
    UCB0CTLW0 |= UCTR;
    // 发起开始信号 UCTXSTT=1
    UCB0CTLW0 |= UCTXSTT;
    // 等待UCTXSTT变为0
    while(UCB0CTLW0 & UCTXSTT);
    // 等待UCTXIFG变为1
    while(!(UCB0IFG & UCTXIFG));
    // 向UCB0TXBUF填充数据（字地址）
    UCB0TXBUF = byteAddr;
    while(!(UCB0IFG & UCTXIFG));
    // 设置为接收模式 UCTR=0
    UCB0CTLW0 &= ~UCTR;

    // 发送开始信号 UCTXSTT=1
    UCB0CTLW0 |= UCTXSTT;
    // 等待字地址发送完成
    //while(!(UCB0IFG & UCTXIFG));

    // 等待UCTXSTT=0 此时设备地址又发送了一遍
    while(UCB0CTLW0 & UCTXSTT);

    // 等待UCRXIFG置1
    for(i = 0; i < len; i++){
        while(!(UCB0IFG & UCRXIFG));
        // 读取UCRXBUF寄存器
        rxBuf[i] = UCB0RXBUF;
    }
    // 发送停止信号 UXTCSTP=0
        UCB0CTLW0 |= UCTXSTP;
    // 等待UXTCSTP=0
    while(UCB0CTLW0 & UCTXSTP);
}
