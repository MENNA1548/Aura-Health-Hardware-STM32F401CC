#include "Std_type.h"

#include "MEXTI_Interface.h"
#include "MEXTI_Private.h"

static void (*EXTI_CallBack[16])(void) = {0};


/*************************************************
 Enable Interrupt
**************************************************/
void MEXTI_voidEnableInterrupt(EXTI_Line_t Copy_Line)
{
    EXTI->IMR |= (1<<Copy_Line);
}


/*************************************************
 Disable Interrupt
**************************************************/
void MEXTI_voidDisableInterrupt(EXTI_Line_t Copy_Line)
{
    EXTI->IMR &= ~(1<<Copy_Line);
}


/*************************************************
 Set Trigger Edge
**************************************************/
void MEXTI_voidSetTrigger(EXTI_Line_t Copy_Line,
                          EXTI_Trigger_t Copy_Trigger)
{

    switch(Copy_Trigger)
    {

    case EXTI_RISING_EDGE:

        EXTI->RTSR |= (1<<Copy_Line);
        EXTI->FTSR &= ~(1<<Copy_Line);

        break;


    case EXTI_FALLING_EDGE:

        EXTI->FTSR |= (1<<Copy_Line);
        EXTI->RTSR &= ~(1<<Copy_Line);

        break;


    case EXTI_ON_CHANGE:

        EXTI->RTSR |= (1<<Copy_Line);
        EXTI->FTSR |= (1<<Copy_Line);

        break;

    }

}


/*************************************************
 Clear Pending Flag
**************************************************/
void MEXTI_voidClearPendingFlag(EXTI_Line_t Copy_Line)
{
    EXTI->PR = (1<<Copy_Line);
}


/*************************************************
 Callback Function
**************************************************/
void MEXTI_voidSetCallBack(EXTI_Line_t Copy_Line,
                           void (*ptr)(void))
{
    EXTI_CallBack[Copy_Line] = ptr;
}


/*************************************************
 ISR
**************************************************/

void EXTI0_IRQHandler(void)
{
    MEXTI_voidClearPendingFlag(EXTI_LINE0);

    if(EXTI_CallBack[0] != 0)
    {
        EXTI_CallBack[0]();
    }
}


void EXTI1_IRQHandler(void)
{
    MEXTI_voidClearPendingFlag(EXTI_LINE1);

    if(EXTI_CallBack[1] != 0)
    {
        EXTI_CallBack[1]();
    }
}


void EXTI2_IRQHandler(void)
{
    MEXTI_voidClearPendingFlag(EXTI_LINE2);

    if(EXTI_CallBack[2] != 0)
    {
        EXTI_CallBack[2]();
    }
}


void EXTI3_IRQHandler(void)
{
    MEXTI_voidClearPendingFlag(EXTI_LINE3);

    if(EXTI_CallBack[3] != 0)
    {
        EXTI_CallBack[3]();
    }
}


void EXTI4_IRQHandler(void)
{
    MEXTI_voidClearPendingFlag(EXTI_LINE4);

    if(EXTI_CallBack[4] != 0)
    {
        EXTI_CallBack[4]();
    }
}
