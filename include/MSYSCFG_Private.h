/**************************************************************
 * File Name : MSYSCFG_Private.h
 * Author    : Your Name
 * Layer     : MCAL
 **************************************************************/

#ifndef MSYSCFG_PRIVATE_H_
#define MSYSCFG_PRIVATE_H_

#include "Std_type.h"

/*=========================================================
                Base Address
=========================================================*/

#define SYSCFG_BASE_ADDRESS     0x40013800UL

/*=========================================================
                SYSCFG Registers
=========================================================*/

typedef struct
{
    volatile u32 MEMRMP;       //0x00
    volatile u32 PMC;          //0x04
    volatile u32 EXTICR[4];    //0x08 - 0x14
    volatile u32 RESERVED[2];
    volatile u32 CMPCR;        //0x20

}SYSCFG_t;

#define SYSCFG    ((volatile SYSCFG_t*)SYSCFG_BASE_ADDRESS)

#endif
