/************************************************************
 * File Name : MNVIC_Program.c
 * Author    :
 * Layer     : MCAL
 ************************************************************/

#include "Std_type.h"

#include "MNVIC_Interface.h"
#include "MNVIC_Private.h"

/*=========================================================
 * SCB AIRCR Register
 *========================================================*/
#define SCB_AIRCR   (*(volatile u32 *)0xE000ED0CUL)

/*=========================================================
 * Set Priority Grouping
 *========================================================*/
void NVIC_SetPriorityGrouping(u32 priority_grouping)
{
    SCB_AIRCR = priority_grouping;
}

/*=========================================================
 * Enable Interrupt
 *========================================================*/
void NVIC_EnableIRQ(IRQn_t IRQn)
{
    NVIC->ISER[IRQn / 32] = (1UL << (IRQn % 32));
}

/*=========================================================
 * Disable Interrupt
 *========================================================*/
void NVIC_DisableIRQ(IRQn_t IRQn)
{
    NVIC->ICER[IRQn / 32] = (1UL << (IRQn % 32));
}

/*=========================================================
 * Get Pending Interrupt
 *========================================================*/
u32 NVIC_GetPendingIRQ(IRQn_t IRQn)
{
    return ((NVIC->ISPR[IRQn / 32] >> (IRQn % 32)) & 1UL);
}

/*=========================================================
 * Set Pending Interrupt
 *========================================================*/
void NVIC_SetPendingIRQ(IRQn_t IRQn)
{
    NVIC->ISPR[IRQn / 32] = (1UL << (IRQn % 32));
}

/*=========================================================
 * Clear Pending Interrupt
 *========================================================*/
void NVIC_ClearPendingIRQ(IRQn_t IRQn)
{
    NVIC->ICPR[IRQn / 32] = (1UL << (IRQn % 32));
}

/*=========================================================
 * Get Active Interrupt
 *========================================================*/
u32 NVIC_GetActive(IRQn_t IRQn)
{
    return ((NVIC->IABR[IRQn / 32] >> (IRQn % 32)) & 1UL);
}

/*=========================================================
 * Set Interrupt Priority
 *========================================================*/
void NVIC_SetPriority(IRQn_t IRQn, u32 priority)
{
    /*
     * STM32F401 implements only the upper 4 bits
     * of each priority register.
     */
    NVIC->IPR[IRQn] = (u8)(priority << 4);
}

/*=========================================================
 * Get Interrupt Priority
 *========================================================*/
u32 NVIC_GetPriority(IRQn_t IRQn)
{
    return (NVIC->IPR[IRQn] >> 4);
}

/*=========================================================
 * System Reset
 *========================================================*/
void NVIC_SystemReset(void)
{
    /* Write VECTKEY and SYSRESETREQ */
    SCB_AIRCR = (0x5FA << 16) | (1UL << 2);
}
void NVIC_GenerateSoftwareInterrupt(IRQn_t IRQn)
{
    NVIC->STIR = (u32)IRQn;
}
