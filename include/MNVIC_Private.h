#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

#include "Std_type.h"

/*================== NVIC Base Address ==================*/

#define NVIC_BASE_ADDRESS    0xE000E100UL

/*================== NVIC Register Map ==================*/

typedef struct
{
    volatile u32 ISER[8];       /* 0x000 - 0x01C */
    u32 RESERVED0[24];

    volatile u32 ICER[8];       /* 0x080 - 0x09C */
    u32 RESERVED1[24];

    volatile u32 ISPR[8];       /* 0x100 - 0x11C */
    u32 RESERVED2[24];

    volatile u32 ICPR[8];       /* 0x180 - 0x19C */
    u32 RESERVED3[24];

    volatile u32 IABR[8];       /* 0x200 - 0x21C */
    u32 RESERVED4[56];

    volatile u8 IPR[240];       /* 0x300 - 0x3EF */

    u32 RESERVED5[580];

    volatile u32 STIR;          /* 0xF00 */

} NVIC_t;

/*================== NVIC Pointer ==================*/

#define NVIC ((volatile NVIC_t *)NVIC_BASE_ADDRESS)

#endif /* NVIC_PRIVATE_H_ */
