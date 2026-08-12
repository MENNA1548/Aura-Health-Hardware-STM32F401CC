#ifndef MEXTI_PRIVATE_H_
#define MEXTI_PRIVATE_H_

#include "Std_type.h"

#define EXTI_BASE_ADDRESS     0x40013C00UL

typedef struct
{
    volatile u32 IMR;
    volatile u32 EMR;
    volatile u32 RTSR;
    volatile u32 FTSR;
    volatile u32 SWIER;
    volatile u32 PR;

}EXTI_t;

#define EXTI    ((volatile EXTI_t*)EXTI_BASE_ADDRESS)

#endif
