#include "clock.h"
/*
复位状态的时钟：
LFXT()→LFXTCLK→ACLK
DCOCLK/8→MCLK & SMCLK
LFXTIN LFXTOUT需要配置IO口才能使用
VLOCLK = 10 kHz
*/




/*
 * 设置完以后：
 * LFXT→ ACLK
 * DCOCLK（8MHz）→ MCLK & SMCLK
 */
// 手册建议时钟不要超过16MHz
void Clock_System_Init(void){
    CSCTL0 = CSKEY;         // 解锁



    CSCTL1 = DCOFRE_1MHz;     // Set DCO to 1MHz

    // Set SMCLK = MCLK = DCO, ACLK = LFXTCLK
    CSCTL2 = SELA__LFXTCLK |\
             SELS__DCOCLK  |\
             SELM__DCOCLK;

    // Per Device Errata set divider to 4 before changing frequency to
    // prevent out of spec operation from overshoot transient
    CSCTL3 = DIVA__4 | DIVS__4 | DIVM__4;     // Set all corresponding clk sources to divide by 4 for errata
    CSCTL1 = DCOFRE_8MHz;                     // Set DCO to 8MHz
    __delay_cycles(60);
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;

    Config_PJ4_LFXIN_CRYSTAL();
    Config_PJ5_LFXOUT_CRYSTAL();
    __delay_cycles(60);

}

