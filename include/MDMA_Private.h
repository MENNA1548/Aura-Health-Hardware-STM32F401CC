#ifndef MDMA_PRIVATE_H_
#define MDMA_PRIVATE_H_

#include "Std_type.h"

/************************************************
 * Base Addresses
 ***********************************************/

#define DMA1_BASE_ADDRESS      0x40026000UL
#define DMA2_BASE_ADDRESS      0x40026400UL

/************************************************
 * Stream Registers
 ***********************************************/

typedef struct
{
    volatile u32 CR;
    volatile u32 NDTR;
    volatile u32 PAR;
    volatile u32 M0AR;
    volatile u32 M1AR;
    volatile u32 FCR;

}DMA_StreamReg_t;


/************************************************
 * DMA Registers
 ***********************************************/

typedef struct
{
    volatile u32 LISR;
    volatile u32 HISR;
    volatile u32 LIFCR;
    volatile u32 HIFCR;

    DMA_StreamReg_t STREAM[8];

}DMA_RegDef_t;


/************************************************
 * Pointers
 ***********************************************/

#define DMA1_REG ((volatile DMA_RegDef_t*)DMA1_BASE_ADDRESS)
#define DMA2_REG ((volatile DMA_RegDef_t*)DMA2_BASE_ADDRESS)

#endif
