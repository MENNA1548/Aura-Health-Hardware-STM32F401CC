/**************************************************************
 * File Name : MSYSCFG_Program.c
 * Author    : Your Name
 * Layer     : MCAL
 **************************************************************/

#include "Std_type.h"

#include "MSYSCFG_Interface.h"
#include "MSYSCFG_Private.h"

/*=========================================================
        Configure GPIO Port for EXTI Line
=========================================================*/

void MSYSCFG_voidSetEXTIConfiguration(EXTI_Line_t Copy_Line,
                                      Ports_t Copy_Port)
{
    u8 Local_Register;
    u8 Local_Position;

    /*
        EXTI0~3  -> EXTICR0
        EXTI4~7  -> EXTICR1
        EXTI8~11 -> EXTICR2
        EXTI12~15-> EXTICR3
    */

    Local_Register = Copy_Line / 4;

    /*
        Line0  -> bits0:3
        Line1  -> bits4:7
        Line2  -> bits8:11
        Line3  -> bits12:15
    */

    Local_Position = (Copy_Line % 4) * 4;

    /* Clear old port selection */

    SYSCFG->EXTICR[Local_Register] &= ~(0x0F << Local_Position);

    /* Select new port */

    SYSCFG->EXTICR[Local_Register] |=
            (Copy_Port << Local_Position);
}
