/**************************************************************
 * File Name : MUART_Private.h
 **************************************************************/

#ifndef MUART_PRIVATE_H_
#define MUART_PRIVATE_H_

#include "Std_type.h"

/**************************************************************
                    USART Registers
**************************************************************/

typedef struct
{

    volatile u32 SR;
    volatile u32 DR;
    volatile u32 BRR;
    volatile u32 CR1;
    volatile u32 CR2;
    volatile u32 CR3;
    volatile u32 GTPR;

}USART_t;

/**************************************************************
                    Base Addresses
**************************************************************/

#define USART1_BASE_ADDRESS      0x40011000UL
#define USART2_BASE_ADDRESS      0x40004400UL
#define USART6_BASE_ADDRESS      0x40011400UL

#define USART1 ((volatile USART_t*)USART1_BASE_ADDRESS)
#define USART2 ((volatile USART_t*)USART2_BASE_ADDRESS)
#define USART6 ((volatile USART_t*)USART6_BASE_ADDRESS)

/**************************************************************
                     Status Register Bits
**************************************************************/

#define PE      0
#define FE      1
#define NE      2
#define ORE     3
#define IDLE    4
#define RXNE    5
#define TC      6
#define TXE     7
#define LBD     8
#define CTS     9

/**************************************************************
                    Control Register1 Bits
**************************************************************/

#define SBK     0
#define RWU     1
#define RE      2
#define TE      3
#define IDLEIE  4
#define RXNEIE  5
#define TCIE    6
#define TXEIE   7
#define PEIE    8
#define PS      9
#define PCE     10
#define WAKE    11
#define M       12
#define UE      13

/**************************************************************
                    Control Register2 Bits
**************************************************************/

#define STOP0   12
#define STOP1   13

#endif
