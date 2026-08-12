
#ifndef MSTK_PRIVATE_H
#define MSTK_PRIVATE_H

#define STK_BASE_ADDRESS     0xE000E010

typedef struct
{
    volatile u32 CTRL;
    volatile u32 LOAD;
    volatile u32 VAL;
    volatile u32 CALIB;

}STK_t;

#define MSTK   ((volatile STK_t*)STK_BASE_ADDRESS)

/* CTRL Register Bits */
#define ENABLE      0
#define TICKINT     1
#define CLKSOURCE   2
#define COUNTFLAG   16

#endif
