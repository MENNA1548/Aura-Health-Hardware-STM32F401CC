#ifndef MGPIO_PRIVATE_H_
#define MGPIO_PRIVATE_H_

#include "Std_type.h"


/*=========================================================
 * GPIO Register Definition
 *=========================================================*/

typedef struct
{
    volatile u32 MODER;      /* 0x00 */
    volatile u32 OTYPER;     /* 0x04 */
    volatile u32 OSPEEDR;    /* 0x08 */
    volatile u32 PUPDR;      /* 0x0C */
    volatile u32 IDR;        /* 0x10 */
    volatile u32 ODR;        /* 0x14 */
    volatile u32 BSRR;       /* 0x18 */
    volatile u32 LCKR;       /* 0x1C */
    volatile u32 AFRL;       /* 0x20 */
    volatile u32 AFRH;       /* 0x24 */

} GPIO_t;



/*=========================================================
 * GPIO Base Addresses
 *=========================================================*/

#define GPIOA_BASE_ADDRESS     0x40020000UL
#define GPIOB_BASE_ADDRESS     0x40020400UL
#define GPIOC_BASE_ADDRESS     0x40020800UL



/*=========================================================
 * GPIO Peripheral Definitions
 *=========================================================*/

#define GPIOA   ((volatile GPIO_t *)GPIOA_BASE_ADDRESS)
#define GPIOB   ((volatile GPIO_t *)GPIOB_BASE_ADDRESS)
#define GPIOC   ((volatile GPIO_t *)GPIOC_BASE_ADDRESS)



#define GPIO_MASK 3



#endif /* MGPIO_PRIVATE_H_ */
