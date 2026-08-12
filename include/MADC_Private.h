#ifndef MADC_PRIVATE_H_
#define MADC_PRIVATE_H_

#include "Std_type.h"


/*==============================
 ADC1 Base Address
==============================*/

#define ADC1_BASE_ADDRESS   0x40012000UL



/*==============================
 ADC Register Map
==============================*/

typedef struct
{

    volatile u32 SR;          /* 0x00 Status Register */

    volatile u32 CR1;         /* 0x04 Control Register 1 */

    volatile u32 CR2;         /* 0x08 Control Register 2 */

    volatile u32 SMPR1;       /* 0x0C Sample time 1 */

    volatile u32 SMPR2;       /* 0x10 Sample time 2 */

    volatile u32 JOFR1;

    volatile u32 JOFR2;

    volatile u32 JOFR3;

    volatile u32 JOFR4;

    volatile u32 HTR;

    volatile u32 LTR;

    volatile u32 SQR1;

    volatile u32 SQR2;

    volatile u32 SQR3;

    volatile u32 JSQR;

    volatile u32 JDR1;

    volatile u32 JDR2;

    volatile u32 JDR3;

    volatile u32 JDR4;

    volatile u32 DR;


}ADC_t;



#define ADC1   ((volatile ADC_t*)ADC1_BASE_ADDRESS)



/*==============================
 ADC Status Bits
==============================*/


#define ADC_SR_EOC       1



/*==============================
 ADC Control Bits
==============================*/


#define ADC_CR2_ADON     0

#define ADC_CR2_SWSTART  30



#endif
