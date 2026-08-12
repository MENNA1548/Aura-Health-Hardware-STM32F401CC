#ifndef MEXTI_INTERFACE_H_
#define MEXTI_INTERFACE_H_

#include "Std_type.h"

/*=============================================
    EXTI LINES
=============================================*/
typedef enum
{
    EXTI_LINE0 = 0,
    EXTI_LINE1,
    EXTI_LINE2,
    EXTI_LINE3,
    EXTI_LINE4,
    EXTI_LINE5,
    EXTI_LINE6,
    EXTI_LINE7,
    EXTI_LINE8,
    EXTI_LINE9,
    EXTI_LINE10,
    EXTI_LINE11,
    EXTI_LINE12,
    EXTI_LINE13,
    EXTI_LINE14,
    EXTI_LINE15
}EXTI_Line_t;


/*=============================================
    Trigger Types
=============================================*/
typedef enum
{
    EXTI_RISING_EDGE,
    EXTI_FALLING_EDGE,
    EXTI_ON_CHANGE
}EXTI_Trigger_t;


/*=============================================
    APIs
=============================================*/

void MEXTI_voidEnableInterrupt(EXTI_Line_t Copy_Line);

void MEXTI_voidDisableInterrupt(EXTI_Line_t Copy_Line);

void MEXTI_voidSetTrigger(EXTI_Line_t Copy_Line,
                          EXTI_Trigger_t Copy_Trigger);

void MEXTI_voidClearPendingFlag(EXTI_Line_t Copy_Line);

void MEXTI_voidSetCallBack(EXTI_Line_t Copy_Line,
                           void (*ptr)(void));

#endif
