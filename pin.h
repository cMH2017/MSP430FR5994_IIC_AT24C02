#ifndef _PIN_H
#define _PIN_H
#include "msp430fr5994.h"
// 配置引脚的宏函数，在开发过程中完善
#define Config_P16_UCB0SDA()    P1DIR |= BIT6;\
                                P1SEL0 &= ~BIT6;\
                                P1SEL1 |= BIT6;\
                                PM5CTL0 &= ~LOCKLPM5

#define Config_P16_Out()        P1DIR |= BIT6;\
                                P1SEL0 &= ~BIT6;\
                                P1SEL1 &= ~BIT6;\
                                PM5CTL0 &= ~LOCKLPM5

#define Config_P17_Pullup_In()  P1SEL0 &= ~BIT7;\
                                P1SEL1 &= ~BIT7;\
                                P1DIR &= ~BIT7;\
                                P1REN |= BIT7;\
                                P1OUT |= BIT7;\
                                PM5CTL0 &= ~LOCKLPM5
// 手册是错的，按着下面来
#define Config_P17_UCB0SCL()    P1DIR |= BIT7;\
                                P1SEL0 &= ~BIT7;\
                                P1SEL1 |= BIT7;\
                                P1REN &= ~BIT7;\
                                P1OUT &=~ BIT7;\
                                PM5CTL0 &= ~LOCKLPM5

#define Config_P17_Out()        P1DIR |= BIT7;\
                                P1SEL0 &= ~BIT7;\
                                P1SEL1 &= ~BIT7;\
                                PM5CTL0 &= ~LOCKLPM5

#define Config_P20_UCA0TXD()    P2DIR |= BIT0;\
                                P2SEL0 &= ~BIT0;\
                                P2SEL1 |= BIT0;\
                                PM5CTL0 &= ~LOCKLPM5

#define Config_P21_UCA0RXD()    P2DIR |= BIT1;\
                                P2SEL0 &= ~BIT1;\
                                P2SEL1 |= BIT1;\
                                PM5CTL0 &= ~LOCKLPM5

#define Config_P22_Pullup_Rasing_Edge_Interrupt()   P2DIR &= ~BIT2;\
                                                    P2REN |= BIT2;\
                                                    P2OUT |= BIT2;\
                                                    P2IES &= ~BIT2;\
                                                    P2IFG &= ~BIT2;\
                                                    P2IE |= BIT2;\
                                                    PM5CTL0 &= ~LOCKLPM5

#define Config_P23_Out()    P2DIR |= BIT3;\
                            P2SEL0 &= ~BIT3;\
                            P2SEL1 &= ~BIT3;\
                            PM5CTL0 &= ~LOCKLPM5

//SPIA1
#define Config_P24_UCA1CLK()  P2SEL0 &= ~BIT4;\
                              P2SEL1 |= BIT4;\
                              P2DIR |= BIT4;\
                              PM5CTL0 &= ~LOCKLPM5



#define Config_P25_UCA1SIMO()   P2SEL0 &= ~BIT5;\
                                P2SEL1 |= BIT5;\
                                P2DIR |= BIT5;\
                                PM5CTL0 &= ~LOCKLPM5

#define Config_P26_UCA1SOMI()   P2SEL0  &= ~BIT6;\
                                P2SEL1 |= BIT6;\
                                PM5CTL0 &= ~LOCKLPM5


// 板子上的P2.7焊接有问题 不要用
#define Config_P27_Out()    P2DIR |= BIT7;\
                            P2SEL0 &= ~BIT7;\
                            P2SEL1 &= ~BIT7;\
                            PM5CTL0 &= ~LOCKLPM5


#define Config_P30_Out()    P3DIR |= BIT0;\
                            P3SEL0 &= ~BIT0;\
                            P3SEL1 &= ~BIT0;\
                            P3OUT |= BIT0;\
                            PM5CTL0 &= ~LOCKLPM5


#define Config_P31_Out()    P3DIR |= BIT1;\
                            P3SEL0 &= ~BIT1;\
                            P3SEL1 &= ~BIT1;\
                            P3OUT |= BIT1;\
                            PM5CTL0 &= ~LOCKLPM5

#define Config_P35_Out()    P3DIR |= BIT5;\
                            P3SEL0 &= ~BIT5;\
                            P3SEL1 &= ~BIT5;\
                            P3OUT |= BIT5;\
                            PM5CTL0 &= ~LOCKLPM5

#define Config_P41_Out()    P4DIR |= BIT1;\
                            P4SEL0 &= ~BIT1;\
                            P4SEL1 &= ~BIT1;\
                            P4OUT |= BIT1;\
                            PM5CTL0 &= ~LOCKLPM5

#define Config_P45_Out()    P4DIR |= BIT5;\
                            P4SEL0 &= ~BIT5;\
                            P4SEL1 &= ~BIT5;\
                            P4OUT |= BIT5;\
                            PM5CTL0 &= ~LOCKLPM5

#define Config_P47_Out()    P4DIR |= BIT7;\
                            P4SEL0 &= ~BIT7;\
                            P4SEL1 &= ~BIT7;\
                            P4OUT |= BIT7;\
                            PM5CTL0 &= ~LOCKLPM5


#define Config_PJ0_SMCLK()  PJDIR |= BIT0;\
                            PJSEL0 |= BIT0;\
                            PJSEL1 &= ~BIT0;\
                            PM5CTL0 &= ~LOCKLPM5

#define Config_PJ1_MCLK()   PJDIR |= BIT1;\
                            PJSEL0 |= BIT1;\
                            PJSEL1 &= ~BIT1;\
                            PM5CTL0 &= ~LOCKLPM5

#define Config_PJ2_ACLK()   PJDIR |= BIT2;\
                            PJSEL0 |= BIT2;\
                            PJSEL1 &= ~BIT2;\
                            PM5CTL0 &= ~LOCKLPM5

#define Config_PJ4_LFXIN_CRYSTAL()  PJSEL0 |= BIT4;\
                                    PJSEL1 &= ~BIT4;\
                                    CSCTL4 &= ~LFXTBYPASS;\
                                    PM5CTL0 &= ~LOCKLPM5

#define Config_PJ5_LFXOUT_CRYSTAL() PJSEL0 |= BIT5;\
                                    PJSEL1 &= ~BIT5;\
                                    CSCTL4 &= ~LFXTBYPASS;\
                                    PM5CTL0 &= ~LOCKLPM5

// 对应板子P4[7]
#define Config_PJ6_Out()        PJDIR |= BIT6;\
                                PJSEL0 &= ~BIT7;\
                                PJSEL1 &= ~BIT7;\
                                PJSEL0 &= ~BIT6;\
                                PJSEL1 &= ~BIT6;\
                                CSCTL4 &= ~HFXTBYPASS;\
                                PJOUT |= BIT6;\
                                PM5CTL0 &= ~LOCKLPM5
// 对应板子P4[8]
#define Config_PJ7_Out()        PJDIR |= BIT7;\
                                PJSEL0 &= ~BIT7;\
                                PJSEL1 &= ~BIT7;\
                                PJSEL0 &= ~BIT6;\
                                PJSEL1 &= ~BIT6;\
                                CSCTL4 &= ~HFXTBYPASS;\
                                PJOUT |= BIT7;\
                                PM5CTL0 &= ~LOCKLPM5


#define Get_P17()   ((P1IN & BIT7) >> 7)
#define Get_P22()   ((P2IN & BIT2) >> 2)
#define Set_P23()   P2OUT |= BIT3
#define Clr_P23()   P2OUT &= ~BIT3
#define Set_P27()   P2OUT |= BIT7
#define Clr_P27()   P2OUT &= ~BIT7
#define Set_P35()   P3OUT |= BIT5
#define Clr_P35()   P3OUT &= ~BIT5
#define Set_P41()   P4OUT |= BIT1
#define Clr_P41()   P4OUT &= ~BIT1
#define Set_P47()   P4OUT |= BIT7
#define Clr_P47()   P4OUT &= ~BIT7
#define Toggle_PJ6() PJOUT ^= BIT6
#define Set_PJ6()   PJOUT |= BIT6
#define Clr_PJ6()   PJOUT &= ~BIT6
#define Set_PJ7()   PJOUT |= BIT7
#define Clr_PJ7()   PJOUT &= ~BIT7
#define Toggle_PJ7() PJOUT ^= BIT7


#endif
