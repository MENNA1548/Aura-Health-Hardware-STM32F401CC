
#include "Std_type.h"

#include "MSTK_Interface.h"
#include "MSTK_Private.h"


void MSTK_voidInit(void)
{
#if MSTK_CLOCK_SOURCE == MSTK_AHB
    SET_BIT(MSTK->CTRL, CLKSOURCE);

#elif MSTK_CLOCK_SOURCE == MSTK_AHB_DIV_8
    CLR_BIT(MSTK->CTRL, CLKSOURCE);

#endif
}

void MSTK_voidStart(u32 Copy_u32LoadValue)
{
    MSTK->LOAD = Copy_u32LoadValue - 1;

    MSTK->VAL = 0;

    SET_BIT(MSTK->CTRL, ENABLE);
}

void MSTK_voidStop(void)
{
    CLR_BIT(MSTK->CTRL, ENABLE);
}

u32 MSTK_u32GetElapsedTime(void)
{
    return (MSTK->LOAD - MSTK->VAL);
}

u32 MSTK_u32GetRemainingTime(void)
{
    return MSTK->VAL;
}



void MSTK_voidSetBusyWait(u32 Copy_u32Ticks)
{
    /* Stop SysTick */
    CLR_BIT(MSTK->CTRL, ENABLE);

    /* Load the required ticks */
    MSTK->LOAD = Copy_u32Ticks - 1;

    /* Clear current value */
    MSTK->VAL = 0;

    /* Start timer */
    SET_BIT(MSTK->CTRL, ENABLE);

    /* Wait until COUNTFLAG becomes 1 */
    while(GET_BIT(MSTK->CTRL, COUNTFLAG) == 0);

    /* Stop timer */
    CLR_BIT(MSTK->CTRL, ENABLE);

    /* Clear registers */
    MSTK->LOAD = 0;
    MSTK->VAL  = 0;
}
